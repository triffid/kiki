/*
 *  KikiAtom.h
 *  kiki
 */
 
#ifndef __KikiAtom
#define __KikiAtom

#include "KikiObject.h"

class KikiNeutron;

// __________________________________________________________________________________________________
class KikiAtom : public KikiObject
{
    KIKI_OBJECT_HEADER

    protected: // ..................................................................... PROTECTED

    static int		num_neutrons;
    
    std::vector<KikiNeutron*> neutrons;
    float		nucleus_size;
    float		value;
    
    void		addNeutron 	();
    void		deleteNeutron	();
    
    public: // ........................................................................ PUBLIC
                        KikiAtom	( int neutrons = 9 );
                        ~KikiAtom	();
    
    void		initAction	( KikiAction * action );
    void		performAction	( KikiAction * action );
    void		actionFinished	( KikiAction * action );
    void		setValue	( float value );
    virtual float	getValue	() const { return value; }
    void		render	 	();
    
    virtual const KColor & getNucleusColor () = 0;
    virtual const KColor & getNeutronColor () = 0;
};

// __________________________________________________________________________________________________
class KikiMovesAtom : public KikiAtom
{
    KIKI_OBJECT_HEADER
    
    public: // ........................................................................ PUBLIC
                        KikiMovesAtom	( int neutrons = 9 ) : KikiAtom (neutrons) {}
    const KColor & 	getNucleusColor () { return colors[0]; }
    const KColor & 	getNeutronColor () { return colors[1]; }
};

// __________________________________________________________________________________________________
class KikiValueAtom : public KikiAtom
{
    KIKI_OBJECT_HEADER
    
    protected: // ..................................................................... PROTECTED
    
    float		range[2];
    float		increment;
    
    float		mapValue 	( float unmapped_value ) const;
    float		unmapValue	( float mapped_value ) const;
    
    public: // ........................................................................ PUBLIC
                        KikiValueAtom	( float range_start = 0.0, float range_end = 1.0, 
                                          float start_value = 1.0, int levels = 9 );
                                          
    float		getValue	() const { return unmapValue(value); }                        
    void		bulletImpact	();
    const KColor & 	getNucleusColor () { return colors[0]; }
    const KColor & 	getNeutronColor () { return colors[1]; }
};

#endif

