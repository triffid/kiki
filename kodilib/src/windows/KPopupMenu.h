/*
 *  KPopupMenu.h
 *  kodisein
 */

#ifndef __KPopupMenu
#define __KPopupMenu

#include "KMenuWindow.h"

class KPopupMenu : public KMenuWindow
{
    INTROSPECTION
    
    KPickHandler *		old_release_handler;
    
    public:
    
                                KPopupMenu		();
                             
    virtual void		show			();
    virtual void		close			();
    virtual void		release			( const KMouseEvent & );
};

#endif


