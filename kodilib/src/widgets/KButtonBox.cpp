/*
 *  KButtonBox.cpp
 *  kodisein
 */

#include "KButtonBox.h"
#include "KButton.h"
#include "KConsole.h"
#include "KNotificationObject.h"

KDL_CLASS_INTROSPECTION_1 (KButtonBox, KWidgetArray)

// --------------------------------------------------------------------------------------------------------
KButtonBox::KButtonBox () : KWidgetArray ()
{
}

// --------------------------------------------------------------------------------------------------------
void KButtonBox::addButton ( KButton * button )
{  
    addChild (button);
    button->addReceiverCallback ((KObject*)this, (KSetStringPtr)&KButtonBox::buttonCallback);
}

// --------------------------------------------------------------------------------------------------------
void KButtonBox::buttonCallback ( const std::string & buttonText )
{
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        if (((KButton*)*iter)->getText() != buttonText)
        {
            ((KButton*)*iter)->deactivate();
        } 
        iter++;
    }
}


