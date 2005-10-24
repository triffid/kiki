/*
 *  KikiColumnMenu.h
 *  kiki
 */

#ifndef __KikiColumnMenu
#define __KikiColumnMenu

#include "KikiMenu.h"

// __________________________________________________________________________________________________
class KikiColumnMenu : public KikiMenu 
{
    public: // ........................................................................ PUBLIC

    // ........................................................................ (con|de)struction
                KikiColumnMenu	( int maxColumnItems = 10, int selectedItem = -1 );
    
	virtual void alignItems ();

    protected: // ..................................................................... PROTECTED
       
    float	column_spacing;
    int 	max_column_items;
};

#endif

