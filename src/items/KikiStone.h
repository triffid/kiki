/*
 *  KikiStone.h
 *  kiki
 */
 
#ifndef __KikiStone
#define __KikiStone

#include "KikiPushable.h"

// __________________________________________________________________________________________________
class KikiStone : public KikiPushable
{
    KIKI_OBJECT_HEADER
    
    public: // ........................................................................ PUBLIC
    
                        KikiStone 	 	();
    
    virtual void	render			();
};

#endif

