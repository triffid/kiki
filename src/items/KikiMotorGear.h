/*
 *  KikiMotorGear.h
 *  kiki
 */

#ifndef __KikiMotorGear
#define __KikiMotorGear

#include "KikiGear.h"

// __________________________________________________________________________________________________

class KikiMotorGear : public KikiGear
{
    public: // ........................................................................ PUBLIC
    
                        KikiMotorGear	( int face = KikiFace::PZ );
    
    void		updateActive	() {}
    void		render		();
        
    protected: // ..................................................................... PROTECTED
    
    KIKI_OBJECT_HEADER

};

#endif

