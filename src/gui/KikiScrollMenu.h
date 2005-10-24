/*
 *  KikiScrollMenu.h
 *  kiki
 */

#ifndef __KikiScrollMenu
#define __KikiScrollMenu

#include "KikiColumnMenu.h"

// __________________________________________________________________________________________________
class KikiScrollMenu : public KikiColumnMenu
{
    public: // ........................................................................ PUBLIC

    // ........................................................................ (con|de)struction
                KikiScrollMenu	( int rows = 5, int columns = 4, int selectedItem = -1 );
    
    // ........................................................................ menu items
    virtual void addItem	( const std::string & itemText, KikiAction * action = 0, bool option = false );
	virtual KikiMenuItem * currentItem ();

	virtual void show ();

	virtual int  getCurrentIndex ();
	virtual void setCurrentIndex (int index);

    protected: // ..................................................................... PROTECTED
    
    void	activeIndexChanged ();
    void	nextItem ();
    void	previousItem ();
	bool    handleKey ( const KKey & key );
    
    int 	visible_items;
	int     offset;
	int     num_rows;
    std::vector<KikiMenuItem*>	all_menu_items;
};

#endif

