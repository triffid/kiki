/*
 *  KMessagePanel.cpp
 *  kodisein
 */

#include "KMessagePanel.h"
#include "KProjection.h"
#include "KEventHandler.h"
#include "KTrash.h"
#include "KLabel.h"

// --------------------------------------------------------------------------------------------------------
KMessagePanel::KMessagePanel ( const std::string & title, const std::string & message ) : 
    KWindow ( KDL_WINDOW_FEATURES_WIDGET | KDL_WINDOW_FEATURES_BUTTON_WIDGET | 
              KDL_WINDOW_FEATURES_CLOSE_BUTTON | KDL_WINDOW_FEATURES_PROJECTION )
{
    KLabel * label;
    label = new KLabel(title);    
    button_widget->addChild(label);
    
    KWidgetArray * widgetArray = new KWidgetArray ();
    widgetArray->flags[KDL_WIDGET_FLAG_FRAMED] = true;
    widgetArray->setFrameSpacing(10);
    widget->addChild(widgetArray);
    
    label = new KLabel(message);
    widgetArray->addChild(label);
    
    KSize screenSize = KEventHandler::getScreenSize();
    KSize widgetSize = widget->layout();
    
    // center on screen
    setPosition(KPosition((screenSize.w/2 - projection->getViewportScreenPos().x - widgetSize.w/2), 
                         -(screenSize.h/2 - projection->getViewportTopBorder()   - widgetSize.h/2)));
                         
    setDepth(INT_MAX);
    KEventHandler::addPickHandler(this);
    widget->show();
}

// --------------------------------------------------------------------------------------------------------
void KMessagePanel::displayMessage ( const std::string & title, const std::string & message )
{
    new KMessagePanel(title, message);
}

// --------------------------------------------------------------------------------------------------------
void KMessagePanel::close ()
{
    // there could be notifications pending -> delay destruction
    hide();
    KTrash::addObject((KObject*)this);
    KEventHandler::removePickHandler(this);
}
