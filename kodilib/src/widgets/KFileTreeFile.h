/*
 *  KFileTreeFile.h
 *  kodisein
 */

#ifndef __KFileTreeFile
#define __KFileTreeFile

#include "KFileTreeNode.h"

class KFileTreeDir;

class KFileTreeFile : public KFileTreeNode
{
    INTROSPECTION
    
    public:
    
                        KFileTreeFile 	( const KFileTreeDir *, const std::string & );
                        
    virtual void	render		();
}; 

#endif

