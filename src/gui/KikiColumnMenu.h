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
    
    protected: // ..................................................................... PROTECTED
    
    void	alignItems ();
    
    float	column_spacing;
    int 	max_column_items;
};

#endif

