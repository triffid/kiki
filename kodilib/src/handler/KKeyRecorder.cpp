/*
 *  KKeyRecorder.cpp
 *  kodisein
 */

#include "KKeyRecorder.h"
#include "KEventHandler.h"
#include "KKey.h"

KDL_CLASS_INTROSPECTION_1	(KKeyRecorder, KKeyHandler)

// --------------------------------------------------------------------------------------------------------
KKeyRecorder::KKeyRecorder () : KKeyHandler ()
{
    max_num_recorded_keys = INT_MAX;
    recorded_sequence = "";
    num_recorded_keys = 0;
    recording = false;
}

// --------------------------------------------------------------------------------------------------------
void KKeyRecorder::startRecordingSequence ( KObject * rec, KSetStringPtr cb, int numKeys )
{
    max_num_recorded_keys = numKeys;
    recorded_sequence = "";
    num_recorded_keys = 0;
    recording = true;
    
    removeAllReceivers();
        
    addReceiverCallback(rec, cb);
    
    KEventHandler::setFocusKeyHandler(this);
}

// --------------------------------------------------------------------------------------------------------
void KKeyRecorder::stopRecording ()
{
    recording = false;
    KEventHandler::setFocusKeyHandler(NULL);
    notifyReceivers(recorded_sequence);
}

// --------------------------------------------------------------------------------------------------------
bool KKeyRecorder::handleKey ( const KKey & key )
{
    if (key.name == "RETURN")
    {
        stopRecording(); 
        return true;
    }
    
    if (recorded_sequence == "")
    {
        recorded_sequence = key.name;
    }
    else
    {
        recorded_sequence += " " + key.name;
    }

    num_recorded_keys++;
        
    if (num_recorded_keys >= max_num_recorded_keys)
    {
        stopRecording();
        return true;
    }

    notifyReceivers(recorded_sequence);
    
    return true;
}


