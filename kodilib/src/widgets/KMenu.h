/*
 *  KMenu.h
 *  kodisein
 */

#ifndef __KMenu
#define __KMenu

#define KDL_MENU_DEFAULT_ITEM_HEIGHT		25

#include "KWidgetArray.h"
#include "KKeyRecorder.h"

class KMenu : public KWidgetArray
{   
    INTROSPECTION
        
    public:
    
    static KKeyRecorder	shortcut_recorder;
    static bool		show_shortcuts;

                        KMenu 			();

    virtual void	close 			();
    
    virtual std::string	getXML 			( int = 0 ) const;
    virtual void	setXML			( std::string & );
};

#endif
