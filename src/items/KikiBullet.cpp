/*
 *  KikiBullet.cpp
 *  kiki
 */

#include "KikiBullet.h"
#include "KikiWorld.h"
#include "KikiSound.h"
#include "KikiMutant.h"
#include "KikiBotStatus.h"
#include "KikiStatusDisplay.h"

#include <KConsole.h>
#include <KDisplayTools.h>

KDL_CLASS_INTROSPECTION_1 	(KikiBullet, KikiObject)
KIKI_OBJECT_VALUES		(KikiBullet, false)

// __________________________________________________________________________________________________
#define KIKI_BULLET_RADIUS 0.1

// __________________________________________________________________________________________________
KikiBullet::KikiBullet () : KikiObject ()
{                            
    size = KIKI_BULLET_RADIUS;
    
    color = colors[KikiBullet_base_color];
    
    src_object = NULL;

    addAction (new KikiAction (this, ACTION_FLY, 	"fly",		40));
    addAction (new KikiAction (this, ACTION_EXPLODE,	"explode", 	200));
}

// __________________________________________________________________________________________________
void KikiBullet::shootFromBot ( KikiBot * bot )
{
    if (bot->getStatus()->getEnergy() >= 0.01 || Controller.player_status->isVisible() == false)
    {
        KikiBullet * bullet = new KikiBullet ();
        Controller.world->addObject(bullet);
        bullet->direction = bot->getCurrentDir();
        bullet->setPosition((KVector)bot->getPos() + bullet->direction/2.0);
        bullet->src_object = bot;
        bullet->color = bot->getBodyColor();
        bullet->color.setAlpha(0.8);
    
        if (bot->getClassId() >= KikiMutant::classId())
        {
            bot->getStatus()->addEnergy(-0.01);
        }
    
        Controller.sound->playSoundAtPos(KikiSound::BULLET_SHOT, bot->getPos());
    
        if (bullet->hitObjectAtPos (bullet->position + bullet->direction/2.0)) return;
    
        Controller.timer_event->addAction (bullet->getActionWithId(ACTION_FLY));
    }
    else
    {
        Controller.sound->playSoundAtPos(KikiSound::BOT_NO_ENERGY, bot->getPos());       
    }
}

// __________________________________________________________________________________________________
void KikiBullet::performAction ( KikiAction * action )
{
    float relTime = action->getRelativeTime();
    int actionId = action->getId();
    
    if (actionId == ACTION_FLY)
    {
        current_position = position + relTime * direction;
    }
    else if (actionId == ACTION_EXPLODE)
    {
        size  = KIKI_BULLET_RADIUS + relTime/2.0;
        color.setAlpha(0.8 * (1.0-relTime));
    }
}

// __________________________________________________________________________________________________
void KikiBullet::display ()
{
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    current_position.glTranslate();
    color.glColor();
    kDisplaySolidSphere(size);
    glPopMatrix();
    glPopAttrib();
}

// __________________________________________________________________________________________________
bool KikiBullet::hitObjectAtPos ( const KikiPos & pos )
{
    if (Controller.world->isInvalidPos(pos) || Controller.world->isOccupiedPos(pos))
    {
        KikiObject * hitObject = Controller.world->getRealOccupantAtPos (pos);
        
        if (hitObject != src_object)
        {
            if (hitObject)
            {
                hitObject->bulletImpact();
                if (hitObject->getClassId() >= KikiMutant::classId() && 
                    ((KikiMutant*)hitObject)->isDead() == false)
                {
                    Controller.sound->playSoundAtPos(KikiSound::BULLET_HIT_MUTANT, pos);
                }
                else if (hitObject == (KikiBot*)Controller.player)
                {
                    Controller.sound->playSoundAtPos(KikiSound::BULLET_HIT_PLAYER, pos);
                }
                else
                {
                    Controller.sound->playSoundAtPos(KikiSound::BULLET_HIT_OBJECT, pos);
                }
            }
            else
            {
                Controller.sound->playSoundAtPos(KikiSound::BULLET_HIT_WALL, pos);
            }
            Controller.timer_event->addAction (getActionWithId(ACTION_EXPLODE));
            return true;
        }
    }
    
    return false;
}

// __________________________________________________________________________________________________
void KikiBullet::finishAction ( KikiAction * action )
{
    std::string actionName = action->getName();

    if (actionName == "fly")
    {
        position = current_position;
    }
}

// __________________________________________________________________________________________________
void KikiBullet::actionFinished ( KikiAction * action )
{
    int actionId = action->getId();

    if (actionId == ACTION_FLY)
    {
        if (hitObjectAtPos (position + direction/2.0))
        {
            return;
        }

        Controller.timer_event->addAction (getActionWithId(ACTION_FLY));
    }
    else if (actionId == ACTION_EXPLODE)
    {
        Controller.world->deleteObject(this);
    }
}
