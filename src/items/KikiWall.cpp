/*
 *  KikiWall.cpp
 *  kiki
 */

#include "KikiWall.h"

#include <KDisplayTools.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiWall, KikiObject )
KIKI_OBJECT_VALUES_1 		( KikiWall, true, plate )

// __________________________________________________________________________________________________
void KikiWall::render ()
{
    glDisable(GL_LIGHTING);
    colors[KikiWall_base_color].glColor();
    glDepthMask(false);
    kDisplaySolidCube(1.0);
    glDepthMask(true);
    float s = 0.45;
    float d = 0.5;

    colors[KikiWall_plate_color].glColor();
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);
    
        glNormal3f (0.0, 0.0, 1.0);
        glVertex3f ( s, -s, d);
        glVertex3f ( s,  s, d);
        glVertex3f (-s,  s, d);
        glVertex3f (-s, -s, d);

        glNormal3f (0.0, 0.0, -1.0);
        glVertex3f (-s, -s, -d);
        glVertex3f (-s,  s, -d);
        glVertex3f ( s,  s, -d);
        glVertex3f ( s, -s, -d);
        
	glNormal3f (0.0, 1.0, 0.0);
        glVertex3f (-s, d, -s);
        glVertex3f (-s, d,  s);
        glVertex3f ( s, d,  s);
        glVertex3f ( s, d, -s);

        glNormal3f (0.0, -1.0, 0.0);
        glVertex3f ( s, -d, -s);
        glVertex3f ( s, -d,  s);
        glVertex3f (-s, -d,  s);
        glVertex3f (-s, -d, -s);

        glNormal3f (1.0, 0.0, 0.0);
        glVertex3f (d,  s, -s);
        glVertex3f (d,  s,  s);
        glVertex3f (d, -s,  s);
        glVertex3f (d, -s, -s);

	glNormal3f (-1.0, 0.0, 0.0);
        glVertex3f (-d, -s, -s);
        glVertex3f (-d, -s,  s);
        glVertex3f (-d,  s,  s);
        glVertex3f (-d,  s, -s);

    glEnd();       
}

