/*
 *  KikiMotorCylinder.h
 *  kiki
 */

#include "KikiObject.h"

// __________________________________________________________________________________________________
class KikiMotorCylinder : public KikiObject
{
    KIKI_OBJECT_HEADER
    
    public: // ........................................................................ PUBLIC
                        KikiMotorCylinder 	( int face = KikiFace::PZ );
                        
    void		setActive		( bool active );
    
    void		performAction		( KikiAction * action );
    void		finishAction		( KikiAction * action );
    void		render			();
    
    protected: // ..................................................................... PROTECTED

    enum {		ACTION_TUCKER };
    
    bool		active;
    float		value;
};

