/*
 *  KikiScreenText.cpp
 *  kiki
 */

#include "KikiScreenText.h"
#include "KikiTextLine.h"
#include "KikiController.h"

#include <KDisplayTools.h>
#include <KConsole.h>
#include <KLightingProjection.h>

// __________________________________________________________________________________________________
KikiScreenText::KikiScreenText () : KPickHandler (), KKeyHandler (), KikiText (), KikiActionObject ()
{
    depth = INT_MAX-11; // one below console

    Controller.addPickHandler (this);
    KEventHandler::setFocusKeyHandler (this);

    fade_value = 0.0;
    
    addEventWithName ("hide");
    
    addAction (new KikiAction (this, ACTION_SHOW,   "show",  500));
    addAction (new KikiAction (this, ACTION_HIDE,   "hide",  500));
    addAction (new KikiAction (this, ACTION_DELETE, "delete"));    
    
    projection = new KLightingProjection (60.0, 0.1, 600.0);
}

// __________________________________________________________________________________________________
KikiScreenText::~KikiScreenText ()
{
    Controller.removePickHandler (this);
    KEventHandler::removeFocusKeyHandler (this);
}

// __________________________________________________________________________________________________
void KikiScreenText::show ()
{
    startTimedAction (getActionWithId (ACTION_SHOW));
}

// __________________________________________________________________________________________________
void KikiScreenText::addText ( const std::string & str, float scaleFactor )
{
    KikiText::addText (str, scaleFactor); 

    // ............................................................................ adjust projection    
    projection->KMatrix::reset();
    projection->translate (0.0, 0.0, kMax(width, height));
    ((KLightingProjection*)projection)->setLightOffset (KVector (-width/2.0, height, 0.0));
    projection->setZFar (kMax(width, height) + 10);
    projection->setZNear (kMax(width, height) - 10);
}

// __________________________________________________________________________________________________
void KikiScreenText::performAction ( KikiAction * action )
{    
    if (action->getId() == ACTION_SHOW)
    {
        fade_value = action->getRelativeTime();
    }
    else if (action->getId() == ACTION_HIDE)
    {
        fade_value =  1.0 - action->getRelativeTime();
    }
}

// __________________________________________________________________________________________________
void KikiScreenText::actionFinished ( KikiAction * action )
{ 
    switch (action->getId())
    {
        case ACTION_HIDE:
   
            getEventWithName ("hide")->triggerActions();

            Controller.timer_event->addAction (getActionWithId (ACTION_DELETE));
            break;

        case ACTION_DELETE:

            delete this;
            break;
        
        case ACTION_SHOW:

            fade_value = 1.0;
            break;
    }
}

// __________________________________________________________________________________________________
bool KikiScreenText::handleKey ( const KKey & key )
{   
    startTimedAction (getActionWithId (ACTION_HIDE));
    return false;
}

// __________________________________________________________________________________________________
void KikiScreenText::display ()
{
    if (fade_value != 1.0)
    {
        color.setAlpha (fade_value);
    }
    
    KikiText::display();
}

// __________________________________________________________________________________________________
void KikiScreenText::display ( int )
{
    glPushAttrib (GL_CURRENT_BIT);

    glClear (GL_DEPTH_BUFFER_BIT);

    projection->initProjection();

    glDepthMask(false);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    
    glColor4f (0.0, 0.0, 0.0, fade_value * 0.5);
    glTranslatef (0,0,-bevel_depth);
    glRectf (-getWidth()*0.6, -getHeight()*0.7, getWidth()*0.6, getHeight()*0.7);
    
    glPopMatrix();
    glEnable (GL_LIGHTING);
    glDepthMask(true);
    
    ((KikiText*)this)->display();
    glPopAttrib();
}
