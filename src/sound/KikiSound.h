/*
 *  KikiSound.h
 */

#ifndef __KikiSound
#define __KikiSound

#include "KikiController.h"

#include <SDL_mixer.h>

// __________________________________________________________________________________________________
class KikiSound
{
    protected: // ..................................................................... PROTECTED
    
    int  			num_channels;
        
    std::vector<Mix_Chunk *> 	snd_chunks;
    
    int 			sound_volume;
    bool			mute;

    public: // ........................................................................ PUBLIC

    enum {	BOT_MOVE,
                BOT_JUMP,
                BOT_LAND,
                BOT_SPIKED,
                BOT_HEALTH_ALERT,
                BOT_DEATH,
                BOT_NO_ENERGY, 
                BULLET_SHOT,
                BULLET_HIT_WALL, 
                BULLET_HIT_OBJECT, 
                BULLET_HIT_PLAYER, 
                BULLET_HIT_MUTANT, 
                STONE_MOVE,
                STONE_LAND,
                SWITCH_ON,
                SWITCH_OFF,
                ATOM_BIRTH,
                ATOM_DIGEST,
                SPIKES_START,
                MENU_FADE,
                MENU_ITEM,
                MENU_SELECT,
                MENU_ABORT,
                GATE_OPEN,
                GATE_CLOSE,
                GATE_WARP,
                BOMB_EXPLODE,
                BOMB_SPLITTER,
                GEAR_ON,
                GEAR_OFF,
                GENERATOR_ON,
                GENERATOR_OFF,
                MOTOR,
                END };

                KikiSound	();
                ~KikiSound	();

    void	toggleMute	() { setMute (!mute); }
    void	setMute		( bool b );
    bool	isMute		() const { return mute; }
    
    void	setSoundVolume	( int v );
    int		getSoundVolume	() const { return sound_volume; }

    int		getFreeChannel	();

    Mix_Chunk * loadWav		( const std::string & file );    
    
    bool	loadSound	( const std::string & file );
    void	playSound	( int sndId, float volume = -1.0, int loops = 0 );
    void	playSoundAtPos	( int sndId, const KikiPos & pos, float = 1.0 );
};

#endif

