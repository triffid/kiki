/*
 *  KSelectable.cpp
 *  kodisein
 */

#include "KSelectable.h"

KDL_CLASS_INTROSPECTION_1 (KSelectable,KPickable)

// --------------------------------------------------------------------------------------------------------
KSelectable::KSelectable () : KPickable ()
{
    selected = false;
}



