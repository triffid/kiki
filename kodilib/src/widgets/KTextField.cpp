/*
 *  KTextField.cpp
 *  kodisein
 */
 
#include "KTextField.h"
#include "KEventHandler.h"
#include "KMenu.h"
#include "KConsole.h"
#include "KTools.h"
#include "KKey.h"

KDL_CLASS_INTROSPECTION_2 (KTextField, KLabel, KKeyHandler)

// --------------------------------------------------------------------------------------------------------
KTextField::KTextField ( const std::string & n ) : KLabel(n), KKeyHandler()
{
    KWidget::flags.resize(KDL_TEXTFIELD_FLAG_END);
    KWidget::flags[KDL_WIDGET_FLAG_FRAMED]		= true;
    KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK]	= false;
    
    x_offset = 0;
    cursor_pos = text.size();
    selection_pos = cursor_pos;
    selection_color.setValues(0.0, 0.0, 1.0, 0.25);
    update();
}

// --------------------------------------------------------------------------------------------------------
KTextField * KTextField::firstTextFieldInVector ( const std::vector<KWidget*> & widgets )
{
    std::vector<KWidget*>::const_iterator iter = widgets.begin();
    while (iter != widgets.end())
    {
        if ((*iter)->getClassId() >= KTextField::classId()) return (KTextField*)*iter;
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KTextField * KTextField::lastTextFieldInVector ( const std::vector<KWidget*> & widgets )
{
    std::vector<KWidget*>::const_reverse_iterator iter = widgets.rbegin();
    while (iter != widgets.rend())
    {
        if ((*iter)->getClassId() >= KTextField::classId()) return (KTextField*)*iter;
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
KTextField * KTextField::prevTextField ()
{
    KTextField * sibling  = lastTextFieldInVector(getRootWidget()->getChildrenBeforeWidget(this));
    if (!sibling) sibling = lastTextFieldInVector(getRootWidget()->getChildrenBehindWidget(this));
    return sibling;
}

// --------------------------------------------------------------------------------------------------------
KTextField * KTextField::nextTextField ()
{
    KTextField  * sibling = firstTextFieldInVector(getRootWidget()->getChildrenBehindWidget(this));
    if (!sibling) sibling = firstTextFieldInVector(getRootWidget()->getChildrenBeforeWidget(this));
    return sibling;
}

// --------------------------------------------------------------------------------------------------------
void KTextField::setText ( const std::string & t )
{
    KLabel::setText(t);
    cursor_pos = selection_pos = text.size();
}

// --------------------------------------------------------------------------------------------------------
void KTextField::printf ( const char * fmt ... )
{
    va_list argList;
    va_start(argList, fmt);
    setText(text + kStringPrintf(std::string(fmt), &argList));
    va_end(argList);
}

// --------------------------------------------------------------------------------------------------------
void KTextField::setPicked ( bool p )
{
    if (picked != p)
    {
        picked = p;
        if (picked)
        {
            cursor_pos = kMin((int)text.size(), x_offset + kMax(getLocatorWidgetPos().x, 0)/getColumnWidth());
            selection_pos = cursor_pos;
            KEventHandler::setFocusKeyHandler(this);
            getWindow()->setFocusWidget(this);
        }
        else
        {
            if (KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK]) 
            {
                notify();
            }
            getWindow()->setFocusWidget(NULL);
            KEventHandler::setFocusKeyHandler(NULL);
        }
        notifyReceivers(picked, KDL_NOTIFICATION_TYPE_TEXTFIELD_PICKED);
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextField::mouseMoved ( const KMouseEvent & event )
{
    KPosition mouseWidgetPos = event.pos - getScreenPos(); // position relative to widget
    // set new selection pos (we get this event only when mouse down)
    selection_pos = kMin((int)text.size(), x_offset + kMax(mouseWidgetPos.x, 0)/getColumnWidth());
    
    // scroll content if mouse outside window ...
    int columnWidth = getColumnWidth();
    if (mouseWidgetPos.x < -columnWidth) // mouseto the left
    {
        x_offset = kMax(0, x_offset-(-mouseWidgetPos.x/columnWidth));
    }
    else if (mouseWidgetPos.x > size.w + getColumnWidth()) // mouse to the right
    {
        // scroll to the right but don't overscroll
        int securePos = kMax(0, (int)text.size() - getTextCols());
        x_offset = kMin(securePos, x_offset+((mouseWidgetPos.x - size.w)/columnWidth));
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextField::doubleClicked ()
{
    selectAll();
}

// --------------------------------------------------------------------------------------------------------
bool KTextField::handleKey ( const KKey & key )
{    
    if (key.sym == SDLK_RETURN || key.sym == SDLK_TAB)
    {
        setPicked(false);
        
        if (KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK] == false) 
        {
            notify();
        }
        
        if (key.sym != SDLK_RETURN)
        {
            KTextField * textField;
            if (key.mod & KMOD_SHIFT)
            {
                textField = prevTextField();
            }
            else 
            {
                textField = nextTextField();
            }
            if (textField) 
            {
                textField->setPicked(true);
                textField->selectAll();
            }
        }
    }
    else if (key.sym == SDLK_BACKSPACE)
    {
        if (cursor_pos > 0 && cursor_pos == selection_pos)
        {
            text.erase(text.begin()+cursor_pos-1);
            cursor_pos--;
        }
        else
        {
            eraseSelection();
            cursor_pos = kMin(cursor_pos, selection_pos);
        }
        selection_pos = cursor_pos;
    }
    else if (key.sym == SDLK_RIGHT)
    {
        cursor_pos = kMin(cursor_pos+1, (int)text.size());
        if (!(key.mod & KMOD_SHIFT)) selection_pos = cursor_pos;
    }
    else if (key.sym == SDLK_LEFT)
    {
        cursor_pos = kMax(cursor_pos-1, 0);
        if (!(key.mod & KMOD_SHIFT)) selection_pos = cursor_pos;
    }
    else if (key.sym == SDLK_DELETE) // entf
    {
        if (cursor_pos < (int)text.size() && cursor_pos == selection_pos)
        {
            text.erase(text.begin()+cursor_pos);
        }
        else
        {
            eraseSelection();
        }
    }    
    else if (key.mod & KMOD_META)
    {
        if (key.sym == SDLK_a)
        {
            selectAll();
        }
        else if (key.sym == SDLK_x)
        {
            KEventHandler::copy_string = getSelection();
            eraseSelection();
        }
        else if (key.sym == SDLK_c)
        {
            KEventHandler::copy_string = getSelection();
        }
        else if (key.sym == SDLK_v)
        {
            eraseSelection();

            text.insert(cursor_pos, KEventHandler::copy_string);
            update();
            cursor_pos+=KEventHandler::copy_string.size(); 
            selection_pos = cursor_pos;
        }
    }
    else if (key.mod & KMOD_CTRL)
    {
        if (key.sym == SDLK_a) 
        {
            cursor_pos = selection_pos = 0;
        }
        else if (key.sym == SDLK_e)
        {
            cursor_pos = selection_pos = text.size();
        }
        else if (key.sym == SDLK_k)
        {
            selection_pos = text.size();
            eraseSelection();
        }
    }
    else if (key.character >= 32 ) // character input
    {
	eraseSelection();

        text.insert(text.begin()+cursor_pos, key.character);
        update();
        cursor_pos++;
        selection_pos = cursor_pos;
    }
    update();
    
    return true;
}

// --------------------------------------------------------------------------------------------------------
std::string KTextField::getSelection () const
{
    if (cursor_pos == selection_pos) return "";
    unsigned int start = kMin(cursor_pos, selection_pos);
    return text.substr (start, kMax(cursor_pos, selection_pos)-start);
}

// --------------------------------------------------------------------------------------------------------
void KTextField::selectAll ()
{
    cursor_pos = 0;
    selection_pos = text.size();
}

// --------------------------------------------------------------------------------------------------------
void KTextField::eraseSelection ()
{
    if (selection_pos != cursor_pos)
    {
        int minPos = kMin(cursor_pos, selection_pos);
        text.erase( text.begin()+minPos, text.begin()+kMax(cursor_pos, selection_pos));
        cursor_pos = selection_pos = minPos;
    }
}

// --------------------------------------------------------------------------------------------------------
void KTextField::render ()
{
    KWidget::render();
    
    glEnable(GL_SCISSOR_TEST);
    glScissor(getScreenPos().x, getScreenPos().y, size.w, size.h);
    
    int xOffset = (-x_offset * getColumnWidth());

    if (picked)
    {
        int cPos = xOffset + cursor_pos    * getColumnWidth();
        int sPos = xOffset + selection_pos * getColumnWidth();
        
        if (selection_pos != cursor_pos) // draw the selection
        {
            glPushAttrib (GL_CURRENT_BIT | GL_LIGHTING_BIT | GL_POLYGON_BIT);
            selection_color.glColor();
            glDisable (GL_CULL_FACE);
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            glBegin (GL_QUADS);
                glVertex2i (3 + cPos, 0);
                glVertex2i (3 + cPos, -getSize().h);
                glVertex2i (3 + sPos, -getSize().h);
                glVertex2i (3 + sPos, 0);
            glEnd();
            glPopAttrib();
        }
        glBegin(GL_LINES); // draw the cursor
        glVertex2i(3 + cPos, 0);
        glVertex2i(3 + cPos, -getSize().h);
        glEnd();
    }
    
    glPushMatrix();
    KWidget::flags[KDL_LABEL_FLAG_LARGE_FONT] ? glTranslatef(5, -15, 0) : glTranslatef(3, -10, 0);
    kDisplayString(text, KPosition(xOffset, 0), KWidget::flags[KDL_LABEL_FLAG_LARGE_FONT]);
    glPopMatrix();

    glDisable(GL_SCISSOR_TEST);    
}

// --------------------------------------------------------------------------------------------------------
void KTextField::update ()
{
    if (KWidget::flags[KDL_WIDGET_FLAG_FIXED_SIZE])
    {
        // avoid wasting available space ()
        x_offset = kMax(0, kMin(x_offset, (int)text.size() - getTextCols()));
        
        // make sure that cursor is in visible part of text
        if (cursor_pos - x_offset > getTextCols()) // right 
        {
            x_offset = cursor_pos - getTextCols();
        }
        else if (cursor_pos < x_offset) // left
        {
            x_offset = cursor_pos;
        }

        // try to make whole selection visible
        if (selection_pos - x_offset > getTextCols())
        {
            x_offset = kMin(cursor_pos, selection_pos - getTextCols());
        }
        else if ((int)selection_pos < x_offset)
        {
            x_offset = kMax (cursor_pos, selection_pos);
        }
    }
    else
    {
        KLabel::update();
    }
}

