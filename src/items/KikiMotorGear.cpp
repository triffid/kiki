/*
 *  KikiMotorGear.cpp
 *  kiki
 */

#include "KikiMotorGear.h"
#include "gear.h"
#include "motor.h"

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiMotorGear, KikiGear )
KIKI_OBJECT_VALUES 		( KikiMotorGear, true )

// __________________________________________________________________________________________________
KikiMotorGear::KikiMotorGear ( int face ) : KikiGear (face) 
{
    setActive (true);
}

// __________________________________________________________________________________________________
void KikiMotorGear::render () 
{
    colors[0].glColor();

    render_motor;
    
    if (active)
    {
        glRotatef (clockwise ? angle : -angle, 0.0, 0.0, 1.0);
    }

    KikiGear::getObjectColor(0).glColor();
        
    glTranslatef (0.0, 0.0, 0.4);

    render_gear;
}
