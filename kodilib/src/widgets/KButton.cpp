/*
 *  KButton.cpp
 *  kodisein
 */

#include "KButton.h"
#include "KConsole.h"
#include "KColor.h"

KDL_CLASS_INTROSPECTION_2 (KButton, KLabel, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KButton::KButton ( const std::string & n ) : KLabel(n)
{
    flags[KDL_WIDGET_FLAG_FIXED_SIZE]	= false;
    flags[KDL_WIDGET_FLAG_FRAMED]	= true;
}

// --------------------------------------------------------------------------------------------------------
void KButton::setPicked ( bool p )
{ 
    if (p) activate();
    //picked = p;
}
 
// --------------------------------------------------------------------------------------------------------
void KButton::activate()		
{
    picked = true;
    notifyReceivers();
    notifyReceivers(true);
    notifyReceivers(text);
}

// --------------------------------------------------------------------------------------------------------
void KButton::deactivate ()
{
    picked = false;
    notifyReceivers(false);
}

// --------------------------------------------------------------------------------------------------------
KColor * KButton::getFGColor () const
{ 
    if (fg_color) return fg_color;
    if (parent) return parent->getFGColor();
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KColor * KButton::getBGColor () const
{ 
    if (bg_color) return bg_color;
    if (parent) return parent->getBGColor();
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KButton::render ()
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
    KLabel::render();
    glPopAttrib();
}



