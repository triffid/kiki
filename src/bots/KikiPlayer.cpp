/*
 *  KikiPlayer.cpp
 *  kiki
 */

#include "KikiPlayer.h"
#include "KikiWorld.h"
#include "KikiSound.h"
#include "KikiBullet.h"
#include "KikiController.h"
#include "KikiStatusDisplay.h"
#include "KikiScreenText.h"
#include "KConsole.h"
#include "KikiAction.h"
#include "KikiEvent.h"
#include "KikiTools.h"
#include "KikiRecorder.h"
#include "KikiPlayback.h"

#include <KKey.h>
#include <KKeyRecorder.h>
#include <KLightingProjection.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiPlayer, KikiBot )
KIKI_OBJECT_VALUES_2 		( KikiPlayer, true, dead, tire )

// __________________________________________________________________________________________________
std::string KikiPlayer::forward_key	= "UP";
std::string KikiPlayer::backward_key	= "DOWN";
std::string KikiPlayer::turn_left_key	= "LEFT";
std::string KikiPlayer::turn_right_key	= "RIGHT";
std::string KikiPlayer::shoot_key	= "SPACE";
std::string KikiPlayer::jump_key	= "CTRL";
std::string KikiPlayer::push_key	= "SHIFT";
std::string KikiPlayer::look_up_key	= "HOME";
std::string KikiPlayer::look_down_key	= "END";
std::string KikiPlayer::view_key	= "PAGEDOWN";
 
KikiActionKey KikiPlayer::actionKeyMapping[] = 
{
    {"move forward", 	&KikiPlayer::forward_key}, 
    {"move backward",	&KikiPlayer::backward_key}, 
    {"turn left",	&KikiPlayer::turn_left_key}, 
    {"turn right",	&KikiPlayer::turn_right_key}, 
    {"shoot",		&KikiPlayer::shoot_key}, 
    {"jump",		&KikiPlayer::jump_key}, 
    {"push",		&KikiPlayer::push_key}, 
    {"look up",		&KikiPlayer::look_up_key}, 
    {"look down",	&KikiPlayer::look_down_key}, 
    {"change view",	&KikiPlayer::view_key}, 
    {NULL, NULL}
};

static KKeyRecorder KeyRecorder;
static std::string RecordingActionName;

// __________________________________________________________________________________________________
KikiPlayer::KikiPlayer () : KikiBot (), KKeyHandler ()
{                            
    look_action = NULL;
    look_angle  = 0.0;
    new_dir_sgn = 1.0;
    rotate      = 0;
    
    recorder	= NULL;
    playback	= NULL;
    
    flags[KDL_KEYHANDLER_FLAG_HANDLES_RELEASE] = true;
    
    addAction (new KikiAction (this, ACTION_LOOK_UP,	"look up",	220));
    addAction (new KikiAction (this, ACTION_LOOK_DOWN,	"look down",	220));
    addAction (new KikiAction (this, ACTION_LOOK_RESET,	"look reset",	60));

    addEventWithName ("keyset");
    addEventWithName ("keyset failed");
    addEventWithName ("landed");

    projection = new KLightingProjection (90.0);
    projection->updateViewport();
    projection->getLight().setCutoff (90.0);
    projection->getLight().setAttenuation (1.0, 0.0, 0.05);

    Controller.player_status->setStatus (status);
}

// __________________________________________________________________________________________________
KikiPlayer::~KikiPlayer ()
{
    delete projection;
    if (recorder) delete recorder;
    if (playback) delete playback;
}

// __________________________________________________________________________________________________
std::string KikiPlayer::getActionForKey ( const std::string & keyName )
{
    int index = 0;
    while (actionKeyMapping[index].actionName)
    {
        if (keyName == *actionKeyMapping[index].keyName)
        {
            return actionKeyMapping[index].actionName;
        }
        index++;
    }
  
    return "";
}

// __________________________________________________________________________________________________
std::string KikiPlayer::getKeyForAction ( const std::string & actionName )
{
    int index = 0;
    while (actionKeyMapping[index].actionName)
    {
        if (actionName == actionKeyMapping[index].actionName)
        {
            return *actionKeyMapping[index].keyName;
        }
        index++;
    }
  
    return "";
}

// __________________________________________________________________________________________________
void KikiPlayer::setKeyForAction ( const std::string & keyName, const std::string & actionName )
{
    int index = 0;
    while (actionKeyMapping[index].actionName)
    {
        if (actionName == actionKeyMapping[index].actionName)
        {
            (*actionKeyMapping[index].keyName) = keyName;
        }
        index++;
    }
}

