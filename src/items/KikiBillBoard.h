/*
 *  KikiBillBoard.h
 *  kiki
 */

#ifndef __KikiBillBoard
#define __KikiBillBoard

#include "KikiObject.h"

// __________________________________________________________________________________________________
class KikiBillBoard : public KikiObject
{
    KIKI_OBJECT_HEADER

    public: // ........................................................................ PUBLIC
    
                        KikiBillBoard  	();

    virtual KColor	getColor	() = 0;
    virtual GLuint	getTextureId	() = 0;
    virtual void	display		();
    
    static  void 	displayTextureWithSize ( GLuint textureId, float size );

    protected: // ..................................................................... PROTECTED

    float  		size;
};

#endif

