/*
 *  KikiBot.cpp
 *  kiki
 */

#include "KikiBot.h"
#include "KikiWorld.h"
#include "KikiBullet.h"
#include "KikiController.h"
#include "KikiSound.h"
#include "KikiAction.h"
#include "KikiPlayer.h"
#include "KikiBotFume.h"

#include "body.h"
#include "tire.h"

#include <KConsole.h>
#include <KDisplayTools.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#ifdef WIN32
#include <glut.h>
#include <math.h>
#else
#include <GL/glut.h>
#endif
#endif

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiBot, KikiPushable )
KIKI_OBJECT_VALUES  		( KikiBot, true )

// __________________________________________________________________________________________________
KikiBot::KikiBot () : KikiPushable ()
{                            
    left_tire_rot  	= 0.0;
    right_tire_rot 	= 0.0;
    last_fume		= 0;

    status		= new KikiBotStatus (this);
    move      		= false;
    push      		= false;
    jump      		= false;
    shoot		= false;
    jump_once 		= false;
    
    spiked		= false;
    died		= false;
    
    move_action   	= NULL;
    rotate_action 	= NULL;
    
    dir_sgn 		= 1.0;
    
    addAction (new KikiAction (this, ACTION_NOOP, 	 	"noop",			0));
    addAction (new KikiAction (this, ACTION_FORWARD, 	 	"move forward",		200));
    addAction (new KikiAction (this, ACTION_CLIMB_UP,	 	"climb up",		200));
    addAction (new KikiAction (this, ACTION_CLIMB_DOWN, 	"climb down",		500));
    addAction (new KikiAction (this, ACTION_TURN_LEFT,  	"turn left",		200));
    addAction (new KikiAction (this, ACTION_TURN_RIGHT,		"turn right",		200));
    addAction (new KikiAction (this, ACTION_JUMP,		"jump",			120));
    addAction (new KikiAction (this, ACTION_JUMP_FORWARD,	"jump forward", 	200));
    addAction (new KikiAction (this, ACTION_FALL_FORWARD,	"fall forward", 	200));
    addAction (new KikiAction (this, ACTION_SHOOT,		"shoot", 		60, 												KikiAction::REPEAT));

    getActionWithId (ACTION_FALL)->setDuration (120);
    addEventWithName ("died");

    startTimedAction (getActionWithId (ACTION_NOOP), 500);
}

// __________________________________________________________________________________________________
KikiBot::~KikiBot ()
{
    delete status;
}

// __________________________________________________________________________________________________
void KikiBot::die ()
{
    Controller.timer_event->removeActionsOfObject (this);
    
    move  = false;
    jump  = false;
    shoot = false;
    push  = false;

    getEventWithName ("died")->triggerActions();
    died  = true;
}

// __________________________________________________________________________________________________
void KikiBot::reset ()
{
    left_tire_rot  	= 0.0;
    right_tire_rot 	= 0.0;
    last_fume		= 0;

    direction.reset();
    orientation.reset();
    current_orientation.reset();
    rotate_orientation.reset();
    climb_orientation.reset();
    rest_orientation.reset();

    move_action		= NULL;
    move      		= false;
    push      		= false;
    jump      		= false;
    shoot		= false;
    jump_once 		= false;
    
    spiked		= false;
    died		= false;
}

// __________________________________________________________________________________________________
void KikiBot::initAction ( KikiAction * action )
{
    KikiPos newPos (position);

    switch (action->getId())
    {
        case ACTION_NOOP: 						return;
        
    	case ACTION_FORWARD:		newPos += getDir(); 		break;
    	case ACTION_CLIMB_DOWN:		newPos += getDir() + getDown();	break;
    	case ACTION_JUMP:		newPos += getUp();		break;
    	case ACTION_JUMP_FORWARD:	newPos += getUp() + getDir();	break;
	case ACTION_FALL_FORWARD:	newPos += getDown() + getDir();	break;
    	case ACTION_FALL:		
            if (direction != KVector())
            {
                KConsole::printf ("bot push fall direction [%f %f %f]", direction[X], direction[Y], direction[Z]);
                KikiPushable::initAction (action);
                return;
            }
            else
                newPos += getDown();		
            break;
        
        default:
        
            KikiPushable::initAction (action);
            return;
    }

    if (newPos != KikiPos (position))
    {
        //KConsole::printf ("KikiBot::initAction object will move to pos [%d %d %d]", newPos.x, newPos.y, newPos.z);
        Controller.world->objectWillMoveToPos (this, newPos, action->getDuration());
    }
}

