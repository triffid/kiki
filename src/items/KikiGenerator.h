/*
 *  KikiGenerator.h
 *  kiki
 */

#ifndef __KikiGenerator
#define __KikiGenerator

#include "KikiGear.h"

// __________________________________________________________________________________________________

class KikiGenerator : public KikiGear
{
    public: // ........................................................................ PUBLIC
    
                        KikiGenerator	( int face = KikiFace::PZ );
    
    void		render		();
    void		setActive	( bool active = true );
    void		activateWires	();
        
    protected: // ..................................................................... PROTECTED
    
    KIKI_OBJECT_HEADER

};

#endif

