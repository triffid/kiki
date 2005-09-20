/*
 *  KikiWorld.cpp
 */

#include "KikiWorld.h"
#include "KikiSound.h"
#include "KikiPlayer.h"
#include "KikiPython.h"
#include "KikiText.h"
#include "KikiBotFume.h"

#include "KikiItems.h"

#include "KikiTools.h"
#include "KikiAction.h"

#include <KLightingProjection.h>
#include <KTools.h>
#include <KConsole.h>

#include <map>
#include <algorithm>

KDL_CLASS_INTROSPECTION   (KikiWorld)

#undef  KIKI_COLOR_VALUES
#define KIKI_COLOR_VALUES(a,b)

KIKI_COLOR_VALUES_1	  (KikiWorld, plate)

// __________________________________________________________________________________________________
KikiWorld::KikiWorld () : KPickHandler ()
{
    display_list = 0;

    depth	 	= -INT_MAX;
    camera_mode	 	= CAMERA_BEHIND;
    
    edit_projection	= NULL;
    edit_mode		= false;
    debug_camera	= false;
    debug_cells		= false;

    flags[KDL_PICKHANDLER_FLAG_MOVING_ENABLED]     = true;
    flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED] = true;
    
    flags.resize(WORLD_END);
    flags[DISPLAY_BORDER]	= true;
    flags[DISPLAY_DOTS]		= false;
    flags[DISPLAY_RASTER]	= true;  
    flags[DISPLAY_SHADOWS]	= false;
    
    raster_size			= 0.1;

    KEventHandler::notification_center.addReceiverCallback((KPickHandler*)this, 
                                                        (KCallbackPtr)&KikiWorld::reinit,
                                                        KDL_NOTIFICATION_TYPE_VIDEO_MODE_CHANGED);    

    KEventHandler::notification_center.addReceiverCallback((KPickHandler*)this, 
                                                        (KCallbackPtr)&KikiWorld::reinit,
                                                        KDL_NOTIFICATION_TYPE_WINDOW_SIZE_CHANGED);
                                                        
    initializeTextures ();
}

// __________________________________________________________________________________________________
KikiWorld::~KikiWorld ()
{
    deleteAllObjects();
}

// __________________________________________________________________________________________________
KikiCell * KikiWorld::getCellAtPos ( const KikiPos & pos ) const
{
    if (isValidPos (pos))
    {
        return cells[posToIndex(pos)];
    }
    return NULL;
}

// __________________________________________________________________________________________________
KikiBot * KikiWorld::getBotAtPos ( const KikiPos & pos ) const
{
    return (KikiBot*)getObjectOfTypeAtPos (KikiBot::classId(), pos);
}

// __________________________________________________________________________________________________
KikiObjectList KikiWorld::getObjectsOfTypeAtPos ( const KClassId & classId, const KikiPos & pos ) const
{
    KikiCell * cell = getCellAtPos (pos);
    if (cell)
    {
        return cell->getObjectsOfType (classId);
    }
    return KikiObjectList();
}

// __________________________________________________________________________________________________
KikiObjectList KikiWorld::getObjectsOfType ( const KClassId & classId ) const
{
    KikiObjectList object_list;

    for (KikiObjectList::const_iterator iter = objects.begin(); iter != objects.end(); iter++)
    {
        if ((*iter)->getClassId() >= classId)
        {
            object_list.push_back (*iter);
        }
    }
    
    return object_list;
}

// __________________________________________________________________________________________________
KikiObject * KikiWorld::getObjectOfTypeAtPos ( const KClassId & classId, const KikiPos & pos ) const
{
    KikiCell * cell = getCellAtPos (pos);
    if (cell)
    {
        return cell->getRealObjectOfType (classId);
    }
    return NULL;
}

// __________________________________________________________________________________________________
KikiObject * KikiWorld::getRealOccupantAtPos ( const KikiPos & pos ) const
{
    KikiObject * occupant = getOccupantAtPos (pos);
    if (occupant && occupant->getClassId() >= KikiTmpObject::classId())
    {
        return ((KikiTmpObject*)occupant)->object;
    }
    
    return occupant;
}

