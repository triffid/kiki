/*
 *  KikiNeutron.cpp
 *  kiki
 */

#include "KikiNeutron.h"
#include "KikiAtom.h"
#include "KikiController.h"

#include <KDisplayTools.h>

// __________________________________________________________________________________________________
KikiNeutron::KikiNeutron ( const KVector & orbitNormal, float startAngle )
{
    start_angle = startAngle;
    
    // ............................................................. init the orbit rotation
    KVector orbit_normal (orbitNormal.normal());
    KVector zVector(0.0, 0.0, 1.0);
    
    angle = zVector.angle(orbitNormal);
    
    if (angle != 0) // normal is not aligned with z-axis
    {
        orientation = KQuaternion::rotationAroundVector (angle, zVector.cross (orbit_normal));    
    }
}

// __________________________________________________________________________________________________
void KikiNeutron::display ()
{
    glPushMatrix();
    
    orientation.glRotate();
    
    angle += Controller.getRelativeDelta() * 360.0;
    glRotatef(start_angle + angle, 0.0, 0.0, 1.0);

    glTranslatef(0.4, 0.0, 0.0);
    kDisplaySolidSphere(0.1);
    
    glPopMatrix();
}
