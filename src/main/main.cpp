/*
 *  main.cpp
 *  kiki
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL.h>
#include "KikiController.h"

// __________________________________________________________________________________________________
// __________________________________________________________________________________________________
//SDL_main.h should take care of converting main to SDL_main for win and macos
int main (int argc, char * argv[])
{
    int width, height;
    SDL_Surface * screen;

    // initialize SDL
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0 ) // SDL_INIT_TIMER
    {
            fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
            exit(1);
    }

#if defined(__APPLE__) && defined(__MACH__)
    // OpenGL attributes
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    // Set video mode
    width  = 1024; 
    height = 695;
#else
    //Any GLX visual should do

    // Set video mode
    width  = 800; 
    height = 600;
#endif
    
    screen = SDL_SetVideoMode (width, height, 0, SDL_OPENGL | SDL_RESIZABLE); //  | SDL_FULLSCREEN 
    if (screen == NULL) 
    {
        fprintf(stderr, "Couldn't initialize SDL video mode: %s\n", SDL_GetError());
        SDL_Quit();
        exit(2);
    }

    // init Controller ...
    Controller.init();

    // ... and he does the rest ...
    Controller.mainLoop();
    
    SDL_Quit();

	fprintf(stderr, "kiki quitted\n");

    return 0;
}

