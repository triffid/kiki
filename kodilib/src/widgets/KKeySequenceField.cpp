/*
 *  KKeySequenceField.cpp
 *  kodisein
 */

#include "KKeySequenceField.h"
#include "KMenu.h"
#include "KColor.h"
#include "KKeyTools.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_2 (KKeySequenceField, KWidget, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KKeySequenceField::KKeySequenceField ( const std::string & s, int maxLength ) : KWidget ()
{
    sequence = s;
    max_sequence_length = maxLength;
    
    flags[KDL_WIDGET_FLAG_FIXED_SIZE]  	= false;
    flags[KDL_WIDGET_FLAG_FRAMED]  	= true;

    setBGColor(KColor(0.2, 0.2, 0.4, 0.5));
}


#define DEBUG false

// --------------------------------------------------------------------------------------------------------
void KKeySequenceField::setSequence ( const std::string & seq )
{
    KConsole::debugf(DEBUG, "KKeySequenceField::setSequence const std::string & seq = '%s'", seq.c_str());
    KConsole::debugf(DEBUG, "KKeySequenceField::setSequence nolooop here, so let's check how far we get");
    KConsole::debugf(DEBUG, "KKeySequenceField::setSequence set sequence");
    sequence = seq;
    if (KMenu::shortcut_recorder.isRecording())
    {
        KConsole::debugf(DEBUG, "KKeySequenceField::setSequence KMenu::shortcut_recorder.isRecording() == true");
        return;
    }
    KConsole::debugf(DEBUG, "KKeySequenceField::setSequence notifyReceivers(sequence)");
    notifyReceivers(sequence);
    KConsole::debugf(DEBUG, "KKeySequenceField::setSequence setPicked(false)");
    setPicked(false);
    KConsole::debugf(DEBUG, "KKeySequenceField::setSequence getRootWidget()->layout()");
    getRootWidget()->layout();
}

// --------------------------------------------------------------------------------------------------------
void KKeySequenceField::setPicked ( bool p )
{
    if (picked != p)
    {
        picked = p;
        if (picked)
        {
            sequence = "";
            KMenu::shortcut_recorder.startRecordingSequence((KObject*)this, 					                                                    				(KSetStringPtr)&KKeySequenceField::setSequence, max_sequence_length);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
KSize KKeySequenceField::getSize () const
{
    int width = kMax(20, kKeyGetDisplayWidthForKeySequence(sequence) + 5);
    return KSize(width, 20);
}

// --------------------------------------------------------------------------------------------------------
void KKeySequenceField::render ()
{
    KWidget::render();

    glPushMatrix();
    glTranslatef(5.0, -13.0, 0.0);

    if (sequence != "") // draw the sequence
    {
        glColor4f(0.5, 0.5, 1.0, 1.0);
        kKeyDisplayKeySequence(sequence, KPosition());
    }
    
    if (picked) // draw the cursor
    {
        int cPos = kKeyGetDisplayWidthForKeySequence(sequence)-5;
    
        glBegin(GL_LINES); 
        glVertex2i(cPos, -3);
        glVertex2i(cPos, 10);
        glEnd();
    }
        
    glPopMatrix();
}

