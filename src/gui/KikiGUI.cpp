/*
 *  KikiGUI.cpp
 */

#include "KikiGUI.h"
#include "KikiController.h"
#include "KikiSound.h"
#include "KikiPython.h"

#include <KMenuWindow.h>
#include <KSubMenuItem.h>
#include <KStatusMenuItem.h>
#include <KKeyActionHandler.h>
#include <KButtonBox.h>
#include <KButton.h>
#include <KColor.h>
#include <KTools.h>
#include <KConsole.h>

// __________________________________________________________________________________________________
KikiGUI::KikiGUI () : KMenuWindow ()
{
    depth = INT_MAX-1;
}

// __________________________________________________________________________________________________
void KikiGUI::init ()
{
    KMenuItem * item;
    KMenu * fileMenu	= new KMenu();
    KMenu * viewMenu	= new KMenu();

    addMenuItem(new KSubMenuItem ("file", fileMenu));

    fileMenu->addChild(item = new KMenuItem ("quit", Controller.quit_key));
    item->addReceiverCallback(&Controller, (KCallbackPtr)&KikiController::quit );

    addMenuItem(new KSubMenuItem ("view", viewMenu));

    viewMenu->addChild(item = new KStatusMenuItem ("hide python", "show python", "META_w"));
    item->addReceiverCallback(Controller.python, (KSetBoolPtr)&KWindow::setVisibility );
    item->setProviderCallback(Controller.python, (KGetBoolPtr)&KWindow::getVisibility );
    
    viewMenu->addChild(item = new KStatusMenuItem ("hide console", "show console", "META_e"));
    item->addReceiverCallback(KConsole::getConsole(), (KSetBoolPtr)&KConsole::setVisibility );
    item->setProviderCallback(KConsole::getConsole(), (KGetBoolPtr)&KConsole::getVisibility );

    viewMenu->addChild(item = new KStatusMenuItem ("hide shortcuts", "show shortcuts", "ALT_s"));
    item->addReceiverCallback(this, (KSetBoolPtr)&KikiGUI::setShowShortCuts );
    item->setProviderCallback(this, (KGetBoolPtr)&KikiGUI::getShowShortCuts );

    viewMenu->addChild(item = new KStatusMenuItem ("hide menu", "show menu", "ALT_m"));
    item->addReceiverCallback(this, (KSetBoolPtr)&KikiGUI::setVisibility );
    item->setProviderCallback(this, (KGetBoolPtr)&KikiGUI::getVisibility );

    viewMenu->addChild(item = new KMenuItem ("save screenshot", "F1"));
    item->addReceiverCallback(&Controller, (KCallbackPtr)&KikiController::saveScreenShot );

	viewMenu->addChild(item = new KStatusMenuItem ("hide fps", "show fps", "ALT_f"));
    item->addReceiverCallback(&Controller, (KSetBoolPtr)&KikiController::setDisplayFps );
    item->setProviderCallback(&Controller, (KGetBoolPtr)&KikiController::getDisplayFps );
    
    layout();
    initializeIds();
}

// --------------------------------------------------------------------------------------------------------
void KikiGUI::layout ()
{
    widget->layout();
}

// --------------------------------------------------------------------------------------------------------
void KikiGUI::setShowShortCuts ( bool b )
{
    if (b != KMenu::show_shortcuts)
    {
        KMenu::show_shortcuts = b;
        layout();
    }
}

// --------------------------------------------------------------------------------------------------------
bool KikiGUI::getShowShortCuts () const
{
    return KMenu::show_shortcuts;
}

