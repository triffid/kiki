/*
 *  KFileHandler.cpp
 *  kodisein
 */

#include "KFileHandler.h"
#include "KFileTools.h"
#include "KConsole.h"


#ifndef WIN32
#	include <unistd.h> 	// chdir & getcwd
//#include <sys/param.h>	// MAXPATHLEN
#else
// #define MAXPATHLEN 32768 
#	include <direct.h>
//#define getwd(x) getcwd(x, MAXPATHLEN)
#endif

std::vector<std::string> KFileHandler::current_dir_stack;

// --------------------------------------------------------------------------------------------------------
void KFileHandler::init()
{
    current_dir_stack.push_back(kFileGetCurrentPath());
}

// --------------------------------------------------------------------------------------------------------
bool KFileHandler::changeCurrentDir ( const std::string & newCurrentDir )
{
    current_dir_stack.pop_back();
    return pushCurrentDir(newCurrentDir);
}

// --------------------------------------------------------------------------------------------------------
bool KFileHandler::pushCurrentDir ( const std::string & newCurrentDir )
{
    std::string absPathName = kFileAbsPathName(newCurrentDir);
    
    if (chdir(absPathName.c_str()) == 0)
    {
        current_dir_stack.push_back(absPathName);
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------
void KFileHandler::popCurrentDir ()
{
    current_dir_stack.pop_back();
    chdir (current_dir_stack.back().c_str());
}

// --------------------------------------------------------------------------------------------------------
std::string KFileHandler::getCurrentDir ()
{
    return current_dir_stack.back();
}
