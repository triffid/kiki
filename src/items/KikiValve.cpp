/*
 *  KikiValve.cpp
 *  kiki
 */

#include "KikiValve.h"
#include "valve.h"

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiValve, KikiPushable )
KIKI_OBJECT_VALUES 		( KikiValve, true )

// __________________________________________________________________________________________________
KikiValve::KikiValve ( int f ) : KikiPushable () 
{
    face      = f;
    angle     = 0.0; 
    active    = false;
    addAction (new KikiAction (this, ACTION_ROTATE,  "rotation", 2000, KikiAction::REPEAT));
    startTimedAction (getActionWithId (ACTION_ROTATE));
}

// __________________________________________________________________________________________________
void KikiValve::display ()
{ 
    KikiObject::preDisplay();
     
    KMatrix m (KikiFace::orientationForFace (face));
    m.glMultMatrix();

    render();
    
    KikiObject::postDisplay();
}
    
// __________________________________________________________________________________________________
void KikiValve::setPosition ( const KVector & pos )
{
    KikiPushable::setPosition (pos);
    KikiPos p = getPos ();
    int dir = face%3;
    int sum =	((dir == KikiFace::Y || dir == KikiFace::Z) ? p.x : 0) + 
                ((dir == KikiFace::X || dir == KikiFace::Z) ? p.y : 0) + 
                ((dir == KikiFace::X || dir == KikiFace::Y) ? p.z : 0);
    clockwise = sum % 2;
}
           
// __________________________________________________________________________________________________
void KikiValve::performAction ( KikiAction * action )
{
    switch (action->getId())
    {
    	case ACTION_ROTATE:
        
            angle += action->getRelativeDelta() * 360;
            break;
            
        default:
        
            KikiPushable::performAction (action);
    }
}

// __________________________________________________________________________________________________
void KikiValve::render ()
{
    colors[0].glColor();

    glRotatef (clockwise ? angle : -angle, 0.0, 0.0, 1.0);
    render_valve;
}
