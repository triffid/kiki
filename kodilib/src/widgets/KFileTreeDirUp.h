/*
 *  KFileTreeDirUp.h
 *  kodisein
 */

#ifndef __KFileTreeDirUp
#define __KFileTreeDirUp

#include "KFileTreeNode.h"

class KFileTreeDir;

class KFileTreeDirUp : public KFileTreeNode
{
    INTROSPECTION
    
    protected:
    
    KFileTreeDir *	current_dir_node;
    
    public:
    
                KFileTreeDirUp 	();

    void	render 		();
    void	relayout	();
    void	setCurrentDir	( KFileTreeDir * );
}; 

#endif

