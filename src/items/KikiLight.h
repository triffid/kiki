/*
 *  KikiLight.h
 *  kiki
 */

#ifndef __KikiLight
#define __KikiLight

#include "KikiObject.h"

#include <KLight.h>

// __________________________________________________________________________________________________

class KikiLight : public KikiObject, public KLight
{
    public: // ........................................................................ PUBLIC
    
                KikiLight  	();
                KikiLight  	( const KVector & position, float radius = 4.0 );
                ~KikiLight 	();

    void	setPosition	( const KVector & position );
            
    void	display		();

    protected: // ..................................................................... PROTECTED

    KIKI_OBJECT_HEADER

    friend class		KikiWorld;
    friend class		KikiWire;
    
    float  			radius;
    float			halo_radius;
        
    void	setup 		();
};

// __________________________________________________________________________________________________

typedef std::vector<KikiLight*>	KikiLightList;
typedef KikiLightList::iterator	KikiLightIter;

#endif

