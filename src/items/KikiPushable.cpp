/*
 *  KikiPushable.cpp
 *  kiki
 */

#include "KikiPushable.h"
#include "KikiWorld.h"
#include "KikiSound.h"
#include "KikiPlayer.h"
#include "KikiBomb.h"

#include <KConsole.h>
#include <KDisplayTools.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiPushable, KikiObject )
KIKI_OBJECT_VALUES 		( KikiPushable, true )

// __________________________________________________________________________________________________
KikiPushable::KikiPushable () : KikiObject ()
{                            
    landing_sound = KikiSound::STONE_LAND;
    pushing_sound = KikiSound::STONE_MOVE;
    pusher 	  = NULL;
    direction     = KVector();
    
    addAction (new KikiAction (this, ACTION_PUSH, "push"));
    addAction (new KikiAction (this, ACTION_FALL, "fall", 40));
}

// __________________________________________________________________________________________________
void KikiPushable::pushedByObjectInDirection ( KikiObject * object, const KVector & dir, int duration )
{
    KikiAction * pushAction = getActionWithId (ACTION_PUSH);
    
    pusher      = object;
    move_action = pushAction;
    direction   = dir;
    //KConsole::printf ("pushedByObjectInDirection [%f %f %f]", direction[X], direction[Y], direction[Z]);
    
    pushAction->setDuration (Controller.unmapMsTime (duration));
    Controller.timer_event->addAction (pushAction);
}

// __________________________________________________________________________________________________
void KikiPushable::initAction ( KikiAction * action )
{
    switch (action->getId())
    {
    	case ACTION_PUSH:
        
            Controller.sound->playSound (pushing_sound);
            
        case ACTION_FALL:

            //KConsole::printf ("KikiPushable::initAction object will move to pos [%f %f %f]", 
            //(position + direction)[0], (position + direction)[1], (position + direction)[2]);
        
            Controller.world->objectWillMoveToPos (this, position + direction, action->getDuration());
    }
}

// __________________________________________________________________________________________________
void KikiPushable::performAction ( KikiAction * action )
{
    switch (action->getId())
    {
    	case ACTION_PUSH:
        case ACTION_FALL:
        
            setCurrentPosition (position + action->getRelativeTime() * direction);
    }
}

// __________________________________________________________________________________________________
void KikiPushable::finishAction ( KikiAction * action )
{
    switch (action->getId())
    {
    	case ACTION_PUSH:
        case ACTION_FALL:
        
            move_action = NULL;
        
            Controller.world->objectMovedFromPos (this, position); // update world position
                                                    
            setPosition (current_position);
    }
}

// __________________________________________________________________________________________________
void KikiPushable::actionFinished ( KikiAction * action )
{    
    int actionId = action->getId();
    
    if (actionId == ACTION_PUSH || actionId == ACTION_FALL)
    {
        KVector gravityDir = direction;
        
        if (actionId == ACTION_PUSH)
        {
            if (pusher->getClassId() >= KikiBot::classId())
            {
                gravityDir = ((KikiBot*)pusher)->getDown();
            }
            else if (pusher->getClassId() >= KikiBomb::classId())
            {
                if (getClassId() >= KikiBot::classId())
                {
                    if (direction == (KVector)((KikiBot*)this)->getUp())
                    {
                        // bots don't fall through bomb splitter
                        direction.reset();
                        return;
                    }
                    else
                    {
                        gravityDir = ((KikiBot*)this)->getDown(); // bots pushed by bombs fall down
                    }
                }
                else
                {	
                    direction.reset();
                    return; // objects pushed by bombs don't fall
                }
            }
        }
        
        if (Controller.world->isUnoccupiedPos (position + gravityDir))
        {
            direction = gravityDir;
            move_action = getActionWithId (ACTION_FALL);
            Controller.timer_event->addAction (move_action);
        }
        else
        {
            direction.reset ();
            Controller.sound->playSoundAtPos (landing_sound, position);
        }
    }
}


