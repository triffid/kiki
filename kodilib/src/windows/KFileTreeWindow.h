/*
 *  KFileTreeWindow.h
 *  kodisein
 */

#ifndef __KFileTreeWindow
#define __KFileTreeWindow

#include "KWindow.h"
#include "KFileTreeWidget.h"
#include "KNotificationObject.h"

class KTextField;
class KLabel;

class KFileTreeWindow : public KWindow, public KNotificationObject
{
    INTROSPECTION
    
    protected:
    
    KFileTreeWidget *	tree_widget;
    KTextField *	filename_widget;
    KLabel *		dirname_widget;
    
    public:
    
                        KFileTreeWindow 	();
    void		show			();
    void		hide			();
    void		displayPickables	( int );
    void		notify			();
    void		relayout		( const KSize & );
    KProjection *	getFileTreeProjection	() { return tree_widget->getProjection(); }
    void		setOpenFileMode		( bool = true );
};

#endif

