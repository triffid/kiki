/*
 *  KFileTreeNode.cpp
 *  kodisein
 */

#include "KFileTreeNode.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_2 (KFileTreeNode, KPickable, KMatrix)

// --------------------------------------------------------------------------------------------------------
KFileTreeNode::KFileTreeNode ( const std::string & n ) : KPickable (),  KMatrix ()
{
    name = n;
    parent = NULL;
}

// --------------------------------------------------------------------------------------------------------
KFileTreeNode::~KFileTreeNode ()
{
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        delete (*iter);
        iter++;
    }
    children.clear();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeNode::addChild ( KFileTreeNode * c )
{
    children.push_back(c);
}

// --------------------------------------------------------------------------------------------------------
KFileTreeNode * KFileTreeNode::getRootNode () const
{
    if (parent) 
    {
        return parent->getRootNode();
    }
    return (KFileTreeNode*)this;
}

// --------------------------------------------------------------------------------------------------------
std::string KFileTreeNode::getSuffix () const
{
    unsigned int pos = name.rfind('.');
    if (pos < name.size()) 
    {
        return name.substr(pos+1);
    }
    else 
    {	
        return "";
    }
}

// --------------------------------------------------------------------------------------------------------
int KFileTreeNode::getPathLength () const
{
    if (parent) 
    {
        return parent->getPathLength() + 1;
    }
    return 0;
}

// --------------------------------------------------------------------------------------------------------
std::string KFileTreeNode::getAbsPathName () const
{
    if (parent)
    {
        return parent->getAbsPathName() + "/" + name;
    }
    return name;
}

// --------------------------------------------------------------------------------------------------------
std::string KFileTreeNode::getPathName () const
{
    if (parent)
    {
        return parent->getPathName() + "/" + name;
    }
    return name;
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeNode::relayout ()
{
    int side = (int)ceil(sqrt(double(children.size()))); 
    int pl = getPathLength() + 1; 
    float scalePow = pow(0.6, kMin(4, pl));
    float transPow = scalePow;
    int index = 0;
        
    if (pl > 3)
    {
        scalePow = 1.0;
        transPow = 0.5;
    }
        
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        int x = (index % side) - side/2;
        int z = (index / side) - side/2;
        ((KFileTreeNode*)*iter)->reset();
        ((KFileTreeNode*)*iter)->transform(*this);
        ((KFileTreeNode*)*iter)->translate(x*2.0*transPow+0.1, pl*2.0*transPow+0.2, z*2.0*transPow+0.1);
        ((KFileTreeNode*)*iter)->scale(scalePow, scalePow, scalePow);
        ((KFileTreeNode*)*iter)->relayout();
        iter++;
        index++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeNode::display ()
{
    glPushMatrix();
    glMultMatrix();
    loadId ();
    if	(picked) glColor4f (1.0, 1.0, 1.0, 1.0);
    else         node_color.glColor();
    render();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        if (((KFileTreeNode*)*iter)->getType() == KDL_FILE_TYPE_DIR)
        {
            getPosition().glVertex();
            ((KFileTreeNode*)*iter)->getPosition().glVertex();
        }
        iter++;
    }
    glEnd();
    glEnable(GL_LIGHTING);
    
    iter = children.begin();
    while (iter != children.end())
    {
        ((KFileTreeNode*)*iter)->display();
        iter++;
    }
}