// __________________________________________________________________________________________________
void KikiBot::performAction ( KikiAction * action )
{
    int actionId   = action->getId();
    float relTime  = action->getRelativeTime();
    float dltTime  = action->getRelativeDelta();

    switch (actionId)
    {        
    	case ACTION_SHOOT:
        
            if (relTime == 0)
            {
                KikiBullet::shootFromBot (this);
            }
            
        case ACTION_NOOP: return;
        
        case ACTION_FORWARD:

            left_tire_rot  += dir_sgn * dltTime;
            right_tire_rot += dir_sgn * dltTime;
            current_position = position + relTime * getDir();
            
            return;
        
        case ACTION_JUMP:
        
            current_position = position + cos(M_PI_2 - M_PI_2 * relTime) * getUp();
            return;
                
        case ACTION_JUMP_FORWARD:
    
            left_tire_rot  += cos(M_PI_2 - M_PI_2 * dltTime);
            right_tire_rot += cos(M_PI_2 - M_PI_2 * dltTime);
            current_position = position  + (1.0 - cos(M_PI_2 * relTime)) * getDir() 
                                        + cos(M_PI_2 - M_PI_2 * relTime) * getUp();
            return;
            
        case ACTION_FALL_FORWARD:
    
            current_position = position + cos(M_PI_2 - M_PI_2 * relTime) * getDir() 
                                        + (1.0 - cos(M_PI_2 * relTime)) * getDown();
            return;

        case ACTION_FALL:
    
            if (direction != KVector())
            {
                KikiPushable::performAction (action);
                return;
            }
            current_position = position + relTime * getDown();
            return;
    
        case ACTION_CLIMB_UP:
    
            left_tire_rot  += dir_sgn * dltTime/2;
            right_tire_rot += dir_sgn * dltTime/2;
            climb_orientation = KQuaternion::rotationAroundVector(dir_sgn * relTime * -90.0, KVector(1,0,0));
            break;
        
        case ACTION_CLIMB_DOWN:
    
            left_tire_rot  += dir_sgn * dltTime;
            right_tire_rot += dir_sgn * dltTime;
            if (relTime <= 0.2)
            {
                current_position = position + (relTime/0.2)/2 * getDir();
            }
            else if (relTime >= 0.8)
            {
                climb_orientation = KQuaternion::rotationAroundVector(dir_sgn * 90.0, KVector(1,0,0));
                current_position = position + getDir() + (0.5+(relTime-0.8)/0.2/2) * getDown();
            }
            else
            {
                climb_orientation = KQuaternion::rotationAroundVector(dir_sgn * (relTime-0.2)/0.6 * 90.0, KVector(1,0,0));
                KVector rotVec = (orientation * climb_orientation).rotate(KVector(0.0, 1.0, 0.0));
                current_position = position + 0.5 * ((KVector)getDir() + (KVector)getDown() + rotVec);
            }
            break;
    
        case ACTION_TURN_LEFT:
        case ACTION_TURN_RIGHT:

            if (move_action == NULL && relTime == 0.0) // if not performing move action and start of rotation
            {
                // update orientation now, so next move action will move in desired direction
                if (actionId == ACTION_TURN_LEFT)  
                {
                    orientation *= KQuaternion::rotationAroundVector(90.0, KVector(0,1,0));
                    rest_orientation = KQuaternion::rotationAroundVector(-90.0, KVector(0,1,0));
                }
                else
                {
                    orientation *= KQuaternion::rotationAroundVector(-90.0, KVector(0,1,0));
                    rest_orientation = KQuaternion::rotationAroundVector(90.0, KVector(0,1,0));
                }
            }

            if (actionId == ACTION_TURN_LEFT)
            {
                left_tire_rot  += -dltTime;
                right_tire_rot +=  dltTime;
                rotate_orientation = KQuaternion::rotationAroundVector(relTime * 90.0, KVector(0,1,0));
            }
            else
            {
                left_tire_rot  +=  dltTime;
                right_tire_rot += -dltTime;
                rotate_orientation = KQuaternion::rotationAroundVector(relTime * -90.0, KVector(0,1,0));
            }
            break;
        
        default:
            
            KikiPushable::performAction (action);
            return;
    }
    
    current_orientation =  orientation * climb_orientation * rotate_orientation * rest_orientation;
}

