/*
 *  KikiController.cpp
 */

#include "KikiController.h"
#include "KikiSound.h"
#include "KikiGUI.h"
#include "KikiWorld.h"
#include "KikiPython.h"
#include "KikiLocalization.h"

#include "KikiSpikes.h"
#include "KikiStone.h"
#include "KikiSwitch.h"
#include "KikiAtom.h"
#include "KikiMutant.h"
#include "KikiPlayer.h"
#include "KikiAction.h"
#include "KikiStatusDisplay.h"
#include "KikiScreenText.h"
#include "KikiLight.h"

#include "KPerspectiveProjection.h"
#include "KButton.h"
#include "KStringTools.h"
#include "KFileTools.h"
#include "KKey.h"
#include "KConsole.h"

#ifndef WIN32
#include <sys/param.h>
#include <unistd.h>
#endif

static int ESCAPE_KEY_EVENT;

const unsigned char 	kikiVersionString[] = "1.0";
extern const double 	kikiVersionNumber;

// __________________________________________________________________________________________________
KikiController::KikiController () : KEventHandler (), KKeyHandler (), KikiActionObject ()
{
    addEventWithName ("timer");
    timer_event		= events.back(); // deserves it's own pointer, since it's used that often :-)
    ESCAPE_KEY_EVENT	= addEventWithName ("escape");

#ifdef DEBUG
    debug_version = true;
#else
    debug_version = false;
#endif

#if defined(__APPLE__) && defined(__MACH__)
    kiki_home = "./";
    quit_key = "META_q";
    gamma = 1;
#else
    char * kiki_home_env = getenv("KIKI_HOME");
    if (kiki_home_env)
    {
       kiki_home = kiki_home_env;
    }
    else
    {
       KConsole::printf("WARNING :: environment variable KIKI_HOME not set ...");
       KConsole::printf("           ... assuming resources in current directory");

	   kiki_home = kFileGetCurrentPath();
    }
#ifndef WIN32
    kiki_home += "/";
#else
    kiki_home += "\\";
#endif

    KConsole::printf("--- KikiController::KikiController :: kiki_home %s", kiki_home.c_str());

    quit_key = "CTRL_q";
    gamma = 8;
#endif
}

// __________________________________________________________________________________________________
KikiController::~KikiController () 
{
    delete world;    
    delete gui;
    delete sound;
    python->finalize();
    delete python;
}

// __________________________________________________________________________________________________
void KikiController::playerDeleted ()
{
    player_status->setStatus(NULL);
    removeKeyHandler(player);
    player = NULL;
}

// __________________________________________________________________________________________________
KikiPlayer * KikiController::getPlayer ()
{
    if (player == NULL)
    {
        player = new KikiPlayer();
        addKeyHandler (player);
        player->KikiObject::addReceiverCallback (this, (KCallbackPtr)&KikiController::playerDeleted,
                                                        KIKI_NOTIFICATION_OBJECT_DELETED);
    }
    return player;
}

// __________________________________________________________________________________________________
std::string KikiController::getLocalizedString ( const std::string & key )
{
#if defined(__APPLE__) && defined(__MACH__)
    return std::string (kikiLocalizedString (key.c_str()));
#else
    return key; // localization only on Mac OS X yet
#endif
}

// __________________________________________________________________________________________________
void KikiController::displayText ( const std::string & text, int colorIndex )
{
    KikiScreenText * screen_text = new KikiScreenText ();
    screen_text->setText (text, colorIndex);
    screen_text->show();
}

// __________________________________________________________________________________________________
void KikiController::display ()
{
    timer_event->triggerActions();
    world->updateStatus();
    timer_event->finishActions();
    KEventHandler::display();
}

// __________________________________________________________________________________________________
bool KikiController::isDebugVersion ()
{
    return debug_version;
}

