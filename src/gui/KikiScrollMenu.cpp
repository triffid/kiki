/*
 *  KikiScrollMenu.cpp
 *  kiki
 */

#include "KikiScrollMenu.h"
#include "KConsole.h"
#include <KKey.h>

// __________________________________________________________________________________________________
KikiScrollMenu::KikiScrollMenu ( int rows, int columns, int activeItem ) : KikiColumnMenu (rows, activeItem)
{
	num_rows = rows;
    visible_items = rows * columns;
    offset = index_offset = kMax (0, (active_index - visible_items + 1));
}

// __________________________________________________________________________________________________
KikiScrollMenu::~KikiScrollMenu ()
{
  menu_items.clear();
  while (all_menu_items.empty() == false)
  {
    delete all_menu_items.back();
    all_menu_items.pop_back();
  }
}

// __________________________________________________________________________________________________
void KikiScrollMenu::addItem ( const std::string & itemText, KikiAction * itemAction, bool option )
{  
    all_menu_items.push_back (newItem (itemText, itemAction));
}

// __________________________________________________________________________________________________

void KikiScrollMenu::show()
{
	for (std::vector<KikiMenuItem*>::iterator iter = menu_items.begin(); iter != menu_items.end(); iter++)
    {
		menu_items.push_back((*iter));
	}
	activeIndexChanged();
	KikiColumnMenu::show();
}

// __________________________________________________________________________________________________

void KikiScrollMenu::setCurrentIndex (int index)
{
	active_index = 0;
	activeIndexChanged();
}

// __________________________________________________________________________________________________
void KikiScrollMenu::nextItem ()
{
	if (circular)
		active_index = (active_index + 1) % all_menu_items.size();
	else
		active_index = kMin(active_index + 1, all_menu_items.size()-1);
	
	activeIndexChanged ();
}

// __________________________________________________________________________________________________
void KikiScrollMenu::previousItem ()
{
	if (circular)
	{
		if (active_index > 0) active_index--;
		else active_index = (int)all_menu_items.size() - 1;
	}
	else
	{
		active_index = kMax(active_index - 1, 0);
	}

	activeIndexChanged ();
}

// __________________________________________________________________________________________________

int KikiScrollMenu::getCurrentIndex ()
{
	return active_index;
}

// __________________________________________________________________________________________________
void KikiScrollMenu::activeIndexChanged ()
{
	int min_index_offset = kMax(0, active_index - visible_items + 1);
	int max_index_offset = active_index;
	offset = kMin(max_index_offset, kMax(min_index_offset, offset));

	menu_items.clear();
    for (int index = offset;
         index < kMin ((int)all_menu_items.size(), offset + visible_items);
		 index++)
    {
         menu_items.push_back (all_menu_items[index]);
    }
	index_offset = offset;
    alignItems();
} 

// __________________________________________________________________________________________________

KikiMenuItem * KikiScrollMenu::currentItem()
{
	if (active_index >= 0)
		return all_menu_items[active_index];
	return NULL;
}

// __________________________________________________________________________________________________
bool KikiScrollMenu::handleKey ( const KKey & key )
{    
    std::string keyName = key.getUnmodifiedName ();

    if (keyName == "LEFT" || keyName == "RIGHT")
    {
		active_index += ((keyName == "LEFT") ? -1 : 1) * num_rows;
		if (circular)
		{
			if (active_index < 0)
				active_index += (int)all_menu_items.size();
			else if ((active_index) >= (int)all_menu_items.size())
				active_index -= (int)all_menu_items.size();
		}
		else
		{
			if (active_index < 0)
			{
				offset = index_offset = active_index = 0;
			}
			else
			{
				active_index = kMin(all_menu_items.size()-1, active_index);
			}
		}
		
		activeIndexChanged ();
		getEventWithName ("changed")->triggerActions();
	}
	else
	{
		return KikiMenu::handleKey (key);
	}

	return true;
}
