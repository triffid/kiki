/*
 *  KScrollBar.cpp
 *  kodisein
 */

#include "KScrollBar.h"
#include "KWindow.h"
#include "KIconButton.h"
#include "KSliderButton.h"
#include "KConsole.h"
#include "KColor.h"

KDL_CLASS_INTROSPECTION_2 (KScrollBar, KWidgetArray, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KScrollBar::KScrollBar ( KWindow * parentWindow ) : KWidgetArray ()
{
    spacing	  = 0;
    frame_spacing = 0;

    flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
    flags[KDL_WIDGET_FLAG_FRAMED] = false;
    
    pageup_button = new KSliderButton ();
    addChild(pageup_button);
    pageup_button->flags[KDL_WIDGET_FLAG_FILL_Y] = true;
    parentWindow->addPickable (pageup_button);
    pageup_button->addReceiverCallback(this, (KCallbackPtr)&KScrollBar::pageUpButtonCallback);

    slider = new KSliderButton ();
    addChild(slider);
    parentWindow->addPickable (slider);
    slider->setBGColor(KColor(0.25, 0.25, 0.25, 0.5));
    slider->addReceiverCallback(this, (KCallbackPtr)&KScrollBar::sliderMovedCallback);

    pagedown_button = new KSliderButton ();
    addChild(pagedown_button);
    parentWindow->addPickable (pagedown_button);
    pagedown_button->addReceiverCallback(this, (KCallbackPtr)&KScrollBar::pageDownButtonCallback);
    
    up_button = new KIconButton (KDL_ICONBUTTON_ARROW_UP);
    addChild(up_button);
    parentWindow->addPickable (up_button);
    up_button->addReceiverCallback(this, (KCallbackPtr)&KScrollBar::lineUpButtonCallback);

    down_button = new KIconButton (KDL_ICONBUTTON_ARROW_DOWN);
    addChild(down_button);
    parentWindow->addPickable (down_button);
    down_button->addReceiverCallback(this, (KCallbackPtr)&KScrollBar::lineDownButtonCallback);

    layout();

    setUnits(0,0,0);
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::lineDownButtonCallback ()
{
    if (slider_value >= 1.0) return;
    slider_value = kMin(slider_value+line_increment, 1.0);
    updateSlider();
    notifyReceiversType(KDL_NOTIFICATION_TYPE_SCROLL_LINE_DOWN);
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::lineUpButtonCallback ()
{
    if (slider_value <= 0.0) return;
    slider_value = kMax(slider_value-line_increment, 0.0);
    updateSlider();
    notifyReceiversType(KDL_NOTIFICATION_TYPE_SCROLL_LINE_UP);
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::pageUpButtonCallback ()
{
    if (slider_value <= 0.0) return;
    slider_value = kMax(slider_value-page_increment, 0.0);
    updateSlider();
    notifyReceiversType(KDL_NOTIFICATION_TYPE_SCROLL_PAGE_UP);
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::pageDownButtonCallback ()
{
    if (slider_value >= 1.0) return;
    slider_value = kMin(slider_value+page_increment, 1.0);
    updateSlider();
    notifyReceiversType(KDL_NOTIFICATION_TYPE_SCROLL_PAGE_DOWN);
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::sliderMovedCallback ()
{
    float slider_y = slider->getPosition()[Y];
    //slider_value = kMin(1.0, kMax(0.0, (float)(size.h-getLocatorWidgetPos().y-7)/(size.h - 3*14)));
    int net_bar_height = size.h - 28 - slider->getSize().h; // minus two arrow buttons and slider
    slider_value = kMinMax(0.0, 1.0, (float)-slider_y / net_bar_height);
    updateSlider();
    notifyReceivers(slider_value);
}

// --------------------------------------------------------------------------------------------------------
KSize KScrollBar::relayout ( const KSize & newSize )
{
    size = KSize(min_size.w, kMax(3*14, newSize.h));
    updateSlider();
    up_button->setPosition  (0,-size.h+28);
    down_button->setPosition(0,-size.h+14);
    return size;
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::setUnits ( float current, float view, float full )
{
    if (view < full)
    {
        line_increment = 1.0/(full-view);
        page_increment = view * line_increment;
        slider_value   = kMax(0.0, kMin(1.0, current/(full-view)));
        slider_size = kMin(1.0, view/full);
    }
    else
    {
        line_increment = 0.0;
        page_increment = 0.0;
        slider_value   = 0.0;
        slider_size = 1.0;
    }
    updateSlider();
}

// --------------------------------------------------------------------------------------------------------
void KScrollBar::updateSlider ()
{
    int bar_height = size.h - 2 * 14;
    int slider_height = (int)(slider_size * (bar_height-14))+14;
    slider->KWidget::setSize(KSize(14,slider_height));
    int net_bar_height = bar_height - slider_height;
    int slider_pos_y = (int)(slider_value * net_bar_height);
    slider->setPosition(0, -slider_pos_y);
    pageup_button->KWidget::setSize(KSize(14, slider_pos_y));
    pagedown_button->KWidget::setSize(KSize(14, net_bar_height - slider_pos_y));
    pagedown_button->setPosition(0, -slider_pos_y-slider_height);
}

