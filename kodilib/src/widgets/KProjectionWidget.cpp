/*
 *  KProjectionWidget.cpp
 *  kodisein
 */

#include "KProjectionWidget.h"
#include "KEventHandler.h"
#include "KLightingProjection.h"
#include "KConsole.h"

#include <SDL.h>

KDL_CLASS_INTROSPECTION_2 (KProjectionWidget, KWidget, KPickHandler)

// --------------------------------------------------------------------------------------------------------
KProjectionWidget::KProjectionWidget() : KWidget (), KPickHandler ()
{
    KWidget::flags[KDL_WIDGET_FLAG_FIXED_SIZE]  = false;
    KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    KWidget::flags[KDL_WIDGET_FLAG_FILL_Y] = true;
    KPickHandler::flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED] = true;
    
    size.w = 300; 
    size.h = 300; 
    
    projection = new KLightingProjection();
}

// --------------------------------------------------------------------------------------------------------
void KProjectionWidget::display ()
{
    if (KWidget::flags[KDL_WIDGET_FLAG_VISIBLE] == false) return;
        
    KWidget::display();
 
    glPushAttrib( GL_CURRENT_BIT | GL_POLYGON_BIT | GL_LIGHTING_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT |
                    GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(matrix);
    
    glEnable (GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor4f(0.0, 0.0, 0.0, 0.75);
    glRasterPos2i(1, -1);
    glPixelZoom(size.w-2, -(size.h-2));
    GLuint depth = (GLuint)-1;
    glDepthFunc(GL_ALWAYS);
    glDrawPixels(1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, &depth);
    glDepthFunc(GL_LESS);
    glPixelZoom(1, 1);
    
    glPolygonMode(GL_FRONT_AND_BACK, KEventHandler::flags[KDL_DISPLAY_MODE_WIREFRAME] ? GL_LINE : GL_FILL);
    KEventHandler::resetLighting();

    KPosition screenPos = getScreenPos();
    KSize screenSize    = KEventHandler::getScreenSize(); 
    projection->setViewportBorder ( screenPos.x + 1, 
                                    screenPos.y + 1,
                                    screenSize.w - (screenPos.x + size.w) + 1,
                                    screenSize.h - (screenPos.y + size.h) + 1);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();    
    projection->initProjection();
    displayContent();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
       
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

// --------------------------------------------------------------------------------------------------------
bool KProjectionWidget::pick ( const KMouseEvent & event )
{
    if (KWidget::flags[KDL_WIDGET_FLAG_VISIBLE] == false) return false;
    
    KPosition widgetMousePos = event.pos - getScreenPos();

    if ( widgetMousePos.x > 0 && widgetMousePos.x < (int)size.w && 
         widgetMousePos.y > 0 && widgetMousePos.y < (int)size.h)
    {
        getWindow()->unpick();
	KPickHandler::pick(event);
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------------------------------------------------------------------------------------------
void KProjectionWidget::displayPickables( int )
{
    KWidget::display();
    displayContent();
}



