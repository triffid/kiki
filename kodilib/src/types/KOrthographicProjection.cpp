/*
 *  KOrthographicProjection.cpp
 *  kodisein
 */

#include "KOrthographicProjection.h"
#include "KConsole.h"

#define K_INCLUDE_GLU
#include "KIncludeTools.h"

KDL_CLASS_INTROSPECTION_1 (KOrthographicProjection, KProjection)

// --------------------------------------------------------------------------------------------------------
KOrthographicProjection::KOrthographicProjection (GLfloat zn, GLfloat zf) : KProjection ( zn, zf)
{
}

// --------------------------------------------------------------------------------------------------------
KOrthographicProjection::KOrthographicProjection ( const KProjection & p ) : KProjection (p)
{
}

// --------------------------------------------------------------------------------------------------------
KProjection * KOrthographicProjection::copy() const
{
    return new KOrthographicProjection(*this);
}
 
// --------------------------------------------------------------------------------------------------------
void KOrthographicProjection::apply ()
{
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    
    if (fov == 0)
    {
        gluOrtho2D( -0.5, vp[2]-0.5, -vp[3]+0.5, +0.5);
    }
    else
    {
        GLfloat sinus   = sin(DEG2RAD(fov/2.0));
        GLfloat ar	= getCurrentAspectRatio();
        GLfloat zf	= zfar / 10.0;

        glOrtho( -sinus * ar * zf, sinus * ar * zf, -sinus * zf, sinus * zf, znear, zfar);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(matrix);
}



