/*
 *  KSliderButton.cpp
 *  kodisein
 */

#include "KSliderButton.h"
#include "KEventHandler.h"
#include "KColor.h"

KDL_CLASS_INTROSPECTION_1 (KSliderButton, KButton)

// --------------------------------------------------------------------------------------------------------
KSliderButton::KSliderButton () : KButton ()
{
    flags[KDL_WIDGET_FLAG_FIXED_SIZE]	= true;
    flags[KDL_WIDGET_FLAG_FRAMED]	= true;
    min_size = KSize(14,14);
    size = min_size;
}

// --------------------------------------------------------------------------------------------------------
void KSliderButton::moved ( const KMouseEvent & mouseEvent )
{
    setPosition (getPosition() + (KVector)mouseEvent.delta);
    notifyReceivers ();
}

// --------------------------------------------------------------------------------------------------------
void KSliderButton::render ()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);
    if (getFGColor()) 
    {
        getFGColor()->glColor();
    }
    KWidget::render();
    glPopAttrib();
}

