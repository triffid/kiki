/*
 *  KFileTreeDir.h
 *  kodisein
 */

#ifndef __KFileTreeDir
#define __KFileTreeDir

#include "KFileTreeNode.h"

enum {	KDL_FILETREEDIR_FLAG_SHOW_DOTFILES,
        KDL_FILETREEDIR_FLAG_SHOW_CUBES,
        KDL_FILETREEDIR_FLAG_END };

class KFileTreeDir : public KFileTreeNode
{
    INTROSPECTION

    public:

    static bool					flags[KDL_FILETREEDIR_FLAG_END];
    static int					max_path_depth;
        
    
                        KFileTreeDir 		( const std::string & = "." );
                        KFileTreeDir 		( const KFileTreeDir *, const std::string & );
                        
    void		createTree 		();
                        
    virtual void	render 			();
}; 

#endif

