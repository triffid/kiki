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
KikiStone::KikiStone () : KikiPushable ()
{                            
}

// __________________________________________________________________________________________________
void KikiStone::render ()
{
    colors[KikiStone_base_color].glColor();
    kDisplaySolidCube (0.98);
}

