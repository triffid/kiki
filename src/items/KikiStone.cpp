/*
 *  KikiStone.cpp
 *  kiki
 */

#include "KikiStone.h"

#include <KDisplayTools.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiStone, KikiPushable )
KIKI_OBJECT_VALUES 		( KikiStone, true )

// __________________________________________________________________________________________________
KikiStone::KikiStone (KColor * c, bool s) : KikiPushable ()
{  
	slippery = s;
	color = NULL;
	if (c)
		color = new KColor(*c);
}

// __________________________________________________________________________________________________

KikiStone::~KikiStone ()
{  
	if (color)
		delete color;
}

// __________________________________________________________________________________________________
void KikiStone::render ()
{
	if (color)
		color->glColor();
	else
		colors[KikiStone_base_color].glColor();
	if (isSlippery())
	{
		float s = 0.38f;
		float o = 0.5-(s+0.02f)/2;
		glPushMatrix();
		glTranslated(o, o, o);
		kDisplaySolidCube (s);
		glTranslated(-2*o, 0.0, 0.0);
		kDisplaySolidCube (s);
		glTranslated(0.0, -2*o, 0.0);
		kDisplaySolidCube (s);
		glTranslated(2*o, 0.0, 0.0);
		kDisplaySolidCube (s);
		glTranslated(0.0, 0.0, -2*o);
		kDisplaySolidCube (s);
		glTranslated(0.0, 2*o, 0.0);
		kDisplaySolidCube (s);
		glTranslated(-2*o, 0.0, 0.0);
		kDisplaySolidCube (s);
		glTranslated(0.0, -2*o, 0.0);
		kDisplaySolidCube (s);
		glPopMatrix();
	}
	else
	{
		kDisplaySolidCube (0.98);
	}
}

