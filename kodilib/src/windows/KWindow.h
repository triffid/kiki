/*
 *  KWindow.h
 *  kodisein
 */

#ifndef __KWindow
#define __KWindow

#include "KPickHandler.h"
#include "KWidgetArray.h"

#define KDL_WINDOW_DEFAULT_VIEWPORT_BORDER	10

#define KDL_WINDOW_FEATURES_WIDGET		1
#define KDL_WINDOW_FEATURES_BUTTON_WIDGET_BIT	2
#define KDL_WINDOW_FEATURES_BUTTON_WIDGET	3
#define KDL_WINDOW_FEATURES_CLOSE_BUTTON_BIT	4
#define KDL_WINDOW_FEATURES_CLOSE_BUTTON	7
#define KDL_WINDOW_FEATURES_MAXIMIZE_BUTTON_BIT	8
#define KDL_WINDOW_FEATURES_MAXIMIZE_BUTTON	11
#define KDL_WINDOW_FEATURES_PROJECTION		16
#define KDL_WINDOW_FEATURES_RESIZE_HANDLE	32

#define KDL_WINDOW_FEATURES_DEFAULT_FEATURES 	63 // all features

enum { 	KDL_WINDOW_FLAG_RESIZABLE = KDL_PICKHANDLER_FLAG_END, 
        KDL_WINDOW_FLAG_END };

class KIconButton;

class KWindow : public KPickHandler, public KPickable
{
    INTROSPECTION

    protected:
    
    KWidget *		focus_widget;
    
    KWidgetArray * 	widget;
    KWidgetArray * 	button_widget;
    KIconButton *	close_button;
    KIconButton *	maximize_button;
    
    KPosition		old_pos;
    KSize		old_size;
    
    public:
            
                        KWindow			( int features = KDL_WINDOW_FEATURES_DEFAULT_FEATURES );
    virtual            ~KWindow			();
                                
    void		toggleVisibility	() { widget->flags[KDL_WIDGET_FLAG_VISIBLE] ? 
                                                     widget->hide() : widget->show(); }
    bool		getVisibility		() const { return widget->flags[KDL_WIDGET_FLAG_VISIBLE]; }
    bool		isVisible		() const { return widget->flags[KDL_WIDGET_FLAG_VISIBLE]; }

    KPosition		mapScreenPos		( const KPosition & );

    virtual bool	pick			( const KMouseEvent &  );
    virtual bool	mouseMotion		( const KMouseEvent &  );
    
    virtual void	display			( int );
    virtual void	displayPickables	( int );
    virtual void	moved			( const KMouseEvent &  );
    virtual void	setSize			( KSize );
    virtual void	setPosition		( const KPosition & );
    virtual void	setFocusWidget		( KWidget * w ) { focus_widget = w; }
    virtual void	doubleClicked 		();
    virtual void	maximize		();
    virtual void	setVisibility		( bool v ) { if (v) show(); else hide(); }
    virtual void	show			() { widget->show(); }
    virtual void	hide			() { widget->hide(); }
    virtual void	close			() { hide(); }
    virtual void	layout			() { widget->layout(); }
    virtual void	relayout		( const KSize & s ) { widget->relayout(s); }
};

#endif


