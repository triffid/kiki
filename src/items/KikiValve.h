/*
 *  KikiValve.h
 *  kiki
 */

#ifndef __KikiValve
#define __KikiValve

#include "KikiPushable.h"

// __________________________________________________________________________________________________

class KikiValve : public KikiPushable
{
    public: // ........................................................................ PUBLIC
    
                        KikiValve	( int face = KikiFace::PZ );
    
    virtual void	display 	();
    virtual void	render		();
    virtual void	performAction	( KikiAction * action );

    virtual void	setPosition	( const KVector & pos );
    bool		isActive	() const { return active; }
    
    protected: // ..................................................................... PROTECTED
    
    KIKI_OBJECT_HEADER

    enum {	ACTION_ROTATE = KikiPushable::ACTION_END,
                ACTION_END };

    int		face;
    float	angle;
    bool	clockwise;
    bool	active;
};

#endif

