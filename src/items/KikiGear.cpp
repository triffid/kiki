/*
 *  KikiGear.cpp
 *  kiki
 */

#include "KikiGear.h"
#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiSound.h"

#include "gear.h"
#include "valve.h"

#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiGear, KikiValve )
KIKI_OBJECT_VALUES 		( KikiGear, true )

// __________________________________________________________________________________________________
KikiGear::KikiGear ( int face ) : KikiValve (face) 
{
}

// __________________________________________________________________________________________________
KikiPos * KikiGear::getNeighborDirections ()
{
    static KikiPos neighbors[3][4] = {
        {KikiPos (0,1,0), KikiPos (0,-1,0), KikiPos (0,0,1), KikiPos (0,0,-1)},
        {KikiPos (1,0,0), KikiPos (-1,0,0), KikiPos (0,0,1), KikiPos (0,0,-1)},
        {KikiPos (1,0,0), KikiPos (-1,0,0), KikiPos (0,1,0), KikiPos (0,-1,0)}};
        
    return neighbors[face % 3];
}

// __________________________________________________________________________________________________
std::vector<KikiGear*> KikiGear::getNeighborGears ()
{
    std::vector<KikiGear*> neighbor_gears;
    
    KikiPos * neighbor_dirs = getNeighborDirections();
    KikiPos pos = getPos();
    
    for (int i = 0; i < 4; i++)
    {
        KikiObject * neighbor = Controller.world->getOccupantAtPos (pos + neighbor_dirs[i]);
        if (neighbor && neighbor->getClassId() >= KikiGear::classId())
        {
            KikiGear * neighbor_gear = (KikiGear*)neighbor;
            if (neighbor_gear->face == face)
            {
                neighbor_gears.push_back (neighbor_gear);
            }
        }
    }
  
    return neighbor_gears;
}

// __________________________________________________________________________________________________
void KikiGear::initAction ( KikiAction * action )
{
    KikiValve::initAction (action);
    
    if (action->getId() == ACTION_PUSH)
    {
        setActive (false);
    }
}
 
// __________________________________________________________________________________________________
void KikiGear::actionFinished ( KikiAction * action )
{
    KikiValve::actionFinished (action);
    
    int actionId = action->getId();
    
    if (actionId == ACTION_PUSH || actionId == ACTION_FALL)
    {
        if (move_action == NULL)
        {
            updateActive();
        }
    }
}

// __________________________________________________________________________________________________
void KikiGear::updateActive ()
{
    setActive (false);
    std::vector<KikiGear*> neighbors = getNeighborGears();
    for (std::vector<KikiGear*>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++)
    {
        if ((*iter)->active)
        {
            setActive (true);
            return;
        }
    }
}
 
// __________________________________________________________________________________________________
void KikiGear::setActive ( bool a )
{
    if (active != a)
    {
        active = a;
                
        Controller.sound->playSound (active ? KikiSound::GEAR_ON : KikiSound::GEAR_OFF);
        
        std::vector<KikiGear*> neighbors = getNeighborGears();
        for (std::vector<KikiGear*>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++)
        {
            if (active)
            {
                (*iter)->setActive (true);
            }
            else
            {
                (*iter)->updateActive ();
            }
        }
    }
} 
 
// __________________________________________________________________________________________________
void KikiGear::render ()
{
    if (active)
    {
        glRotatef (clockwise ? angle : -angle, 0.0, 0.0, 1.0);
    }
    
    KikiValve::colors[0].glColor();
    render_valve;
    
    glTranslatef (0.0, 0.0, 0.4);

    colors[0].glColor();
    render_gear;
}
