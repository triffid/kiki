/*
 *  KikiBullet.h
 *  kiki
 */

#ifndef __KikiBullet
#define __KikiBullet

#include "KikiObject.h"
#include "KikiPos.h"

#include <KColor.h>

class KikiBot;

// __________________________________________________________________________________________________
class KikiBullet : public KikiObject
{
    KIKI_OBJECT_HEADER

    // ........................................................................ PROTECTED
    protected: // ..................................................................... PROTECTED

    float		size;
    KColor		color;
    KikiObject 		* src_object;

    bool		hitObjectAtPos		( const KikiPos & pos );

    enum {		ACTION_FLY,
                        ACTION_EXPLODE };
                        
    // ........................................................................ PUBLIC
    public: // ........................................................................ PUBLIC
                        KikiBullet 	 	();

    static void 	shootFromBot		( KikiBot * bot );
    
    void		performAction	 	( KikiAction * action );
    void		finishAction	 	( KikiAction * action );
    void		actionFinished	 	( KikiAction * action );
    
    void		display			();
};

#endif

