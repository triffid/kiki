/*
 *  KikiController.h
 */

#ifndef __KikiController
#define __KikiController

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#ifdef WIN32
#pragma warning ( disable : 4800 4305 4267 ) // Disable warnings
#include <glut.h>
#endif
#include <GL/glu.h>
#endif

#include <SDL.h>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

#include "KikiPos.h"
#include "KikiEvent.h"
#include "KikiActionObject.h"

#include <KMatrix.h>
#include <KEventHandler.h>
#include <KKeyHandler.h>

class KikiGUI;
class KikiScreenText;
class KikiSound;
class KikiWorld;
class KikiPlayer;
class KikiStatusDisplay;
class KikiEvent;
class KikiPython;

// __________________________________________________________________________________________________
class KikiController : public KEventHandler, public KKeyHandler, public KikiActionObject
{
    protected: // ..................................................................... PROTECTED

    bool                        debug_version;
    bool			cheat;
    int				speed;
    int                         gamma;
    std::string                 kiki_home;

    public: // ........................................................................ PUBLIC

    // ........................................................................ 'global' objects
    KikiGUI * 			gui;
    KikiSound * 		sound;
    KikiPython *		python;
    KikiWorld * 		world;
    
    KikiPlayer *		player;
    KikiStatusDisplay *		player_status;
    KikiEvent *			timer_event;

    std::string         quit_key;

    // ........................................................................ (con/de)struction
                        KikiController		();
                        ~KikiController		();
    
    // ........................................................................ initialization
    void 		init 			();
    void 		initOpenGL		();
    bool		isDebugVersion		();

    std::string         getKikiHome             () { return kiki_home; }
    
    // ........................................................................ display
    void		display			();
    void		saveScreenShot		();
    void		displayText		( const std::string & text, int colorIndex = 0 );
    std::string		getLocalizedString	( const std::string & key );

    void		setGamma		( int );
    int			getGamma		() const { return gamma; }
    
    // ........................................................................ event handling
    bool		handleKey		( const KKey & key );
    void		handleMouseButtonEvent	( SDL_MouseButtonEvent & event );
    void 		mouseModeCallback	( const std::string & button );
    
    // ........................................................................ player
    KikiPlayer * 	getPlayer		();
    void	 	playerDeleted		();
    
    // ........................................................................ timing
    void		setSpeed		( int s ) { speed = s; }
    int			getSpeed		() const { return speed; }
    
    int			mapMsTime		( int unmapped ) { return (int)(10.0 * unmapped/speed); }
    int			unmapMsTime		( int mapped ) { return (int)(mapped * speed/10.0); }
    float		getRelativeTime		() { return (frame_time % (10000/speed))/(10000.0/speed); }
    float		getRelativeDelta	() { return (frame_time - last_time)/(10000.0/speed); }
};

extern KikiController Controller;

#endif