// __________________________________________________________________________________________________
KikiObject * KikiWorld::getOccupantAtPos ( const KikiPos & pos ) const
{
    KikiCell * cell = getCellAtPos (pos);
    if (cell)
    {
        return cell->getOccupant ();
    }
    return NULL;
}

// __________________________________________________________________________________________________
void KikiWorld::setObjectAtPos ( KikiObject * object, const KikiPos & pos )
{
    if (isInvalidPos(pos))
    {
        KConsole::printError (kStringPrintf("KikiWorld::setObjectAtPos pos [%d %d %d] is invalid!",
                                                pos.x, pos.y, pos.z));
        return;
    }
    
    KikiCell * cell = getCellAtPos (pos);
    
    if (object->isSpaceEgoistic() && cell && cell->getOccupant())
    {
        KikiObject * objectAtNewPos = cell->getOccupant();
        if (objectAtNewPos->getClassId() >= KikiTmpObject::classId())
        {
            if (((KikiTmpObject*)objectAtNewPos)->time > 0)
            {
                KConsole::printf ("WARNING KikiWorld::setObject %s at pos [%d %d %d] "
                                                "already occupied by %s with time %d!",
                                                object->getClassName(), pos.x, pos.y, pos.z, 
                                                cell->getOccupant()->getClassName(),
                                                ((KikiTmpObject*)objectAtNewPos)->time);
            }
            delete objectAtNewPos; // temporary object at new pos will vanish anyway -> delete it
        }
        else
        {
            delete objectAtNewPos;
        }
    }
    
    cell = getCellAtPos (pos);
    
    if (cell == NULL)
    {	
        cell = new KikiCell();
        cells[posToIndex(pos)] = cell;
    }
    
    object->setPosition (pos);
    cell->addObject (object);
}

// __________________________________________________________________________________________________
void KikiWorld::unsetObject ( KikiObject * object )
{
    KikiPos pos (object->getPos()); 
    
    KikiCell * cell = getCellAtPos (pos);
    if (cell)
    {
        cell->removeObject (object);
        
        if (cell->isEmpty())
        {	
            delete cell;
            cells[posToIndex(pos)] = 0;
        }
    }
}

// __________________________________________________________________________________________________
void KikiWorld::addObject ( KikiObject * object )
{
    if (object->getClassId() >= KikiLight::classId())
    {
        if (std::find (lights.begin(), lights.end(), object) == lights.end())
        {
            lights.push_back ((KikiLight*)object);
        }
    }
    else
    {
        if (std::find (objects.begin(), objects.end(), object) == objects.end())
        {
            objects.push_back(object); 
        }
    }
}

// __________________________________________________________________________________________________
void KikiWorld::addObjectAtPos ( KikiObject * object, const KikiPos & pos )
{
    setObjectAtPos (object, pos);
    addObject (object);
}

// __________________________________________________________________________________________________
void KikiWorld::removeObject ( KikiObject * object )
{
    unsetObject (object);
    
    KikiLightIter light_result = std::find (lights.begin(), lights.end(), object);
    if (light_result != lights.end())
    {
        lights.erase (light_result);
        return;
    }
    
    KikiObjectIter result = std::find (objects.begin(), objects.end(), object);
    if (result != objects.end())
    {
        objects.erase (result);
    }
}

// __________________________________________________________________________________________________
bool KikiWorld::moveObjectToPos( KikiObject * object, const KikiPos & pos )
{
    if (isInvalidPos(pos) || isOccupiedPos(pos)) return false;

    unsetObject    (object);
    setObjectAtPos (object, pos);

    Controller.sound->playSound(KikiSound::BOT_LAND);

    return true;
}

// __________________________________________________________________________________________________
void KikiWorld::deleteObject ( KikiObject * object )
{	
    if (object == NULL) 
    {
        KConsole::printf ("WARNING: KikiWorld::deleteObject NULL");
        return;
    }
    removeObject (object);
    delete object;
}

