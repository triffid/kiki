/*
 *  KikiPlayback.h
 *  kiki
 */

#ifndef __KikiPlayback
#define __KikiPlayback

#include "KikiRecorder.h"

#include <KKey.h>
#include <vector>

#include <SDL.h>
#include <SDL_thread.h>

// __________________________________________________________________________________________________
class KikiPlayback
{
    public: // ........................................................................ PUBLIC
    
    static void	start		( const std::string filename );
    static void stop		();
    static int 	playback	( void * );
    
    protected: // ..................................................................... PROTECTED
    
    static SDL_Thread * thread;
    static bool	halt;
    static std::string next_world;
};

#endif
