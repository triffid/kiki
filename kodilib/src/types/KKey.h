/*
 *  KKey.h
 *  kodisein
 */

#ifndef __KKey
#define __KKey

#include <SDL_keyboard.h>
#include <string>

// --------------------------------------------------------------------------------------------------------
struct KKey 
{
    KKey 	( SDL_keysym keySym );
    KKey	( std::string keyName );

    std::string	name;
    char 	character;
    SDLKey	sym;
    int    	mod;
    
    std::string	getUnmodifiedName () const;
    std::string	getModifierName () const;
};

#endif
