/*
 *  KNumberField.cpp
 *  kodisein
 */

#include "KNumberField.h"
#include "KConsole.h"
#include "KKey.h"

KDL_CLASS_INTROSPECTION_1 (KNumberField, KTextField)

// --------------------------------------------------------------------------------------------------------
KNumberField::KNumberField ( GLfloat number ) : KTextField ("")
{
    KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK] = true;
    setTextCols(9);
    setText(kStringPrintf("%g", number));
}

// --------------------------------------------------------------------------------------------------------
void KNumberField::notify ()
{
    KTextField::notify();
    notifyReceivers(getValue());
}

// --------------------------------------------------------------------------------------------------------
bool KNumberField::handleKey ( const KKey & key )
{
    if (key.sym == SDLK_DELETE || key.sym == SDLK_BACKSPACE || key.sym == SDLK_TAB ||
        key.sym == SDLK_RETURN || key.sym == SDLK_LEFT || key.sym == SDLK_RIGHT ||
        (key.character >= '+'  && key.character <= '.') ||
        (key.character >= '0' && key.character <= '9') || 
        (key.mod > 1))
    {
        return KTextField::handleKey (key);
    }
    
    return true;
}

// --------------------------------------------------------------------------------------------------------
GLfloat KNumberField::getValue ( )
{
    return atof(text.c_str());
}


