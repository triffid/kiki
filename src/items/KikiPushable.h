/*
 *  KikiPushable.h
 *  kiki
 */
 
#ifndef __KikiPushable
#define __KikiPushable

#include "KikiObject.h"

// __________________________________________________________________________________________________
class KikiPushable : public KikiObject
{
    KIKI_OBJECT_HEADER
    
    friend class	KikiWorld;
    
    protected: // ..................................................................... PROTECTED
    
    enum {		ACTION_PUSH, 
                        ACTION_FALL,
                        ACTION_END };
                        
    int			pushing_sound, landing_sound;
    KikiObject *	pusher;
        
    public: // ........................................................................ PUBLIC
    
                        KikiPushable	();
                        
    virtual void	pushedByObjectInDirection 
                                        ( KikiObject * object, const KVector & direction, int duration );
    
    virtual void	initAction	( KikiAction * action );
    virtual void	performAction	( KikiAction * action );
    virtual void	finishAction	( KikiAction * action );
    virtual void	actionFinished	( KikiAction * action );
};

#endif

