/*
 *  KStatusMenuItem.cpp
 *  kodisein
 */

#include "KStatusMenuItem.h"
#include "KConsole.h"
#include "KXMLTools.h"

KDL_CLASS_INTROSPECTION_1 (KStatusMenuItem, KMenuItem)

// --------------------------------------------------------------------------------------------------------
KStatusMenuItem::KStatusMenuItem (const std::string & trueText, const std::string & falseText, const std::string & shortCut) 
    : KMenuItem (trueText,shortCut)
{
    true_text  = trueText; 
    false_text = falseText;
}

// --------------------------------------------------------------------------------------------------------
void KStatusMenuItem::activateItem ()
{
    setState(!getState());
}

// --------------------------------------------------------------------------------------------------------
void KStatusMenuItem::render ()
{
    setState(getState()); // updates text, if value changed
    KMenuItem::render();
}

// --------------------------------------------------------------------------------------------------------
void KStatusMenuItem::setState ( bool s )
{
    if (s != getState())
    {
        if (s == false) 
        {
            KButton::deactivate(); 	// false notification
        }
        else 
        {
            KButton::activate();	// callback & true notification
            picked = false;
        }
    }
    setText (s ? true_text : false_text);
}

// --------------------------------------------------------------------------------------------------------
bool KStatusMenuItem::getState () const
{
    bool value;
    if (receiveValue(&value)) return value; // value provider callback was set
    return (text == true_text);
}

// --------------------------------------------------------------------------------------------------------
std::string KStatusMenuItem::getXMLAttributes () const
{
    std::string attributes = kStringPrintf("name='%s'", true_text.c_str());
    if (shortcut != "") attributes += kStringPrintf(" shortcut='%s'", shortcut.c_str());
    attributes += !getState() ? " status='yes'" : " status='no'";
    return attributes;
}

// --------------------------------------------------------------------------------------------------------
void KStatusMenuItem::setXMLAttributes ( const std::string & xml )
{
    KMenuItem::setXMLAttributes(xml);
    setState (kXMLReadNamedAttribute(xml, "status") == "no");
}


