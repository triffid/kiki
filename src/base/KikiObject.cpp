/*
 *  KikiObject.cpp
 *  kiki
 */

#include "KikiObject.h"
#include "KikiController.h"
#include "KikiWorld.h"

#include <KProjection.h>
#include <KConsole.h>
#include <KDisplayTools.h>

#include <algorithm>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_2 	(KikiObject,    KikiActionObject, KPickable)
KDL_CLASS_INTROSPECTION_1 	(KikiTmpObject, KikiObject)

KIKI_OBJECT_VALUES  		(KikiObject,    false)
KIKI_OBJECT_VALUES 		(KikiTmpObject, true)

// --------------------------------------------------------------------------------------------------------
KikiObject::KikiObject () : KikiActionObject(), KNotificationObject (), KPickable ()
{
    move_action = NULL;
    name = NULL;
}

// --------------------------------------------------------------------------------------------------------
KikiObject::~KikiObject ()
{
    Controller.world->removeObject (this);

    notifyReceiversType (KIKI_NOTIFICATION_OBJECT_DELETED);

    if (name) delete name;
}

// __________________________________________________________________________________________________
void KikiTmpObject::render ()
{
    if (Controller.world->flags[KikiWorld::DISPLAY_DOTS]) kDisplaySolidSphere (0.1); 
}

// __________________________________________________________________________________________________
void KikiObject::preDisplay ()
{
    loadId();

    glPushAttrib (GL_CURRENT_BIT | GL_ENABLE_BIT);
    glPushMatrix ();

    current_position.glTranslate();

    if (picked)
    {
        glDisable (GL_LIGHTING);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        kDisplayWireCube (1.0);
        glEnable (GL_LIGHTING);
    }
}

// __________________________________________________________________________________________________
void KikiObject::display ()
{
    preDisplay();
    render();    
    postDisplay();
}

// __________________________________________________________________________________________________
void KikiObject::postDisplay ()
{
    glPopMatrix();
    glPopAttrib();
}
