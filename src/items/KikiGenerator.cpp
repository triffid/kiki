/*
 *  KikiGenerator.cpp
 *  kiki
 */

#include "KikiGenerator.h"
#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiSound.h"
#include "KikiWire.h"

#include <KConsole.h>

#include "gear.h"
#include "generator.h"

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiGenerator, KikiGear )
KIKI_OBJECT_VALUES 		( KikiGenerator, true )

// __________________________________________________________________________________________________
KikiGenerator::KikiGenerator ( int face ) : KikiGear (face) 
{
}

// __________________________________________________________________________________________________
void KikiGenerator::activateWires ()
{
    KikiObjectList wires = Controller.world->getObjectsOfTypeAtPos (KikiWire::classId(), getPos());

    for (KikiObjectIter iter = wires.begin(); iter != wires.end(); iter++)
    {
        ((KikiWire*)*iter)->setActive (active);
    }
}

// __________________________________________________________________________________________________
void KikiGenerator::setActive ( bool a )
{
    if (active != a)
    {
        KikiGear::setActive (a);
        activateWires();
        Controller.sound->playSound (active ? KikiSound::GENERATOR_ON : KikiSound::GENERATOR_OFF);
    }
}

// __________________________________________________________________________________________________
void KikiGenerator::render () 
{    
    if (active)
    {
        glRotatef (clockwise ? angle : -angle, 0.0, 0.0, 1.0);
    }

    colors[0].glColor();

    render_generator;

    KikiGear::colors[0].glColor();
        
    glTranslatef (0.0, 0.0, 0.4);

    render_gear;
}
