/*
 *  KikiScrollMenu.cpp
 *  kiki
 */

#include "KikiScrollMenu.h"

// __________________________________________________________________________________________________
KikiScrollMenu::KikiScrollMenu ( int visibleItems, int activeItem ) : KikiMenu (activeItem)
{
    visible_items = visibleItems;
    index_offset = kMax (0, (active_index - visible_items / 2));
}

// __________________________________________________________________________________________________
void KikiScrollMenu::addItem ( const std::string & itemText, KikiAction * itemAction )
{  
    all_menu_items.push_back (newItem (itemText, itemAction));
    if ((int)all_menu_items.size() >= (active_index - visible_items / 2) &&
        (int)all_menu_items.size() <= (active_index + visible_items / 2))
    {
        menu_items.push_back(all_menu_items.back());
        alignItems();
    }
}

// __________________________________________________________________________________________________
void KikiScrollMenu::nextItem ()
{
    do
    {
        active_index = (active_index + 1) % all_menu_items.size();
    }
    while (all_menu_items[active_index]->ignore);
    activeIndexChanged ();
}

// __________________________________________________________________________________________________
void KikiScrollMenu::previousItem ()
{
    do
    {
        if (active_index > 0) active_index--;
        else active_index = (int)all_menu_items.size() - 1;
    }
    while (all_menu_items[active_index]->ignore);
    activeIndexChanged ();
}

// __________________________________________________________________________________________________
void KikiScrollMenu::activeIndexChanged ()
{
    index_offset = kMax (0, kMin ((int)all_menu_items.size() - visible_items, 
                                    (active_index - visible_items / 2)));
    menu_items.clear();
    for (int index = index_offset; 
         index < kMin ((int)all_menu_items.size(), 
                        kMax(index_offset + visible_items, (active_index + visible_items / 2))); index++)
    {
         menu_items.push_back (all_menu_items[index]);
    }
    alignItems();
} 
