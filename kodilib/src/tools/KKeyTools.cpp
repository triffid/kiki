/*
 *  KKeyTools.cpp
 *  kodisein
 */

#include "KKeyTools.h"
#include "KStringTools.h"
#include "KTools.h"

#include <SDL.h>

#define SDLLastModSym		17

#define KDL_MOD_ICON_WIDTH	13
#define KDL_MOD_ICON_HEIGHT	13
#define KDL_MOD_ICON_SPACING	2
#define KDL_MOD_KEY_SPACING	5
#define KDL_MENU_CHARACTER_WIDTH	9
#define KDL_MENU_CHARACTER_HEIGHT	15

#include "KKeySymbols.h"

const char * SDLKeyNames[] = {
	"FIRST",
        "", "", "", "", "", "", "",
	"BACKSPACE", "TAB", // 9
         "", "",
	"CLEAR", "RETURN", // 13
        "", "", "", "", "",
	"PAUSE", "RETURN", // 20
        "", "", "", "", "", "",
	"ESCAPE", // 27
        "", "", "", "",
	"SPACE", // 32
        "EXCLAIM", "QUOTEDBL",	"HASH",	"DOLLAR",
        "",
	"AMPERSAND", "QUOTE", "LEFTPAREN", "RIGHTPAREN", "ASTERISK", "PLUS", "COMMA", "MINUS", "PERIOD", "SLASH",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
        "COLON", "SEMICOLON", "LESS", "EQUALS", "GREATER", "QUESTION",
	"AT", //  skip uppercase letters 64 
        "", "", "", "", "", "", // 70 
        "", "", "", "", "", "", "", "", "", "", // 80
        "", "", "", "", "", "", "", "", "", "", // 90
	"LEFTBRACKET", "BACKSLASH", "RIGHTBRACKET", "CARET", "UNDERSCORE", "BACKQUOTE",
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
        "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", // 122
        "", "", "", "",
	"DELETE", // end of ASCII mapped keysyms 127
        "", "", "", // 130
        "", "", "", "", "", "", "", "", "", "", // 140
        "", "", "", "", "", "", "", "", "", "", // 150
        "", "", "", "", "", "", "", "", "",  
	"WORLD0", // international keyboard syms 160 
	"WORLD1", "WORLD2", "WORLD3", "WORLD4", "WORLD5", "WORLD6", "WORLD7", "WORLD8", "WORLD9",
	"WORLD10", "WORLD11", "WORLD12", "WORLD13", "WORLD14", "WORLD15", "WORLD16", "WORLD17",
	"WORLD18", "WORLD19", "WORLD20", "WORLD21", "WORLD22", "WORLD23", "WORLD24", "WORLD25",
	"WORLD26", "WORLD27", "WORLD28", "WORLD29", "WORLD30", "WORLD31", "WORLD32", "WORLD33",
	"WORLD34", "WORLD35", "WORLD36", "WORLD37", "WORLD38", "WORLD39", "WORLD40", "WORLD41",
	"WORLD42", "WORLD43", "WORLD44", "WORLD45", "WORLD46", "WORLD47", "WORLD48", "WORLD49",
	"WORLD50", "WORLD51", "WORLD52", "WORLD53", "WORLD54", "WORLD55", "WORLD56", "WORLD57",
	"WORLD58", "WORLD59", "WORLD60", "WORLD61", "WORLD62", "WORLD63", "WORLD64", "WORLD65",
	"WORLD66", "WORLD67", "WORLD68", "WORLD69", "WORLD70", "WORLD71", "WORLD72", "WORLD73",
	"WORLD74", "WORLD75", "WORLD76", "WORLD77", "WORLD78", "WORLD79", "WORLD80", "WORLD81",
	"WORLD82", "WORLD83", "WORLD84", "WORLD85", "WORLD86", "WORLD87", "WORLD88", "WORLD89",
	"WORLD90", "WORLD91", "WORLD92", "WORLD93", "WORLD94", "WORLD95", 
        // numeric keypad 256
	"KP0", "KP1", "KP2", "KP3", "KP4", "KP5", "KP6", "KP7", "KP8", "KP9",
	"KPPERIOD", "KPDIVIDE", "KPMULTIPLY", "KPMINUS", "KPPLUS", "KPENTER", "KPEQUALS", // 272
         // arrows + home/end pad 273
	"UP", "DOWN", "RIGHT", "LEFT", "INSERT", "HOME", "END", "PAGEUP", "PAGEDOWN",
        // function keys 282
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",	
        "F9", "F10", "F11", "F12", "F13", "F14", "F15", // 296
        "", "", "", 
        // key state modifier keys 300
	"NUMLOCK", "CAPSLOCK", "SCROLLOCK", "SHIFT", "SHIFT",	"CTRL", "CTRL", 
        "ALT", "ALT", "META", "META", 
        "SUPER",		// left "Windows" key 
	"SUPER",		// right "Windows" key 
	"MODE",			// "Alt Gr" key
	"COMPOSE",		// multi-key compose key 
	"HELP",	"PRINT", 
        "SYSREQ", "BREAK", "MENU",
	"POWER",		// power Macintosh power key 
	"EURO",			// some european keyboards 
	"UNDO",			// atari keyboard has Undo 
	"LAST" // 323 
};