// __________________________________________________________________________________________________
void KikiController::init ()
{
    cheat  = false; 
    speed  = 5;
    
    KEventHandler::notification_center.addReceiverCallback(this, (KCallbackPtr)&KikiController::initOpenGL,
                                                                KDL_NOTIFICATION_TYPE_VIDEO_MODE_CHANGED);

    KEventHandler::notification_center.addReceiverCallback(this, (KCallbackPtr)&KikiController::initOpenGL,
                                                                KDL_NOTIFICATION_TYPE_WINDOW_SIZE_CHANGED);

#ifndef WIN32
    srandom(1); // repeatable random sequence
#endif

    initOpenGL();

    SDL_EnableUNICODE(true);
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL/6);
    SDL_EnableKeyRepeat(0,0);

    // ........................................................ sound
    sound = new KikiSound ();

    // ........................................................ world
    
    world = new KikiWorld();
    addPickHandler (world);
        
    // ........................................................ console    
    KConsole::create();
    KConsole::getConsole()->setPosition (KPosition(80, -20));
    KConsole::getConsole()->setSize (KSize(300, 200));
    KConsole::getConsole()->setDepth (INT_MAX - 10);

    addPickHandler((KPickHandler*)KConsole::getConsole());

    //KConsole::printf ("%s", kikiVersionString);

    // ........................................................ python
    python = NULL; // to prevent PythonWidget sending size messages
    KikiPython * kiki_python = new KikiPython();
    python = kiki_python;

    // ........................................................ gui    
    //gui = new KikiGUI ();
    //addPickHandler(gui);
    //gui->init();
    //gui->hide();

    world->init();
    projection_handler = world;
    
    KikiText::init();
        
    // ........................................................ status display  
    player_status = new KikiStatusDisplay ();
    addPickHandler(player_status);

    // ........................................................ create player  
    getPlayer();
    
    addKeyHandler(this);
    addKeyHandler(&KEventHandler::menu_key_handler); // don't know why I have to add this again !?
    
    // ........................................................ hide cursor

    if (isDebugVersion() == false) SDL_ShowCursor (SDL_DISABLE);

    // ........................................................ python init
    
    python->initPython();
}

// __________________________________________________________________________________________________
void KikiController::initOpenGL ()
{
    // openGL init
    glShadeModel(GL_SMOOTH);
    glCullFace	(GL_BACK);
    
    glEnable (GL_CULL_FACE);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_NORMALIZE);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_COLOR_MATERIAL);
    glEnable (GL_BLEND);
    
    glDepthRange(0.0, 0.5);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_NORMAL_ARRAY);

    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glViewport(0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h); 

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
    
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, 		none);
    glLightModeli  (GL_LIGHT_MODEL_LOCAL_VIEWER, 	0);
    
    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,   none);
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION,  none);
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR,  gray);
    glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 60.0);

    GLint maxLights; 
    glGetIntegerv (GL_MAX_LIGHTS, &maxLights);
    for (GLenum l = GL_LIGHT1; l < (GL_LIGHT0+(GLuint)maxLights); l++)
    {
        glDisable(l);
    }

    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    setGamma (gamma);
}

