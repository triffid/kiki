/*
 *  KPickHandler.cpp
 *  kodisein
 */

#include "KPickHandler.h"
#include "KEventHandler.h"
#include "KPerspectiveProjection.h"
#include "KConsole.h"

#include <algorithm>
#include <SDL.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KPickHandler, KObject)

// --------------------------------------------------------------------------------------------------------
KPickHandler::KPickHandler () : KObject ()
{    
    depth 	 	= 0;
    picked_pickable	= NULL;
    projection		= NULL;
    reset_projection 	= NULL;
    last_time		= 0;
    
    flags.resize (KDL_PICKHANDLER_FLAG_END);
    flags[KDL_PICKHANDLER_FLAG_FOCUS_ON_ENABLED]   	= false;
    flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED] 	= false;
    flags[KDL_PICKHANDLER_FLAG_MENU_ENABLED] 		= false;
    flags[KDL_PICKHANDLER_FLAG_MOVING_ENABLED] 		= false;
    flags[KDL_PICKHANDLER_FLAG_TRANSPARENT_ZERO]	= false;
    flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS]   		= false;
    flags[KDL_PICKHANDLER_FLAG_DOUBLECLICK_ENABLED] 	= true;
    flags[KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED] 	= true;
}

// --------------------------------------------------------------------------------------------------------
KPickHandler::~KPickHandler ()
{
    if (projection) delete projection;
}

// --------------------------------------------------------------------------------------------------------
// handles a mouse button down event at mousePos
// returns true if a pickable was hit

