/*
 *  KikiGear.h
 *  kiki
 */

#ifndef __KikiGear
#define __KikiGear

#include "KikiValve.h"

// __________________________________________________________________________________________________

class KikiGear : public KikiValve
{
    public: // ........................................................................ PUBLIC
    
                        KikiGear	( int face = KikiFace::PZ );
    
    virtual void	render		();
    virtual void	initAction	( KikiAction * action );
    virtual void	actionFinished	( KikiAction * action );
    
    virtual void	setActive	( bool active = true );
    virtual void	updateActive	();
    
    protected: // ..................................................................... PROTECTED
    
    KIKI_OBJECT_HEADER
    
    KikiPos * 			getNeighborDirections ();
    std::vector<KikiGear*>	getNeighborGears ();
};

#endif