// __________________________________________________________________________________________________
void KikiPlayer::recordKeyForAction ( const std::string & actionName )
{
    RecordingActionName = actionName;
	KeyRecorder.startRecordingSequence ((KObject*)this, (KSetStringPtr) &KikiPlayer::setRecordedKey, 1);
}

// __________________________________________________________________________________________________
void KikiPlayer::setRecordedKey ( const std::string & keyName )
{
    int index = 0;
    while (actionKeyMapping[index].actionName)
    {
        if (keyName == *(actionKeyMapping[index].keyName) && 
            actionKeyMapping[index].actionName != RecordingActionName)
        {
            setKeyForAction ("", actionKeyMapping[index].actionName);
        }
        index++;
    }
    setKeyForAction (keyName, RecordingActionName);
    getEventWithName ("keyset")->triggerActions();
}

// __________________________________________________________________________________________________
void KikiPlayer::updatePosition ()
{
    if (move_action)
    {
        float relTime = (Controller.getTime() - move_action->getStart()) / 
                                    (float)move_action->getDuration();
        if (relTime <= 1.0)
        {
            switch (move_action->getId())
            {
                case ACTION_FORWARD:
                    current_position = position + relTime * getDir();
                    break;
                case ACTION_FALL:
                    current_position = position - relTime * getUp(); 
                    break;
                case ACTION_JUMP_FORWARD:
                    current_position = position  + (1.0 - cos(M_PI_2 * relTime)) * getDir() 
                                        + cos(M_PI_2 - M_PI_2 * relTime) * getUp();
                    break;
                case ACTION_FALL_FORWARD:
                    current_position = position + cos(M_PI_2 - M_PI_2 * relTime) * getDir() 
                                        + (1.0 - cos(M_PI_2 * relTime)) * -getUp();
                    break;
            }
        }
    }    
}

// __________________________________________________________________________________________________
KProjection * KikiPlayer::getProjection ()
{
    // smooth camera movement a little bit
    float posDelta = Controller.getSpeed() / 10.0;
    projection->setPosition ((1.0 - posDelta) * projection->getPosition() + posDelta * current_position);

    KVector playerDir   = getCurrentDir();
    KVector playerUp  	= current_orientation.rotate (KVector(0,1,0)).normal();
        
    if (look_angle) // player is looking up or down
    {        
        projection->setXVector (playerUp.cross (playerDir).normal());
        KQuaternion look_rot = KQuaternion::rotationAroundVector (look_angle, projection->getXVector());
        projection->setYVector (look_rot.rotate (playerUp));
        projection->setZVector (look_rot.rotate (-playerDir));
    }
    else
    {
        // smooth camera rotation a little bit
        float lookDelta = (2.0 - projection->getZVector() * playerDir) * Controller.getSpeed() / 50.0;
        KVector newLookVector  = (1.0 - lookDelta) * projection->getZVector() - lookDelta * playerDir;
        newLookVector.normalize();

        projection->setXVector (playerUp.cross(newLookVector).normal());
        projection->setYVector (playerUp);
        projection->setZVector (newLookVector);
    }
        
    return projection;
}

// __________________________________________________________________________________________________
KProjection * KikiPlayer::getBehindProjection ()
{
    updatePosition ();

    KVector playerDir   = getCurrentDir();
    KVector playerUp  	= current_orientation.rotate(KVector(0,1,0)).normal();
    
    // find a valid camera position
    KVector botToCamera = (playerUp - 2 * playerDir);
    float min_f = botToCamera.length();
    botToCamera.normalize();
    
    min_f = kMin (Controller.world->getWallDistanceForRay(current_position, botToCamera), min_f);
    KVector cameraPos = current_position + kMax(min_f, 0.72) * botToCamera;
    cameraPos = Controller.world->getInsideWallPosWithDelta (cameraPos, 0.2);
        
    // smooth camera movement a little bit
    float posDelta = 0.2;
    projection->setPosition ((1.0 - posDelta) * projection->getPosition() + posDelta * cameraPos);
                                                                            
    if (look_angle)
    {        
        projection->setXVector (playerUp.cross(playerDir).normal());
        KQuaternion look_rot = KQuaternion::rotationAroundVector (look_angle, projection->getXVector());
        projection->setYVector (look_rot.rotate(playerUp));
        projection->setZVector (look_rot.rotate(-playerDir));
    }
    else
    {
        // smooth camera rotation a little bit
        float lookDelta = 0.3;
        KVector newLookVector  = (1.0 - lookDelta) * projection->getZVector() - lookDelta * playerDir;
        newLookVector.normalize();
        
        projection->setZVector (newLookVector); 
        projection->setXVector (playerUp.cross(newLookVector).normal());
        projection->setYVector (newLookVector.cross(projection->getXVector()).normal());
    }
    
    return projection;
}

