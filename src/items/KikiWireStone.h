/*
 *  KikiWireStone.h
 *  kiki
 */
 
#ifndef __KikiWireStone
#define __KikiWireStone

#include "KikiStone.h"

class KikiWire;

// __________________________________________________________________________________________________

class KikiWireStone : public KikiStone
{    
    public: // ........................................................................ PUBLIC
    
                        KikiWireStone 	 	();

    void		setPosition		( const KVector & pos );
    void		setCurrentPosition	( const KVector & pos );
    void		initAction		( KikiAction * action );

    protected: // ..................................................................... PROTECTED

    KIKI_OBJECT_HEADER

    KikiWire * 		wires[6];
    
    bool		isFreePos		( const KVector & pos );
};

#endif