// __________________________________________________________________________________________________
void KikiWorld::deleteAllObjects ()
{
    picked_pickable = NULL;
    moved_objects.clear();

    if (Controller.player)
    {
        removeObject (Controller.player); // remove the player first, to keep it's state
        Controller.timer_event->removeAllActions ();
        Controller.removeKeyHandler (Controller.player); // prevent keyboard input while building world
        Controller.player->reset ();
    }

    while (lights.empty() == false)
    {
        unsigned int oldSize = lights.size();

        delete lights.back(); // destructor will call remove object
        if (oldSize == lights.size())
        {
            KConsole::printf ("WARNING KikiWorld::deleteAllObjects light no auto remove");
            lights.pop_back();
        }
    }

    while (objects.empty() == false)
    {
        if (debug_cells)
        {
            Controller.KEventHandler::display ();
            SDL_Delay (20);
        }
    
        unsigned int oldSize = objects.size();

        delete objects.back(); // destructor will call remove object
        if (oldSize == objects.size())
        {
            KConsole::printf ("WARNING KikiWorld::deleteAllObjects object no auto remove");
            objects.pop_back();
        }
    }
}

// __________________________________________________________________________________________________
void KikiWorld::deleteObjectsWithClassName ( const std::string & className )
{
    for (KikiObjectList::reverse_iterator iter = objects.rbegin(); iter != objects.rend(); iter++)
    {
        if (className == (*iter)->getClassName())
        {
            delete (*iter);
        }
    }
}

// __________________________________________________________________________________________________
KikiObject * KikiWorld::getObjectWithName ( const std::string & objectName )
{
    for (KikiObjectIter iter = objects.begin(); iter != objects.end(); iter++)
    {
        if (objectName == (*iter)->getName())
        {
            return (*iter);
        }
    }
    KConsole::printf("KikiWorld::getObjectWithName :: no object found with name %s", objectName.c_str());
    return NULL;
}

// __________________________________________________________________________________________________
void KikiWorld::setEditMode ( bool editMode )
{
    edit_mode = editMode;
    
    if (edit_mode && edit_projection == NULL)
    {
        edit_projection = new KLightingProjection ();
    }
        
    edit_projection->focusOn (((KVector)size)/2.0);
    edit_projection->setEyeDistance (max_distance);
}

// __________________________________________________________________________________________________
void KikiWorld::focusOnPickedPickable ( bool zoom )
{
   if (edit_mode && picked_pickable)
   {
        projection->focusOn (((KikiObject*)picked_pickable)->getPosition());
   }
}

// __________________________________________________________________________________________________
void KikiWorld::setCameraMode ( int mode )
{
    camera_mode = kMinMax (CAMERA_INSIDE, CAMERA_FOLLOW, mode);
}

// __________________________________________________________________________________________________
void KikiWorld::changeCameraMode ()
{
    camera_mode = ((camera_mode+1) % (CAMERA_FOLLOW+1));
}

// __________________________________________________________________________________________________
bool KikiWorld::shouldPick ( const KPickable * )
{ 
    return edit_mode; 
}

// __________________________________________________________________________________________________
void KikiWorld::picked ()
{
    // reset drag deltas and start pos
    deltas.x = deltas.y = 0;
    if (picked_pickable)
    {
        drag_start_pos = ((KikiObject*)picked_pickable)->position;
    }
}

// __________________________________________________________________________________________________
void KikiWorld::moved ( const KMouseEvent & mouseEvent )
{
    KikiObject * object = (KikiObject*)picked_pickable;
         
    if (object == NULL) return;
         
    KVector newPosition = drag_start_pos;
    
    deltas = deltas + mouseEvent.delta;
    
    getProjection()->moveObjectRelativeToWindow(deltas, newPosition);    

    // round to next integer positions and make a valid pos
    KikiPos newPos = getNearestValidPos(newPosition);
            
    if (getOccupantAtPos(newPos) == NULL && (newPos != object->getPos()))
    {
        // empty position != old position -> move object
        moveObjectToPos(object, newPos);
    }
}

// __________________________________________________________________________________________________
void KikiWorld::objectMovedFromPos ( KikiObject * object, const KikiPos & pos )
{
    KikiCell * cell = getCellAtPos(pos);

    if (cell)
    {
        KikiTmpObject * tmpObject = (KikiTmpObject*)cell->getObjectOfType(KikiTmpObject::classId());
    
        if (tmpObject)
        {
            if (tmpObject->object == object)
            {
                delete tmpObject;
            }
        }
    }
        
    moved_objects.push_back(object);
}

