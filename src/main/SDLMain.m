/*
 *  SDLMain.m
 *  kiki
 */

#import <Cocoa/Cocoa.h>
#import <SDL.h>

#import <sys/param.h> // MAXPATHLEN 
#import <unistd.h>

// __________________________________________________________________________________________________
static int    gArgc;
static char  **gArgv;

// __________________________________________________________________________________________________
@interface SDLMain : NSObject
@end

// __________________________________________________________________________________________________
@interface SDLApplication : NSApplication
@end

// __________________________________________________________________________________________________
// __________________________________________________________________________________________________
@implementation SDLApplication

// __________________________________________________________________________________________________
- (void) terminate: (id) sender
{
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent (&event);
}

@end

// __________________________________________________________________________________________________
// __________________________________________________________________________________________________
@implementation SDLMain

// --------------------------------------------------------------------------------------------------------
// set the working directory to the resources directory 
- (void) setupWorkingDirectory
{
    char parentdir[MAXPATHLEN];
    char *c;
    
    strncpy ( parentdir, gArgv[0], sizeof(parentdir) );
    c = (char*) parentdir;

    while (*c != '\0')  c++; // go to end 
    
    while (*c != '/') c--; // back up to parent 
    
    *c++ = '\0'; // cut off last part (binary name) 

    assert ( chdir (parentdir) == 0 );   // chdir to the binary app's parent 
    assert ( chdir ("../Resources") == 0 ); // chdir to the .app's resource directory 
}

// __________________________________________________________________________________________________
- (void) applicationDidFinishLaunching: (NSNotification *) note
{
    int status;

    [self setupWorkingDirectory];

    status = SDL_main (gArgc, gArgv);

    exit(status);
}
@end

#ifdef main
#undef main
#endif

// __________________________________________________________________________________________________
// __________________________________________________________________________________________________
int main(int argc, const char *argv[])
{
    int i;
    
    if ( argc >= 2 && strncmp (argv[1], "-psn", 4) == 0 ) 
    {
        gArgc = 1;
    } 
    else 
    {
        gArgc = argc;
    }
    gArgv = (char**) malloc (sizeof(*gArgv) * (gArgc+1));
    assert (gArgv != NULL);
    for (i = 0; i < gArgc; i++)
    {
        gArgv[i] = (char *)argv[i];
    }
    gArgv[i] = NULL;

    [SDLApplication poseAsClass:[NSApplication class]];
    NSApplicationMain(argc, argv);

    return 0;
}
