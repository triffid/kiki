/*
 *  KikiWall.h
 *  kiki
 */
 
#ifndef __KikiWall
#define __KikiWall

#include "KikiObject.h"

// __________________________________________________________________________________________________
class KikiWall : public KikiObject
{
    KIKI_OBJECT_HEADER
        
    public: // ........................................................................ PUBLIC
                        KikiWall 	 	() {}
    void		render			();
};

#endif

