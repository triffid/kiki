/*
 *  KikiBot.h
 *  kiki
 */

#ifndef __KikiBot
#define __KikiBot

#include "KikiPushable.h"
#include "KikiBotStatus.h"

class KikiAction;

// __________________________________________________________________________________________________
class KikiBot : public KikiPushable
{
    KIKI_OBJECT_HEADER
 
    public: // ........................................................................ PUBLIC
    
                        KikiBot		();
                        ~KikiBot	();
    
    virtual void	initAction	( KikiAction * action );
    virtual void	performAction	( KikiAction * action );
    virtual void	finishAction	( KikiAction * action );
    virtual void	actionFinished	( KikiAction * action );

    void		setSpiked	( bool b ) { spiked = b; }
    void		setMove		( bool b ) { move = b; }
    
    virtual void	die		();
    bool		isDead		() const { return (status->getHealth() == 0.0); }
	bool		isFalling   () const;

    void		renderBody	();
    virtual void	render		();
    virtual void	reset		();
    
    virtual const KColor & getBodyColor	() = 0;
    virtual const KColor & getDeadColor () = 0;
    virtual const KColor & getTireColor	() = 0;

    KikiPos		getDown		() { return -(orientation.rotate(KVector(0,1,0))); }
    KikiPos		getUp		() { return   orientation.rotate(KVector(0,1,0)); }
    KikiPos		getDir		() { return dir_sgn * orientation.rotate(KVector(0,0,1)); }
    KVector		getCurrentDir	() { return current_orientation.rotate(KVector(0,0,1)).normal(); }
    
    KikiBotStatus *	getStatus	() { return status; }
    
    enum {  ACTION_NOOP = KikiPushable::ACTION_END,
            ACTION_FORWARD,
            ACTION_CLIMB_UP,
            ACTION_CLIMB_DOWN,
            ACTION_TURN_LEFT,
            ACTION_TURN_RIGHT,
            ACTION_JUMP,
            ACTION_JUMP_FORWARD,
            ACTION_FALL_FORWARD,
            ACTION_SHOOT,
            ACTION_END
    };

    protected: // ..................................................................... PROTECTED

    bool		move;
    bool		push;
    bool		jump;
    bool		shoot;
    bool		jump_once;
    
    bool		spiked;
    bool		died;
    
    float		dir_sgn;

    KikiAction * 	rotate_action;

    KikiBotStatus *	status;
    
    virtual void	moveBot		();
    
    // .................................... private
    private:

    KQuaternion		rotate_orientation;
    KQuaternion		climb_orientation;
    KQuaternion		rest_orientation;

    float		left_tire_rot;
    float		right_tire_rot;
    
    unsigned int	last_fume;

};

#endif
