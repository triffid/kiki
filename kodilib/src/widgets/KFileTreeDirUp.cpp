/*
 *  KFileTreeDirUp.cpp
 *  kodisein
 */
 
#include "KFileTreeDirUp.h"
#include "KFileTreeDir.h"
#include "KEventHandler.h"
#include "KTools.h"

KDL_CLASS_INTROSPECTION_1 (KFileTreeDirUp, KFileTreeNode)

// --------------------------------------------------------------------------------------------------------
KFileTreeDirUp::KFileTreeDirUp () : KFileTreeNode ( ".." )
{
    node_color.setValues   (0.0, 0.0, 1.0, KDL_FILETREENODE_DEFAULT_ALPHA);
    type = KDL_FILE_TYPE_DIR;
    current_dir_node = NULL;
    parent = NULL;
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeDirUp::setCurrentDir ( KFileTreeDir * currentDir )
{
    current_dir_node = currentDir;
    relayout();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeDirUp::relayout ()
{
    current_dir_node->setPosition(matrix[TX], matrix[TY], matrix[TZ]);
    current_dir_node->relayout();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeDirUp::render ()
{
    int divisions = KEventHandler::flags[KDL_DISPLAY_MODE_FAST] ? 5 : 8;

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glVertex3f( 0.5, -1.0, 0.0);
    glVertex3f(-0.5, -1.0, 0.0);
    glVertex3f( 0.0,  0.0, 0.0);
    glVertex3f( 0.0, -1.0, 0.0);    
    glEnd();
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(0.5, -1.0, 0.0);
    kDisplaySolidSphere(0.4, divisions);
    glTranslated(-1.0, 0.0, 0.0);
    kDisplaySolidSphere(0.4, divisions);
    glPopMatrix();
}

