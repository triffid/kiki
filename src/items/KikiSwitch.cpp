/*
 *  KikiSwitch.cpp
 *  kiki
 */

#include "KikiSwitch.h"
#include "KikiController.h"
#include "KikiSound.h"
#include "KikiLight.h"

#include <KConsole.h>
#include <KDisplayTools.h>

//#if defined(__APPLE__) && defined(__MACH__)
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiSwitch, KikiObject )
KIKI_OBJECT_VALUES_1 		( KikiSwitch, true, sphere )

static int SWITCH_OFF_EVENT;
static int SWITCH_ON_EVENT;
static int SWITCHED_EVENT;

// __________________________________________________________________________________________________
KikiSwitch::KikiSwitch ( bool on ) : KikiObject()
{
    angle = 0.0;
    light = NULL;
    active = on;
    
    sound_on  = KikiSound::SWITCH_ON;
    sound_off = KikiSound::SWITCH_OFF;

    SWITCH_OFF_EVENT = addEventWithName ("off");
    SWITCH_ON_EVENT  = addEventWithName ("on");
    SWITCHED_EVENT   = addEventWithName ("switched");

    addAction (new KikiAction (this, ACTION_TOGGLE, "toggle", 0));
    addAction (new KikiAction (this, ACTION_ROTATE, "rotation", 2000, KikiAction::CONTINUOUS));

    if (active)
    {
        startTimedAction (getActionWithId(ACTION_ROTATE));
        light = new KikiLight (position, 3.0);

		light->addReceiverCallback((KObject*)this, (KCallbackPtr)&KikiSwitch::lightDeleted, 
                                                    KIKI_NOTIFICATION_OBJECT_DELETED);
    }
}

// __________________________________________________________________________________________________
KikiSwitch::~KikiSwitch ()
{
    if (light) delete light;
}

// __________________________________________________________________________________________________
void KikiSwitch::lightDeleted ()
{
    light = NULL;
}

// __________________________________________________________________________________________________
void KikiSwitch::setActive ( bool status )
{
    if (active != status)
    {
        active = status;
        
        if (active)
        {
            // ............................................................. start the orbit rotation
            startTimedAction (getActionWithId(ACTION_ROTATE));

            Controller.sound->playSound (sound_on);
            events[SWITCH_ON_EVENT]->triggerActions();
            
            light = new KikiLight (position, 3.0);

            light->addReceiverCallback((KObject*)this, (KCallbackPtr)&KikiSwitch::lightDeleted, 
                                                       KIKI_NOTIFICATION_OBJECT_DELETED);
        }
        else
        {
            stopAction (getActionWithId(ACTION_ROTATE));
            
            Controller.sound->playSound (sound_off);
            events[SWITCH_OFF_EVENT]->triggerActions();

            if (light) 
            {
                delete light;
                light = NULL;
            }
        }
        
        events[SWITCHED_EVENT]->triggerActions();
    }
}

// __________________________________________________________________________________________________
void KikiSwitch::setPosition ( const KVector & pos )
{
    if (light)
    {
        light->setPosition(pos);
    }
    KikiObject::setPosition(pos);
}

// __________________________________________________________________________________________________
void KikiSwitch::performAction ( KikiAction * action )
{
    int actionId = action->getId();
    
    if (actionId == ACTION_TOGGLE)
    {
        toggle();
    }
    else
    {
        angle += action->getRelativeDelta() * 360;
    }
}

// __________________________________________________________________________________________________
void KikiSwitch::render ()
{
    float radius = 0.5;
    float innerRadius = 0.05;

    colors[KikiSwitch_base_color].glColor();
    glPushMatrix();
    glRotatef(angle, 1.0, 0.0, 0.0);
    glutSolidTorus (innerRadius, (radius-innerRadius), 6, 8);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glutSolidTorus (innerRadius, (radius-innerRadius), 6, 8);
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus (innerRadius, (radius-innerRadius), 6, 8);
    glPopMatrix();

    if (active)
    {
        colors[KikiSwitch_sphere_color].glColor();
        kDisplaySolidSphere(0.3);
    }
}

