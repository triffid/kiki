/*
 *  KikiPythonWidget.cpp
 *  kiki
 */

#include "KikiPythonWidget.h"
#include "KikiController.h"
#include "KikiPython.h"

#include <KConsole.h>
#include <KDisplayTools.h>
#include <KKey.h>
#include <KEventHandler.h>

// --------------------------------------------------------------------------------------------------------
KikiPythonWidget::KikiPythonWidget () : KTextField ()
{
    bg_color = new KColor(0.0, 0.0, 0.0, 0.8);
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::initPython ()
{
    Controller.python->executeFile(Controller.getKikiHome() + "/py/edit.py");
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::displayStringAtPos ( const std::string & str, const KikiPos & pos )
{
    kDisplayString(str, KPosition(pos.x*8, -pos.y*13), false);
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::render ()
{
    KWidget::render();
    
    int cHeight 	= getRowHeight();
    int cWidth  	= getColumnWidth();
    int widgetWidth	= getSize().w;
    
    glEnable(GL_SCISSOR_TEST);
    glScissor(getScreenPos().x, getScreenPos().y, size.w, size.h);

    // ............................................................ display python text
    glPushMatrix();
    glTranslatef(3, -10, 0);
    execute("displayText()");
    glPopMatrix();
    
    // ............................................................ display selection and cursor
    int posX =  cursorPos.x * cWidth;
    int posY = -cursorPos.y * cHeight;
    
    if (picked)
    {
        // ............................................................ the cursor
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin (GL_QUADS);
            glVertex2i(posX+3, posY);
            glVertex2i(posX+3, posY-cHeight);
            glColor4f(1.0, 1.0, 0.0, 0.1);
            glVertex2i(posX+3+cWidth, posY-cHeight);
            glVertex2i(posX+3+cWidth, posY);
        glEnd();

        // ............................................................ selection
        if (selectionPos != cursorPos) // if exists, draw the selection
        {
            int startX, startY, endX, endY;
            
            if (selectionPos.y > cursorPos.y)
            {
                startX = posX+3; 
                startY = posY;
                endX = selectionPos.x * cWidth; 
                endY = -selectionPos.y * cHeight;
            }
            else
            {
                startX = selectionPos.x * cWidth+3; 
                startY = -selectionPos.y * cHeight;
                endX = posX; 
                endY = posY;
            }
    
            glPushAttrib (GL_CURRENT_BIT | GL_POLYGON_BIT);
            
            selection_color.glColor();
            glDisable (GL_CULL_FACE);
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            glBegin (GL_QUADS);
                if (startY == endY) // just one line selected
                {
                    glVertex2i (startX,		startY);
                    glVertex2i (startX,		startY	-cHeight);
                    glVertex2i (endX,   	startY	-cHeight);
                    glVertex2i (endX,   	startY);
                }
                else  // multiple lines selected
                {
                    glVertex2i (startX, 	startY);
                    glVertex2i (startX, 	startY	-cHeight);
                    glVertex2i (widgetWidth,   	startY	-cHeight);
                    glVertex2i (widgetWidth,	startY);
    
                    glVertex2i (0,		endY);
                    glVertex2i (0,		endY	-cHeight);
                    glVertex2i (endX,   	endY	-cHeight);
                    glVertex2i (endX,   	endY);
    
                    glVertex2i (0, 		startY	-cHeight);
                    glVertex2i (0, 		endY);
                    glVertex2i (widgetWidth,	endY);
                    glVertex2i (widgetWidth,	startY	-cHeight);
                }
            glEnd();

            glPopAttrib();
        }        
    }

    glDisable(GL_SCISSOR_TEST);    
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::clear ()
{
    execute("clearBuffer()\n");
    getWindow()->pickPickable(this);
}

// --------------------------------------------------------------------------------------------------------
bool KikiPythonWidget::execute ( const std::string & cmd, bool eval )
{
    if (Controller.python)
    {
        return Controller.python->execute("pythonConsole." + cmd + "\n", eval);
    }
    return false;
}

// --------------------------------------------------------------------------------------------------------
KSize KikiPythonWidget::relayout (  const KSize & newSize  )
{
    KTextField::relayout(newSize);
    printf ("Controller.python %#x\n", Controller.python);
    if (Controller.python != NULL)
    {
        Controller.python->execute(kStringPrintf("if 'pythonConsole' in locals():\n"
                                                 "    pythonConsole.setSize(%d, %d)\n\n", 
                                                                            getTextCols(), getTextRows()));
    }
    return size;
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::scrollRelative ( float f )
{
    execute(kStringPrintf("scrollRelative(%f)\n", f));
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::mouseMoved ( const KMouseEvent & event )
{
    KPosition mouseWidgetPos = event.pos - getScreenPos(); // position relative to widget
    
    execute(kStringPrintf("mouseMoved((%d, %d))\n", mouseWidgetPos.x / getColumnWidth(), 
                                            (getSize().h-mouseWidgetPos.y) / getRowHeight()));
}

// --------------------------------------------------------------------------------------------------------
void KikiPythonWidget::setPicked ( bool p )
{
    if (picked != p)
    {
        picked = p;
        if (picked)
        {
            execute(kStringPrintf("picked((%d, %d))", getLocatorWidgetPos().x/getColumnWidth(),
                                        (getSize().h-getLocatorWidgetPos().y)/getRowHeight()));
            KEventHandler::setFocusKeyHandler(this);
            getWindow()->setFocusWidget(this);
        }
        else
        {
            getWindow()->setFocusWidget(NULL);
            KEventHandler::removeFocusKeyHandler((KKeyHandler*)this);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
bool KikiPythonWidget::handleKey ( const KKey & key )
{	
    char character = 0;
    if (key.character != '\\' && key.character != '\'')
    {
        character = key.character;
    }
    return execute(kStringPrintf("handleKey('%s', '%c')", key.name.c_str(), character), true);
}

