/*
 *  KWidget.cpp
 *  kodisein
 */

#include "KWidget.h"
#include "KEventHandler.h"
#include "KConsole.h"
#include "KWindow.h"
#include "KProjection.h"
#include "KColor.h"

#include <algorithm>
#include <SDL.h>

KDL_CLASS_INTROSPECTION_2 (KWidget, KMatrix, KPickable)

// --------------------------------------------------------------------------------------------------------
KWidget::KWidget() : KMatrix(), KPickable()
{
    parent		= NULL;
    window		= NULL;
    fg_color 		= NULL;
    bg_color 		= NULL;
    flags.resize 	(KDL_WIDGET_FLAG_END);
    flags[KDL_WIDGET_FLAG_FRAMED]  = false;
    flags[KDL_WIDGET_FLAG_VISIBLE] = true;
    flags[KDL_WIDGET_FLAG_FILL_X]  = false;
    flags[KDL_WIDGET_FLAG_FILL_Y]  = false;
}

// --------------------------------------------------------------------------------------------------------
KWidget::~KWidget() 
{
    if (fg_color) { delete fg_color; fg_color = NULL; }
    if (bg_color) { delete bg_color; bg_color = NULL; }
    
    PickableVector::iterator iter = children.begin();
    parent = NULL;
    while (iter != children.end())
    {
        delete (*iter);
        iter++;
    }
    children.clear();
}

// --------------------------------------------------------------------------------------------------------
void KWidget::getWidgetsInHierarchy ( std::vector<KWidget*>* widgets )
{
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        widgets->push_back((KWidget*)*iter);
        ((KWidget*)*iter)->getWidgetsInHierarchy(widgets);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
std::vector<KWidget*> KWidget::getChildrenBehindWidget ( KWidget * w )
{
    std::vector<KWidget*> hierarchy;
    getWidgetsInHierarchy(&hierarchy);
    std::vector<KWidget*>::iterator result = std::find(hierarchy.begin(), hierarchy.end(), w);
    if (result != hierarchy.end())
    {
        hierarchy.erase(hierarchy.begin(), result+1);
    }
    return hierarchy;
}

// --------------------------------------------------------------------------------------------------------
std::vector<KWidget*> KWidget::getChildrenBeforeWidget ( KWidget * w )
{
    std::vector<KWidget*> hierarchy;
    getWidgetsInHierarchy(&hierarchy);
    std::vector<KWidget*>::iterator result = std::find(hierarchy.begin(), hierarchy.end(), w);
    if (result != hierarchy.end())
    {
        hierarchy.erase(result, hierarchy.end());
    }
    return hierarchy;
}

// --------------------------------------------------------------------------------------------------------
/* returns the position of the locator relative to the lower left corner of the widget 
*/
KPosition KWidget::getLocatorWidgetPos () const
{
    return KEventHandler::getMousePos() - getScreenPos();
}

// --------------------------------------------------------------------------------------------------------
/* returns the position of the lower left corner of the widget in "screen coordinates" 
   screen coordinates:  bottom y = 0, top y = screen.h
*/
KPosition KWidget::getScreenPos () const
{
    KPosition viewportScreenPos = getWindow()->getProjection()->getViewportScreenPos();
    KSize viewportSize = getWindow()->getProjection()->getViewportSize();
    KPosition widgetViewportPos = getViewportPos();
    return KPosition(viewportScreenPos.x + widgetViewportPos.x,
                     viewportScreenPos.y + viewportSize.h + widgetViewportPos.y - size.h);
}

// --------------------------------------------------------------------------------------------------------
/* returns the position of the top left corner of the widget in "window viewport coordinates"
   window viewport coordinates:  top y = 0, bottom y = -viewport.h
*/
KPosition KWidget::getViewportPos () const
{
    KPosition vpPos((int)matrix[TX], (int)matrix[TY]);
    
    if (parent)
    {
        return  vpPos + parent->getViewportPos();
    }
    
    return vpPos;
}

// --------------------------------------------------------------------------------------------------------
void KWidget::setFGColor (const KColor & c)
{
    if (fg_color != NULL) 
    {	
        *fg_color = c;
    }
    else 
    {
        fg_color = new KColor(c);
    }
}

// --------------------------------------------------------------------------------------------------------
void KWidget::setBGColor (const KColor & c)
{
    if (bg_color != NULL) 
    {
        *bg_color = c;
    }
    else 
    {
        bg_color = new KColor(c);
    }
}

// --------------------------------------------------------------------------------------------------------
void KWidget::hide ()
{ 
    flags[KDL_WIDGET_FLAG_VISIBLE] = false;
}

// --------------------------------------------------------------------------------------------------------
void KWidget::show ()
{ 
    flags[KDL_WIDGET_FLAG_VISIBLE] = true; 
}

// --------------------------------------------------------------------------------------------------------
KWindow * KWidget::getWindow () const
{
    if (window == NULL) return getParent()->getWindow();
    return window;
}

// --------------------------------------------------------------------------------------------------------
KWidget * KWidget::getRootWidget () const
{
    if (parent == NULL) return (KWidget*)this;
    return parent->getRootWidget();
}

// --------------------------------------------------------------------------------------------------------
void KWidget::addChild ( KWidget * child )
{
    children.push_back(child);
    child->setParent(this);
}

// --------------------------------------------------------------------------------------------------------
void KWidget::display ()
{   
    if (flags[KDL_WIDGET_FLAG_VISIBLE] == false) return;

    glPushAttrib (GL_CURRENT_BIT);
    glPushMatrix();
    glMultMatrixf (matrix);
    
    if (getFGColor()) getFGColor()->glColor();
    
    render ();
    
    for (PickableVector::iterator iter = children.begin(); iter != children.end(); iter++)
    {
        ((KWidget*)*iter)->display();
    }
    
    glPopMatrix();
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
void KWidget::render ()
{
    loadId();
    if (flags[KDL_WIDGET_FLAG_FRAMED])
    {
        KSize ws = getSize();
    
        if (getBGColor())
        {
            glPushAttrib (GL_CURRENT_BIT | GL_POLYGON_BIT);
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            getBGColor()->glColor();
            glRecti (0, -ws.h, ws.w, 0);
            glPopAttrib();
        }
        
        glRecti(0, -ws.h, ws.w, 0);
    }
}

// --------------------------------------------------------------------------------------------------------
KSize KWidget::relayout ( const KSize & newSize )
{
    if (flags[KDL_WIDGET_FLAG_FILL_X] && newSize.w != size.w) 
    {
        size.w = kMax(newSize.w, min_size.w);
    }
    if (flags[KDL_WIDGET_FLAG_FILL_Y] && newSize.h != size.h) 
    {	
        size.h = kMax(newSize.h, min_size.h);
    }
    return size;
}


