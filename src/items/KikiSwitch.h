/*
 *  KikiSwitch.h
 *  kiki
 */
 
#ifndef __KikiSwitch
#define __KikiSwitch

#include "KikiObject.h"

class KikiLight;

// __________________________________________________________________________________________________
class KikiSwitch : public KikiObject
{
    KIKI_OBJECT_HEADER

    protected:
    
    bool		active;
    int			sound_on, sound_off;
    float		angle;
    KikiLight *		light;
    
    enum {		ACTION_TOGGLE,
                        ACTION_ROTATE,
                        ACTION_END };
    
    public: // ........................................................................ PUBLIC
                        KikiSwitch	( bool on = false );
                        ~KikiSwitch	();
    
    void		lightDeleted	();
    virtual void	performAction	( KikiAction * action );
    
    void		bulletImpact	() { toggle(); } 
    
    void		toggle		() { setActive(!active); }
    void		setActive	( bool active );
    bool		isActive	() const { return active; }
    
    void		render	 	();
    void		setPosition	( const KVector & position );
};

#endif

