/*
 *  KikiCellText.cpp
 *  kiki
 */

#include "KikiCellText.h"
#include <KConsole.h>
#include <KDisplayTools.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiCellText,	KikiObject )
KIKI_OBJECT_VALUES 		( KikiCellText, false )

// __________________________________________________________________________________________________
KikiCellText::KikiCellText (const std::string & text, float height, bool center, int colorIndex ) 
    : KikiObject(), KikiText (text, center, colorIndex)
{
    offset	= NULL;
    cell_height = height;
}

// __________________________________________________________________________________________________
void KikiCellText::setOffset ( const KVector & v )
{ 
    if (offset) 
    {
        delete offset; 
    }
    offset = new KVector(v); 
}

// __________________________________________________________________________________________________
void KikiCellText::display ()
{
    loadId();

    glPushAttrib (GL_CURRENT_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);
    glPushMatrix ();
    
    glTranslatef (position[X], position[Y], position[Z]);
    KMatrix (current_orientation).glMultMatrix();
    if (offset)
    {
        glTranslatef ((*offset)[X], (*offset)[Y], (*offset)[Z]);
    }
    
    float factor = cell_height/height;
    glScalef (factor, factor, factor);
    
    if (picked)
    {
        glPushAttrib (GL_CURRENT_BIT);
        glDisable (GL_LIGHTING);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        glPushMatrix();
        glScalef (width, height, 1);
        kDisplayWireCube (1.0);
        glPopMatrix();
        glEnable (GL_LIGHTING);
        glPopAttrib();
    }
    
    KikiText::display();
    
    glPopMatrix();
    glPopAttrib();
}
    
