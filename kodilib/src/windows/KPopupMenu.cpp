/*
 *  KPopupMenu.cpp
 *  kodisein
 */

#include "KPopupMenu.h"
#include "KEventHandler.h"
#include "KTrash.h"
#include "KConsole.h"

#include "KLabel.h"

KDL_CLASS_INTROSPECTION_1 (KPopupMenu, KMenuWindow)

// --------------------------------------------------------------------------------------------------------
KPopupMenu::KPopupMenu () : KMenuWindow ()
{
    widget->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;

    setDepth(INT_MAX);
}

// --------------------------------------------------------------------------------------------------------
void KPopupMenu::show ()
{
    KEventHandler::addPickHandler(this);
    old_release_handler = KEventHandler::release_handler;
    KEventHandler::release_handler = this;
     
    flags[KDL_PICKHANDLER_FLAG_MOTION_FOCUS] = true;
    picked_pickable = pickables[0];
    pickables[0]->setPicked(true);
    widget->show();
}

// --------------------------------------------------------------------------------------------------------
void KPopupMenu::release ( const KMouseEvent & mouseEvent )
{
    KEventHandler::release_handler = old_release_handler;
    KEventHandler::removePickHandler(this);
    KMenuWindow::release( mouseEvent );
    ((KMenu*)widget)->hide();
}

// --------------------------------------------------------------------------------------------------------
void KPopupMenu::close ()
{
    // there could be notifications pending -> delay destruction
    hide();
    KTrash::addObject((KObject*)this);
}
