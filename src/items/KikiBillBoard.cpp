/*
 *  KikiBillBoard.cpp
 *  kiki
 */

#include "KikiBillBoard.h"
#include "KikiController.h"
#include "KikiWorld.h"

#include <KProjection.h>
#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiBillBoard, KikiObject )
KIKI_OBJECT_VALUES 		( KikiBillBoard, false )

// __________________________________________________________________________________________________
KikiBillBoard::KikiBillBoard () : KikiObject ()
{
    size = 1.0;
}

// __________________________________________________________________________________________________
void KikiBillBoard::displayTextureWithSize ( GLuint textureId, float size )
{
    glPushAttrib (GL_TEXTURE_BIT | GL_LIGHTING_BIT);
    glDisable (GL_LIGHTING);
    glEnable (GL_TEXTURE_2D);

    glPushMatrix();

    KQuaternion quat = Controller.world->getProjection()->getQuaternion();
    KMatrix (quat).glMultMatrix();

    glBindTexture (GL_TEXTURE_2D, textureId);

    float w = size/2.0;
    float h = size/2.0;
    
    glBegin (GL_QUADS);
        glNormal3f (0,0,1);
        glTexCoord2f (0.0f, 0.0f); glVertex2f (-w, h);
        glTexCoord2f (0.0f, 1.0f); glVertex2f (-w,-h);
        glTexCoord2f (1.0f, 1.0f); glVertex2f ( w,-h);
        glTexCoord2f (1.0f, 0.0f); glVertex2f ( w, h);
    glEnd();
    
    glPopMatrix();
    
    glDisable (GL_TEXTURE_2D);
    glEnable (GL_LIGHTING);
    glPopAttrib();
}

// __________________________________________________________________________________________________
void KikiBillBoard::display()
{
    glPushMatrix();
    getColor().glColor();

    current_position.glTranslate();
    displayTextureWithSize (getTextureId(), size);
    glPopMatrix();
}

