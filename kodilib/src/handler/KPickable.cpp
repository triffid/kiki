/*
 *  KPickable.cpp
 *  kodisein
 */

#include "KPickable.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#ifdef _WIN32
#include <GLUT/glut.h>
#endif
#include <GL/gl.h>
#endif

KDL_CLASS_INTROSPECTION (KPickable)

// --------------------------------------------------------------------------------------------------------
KPickable::KPickable ()
{
    picked = false;
    pickable_id = 0;
}

// --------------------------------------------------------------------------------------------------------
void KPickable::loadId ()
{
    GLint names;
    glGetIntegerv(GL_NAME_STACK_DEPTH, &names);

    if (names) glLoadName(pickable_id);
    else glPushName(pickable_id);
}

// --------------------------------------------------------------------------------------------------------
void KPickable::unloadId ()
{
    GLint names;
    glGetIntegerv(GL_NAME_STACK_DEPTH, &names);

    if (names) glLoadName(0);
    else glPushName(0);
}
