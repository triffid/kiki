/*
 *  KikiWire.cpp
 *  kiki
 */

#include "wire.h"
#include "KikiWire.h"
#include "KikiBillBoard.h"
#include "KikiSwitch.h"
#include "KikiController.h"
#include "KikiWorld.h"

#include <KProjection.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiWire, KikiObject )
KIKI_OBJECT_VALUES_1 		( KikiWire, false, light )

static int SWITCH_OFF_EVENT;
static int SWITCH_ON_EVENT;
static int SWITCHED_EVENT;

// __________________________________________________________________________________________________
KikiWire::KikiWire (int f, int connection_dirs) : KikiObject ()
{
    connections = connection_dirs;
    active	= false;
    value	= 1.0;
    face	= f;

    SWITCH_OFF_EVENT = addEventWithName ("off");
    SWITCH_ON_EVENT  = addEventWithName ("on");
    SWITCHED_EVENT   = addEventWithName ("switched");
}

// __________________________________________________________________________________________________
void KikiWire::updateActive ()
{
    std::vector<KikiWire*> neighbors = getNeighborWires();
    for (std::vector<KikiWire*>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++)
    {
        if ((*iter)->active)
        {
            setActive (true);
        }
    }
}

// __________________________________________________________________________________________________
void KikiWire::setActive ( bool a )
{
    if (active != a)
    {
        active = a;
        std::vector<KikiWire*> neighbors = getNeighborWires();

        bool active_neighbor = false;
        if (active)
        {
            for (std::vector<KikiWire*>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++)
            {
                if ((*iter)->active)
                {
                    active_neighbor = true;
                    break;
                }
            }
        }
        
        for (std::vector<KikiWire*>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++)
        {
            (*iter)->setActive (active);
        }

        KikiSwitch * cellSwitch = (KikiSwitch*)Controller.world->getObjectOfTypeAtPos 
                                                    (KikiSwitch::classId(), getPos ());
        if (cellSwitch)
        {
            cellSwitch->setActive (active);
        }

        events[active ? SWITCH_ON_EVENT : SWITCH_OFF_EVENT]->triggerActions();
        events[SWITCHED_EVENT]->triggerActions();
    }
} 

// __________________________________________________________________________________________________
std::vector<KikiWire*> KikiWire::getNeighborWires ()
{
    std::vector<KikiWire*> neighbor_wires;
    std::vector<KVector> point_list = getConnectionPoints();
    std::vector<KVector> neighbor_dirs;
    
    KQuaternion rot = KikiFace::orientationForFace (face);
    KVector n = KikiFace::normalVectorForFace (face);

    neighbor_dirs.push_back (KVector (0,0,0));
    
    if (connections & RIGHT) 
    {
        neighbor_dirs.push_back (rot.rotate (KVector (1,0,0)));
        neighbor_dirs.push_back (rot.rotate (KVector (1,0,0)) + n);
    }
    if (connections & LEFT)  
    {
        neighbor_dirs.push_back (rot.rotate (KVector (-1,0,0)));
        neighbor_dirs.push_back (rot.rotate (KVector (-1,0,0)) + n);
    }
    if (connections & UP)    
    {
        neighbor_dirs.push_back (rot.rotate (KVector (0,1,0)));
        neighbor_dirs.push_back (rot.rotate (KVector (0,1,0)) + n);
    }
    if (connections & DOWN)  
    {
        neighbor_dirs.push_back (rot.rotate (KVector (0,-1,0)));
        neighbor_dirs.push_back (rot.rotate (KVector (0,-1,0)) + n);
    }
    
    for (int i = 0; i < (int)neighbor_dirs.size(); i++)
    {
        KikiObjectList neighbors = Controller.world->getObjectsOfTypeAtPos 
                                    (getClassId(), position + neighbor_dirs[i]);
        for (KikiObjectIter iter = neighbors.begin(); iter != neighbors.end(); iter++)
        {
            if (*iter == this) continue;
            std::vector<KVector> neighbor_points = ((KikiWire*)*iter)->getConnectionPoints();
            for (std::vector<KVector>::iterator point = point_list.begin(); 
                    point != point_list.end(); point++)
            {
                for (std::vector<KVector>::iterator neighbor_point = neighbor_points.begin(); 
                        neighbor_point != neighbor_points.end(); neighbor_point++)
                {
                    if (((*neighbor_point) - (*point)).length() < 0.1)
                    {
                        neighbor_wires.push_back ((KikiWire*)*iter);
                    }
                }
            }
        }
    }
  
    return neighbor_wires;
}

// __________________________________________________________________________________________________
std::vector<KVector> KikiWire::getConnectionPoints ()
{
    std::vector<KVector> point_list;
    
    KVector to_border = 0.5 * KikiFace::normalVectorForFace (face);
    KQuaternion rot = KikiFace::orientationForFace (face);

    if (connections & RIGHT) 
    {
        point_list.push_back (position + to_border + rot.rotate(KVector (0.5, 0, 0)));
    }
    if (connections & LEFT)
    {
        point_list.push_back (position + to_border + rot.rotate(KVector (-0.5, 0, 0)));
    }
    if (connections & UP) 
    {
        point_list.push_back (position + to_border + rot.rotate(KVector (0, 0.5, 0)));
    }
    if (connections & DOWN)
    {
        point_list.push_back (position + to_border + rot.rotate(KVector (0, -0.5, 0)));
    }
    
    return point_list;
}

// __________________________________________________________________________________________________
void KikiWire::display ()
{
    KikiObject::preDisplay();
    KVector face_normal = KikiFace::normalVectorForFace (face);
    (0.5 * face_normal).glTranslate();

    glPushMatrix();

    KMatrix mat(KikiFace::orientationForFace (face));
    mat.glMultMatrix();    

    colors[KikiWire_base_color].glColor();

    render_wire;

    glDisable (GL_CULL_FACE);
    float h = 0.05;
    glNormal3f(0.0, 0.0, 1.0);
    if (connections & RIGHT) 	glRectf ( 0.0, -h, 0.5, h);
    if (connections & LEFT)  	glRectf (-0.5, -h, 0.0, h);
    if (connections & UP) 	glRectf (-h,  0.0, h, 0.5);
    if (connections & DOWN) 	glRectf (-h, -0.5, h, 0.0);
    glEnable (GL_CULL_FACE);
    
    glPopMatrix();
    
    if (active)
    {
        KColor c (colors[KikiWire_light_color]);
        c.setAlpha (value);
        c.glColor();
    
        (face_normal * -0.1).glTranslate();
        
        KikiBillBoard::displayTextureWithSize 
                        (Controller.world->getTextureId(KikiWorld::TEXTURE_GRADIENT), 0.15);
    }

    KikiObject::postDisplay();
}