bool KPickHandler::pick ( const KMouseEvent & event )
{
    GLuint	hits, minDepth = (GLuint)-1, * p;
    GLint	picked_id;
    GLuint	selectBuffer[2560];
    
    glSelectBuffer 	(2560, selectBuffer);

    glRenderMode	(GL_SELECT);
    glInitNames		();

    glMatrixMode	(GL_MODELVIEW);
    glPushMatrix	();
    glMatrixMode	(GL_PROJECTION);
    glPushMatrix	();
    glLoadIdentity	();
    gluPickMatrix	(event.pos.x, event.pos.y, 3.0, 3.0, (GLint*)getProjection()->getViewport());
    getProjection()->apply();
    
    // render pickables
    displayPickables	( KEventHandler::getApplicationMode() );

    glMatrixMode	(GL_PROJECTION);
    glPopMatrix		();
    glMatrixMode	(GL_MODELVIEW);
    glPopMatrix		();
    
    hits = glRenderMode (GL_RENDER);
    
    if (hits < 0) KConsole::printError("selection buffer overflow!");
    
    p = selectBuffer;
    picked_id	= 0;
    
    for (GLuint i = 0; i < hits; i++) 
    {
        GLuint numNames = *p; p++; // number of names
               
        GLuint pickableDepth;
        
        pickableDepth = *p; p++; 		    // first depth value
        pickableDepth = kMin(*p, pickableDepth); p++; // second depth value
                
        while (numNames > 0)
        {
            if (pickableDepth <= minDepth && (flags[KDL_PICKHANDLER_FLAG_TRANSPARENT_ZERO] || (*p > 0))) 
            {	
                if (flags[KDL_PICKHANDLER_FLAG_TRANSPARENT_ZERO] || *p > 0)
                {
                    minDepth = pickableDepth;
                    picked_id = *p;
                }
            }
            numNames--;
            p++;
        }
    }

    if (picked_id > 0)
    {
        KPickable * pickable = (KPickable*)getPickableWithId(picked_id);

        KPickable * last_picked_pickable = picked_pickable;
        unpick();
                
        if (pickable == NULL) 
        {
            KConsole::printError(kStringPrintf("id %d found, but no pickable!", picked_id));
            return false;
        }
        if (shouldPick(pickable))
        {
            picked_pickable = (KPickable *)pickable;
            picked_pickable->setPicked(true);

            flags[KDL_PICKHANDLER_FLAG_MOVING_ENABLED] = true;
            KEventHandler::release_handler = this;

            if (flags[KDL_PICKHANDLER_FLAG_DOUBLECLICK_ENABLED])
            {
                unsigned int thisTime = SDL_GetTicks();
                if ((thisTime-last_time < 700) && (last_picked_pickable == picked_pickable))
                {
                    doubleClicked();
                    last_time = thisTime;
                    return true;
                }
                last_time = thisTime;
            }
            picked ();  // notification
        }
    }
    else if (flags[KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED])
    {
        unpick();
    }

    if (flags[KDL_PICKHANDLER_FLAG_MENU_ENABLED] && (SDL_GetModState() & KMOD_CTRL))
    {
        displayMenu(); return true;
    }
        
    return picked_id;
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::pickPickable ( KPickable * pickable )
{
    unpick();
    picked_pickable = (KPickable *)pickable;
    picked_pickable->setPicked(true);
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::addPickable ( KPickable * pickable )
{
    pickables.push_back(pickable);
    initializeIds();
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::deletePickable ( KPickable * pickable )
{
    removePickable(pickable);
    delete pickable;
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::deleteAllPickables ()
{
    picked_pickable = NULL;
    while (pickables.empty() == false)
    {
        deletePickable(pickables.back());
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::removeAllPickables ()
{
    picked_pickable = NULL;
    while (pickables.empty() == false)
    {
        removePickable(pickables.back());
    }
}

// --------------------------------------------------------------------------------------------------------
// removes pickable from list of all pickables without deleting it
void KPickHandler::removePickable( KPickable * pickable )
{
    if (picked_pickable)
    {
        if (picked_pickable == pickable || 
                (pickable->hasSubPickables() && 
                 pickableWithIdInVector (picked_pickable->getId(), pickable->getSubPickables()) != NULL)) 
        {
            picked_pickable = NULL;
        }
    }
    
    PickableVector::iterator result = std::find(pickables.begin(), pickables.end(), pickable);
    if (result != pickables.end())
    {
        if (pickable->isPicked()) 
        {
            pickable->setPicked(false);
        }
        pickables.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::displayPickables ( int mode )
{
    PickableVector::const_iterator iter = pickables.begin();
    while (iter != pickables.end())
    {
        glPushMatrix();
        (*iter)->display(mode);
        glPopMatrix();
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::display ( int mode )
{
    getProjection()->initProjection();
    displayPickables( mode );
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::release ( const KMouseEvent & )
{
    flags[KDL_PICKHANDLER_FLAG_MOVING_ENABLED] = false;
}

// --------------------------------------------------------------------------------------------------------
bool KPickHandler::mouseMotion ( const KMouseEvent & mouseEvent )
{
    if (flags[KDL_PICKHANDLER_FLAG_MOVING_ENABLED] && picked_pickable != NULL)
    {
        moved(mouseEvent);
        return true;
    }
    
    return false;
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::unpick ()
{    
    if (picked_pickable) 
    {	
        picked_pickable->setPicked(false);
        unpicked();
        picked_pickable = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::unpickAllInVector (const PickableVector * pv)
{
    PickableVector::const_iterator iter = pv->begin();

    while (iter != pv->end())
    {
        (*iter)->setPicked(false);
        if ((*iter)->hasSubPickables())
        {
            unpickAllInVector((*iter)->getSubPickables());    
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::unpickAll ()
{
    unpickAllInVector(&pickables);
    unpick();
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::updateProjectionFromEventInMode ( KProjection * proj, 
                                                    const KMouseEvent & mouseEvent, int mouseMode )
{
    if (mouseMode == KDL_MOUSE_MODE_TRANSLATE)
    {
        if (SDL_GetModState() & KMOD_SHIFT)
        {
            proj->translate( 0.0, 0.0, -kAbsMax(mouseEvent.delta.x, mouseEvent.delta.y) / 10.0 );
        }
        else
        {
            proj->translate(-mouseEvent.delta.x / 10.0, -mouseEvent.delta.y / 10.0, 0.0 );
        }
    }
    else if (mouseMode == KDL_MOUSE_MODE_SCALE)
    {
        GLfloat f =  1.0 - kAbsMax(mouseEvent.delta.x, mouseEvent.delta.y) / 200.0;
        
        if (SDL_GetModState() & KMOD_SHIFT)
        {
            proj->setFov(proj->getFov() * f);
        }
        else
        {
            proj->setEyeDistance(proj->getEyeDistance() * f);
        }
    }
    else if (mouseMode == KDL_MOUSE_MODE_ROTATE)
    {
        KSize screenSize = KEventHandler::getScreenSize();

        if (SDL_GetModState() & KMOD_SHIFT)
        {
            float rot = 360.0;
            
            if (kAbs(mouseEvent.delta.x) > kAbs(mouseEvent.delta.y))
            {
                if (mouseEvent.pos.y < screenSize.h/2.0) rot *= -1;
                proj->rotate(0.0, 0.0, mouseEvent.delta.x * rot/screenSize.w);
            }
            else
            {
                if (mouseEvent.pos.x > screenSize.w/2.0) rot *= -1;
                proj->rotate(0.0, 0.0, mouseEvent.delta.y * rot/screenSize.h);
            }
        }
        else 
        {
            proj->rotate (mouseEvent.delta.y * 180.0 / screenSize.h, 
                         -mouseEvent.delta.x * 360.0 / screenSize.w, 0.0);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::updateProjection ( const KMouseEvent & mouseEvent )
{
    if (isProjectionEnabled())
    {
        if (SDL_GetModState() & KMOD_CTRL || mouseEvent.button_state == SDL_BUTTON(3))
        {
            KEventHandler::setMouseMode(KDL_MOUSE_MODE_TRANSLATE);
        }
        else if (SDL_GetModState() & KMOD_ALT || mouseEvent.button_state == SDL_BUTTON(2))
        {
            KEventHandler::setMouseMode(KDL_MOUSE_MODE_SCALE);
        }

        updateProjectionFromEventInMode (getProjection(), mouseEvent, KEventHandler::getMouseMode());
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::setProjection ( const KProjection * p ) 
{
    if (projection)
    {
        delete projection;
    }
    
    projection = p->copy();
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::setResetProjection()
{
    if (reset_projection)
    {	
        delete reset_projection;
    }
    
    reset_projection = projection->copy();
}

// --------------------------------------------------------------------------------------------------------
const KProjection * KPickHandler::getResetProjection() const
{
    if (reset_projection == NULL)
    {
        ((KPickHandler*)this)->reset_projection = new KPerspectiveProjection();
    }
        
    return reset_projection;
}

// --------------------------------------------------------------------------------------------------------
const KPickable * KPickHandler::getParentOfPickable( const KPickable * child ) const
{
    return parentOfPickableInVector (child, &pickables);
}

// --------------------------------------------------------------------------------------------------------
const KPickable * KPickHandler::getPickableWithId ( int i ) const
{
    return pickableWithIdInVector (i, &pickables);
}

// --------------------------------------------------------------------------------------------------------
const KPickable * KPickHandler::pickableWithIdInVector ( int i, const PickableVector * pv ) const
{
    PickableVector::const_iterator iter = pv->begin();

    while (iter != pv->end())
    {
        if ((*iter)->getId() == i)
        {
            return (*iter);
        }
        if ((*iter)->hasSubPickables() && (*iter)->getMinId() <= i && (*iter)->getMaxId() >= i)
        {
            const KPickable * pickable = pickableWithIdInVector (i, (*iter)->getSubPickables());
            if (pickable) return pickable;
        }
        iter++;
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
const KPickable * KPickHandler::parentOfPickableInVector 
                                                ( const KPickable * child, const PickableVector * pv ) const
{
    PickableVector::const_iterator iter = pv->begin();

    while (iter != pv->end())
    {
        if ((*iter)->hasSubPickables())
        {
            const KPickable * pickable = pickableWithIdInVector (child->getId(), (*iter)->getSubPickables());
            if (pickable) return (*iter);
            pickable = parentOfPickableInVector(child, (*iter)->getSubPickables());
            if (pickable) return pickable;
        }
        iter++;
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::initializeIdsInVector ( const PickableVector * pv, int & max_id ) const
{
    PickableVector::const_iterator iter = pv->begin();

    while (iter != pv->end())
    {
        (*iter)->setId(++max_id);

        if ((*iter)->hasSubPickables())
        {
            (*iter)->setMinId(max_id+1);
            initializeIdsInVector((*iter)->getSubPickables(), max_id);
            (*iter)->setMaxId(max_id);
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KPickHandler::initializeIds ()
{
    int max_id = 0;
    initializeIdsInVector(&pickables, max_id);
}


