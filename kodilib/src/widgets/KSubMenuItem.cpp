/*
 *  KSubMenuItem.cpp
 *  kodisein
 */

#include "KSubMenuItem.h"
#include "KEventHandler.h"
#include "KConsole.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KSubMenuItem, KMenuItem)

// --------------------------------------------------------------------------------------------------------
KSubMenuItem::KSubMenuItem ( const std::string & nm, KMenu * menu ) : KMenuItem (nm)
{
    child_menu = menu;
}

// --------------------------------------------------------------------------------------------------------
void KSubMenuItem::setParent ( KWidget * w )    
{
    KMenuItem::setParent(w);
    if (getFGColor()) child_menu->setFGColor(*getFGColor());
    if (getBGColor()) child_menu->setBGColor(*getBGColor());
}

// --------------------------------------------------------------------------------------------------------
void KSubMenuItem::deactivate ()		
{ 
    picked = false;
    child_menu->close();
}

// --------------------------------------------------------------------------------------------------------
void KSubMenuItem::render ()
{
    KMenuItem::render();

    KSize itemSize = getSize();

    if (((KMenu*)parent)->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL]) 
    { 
        glBegin(GL_TRIANGLES); // display down arrow
            glVertex2i(itemSize.w - 21, -itemSize.h/2 + 5);
            glVertex2i(itemSize.w - 13, -itemSize.h/2 - 3);
            glVertex2i(itemSize.w - 5,  -itemSize.h/2 + 5);
        glEnd();
    }
    else     
    {
        glBegin(GL_TRIANGLES); // display right arrow
            glVertex2i(itemSize.w - 13, -itemSize.h/2 + 8);
            glVertex2i(itemSize.w - 13, -itemSize.h/2 - 8);    
            glVertex2i(itemSize.w - 5,  -itemSize.h/2);
        glEnd();
    }

    if (picked) // display child menu
    {
        int spacing = child_menu->getSpacing();
        KSize parentSize = ((KMenu*)parent)->getSize();
        
        if (((KMenu*)parent)->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL]) // display childmenu below
        {
            glTranslatef(0.0, -parentSize.h - spacing, 0.0);
        }
        else // display child menu beside
        {
            glBegin(GL_LINES);
            glVertex2i(itemSize.w + 1, -itemSize.h/2);
            glVertex2i(parentSize.w + spacing, -itemSize.h/2);
            glEnd();

            glTranslatef(parentSize.w + spacing, 0.0, 0.0);
        }
        child_menu->display();
    }
}

// --------------------------------------------------------------------------------------------------------
KSize KSubMenuItem::getSize () const
{
    KSize menuItemSize = KButton::getSize();
    return KSize(menuItemSize.w + 25, menuItemSize.h);
}

// --------------------------------------------------------------------------------------------------------
std::string KSubMenuItem::getXML ( int depth ) const
{
    std::string xml;
    xml += kXMLOpenTag("SubMenu", getXMLAttributes(), depth);
    xml += getChildMenu()->getXML(depth+KDL_XML_INDENT);    
    xml += kXMLCloseTag("SubMenu", depth);
    return xml;
}

// --------------------------------------------------------------------------------------------------------
void KSubMenuItem::setXML ( std::string & xml )
{
    std::string attributes;
    kXMLParseNamedOpenTag(xml, "SubMenu", &attributes);
    setXMLAttributes(attributes);
    child_menu->setXML(xml);
    kXMLParseNamedCloseTag(xml, "SubMenu");
}



