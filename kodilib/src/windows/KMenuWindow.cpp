/*
 *  KMenuWindow.cpp
 *  kodisein
 */

#include "KMenuWindow.h"
#include "KEventHandler.h"
#include "KOrthographicProjection.h"
#include "KKeyHandler.h"
#include "KSubMenuItem.h"
#include "KXMLTools.h"
#include "KConsole.h"
#include "KColor.h"

KDL_CLASS_INTROSPECTION_1 (KMenuWindow, KWindow)

// --------------------------------------------------------------------------------------------------------
KMenuWindow::KMenuWindow () : KWindow ( 0 )
{
    widget = new KMenu (); 
    projection = new KOrthographicProjection (); 
    projection->setViewportBorder(KDL_WINDOW_DEFAULT_VIEWPORT_BORDER, KDL_WINDOW_DEFAULT_VIEWPORT_BORDER, 
                                  KDL_WINDOW_DEFAULT_VIEWPORT_BORDER, KDL_WINDOW_DEFAULT_VIEWPORT_BORDER);
    flags.resize(KDL_WINDOW_FLAG_END);
    flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS]	 = false;
    flags[KDL_MENUWINDOW_FLAG_STATUS_RELEASING]	 = false;
    flags[KDL_MENUWINDOW_FLAG_STATUS_MOVING]	 = false;
    widget->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = true;
    widget->setWindow  (this); 
    widget->setBGColor (KColor(0.0, 0.0, 0.0, 0.6));
    widget->setFGColor (KColor(0.7, 0.7, 0.7, 1.0));

    flags[KDL_PICKHANDLER_FLAG_DOUBLECLICK_ENABLED] = false;
}

// --------------------------------------------------------------------------------------------------------
void KMenuWindow::addMenuItem ( KMenuItem * mi )
{
    pickables.push_back(mi);
    widget->addChild(mi);
}

// --------------------------------------------------------------------------------------------------------
KMenuItem * itemWithCallbackInVector ( KCallbackPtr cb, const PickableVector * pv )
{
    PickableVector::const_iterator iter = pv->begin();
    while (iter != pv->end())
    {
        if ((*iter)->getClassId() >= KMenuItem::classId())
        {
            if (((KMenuItem*)*iter)->hasCallback(cb)) return ((KMenuItem*)*iter);
        }
        if ((*iter)->hasSubPickables())
        {
            KMenuItem * item = itemWithCallbackInVector(cb, (*iter)->getSubPickables());
            if (item) return item;
        }
        iter++;
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KMenuItem * KMenuWindow::getItemWithCallback (KCallbackPtr cb)
{
    return itemWithCallbackInVector(cb, widget->getChildren());
}

// --------------------------------------------------------------------------------------------------------
bool KMenuWindow::shouldPick ( const KPickable * pickable )
{
    if (flags[KDL_MENUWINDOW_FLAG_STATUS_MOVING] || flags[KDL_MENUWINDOW_FLAG_STATUS_RELEASING])
    {
        if ((pickable->getClassId() >= KMenuItem::classId()) == false)
        {
            return false; // prevent button activation in menu rollover (focus) mode
        }
    }
     
    return true;
}

// --------------------------------------------------------------------------------------------------------
void KMenuWindow::picked ()
{
    if (picked_pickable->getClassId() >= KMenuItem::classId())
    {
        KMenuItem * item = (KMenuItem*)picked_pickable;
        
        if (flags[KDL_MENUWINDOW_FLAG_STATUS_RELEASING]) 
        {
            item->activate();
        }
        else
        {
            ((KMenu *)(item->getParent()))->close();
            item->highlight();
            flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] = true;
        }
    }
    else // close menu if button was picked
    {
        flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] = false;
        ((KMenu*)widget)->close();
    }
}

// --------------------------------------------------------------------------------------------------------
// returns the id of the item at current locator location
bool KMenuWindow::mouseMotion ( const KMouseEvent & mouseEvent )
{
    if (flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS]) // handles motion only in focus mode
    {
        flags[KDL_MENUWINDOW_FLAG_STATUS_MOVING] = true;
        KWindow::pick (mouseEvent);
        flags[KDL_MENUWINDOW_FLAG_STATUS_MOVING] = false;
        return true;
    }
    
    return false;
}

// --------------------------------------------------------------------------------------------------------
bool KMenuWindow::pick( const KMouseEvent & mouseEvent )
{	
    bool itemPicked = KWindow::pick(mouseEvent);
    
    if (itemPicked == false)
    {
        flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] = false;
        ((KMenu*)widget)->close();
    }
    
    return itemPicked;
}

// --------------------------------------------------------------------------------------------------------
void KMenuWindow::release( const KMouseEvent & mouseEvent )
{    
    if (flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS])
    {
        flags[KDL_MENUWINDOW_FLAG_STATUS_RELEASING] = true;
        bool pickedItem = KWindow::pick (mouseEvent);
        flags[KDL_MENUWINDOW_FLAG_STATUS_RELEASING] = false;
        
        if (KMenu::shortcut_recorder.isRecording())
        {
            KEventHandler::release_handler = this;
            return;
        }

        if (pickedItem && picked_pickable && picked_pickable->getClassId() >= KSubMenuItem::classId())
        {
            return;
        }
        
        flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] = false;
    }

    ((KMenu*)widget)->close();
}

// --------------------------------------------------------------------------------------------------------
void KMenuWindow::unpicked ()
{
    if (flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] == false)
    {
        ((KMenu*)widget)->close();
    }
}

// --------------------------------------------------------------------------------------------------------
void KMenuWindow::setXML ( std::string & xml )
{
    if (kXMLParseNamedOpenTag(xml, "Menu", NULL, false) != "")
    {
        ((KMenu*)widget)->setXML(xml);
        kXMLParseNamedCloseTag(xml, "Menu");
    }
}

// --------------------------------------------------------------------------------------------------------
std::string KMenuWindow::getXML ( int depth ) const
{
    std::string xml;
    xml += kXMLOpenTag("Menu", "", depth);
    xml += ((KMenu*)widget)->getXML(depth+KDL_XML_INDENT);
    xml += kXMLCloseTag("Menu", depth);
    return xml;
}

