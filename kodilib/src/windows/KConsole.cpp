/*
 *  KConsole.cpp
 *  kodisein
 */

#include "KConsole.h"
#include "KIconButton.h"
#include "KTextWidget.h"
#include "KScrollBar.h"
#include "KMessagePanel.h"
#include "KProjection.h"
#include "KColor.h"

#include <SDL.h>

#define K_INCLUDE_GLU
#include "KIncludeTools.h"

KDL_CLASS_INTROSPECTION_1 (KConsole, KWindow)

KConsole * KConsole::console = NULL;

// --------------------------------------------------------------------------------------------------------
KConsole::KConsole () : KWindow ()
{
    depth 	= -INT_MAX+1;
    text_widget = new KTextWidget();
    
    text_widget->setTextSize(KSize(20,1));
    text_widget->setMinSize(text_widget->getSize());
    text_widget->flags[KDL_WIDGET_FLAG_FILL_X] = true;
    text_widget->flags[KDL_WIDGET_FLAG_FILL_Y] = true;
    text_widget->flags[KDL_TEXTWIDGET_FLAG_AUTO_SCROLLDOWN] = true; 

    // ................................................................. scrolled text array
    KWidgetArray * scrolledText = new KWidgetArray();
    scrolledText->setFrameSpacing	(0);
    scrolledText->setChildSpacing	(2);
    
    // ................................................................. scrollbar
    scroll_bar = new KScrollBar(this);
    scroll_bar->addReceiverCallback(text_widget, (KSetFloatPtr)&KTextWidget::scrollRelative);
    scroll_bar->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollLineDown,
                                            KDL_NOTIFICATION_TYPE_SCROLL_LINE_DOWN);
    scroll_bar->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollLineUp,
                                            KDL_NOTIFICATION_TYPE_SCROLL_LINE_UP);
    scroll_bar->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollPageDown,
                                            KDL_NOTIFICATION_TYPE_SCROLL_PAGE_DOWN);
    scroll_bar->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollPageUp,
                                            KDL_NOTIFICATION_TYPE_SCROLL_PAGE_UP);
    
    // insert into widget array
    scrolledText->addChild(text_widget);
    scrolledText->addChild(scroll_bar);
    
    // ................................................................. buttons
    KButton * button;
    button = new KIconButton(KDL_ICONBUTTON_CLEAR);
    button->addReceiverCallback(this, (KCallbackPtr)&KConsole::clear);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(KDL_ICONBUTTON_TOP);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollToTop);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(KDL_ICONBUTTON_BOTTOM);
    button->addReceiverCallback(text_widget, (KCallbackPtr)&KTextWidget::scrollToBottom);
    button_widget->addChild(button);
    addPickable(button);

    widget->addChild(scrolledText);
    widget->layout();
    widget->hide();        
}

// --------------------------------------------------------------------------------------------------------
void KConsole::create ()
{
    if (console == NULL)
    {
        console = new KConsole();
    }
}
            
// --------------------------------------------------------------------------------------------------------
void KConsole::clear()
{ 
    text_widget->clear();
    scroll_bar->setUnits(0, text_widget->getTextRows(), 0);
}

// --------------------------------------------------------------------------------------------------------
void KConsole::checkGLError ( const std::string & msg )
{ 
    int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        KConsole::printf("[GL_ERROR] %s %s", gluErrorString(error), msg.c_str());
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::printString ( const std::string & str )
{
    if (console)
    {
        console->text_widget->print(str);
        console->scroll_bar->setUnits( console->text_widget->getCurrentRow(),
                                        console->text_widget->getTextRows(), 
                                        kStringRows(console->text_widget->getFullText()));
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::printError ( const std::string & str, bool panel )
{ 
    std::string errorStr = "[ERROR] ";
    errorStr += str; errorStr += "\n";
    ::printf("%s", errorStr.c_str());
    if (panel)  KMessagePanel::displayMessage("[ERROR]", str);
    if (console)
    {
        printString(errorStr);
        if (panel == false && console->isVisible() == false) 
        {
            // show console if no panel displayed
            console->show(); 
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KConsole::debugf ( bool output, const char * fmt ...)
{
    if (!output) return;
    va_list argList;
    va_start(argList,fmt);
    std::string newText = kStringPrintf(std::string(fmt), &argList); newText += "\n";
    va_end(argList);
    ::printf("%s", newText.c_str());
    printString(newText);
}

// --------------------------------------------------------------------------------------------------------
void KConsole::write ( const std::string & str )
{
    ::printf("%s", str.c_str());
    printString(str);
}

// --------------------------------------------------------------------------------------------------------
void KConsole::printf ( const char * fmt ...)
{
    va_list argList;
    va_start(argList,fmt);
    std::string newText = kStringPrintf(std::string(fmt), &argList); newText += "\n";
    va_end(argList);
    ::printf("%s", newText.c_str());
    printString (newText);
}

// --------------------------------------------------------------------------------------------------------
void KConsole::relayout ( const KSize & newSize )
{
    KWindow::relayout(newSize);
    text_widget->setLabelText();
    scroll_bar->setUnits( text_widget->getCurrentRow(), text_widget->getTextRows(), 
                                                    kStringRows(text_widget->getFullText()));
}
