/*
 *  KikiPageText.cpp
 *  kiki
 */

#include "KikiPageText.h"
#include "KikiTextLine.h"
#include "KikiController.h"
#include "KikiSound.h"

#include <KConsole.h>
#include <KKey.h>

// __________________________________________________________________________________________________
KikiPageText::KikiPageText ( const std::string & pageText, bool nextPage, bool previousPage ) 
    : KikiScreenText ()
{
    Controller.sound->playSound (KikiSound::MENU_FADE);

    setText (pageText, bright_color);
    
    addAction (new KikiAction (this, ACTION_NEXT_PAGE,     "next"));
    addAction (new KikiAction (this, ACTION_PREVIOUS_PAGE, "previous"));

    if (nextPage) addEventWithName ("next");
    if (previousPage) addEventWithName ("previous");

    show();
}

// __________________________________________________________________________________________________
void KikiPageText::actionFinished ( KikiAction * action )
{    
    switch (action->getId())
    {
        case ACTION_NEXT_PAGE:
        
            if (getEventWithName ("next"))
            {
                getEventWithName ("next")->triggerActions();
            }
            Controller.timer_event->addAction (getActionWithId (ACTION_DELETE));
            
            break;
            
        case ACTION_PREVIOUS_PAGE:
        
            if (getEventWithName ("previous"))
            {
                getEventWithName ("previous")->triggerActions();
            }
            Controller.timer_event->addAction (getActionWithId (ACTION_DELETE));

            break;
            
        default:
        
            KikiScreenText::actionFinished (action);
    }
}

// __________________________________________________________________________________________________
bool KikiPageText::handleKey ( const KKey & key )
{   
    bool retval = false;
    std::string keyName = key.getUnmodifiedName ();
    
    if (keyName == "DOWN" || keyName == "PAGEDOWN" || keyName == "RIGHT" || 
        keyName == "RETURN" || keyName == "SPACE")
    {
        if (getEventWithName ("next"))
        {
            Controller.sound->playSound (KikiSound::MENU_SELECT);
            startTimedAction (getActionWithId (ACTION_NEXT_PAGE));
        }
        else
        {
            KikiEvent * prevEvent = getEventWithName ("previous");
            if (prevEvent)
            {
                events.erase (std::find (events.begin(), events.end(), prevEvent));
                delete prevEvent;
            }
            Controller.sound->playSound (KikiSound::MENU_ABORT);
            Controller.timer_event->addAction (getActionWithId (ACTION_HIDE));
        }
        retval = true;
    }
    else if (keyName == "UP" || keyName == "PAGEUP" || keyName == "LEFT")
    {
        if (getEventWithName ("previous"))
        {
            Controller.sound->playSound (KikiSound::MENU_SELECT);
            startTimedAction (getActionWithId (ACTION_PREVIOUS_PAGE));
        }
        retval = true;
    }
    else
    {
        if (keyName == "ESCAPE")  retval = true;
        
        KikiEvent * nextEvent = getEventWithName ("next");
        if (nextEvent)
        {
            events.erase (std::find (events.begin(), events.end(), nextEvent));
            delete nextEvent;
        }
        KikiEvent * prevEvent = getEventWithName ("previous");
        if (prevEvent)
        {
            events.erase (std::find (events.begin(), events.end(), prevEvent));
            delete prevEvent;
        }
        Controller.sound->playSound (KikiSound::MENU_ABORT);
        Controller.timer_event->addAction (getActionWithId (ACTION_HIDE));
    }
        
    return retval;
}

// __________________________________________________________________________________________________
void KikiPageText::display ()
{
    list_color = bright_color;
    
    if (fade_value != 1.0)
    {
        color = KikiText::colors[list_color];
        color.setAlpha (fade_value);
        color.glColor();
        list_color = -1;
    }
    else
    {
        KikiText::colors[list_color].glColor();
    }
    
    //KikiText::colors[list_color].glColor();

    for (int index = 0; index < (int)text_lines.size(); index++)
    {        
        text_lines[index]->display();
    }
}