const char * SDLModNames[] = {
	"NONE", "SHIFT", "CTRL", "ALT", "META", "LSHIFT", "RSHIFT", "LCTRL", "RCTRL", 
        "LALT", "RALT", "LMETA", "RMETA", "NUM", "CAPS", "MODE", "RESERVED"
};

const int SDLModNameMapping[] = {
	KMOD_NONE, KMOD_SHIFT, KMOD_CTRL, KMOD_ALT, KMOD_META, KMOD_LSHIFT, KMOD_RSHIFT,
	KMOD_LCTRL, KMOD_RCTRL,	KMOD_LALT, KMOD_RALT, KMOD_LMETA, KMOD_RMETA, KMOD_NUM,
	KMOD_CAPS, KMOD_MODE, KMOD_RESERVED
};

// --------------------------------------------------------------------------------------------------------
int kKeyGetDisplayWidthForPureKey ( const std::string & keyName )
{
    SDLKey keySym = kKeyGetSymForSymName(keyName);
    if (keySym > 32 && keySym < 127) // ascii characters
    {
        return KDL_MENU_CHARACTER_WIDTH;
    }
    else if (keySym >= 256 && keySym <= 272) // key pad keys
    {
        // display KP symbol and character
        if (keySym == SDLK_KP_ENTER) return (atoi(KDL_KEY_ICON_ENTER[0]));
        int width = atoi(KDL_KEY_ICON_KP[0]);
        return (width + KDL_MENU_CHARACTER_WIDTH);
    }
    
    switch (keySym)
    {
        case SDLK_BACKSPACE:
            return atoi(KDL_KEY_ICON_BACKSPACE[0]);
        case SDLK_TAB:
            return atoi(KDL_KEY_ICON_TAB[0]);
        case SDLK_UP:
            return atoi(KDL_KEY_ICON_UP[0]);
        case SDLK_DOWN:
            return atoi(KDL_KEY_ICON_DOWN[0]);
        case SDLK_LEFT:
            return atoi(KDL_KEY_ICON_LEFT[0]);
        case SDLK_RIGHT:
            return atoi(KDL_KEY_ICON_RIGHT[0]);
        case SDLK_PAGEUP:
            return atoi(KDL_KEY_ICON_PAGEUP[0]);
        case SDLK_PAGEDOWN:
            return atoi(KDL_KEY_ICON_PAGEDOWN[0]);
        case SDLK_DELETE:
            return atoi(KDL_KEY_ICON_DELETE[0]);
        case SDLK_HOME:
            return atoi(KDL_KEY_ICON_HOME[0]);
        case SDLK_END:
            return atoi(KDL_KEY_ICON_END[0]);
        case SDLK_RETURN:
            return atoi(KDL_KEY_ICON_RETURN[0]);
        case SDLK_KP_ENTER:
            return atoi(KDL_KEY_ICON_ENTER[0]);

        default:
            return KDL_MENU_CHARACTER_WIDTH * keyName.length();
    }

    return 0;
}

