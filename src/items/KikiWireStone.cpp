/*
 *  KikiWireStone.cpp
 *  kiki
 */

#include "KikiWireStone.h"
#include "KikiWire.h"
#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiGenerator.h"
#include "KikiWall.h"

#include <KDisplayTools.h>
#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiWireStone, KikiStone )
KIKI_OBJECT_VALUES 		( KikiWireStone, true )

// __________________________________________________________________________________________________
KikiWireStone::KikiWireStone () : KikiStone ()
{
    for (int i = 0; i < 6; i++)
    {
        wires[i] = NULL;
    }
}

// __________________________________________________________________________________________________
void KikiWireStone::initAction ( KikiAction * action )
{
    switch (action->getId())
    {
    	case ACTION_PUSH:
        case ACTION_FALL:
        
        for (int i = 0; i < 6; i++)
        {
            if (wires[i])
            {
                Controller.world->unsetObject (wires[i]);
                wires[i]->setActive (false);
            }
        }
        
        KikiObjectList generators = Controller.world->getObjectsOfType (KikiGenerator::classId());
        for (KikiObjectIter iter = generators.begin(); iter != generators.end(); iter++)
        {
            if (((KikiGenerator*)*iter)->isActive())
            {
                ((KikiGenerator*)*iter)->activateWires();
            }
        }
    }

    KikiStone::initAction (action);
}

// __________________________________________________________________________________________________
void  KikiWireStone::setPosition ( const KVector & pos )      
{
    for (int i = 0; i < 6; i++)
    {
        KVector newPos = pos - KikiFace::normalVectorForFace (i);
        if (isFreePos (newPos))
        {
            if (wires[i] == NULL)
            {
                wires[i] = new KikiWire (i);
                Controller.world->addObjectAtPos (wires[i], newPos);
            }
            else
            {
                Controller.world->setObjectAtPos (wires[i], newPos);
                wires[i]->updateActive();
            }
        }
        else if (wires[i])
        {
            delete wires[i];
            wires[i] = NULL;
        }
    }

    KikiObjectList generators = Controller.world->getObjectsOfType (KikiGenerator::classId());
    for (KikiObjectIter iter = generators.begin(); iter != generators.end(); iter++)
    {
        if (((KikiGenerator*)*iter)->isActive())
        {
            ((KikiGenerator*)*iter)->activateWires();
        }
    }
    
    KikiStone::setPosition (pos);
}

// __________________________________________________________________________________________________
void KikiWireStone::setCurrentPosition ( const KVector & pos )
{
    KikiStone::setCurrentPosition (pos);
    for (int i = 0; i < 6; i++)
    {
        if (wires[i])
        {
            wires[i]->setPosition (pos - KikiFace::normalVectorForFace (i));
        }
    }
}

// __________________________________________________________________________________________________
bool KikiWireStone::isFreePos ( const KVector & pos )      
{
    if (Controller.world->isUnoccupiedPos (pos))
    {
        return true;
    } 
    if (Controller.world->isValidPos (pos))
    {
        KikiObject * occupant = Controller.world->getOccupantAtPos (pos);
        return ((occupant->getClassId () >= KikiWall::classId () ||
                 occupant->getClassId () >= KikiStone::classId ()) == false);
    }
    return false;
}

