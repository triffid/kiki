/*
 *  KWindow.cpp
 *  kodisein
 */

#include "KWindow.h"
#include "KEventHandler.h"
#include "KOrthographicProjection.h"
#include "KConsole.h"
#include "KColor.h"
#include "KIconButton.h"
#include "KSliderButton.h"
#include "KMenu.h"

KDL_CLASS_INTROSPECTION_2 (KWindow, KPickHandler, KPickable)

// --------------------------------------------------------------------------------------------------------
KWindow::KWindow ( int features ) : KPickHandler (), KPickable ()
{
    flags.resize(KDL_WINDOW_FLAG_END);
    focus_widget = NULL;
    
    flags[KDL_WINDOW_FLAG_RESIZABLE] 		= (features & KDL_WINDOW_FEATURES_RESIZE_HANDLE);
    flags[KDL_PICKHANDLER_FLAG_TRANSPARENT_ZERO] = true;

    if (features & KDL_WINDOW_FEATURES_WIDGET)
    {
        widget = new KWidgetArray ();
        widget->flags[KDL_WIDGET_FLAG_FRAMED] = true;
        widget->flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = false;
        widget->setFGColor (KColor(0.7, 0.7, 0.7, 1.0));
        widget->setBGColor (KColor(0.0, 0.0, 0.0, 0.7));
        widget->setWindow  (this);
        addPickable(widget);
    
        if (features & KDL_WINDOW_FEATURES_BUTTON_WIDGET_BIT)
        {
            button_widget = new KWidgetArray ();
            button_widget->setFrameSpacing(0);
            widget->addChild(button_widget);
    
            if (features & KDL_WINDOW_FEATURES_CLOSE_BUTTON_BIT)
            {
                close_button = new KIconButton(KDL_ICONBUTTON_CROSS);
                close_button->addReceiverCallback(this, (KCallbackPtr)&KWindow::close );
                button_widget->addChild(close_button);
                addPickable(close_button);
            }
            else
            {
                close_button = NULL;
            }
            
            if (features & KDL_WINDOW_FEATURES_MAXIMIZE_BUTTON_BIT)
            {
                maximize_button = new KIconButton(KDL_ICONBUTTON_ARROW_UP);
                maximize_button->addReceiverCallback(this, (KCallbackPtr)&KWindow::maximize );
                    button_widget->addChild(maximize_button); 
                addPickable(maximize_button);
            }
            else
            {
                maximize_button = NULL;
            }
        }
        else
        {
            button_widget = NULL;
        }
    }
    else
    {
        widget = NULL;
    }
    
    if (features & KDL_WINDOW_FEATURES_PROJECTION)
    {
        projection = new KOrthographicProjection ();
        projection->setViewportBorder(	KDL_WINDOW_DEFAULT_VIEWPORT_BORDER, KDL_WINDOW_DEFAULT_VIEWPORT_BORDER, 
                                        KDL_WINDOW_DEFAULT_VIEWPORT_BORDER, 
                                        KDL_WINDOW_DEFAULT_VIEWPORT_BORDER + KDL_MENU_DEFAULT_ITEM_HEIGHT + KDL_WIDGET_DEFAULT_CHILD_SPACING);
    }
    else
    {
        projection = NULL;
    }
}

// --------------------------------------------------------------------------------------------------------
KWindow::~KWindow () 
{
    delete widget;
}

// --------------------------------------------------------------------------------------------------------
bool KWindow::mouseMotion ( const KMouseEvent & mouseEvent )
{
    if (focus_widget)
    {
        focus_widget->mouseMoved(mouseEvent);
        return true;
    }
    
    return KPickHandler::mouseMotion(mouseEvent);
}

// --------------------------------------------------------------------------------------------------------
void KWindow::doubleClicked ()
{
    if (focus_widget)
    {
        focus_widget->doubleClicked();
    }
    else if (picked_pickable->getClassId() >= KWidget::classId())
    {
        ((KWidget*)picked_pickable)->doubleClicked();
    }
}

