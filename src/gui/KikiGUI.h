/*
 *  KikiGUI.h
 */

#ifndef __KikiGUI
#define __KikiGUI

#include "KikiGUI.h"
#include "KikiMenu.h"
#include "KikiScrollMenu.h"
#include "KikiColumnMenu.h"
#include "KikiPageText.h"
#include "KikiScreenText.h"

#include <KMenuWindow.h>

class KButtonBox;
class KButton;
class KLabel;

// __________________________________________________________________________________________________
class KikiGUI : public KMenuWindow
{
    public: // ........................................................................ PUBLIC
    
                KikiGUI			();
        
    void 	init			(); 
    
    void	layout			();
    
    void	setShowShortCuts 	( bool );
    bool	getShowShortCuts 	() const;
};

#endif

