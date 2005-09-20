/*
 *  KEventHandler.h
 *  kodisein
 */

#ifndef __KEventHandler
#define __KEventHandler

#include <SDL_events.h>

enum { 	KDL_MOUSE_MODE_SCALE,
        KDL_MOUSE_MODE_ROTATE, 
        KDL_MOUSE_MODE_TRANSLATE };
enum {  KDL_DISPLAY_MODE_WIREFRAME, 
        KDL_DISPLAY_MODE_FREE_ROTATION, 
        KDL_DISPLAY_MODE_SHOW_FPS,
        KDL_DISPLAY_MODE_FAST,
        KDL_DISPLAY_MODE_END };
enum {  KDL_NOTIFICATION_TYPE_VIDEO_MODE_CHANGED = SDL_USEREVENT,
        KDL_NOTIFICATION_TYPE_WINDOW_SIZE_CHANGED,
        KDL_NOTIFICATION_TYPE_PROJECTION_HANDLER_CHANGED,
        KDL_NOTIFICATION_TYPE_MOUSE_MODE_CHANGED,
        KDL_NOTIFICATION_TYPE_EVENT_HANDLER_END };

#ifdef __cplusplus

#include "KIntrospection.h"
#include "KNotificationObject.h"
#include "KKeyActionHandler.h"
#include "KPickHandler.h"
#include "KVector.h"

#include <vector>
#include <deque>
#include <SDL_timer.h>
        
// --------------------------------------------------------------------------------------------------------
class KMouseEvent
{
    public:

    int       button_state;
    KPosition pos;
    KPosition delta;
    
    KMouseEvent ( const SDL_MouseMotionEvent & e ) 
                { pos.x = e.x; pos.y = SDL_GetVideoSurface()->h - e.y; 
                  delta.x = e.xrel, delta.y = -e.yrel;
                  button_state = e.state; }
    KMouseEvent ( const SDL_MouseButtonEvent & e ) 
                { pos.x = e.x; pos.y = SDL_GetVideoSurface()->h - e.y;
                  delta.x = delta.y = 0;
                  button_state = e.state; }
    bool leftButton   () const { return button_state & SDL_BUTTON(SDL_BUTTON_LEFT); }
    bool middleButton () const { return button_state & SDL_BUTTON(SDL_BUTTON_MIDDLE); }
    bool rightButton  () const { return button_state & SDL_BUTTON(SDL_BUTTON_RIGHT); }
    bool motion	      () const { return delta.x != 0 || delta.y != 0; }
};

class KProjection;

// --------------------------------------------------------------------------------------------------------
class KEventHandler : public KObject
{
    INTROSPECTION
    
    protected:

    static int			mode; 			// application mode
    static int			mouse_mode;		// mouse mode 
    static KPickHandler *	projection_handler;	// handlers
    static KPickHandlerList	pick_handlers;		
    static KKeyHandlerList  	key_handlers;
    static KKeyHandler *	focus_key_handler;	// key focus handler 
    
    void			updateProjection ();

    public:

    static KNotificationObject	notification_center;    
    static unsigned int		frame_time;
    static unsigned int		last_time;
    static std::deque<float>	fps;
    static bool			flags[KDL_DISPLAY_MODE_END];

    static std::string		copy_string;
    static KPickHandler *	release_handler;
    static KKeyActionHandler	menu_key_handler;

                        KEventHandler 			();
    virtual		~KEventHandler 			() {}

    virtual void	display 			();
    virtual void	displayPickHandlers		();
    virtual void	quit				();

    virtual void	mainLoop			();
    virtual void	handleKeyboardEvent 		( SDL_KeyboardEvent & );
    virtual void	handleMouseMotionEvent 		( SDL_MouseMotionEvent & );
    virtual void	handleMouseButtonEvent 		( SDL_MouseButtonEvent & );
    virtual void	handleUserEvent 		( SDL_UserEvent & );
    virtual void	handleResizeEvent 		( SDL_ResizeEvent & );

    virtual void	setFastDisplay			( bool );

    static void		setMouseMode			( int );
    static int		getMouseMode			() { return mouse_mode; }

    static void		addPickHandler 			( KPickHandler * );
    static void		removePickHandler 		( KPickHandler * );
    static void		addKeyHandler 			( KKeyHandler * );
    static void		removeKeyHandler 		( KKeyHandler * );
    static void		setFocusKeyHandler 		( KKeyHandler * keyHandler );
    static void		removeFocusKeyHandler		( KKeyHandler * keyHandler );

    static void		setProjectionHandler		( KPickHandler * = NULL );
    static void		removeProjectionHandler		( KPickHandler * = NULL );
    static void		resetLighting			();
    static unsigned int getTime				() { return SDL_GetTicks(); }
    static int		getApplicationMode		() { return mode; }
    static int		getMouseState			();
    static KPosition	getMousePos			();
    static KPosition	getMouseDelta 			();
    static KSize	getScreenSize 			();
    static bool		setScreenSize			( int width, int height, bool fullscreen = false );
    static bool		getFullscreen			();
    static void		setFullscreen			( bool );

    void		resetProjection 		();
    void		setResetProjection 		();
    void		focusOnSelection 		();
    void		focusAndZoomOnSelection 	();

    void		setFreeRotation			( bool b ) { flags[KDL_DISPLAY_MODE_FREE_ROTATION] = b; }
    void		setWireframeMode		( bool b ) {flags[KDL_DISPLAY_MODE_WIREFRAME] = b;}
    void		setDisplayFps			( bool b ) {flags[KDL_DISPLAY_MODE_SHOW_FPS] = b;}
    bool		getFreeRotation			() const {return flags[KDL_DISPLAY_MODE_FREE_ROTATION];}
    bool		getFastDisplay			() const {return flags[KDL_DISPLAY_MODE_FAST]; }
    bool		getWireframeMode		() const {return flags[KDL_DISPLAY_MODE_WIREFRAME];}
    bool		getDisplayFps			() const {return flags[KDL_DISPLAY_MODE_SHOW_FPS];}
    
    void		toggleFreeRotation		();
    void		toggleWireframeMode		();
    void		toggleDisplayFps		();
    
    KPickHandler *	getPickHandlerForProjection 	( const KProjection * ) const;
};

#endif // __cplusplus
#endif


