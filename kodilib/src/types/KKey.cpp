/*
 *  KKey.cpp
 *  kodisein
 */

#include "KKey.h"
#include "KKeyTools.h"

// --------------------------------------------------------------------------------------------------------
KKey::KKey ( SDL_keysym keySym )
{
    name = kKeyGetNameForKeysym(keySym);
    character = 0;
    if ( (keySym.unicode & 0xFF80) == 0 ) 
    {
        character = keySym.unicode & 0x7F;
    }
    sym = keySym.sym;
    mod = keySym.mod;
}

// --------------------------------------------------------------------------------------------------------
KKey::KKey ( std::string keyName )
{
    name = keyName;
    character = 0; // should maybe be fixed sometimes
    sym = kKeyGetSymForSymName (getUnmodifiedName ());
    mod = kKeyGetModForModName (getModifierName ());
}

// --------------------------------------------------------------------------------------------------------
std::string KKey::getUnmodifiedName () const
{
    unsigned int keyPos = name.find('_', 0);
    if (keyPos == std::string::npos) 
    {
        return name;
    }
    return name.substr(keyPos+1);
}

// --------------------------------------------------------------------------------------------------------
std::string KKey::getModifierName () const
{
    unsigned int keyPos = name.find('_', 0);
    if (keyPos == std::string::npos) 
    {
        return "";
    }
    return name.substr(0, keyPos);
}
