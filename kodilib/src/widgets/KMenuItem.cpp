/*
 *  KMenuItem.cpp
 *  kodisein
 */

#include "KMenuItem.h"
#include "KEventHandler.h"
#include "KConsole.h"
#include "KMenu.h"
#include "KKeyRecorder.h"
#include "KColor.h"
#include "KTools.h"
#include "KXMLTools.h"
#include "KKeyTools.h"

#include <SDL.h>

KDL_CLASS_INTROSPECTION_1 (KMenuItem, KButton)

// --------------------------------------------------------------------------------------------------------
KMenuItem::KMenuItem (const std::string & n, const std::string & shortCut) : KButton (n)
{ 
    setLargeFont(true);
    shortcut = "";
    setShortcut(shortCut);
    size.h = KDL_MENU_DEFAULT_ITEM_HEIGHT;
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::setShortcut ( const std::string & shortcutString )
{
    if (shortcutString != shortcut)
    {
        KEventHandler::menu_key_handler.removeSequenceCallback
                                                    (shortcut, this, (KCallbackPtr)&KMenuItem::activate);
        shortcut = shortcutString;
        if (!KEventHandler::menu_key_handler.isSaveSequenceCallback(shortcut))
        {
            // is an unsave shortcut, so restart the shortcut recording
            std::string errorMessage = kStringPrintf
            ("You can't use this shortcut (%s)\nbecause it's already in use.\nTry another one.", 
                                            shortcutString.c_str());
            KConsole::printError(errorMessage, true);

            KMenu::shortcut_recorder.startRecordingSequence((KObject*)this, 
                                                        (KSetStringPtr)&KMenuItem::setShortcut, 2);
            shortcut = "";
        }
        else
        {
            KEventHandler::menu_key_handler.setSequenceCallback
                                                    (shortcut, this, (KCallbackPtr)&KMenuItem::activate);
        }
        if (KMenu::show_shortcuts) 
        {
            ((KMenu*)parent)->layout();
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::highlight ()
{ 
    picked = true; 
}
 
// --------------------------------------------------------------------------------------------------------
void KMenuItem::setPicked ( bool p )
{ 
    if (p) 
    {
        highlight();
    }
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::activate ()
{
    if (SDL_GetModState() == (KMOD_LALT | KMOD_LCTRL) && flags[KDL_WIDGET_FLAG_VISIBLE])
    {
        KEventHandler::release_handler = NULL;
        setShortcut("");
        KMenu::shortcut_recorder.startRecordingSequence((KObject*)this, (KSetStringPtr)&KMenuItem::setShortcut, 2);
    }
    else
    {
        activateItem();
    }
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::activateItem ()
{ 
    KButton::activate();
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::deactivate ()
{ 
    picked = false;
}

// --------------------------------------------------------------------------------------------------------
std::string KMenuItem::getXMLAttributes () const
{
    std::string attributes = kStringPrintf("name='%s'", text.c_str());
    if (shortcut != "") attributes += kStringPrintf(" shortcut='%s'", shortcut.c_str());
    return attributes;
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::setXMLAttributes ( const std::string & xml )
{
    std::string shortcutString = kXMLReadNamedAttribute(xml, "shortcut");
    if (shortcutString != "") setShortcut(shortcutString);
}

// --------------------------------------------------------------------------------------------------------
std::string KMenuItem::getXML ( int depth ) const
{
    return kXMLTag("Item", getXMLAttributes(), depth);
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::setXML ( std::string & xml )
{
    std::string attributes;
    kXMLParseNamedOpenTag(xml, "Item", &attributes);
    setXMLAttributes(attributes);
}

// --------------------------------------------------------------------------------------------------------
std::string KMenuItem::getText () const
{
    std::string itemText = KButton::getText();
    if (KMenu::show_shortcuts && shortcut != "") itemText += " " + shortcut;
    return itemText;
}

// --------------------------------------------------------------------------------------------------------
KSize KMenuItem::getSize () const
{
    int addWidth = 10;
    if (KMenu::show_shortcuts) 
    {
        addWidth += kKeyGetDisplayWidthForKeySequence(shortcut) + 5;
    }
    return KSize(kStringWidth(KButton::getText(), flags[KDL_LABEL_FLAG_LARGE_FONT]) + addWidth, KDL_MENU_DEFAULT_ITEM_HEIGHT);
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::renderShortCut ()
{
    if (shortcut == "") return;
    
    glColor4f(0.5, 0.5, 1.0, 1.0);
    
    KPosition startPos(kStringWidth(text + " ", flags[KDL_LABEL_FLAG_LARGE_FONT]), 0);
    
    kKeyDisplayKeySequence(shortcut, startPos);
}

// --------------------------------------------------------------------------------------------------------
void KMenuItem::render ()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);
    
    if (picked) 
    {
        glColor4f(1.0, 1.0, 1.0, 1.0);
    }
    else if (getFGColor()) 
    {
        getFGColor()->glColor();
    }
    
    KWidget::render();
    
    glPushMatrix();
    flags[KDL_LABEL_FLAG_LARGE_FONT] ? glTranslatef(5.0, -15.0, 0.0) : glTranslatef(3.0, -10.0, 0.0);
    kDisplayString(text, KPosition(0, 0), flags[KDL_LABEL_FLAG_LARGE_FONT]);
    
    if (KMenu::show_shortcuts) 
    {
        renderShortCut();
    }
    
    glPopMatrix();
    glPopAttrib();
}

