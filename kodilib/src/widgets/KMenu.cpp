/*
 *  KMenu.cpp
 *  kodisein
 */

#include "KMenu.h"
#include "KStatusMenuItem.h"
#include "KSubMenuItem.h"

KDL_CLASS_INTROSPECTION_1 (KMenu, KWidgetArray)

bool 		KMenu::show_shortcuts = false;
KKeyRecorder	KMenu::shortcut_recorder;

// --------------------------------------------------------------------------------------------------------
KMenu::KMenu () : KWidgetArray ()
{
    frame_spacing = 0;
    flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
}

// --------------------------------------------------------------------------------------------------------
void KMenu::close()
{
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        if ((*iter)->getClassId() >= KMenuItem::classId())
        {
            ((KMenuItem*)*iter)->deactivate();
        }
        iter++;
    }
    
    if (shortcut_recorder.isRecording())
    {
        shortcut_recorder.stopRecording();
    }
}

// --------------------------------------------------------------------------------------------------------
void KMenu::setXML ( std::string & xml )
{
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        if ((*iter)->getClassId() >= KMenuItem::classId())
        {
            ((KMenuItem*)*iter)->setXML(xml);
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
std::string KMenu::getXML ( int depth ) const
{
    std::string xml;
    
    PickableVector::const_iterator iter = children.begin();
    while (iter != children.end())
    {
        if ((*iter)->getClassId() >= KMenuItem::classId())
        {
            xml += ((KMenuItem*)*iter)->getXML(depth);
        }
        iter++;
    }
    return xml;
}


