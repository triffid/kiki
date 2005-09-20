/*
 *  KEventHandler.cpp
 *  kodisein
 */

#include "KEventHandler.h"
#include "KConsole.h"
#include "KPickHandler.h"
#include "KOrthographicProjection.h"
#include "KPerspectiveProjection.h"
#include "KStringTools.h"
#include "KKey.h"
#include "KTools.h"
#include "KKeyTools.h"

#include <SDL.h>
#include <algorithm>

KDL_CLASS_INTROSPECTION_1 (KEventHandler, KObject)

// --------------------------------------------------------------------------------------------------------
unsigned int		KEventHandler::frame_time;
unsigned int		KEventHandler::last_time;
std::deque<float>	KEventHandler::fps;
bool			KEventHandler::flags[KDL_DISPLAY_MODE_END];
int			KEventHandler::mode;
int			KEventHandler::mouse_mode;

std::string		KEventHandler::copy_string;

KPickHandler * 		KEventHandler::release_handler;
KPickHandler *		KEventHandler::projection_handler;

KPickHandlerList	KEventHandler::pick_handlers;		
KKeyHandlerList		KEventHandler::key_handlers;

KKeyActionHandler	KEventHandler::menu_key_handler;
KKeyHandler *		KEventHandler::focus_key_handler;

KNotificationObject	KEventHandler::notification_center;

