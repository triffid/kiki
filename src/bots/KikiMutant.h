/*
 *  KikiMutant.h
 *  kiki
 */

#ifndef __KikiMutant
#define __KikiMutant

#include "KikiBot.h"

// __________________________________________________________________________________________________
class KikiMutant : public KikiBot
{
    KIKI_OBJECT_HEADER
 
    friend class	KikiWorld;
 
    protected: // ..................................................................... PROTECTED
    
    virtual void	moveBot		();
        
    public: // ........................................................................ PUBLIC
    
                        KikiMutant	();
                        
    void		die		();
    void		bulletImpact	() { status->addHealth (-0.1); }

    const KColor &	getBodyColor	() { return colors[0]; }
    const KColor &	getDeadColor 	() { return colors[1]; }
    const KColor &	getTireColor	() { return colors[2]; }
};

#endif

