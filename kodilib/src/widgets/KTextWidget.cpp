/*
 *  KTextWidget.cpp
 *  kodisein
 */

#include "KTextWidget.h"
#include "KConsole.h"
#include "KStringTools.h"

KDL_CLASS_INTROSPECTION_1 (KTextWidget, KLabel)

// --------------------------------------------------------------------------------------------------------
KTextWidget::KTextWidget () : KLabel ()
{  
    setLargeFont(false);
    flags.resize(KDL_TEXTWIDGET_FLAG_END);
    flags[KDL_WIDGET_FLAG_FRAMED]		= true;
    flags[KDL_WIDGET_FLAG_FIXED_SIZE]		= true;
    flags[KDL_TEXTWIDGET_FLAG_AUTO_SCROLLDOWN]	= false; 
    current_row 			= INT_MAX;
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::setLabelText ()
{
    int lineIndex = kStringRows(full_text) - getTextRows();
    if ((int)current_row < lineIndex) lineIndex = current_row;
    lineIndex = kMax(lineIndex, 0);
    unsigned int startPos = lineIndex ? kStringNthCharPos(full_text, lineIndex, '\n')+1 : 0;
    unsigned int endPos   = kStringNthCharPos(full_text, lineIndex + getTextRows(), '\n')+1;
    setText(full_text.substr(startPos, (endPos - startPos)));
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::clear ()
{
    setText(""); full_text = ""; // current_row = 0;
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollRelative ( float value )
{
    current_row = kMax(0, (int)(value * ((int)kStringRows(full_text) - getTextRows())));
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollToTop ()
{
    current_row = 0;
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollToBottom ()
{
    current_row = flags[KDL_TEXTWIDGET_FLAG_AUTO_SCROLLDOWN] ? INT_MAX : kStringRows(full_text);
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollLineUp ()
{
    current_row = kMax(kMin((int)current_row, (int)(kStringRows(full_text) - getTextRows()))-1, 0);
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollPageUp ()
{
    current_row = kMax (kMin ((int)current_row, (int)(kStringRows(full_text) - getTextRows()) )-
                            (int)(getTextRows()-2), 0);
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollLineDown ()
{
    current_row++;
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::scrollPageDown ()
{
    current_row += kMax(0, getTextRows()-2);
    setLabelText();
}

// --------------------------------------------------------------------------------------------------------
void KTextWidget::printf ( const char * fmt ... )
{
    va_list argList;
    va_start(argList, fmt);
    std::string newText = kStringPrintf(std::string(fmt), &argList);
    va_end(argList);
    
    full_text += newText;
    setLabelText();
}


