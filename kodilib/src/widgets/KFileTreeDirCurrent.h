/*
 *  KFileTreeDirCurrent.h
 *  kodisein
 */

#ifndef __KFileTreeDirCurrent
#define __KFileTreeDirCurrent

#include "KFileTreeDir.h"

class KFileTreeDirCurrent : public KFileTreeDir
{
    std::string	current_dir_path; 	// absolute path of the current ('.') directory
    
    public:
    
                KFileTreeDirCurrent	( const std::string & );

    std::string	getAbsPathName		() const { return current_dir_path; }
};

#endif
