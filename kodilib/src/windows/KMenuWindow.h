/*
 *  KMenuWindow.h
 *  kodisein
 */

#ifndef __KMenuWindow
#define __KMenuWindow

#include "KWindow.h"
#include "KMenu.h"
#include "KNotificationObject.h"

enum {	KDL_MENUWINDOW_FLAG_STATUS_RELEASING = KDL_WINDOW_FLAG_END,
        KDL_MENUWINDOW_FLAG_STATUS_MOVING,
        KDL_MENUWINDOW_FLAG_END };

class KMenuItem;

class KMenuWindow : public KWindow
{
    INTROSPECTION
    
    public:
    
                                KMenuWindow		();

    virtual void		addMenuItem		( KMenuItem * );
    virtual void		release			( const KMouseEvent & );
    virtual bool		mouseMotion		( const KMouseEvent & );
    virtual void		layout			() { widget->layout(); }

    KMenuItem *			getItemWithCallback	( KCallbackPtr );
    GLfloat			getMenuHeight		() 
                                { return widget->getSpacing()+KDL_MENU_DEFAULT_ITEM_HEIGHT; }
                                
    virtual bool	pick			( const KMouseEvent & );
    
    // pickhandler notifications
    virtual void		unpicked		();
    virtual bool		shouldPick		( const KPickable * );
    virtual void		picked			();

    virtual std::string		getXML 			( int = 0 ) const;
    virtual void		setXML			( std::string & );
};

#endif


