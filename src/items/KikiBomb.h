/*
 *  KikiBomb.h
 *  kiki
 */

#ifndef __KikiBomb
#define __KikiBomb

#include "KikiPushable.h"

// __________________________________________________________________________________________________
class KikiBomb : public KikiPushable
{
    KIKI_OBJECT_HEADER

    protected: // ..................................................................... PROTECTED

    float		angle;
    float		size;
    bool		splitted;
    void		splitterInDirection ( const KVector & direction );
    
    enum {		ACTION_ROTATE = KikiPushable::ACTION_END,
                        ACTION_IMPLODE,
                        ACTION_EXPLODE,
                        ACTION_END };
            
    public: // ........................................................................ PUBLIC
                        KikiBomb	();
    
    virtual void	performAction	( KikiAction * action );
    virtual void	actionFinished	( KikiAction * action );
    
    void		bulletImpact	();
    void		render		();
};

// __________________________________________________________________________________________________
class KikiBombSplitter : public KikiBomb
{
    KIKI_OBJECT_HEADER
  
    public: // ........................................................................ PUBLIC
    
                        KikiBombSplitter ( const KVector & direction );
};

#endif