// --------------------------------------------------------------------------------------------------------
void KWindow::moved ( const KMouseEvent &  mouseEvent )
{
    if (picked_pickable == widget)
    {
        KPosition mouseWidgetPos = mouseEvent.pos - widget->getScreenPos();
        KSize widgetSize = widget->getSize();

        if (flags[KDL_WINDOW_FLAG_RESIZABLE] && 
            mouseWidgetPos.x-mouseEvent.delta.x > (widgetSize.w - 20) &&
            mouseWidgetPos.y-mouseEvent.delta.y < 20)
        {
            // resize corner moved
            setSize(KSize(widgetSize.w + mouseEvent.delta.x, widgetSize.h - mouseEvent.delta.y));
        }
        else // move window
        {
            setPosition(widget->getViewportPos() + mouseEvent.delta);
        }
    }
    else if (picked_pickable->getClassId() >= KSliderButton::classId())
    {
        ((KSliderButton*)picked_pickable)->moved(mouseEvent);
    }
}

// --------------------------------------------------------------------------------------------------------
/* maps a position in screen coordinates to a position in "window viewport coordinates"
*/
KPosition KWindow::mapScreenPos( const KPosition & screenPos )
{
    KPosition viewportPos  = projection->getViewportScreenPos();
    KSize     viewportSize = projection->getViewportSize();
     
    return KPosition (screenPos.x - viewportPos.x,
                      screenPos.y - (viewportPos.y + viewportSize.h));
}

// --------------------------------------------------------------------------------------------------------
void KWindow::maximize ()
{
    if (maximize_button->getType() == KDL_ICONBUTTON_ARROW_UP)
    {
        old_pos  = widget->getViewportPos();
        old_size = widget->getSize();
        
        setPosition (KPosition(0, 0));
        KSize viewportSize = projection->getViewportSize();
        setSize     (viewportSize);
        maximize_button->setType(KDL_ICONBUTTON_ARROW_DOWN);
    }
    else
    {
        setSize 	(old_size);
        setPosition	(old_pos);
        maximize_button->setType(KDL_ICONBUTTON_ARROW_UP);
    }
}

// --------------------------------------------------------------------------------------------------------
void KWindow::setSize ( KSize newSize )
{
    KPosition widgetPos = widget->getViewportPos();
    KSize viewportSize  = projection->getViewportSize();
    KSize maxSize(kMin(newSize.w, viewportSize.w - widgetPos.x - 1),
                  kMin(newSize.h, viewportSize.h - widgetPos.y - 1));
    relayout (maxSize);
}

// --------------------------------------------------------------------------------------------------------
void KWindow::setPosition ( const KPosition & newPos )
{
    KSize viewportSize  = projection->getViewportSize();
    KSize widgetSize	= widget->getSize();

    KPosition maxPos (kMax(0, kMin(newPos.x, viewportSize.w - widgetSize.w - 1)),
                      kMin(0, kMax(newPos.y, -(viewportSize.h - widgetSize.h - 1))));

    widget->setPosition(maxPos);
}

// --------------------------------------------------------------------------------------------------------
void KWindow::display ( int mode )
{
    if (widget->flags[KDL_WIDGET_FLAG_VISIBLE])
    {
        glPushAttrib (GL_CURRENT_BIT | GL_POLYGON_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT | GL_ENABLE_BIT);
    
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    
        glDisable (GL_LIGHTING);
        glDisable (GL_DEPTH_TEST);
    
        projection->initProjection();
        
        widget->display();
    
        if (flags[KDL_WINDOW_FLAG_RESIZABLE]) // draw the resize corner
        {
            if (widget->getFGColor()) widget->getFGColor()->glColor();
            KPosition widgetPos  = widget->getViewportPos(); 
            KSize     widgetSize = widget->getSize();
            
            int fs = ((KWidgetArray*)widget)->getFrameSpacing();
            
            glBegin(GL_LINE_STRIP);
            glVertex2i( widgetPos.x + widgetSize.w - 20,      widgetPos.y - widgetSize.h);
            glVertex2i( widgetPos.x + widgetSize.w - (20-fs), widgetPos.y - widgetSize.h + fs);
            glVertex2i( widgetPos.x + widgetSize.w - fs,      widgetPos.y - widgetSize.h + fs); 
            glVertex2i( widgetPos.x + widgetSize.w - fs,      widgetPos.y - widgetSize.h + (20-fs));        
            glVertex2i( widgetPos.x + widgetSize.w,           widgetPos.y - widgetSize.h + 20);
            glEnd();
        }
    
        glEnable (GL_LIGHTING);
        
        glPopAttrib();
    }
}

// --------------------------------------------------------------------------------------------------------
void KWindow::displayPickables ( int )
{
    widget->display();
}

// --------------------------------------------------------------------------------------------------------
bool KWindow::pick ( const KMouseEvent & event )
{
    if (isVisible() == false) return false;
    return KPickHandler::pick(event);
}


