/*
 *  KikiGate.h
 *  kiki
 */

#ifndef __KikiGate
#define __KikiGate

#include "KikiSwitch.h"

// __________________________________________________________________________________________________
class KikiGate : public KikiSwitch
{
    KIKI_OBJECT_HEADER

    protected: // ..................................................................... PROTECTED
    
    float		value;
    void		renderBar	( float, float, float );
            
    public: // ........................................................................ PUBLIC
                        KikiGate	( bool open = false );
    
    void		bulletImpact	() {}
    
    void		newCellMate	( KikiObject * object );
    void		render		();
};

#endif

