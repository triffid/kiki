/*
 *  KWidget.h
 *  kodisein
 */

#ifndef __KWidget
#define __KWidget

#include "KMatrix.h"
#include "KPickable.h"

#define KDL_WIDGET_DEFAULT_FRAME_SPACING	5
#define KDL_WIDGET_DEFAULT_CHILD_SPACING	5

enum {	KDL_WIDGET_FLAG_VISIBLE,
        KDL_WIDGET_FLAG_FRAMED,
        KDL_WIDGET_FLAG_FIXED_SIZE,
        KDL_WIDGET_FLAG_FILL_X,
        KDL_WIDGET_FLAG_FILL_Y,
        KDL_WIDGET_FLAG_END };

class KWindow;
class KColor;
class KMouseEvent;

class KWidget : public KMatrix, public KPickable
{
    INTROSPECTION

    protected:
    
    KColor *				bg_color;
    KColor *				fg_color;
    KWidget * 				parent;
    KWindow *				window;
    PickableVector			children;
    
    KSize 				size;
    KSize 				min_size;

    public:

    std::vector<bool>			flags;
    
                                        KWidget			();
                                        ~KWidget		();
                                
    virtual void			display			();
    virtual void			render			();
    virtual void			setParent		( KWidget * w ) { parent = w; }
    virtual void			addChild		( KWidget * );
    virtual void 			getWidgetsInHierarchy	( std::vector<KWidget*> * );
    virtual KWidget *			getParent		() const { return parent; }

    virtual KSize			getSize			() const { return size; }
    virtual void			setSize			( KSize s ) { size = s; }
    virtual KSize			getMinSize		() const { return min_size; }
    virtual void			setMinSize		( KSize s ) { min_size = s; }
    
            std::vector<KWidget*>		getChildrenBehindWidget	( KWidget * );
            std::vector<KWidget*>		getChildrenBeforeWidget	( KWidget * );
            void			setWindow		( KWindow * w ) { window = w; }
            KWindow *			getWindow		() const;
            KWidget *			getRootWidget		() const;
                
            KPosition			getViewportPos		() const;    
            KPosition			getScreenPos		() const;
            KPosition			getLocatorWidgetPos	() const;
    
    virtual void			setFGColor		( const KColor & );
    virtual void			setBGColor		( const KColor & );
    virtual KColor *			getFGColor		() const { return fg_color; }
    virtual KColor *			getBGColor		() const { return bg_color; }
    virtual const PickableVector * 	getChildren		() const { return &children; }
    virtual void			mouseMoved 		( const KMouseEvent & ) {}
    virtual void			doubleClicked		() {}
    virtual void			hide			();
    virtual void			show			();
    virtual KSize			layout			() { return getSize(); }
    virtual KSize			relayout		( const KSize & newSize );
};

#endif

