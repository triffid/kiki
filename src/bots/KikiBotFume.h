/*
 *  KikiBotFume.h
 *  kiki
 */

#ifndef __KikiBotFume
#define __KikiBotFume

#include "KikiBillBoard.h"

// __________________________________________________________________________________________________
class KikiBotFume : public KikiBillBoard
{
    KIKI_OBJECT_HEADER

    protected: // ..................................................................... PROTECTED
    
    float		alpha_value;

    public: // ........................................................................ PUBLIC
    
                        KikiBotFume  	();
    
    void 		performAction	( KikiAction * action );
    void 		actionFinished	( KikiAction * action );
    
    KColor		getColor	();
    GLuint		getTextureId	();
};

#endif

