/*
 *  KFileTreeDirCurrent.cpp
 *  kodisein
 */

#include "KFileTreeDirCurrent.h"
#include "KFileTools.h"

// --------------------------------------------------------------------------------------------------------
KFileTreeDirCurrent::KFileTreeDirCurrent ( const std::string & dirName ) : KFileTreeDir (std::string("."))
{
    current_dir_path = kFileAbsPathName(dirName);
}

