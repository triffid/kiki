/*
 *  KikiActionObject.cpp
 *  kiki
 */

#include "KikiActionObject.h"
#include "KikiController.h"

#include <KConsole.h>
#include <algorithm>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION 	(KikiActionObject)

// --------------------------------------------------------------------------------------------------------
KikiActionObject::~KikiActionObject ()
{
    deleteActions();
    while (events.empty() == false)
    {	
        delete events.back();
        events.pop_back();
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiActionObject::deleteActions ()
{ 
    while (actions.empty() == false)
    {	
        delete actions.back(); // will remove action from actions
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiActionObject::addAction ( KikiAction * action )
{
    if (std::find (actions.begin(), actions.end(), action) == actions.end())
    {	
        actions.push_back(action);
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiActionObject::startTimer ( int duration, int mode )
{
    KikiAction * action = new KikiAction (this, 0, "timer", duration, mode);
    actions.push_back(action);
    Controller.timer_event->addAction (action);
}

// --------------------------------------------------------------------------------------------------------
void KikiActionObject::stopAction ( KikiAction * action )
{
    Controller.timer_event->removeAction(action);
}

// --------------------------------------------------------------------------------------------------------
void KikiActionObject::startTimedAction ( KikiAction * action, int duration )
{
    if (duration >= 0)
    {
        action->setDuration(duration);
    }
    Controller.timer_event->addAction (action);
}

// --------------------------------------------------------------------------------------------------------
void KikiActionObject::removeAction ( KikiAction * action )
{
    KikiActionList::iterator result = std::find (actions.begin(), actions.end(), action);
    if (result != actions.end())
    {	
        actions.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
KikiAction * KikiActionObject::getActionWithId ( int actionId )
{
    if (actionId < (int)actions.size() && actions[actionId]->getId() == actionId) 
    {
        return actions[actionId];
    }

    // to be deleted...
    KConsole::printf ("[WARNING] KikiActionObject::getActionWithId %d [%d actions]'", actionId, (int)actions.size());
    
    for (KikiActionIter iter = actions.begin(); iter != actions.end(); iter++)
    {
        if ((*iter)->getId() == actionId)
        {
            return *iter;
        }
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KikiAction * KikiActionObject::getActionWithName ( const std::string & name )
{
    KikiActionList::iterator actionIter = actions.begin();
    while (actionIter != actions.end())
    {
        if ((*actionIter)->getName() == name)
        {
            return *actionIter;
        }
        actionIter++;
    }
    
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
int KikiActionObject::addEventWithName ( const std::string & eventName )
{
    if (getEventWithName (eventName)) // to be removed
    {
        KConsole::printError (kStringPrintf ("KikiActionObject::addEventWithName '%s' already in use!",
                                                                                eventName.c_str()));
        return -1; // shouldn't happen anyway :-)
    }
    events.push_back (new KikiEvent (this, eventName));
    return events.size()-1;
}

// --------------------------------------------------------------------------------------------------------
KikiEvent * KikiActionObject::getEventWithId ( int eventId )
{
    return events[eventId];
}

// --------------------------------------------------------------------------------------------------------
KikiEvent * KikiActionObject::getEventWithName ( const std::string & name )
{
    
    for (KikiEventIter iter = events.begin(); iter != events.end(); iter++)
    {
        if ((*iter)->getName() == name)
        {
            return *iter;
        }
    }
    
    return NULL;
}