// __________________________________________________________________________________________________
void KikiBot::finishAction ( KikiAction * action )
{
    int actionId = action->getId();

    if (actionId == ACTION_NOOP || actionId == ACTION_SHOOT) return;
    
    if (actionId == ACTION_PUSH) 
    {
        KikiPushable::finishAction (action);
        return;
    }
    
    if (actionId == ACTION_TURN_LEFT || actionId == ACTION_TURN_RIGHT)
    {
        rotate_action = NULL;
        
        if (move_action) // bot currently performing a move action -> store rotation in rest_orientation
        {           
            rest_orientation *= rotate_orientation;
            rotate_orientation.reset();
        }
        else
        {
            orientation *= rotate_orientation * rest_orientation; // update rotation matrix
            rotate_orientation.reset();
            rest_orientation.reset();
        }
    }
    else if (actionId < ACTION_END)
    {
        move_action = NULL;

        orientation *= climb_orientation; // update climb orientation
        climb_orientation.reset();

        if (rotate_action && actionId != ACTION_JUMP_FORWARD) // bot is currently performing a rotation ->
        {		   // take over result of rotation to prevent sliding
            if (rotate_action->getId() == ACTION_TURN_LEFT)  
            {
                orientation *= KQuaternion::rotationAroundVector(90.0, KVector(0,1,0)) * rest_orientation;
                rest_orientation = KQuaternion::rotationAroundVector(-90.0, KVector(0,1,0));
            }
            else
            {
                orientation *= KQuaternion::rotationAroundVector(-90.0, KVector(0,1,0)) * rest_orientation;
                rest_orientation = KQuaternion::rotationAroundVector(90.0, KVector(0,1,0));
            }
        }       
    
        if (actionId != ACTION_CLIMB_UP)
        {
            Controller.world->objectMovedFromPos (this, position); // update world position
            position = current_position.round();
        }
                
        if (actionId != ACTION_JUMP_FORWARD && rotate_action == NULL) // if not jumping forward
        {
            orientation *= rest_orientation; // update rotation orientation
            rest_orientation.reset();
        }
    }
}

// __________________________________________________________________________________________________
void KikiBot::actionFinished ( KikiAction * action )
{
    int actionId = action->getId();

    if (isDead())
    {	
        if (!died) die();
        
        if (actionId != ACTION_PUSH && actionId != ACTION_FALL)
        {
            // dead player may only fall, nothing else
            return;
        }
    }
    
    if (spiked)
    {
        move_action = NULL;
        startTimedAction (getActionWithId(ACTION_NOOP), 0);
        return;
    }

    if (actionId == ACTION_PUSH || direction != KVector()) 
    { 
        KikiPushable::actionFinished (action);
        return;
    }

    if (move_action) return; // action was not a move action -> return
    
    // find next action depending on type of finished action and surrounding environment
    if (actionId == ACTION_JUMP_FORWARD)
    {
        KVector forwardPos = position + getDir();
        if (Controller.world->isUnoccupiedPos (forwardPos)) 
        { // forward will be empty
            if (Controller.world->isUnoccupiedPos (forwardPos - getUp())) 
            { // below forward will also be empty
                move_action = getActionWithId (ACTION_FALL_FORWARD);
                move_action->takeRest (action);
            }
            else
            {
                move_action = getActionWithId (ACTION_FORWARD);
                Controller.sound->playSoundAtPos (KikiSound::BOT_LAND, getPos(), 0.25);
            }
        }
        else // forward will not be empty
        {
            if (Controller.world->isUnoccupiedPos (position - getUp())) // below is empty
            {
                move_action = getActionWithId (ACTION_CLIMB_UP);
                Controller.sound->playSoundAtPos (KikiSound::BOT_LAND, getPos(), 0.5);
            }
        }
    }
    else if (Controller.world->isUnoccupiedPos (position - getUp())) // below will be empty
    {
        if (move) // sticky if moving
        {
            if (Controller.world->isUnoccupiedPos (position + getDir()))
            { // forward will be empty 
                if (Controller.world->isOccupiedPos (position + getDir() - getUp()))
                { // below forward is solid
                    move_action = getActionWithId (ACTION_FORWARD);
                }
            }
            else
            {
                move_action = getActionWithId (ACTION_CLIMB_UP);
            }
        }
        
        if (move_action == NULL)
        {
            move_action = getActionWithId (ACTION_FALL);
            move_action->takeRest (action);
        }
    }
    else if (actionId == ACTION_FALL || actionId == ACTION_FALL_FORWARD) // landed
    {
        if (this == (KikiBot*)Controller.player)
        {
            Controller.sound->playSound (KikiSound::BOT_LAND);
        }
        else
        {
            Controller.sound->playSoundAtPos(KikiSound::BOT_LAND, getPos());
        }
    }
    
    if (move_action)
    {
        Controller.timer_event->addAction (move_action);
        return;
    }
    
    if (rotate_action) return;
    
    if (move)
    {
        moveBot();
    }
    else
    {
        dir_sgn = 1.0;
        if (actionId != ACTION_NOOP) jump_once = false;
        // keep action chain flowing in order to detect environment changes
        startTimedAction (getActionWithId (ACTION_NOOP), 0);
    }    
}

