/*
 *  KLightingProjection.cpp
 *  kodisein
 */

#include "KLightingProjection.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KLightingProjection, KPerspectiveProjection)

// -------------------------------------------------------------------------------------------------------- 
// -------------------------------------------------------------------------------------------------------- 
KLightingProjection::KLightingProjection ( GLfloat f, GLfloat zn, GLfloat zf ) 
    : KPerspectiveProjection (f, zn, zf)
{
    light.setDirection (KVector(0.0, 0.0, -1.0));
    light.setCutoff(90.0);
}

// -------------------------------------------------------------------------------------------------------- 
KLightingProjection::KLightingProjection ( const KProjection & p ) : KPerspectiveProjection (p)
{
}

// -------------------------------------------------------------------------------------------------------- 
KLightingProjection::KLightingProjection ( const KLightingProjection & p ) : KPerspectiveProjection (p)
{
    light = p.light;
}

// --------------------------------------------------------------------------------------------------------
KProjection * KLightingProjection::copy () const
{
    return new KLightingProjection (*this);
}
 
// --------------------------------------------------------------------------------------------------------
void KLightingProjection::apply ()
{
    KPerspectiveProjection::apply();

    KVector pos = getPosition() + light_offset;
    light.setDirection(-getZVector());
    light.setPosition (KVector(pos[X], pos[Y], pos[Z], 1.0)); // positional light source
    light.initialize  (GL_LIGHT0);
}


