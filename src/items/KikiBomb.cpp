/*
 *  KikiBomb.cpp
 *  kiki
 */

#include "KikiBomb.h"
#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiSound.h"
#include "KikiPlayer.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#ifdef WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#endif

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiBomb, KikiPushable )
KIKI_OBJECT_VALUES  		( KikiBomb, true )

KDL_CLASS_INTROSPECTION_1 	( KikiBombSplitter, KikiBomb )
KIKI_OBJECT_VALUES  		( KikiBombSplitter, false )

// __________________________________________________________________________________________________
KikiBomb::KikiBomb () : KikiPushable ()
{
    angle    = 0.0;
    size     = 1.0;
    splitted = false;

    addEventWithName ("explode");
    
    addAction (new KikiAction (this, ACTION_ROTATE,  "rotation", 2000, KikiAction::CONTINUOUS));
    addAction (new KikiAction (this, ACTION_IMPLODE, "implode", 100));
    addAction (new KikiAction (this, ACTION_EXPLODE, "explode", 100));
    startTimedAction (getActionWithId (ACTION_ROTATE));
}

// __________________________________________________________________________________________________
KikiBombSplitter::KikiBombSplitter ( const KVector & dir ) : KikiBomb ()
{
    size      = 0.0;
    splitted  = true;
    direction = dir;

    startTimedAction (getActionWithId (ACTION_EXPLODE));
}

// __________________________________________________________________________________________________
void KikiBomb::splitterInDirection ( const KVector & dir )
{
    bool splitter = false;
    KikiPos pos = getPos() + dir;
    
    if (Controller.world->isUnoccupiedPos (pos)) 
    {
        splitter = true;
    }
    else
    {
        KikiObject * occupant = Controller.world->getRealOccupantAtPos (pos);
        if (occupant)
        {
            if (occupant->getClassId() >= KikiBomb::classId())
            {
                occupant->bulletImpact();
                return;
            }
            /*
            else if (occupant->getClassId() >= KikiBot::classId())
            {
                ((KikiBot*)occupant)->getStatus()->addHealth (-0.2); // bombs damage seriously
            }
            */
            if (Controller.world->mayObjectPushToPos 
                        (this, pos, getActionWithId (ACTION_EXPLODE)->getDuration()))
            {
                splitter = true;
            }
        }        
    } 
        
    if (splitter)
    {
        Controller.world->addObjectAtPos (new KikiBombSplitter (dir), pos);
    }
}

// __________________________________________________________________________________________________
void KikiBomb::bulletImpact ()
{
    if (!splitted)
    {
        splitted = true;
        static float directions[6][3] = {{1,0,0}, {0,1,0}, {0,0,1}, {-1,0,0}, {0,-1,0}, {0,0,-1}};
        for (int i = 0; i < 6; i++)
        {
            splitterInDirection (KVector (directions[i][X], directions[i][Y], directions[i][Z]));
        }
        
        startTimedAction (getActionWithId (ACTION_IMPLODE));
        Controller.sound->playSoundAtPos (KikiSound::BOMB_EXPLODE, getPos());
        getEventWithName ("explode")->triggerActions();
    }
}

// __________________________________________________________________________________________________
void KikiBomb::performAction ( KikiAction * action )
{
    switch (action->getId())
    {
    	case ACTION_ROTATE:
        
            angle += action->getRelativeDelta() * 360;
            break;
            
    	case ACTION_IMPLODE:
        
            size = 1.0 - action->getRelativeTime();
            break;
    
        case ACTION_EXPLODE:

            size = action->getRelativeTime();
            break;
            
        default:
            
            KikiPushable::performAction (action);
    }
}

// __________________________________________________________________________________________________
void KikiBomb::actionFinished ( KikiAction * action )
{
    int actionId = action->getId();
    
    if (actionId == ACTION_IMPLODE)
    {
        delete this;
    }
    else if (actionId == ACTION_EXPLODE)
    {
        splitterInDirection (direction);
        Controller.sound->playSoundAtPos (KikiSound::BOMB_SPLITTER, getPos());
        startTimedAction (getActionWithId (ACTION_IMPLODE));
    }
    else 
    {
        KikiPushable::actionFinished (action);
    }
}

// __________________________________________________________________________________________________
void KikiBomb::render ()
{
    colors[KikiBomb_base_color].glColor();
    
    glScalef(size*0.3, size*0.3, size*0.3);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glutSolidDodecahedron ();
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidDodecahedron ();
}
