/*
 *  KikiAtom.cpp
 *  kiki
 */

#include "KikiAtom.h"
#include "KikiNeutron.h"
#include "KikiBot.h"
#include "KikiSound.h"
#include "KikiController.h"

#include <KConsole.h>
#include <KDisplayTools.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiAtom, 	  KikiObject )
KDL_CLASS_INTROSPECTION_1 	( KikiMovesAtom, KikiAtom )
#ifdef KIKI_OLD_STATUS
KDL_CLASS_INTROSPECTION_1 	( KikiEnergyAtom, KikiAtom )
KDL_CLASS_INTROSPECTION_1 	( KikiHealthAtom, KikiAtom )
KIKI_OBJECT_VALUES_1 		( KikiEnergyAtom, false, neutron )
KIKI_OBJECT_VALUES_1 		( KikiHealthAtom, false, neutron )
#endif
KDL_CLASS_INTROSPECTION_1 	( KikiValueAtom,  KikiAtom )
KIKI_OBJECT_VALUES 		( KikiAtom, 	  false )
KIKI_OBJECT_VALUES_1 		( KikiMovesAtom,  false, neutron )
KIKI_OBJECT_VALUES_1 		( KikiValueAtom,  true, neutron )

// __________________________________________________________________________________________________
static float KikiNeutronOrbits [9][6] = // values for neutron orbit plane normals and start angles
{
    {0,0,1, 	0},
    {0,1,0,	180}, 
    {1,0,0,	180}, 
    {0,1,1,	90}, 
    {1,0,1,	-90}, 
    {-1,-1,0,	180},
    {0,1,-1,	 45}, 
    {1,0,-1,	-45},
    {1,-1,0,	-45}    
};

int KikiAtom::num_neutrons = 9;

static int VALUE_CHANGED_EVENT;

// __________________________________________________________________________________________________
KikiAtom::KikiAtom ( int neutrons ) : KikiObject()
{
    value = neutrons/(float)num_neutrons;
    nucleus_size = neutrons/(num_neutrons*2.0);

    for (int i = 0; i < neutrons; i++) addNeutron();
}

// __________________________________________________________________________________________________
KikiValueAtom::KikiValueAtom ( float range_start, float range_end, float start_value, int levels ) 
    : KikiAtom (0)
{
    range[0]  = range_start;
    range[1]  = range_end;
    increment = (range_end - range_start) / levels;
    
    VALUE_CHANGED_EVENT = addEventWithName("value changed");
    
    setValue(mapValue(start_value));
    nucleus_size = kMax(0.1, nucleus_size); // minimum nucleus size
}

// __________________________________________________________________________________________________
float KikiValueAtom::mapValue ( float unmapped_value ) const
{
    return (unmapped_value - range[0])/(range[1] - range[0]);
}

// __________________________________________________________________________________________________
float KikiValueAtom::unmapValue ( float mapped_value ) const
{
    return mapped_value * (range[1] - range[0]) + range[0];
}

// __________________________________________________________________________________________________
void KikiValueAtom::bulletImpact ()
{
    float newValue = unmapValue(value) + increment;

    if (newValue > range[1])
    {
        increment = -increment;
        if (value == 1.0) newValue = range[1] + increment;
    }
    else if (newValue < range[0])
    {
        increment = -increment;
        if (value == 0.0) newValue = range[0] + increment;
    }
    setValue(mapValue(newValue));

    nucleus_size = kMax(0.1, nucleus_size); // minimum nucleus size
    events[VALUE_CHANGED_EVENT]->triggerActions();
}

// __________________________________________________________________________________________________
KikiAtom::~KikiAtom ()
{
    while (neutrons.empty() == false)
    {
        deleteNeutron();
    }
}

// __________________________________________________________________________________________________
void KikiAtom::deleteNeutron ()
{
    delete neutrons.back();
    neutrons.pop_back();
}

// __________________________________________________________________________________________________
void KikiAtom::addNeutron ()
{
    KVector orbitNormal(KikiNeutronOrbits[neutrons.size()][0],
                        KikiNeutronOrbits[neutrons.size()][1],
                        KikiNeutronOrbits[neutrons.size()][2]);

    KikiNeutron * newNeutron = new KikiNeutron(orbitNormal, KikiNeutronOrbits[neutrons.size()][3]);
    neutrons.push_back(newNeutron);
}

// __________________________________________________________________________________________________
#ifdef KIKI_OLD_STATUS 
void KikiHealthAtom::newCellMate ( KikiObject * object )
{
    if (object->getClassId() >= KikiBot::classId())
    {
        ((KikiBot*)object)->getStatus()->addHealth(neutrons.size()/9.0);
        startTimer (200); // atom digest action
    }
}

// __________________________________________________________________________________________________
void KikiEnergyAtom::newCellMate ( KikiObject * object )
{
    if (object->getClassId() >= KikiBot::classId())
    {
        ((KikiBot*)object)->getStatus()->addEnergy(neutrons.size()/9.0);
        startTimer (200); // atom digest action
    }
}
#endif

// __________________________________________________________________________________________________
void KikiAtom::initAction ( KikiAction * action )
{
    Controller.sound->playSound(KikiSound::ATOM_DIGEST);
}

// __________________________________________________________________________________________________
void KikiAtom::performAction ( KikiAction * action )
{
    setValue (1.0 - action->getRelativeTime());
}

// __________________________________________________________________________________________________
void KikiAtom::actionFinished ( KikiAction * action )
{
    delete this;
}

// __________________________________________________________________________________________________
void KikiAtom::setValue ( float v )
{ 
    value = kMin(kMax(0.0, v), 1.0);
    nucleus_size = value/2.0;

    while (value * num_neutrons < neutrons.size())
    {
        deleteNeutron ();
    }
    while (floor(value * num_neutrons) > neutrons.size())
    {
        addNeutron ();
    }
}

// __________________________________________________________________________________________________
void KikiAtom::render ()
{
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

    getNucleusColor().glColor();
    kDisplaySolidSphere(nucleus_size/2.0); // nucleus (is this the correct spelling ?)

    std::vector<KikiNeutron*>::iterator neutronIter = neutrons.begin();

    getNeutronColor().glColor();

    while (neutronIter != neutrons.end())
    {
        (*neutronIter)->display();
        neutronIter++;
    }
    
    glPopMatrix();
    glPopAttrib();
}
