/*
 *  KikiGate.cpp
 *  kiki
 */

#include "KikiGate.h"
#include "KikiWorld.h"
#include "KikiPlayer.h"
#include "KikiSound.h"

#include <KDisplayTools.h>
#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiGate, KikiSwitch )
KIKI_OBJECT_VALUES_1 		( KikiGate, false, sphere )

static int ENTER_EVENT;

// __________________________________________________________________________________________________
KikiGate::KikiGate ( bool open ) : KikiSwitch (open)
{
    ENTER_EVENT = addEventWithName ("enter");
    value = 0.0;
    getActionWithId(ACTION_ROTATE)->setDuration(3000);
    sound_on  = KikiSound::GATE_OPEN;
    sound_off = KikiSound::GATE_CLOSE;
}

// __________________________________________________________________________________________________
void KikiGate::newCellMate ( KikiObject * object )
{	
    if (object == Controller.getPlayer() && active) // if new cell mate is player and gate is active
    {
        Controller.sound->playSound (KikiSound::GATE_WARP);
        events[ENTER_EVENT]->triggerActions();	    // trigger actions
    }
}

// __________________________________________________________________________________________________
void KikiGate::renderBar ( float r, float b, float h )
{
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0,1,0);
    glVertex3f(-r, h, -r); glVertex3f(-b, h, -b); 
    glVertex3f( r, h, -r); glVertex3f( b, h, -b); 
    glVertex3f( r, h,  r); glVertex3f( b, h,  b); 
    glVertex3f(-r, h,  r); glVertex3f(-b, h,  b); 
    glVertex3f(-r, h, -r); glVertex3f(-b, h, -b);     
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0,-1,0);
    glVertex3f(-b, -h, -b); glVertex3f(-r, -h, -r); 
    glVertex3f( b, -h, -b); glVertex3f( r, -h, -r); 
    glVertex3f( b, -h,  b); glVertex3f( r, -h,  r); 
    glVertex3f(-b, -h,  b); glVertex3f(-r, -h,  r); 
    glVertex3f(-b, -h, -b); glVertex3f(-r, -h, -r);  
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glVertex3f(-r, -h, -r); glVertex3f(-r,  h, -r); 
    glVertex3f( r,  h, -r); glVertex3f( r, -h, -r); 
    glNormal3f(1,0,0);
    glVertex3f( r, -h, -r); glVertex3f( r,  h, -r); 
    glVertex3f( r,  h,  r); glVertex3f( r, -h,  r);  
    glNormal3f(0,0,1);
    glVertex3f( r, -h,  r); glVertex3f( r,  h,  r); 
    glVertex3f(-r,  h,  r); glVertex3f(-r, -h,  r); 
    glNormal3f(-1,0,0);
    glVertex3f(-r, -h,  r); glVertex3f(-r,  h,  r); 
    glVertex3f(-r,  h, -r); glVertex3f(-r, -h, -r);   
    glNormal3f(0,0,1);
    glVertex3f(-b,  h, -b); glVertex3f(-b, -h, -b); 
    glVertex3f( b, -h, -b); glVertex3f( b,  h, -b);  
    glNormal3f(-1,0,0);
    glVertex3f( b,  h, -b); glVertex3f( b, -h, -b); 
    glVertex3f( b, -h,  b); glVertex3f( b,  h,  b);  
    glNormal3f(0,0,-1);
    glVertex3f( b,  h,  b); glVertex3f( b, -h,  b); 
    glVertex3f(-b, -h,  b); glVertex3f(-b,  h,  b);  
    glNormal3f(1,0,0);
    glVertex3f(-b,  h,  b); glVertex3f(-b, -h,  b); 
    glVertex3f(-b, -h, -b); glVertex3f(-b,  h, -b);   
    glEnd();
}

// __________________________________________________________________________________________________
void KikiGate::render ()
{
    KColor gate_color = colors[KikiGate_base_color];
    if (active == false)
    {
        gate_color.setAlpha (gate_color.getAlpha()/4.0);
    }
    
    gate_color.glColor();
    
    float v = sin(DEG2RAD(angle));
    float av = kAbs(v);
    float b = 0.29 + av * 0.1;
    float h = 0.1  - av * 0.05;
    float r = 0.49;
    float t = v * (0.49 - h);
    float s = 1.0 - av * 0.5; 

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPushMatrix();
    glScalef(s, 1.0, s);
    glTranslatef (0, t, 0);
    glPolygonOffset(0.1, 0.1);
    renderBar (r, b, h);
    glTranslatef (0, -2*t, 0);
    glPolygonOffset(0.2, 0.2);
    renderBar (r, b, h);
    glPopMatrix();

    glPushMatrix();
    glRotatef (90, 1.0, 0.0, 0.0);
    glScalef(s, 1.0, s);
    glTranslatef (0, t, 0);
    glPolygonOffset(0.3, 0.3);
    renderBar (r, b, h);
    glTranslatef (0, -2*t, 0);
    glPolygonOffset(0.4, 0.4);
    renderBar (r, b, h);
    glPopMatrix();

    glPushMatrix();
    glRotatef (-90, 0.0, 0.0, 1.0);
    glScalef(s, 1.0, s);
    glTranslatef (0, t, 0);
    glPolygonOffset(0.5, 0.5);
    renderBar (r, b, h);
    glTranslatef (0, -2*t, 0);
    glPolygonOffset(0.6, 0.6);
    renderBar (r, b, h);
    glPopMatrix();
    glDisable(GL_POLYGON_OFFSET_FILL);

    if (active)
    {
        colors[KikiGate_sphere_color].glColor();
        kDisplaySolidSphere(0.20);
    }
}