// --------------------------------------------------------------------------------------------------------
int kKeyGetDisplayWidthForModifier ( const std::string & modName )
{    
    switch (modName[0])
    {
        case 'M': // META (APPLE)
            return atoi(KDL_KEY_ICON_META[0]);
        case 'S': // SHIFT
            return atoi(KDL_KEY_ICON_SHIFT[0]);
        case 'A': // ALT
            return atoi(KDL_KEY_ICON_ALT[0]);
        case 'C': // CTRL
            return atoi(KDL_KEY_ICON_CTRL[0]);
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
int kKeyGetDisplayWidthForKey ( const std::string & keyName )
{
    unsigned int keyPos = keyName.find('_', 0);
    if (keyPos == std::string::npos) 
    {
        return kKeyGetDisplayWidthForPureKey(keyName) + KDL_MOD_KEY_SPACING;
    }
    
    std::string mod = keyName.substr(0, keyPos);
    std::string key = keyName.substr(keyPos+1);
    int width = 0;

    // width of the modifier symbols
    std::vector<std::string> modNames = kStringGetComponents(mod, "+");
    std::vector<std::string>::iterator iter = modNames.begin();
    while (iter != modNames.end())
    {
        width += kKeyGetDisplayWidthForModifier ((*iter));
        width += KDL_MOD_ICON_SPACING;
        iter++;
    }
    // width of the pure key
    width += kKeyGetDisplayWidthForPureKey (key);
    width += KDL_MOD_KEY_SPACING;

    return width;
}

// --------------------------------------------------------------------------------------------------------
int kKeyGetDisplayWidthForKeySequence ( const std::string & shortcut )
{
    int width = 0;
    std::vector<std::string> keyNames = kStringGetComponents(shortcut, " ");
    std::vector<std::string>::iterator iter = keyNames.begin();
    while (iter != keyNames.end())
    {
        width += kKeyGetDisplayWidthForKey((*iter)); // the key width
        width += KDL_MOD_KEY_SPACING;                  // plus the dividing space
        iter++;
    }
    return width;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
int kKeyDisplayModifier ( const std::string & modName, const KPosition & pos )
{    
    KPosition iconPos(pos.x, pos.y - KDL_MOD_ICON_SPACING);
    switch (modName[0])
    {
        case 'M': // META (APPLE)
            return kDisplayXPMIcon(KDL_KEY_ICON_META, iconPos);
        case 'S': // SHIFT
            return kDisplayXPMIcon(KDL_KEY_ICON_SHIFT, iconPos);
        case 'A': // ALT
            return kDisplayXPMIcon(KDL_KEY_ICON_ALT, iconPos);
        case 'C': // CTRL
            return kDisplayXPMIcon(KDL_KEY_ICON_CTRL, iconPos);
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
int kKeyDisplayPureKey ( const std::string & keyName, const KPosition & pos )
{
    KPosition start = pos;
    KPosition iconPos(pos.x, pos.y - KDL_MOD_ICON_SPACING);

    SDLKey keySym = kKeyGetSymForSymName(keyName);
    if (keySym > 32 && keySym < 127) // ascii characters
    {
        kDisplayString(std::string(1, keySym), pos);
        return KDL_MENU_CHARACTER_WIDTH;
    }
    else if (keySym >= 256 && keySym <= 272) // key pad keys
    {
        if (keySym == SDLK_KP_ENTER) 
        {
            return (start.x + kDisplayXPMIcon(KDL_KEY_ICON_ENTER, iconPos));
        }

        // display KP symbol and character
        start.x += kDisplayXPMIcon(KDL_KEY_ICON_KP, iconPos) + KDL_MOD_ICON_SPACING;
        switch (keySym)
        {
            case SDLK_KP0: kDisplayString("0", start); break;
            case SDLK_KP1: kDisplayString("1", start); break;
            case SDLK_KP2: kDisplayString("2", start); break;
            case SDLK_KP3: kDisplayString("3", start); break;
            case SDLK_KP4: kDisplayString("4", start); break;
            case SDLK_KP5: kDisplayString("5", start); break;
            case SDLK_KP6: kDisplayString("6", start); break;
            case SDLK_KP7: kDisplayString("7", start); break;
            case SDLK_KP8: kDisplayString("8", start); break;
            case SDLK_KP9: kDisplayString("9", start); break;
            case SDLK_KP_PERIOD: kDisplayString(".", start); break;
            case SDLK_KP_DIVIDE: kDisplayString("/", start); break;
            case SDLK_KP_MULTIPLY: kDisplayString("*", start); break;
            case SDLK_KP_MINUS: kDisplayString("-", start); break;
            case SDLK_KP_PLUS: kDisplayString("+", start); break;
            case SDLK_KP_EQUALS: kDisplayString("+", start); break;
            default:
            break;
        }
        return (start.x + KDL_MENU_CHARACTER_WIDTH);
    }
    
    switch (keySym)
    {
        case SDLK_BACKSPACE:
            return kDisplayXPMIcon(KDL_KEY_ICON_BACKSPACE, iconPos);
        case SDLK_TAB:
            return kDisplayXPMIcon(KDL_KEY_ICON_TAB, iconPos);
        case SDLK_UP:
            return kDisplayXPMIcon(KDL_KEY_ICON_UP, iconPos);
        case SDLK_DOWN:
            return kDisplayXPMIcon(KDL_KEY_ICON_DOWN, iconPos);
        case SDLK_LEFT:
            return kDisplayXPMIcon(KDL_KEY_ICON_LEFT, iconPos);
        case SDLK_RIGHT:
            return kDisplayXPMIcon(KDL_KEY_ICON_RIGHT, iconPos);
        case SDLK_PAGEUP:
            return kDisplayXPMIcon(KDL_KEY_ICON_PAGEUP, iconPos);
        case SDLK_PAGEDOWN:
            return kDisplayXPMIcon(KDL_KEY_ICON_PAGEDOWN, iconPos);
        case SDLK_DELETE:
            return kDisplayXPMIcon(KDL_KEY_ICON_DELETE, iconPos);
        case SDLK_HOME:
            return kDisplayXPMIcon(KDL_KEY_ICON_HOME, iconPos);
        case SDLK_END:
            return kDisplayXPMIcon(KDL_KEY_ICON_END, iconPos);
        case SDLK_RETURN:
            return kDisplayXPMIcon(KDL_KEY_ICON_RETURN, iconPos);
        default:
            kDisplayString(keyName, pos);
            return KDL_MENU_CHARACTER_WIDTH * keyName.length();
    }

    return 0;
}

// --------------------------------------------------------------------------------------------------------
int kKeyDisplayKey ( const std::string & keyName, const KPosition & pos )
{
    KPosition start = pos;
    unsigned int keyPos = keyName.find('_', 0);
    if (keyPos == std::string::npos) 
    {
        return start.x + kKeyDisplayPureKey(keyName, start) + KDL_MOD_KEY_SPACING;
    }

    std::string mod = keyName.substr(0, keyPos);
    std::string key = keyName.substr(keyPos+1);

    // display the modifier symbols
    std::vector<std::string> modNames = kStringGetComponents(mod, "+");
    std::vector<std::string>::iterator iter = modNames.begin();
    while (iter != modNames.end())
    {
        start.x += kKeyDisplayModifier ((*iter), start);
        start.x += KDL_MOD_ICON_SPACING;
        iter++;
    }
    // display the pure key symbol
    start.x += kKeyDisplayPureKey (key, start);
    start.x += KDL_MOD_KEY_SPACING;
    return start.x;
}

// --------------------------------------------------------------------------------------------------------
void kKeyDisplayKeySequence ( const std::string & shortcut, const KPosition & pos )
{
    KPosition start = pos;
    std::vector<std::string> keyNames = kStringGetComponents(shortcut, " ");
    std::vector<std::string>::iterator iter = keyNames.begin();
    while (iter != keyNames.end())
    {
        start.x = kKeyDisplayKey((*iter), start);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
SDLKey kKeyGetSymForSymName ( const std::string & keyName )
{
    for (int i = SDLK_FIRST; i < SDLK_LAST; i++)
    {
        if (SDLKeyNames[i] == keyName) 
        {
            return (SDLKey)i;
        }
    }
    return SDLK_LAST;
}

// --------------------------------------------------------------------------------------------------------
SDLMod kKeyGetModForModName ( const std::string & modName )
{
    if (modName == "") return KMOD_NONE;
    for (int i = 0; i < SDLLastModSym; i++)
    {
        if (SDLModNames[i] == modName) 
        {
            return (SDLMod)SDLModNameMapping[i];
        }
    }
    return KMOD_NONE;
}

// --------------------------------------------------------------------------------------------------------
SDL_keysym kKeyGetKeysymForKeyName ( const std::string & keyName )
{
    unsigned int pos = keyName.find('_');
    
    std::string modString;
    std::string symString = keyName;
    
    SDL_keysym key;

    if (pos != std::string::npos)
    {
        modString = keyName.substr(0, pos);
        symString = keyName.substr(pos+1);
    }
    
    key.sym = kKeyGetSymForSymName (symString);
    key.mod = kKeyGetModForModName (modString);
    
    return key;
}

// --------------------------------------------------------------------------------------------------------
std::string kKeyGetNameForSym ( SDLKey keySym )
{
    return SDLKeyNames[keySym];
}

// --------------------------------------------------------------------------------------------------------
std::string kKeyGetNameForMod ( int keyMod )
{
    for (int i = 0; i < SDLLastModSym; i++)
    {
        if (SDLModNameMapping[i] == keyMod)
        {
            return SDLModNames[i];
        }
    }
    return SDLKeyNames[SDLLastModSym];
}

// --------------------------------------------------------------------------------------------------------
std::string kKeyGetNameForKeysym ( SDL_keysym keySym )
{
    std::string keyName = kKeyGetNameForSym(keySym.sym);
    
    if (keySym.mod)
    {
        std::string modifierString;
        if (keySym.mod & KMOD_SHIFT) modifierString += kKeyGetNameForMod(KMOD_SHIFT) + "+";
        if (keySym.mod & KMOD_CTRL)  modifierString += kKeyGetNameForMod(KMOD_CTRL) + "+";
        if (keySym.mod & KMOD_ALT)   modifierString += kKeyGetNameForMod(KMOD_ALT)  + "+";
        if (keySym.mod & KMOD_META)  modifierString += kKeyGetNameForMod(KMOD_META) + "+";
        if (modifierString.size() > 0)
        {
            modifierString.erase(modifierString.size()-1);
            keyName = modifierString + "_" + keyName;
        }
    }
        
    return keyName;
}


