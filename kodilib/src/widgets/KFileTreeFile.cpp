/*
 *  KFileTreeFile.cpp
 *  kodisein
 */

#include "KFileTreeFile.h"
#include "KFileTreeDir.h"

KDL_CLASS_INTROSPECTION_1 (KFileTreeFile, KFileTreeNode)

// --------------------------------------------------------------------------------------------------------
KFileTreeFile::KFileTreeFile ( const KFileTreeDir * d, const std::string & n ) : KFileTreeNode ( n )
{
    parent = d;
    type   = KDL_FILE_TYPE_UNKNOWN;
    
    std::string suffix = getSuffix ();
    if (suffix == "kds")
    {
        node_color.setValues   (1.0, 0.5, 0.0, KDL_FILETREENODE_DEFAULT_ALPHA);
        type = KDL_FILE_TYPE_KODISEIN;
    }
    else if (suffix == "kts")
    {
        node_color.setValues   (0.5, 0.5, 0.5, KDL_FILETREENODE_DEFAULT_ALPHA);
        type = KDL_FILE_TYPE_KODISEIN_TEXTURESET;
    }
    else if (suffix == "tga" || suffix == "tif" || suffix == "jpg" || suffix == "png" || suffix == "gif")
    {
        node_color.setValues   (0.0, 1.0, 0.0, KDL_FILETREENODE_DEFAULT_ALPHA);
        type = KDL_FILE_TYPE_TEXTURE;
    }
    else
    {
        if (n[0] == '.') node_color.setValues (0.1, 0.1, 0.1, KDL_FILETREENODE_DEFAULT_ALPHA);
        else             node_color.setValues (0.25, 0.25, 0.25, KDL_FILETREENODE_DEFAULT_ALPHA);
        type   = KDL_FILE_TYPE_UNKNOWN;
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeFile::render ()
{
    if (type == KDL_FILE_TYPE_KODISEIN) glutSolidIcosahedron();
    else if (type == KDL_FILE_TYPE_TEXTURE) 
    {
        glPushMatrix();
        glScaled(1.0, 0.5, 1.0);
        glutSolidCube(1.8);
        glPopMatrix();
    }
    else if (type == KDL_FILE_TYPE_KODISEIN_TEXTURESET) 
    {
        glPushMatrix();
        glTranslated(-0.5, 0.0,  0.5); glutSolidCube(0.8);
        glTranslated( 0.0, 0.0, -1.0); glutSolidCube(0.8);
        glTranslated( 1.0, 0.0,  0.0); glutSolidCube(0.8);
        glTranslated( 0.0, 0.0,  1.0); glutSolidCube(0.8);
        glPopMatrix();
    }
    else glutSolidCube(0.5);
}

