/*
 *  KikiPlayer.h
 *  kiki
 */

#ifndef __KikiPlayer
#define __KikiPlayer

#include "KikiBot.h"
#include <KKeyHandler.h>

class KikiRecorder;
class KikiPlayback;
class KProjection;
class KLightingProjection;

// __________________________________________________________________________________________________
typedef struct {

    const char * 	actionName;
    std::string *	keyName;
    
} KikiActionKey;

// __________________________________________________________________________________________________
class KikiPlayer : public KikiBot, public KKeyHandler
{
    public: // ........................................................................ PUBLIC
    
    // ........................................................................ (con/de)struction
                        KikiPlayer 	 	();
                        ~KikiPlayer 	 	();

    // ........................................................................ recorder
    void		startRecorder	 	( const std::string & file );    
    void		saveRecorder	 	();

    // ........................................................................ action
    void		initAction	 	( KikiAction * action );    
    void		performAction	 	( KikiAction * action );
    void		finishAction	 	( KikiAction * action );
    void    finishRotateAction ();

    // ........................................................................ display
    void		display		 	();
    void		die		 	();
    void		reborn		 	();
    void		reset			();

    const KColor &	getBodyColor     	();
    const KColor &	getTireColor		();
    const KColor &	getDeadColor 		() { return colors[1]; }

    // ........................................................................ projections
    KProjection * 	getProjection 		();
    KProjection * 	getBehindProjection	();
    KProjection * 	getFollowProjection	();

    // ........................................................................ keys
    static std::string	getKeyForAction		( const std::string & actionName );
    static std::string	getActionForKey		( const std::string & keyName );
    static void		setKeyForAction		( const std::string & keyName, const std::string & actionName );
    void 		recordKeyForAction	( const std::string & actionName );
    void		setRecordedKey		( const std::string & keyName );

    bool		handleKey	 	( const KKey & );
    bool		handleKeyRelease 	( const KKey & );

    KIKI_OBJECT_HEADER
 
    friend class	KikiWorld;
    friend class	KikiController;

    protected: // ..................................................................... PROTECTED
                            
    static std::string	jump_key;
    static std::string	push_key;
    static std::string	forward_key;
    static std::string	backward_key;
    static std::string	turn_left_key;
    static std::string	turn_right_key;
    static std::string	shoot_key;
    static std::string	look_up_key; 
    static std::string	look_down_key;
    static std::string	view_key;
    
    static KikiActionKey actionKeyMapping[];
    
    void		updatePosition ();
    KLightingProjection	* projection;
 
    float		look_angle;
    KikiAction *	look_action;
    
    KikiRecorder *	recorder;
    KikiPlayback *	playback;
    
    float		new_dir_sgn;
    int			rotate;

    // ........................................................................ action enum
    enum {		ACTION_LOOK_UP = KikiBot::ACTION_END,
                        ACTION_LOOK_DOWN,
                        ACTION_LOOK_RESET,
                        ACTION_END };
};

#endif
