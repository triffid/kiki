/*
 *  KLabel.cpp
 *  kodisein
 */

#include "KLabel.h"
#include "KConsole.h"
#include "KTools.h"
#include "KStringTools.h"

KDL_CLASS_INTROSPECTION_1 (KLabel, KWidget)

// --------------------------------------------------------------------------------------------------------
KLabel::KLabel ( const std::string & n ) : KWidget ()
{  
    flags.resize(KDL_LABEL_FLAG_END);
    flags[KDL_WIDGET_FLAG_FIXED_SIZE]  = false;
    setLargeFont(false);
    setText(n);
}

// --------------------------------------------------------------------------------------------------------
void KLabel::updateTextSize ()
{
    if (flags[KDL_WIDGET_FLAG_FIXED_SIZE])
    {
        kStringCropRows (text, getTextRows());
        kStringCropCols (text, getTextCols());
    }
    else
    {
        size.w = kStringWidth (text, flags[KDL_LABEL_FLAG_LARGE_FONT]) + 10;
        size.h = kStringHeight(text, flags[KDL_LABEL_FLAG_LARGE_FONT]) + 5;
    }
}

// --------------------------------------------------------------------------------------------------------
void KLabel::setText( const std::string & t )
{
    text = t;
    update();
}

// --------------------------------------------------------------------------------------------------------
void KLabel::update ()
{
    updateTextSize();
    
    if (flags[KDL_WIDGET_FLAG_FIXED_SIZE] == false) 
    {
        getRootWidget()->layout();
    }
}

// --------------------------------------------------------------------------------------------------------
void KLabel::setSize ( KSize newSize )
{   
    KSize maxSize(kMax(newSize.w, (int)getColumnWidth() + 10), kMax(newSize.h, (int)getRowHeight() + 5));
    KWidget::setSize(maxSize);
    updateTextSize();
}

// --------------------------------------------------------------------------------------------------------
void KLabel::setLargeFont ( bool lf )
{  
    flags[KDL_LABEL_FLAG_LARGE_FONT] = lf;
    if (flags[KDL_WIDGET_FLAG_FIXED_SIZE] == false) 
    {
        size.w = kStringWidth(text, flags[KDL_LABEL_FLAG_LARGE_FONT]) + 10;
    }
}

// --------------------------------------------------------------------------------------------------------
void KLabel::setTextSize ( KSize newSize )
{
    flags[KDL_WIDGET_FLAG_FIXED_SIZE] = true;
    setSize (KSize(getColumnWidth() * newSize.w + 5, getRowHeight() * newSize.h + 5));
}

// --------------------------------------------------------------------------------------------------------
void KLabel::render ()
{
    KWidget::render();
    
    glPushMatrix();
    flags[KDL_LABEL_FLAG_LARGE_FONT] ? glTranslatef(5.0, -16.0, 0.0) : glTranslatef(3.0, -11.0, 0.0);
    kDisplayString(getText(), KPosition(0,0), flags[KDL_LABEL_FLAG_LARGE_FONT]);
    glPopMatrix();
}