// __________________________________________________________________________________________________
void KikiWorld::objectWillMoveToPos ( KikiObject * object, const KikiPos & pos, int duration )
{
    KikiCell * cell = getCellAtPos (pos);

    if (isInvalidPos(pos))
    {
        KConsole::printError (kStringPrintf("KikiWorld::objectWillMoveToPos invalid pos [%d %d %d]", 
                                                                            pos.x, pos.y, pos.z));
    }
    
    if (object->getPos() == pos)
    {
        KConsole::printf ("WARNING KikiWorld::objectWillMoveToPos equal pos [%d %d %d]", 
                                                                            pos.x, pos.y, pos.z);
        return;
    }

    if (cell)
    {
        KikiObject * objectAtNewPos = cell->getOccupant();
        if (objectAtNewPos)
        {
            if (objectAtNewPos->getClassId() >= KikiTmpObject::classId())
            {
                KikiTmpObject * tmpObject = (KikiTmpObject*)objectAtNewPos;
                
                if (tmpObject->time < 0 && -tmpObject->time <= duration)
                {
                    // temporary object at new pos will vanish before object will arrive -> delete it
                    delete tmpObject;
                }
                else
                {
                    KConsole::printError
                        (kStringPrintf("KikiWorld::objectWillMoveToPos timing conflict at pos [%d %d %d]", 
                                        pos.x, pos.y, pos.z));
                    KConsole::printError                 
                        (kStringPrintf("KikiWorld::objectWillMoveToPos %d %s <> %d %s", duration, 
                                        object->getClassName(), tmpObject->time,
                                        tmpObject->object->getClassName()));
                    KConsole::printError                 
                        (kStringPrintf("KikiWorld::objectWillMoveToPos %s && %s", 
                            object->move_action->getName().c_str(), 
                            tmpObject->object->move_action->getName().c_str()));
                }
            }
            else
            {
                KConsole::printError
                (kStringPrintf("KikiWorld::objectWillMoveToPos pos [%d %d %d] already occupied", 
                                    pos.x, pos.y, pos.z));
            }
        }
    }

    unsetObject (object); // remove object from cell grid
    
    KikiTmpObject * tmpObject = new KikiTmpObject(object); // insert temporary objects at new pos
    tmpObject->setPosition(pos);
    tmpObject->time = +duration;
    addObjectAtPos(tmpObject, pos);
    
    tmpObject = new KikiTmpObject(object); // insert temporary objects at old pos
    tmpObject->setPosition(object->getPosition());
    tmpObject->time = -duration;
    addObjectAtPos(tmpObject, object->getPos());
}

// --------------------------------------------------------------------------------------------------------
void KikiWorld::updateStatus ()
{
    glClearColor(colors[KikiWorld_base_color][R], colors[KikiWorld_base_color][G], 
                 colors[KikiWorld_base_color][B], colors[KikiWorld_base_color][A]);

    while (moved_objects.empty() == false)
    {
        KikiObject * movedObject = moved_objects.back();
        KikiPos pos(movedObject->position);

        if (isInvalidPos(pos))
        {
             KConsole::printError ("KikiWorld::updateStatus invalid new pos");
             return;
        }

        KikiTmpObject * tmpObject;
        tmpObject = (KikiTmpObject*)getObjectOfTypeAtPos(KikiTmpObject::classId(), pos);
        
        if (tmpObject)
        {
            if (tmpObject->object == movedObject)
            {
                delete tmpObject;
            }
            else
            {
                KConsole::printError(kStringPrintf("KikiWorld::updateStatus wrong tmp object "
                                                    "at pos [%d %d %d]\n", pos.x, pos.y, pos.z));
            }
        }
        else if (isOccupiedPos(pos))
        {
            KConsole::printError(kStringPrintf("KikiWorld::updateStatus object moved to " 
                                                "occupied pos [%d %d %d]", pos.x, pos.y, pos.z));
        }
                
        setObjectAtPos(movedObject, pos);
        moved_objects.pop_back();
    }
}

// __________________________________________________________________________________________________
void KikiWorld::deleteDisplayList ()
{
    if (display_list)
    {
        glDeleteLists(display_list, 1);
        display_list = 0;
    }
}