// __________________________________________________________________________________________________
KProjection *  KikiPlayer::getFollowProjection ()
{
    KVector cameraPos = projection->getPosition();	// current camera position
    float   desiredDistance = 2.0;			// desired distance from camera to bot

    updatePosition ();

    KVector playerPos   = current_position;		// desired look pos
    KVector playerDir   = getCurrentDir();
    KVector playerUp  	= current_orientation.rotate (KVector (0,1,0)).normal();
    KVector playerRight = (playerDir.cross (playerUp)).normal();

    // .................................................................. camera follows bot
    // first, adjust distance from camera to bot
     
    KVector botToCamera (cameraPos - playerPos);	// vector from bot to current pos
    float cameraBotDistance = botToCamera.length();	// distance from camera to bot
    
    if (cameraBotDistance >= desiredDistance)
    {
        float difference = cameraBotDistance - desiredDistance;
        float delta = (difference*difference)/400.0;		// weight for following speed
        cameraPos = (1.0 - delta) * cameraPos + delta * playerPos;
    }
    else
    {
        float difference = desiredDistance - cameraBotDistance;
        float delta = difference/20.0;				// weight for negative following speed
        cameraPos = (1.0 - delta) * cameraPos + delta * (playerPos + desiredDistance * botToCamera.normal());
    }

    // .................................................................. refining camera position
    // second, rotate around bot

    botToCamera = cameraPos - playerPos;
    KVector botToCameraNormal = botToCamera.normal();

    // .................................................................. try view bot from above
    // if camera below bot, rotate up
    if (botToCameraNormal * playerUp < 0)
    {
        // calculate angle between player to camera vector and player up vector
        float verticalAngle = RAD2DEG (acos (kMinMax(-1.0, 1.0, botToCameraNormal * playerUp))) - 90.0;
        cameraPos = playerPos + KQuaternion::rotationAroundVector
                            (verticalAngle/40.0, botToCameraNormal.cross(playerUp)).rotate(botToCamera);
        
        botToCamera = cameraPos - playerPos;
        botToCameraNormal = (cameraPos - playerPos).normal();
    }

    float rot_factor = 1.0;
    float wall_distance = Controller.world->getWallDistanceForPos (playerPos + botToCamera);
    if (wall_distance < 0.5)
    {
        // .................................................................. avoid piercing walls
        
        if (wall_distance < 0.2)
        {
            cameraPos = Controller.world->getInsideWallPosWithDelta (cameraPos, 0.2);
            botToCamera = cameraPos - playerPos;
            botToCameraNormal = (cameraPos - playerPos).normal();
        }
        
        rot_factor = 0.5 / (wall_distance-0.2);
    }

    // .................................................................. try view bot from behind
    // calculate horizontal angle between bot orientation and vector to camera
    KVector mappedToXZ ((botToCamera - playerUp * (botToCamera * playerUp)).normal());
    float horizontalAngle = RAD2DEG (acos (kMinMax(-1.0, 1.0, -playerDir * mappedToXZ)));
    if (botToCameraNormal * playerRight > 0)
    {
        horizontalAngle = -horizontalAngle;
    }

    cameraPos = playerPos + KQuaternion::rotationAroundVector 
                        (horizontalAngle / (rot_factor * 400.0), playerUp).rotate (botToCamera);

    botToCamera = cameraPos - playerPos;
    botToCameraNormal = botToCamera.normal();

    // .................................................................. finally, set the position
    
    projection->setPosition(cameraPos);
    
    // .................................................................. refining camera orientation
    
    // slowly adjust look direction by interpolating current and desired directions
    float lookDelta = 2.0 - projection->getZVector() * botToCameraNormal;
    lookDelta *= lookDelta / 30.0;    
    KVector newLookVector = (1.0 - lookDelta) * projection->getZVector() + lookDelta * botToCameraNormal;
    newLookVector.normalize();
    
    // slowly adjust up vector by interpolating current and desired up vectors
    float upDelta = 2.0 - projection->getYVector() * playerUp;
    upDelta *= upDelta / 100.0;    
    KVector newRightVector = ((1.0 - upDelta) * projection->getYVector() + upDelta * playerUp).cross(newLookVector);
    newRightVector.normalize();
    KVector newUpVector = newLookVector.cross(newRightVector).normal();

    // finished interpolations, update camera matrix
    projection->setZVector (newLookVector);
    projection->setXVector (newRightVector);
    projection->setYVector (newUpVector);
    
    return projection;
}

