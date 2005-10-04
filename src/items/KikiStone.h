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
    
                    KikiStone (KColor * c = NULL, bool slippery = false);
                   ~KikiStone ();
    virtual void	render	  ();

	virtual bool    isSlippery() { return slippery; }

	bool     slippery;
	KColor * color;
};

#endif

