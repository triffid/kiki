/*
 *  KikiMenu.cpp
 *  kiki
 */

#include "KikiMenu.h"
#include "KikiTextLine.h"
#include "KikiController.h"
#include "KikiSound.h"

#include <KKey.h>
#include <KConsole.h>
#include <KLightingProjection.h>

// __________________________________________________________________________________________________
// __________________________________________________________________________________________________

KikiMenu::KikiMenu ( int selectedItem ) : KikiScreenText ()
{    
    index_offset = 0;
    circular     = true;

    if (selectedItem < 0)
    {
		active_index = 0;
        Controller.sound->playSound (KikiSound::MENU_FADE);
    }
    else
    {
		active_index = selectedItem;
        getActionWithId (ACTION_SHOW)->setDuration (0);
        getActionWithId (ACTION_HIDE)->setDuration (0);
        fade_value = 1.0;
    }

    addEventWithName ("next");
    addEventWithName ("previous");
    addEventWithName ("changed");
    
    escape_active = true;
    
    show();
}

// __________________________________________________________________________________________________

KikiMenu::~KikiMenu ()
{
  while (menu_items.empty() == false)
  {
    delete menu_items.back();
    menu_items.pop_back();
  }
}

// __________________________________________________________________________________________________

void KikiMenu::setCurrentIndex (int index)
{
	active_index = 0;
}

// __________________________________________________________________________________________________
KikiMenuItem * KikiMenu::newItem ( const std::string & itemText, KikiAction * itemAction )
{
    std::string item_text (itemText);
    std::string event_name (itemText);
    std::string::size_type pos;
    float scale_factor = 1.0;

    KikiMenuItem * menu_item = new KikiMenuItem ();

    if ((pos = item_text.find ("$event(")) != std::string::npos)
    {
        item_text.erase (pos, pos+7);
        event_name = item_text.substr (pos, item_text.find (")", pos));
        item_text.erase (pos, item_text.find (")", pos)+1);
    }
    
    if ((pos = item_text.find ("$no_item")) != std::string::npos)
    {
        item_text.erase (pos, pos+8);
        menu_item->ignore = true;
    }
    else
    {
        addEventWithName (event_name);
        menu_item->event_name = event_name;
        if (itemAction) getEventWithName (event_name)->addAction (itemAction);
    }      
        
    if ((pos = item_text.find ("|")) != std::string::npos)
    {
		std::string valueText(item_text.substr (pos+1, item_text.size()));
		item_text.erase (pos, item_text.size());

		if ((pos = valueText.find("|")) != std::string::npos)
		{
			menu_item->extra_text = new KikiTextLine (valueText.substr (pos+1, valueText.size()), scale_factor);
			valueText.erase (pos, valueText.size());
		}

		menu_item->value_text = new KikiTextLine (valueText, scale_factor);    
    }
    
    menu_item->item_text = new KikiTextLine (item_text);

    return menu_item;
}

// __________________________________________________________________________________________________
void KikiMenu::addItem ( const std::string & itemText, KikiAction * itemAction, bool option )
{  
    menu_items.push_back (newItem (itemText, itemAction));
	menu_items.back()->option = option;
    alignItems();
}

// __________________________________________________________________________________________________
void KikiMenu::alignItems ()
{ 
    // ............................................................................ align text lines
    int numLines = menu_items.size();
    width  = 0.0;
    height = 0.0;
    float value_offset = 0.0;
    float value_width  = 0.0;
    
    for (std::vector<KikiMenuItem*>::iterator iter = menu_items.begin(); iter != menu_items.end(); iter++)
    {
        if ((*iter)->getWidth() > width) width = (*iter)->getWidth();
        height += (*iter)->getHeight() + line_spacing;
        
        if ((*iter)->value_text)
        {
            value_offset = kMax ((*iter)->item_text->getWidth(), value_offset);
            value_width  = kMax ((*iter)->value_text->getWidth(), value_width);
        }
    }

    if (value_offset == 0.0)
    {
        value_offset = width/2.0;
    }
    else
    {
        width = kMax (width, value_offset + value_width);
    }

    float currentHeight = menu_items[0]->getHeight();

    for (int lineIndex = 0; lineIndex < numLines; lineIndex++)
    {
        float yOffset = -(currentHeight - height/2.0);
        currentHeight += menu_items[lineIndex]->getHeight() + line_spacing;
        
        if (KikiText::flags[ALIGN_CENTER])
        {
            if (menu_items[lineIndex]->value_text)
            {
                menu_items[lineIndex]->item_text->setPosition
                        (KVector (-width/2.0 + value_offset - menu_items[lineIndex]->item_text->getWidth(), 
                                    yOffset, 0.0));
                menu_items[lineIndex]->value_text->setPosition 
                        (KVector (-width/2.0 + value_offset, yOffset, 0.0));            
            }
            else
            {
                menu_items[lineIndex]->item_text->setPosition
                        (KVector (-menu_items[lineIndex]->item_text->getWidth()/2.0, yOffset, 0.0));
            }
        }
        else
        {
            menu_items[lineIndex]->item_text->setPosition(KVector(0.0, yOffset, 0.0));
            if (menu_items[lineIndex]->value_text)
            {
                menu_items[lineIndex]->value_text->setPosition (KVector (value_offset, yOffset, 0.0));
            }
        }
    }

    // ............................................................................ adjust projection    
    float distance = kMax (width / projection->getCurrentAspectRatio(), height) * 1.2;
    projection->KMatrix::reset();
    projection->translate (0.0, 0.0, distance);
    ((KLightingProjection*)projection)->setLightOffset 
                        (KVector (-width / (projection->getCurrentAspectRatio() * 2.0), height, 0.0));
    projection->setZFar (distance + 10);
    projection->setZNear (distance - 10);
}

