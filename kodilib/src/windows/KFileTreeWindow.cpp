/*
 *  KFileTreeWindow.cpp
 *  kodisein
 */

#include "KFileTreeWindow.h"
#include "KEventHandler.h"
#include "KProjection.h"
#include "KFileNameField.h"
#include "KButton.h"
#include "KConsole.h"
#include "KFileTools.h"

KDL_CLASS_INTROSPECTION_2 (KFileTreeWindow, KWindow, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KFileTreeWindow::KFileTreeWindow () : KWindow ( KDL_WINDOW_FEATURES_DEFAULT_FEATURES | KDL_WINDOW_FEATURES_RESIZE_HANDLE )
{
    tree_widget = new KFileTreeWidget();
    tree_widget->setSize    (KSize(200,150));
    tree_widget->setMinSize (KSize(200,150));
    
    depth = INT_MAX/2;
    tree_widget->setDepth(depth+1);
    
    tree_widget->KWidget::flags[KDL_WIDGET_FLAG_FRAMED] = true;
    
    KWidgetArray * widgetArray = new KWidgetArray();
    widgetArray->setFrameSpacing(0);

    dirname_widget = new KLabel("");
    dirname_widget->flags[KDL_WIDGET_FLAG_FRAMED] = false;
    dirname_widget->setTextCols(20);
    dirname_widget->setMinSize(dirname_widget->getSize());
    dirname_widget->flags[KDL_WIDGET_FLAG_FILL_X] = true;
    button_widget->addChild(dirname_widget);
    
    filename_widget = new KFileNameField("");
    filename_widget->setTextCols(20);
    filename_widget->setMinSize(filename_widget->getSize());
    filename_widget->KWidget::flags[KDL_FILENAMEFIELD_FLAG_OPEN_FILE_MODE] = true;
    filename_widget->KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    filename_widget->addReceiverCallback((KWidget*)tree_widget,
        (KSetStringPtr)(void (KWidget::*)(const std::string &))&KFileTreeWidget::setCurrentDir,
                                        KDL_NOTIFICATION_TYPE_CURRENT_DIRECTORY_CHANGED);
    filename_widget->addReceiverCallback(dirname_widget, (KSetStringPtr)&KLabel::setText,
                                        KDL_NOTIFICATION_TYPE_CURRENT_DIRECTORY_CHANGED);
    filename_widget->addReceiverCallback(this, (KCallbackPtr)&KFileTreeWindow::notify);
    
    KButton * okButton = new KButton ("ok");
    
    okButton->addReceiverCallback(this, (KCallbackPtr)&KFileTreeWindow::notify);

    tree_widget->addReceiverCallback(filename_widget, (KSetStringPtr)&KTextField::setText, 
                                        KDL_NOTIFICATION_TYPE_SELECT_NODE);
    tree_widget->addReceiverCallback(filename_widget, (KSetStringPtr)&KFileNameField::setCurrentDirPath, 
                                        KDL_NOTIFICATION_TYPE_OPEN_DIRECTORY);
    tree_widget->addReceiverCallback(dirname_widget, (KSetStringPtr)&KTextField::setText, 
                                        KDL_NOTIFICATION_TYPE_OPEN_DIRECTORY);
    tree_widget->addReceiverCallback(okButton, (KCallbackPtr)&KButton::activate);
    
    widget->addChild(tree_widget);
    widget->addChild(widgetArray);
    
    widgetArray->addChild(filename_widget);
    widgetArray->addChild(okButton);

    addPickable(filename_widget);
    addPickable(okButton);
    
    widget->layout();
    widget->hide();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWindow::displayPickables ( int )
{
    tree_widget->hide();
    widget->display();
    tree_widget->show();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWindow::notify () 
{
    notifyReceivers(tree_widget->getCurrentDir() + "/" + filename_widget->getText());
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWindow::show ()
{
    tree_widget->setCurrentDir(".");

    KEventHandler::addPickHandler(tree_widget);
    KEventHandler::setProjectionHandler(tree_widget);

    dirname_widget->setText(tree_widget->getCurrentDir());
    KWindow::show();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWindow::hide ()
{
    KWindow::hide();
    removeAllReceivers();
    KEventHandler::removePickHandler(tree_widget);
    KEventHandler::removeProjectionHandler(tree_widget);
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWindow::relayout ( const KSize & newSize )
{
    KWindow::relayout(newSize);
    dirname_widget->setText(tree_widget->getCurrentDir());
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWindow::setOpenFileMode ( bool openFileMode )
{	
    filename_widget->KWidget::flags[KDL_FILENAMEFIELD_FLAG_OPEN_FILE_MODE] = openFileMode;
}

