/*
 *  KikiMutant.cpp
 *  kiki
 */

#include "KikiMutant.h"
#include "KikiWorld.h"
#include "KikiPlayer.h"
#include "KikiSound.h"
#include "KikiBullet.h"
#include "KikiController.h"
#include "KikiAction.h"

#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiMutant, KikiBot )
KIKI_OBJECT_VALUES_2 		( KikiMutant, true, dead, tire )

// __________________________________________________________________________________________________
KikiMutant::KikiMutant () : KikiBot()
{                                
    move = true;
}

// __________________________________________________________________________________________________
void KikiMutant::die ()
{
    Controller.sound->playSound (KikiSound::BOT_DEATH);
    KikiBot::die();
    getActionWithId (ACTION_FALL)->setDuration(40);
}

// __________________________________________________________________________________________________
void KikiMutant::moveBot ()
{
    bool changeOrientation = (RANDOM < 0.3);
    bool changeJumpMode    = (RANDOM < 0.3);
    bool changeDirection   = (RANDOM < 0.3);
    push    	   	   = (RANDOM < 0.1);
    bool fire              = (RANDOM < 0.5);
    bool noop              = (RANDOM < 0.05);
     
    if (changeDirection)
    {
        dir_sgn = (RANDOM < 0.3) ? -1 : 1;
    }

    if (changeJumpMode)
    {
        if (jump || dir_sgn > 0) // prevent jumping backwards
        {
            jump = !jump;
        }
    }

    KikiPos forwardPos = position + getDir();
        
    if (fire && Controller.world->isValidPos(forwardPos))
    {
        KikiBullet::shootFromBot(this);
    }
        
    if (changeOrientation)
    {
        if (RANDOM < 0.5) 
        {
            rotate_action = getActionWithId (KikiBot::ACTION_TURN_LEFT);
        }
        else			   
        {
            rotate_action = getActionWithId (KikiBot::ACTION_TURN_RIGHT);
        }
        Controller.timer_event->addAction (rotate_action);
        
        return;
    }
    
    if (noop)
    {
        startTimedAction (getActionWithId (ACTION_NOOP), 666);
        return;
    }
    
    KikiBot::moveBot();
}

