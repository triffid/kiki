/*
 *  KikiAction.cpp
 *  kiki
 */

#include "KikiAction.h"
#include "KikiEvent.h"
#include "KikiObject.h"
#include "KikiController.h"

#include <KConsole.h>

// --------------------------------------------------------------------------------------------------------
KikiAction::KikiAction ( KikiActionObject * o, int i, const std::string & n, int d, int m ) 
{ 
    action_object	= o;
    action_name 	= n;
    action_id		= i;
    mode		= m;
    duration		= d;
    event		= NULL;
    
    reset();
}

// --------------------------------------------------------------------------------------------------------
KikiAction::KikiAction ( KikiActionObject * o, int d, int m ) 
{ 
    action_object 	= o;
    action_id		= 0;
    mode		= m;
    duration		= d;
    event		= NULL;

    reset();
}

// --------------------------------------------------------------------------------------------------------
KikiAction::~KikiAction ()
{
    if (event) event->removeAction(this);
    if (action_object) action_object->removeAction(this);
}

// --------------------------------------------------------------------------------------------------------
void KikiAction::init ()    { action_object->initAction (this); }
// --------------------------------------------------------------------------------------------------------
void KikiAction::perform () { action_object->performAction (this); }
// --------------------------------------------------------------------------------------------------------
void KikiAction::finish ()  { action_object->finishAction (this); }
// --------------------------------------------------------------------------------------------------------
void KikiAction::finished () 
{ 
    action_object->actionFinished(this);

    if (current == getDuration()) // if keepRest wasn't called -> reset start and current values
    {
        reset();
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiAction::reset ()
{
    start   = 0;
    rest    = 0;
    last    = 0;
    current = 0;
}

// --------------------------------------------------------------------------------------------------------
void KikiAction::takeRest ( KikiAction * action )
{
    current = action->rest;
    start   = action->start;
    last    = 0;
    rest    = 0;
}

// --------------------------------------------------------------------------------------------------------
void KikiAction::keepRest ()
{
    if (rest != 0)
    {
        current = rest;
        rest = 0;
    }
}

// --------------------------------------------------------------------------------------------------------
float KikiAction::getRelativeTime ()
{ 
    return current / (float)getDuration(); 
}
 
// --------------------------------------------------------------------------------------------------------
int KikiAction::getDuration () const
{
    return Controller.mapMsTime(duration);
}

// --------------------------------------------------------------------------------------------------------
void KikiAction::performWithEvent ( KikiEvent & event )
{
    int eventTime = event.getTime();

    if (start == 0)
    {
        start   = eventTime;
        current = 0;
        rest    = 0;
        last	= 0;
        if (duration == 0 && mode == ONCE)
        {
            event.removeAction (this);
        }

        perform ();
        
        last = current;
        
        if (duration == 0 && mode == ONCE)
        {
            finished();
        }
    }
    else
    {
        int currentDiff = eventTime - start;
        
        if (currentDiff >= getDuration())
        {
            current = getDuration();

            start  += current;
            rest    = eventTime - start;
            perform ();
            last    = 0;
            
            if (mode == CONTINUOUS)
            {	
                current = rest;
                return;
            }
            if (mode == ONCE)
            {
                event.removeAction (this);
            }
            
            finish ();

            if (mode == REPEAT)
            {
                if (current == getDuration()) // if keepRest wasn't called -> reset start and current values
                {
                    reset();
                }
                return;
            }
            
            event.addFinishedAction (this);
        }
        else
        {
            current = currentDiff;
            perform ();
            last    = current;
        }
    }
}

