/*
 *  KKeyRecorder.h
 *  kodisein
 */
 
#ifndef __KKeyRecorder
#define __KKeyRecorder

#include "KKeyHandler.h"

// --------------------------------------------------------------------------------------------------------
class KKeyRecorder : public KKeyHandler
{
    INTROSPECTION
    
    protected:
    
    bool		recording;
    std::string		recorded_sequence;
    unsigned int	num_recorded_keys;
    unsigned int	max_num_recorded_keys;
    
    public:
    
    			KKeyRecorder 		();
    
    void		startRecordingSequence	( KObject *, KSetStringPtr, int = 2 );
    void		stopRecording		();
    bool		isRecording		() const { return recording; }
    bool		handleKey		( const KKey & );
};

#endif