// __________________________________________________________________________________________________
void KikiWorld::setObjectColor (const char * color_name, const KColor & color)
{ 	
    if (strcmp("base", color_name) == 0)
    {
        KikiWall::setObjectColor("base", color);
        colors[0] = color;
    }
    else if (strcmp("plate", color_name) == 0)
    {
        KikiWall::setObjectColor("plate", color);
        colors[1] = color;
    }
    
    Controller.world->deleteDisplayList ();
}

// __________________________________________________________________________________________________
void KikiWorld::setSize ( int x, int y, int z )
{
    deleteAllObjects();
    deleteDisplayList();
    cells.clear();

    size.x = x; size.y = y; size.z = z;
    
    cells.resize(x*y*z, 0);
        
    // .......................................... calcuate max distance (for position relative sound)
    max_distance = kMax(x, kMax(y, z)); // ............................. heuristic of a heuristic :-)
}

// __________________________________________________________________________________________________
void KikiWorld::init ()
{
    int max_id = 0;
    for (KikiObjectIter iter = objects.begin(); iter != objects.end(); iter++)
    {
        (*iter)->setId (++max_id);
    }
    
    if (Controller.player)
    {
        Controller.addKeyHandler (Controller.player);
        Controller.timer_event->addAction (Controller.player->getActionWithId (KikiBot::ACTION_NOOP));
    }
}

// __________________________________________________________________________________________________
KikiPos KikiWorld::getNearestValidPos( const KikiPos & pos ) const
{
    return KikiPos (kMin(size.x-1, kMax(pos.x, 0)), 
                    kMin(size.y-1, kMax(pos.y, 0)), 
                    kMin(size.z-1, kMax(pos.z, 0))); 
}

// __________________________________________________________________________________________________
bool KikiWorld::isUnoccupiedPos( const KikiPos & pos ) const
{
    if (isInvalidPos(pos)) return false;

    return (getOccupantAtPos(pos) == NULL);
}

// __________________________________________________________________________________________________
bool KikiWorld::isOccupiedPos( const KikiPos & pos ) const
{
    return !isUnoccupiedPos(pos);
}

