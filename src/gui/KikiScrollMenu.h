/*
 *  KikiScrollMenu.h
 *  kiki
 */

#ifndef __KikiScrollMenu
#define __KikiScrollMenu

#include "KikiMenu.h"

// __________________________________________________________________________________________________
class KikiScrollMenu : public KikiMenu 
{
    public: // ........................................................................ PUBLIC

    // ........................................................................ (con|de)struction
                KikiScrollMenu	( int visibleItems = 10, int selectedItem = -1 );
    
    // ........................................................................ menu items
    virtual void addItem	( const std::string & itemText, KikiAction * action = 0 );    

    protected: // ..................................................................... PROTECTED
    
    void	activeIndexChanged ();
    void	nextItem ();
    void	previousItem ();
    
    int 	visible_items;
    std::vector<KikiMenuItem*>	all_menu_items;
};

#endif

