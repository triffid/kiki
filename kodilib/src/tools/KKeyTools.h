/*
 *  KKeyTools.h
 *  kodisein
 */

#ifndef __KKeyTools
#define __KKeyTools

#include <string>
#include <SDL_keyboard.h>

extern const char * SDLKeyNames[];
extern const char * SDLModNames[];

class KPosition;

// --------------------------------------------------------------------------------------------------------
SDLKey 		kKeyGetSymForSymName			( const std::string & symName );
SDLMod 		kKeyGetModForModName			( const std::string & modName );
SDL_keysym 	kKeyGetKeysymForKeyName       		( const std::string & keyName );
std::string	kKeyGetNameForSym			( SDLKey keySym );
std::string	kKeyGetNameForMod			( int keyMod );
std::string	kKeyGetNameForKeysym 			( SDL_keysym keySym );

int 		kKeyGetDisplayWidthForKeyName		( const std::string & keyName );
int		kKeyGetDisplayWidthForKeySequence	( const std::string & shortcut );
int 		kKeyDisplayKey 				( const std::string & keyName,  const KPosition & pos );
void 		kKeyDisplayKeySequence 			( const std::string & sequence, const KPosition & pos );

#endif

