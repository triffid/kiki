/*
 *  KikiMotorCylinder.cpp
 *  kiki
 */

#include "KikiMotorCylinder.h"
#include "KikiController.h"
#include "KikiSound.h"
#include "KikiGear.h"

#include "cylinder.h"
#include "kolben.h"

#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiMotorCylinder, KikiObject )
KIKI_OBJECT_VALUES  		( KikiMotorCylinder, true )

// __________________________________________________________________________________________________
KikiMotorCylinder::KikiMotorCylinder ( int face ) : KikiObject ()
{
    value = 0.0;
    active = false;
    orientation = KikiFace::orientationForFace (face);
    addAction (new KikiAction (this, ACTION_TUCKER, "tucker", 500, KikiAction::REPEAT));
    
    setActive (true);
}

// __________________________________________________________________________________________________
void KikiMotorCylinder::setActive ( bool a )
{
    if (active != a)
    {
        active = a;
        
        if (active)
        {
            // ............................................................. start tucker
            startTimedAction (getActionWithId (ACTION_TUCKER));
        }
        else
        {
            stopAction (getActionWithId (ACTION_TUCKER));
        }
    }
}

// __________________________________________________________________________________________________
void KikiMotorCylinder::performAction ( KikiAction * action )
{
    int actionId = action->getId();
    
    if (actionId == ACTION_TUCKER)
    {
        float relTime = action->getRelativeTime();
        value = (relTime < 0.5) ? relTime : 1.0 - relTime;
        value *= 2;
    }
}

// __________________________________________________________________________________________________
void KikiMotorCylinder::finishAction ( KikiAction * action )
{
    int actionId = action->getId();
    
    if (actionId == ACTION_TUCKER)
    {
        Controller.sound->playSoundAtPos (KikiSound::MOTOR, getPos());
    }
}

// __________________________________________________________________________________________________
void KikiMotorCylinder::render ()
{
    colors[0].glColor();

    KMatrix (orientation).glMultMatrix();

    render_cylinder;
    
    glTranslatef (0.0, 0.0, -0.5 * sin(value));
    
    KikiGear::getObjectColor(0).glColor();
    
    render_kolben;
}