// --------------------------------------------------------------------------------------------------------
KEventHandler::KEventHandler ()
{
    mode 		= 0;
    mouse_mode 		= KDL_MOUSE_MODE_ROTATE;
    release_handler	= NULL;
    focus_key_handler	= NULL;
    projection_handler	= NULL;
   
    flags[KDL_DISPLAY_MODE_WIREFRAME]		= false;
    flags[KDL_DISPLAY_MODE_FREE_ROTATION]	= false;
    flags[KDL_DISPLAY_MODE_SHOW_FPS]      	= false;
    flags[KDL_DISPLAY_MODE_FAST]		= false;

    addKeyHandler (&KEventHandler::menu_key_handler);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::quit ()
{
	SDL_SetGamma (1, 1, 1);
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent (&event);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::displayPickHandlers ()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (KPickHandlerIter iter = pick_handlers.begin(); iter != pick_handlers.end(); iter++)
    {
        (*iter)->display(mode);
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::display ()
{
    displayPickHandlers();
    
    if (flags[KDL_DISPLAY_MODE_SHOW_FPS])
    {
        KOrthographicProjection projection; 
        projection.initProjection();
        
        glDisable (GL_LIGHTING);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        
        KSize screenSize = getScreenSize();
        
        float fps_sum = 0.0;
        for (int i = 0; i < (int)fps.size(); i++)
        {
            fps_sum += fps[i];
        }
        std::string timeString = kStringPrintf ("fps %1.0f", fps_sum/fps.size());

        kDisplayString (timeString, KPosition (screenSize.w - kStringWidth (timeString, false) - 20,
                                                -screenSize.h+5), false);
        glEnable (GL_LIGHTING);
    }
    
    KConsole::checkGLError();
    
    glFinish();
    SDL_GL_SwapBuffers();
}

// --------------------------------------------------------------------------------------------------------
KPickHandler * KEventHandler::getPickHandlerForProjection ( const KProjection * p ) const
{
    std::vector<KPickHandler*>::const_iterator iter = pick_handlers.begin();
    while (iter != pick_handlers.end())
    {
        if ((*iter)->getProjection() == p) return (*iter);
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::resetLighting ()
{
    float white[4]    	= {1.0, 1.0, 1.0, 1.0};
    float gray[4]    	= {0.5, 0.5, 0.5, 0.5};
    float none[4]	= {0.0, 0.0, 0.0, 0.0};

    glLightfv (GL_LIGHT0, GL_AMBIENT, 			none);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, 			white);
    glLightfv (GL_LIGHT0, GL_SPECULAR, 			white);
    glLightf  (GL_LIGHT0, GL_SPOT_CUTOFF,		180.0);
    glLightf  (GL_LIGHT0, GL_CONSTANT_ATTENUATION,	1.0);
    glLightf  (GL_LIGHT0, GL_LINEAR_ATTENUATION,	0.0);
    glLightf  (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,	0.0);
    glEnable  (GL_LIGHT0);

    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, 		none);
    glLightModeli  (GL_LIGHT_MODEL_LOCAL_VIEWER, 	1);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable	   (GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   none);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  none);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  gray);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 60.0);

    GLint maxLights; 
    glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
    for (GLenum l = GL_LIGHT1; l < (GL_LIGHT0+(GLuint)maxLights); l++) 
    {
        glDisable(l);
    }

    glEnable(GL_LIGHTING);

    glClearColor(0.0, 0.0, 0.0, 0.0);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::setFastDisplay ( bool b )
{
    if (b != flags[KDL_DISPLAY_MODE_FAST])
    {
        flags[KDL_DISPLAY_MODE_FAST] = b;
        if (b)
        {
            glDisable(GL_BLEND);
            glShadeModel(GL_FLAT);
        }
        else
        {
            glEnable(GL_BLEND);
            glShadeModel(GL_SMOOTH);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::resetProjection ()
{
    if (projection_handler)
    {
        projection_handler->setProjection(projection_handler->getResetProjection());
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::setResetProjection ()
{
    if (projection_handler)
    {
        projection_handler->setResetProjection();
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::focusOnSelection ()
{
    if (projection_handler)
    {
        projection_handler->focusOnPickedPickable();
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::focusAndZoomOnSelection ()
{
    if (projection_handler)
    {
        projection_handler->focusOnPickedPickable(true);
    }
}

// --------------------------------------------------------------------------------------------------------
KSize KEventHandler::getScreenSize ()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    if (screen) return KSize (screen->w, screen->h);
    return KSize();
}

// --------------------------------------------------------------------------------------------------------
bool KEventHandler::setScreenSize ( int width, int height, bool fullscreen )
{
    int flags = SDL_OPENGL; // | SDL_ANYFORMAT;
    if (fullscreen) 
    {
        flags |= SDL_FULLSCREEN;
    }
    else 
    {
        flags |= SDL_RESIZABLE;
    }
    
    if (SDL_VideoModeOK (width, height, 32, flags) == 0)
    {
        if (fullscreen)
        {
            // fallback to window mode
            KConsole::printf ("couldn't set video mode %dx%d (%s):\n%s\n", 
                             width, height, 
                             fullscreen ? "fullscreen" : "window", SDL_GetError());
            KConsole::printf ("trying to fallback to window mode");
            return setScreenSize (width, height, false);
        }
        else
        {
            KConsole::printError( kStringPrintf("couldn't set video mode %dx%d (%s)", 
                              width, height, 
                              fullscreen ? "fullscreen" : "window"), true);
            return false;
        }
    }
    
    if (SDL_SetVideoMode (width, height, 32, flags) == NULL) // paranoid
    {
        if (fullscreen)
        {
            // fallback to window mode
            KConsole::printf ("couldn't change video mode %dx%d (%s):\n%s\n", 
                             width, height, 
                             fullscreen ? "fullscreen" : "window", SDL_GetError());
            KConsole::printf ("trying to fallback to window mode");
            return setScreenSize (width, height, false);
        }
        else
        {
            KConsole::printError(kStringPrintf("couldn't change video mode %dx%d (%s):\n%s\n", 
                             width, height, 
                             fullscreen ? "fullscreen" : "window", SDL_GetError()), true);
            return false;
        }
    }

    // notify interested receivers that the resolution changed
    notification_center.notifyReceiversType(KDL_NOTIFICATION_TYPE_VIDEO_MODE_CHANGED);

    return true;
}

// --------------------------------------------------------------------------------------------------------
bool KEventHandler::getFullscreen () 
{
    return (SDL_GetVideoSurface()->flags & SDL_FULLSCREEN);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::setFullscreen ( bool fullscreen )
{
    // toggle between fullscreen or window mode
    if (!fullscreen)
    {
        // switch to normal mode
		int width, height;
        // get available hardware modes
        SDL_Rect **modes = SDL_ListModes (NULL, SDL_OPENGL);
        
        // Check if there are any modes available
        if (modes == (SDL_Rect **)0)
        {
            KConsole::printError("sorry, no window video modes available!", true);
            return;
        }
        // check if resolution is restricted
        if (modes != (SDL_Rect **)-1)
        {
            // all resolutions available
            width  = 1024;
            height = 768;
        }
        else
        {
            width  = modes[0]->w;
            height = modes[0]->h;
        }

        setScreenSize(width, height, false);
    }
    else
    {
        int width, height;
        // get available fullscreen/hardware modes
        SDL_Rect **modes = SDL_ListModes(NULL, SDL_OPENGL | SDL_HWSURFACE | SDL_FULLSCREEN);
        
        // Check is there are any modes available
        if (modes == (SDL_Rect **)0)
        {
            KConsole::printError("sorry, no fullscreen mode available!", true);
            return;
        }
        // check if resolution is restricted
        if (modes != (SDL_Rect **)-1)
        {
            // all resolutions available
            width  = 1024;
            height = 768;
        }
        else
        {
            width  = modes[0]->w;
            height = modes[0]->h;
        }

        setScreenSize(width, height, true);
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::toggleWireframeMode ()
{
    flags[KDL_DISPLAY_MODE_WIREFRAME] = !flags[KDL_DISPLAY_MODE_WIREFRAME];
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::toggleFreeRotation ()
{
    flags[KDL_DISPLAY_MODE_FREE_ROTATION] = !flags[KDL_DISPLAY_MODE_FREE_ROTATION];
}

// --------------------------------------------------------------------------------------------------------
KPosition KEventHandler::getMousePos ()
{
    KPosition mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    // we prefer mouse y from 0=screen.bottom to height=screen.top
    mousePos.y = SDL_GetVideoSurface()->h - mousePos.y;  
    return mousePos;
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::setMouseMode ( int m )
{ 
    if (mouse_mode != m)
    {
        mouse_mode = m;
        notification_center.notifyReceiversType(KDL_NOTIFICATION_TYPE_MOUSE_MODE_CHANGED);
    }
}
 
// --------------------------------------------------------------------------------------------------------
KPosition KEventHandler::getMouseDelta ()
{
    KPosition mouseDelta;
    SDL_GetRelativeMouseState(&mouseDelta.x, &mouseDelta.y);
    // we prefer mouse movement up to be positive
    mouseDelta.y = -mouseDelta.y;
    return mouseDelta;
}

// --------------------------------------------------------------------------------------------------------
int KEventHandler::getMouseState ()
{
    return SDL_GetMouseState(NULL, NULL);
}

// --------------------------------------------------------------------------------------------------------
bool depth_comp ( KPickHandler * a, KPickHandler * b )
{
    return *a < *b;
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::addPickHandler ( KPickHandler * pickhandler )
{
    if (pickhandler == NULL) return;
    std::vector<KPickHandler*>::iterator result = std::find(pick_handlers.begin(), pick_handlers.end(), pickhandler);
    if (result == pick_handlers.end())
    {
        pick_handlers.push_back(pickhandler);
		std::sort(pick_handlers.begin(), pick_handlers.end(), depth_comp);
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::removePickHandler ( KPickHandler * pickhandler )
{
    if (pickhandler == NULL) return;
    std::vector<KPickHandler*>::iterator result = std::find(pick_handlers.begin(), pick_handlers.end(), pickhandler);
    if (result != pick_handlers.end())
    {
        if (*result == projection_handler) projection_handler = NULL;
        if (*result == release_handler)	   release_handler    = NULL;
        pick_handlers.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::addKeyHandler ( KKeyHandler * keyhandler )
{
    if (keyhandler == NULL) return;
    KKeyHandlerIter result = std::find (key_handlers.begin(), key_handlers.end(), keyhandler);
    if (result == key_handlers.end())
    {
        key_handlers.push_back (keyhandler);
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::removeKeyHandler ( KKeyHandler * keyhandler )
{
    if (keyhandler == NULL) return;
    KKeyHandlerIter result = std::find (key_handlers.begin(), key_handlers.end(), keyhandler);
    if (result != key_handlers.end())
    {
        key_handlers.erase (result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::setFocusKeyHandler ( KKeyHandler * keyhandler )
{
    focus_key_handler = keyhandler;
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::removeFocusKeyHandler ( KKeyHandler * keyhandler )
{
    if (focus_key_handler == keyhandler)
    {
        focus_key_handler = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::removeProjectionHandler ( KPickHandler * ph )
{
    projection_handler = NULL;
    notification_center.notifyReceiversType(KDL_NOTIFICATION_TYPE_PROJECTION_HANDLER_CHANGED);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::setProjectionHandler ( KPickHandler * ph )
{
    projection_handler = ph;
    notification_center.notifyReceiversType(KDL_NOTIFICATION_TYPE_PROJECTION_HANDLER_CHANGED);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::handleKeyboardEvent ( SDL_KeyboardEvent & event )
{
    KKey key(event.keysym);

    if (focus_key_handler)
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (focus_key_handler->handleKey(key)) 
            {
                // if focus_key_handler returns true, it handled the key and wants to keep keyboard focus.
                // otherwise, propagate key to the other key handlers
                return;
            }
        }
        else if (focus_key_handler->flags[KDL_KEYHANDLER_FLAG_HANDLES_RELEASE])
        {
            if (focus_key_handler->handleKeyRelease(key)) 
            {
                // focus_key_handler handled the key release and wants to keep keyboard focus.
                return;
            }
        }
    }

    for (KKeyHandlerIter iter = key_handlers.begin(); iter != key_handlers.end(); iter++)
    {
        if (event.type == SDL_KEYDOWN)
        {
            if ((*iter)->handleKey(key)) 
            {
                return;
            }
        }
        else if ((*iter)->flags[KDL_KEYHANDLER_FLAG_HANDLES_RELEASE])
        {
            if ((*iter)->handleKeyRelease(key)) 
            {
                return;
            }
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::handleMouseMotionEvent ( SDL_MouseMotionEvent & event )
{
    KMouseEvent mouseEvent(event);
    if (mouseEvent.button_state)
    {
        std::vector<KPickHandler*>::reverse_iterator iter = pick_handlers.rbegin();
        while (iter != pick_handlers.rend())
        {
            if ((*iter)->mouseMotion(mouseEvent))
            {
                if ((*iter)->flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED])
                {
                    projection_handler = *iter;
                }
                return; // pickhandler handles motion
            }
            iter++;
        }
        
        // no pickhandler handles motion -> update current projection
        if (projection_handler) 
        {
            projection_handler->updateProjection(mouseEvent);
        }
    }
    else
    {
        std::vector<KPickHandler*>::reverse_iterator iter = pick_handlers.rbegin();
        while (iter != pick_handlers.rend())
        {
            if ((*iter)->flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS])
            {
                (*iter)->mouseMotion(mouseEvent);
                return; // pickhandler handles motion
            }
            iter++;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::handleMouseButtonEvent ( SDL_MouseButtonEvent & event)
{
    KMouseEvent mouseEvent(event);

    if (event.state == SDL_PRESSED)
    {
        SDL_GetRelativeMouseState(NULL, NULL); // reset relative mouse deltas
        
        for (KPickHandlerList::reverse_iterator iter = pick_handlers.rbegin(); 
             iter != pick_handlers.rend(); iter++)
        {
            if ((*iter)->pick(mouseEvent))
            {
                if ((*iter)->flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED])
                {
                    projection_handler = *iter;
                }
                return;
            }
        }
    } 
    else // event->state == SDL_RELEASED
    {
        if (release_handler)
        {
            KPickHandler * tmpReleaseHandler = release_handler;
            release_handler = NULL;
            tmpReleaseHandler->release (mouseEvent);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::handleResizeEvent ( SDL_ResizeEvent & event )
{
    // notify interested receivers that the window size changed
    SDL_SetVideoMode (event.w, event.h, 32, SDL_OPENGL | SDL_RESIZABLE);
    notification_center.notifyReceiversType (KDL_NOTIFICATION_TYPE_WINDOW_SIZE_CHANGED);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::handleUserEvent ( SDL_UserEvent & event )
{
    // forward the event code to interested receivers
    notification_center.notifyReceiversType (event.code);
}

// --------------------------------------------------------------------------------------------------------
void KEventHandler::mainLoop ()
{
    SDL_Event event;
    while (true)
    {
        frame_time = SDL_GetTicks();

        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
                case SDL_KEYUP:
                    handleKeyboardEvent (event.key);
                    break;
                case SDL_KEYDOWN:
                    handleKeyboardEvent (event.key);
                    break;
                case SDL_MOUSEMOTION:
                    handleMouseMotionEvent (event.motion);
                    break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                    handleMouseButtonEvent (event.button);
                    break;
                case SDL_VIDEORESIZE:
                    handleResizeEvent (event.resize);
                    break;
                case SDL_QUIT:
                    return;
                default:
                    if (event.type >= SDL_USEREVENT)
                    {
                        handleUserEvent (event.user);
                    }
                    break;
            }
        }

        display();
                            
        if ((frame_time - last_time) < 10)
        {
            SDL_Delay (20 - (frame_time - last_time));
        }
               
        if (flags[KDL_DISPLAY_MODE_SHOW_FPS])
        {
            fps.push_back (1000.0 / (float)(frame_time - last_time));
            if (fps.size() > 20) fps.pop_front();
        }
        
        last_time = frame_time;
    }
}


