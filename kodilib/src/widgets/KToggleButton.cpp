/*
 *  KToggleButton.cpp
 *  kodisein
 */

#include "KToggleButton.h"
#include "KColor.h"

KDL_CLASS_INTROSPECTION_1 (KToggleButton, KButton)

// --------------------------------------------------------------------------------------------------------
KToggleButton::KToggleButton () : KButton ()
{
    size.w	= 11;
    size.h	= 11;
}

// --------------------------------------------------------------------------------------------------------
void KToggleButton::setPicked ( bool p )
{ 
    if (p)
    {
        if (picked)	deactivate();
        else		activate();
    }
}

// --------------------------------------------------------------------------------------------------------
void KToggleButton::render ()
{
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);

    if (getFGColor()) getFGColor()->glColor();

    KLabel::render();
    
    if (picked)
    {
        glBegin(GL_LINES);
            glVertex3f(0.0,       0.0, 0.0);
            glVertex3f(size.w, -size.h, 0.0);
            glVertex3f(0.0,   -size.h, 0.0);    
            glVertex3f(size.w,     0.0, 0.0);
        glEnd();
    }
    glPopAttrib();
}