// __________________________________________________________________________________________________
void KikiBot::moveBot ()
{
    move_action = NULL;
     
    KikiPos forwardPos = position + getDir();
    
    if ((jump || jump_once) && 				// jump mode or jump activated while moving
        dir_sgn == 1.0 &&     				// and moving forward
        Controller.world->isUnoccupiedPos (position + getUp())) // and above empty
    {
        if (Controller.world->isUnoccupiedPos (forwardPos + getUp()) &&
            Controller.world->isUnoccupiedPos (forwardPos)) // forward and above forward also empty
        {
            move_action = getActionWithId (KikiBot::ACTION_JUMP_FORWARD);
        }
        else // no space to jump forward -> jump up
        {
            move_action = getActionWithId (KikiBot::ACTION_JUMP);
        }
    }
    else if (Controller.world->isUnoccupiedPos (forwardPos)) // forward is empty
    {
        if (Controller.world->isUnoccupiedPos (forwardPos + getDown())) 
        { // below forward also empty
            move_action = getActionWithId (KikiBot::ACTION_CLIMB_DOWN);
        }
        else // forward down is solid
        {
            move_action = getActionWithId (KikiBot::ACTION_FORWARD);
        }
    }
    else // forward is not empty
    {
        KikiAction * moveAction = getActionWithId (KikiBot::ACTION_FORWARD);
        if (push && Controller.world->mayObjectPushToPos (this, forwardPos, moveAction->getDuration()))
        {
            moveAction->reset();
            // player in push mode and pushing object is possible
            if (Controller.world->isUnoccupiedPos(forwardPos + getDown())) // below forward is empty
            {
                move_action = getActionWithId (KikiBot::ACTION_CLIMB_DOWN);
            }
            else
            {
                move_action = moveAction;
                // pushing stones costs one energy point
                // status->addEnergy (-0.01); 
            }
        }
        else // just climb up
        {
            move_action = getActionWithId (KikiBot::ACTION_CLIMB_UP);
        }
    }
    
    // reset the jump once flag (either we jumped or it's not possible to jump at current position)
    jump_once = false; 

    if (move_action)
    {
        move_action->keepRest(); // try to make subsequent actions smooth
        Controller.timer_event->addAction (move_action);
    }
}

// __________________________________________________________________________________________________
void KikiBot::render ()
{
    float radius	= 0.5;
    float tireRadius	= 0.15;

    if (died) getDeadColor().glColor();
    else getTireColor().glColor();
        
    KMatrix(current_orientation).glMultMatrix();
    glPushMatrix(); // tires
        glRotated(90.0, 0.0, 1.0, 0.0);
        glTranslated(0.0, 0.0, radius-tireRadius);
        glRotated(left_tire_rot * 180.0, 0.0, 0.0, 1.0);
        
        render_tire;
        
    glPopMatrix();
    glPushMatrix();
        glRotated(90.0, 0.0, 1.0, 0.0);
        glTranslated(0.0, 0.0, -(radius-tireRadius));
        glRotated(right_tire_rot * 180.0, 0.0, 0.0, 1.0);

        render_tire;
        
    glPopMatrix();

    if (died == false) getBodyColor().glColor();

    render_body;
    
    if ((move_action || rotate_action) && died == false)
    {
        unsigned int now = Controller.getTime();
        if ((int)(now - last_fume) > Controller.mapMsTime (40))
        { 
            KikiBotFume * fume = new KikiBotFume ();
            Controller.world->addObject (fume);
            fume->setPosition (current_position - getCurrentDir() * 0.4);
            last_fume = now;
        }
    }
}



