/*
 *  KScrollBar.h
 *  kodisein
 */

#ifndef __KScrollBar
#define __KScrollBar

#include "KWidgetArray.h"
#include "KButton.h"

enum {	KDL_NOTIFICATION_TYPE_SCROLL_LINE_UP = KDL_NOTIFICATION_TYPE_NOTIFICATION_END,
        KDL_NOTIFICATION_TYPE_SCROLL_LINE_DOWN,
        KDL_NOTIFICATION_TYPE_SCROLL_PAGE_UP,
        KDL_NOTIFICATION_TYPE_SCROLL_PAGE_DOWN
    };

class KScrollBar : public KWidgetArray, public KNotificationObject
{
    INTROSPECTION

    protected:

    KButton * 	up_button;
    KButton *	down_button;
    KButton * 	pageup_button;
    KButton *	pagedown_button;
    KButton *	slider;
    
    float	slider_value;
    float	slider_size;
    float	line_increment;
    float	page_increment;
    
    void	updateSlider		();

    public:
                KScrollBar		( KWindow * parentWindow );

    KSize	relayout		( const KSize & );

    void	setUnits		( float current, float view, float full );

    void	sliderMovedCallback	();
    void	lineUpButtonCallback	();
    void	lineDownButtonCallback	();
    void	pageUpButtonCallback	();
    void	pageDownButtonCallback	();
};

#endif