// --------------------------------------------------------------------------------------------------------
void KikiController::saveScreenShot ()
{
    static int counter = -1;
    KSize screenSize = getScreenSize();
    Uint32 rmask, gmask, bmask, amask;

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x00000000;

    setDisplayFps(false); // hopefully the programm will run faster in the future :-)
    display();

    void * pixels = malloc (screenSize.w * screenSize.h * sizeof(GLuint));

#ifndef WIN32
    glReadPixels (0, 0, screenSize.w, screenSize.h, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pixels);
#else
	glReadPixels (0, 0, screenSize.w, screenSize.h, GL_RGBA, GL_4_BYTES, pixels);
#endif

    //............................................................ reverse order of lines (mirror vertical)
    int scanlineLength = screenSize.w * sizeof(GLuint);
    void * scanline = malloc (scanlineLength);
    for (int lineIndex = 0; lineIndex < screenSize.h/2; lineIndex++)
    {
        memcpy (scanline, 					// copy from bottom to save line
                &((char*)pixels)[lineIndex * scanlineLength], 
                scanlineLength);
        memcpy (&((char*)pixels)[lineIndex * scanlineLength],   // copy from top to bottom
                &((char*)pixels)[(screenSize.h-lineIndex-1) * scanlineLength], 
                scanlineLength);				// copy from save line to top
        memcpy (&((char*)pixels)[(screenSize.h-lineIndex-1) * scanlineLength], 
                scanline, 
                scanlineLength);
    }
    
    //............................................................ create SDL_surface from pixels
    SDL_Surface * saveSurface = SDL_CreateRGBSurfaceFrom (pixels, screenSize.w, screenSize.h, 32,
                                                          screenSize.w * 4, rmask, gmask, bmask, amask);
    
    free (scanline);
    
    if (saveSurface == NULL)
    {
        KConsole::printf("WARNING unable to copy screen surface for screenshot");
        free (pixels);
        return;
    }
    
    std::string screenShotFile;
    //............................................................ search for a free file name
    do  
    {
        counter++;
        screenShotFile = kStringPrintf("%s/kiki_%03d.bmp", getenv ("HOME"), counter);
    }
    while (kFileExists(screenShotFile));
    
    //............................................................ save the screenshot
    if (SDL_SaveBMP(saveSurface, screenShotFile.c_str()) == 0) 
    {
        KConsole::printf("screenshot saved to file %s", kFileAbsPathName(screenShotFile).c_str());
    }
    else // ooops...
    {
        KConsole::printf("WARNING unable to write screenshot to file %s", screenShotFile.c_str());
    }
    
    SDL_FreeSurface(saveSurface);
    free (pixels);
}

// __________________________________________________________________________________________________
bool KikiController::handleKey ( const KKey & key )
{
    //KConsole::printf("KikiController::handleKey %s", key.name.c_str());

    if (key.getUnmodifiedName() == "ESCAPE")
    {
        events[ESCAPE_KEY_EVENT]->triggerActions();
        return true;
    }

    if (key.name == quit_key)
    {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent (&event);
        return true;
    }

    if (key.name == "F9")
    {
        debug_version = !debug_version;
        KConsole::printf("toggle debug mode");
        if (debug_version)
          SDL_ShowCursor (SDL_ENABLE);
        else
          SDL_ShowCursor (SDL_DISABLE);
        return true;
    }

    if (isDebugVersion())
    {
    if (key.name == "e")
    {        
        world->setEditMode (!world->getEditMode()); 
        return true;
    }
    if (key.name == "f")
    {
        world->focusOnPickedPickable();
        return true;
    }
    if (key.name == "b")
    {
        world->setDisplayBorder (!world->flags[KikiWorld::DISPLAY_BORDER]);
        return true;
    }
    if (key.name == "r")
    {
        world->setDisplayRaster (!world->flags[KikiWorld::DISPLAY_RASTER]); 
        return true;
    }
    if (key.name == "d")
    {
        world->flags[KikiWorld::DISPLAY_DOTS] = !world->flags[KikiWorld::DISPLAY_DOTS];
        world->debug_cells = !world->debug_cells;
        return true;
    }
	if (key.name == "c")
	{
		KConsole::getConsole()->show();
	}
    }

    if (key.character >= '1' && key.character <= '9') { speed = key.character - '0'; return true; }
    //if (key.name == "c") { KConsole::getConsole()->clear(); return true; }
            
    return false;
}

// --------------------------------------------------------------------------------------------------------
void KikiController::mouseModeCallback ( const std::string & buttonText )
{	
    if      (buttonText == "r") mouse_mode = KDL_MOUSE_MODE_ROTATE;
    else if (buttonText == "t") mouse_mode = KDL_MOUSE_MODE_TRANSLATE;
    else if (buttonText == "z") mouse_mode = KDL_MOUSE_MODE_SCALE;
}

// --------------------------------------------------------------------------------------------------------
void KikiController::handleMouseButtonEvent ( SDL_MouseButtonEvent & event)
{
    KEventHandler::handleMouseButtonEvent(event);
    
    if (event.state == SDL_RELEASED)
    {
        setMouseMode(KDL_MOUSE_MODE_ROTATE);
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiController::setGamma ( int g )
{
    float gf = 1.0+g/10.0;
    gamma = g;
    SDL_SetGamma (gf, gf, gf);
}

// __________________________________________________________________________________________________
// Global Controller Object

KikiController Controller;


