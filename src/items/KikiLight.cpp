/*
 *  KikiLight.cpp
 *  kiki
 */

#include "KikiLight.h"
#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiBillBoard.h"

#include <KConsole.h>

KDL_CLASS_INTROSPECTION_1 	( KikiLight, KikiObject )
KIKI_OBJECT_VALUES_3 		( KikiLight, false, diffuse, specular, halo )

// __________________________________________________________________________________________________
KikiLight::KikiLight () : KikiObject(), KLight ()
{
    radius = 4.0;
    setup();
}

// __________________________________________________________________________________________________
KikiLight::KikiLight ( const KVector & pos, float r ) : KikiObject(), KLight ()
{
    radius = r;
    //spot_position = position;
    setPosition (pos);
    spot_position[W] = 1.0;
    setup();
    Controller.world->addObject (this);
}

// __________________________________________________________________________________________________
KikiLight::~KikiLight ()
{
    if (light_number)
    {
        glDisable(light_number);
    }
}

// __________________________________________________________________________________________________
void KikiLight::setup ()
{
    halo_radius           = 1.0;
    quadratic_attenuation = 1.0/(radius*radius);

    ambient_color  = colors[KikiLight_base_color];
    diffuse_color  = colors[KikiLight_diffuse_color];
    specular_color = colors[KikiLight_specular_color];

    initialize ();    
}

// __________________________________________________________________________________________________
void KikiLight::setPosition ( const KVector & pos )
{
    KLight::setPosition (KVector(pos[X], pos[Y], pos[Z], 1.0));
    KikiObject::setPosition (pos);
}

// __________________________________________________________________________________________________
void KikiLight::display()
{
    if (light_number == 0) return;

    KLight::setPosition (KVector(position[X], position[Y], position[Z], 1.0));

    glDepthMask (false);
    glPushMatrix();
    colors[KikiLight_halo_color].glColor();
    position.glTranslate();
    
    KikiBillBoard::displayTextureWithSize 
                        (Controller.world->getTextureId (KikiWorld::TEXTURE_GRADIENT), 1.0);
    glPopMatrix();
    glDepthMask (true);
}