// __________________________________________________________________________________________________
void KikiPlayer::initAction ( KikiAction * action )
{
    int actionId = action->getId();
    switch (actionId)
    {
    	case ACTION_FORWARD:
        case ACTION_CLIMB_DOWN:
            status->addMoves(1);

        case ACTION_TURN_LEFT:
        case ACTION_TURN_RIGHT:
    
            Controller.sound->playSound(KikiSound::BOT_MOVE);
            break;
            
        case ACTION_JUMP:
        case ACTION_JUMP_FORWARD:
    
            status->addMoves(actionId == ACTION_JUMP ? 1 : 2);
            Controller.sound->playSound(KikiSound::BOT_JUMP);
            break;

        case ACTION_CLIMB_UP:
        
            break;

        case ACTION_SHOOT:
            break;
    }
    
    KikiBot::initAction(action);
}

// __________________________________________________________________________________________________
void KikiPlayer::performAction ( KikiAction * action )
{
    float relTime = action->getRelativeTime();

    switch (action->getId())
    {
        case ACTION_NOOP: return;
    
        case ACTION_LOOK_UP:
    
            look_angle = relTime * -90.0;
            break;
    
        case ACTION_LOOK_DOWN:
                
            look_angle = relTime * 90.0;
            break;
            
        case ACTION_LOOK_RESET:
            
            if (look_angle > 0) 
            {
                look_angle = kMin (look_angle, (1.0-relTime) * 90.0);
            }
            else 
            {
                look_angle = kMax (look_angle, (1.0-relTime) * -90.0);
            }
            break;
        
        default:

            KikiBot::performAction(action);
    }
}

// __________________________________________________________________________________________________
void KikiPlayer::finishAction ( KikiAction * action )
{    
    int actionId = action->getId();

    if (actionId == ACTION_LOOK_RESET)
    {
        look_action = NULL;
        look_angle  = 0.0;
    }
    else
    {
        if (action == move_action) // move finished, update direction
        {
            dir_sgn = new_dir_sgn;
        }
        
        if (actionId != ACTION_LOOK_UP && actionId != ACTION_LOOK_DOWN)
        {
            KikiBot::finishAction (action);
        }
        
        if (actionId == ACTION_TURN_LEFT || actionId == ACTION_TURN_RIGHT)
        {
            if (rotate)
            {
                rotate_action = getActionWithId (rotate);
                rotate_action->reset();
                Controller.timer_event->addAction (rotate_action);
            }
        }
    }
}

// __________________________________________________________________________________________________
void KikiPlayer::die ()
{
    Controller.removeKeyHandler (this);
    KikiBot::die();
    Controller.displayText ("game over");
    Controller.sound->playSound (KikiSound::BOT_DEATH);
    Controller.world->setCameraMode (KikiWorld::CAMERA_FOLLOW);
}

// __________________________________________________________________________________________________
void KikiPlayer::reborn ()
{
    Controller.addKeyHandler (this);
    died = false;
}

// __________________________________________________________________________________________________
void KikiPlayer::reset ()
{
    KikiBot::reset ();
    Controller.timer_event->removeActionsOfObject (this);
    
    look_action = NULL;
    look_angle  = 0.0;
    new_dir_sgn = 1.0;
    rotate      = 0;
    
    recorder	= NULL;
    playback	= NULL;
}

// __________________________________________________________________________________________________
void KikiPlayer::saveRecorder ()
{
    if (recorder)
    {
        recorder->save();
        delete recorder;
        recorder = NULL;
    }
}

// __________________________________________________________________________________________________
void KikiPlayer::startRecorder ( const std::string & file )
{
    if (recorder)
    {
        saveRecorder ();
    }

    recorder = new KikiRecorder ( file );
}

#define KEY_HANDLED \
    if (recorder) recorder->recordKey (key); \
    return true;
    
