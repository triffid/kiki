/*
 *  KKeySequenceField.h
 *  kodisein
 */

#ifndef __KKeySequenceField
#define __KKeySequenceField

#include "KWidget.h"
#include "KNotificationObject.h"

class KKeySequenceField : public KWidget, public KNotificationObject
{
    INTROSPECTION
    
    int				max_sequence_length;
    std::string			sequence;
    
    public:
                                KKeySequenceField	( const std::string &, int = 2 );
                                
    void 			setSequence 		( const std::string & );
    void			setPicked		( bool );
    KSize			getSize			() const;
    void			render			();
};

#endif