// __________________________________________________________________________________________________
void KikiMenu::performAction ( KikiAction * action )
{    
    KikiScreenText::performAction (action);
    if (action->getId() == ACTION_SHOW)
    {
        fade_value = 1.0;
    }
}

// __________________________________________________________________________________________________
void KikiMenu::actionFinished ( KikiAction * action )
{    
    if (action->getId() == ACTION_HIDE)
    {
        if (active_index >= 0)
        {
            getEventWithName (currentItem()->event_name)->triggerActions();
        }
        else
        {
            getEventWithName ("hide")->triggerActions();
        }
        Controller.timer_event->addAction (getActionWithId (ACTION_DELETE));
    }
    else
    {
        KikiScreenText::actionFinished (action);
    }
}

// __________________________________________________________________________________________________
void KikiMenu::nextItem ()
{
    do
    {
		if (circular)
			active_index = (active_index + 1) % menu_items.size();
		else
			active_index = kMin(active_index + 1, menu_items.size()-1);
    }
    while (menu_items[active_index]->ignore);
}

// __________________________________________________________________________________________________
void KikiMenu::previousItem ()
{
    do
    {
		if (circular)
		{
			if (active_index > 0) active_index--;
			else active_index = (int)menu_items.size() - 1;
		}
		else
		{
			active_index = kMax(active_index - 1, 0);
		}
    }
    while (menu_items[active_index]->ignore);
}

// __________________________________________________________________________________________________
bool KikiMenu::handleKey ( const KKey & key )
{    
    std::string keyName = key.getUnmodifiedName ();

    if (keyName == "DOWN")
    {
        nextItem ();
        getEventWithName ("next")->triggerActions();
	    getEventWithName ("changed")->triggerActions();
        
        Controller.sound->playSound (KikiSound::MENU_ITEM);
    }
    else if (keyName == "UP")
    {
        previousItem ();
        getEventWithName ("previous")->triggerActions();
		getEventWithName ("changed")->triggerActions();
        
        Controller.sound->playSound (KikiSound::MENU_ITEM);
    }
    else if (keyName == "ESCAPE" && escape_active)
    {
        Controller.sound->playSound (KikiSound::MENU_ABORT);
        active_index = -1;
        getActionWithId (ACTION_HIDE)->setDuration (500);
        Controller.timer_event->addAction (getActionWithId (ACTION_HIDE));
        KEventHandler::removeFocusKeyHandler (this);
    }
    else if (keyName == "RETURN" || keyName == "SPACE")
    {
		if (currentItem()->ignore == false)
        {
            Controller.sound->playSound (KikiSound::MENU_SELECT);
            getEventWithName (currentItem()->event_name)->triggerActions();
            Controller.timer_event->addAction (getActionWithId (ACTION_DELETE));
            KEventHandler::removeFocusKeyHandler (this);
        }
    }
	else if (keyName == "RIGHT" )
	{
		if (currentItem()->option == true && currentItem()->ignore == false)
		{
            Controller.sound->playSound (KikiSound::MENU_SELECT);
            getEventWithName (currentItem()->event_name)->triggerActions();
            Controller.timer_event->addAction (getActionWithId (ACTION_DELETE));
            KEventHandler::removeFocusKeyHandler (this);
        }
	}
    else if (keyName == "F1")
    {
        Controller.saveScreenShot();
    }
    else if ( key.name == Controller.quit_key)
    {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent (&event);
    }

    return true;
}

// __________________________________________________________________________________________________
void KikiMenu::display ()
{
    for (int index = 0; index < (int)menu_items.size(); index++)
    {
        int value_color = base_color;
        
        if (index == active_index - index_offset)
        {
            glPushMatrix();
            glScalef (1.0, 1.0, 2.0);
            glTranslatef (0, 0, bevel_depth);

            list_color = bright_color;

            if (menu_items[index]->value_text)
            {
                value_color = base_color;            
            }
        }
        else
        {
            if (menu_items[index]->value_text)
            {
                value_color = dark_color;
                list_color = base_color;
            }
            else
            {
                list_color = dark_color;
            }
        }
        
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
        
        menu_items[index]->item_text->display();

        if (menu_items[index]->value_text)
        {
            list_color = value_color;
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
            menu_items[index]->value_text->display();

			if (menu_items[index]->extra_text)
			{
				menu_items[index]->extra_text->display();
			}
        }

        if (index == active_index - index_offset)
        {
            glPopMatrix();
        }        
    }
}

// __________________________________________________________________________________________________

KikiMenuItem * KikiMenu::currentItem()
{
	if (active_index >= 0)
		return menu_items[active_index];
	return NULL;
}

// __________________________________________________________________________________________________
// __________________________________________________________________________________________________

KikiMenuItem::KikiMenuItem ()
{
    ignore     = false;
	option     = false;
    item_text  = NULL;
    value_text = NULL;
	extra_text = NULL;
}

// __________________________________________________________________________________________________
KikiMenuItem::~KikiMenuItem ()
{
  delete item_text;
  delete value_text;
  delete extra_text;
}

// __________________________________________________________________________________________________
float KikiMenuItem::getWidth () const
{
    float width = 0.0;
    if (item_text) width += item_text->getWidth();
    if (value_text) width += value_text->getWidth();
    return width;
}

// __________________________________________________________________________________________________
float KikiMenuItem::getHeight () const
{
    float height = 0.0;
    if (item_text) height = item_text->getHeight();
    if (value_text) height = kMax (value_text->getHeight(), height);
    return height;
}
