/*
 *  KikiBotFume.cpp
 *  kiki
 */

#include "KikiBotFume.h"
#include "KikiController.h"
#include "KConsole.h"
#include "KikiWorld.h"

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiBotFume, KikiBillBoard )
KIKI_OBJECT_VALUES 		( KikiBotFume, false )

// __________________________________________________________________________________________________
KikiBotFume::KikiBotFume () : KikiBillBoard ()
{
    size  	= 0.0;
    alpha_value = 1.0;

    startTimer (300);
}

// __________________________________________________________________________________________________
KColor KikiBotFume::getColor ()
{
    KColor c(colors[0]);
    c.setAlpha (c.getAlpha()*alpha_value);
    return c;
}

// __________________________________________________________________________________________________
GLuint KikiBotFume::getTextureId ()
{
    return Controller.world->getTextureId (KikiWorld::TEXTURE_GRADIENT);
}

// __________________________________________________________________________________________________
void KikiBotFume::performAction ( KikiAction * action )
{
    float relTime = action->getRelativeTime();
    size = relTime * 0.25;
    alpha_value = 1.0 - relTime;
}

// __________________________________________________________________________________________________
void KikiBotFume::actionFinished ( KikiAction * action )
{
    delete this;
}