// __________________________________________________________________________________________________
bool KikiPlayer::handleKey ( const KKey & key )
{
    std::string keyName = key.getUnmodifiedName();
    
    if (keyName == forward_key || keyName == backward_key)
    {	
        move = true; // try to move as long as the key is not released
        
        if (move_action == NULL) // player is currently not performing a move action
        {
            // forward or backward direction
            new_dir_sgn = dir_sgn = (key.getUnmodifiedName() == backward_key) ? -1 : 1; 

            moveBot(); // perform new move action (depending on environment)
        }
        else
        {
            new_dir_sgn = (keyName == backward_key) ? -1 : 1;
        }
    
        KEY_HANDLED
    }
    
    if (keyName == turn_left_key || keyName == turn_right_key)
    {
        rotate = (keyName == turn_left_key) ? ACTION_TURN_LEFT : ACTION_TURN_RIGHT;
        
        if (rotate_action == NULL && spiked == false) // player is not performing a rotation and unspiked
        {
            rotate_action = getActionWithId (rotate);
            Controller.timer_event->addAction (rotate_action);
        }
        
        KEY_HANDLED
    }
    
    if (key.name == jump_key)
    {
        jump = true; // switch to jump mode until jump_key released
        jump_once = true;
        
        KEY_HANDLED
    }
    
    if (key.name == push_key)
    {
        push = true;
        
        KEY_HANDLED
    }
    
    if (keyName == shoot_key)
    {
        if (shoot == false)
        {
            shoot = true;
            Controller.timer_event->addAction (getActionWithId (ACTION_SHOOT));
        }
        
        KEY_HANDLED
    }
    
    if (keyName == look_up_key || keyName == look_down_key)
    {
        if (!look_action)
        {
            look_action =  getActionWithId ((key.name == look_up_key) ? ACTION_LOOK_UP : ACTION_LOOK_DOWN);
            look_action->reset();
            Controller.timer_event->addAction (look_action);
        }
        
        KEY_HANDLED
    }
    
    if (keyName == view_key)
    {
        Controller.world->changeCameraMode();
        
        KEY_HANDLED
    }
    
    return false;
}

#define KEY_RELEASE_HANDLED \
    if (recorder) recorder->recordKeyRelease (key); \
    return true;

// __________________________________________________________________________________________________
bool KikiPlayer::handleKeyRelease ( const KKey & key )
{
    std::string keyName = key.getUnmodifiedName();
    
    if (keyName == shoot_key)
    {
        Controller.timer_event->removeAction (getActionWithId(ACTION_SHOOT));
        shoot = false;
        
        KEY_RELEASE_HANDLED
    }
    
    if ( keyName == forward_key || keyName == backward_key )
    {
        move = false;
        
        KEY_RELEASE_HANDLED
    }
    
    if (key.name == jump_key)
    {
        jump = false;
    
        if (jump_once)
        {
            if (move_action == NULL && Controller.world->isUnoccupiedPos (position + getUp()))
            {
                jump_once = false;
                move_action = getActionWithId (ACTION_JUMP); 
                Controller.sound->playSound (KikiSound::BOT_JUMP);
                Controller.timer_event->addAction (move_action);
            }
        }
        
        KEY_RELEASE_HANDLED
    }
    
    if ( keyName ==  turn_left_key || keyName == turn_right_key )
    {
        rotate = 0;
        
        KEY_RELEASE_HANDLED
    }
    
    if (key.name == push_key)
    {
        push = false;
        
        KEY_RELEASE_HANDLED
    }
    
    if (keyName == look_down_key || keyName == look_up_key)
    {
        if (look_action && look_action->getId() != ACTION_LOOK_RESET)
        {
            Controller.timer_event->removeAction (look_action);
        }
        look_action = getActionWithId (ACTION_LOOK_RESET);
        Controller.timer_event->addAction (look_action);
        
        KEY_RELEASE_HANDLED
    }
    
    if (keyName == view_key)
    {
        KEY_RELEASE_HANDLED
    }
        
    return false;
}

// __________________________________________________________________________________________________
void KikiPlayer::display ()
{
    if (Controller.world->getCameraMode() != KikiWorld::CAMERA_INSIDE || Controller.world->getEditMode())
    {
        glPushMatrix ();
        
        current_position.glTranslate();
        
        render();
        
        glPopMatrix();
    }
}

// __________________________________________________________________________________________________
const KColor & KikiPlayer::getBodyColor ()
{
    if (Controller.world->getCameraMode() == KikiWorld::CAMERA_BEHIND)
    {
        static KColor bodyColor;
        bodyColor = colors[KikiPlayer_base_color];
        bodyColor.setAlpha(kMin(0.7, (projection->getPosition()-current_position).length()-0.4));
        return bodyColor;
    }

    return colors[KikiPlayer_base_color];
}

// __________________________________________________________________________________________________
const KColor & KikiPlayer::getTireColor ()
{ 
    if (Controller.world->getCameraMode() == KikiWorld::CAMERA_BEHIND)
    {
        static KColor tireColor;
        tireColor = colors[KikiPlayer_tire_color];
        tireColor.setAlpha(kMin(1.0, (projection->getPosition()-current_position).length()-0.4));
        return tireColor;
    }

    return colors[KikiPlayer_tire_color];
}
 
// __________________________________________________________________________________________________
void KikiPlayer::finishRotateAction ()
{
  if (rotate_action)
  {
    rotate = false;
    finishAction(rotate_action);
  }
}