// __________________________________________________________________________________________________
// returns true, if a pushable object is at pos and may be pushed
bool KikiWorld::mayObjectPushToPos ( KikiObject * object, const KikiPos & pos, int duration )
{
    if (isInvalidPos (pos)) return false;
    
    KVector direction = pos - object->getPos(); // direction from object to pushable object
    
    if (isInvalidPos (pos + direction)) return false;
    
    KikiObject * objectAtNewPos = getOccupantAtPos (pos + direction);
    if (objectAtNewPos)
    {
        if (objectAtNewPos->getClassId() >= KikiTmpObject::classId())
        {
            KikiTmpObject * tmpObject = (KikiTmpObject*)objectAtNewPos;
            
            if (tmpObject->time < 0 && -tmpObject->time <= duration)
            {
                // temporary object at new pos will vanish before object will arrive -> delete it
                delete tmpObject;
            }
            else return false;
        }
        else return false;
    }

    KikiObject * pushableObject = getOccupantAtPos (pos);

    if (pushableObject && pushableObject->getClassId() >= KikiPushable::classId() &&
                            pushableObject->getClassId() != KikiMotorGear::classId()) // bad
    {
        ((KikiPushable*)pushableObject)->pushedByObjectInDirection (object, direction, duration);
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------
void KikiWorld::reinit ()
{
    for (std::vector<KikiObject*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
    {
        if ((*iter)->getClassId() >= KikiLight::classId())
        {
            ((KikiLight*)*iter)->initialize ();
        }
    }
    
    if (display_list)
    {
        glDeleteLists (display_list, 1);
        display_list = 0;
    }

    initializeTextures ();
    
    KikiSpikes::initialize ();
    KikiText::reinit ();
}

// __________________________________________________________________________________________________

void KikiWorld::initializeTextures ()
{
    unsigned char imageBuffer[64*64];

    texture_ids.resize (1);

    for (int x = 0; x < 32; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            float value = kMax(1.0-sqrt(double(x*x+y*y))/32.0, 0.0);
            unsigned char cvalue = (unsigned char)(value * value * 255);

            imageBuffer[(32+x)*64+(32+y)] = cvalue;
            imageBuffer[(31-x)*64+(31-y)] = cvalue;
            imageBuffer[(32+x)*64+(31-y)] = cvalue;
            imageBuffer[(31-x)*64+(32+y)] = cvalue;
        }
    }

    glGenTextures (1, &texture_ids[TEXTURE_GRADIENT]);
    glBindTexture (GL_TEXTURE_2D, texture_ids[TEXTURE_GRADIENT]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 64, 64, 0, GL_ALPHA, GL_UNSIGNED_BYTE, imageBuffer);
}


// --------------------------------------------------------------------------------------------------------
const KPickable * KikiWorld::getPickableWithId ( int pid ) const
{
    for (KikiObjectList::const_iterator iter = objects.begin(); iter != objects.end(); iter++)
    {
        if ((*iter)->getClassId() >= KPickable::classId() && ((KPickable*)*iter)->getId() == pid)
        {
            return ((KPickable *)*iter);
        }
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KVector KikiWorld::getInsideWallPosWithDelta ( const KVector & pos, float delta )
{
    static KVector normals[6] = {   KVector ( 1,0,0), KVector (0, 1,0), KVector (0,0, 1),
                                    KVector (-1,0,0), KVector (0,-1,0), KVector (0,0,-1) };
    KVector insidePos (pos);
    for (int w = 0; w < 6; w++)
    {
        KVector planePos (-0.5, -0.5, -0.5);
        if (w >= 3) planePos += (KVector)size;
    
        float f = kRayPlaneIntersectionFactor (pos, -normals[w], planePos, normals[w]);
        
        if (f < delta)
        {
            insidePos += KVector((delta-f)*normals[w]);
        }
    }
    
    return insidePos;
}

// --------------------------------------------------------------------------------------------------------
/* returns the distance to the next wall (positive or negative) */
float KikiWorld::getWallDistanceForPos ( const KVector & pos )
{
    static KVector normals[6] = {   KVector ( 1,0,0), KVector (0, 1,0), KVector (0,0, 1),
                                    KVector (-1,0,0), KVector (0,-1,0), KVector (0,0,-1) };
    
    float min_f = 10000;
    for (int w = 0; w < 6; w++) 
    {
        KVector planePos (-0.5, -0.5, -0.5);
        if (w >= 3) planePos += (KVector)size;
    
        float f = kRayPlaneIntersectionFactor (pos, -normals[w], planePos, normals[w]);
        
        min_f = kAbsMin(min_f, f);
    }
    return min_f;
}

// --------------------------------------------------------------------------------------------------------
/* returns the distace to the next wall in direction rayDirection from rayPos (positive values only) */
float KikiWorld::getWallDistanceForRay ( const KVector & rayPos, const KVector & rayDirection )
{
    static KVector normals[6] = {   KVector ( 1,0,0), KVector (0, 1,0), KVector (0,0, 1),
                                    KVector (-1,0,0), KVector (0,-1,0), KVector (0,0,-1) };
    
    float min_f = 10000;
    for (int w = 0; w < 6; w++) 
    {
        KVector planePos (-0.5, -0.5, -0.5);
        if (w >= 3) planePos += (KVector)size;
    
        float f = kRayPlaneIntersectionFactor (rayPos, rayDirection, planePos, normals[w]);
        
        if (f >= 0.0 && f < min_f) min_f = f;
    }
    return min_f;
}

// --------------------------------------------------------------------------------------------------------
void KikiWorld::displayLights ()
{
    for (KikiLightIter light = lights.begin(); light != lights.end(); light++)
    {
        (*light)->display();
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiWorld::displayDebug ()
{
    glDisable (GL_LIGHTING);

    glBegin(GL_LINES);
    for (std::vector< std::pair<KVector, KColor> >::iterator edge = debug_edges.begin(); 
            edge != debug_edges.end(); edge++)
    {
        edge->second.glColor();
        edge->first.glVertex();
        edge++;
        edge->second.glColor();
        edge->first.glVertex();
    }
    glEnd();

    if (edit_mode && debug_camera)
    {
        glPushMatrix();
    
        player_projection->glMultMatrix();
        
        glColor3f (1, 1, 1);
        
        GLfloat zf	= player_projection->getZFar() / 10.0;
        GLfloat zn	= player_projection->getZNear();
    
        GLfloat sinus   = sin (DEG2RAD (player_projection->getFov()/2.0));
        GLfloat cosinus = cos (DEG2RAD (player_projection->getFov()/2.0));
        GLfloat ar	    = player_projection->getCurrentAspectRatio();
        GLfloat zback   = -cosinus * zf;
        GLfloat zfront  = -cosinus * zn;
    
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, -1.0);
            glVertex3f(0.0, 0.0, zback);
            glVertex3f(sinus * ar * zn, 	-sinus * zn, 	zfront);
            glVertex3f(sinus * ar * zf, 	-sinus * zf,	zback);
            glVertex3f(-sinus * ar * zn, 	sinus * zn, 	zfront);
            glVertex3f(-sinus * ar * zf,	sinus * zf, 	zback);
            glVertex3f(-sinus * ar * zn, 	-sinus * zn, 	zfront);
            glVertex3f(-sinus * ar * zf,	-sinus * zf,	zback);
        glEnd();
            
        glBegin(GL_LINE_STRIP);
            glVertex3f(sinus * ar * zn,	sinus * zn,	zfront);
            glVertex3f(sinus * ar * zn,	-sinus * zn,	zfront);
            glVertex3f(-sinus * ar * zn,	-sinus * zn,	zfront);
            glVertex3f(-sinus * ar * zn,	sinus * zn, 	zfront);
            glVertex3f(sinus * ar * zn,	sinus * zn,	zfront);
            glVertex3f(sinus * ar * zf, 	sinus * zf,	zback);
            glVertex3f(sinus * ar * zf,	-sinus * zf,	zback);
            glVertex3f(-sinus * ar * zf,	-sinus * zf,	zback);
            glVertex3f(-sinus * ar * zf,	sinus * zf, 	zback);
            glVertex3f(sinus * ar * zf, 	sinus * zf,	zback);
        glEnd();
        
        glPopMatrix();
    }

    glEnable (GL_LIGHTING);
    
    if (debug_cells)
    {
        for (int x = 0; x < size.x; x++)
        {
            for (int y = 0; y < size.y; y++)
            {
                for (int z = 0; z < size.z; z++)
                {
                    KikiCell * cell = getCellAtPos (KikiPos (x, y, z));
                    if (cell)
                    {	
                        glPushMatrix ();
                        glTranslatef (x, y, z);
                        glColor4f (0.5, 0.5, 0.5, 0.5);
                        glLineWidth (cell->objects.size());
                        kDisplayWireCube (1.0 + 0.1 * cell->objects.size());
                        glPopMatrix ();
                    }
                }
            }
        }
    }    
}

// --------------------------------------------------------------------------------------------------------
void KikiWorld::debugLine ( const KVector & p1, const KVector & p2, const KColor & c )
{
    debug_edges.push_back (std::pair<KVector, KColor> (p1, c));
    debug_edges.push_back (std::pair<KVector, KColor> (p2, c));
}

// --------------------------------------------------------------------------------------------------------
void KikiWorld::displayPickables ( int mode )
{
    KProjection * p = projection;
    
    if (debug_camera) p = player_projection;
    
    KVector	look_vector (p->getZVector());
    KVector	projection_position (p->getPosition() + 0.2 *  look_vector);
    float	distance;
    
    std::multimap<float, KikiObject*> sort_map;
    
    float half_sqrt_3   = -sqrt(3.0)/2.0; 
    float half_fov_rad	= DEG2RAD (p->getFov()/2.0); 
    
    float ydir	= sin (half_fov_rad - M_PI_2);
    float ydirz	= cos (half_fov_rad - M_PI_2);
    float ar = p->getCurrentAspectRatio();
    float xangle = atan (sin (half_fov_rad) * ar / cos(half_fov_rad)) - M_PI_2;
    float xdir	= sin (xangle);
    float xdirz	= cos (xangle);
    
    KVector view_volume_normals[4] = {  ((*p) * KVector (0, ydir,-ydirz)),
                                        ((*p) * KVector (0,-ydir,-ydirz)),
                                        ((*p) * KVector (xdir,0,-xdirz)),
                                        ((*p) * KVector (-xdir,0,-xdirz)) };
        
    for (KikiObjectIter iter = objects.begin(); iter != objects.end(); iter++)
    {
        KVector eye_to_object = (*iter)->current_position - projection_position;
        bool outside = false;

        for (int i = 0; i < 4; i++)
        {
            if (view_volume_normals[i] * eye_to_object < half_sqrt_3)
            {
                outside = true;
                break;
            }
        }
        if (outside) continue;
    
        distance =  eye_to_object[X] * eye_to_object[X] +
                    eye_to_object[Y] * eye_to_object[Y] +
                    eye_to_object[Z] * eye_to_object[Z];
                    
        sort_map.insert (std::pair<float, KikiObject*> (distance, *iter));
    }
    
    displayLights ();

    for (std::multimap<float, KikiObject*>::reverse_iterator it = sort_map.rbegin(); it != sort_map.rend(); it++)
    {
        (*it).second->display();
    }

#ifdef DEBUG    
    displayDebug ();
#endif
}

// __________________________________________________________________________________________________
void KikiWorld::displayWall ( int width, int height )
{
    float l = raster_size/2.0;
    float t = 1.0 - l;

    if (flags[DISPLAY_RASTER] == false)
    {
        l = 0.0; t = 1.0;
    }
    
    glNormal3f(0.0, 0.0, 1.0);
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            glRectf (w+l, h+l, w+t, h+t);
        }
    }
}

// __________________________________________________________________________________________________
KProjection * KikiWorld::getProjection ()
{
    if (projection == NULL)
    {
        switch (camera_mode) 
        {
            case CAMERA_INSIDE:	projection = Controller.player->getProjection();	break;
            case CAMERA_BEHIND:	projection = Controller.player->getBehindProjection();	break;
            case CAMERA_FOLLOW:	projection = Controller.player->getFollowProjection();	break;
        }
    }
    
    return projection;
}

// __________________________________________________________________________________________________
void KikiWorld::display ( int mode )
{
    switch (camera_mode) 
    {
        case CAMERA_INSIDE:	projection = Controller.player->getProjection();	break;
        case CAMERA_BEHIND:	projection = Controller.player->getBehindProjection();	break;
        case CAMERA_FOLLOW:	projection = Controller.player->getFollowProjection();	break;
    }

    player_projection = (KLightingProjection*) projection;
    
    debug_edges.clear();

    if (edit_mode)
    {
        projection = edit_projection;
    }
    
    projection->initProjection();

    if (display_list)
    {
        glCallList(display_list);
    }
    else
    {
        if ((display_list = glGenLists(1)))
        {
            glNewList(display_list, GL_COMPILE_AND_EXECUTE);
        }

        glPushAttrib(GL_ENABLE_BIT);
        glPushMatrix();
    
        if (flags[DISPLAY_BORDER])
        {
            glDisable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_ALPHA_TEST);
            glDisable(GL_NORMALIZE);
            
            colors[KikiWorld_plate_color].glColor();
            
            glTranslatef(-0.5, -0.5, -0.5);
            
            displayWall(size.x, size.y); // xy+z
            glRotatef(180.0, 0.0, 1.0, 0.0);
            glTranslatef(-size.x, 0.0, -size.z);
            displayWall(size.x, size.y); // xy-z
            
            glRotatef(90.0, 1.0, 0.0, 0.0); // xz-y
            glTranslatef(0.0, 0.0, -size.y);
            displayWall(size.x, size.z);
            glRotatef(180.0, 0.0, 1.0, 0.0); // xz+y
            glTranslatef(-size.x, 0.0, -size.y);
            displayWall(size.x, size.z);
            
            glRotatef(-90.0, 0.0, 1.0, 0.0); // yz+x
            glTranslatef(0.0, 0.0, -size.x);
            displayWall(size.y, size.z);
            glRotatef(180.0, 1.0, 0.0, 0.0); // yz-x          
            glTranslatef(0.0, -size.z, -size.x); 
            displayWall(size.y, size.z);
        }
        
        glPopMatrix();
        glPopAttrib();
        
        if (display_list)
        {
            glEndList();
        }
    }
    
    displayPickables(mode);
}

