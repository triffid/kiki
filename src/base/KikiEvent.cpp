/*
 *  KikiEvent.cpp
 *  kiki
 */

#include "KikiEvent.h"
#include "KikiActionObject.h"

#include <KEventHandler.h>
#include <KConsole.h>
#include <algorithm>

// --------------------------------------------------------------------------------------------------------
KikiEvent::KikiEvent ( KikiActionObject * o, const std::string & name )
{
    event_object = o;
    event_name = name;
}

// --------------------------------------------------------------------------------------------------------
KikiEvent::~KikiEvent ()
{
  actions.clear();
}

// --------------------------------------------------------------------------------------------------------
bool KikiEvent::hasAction ( KikiAction * action )
{
    return (std::find (actions.begin(), actions.end(), action) != actions.end());
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::addAction ( KikiAction * action )
{
    if (std::find (actions.begin(), actions.end(), action) == actions.end())
    {	
        actions.push_back(action);
        action->event = this;
        action->init();
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::removeAllActions ()
{
    while (actions.empty() == false)
    {
        removeAction(actions.back());
    }
}

// --------------------------------------------------------------------------------------------------------
KikiActionList KikiEvent::getActionsOfObject ( KikiActionObject * object )
{
    KikiActionList action_list;
    KikiActionList sactions(actions);
    for (KikiActionIter iter = sactions.begin(); iter != sactions.end(); iter++)
    {	
        if ((*iter)->getObject() == object)
        {
            action_list.push_back(*iter);
        }
    }
    return action_list;
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::removeActionsOfObject ( KikiActionObject * object )
{
    for (KikiActionIter iter = actions.begin(); iter != actions.end(); iter++)
    {	
        if ((*iter)->getObject() == object)
        {
            removeAction(*iter);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::removeActionWithName ( const std::string & actionName )
{
    for (KikiActionIter iter = actions.begin(); iter != actions.end(); iter++)
    {	
        if ((*iter)->getName() == actionName)
        {
            removeAction(*iter);
            return;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::removeAction ( KikiAction * action )
{
    action->event = NULL;
    
    KikiActionIter result = std::find (actions.begin(), actions.end(), action);
    if (result != actions.end())
    {	
        actions.erase (result);
    }

    result = std::find (save_actions.begin(), save_actions.end(), action);
    if (result != save_actions.end())
    {	
        save_actions.erase (result);
    }

    result = std::find (finished_actions.begin(), finished_actions.end(), action);
    if (result != finished_actions.end())
    {	
        finished_actions.erase (result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::triggerActions ()
{
    time = KEventHandler::getTime ();
    
    save_actions = KikiActionList (actions);

    while (save_actions.empty() == false)
    {
        KikiAction * action = save_actions.back();
        action->performWithEvent (*this);
        if (save_actions.empty() == false && save_actions.back() == action)
        {
            save_actions.pop_back();
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::addFinishedAction ( KikiAction * action )
{
  finished_actions.push_back(action);
}

// --------------------------------------------------------------------------------------------------------
void KikiEvent::finishActions ()
{
	try {
		while (finished_actions.empty() == false)
		{
			KikiAction * action = finished_actions.back();
			action->finished();
			if (finished_actions.empty() == false && finished_actions.back() == action)
			{
				finished_actions.pop_back();
			}
		} 
	}
	catch (...)
	{
		//KConsole::print("!!! finishActions failed !!!");
	}
}
