/*
 *  KikiTest.h
 *  kiki
 */
 
#ifndef __KikiTest
#define __KikiTest

#include "KikiObject.h"

// __________________________________________________________________________________________________
class KikiTest1 : public KikiObject
{
    KIKI_OBJECT_HEADER
    
    public: // ........................................................................ PUBLIC
                        KikiTest1 	 	() : KikiObject () {}
    void		render			();
};

// __________________________________________________________________________________________________
class KikiTest2 : public KikiObject
{
    KIKI_OBJECT_HEADER
    
    public: // ........................................................................ PUBLIC
                        KikiTest2 	 	() : KikiObject () {}
    void		render			();
};

#endif

