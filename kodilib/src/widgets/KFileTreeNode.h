/*
 *  KFileTreeNode.h
 *  kodisein
 */

#ifndef __KFileTreeNode
#define __KFileTreeNode

#include "KPickable.h"
#include "KMatrix.h"
#include "KColor.h"

enum {	KDL_FILE_TYPE_KODISEIN, 
        KDL_FILE_TYPE_KODISEIN_TEXTURESET, 
        KDL_FILE_TYPE_TEXTURE, 
        KDL_FILE_TYPE_UNKNOWN, 
        KDL_FILE_TYPE_DIR };

#define KDL_FILETREENODE_DEFAULT_ALPHA 0.8

class KFileTreeNode : public KPickable, public KMatrix
{
    INTROSPECTION
    
    protected:
    
    int					min_id;
    int					max_id;
    int					type;
    std::string				name;
    PickableVector			children;
    const KFileTreeNode *		parent;
    KColor				node_color;
    
    public:

                                        KFileTreeNode 		( const std::string & );
                                        ~KFileTreeNode 		();
    
            KFileTreeNode *		getRootNode		() const;
            bool			isRootNode		() const { return (parent == NULL); }
            int				getPathLength		() const;
            std::string 			getSuffix 		() const;
            int				getType			() const { return type; }
            const std::string &		getName			() const { return name; }

    virtual std::string 			getPathName     	() const;
    virtual std::string 			getAbsPathName     	() const;

    virtual void			addChild		( KFileTreeNode * );
    virtual void			display 		();
    virtual void			relayout 		();
    virtual void			render			() = 0;
    
    virtual bool			hasSubPickables		() const { return true; }
    virtual const PickableVector *	getSubPickables		() const { return &children; }
    virtual void			setMinId		( int i ) { min_id = i; }
    virtual void			setMaxId		( int i ) { max_id = i; }
    virtual int				getMinId		()  { return min_id; }
    virtual int				getMaxId		()  { return max_id; }
};

#endif

