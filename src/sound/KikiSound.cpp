/*
 *  KikiSound.cpp
 */

#ifndef WIN32
#include <sys/param.h>
#endif

#include "KikiSound.h"
#include "KikiWorld.h"
#include "KikiGUI.h"

#include <KLabel.h>
#include <KStringTools.h>
#include <KConsole.h>
#include <KProjection.h>
#include <KFileTools.h>

#include <SDL.h>

// __________________________________________________________________________________________________
typedef struct _KikiSound 
{    
    int sound_id;
    const char * sound_file;
    float sound_volume;
        
} KikiSoundData;

// __________________________________________________________________________________________________
static KikiSoundData KikiSounds[] = 
{
    {	KikiSound::BOT_MOVE, 			"bot_move.wav",			0.2 },
    {	KikiSound::BOT_JUMP,			"bot_jump.wav",		0.7 },
    {	KikiSound::BOT_LAND,			"bot_land.wav", 		0.7 },
    {	KikiSound::BOT_SPIKED,			"bot_move.wav", 		1.0 },
    {	KikiSound::BOT_HEALTH_ALERT,		"bot_health_alert.wav", 	1.0 },
    {	KikiSound::BOT_DEATH,			"bot_death.wav",		1.0 },
    {	KikiSound::BOT_NO_ENERGY,		"bot_no_energy.wav",		1.0 },
    {	KikiSound::BULLET_SHOT,			"bullet_shot.wav",		1.0 },
    {	KikiSound::BULLET_HIT_WALL,		"bullet_hit_wall.wav",		1.0 }, 
    {	KikiSound::BULLET_HIT_OBJECT,		"bullet_hit_object.wav",	1.0 },
    {	KikiSound::BULLET_HIT_PLAYER,		"bullet_hit_player.wav",	1.0 },
    {	KikiSound::BULLET_HIT_MUTANT,		"bullet_hit_mutant.wav",	1.0 },
    {	KikiSound::STONE_MOVE,			"stone_move.wav",		1.0 },
    {	KikiSound::STONE_LAND,			"stone_land.wav",		1.0 },
    {	KikiSound::SWITCH_ON,			"switch_on.wav",		1.0 },
    {	KikiSound::SWITCH_OFF,			"switch_on.wav",		0.5 },
    {	KikiSound::ATOM_BIRTH,			"atom_digest.wav",		1.0 },
    {	KikiSound::ATOM_DIGEST,			"atom_digest.wav",		1.0 },
    {	KikiSound::SPIKES_START,		"bot_move.wav",			1.0 },
    {	KikiSound::MENU_FADE,			"menu_fade.wav",		1.0 },
    {	KikiSound::MENU_ITEM,			"menu_item.wav",		1.0 },
    {	KikiSound::MENU_SELECT,			"menu_select.wav",		1.0 },
    {	KikiSound::MENU_ABORT,			"menu_abort.wav",		1.0 },
    {	KikiSound::GATE_OPEN,			"gate_open.wav",		1.0 },
    {	KikiSound::GATE_CLOSE,			"gate_close.wav",		1.0 },
    {	KikiSound::GATE_WARP,			"gate_warp.wav",		1.0 },
    {	KikiSound::BOMB_EXPLODE,		"bomb_explode.wav",		1.0 },
    {	KikiSound::BOMB_SPLITTER,		"bomb_splitter.wav",		1.0 },
    {	KikiSound::GEAR_ON,			"gear_on.wav",			1.0 },
    {	KikiSound::GEAR_OFF,			"gear_off.wav",			1.0 },
    {	KikiSound::GENERATOR_ON,		"generator_on.wav",		1.0 },
    {	KikiSound::GENERATOR_OFF,		"generator_off.wav",		1.0 },
    {	KikiSound::MOTOR,			"bomb_splitter.wav",		1.0 },
};

// __________________________________________________________________________________________________
KikiSound::KikiSound ()
{
    sound_volume  = 50;
    mute	  = false;
    
    int frequency = MIX_DEFAULT_FREQUENCY;
    Uint16 format = MIX_DEFAULT_FORMAT;
    int channels  = MIX_DEFAULT_CHANNELS;
    int chunksize = 2048;
    num_channels  = 0;
    
    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) // open mixer
    {
        KConsole::printError (kStringPrintf ("KikiSound::KikiSound couldn't open audio mixer: %s\n",
                                                                                    SDL_GetError()));
        return;
    }

    num_channels = Mix_AllocateChannels (MIX_CHANNELS); // create channels
    Mix_Volume (-1, sound_volume); // set the start volume
    
    // title song
#ifndef _WINDOWS
    std::string song_path = kFileNativePath(Controller.getKikiHome() + "/sound/" + "title_song.mp3");
    Mix_Music * music = Mix_LoadMUS(song_path.c_str());
    if(!music) 
    {
        KConsole::printf ("unable to load title song (\"%s\"): %s\n", song_path.c_str(), Mix_GetError());
    }
    else
    {
        if (Mix_PlayMusic(music, 0) == -1) 
        {
            KConsole::printf("unable to play title song: %s\n", Mix_GetError());
        }
    }
#endif

    int soundIndex = 0;
    while (soundIndex < KikiSound::END)
    {
        loadSound (KikiSounds[soundIndex].sound_file);
        soundIndex++;
    }
}

// __________________________________________________________________________________________________
KikiSound::~KikiSound ()
{
    while (snd_chunks.empty() == false)
    {
        Mix_FreeChunk(snd_chunks.back());
        snd_chunks.pop_back();
    }
}

// __________________________________________________________________________________________________
void KikiSound::setMute ( bool m )
{ 
    if (m != mute)
    {
        mute = m;
    }
}
 
// __________________________________________________________________________________________________
void KikiSound::setSoundVolume ( int v )
{ 
    sound_volume = v;
    if (num_channels) Mix_Volume (-1, sound_volume);
}

// __________________________________________________________________________________________________
Mix_Chunk * KikiSound::loadWav ( const std::string & file )
{
    return Mix_LoadWAV (file.c_str());
}

// __________________________________________________________________________________________________
bool KikiSound::loadSound ( const std::string & file )
{
    if (num_channels == 0) return false;

    std::string file_path = kFileNativePath(Controller.getKikiHome() + "/sound/" + file);
    Mix_Chunk * chunk = loadWav(file_path.c_str());

    if (chunk == NULL)
    {
        KConsole::printError(kStringPrintf("KikiSound::loadSound unable to load sound file %s",
                                                                                    file_path.c_str()));
        return false;
    }
    
    snd_chunks.push_back(chunk);
        
    return true;
}

// __________________________________________________________________________________________________
int KikiSound::getFreeChannel ()
{
    for (int i = 0; i < num_channels; i++)
    {
        if (Mix_Playing(i) == false) 
        {
            return i;
        }
    }
    return -1;
}
    
// __________________________________________________________________________________________________
void KikiSound::playSound ( int sndId, float volume, int loops )
{
    if (mute || num_channels == 0) return;
    
    if (sndId >= (int)snd_chunks.size() || snd_chunks[sndId] == NULL) 
    {
        KConsole::printError(kStringPrintf("KikiSound::playSound unknown sound id %d\n", sndId));
        return;
    }
    
    int freeChannel = getFreeChannel();
    
    if (freeChannel < 0) return;
    
    if (volume < 0)
    {
        volume = KikiSounds[sndId].sound_volume;
    }
    
    Mix_UnregisterAllEffects (freeChannel);
    Mix_VolumeChunk (snd_chunks[sndId], (int)(MIX_MAX_VOLUME * volume));
    Mix_PlayChannel (freeChannel, snd_chunks[sndId], loops);
}

// __________________________________________________________________________________________________
void KikiSound::playSoundAtPos ( int sndId, const KikiPos & pos, float factor )
{
    if (mute || num_channels == 0) return;

    if (sndId >= (int)snd_chunks.size() || snd_chunks[sndId] == NULL) 
    {
        KConsole::printError(kStringPrintf("KikiSound::playSoundAtPos unknown sound id %d\n", sndId));
        return;
    }

    int freeChannel = getFreeChannel();

    if (freeChannel < 0) return;

    float volume;
    float maxDistance = Controller.world->getMaxDistance();
    
    KProjection * projection = Controller.world->getProjection();
    if (projection == NULL) return;
    KVector cameraToPos (pos - projection->getPosition());
    volume = (1.0 - (cameraToPos.length() / maxDistance));
    volume *= volume * factor;
    
    if (volume > 0.05) 	// very low volume sounds just waste cpu time :-)
    {
        float pan = (projection->getXVector() * cameraToPos.normal()) / 2.0 + 0.5;
        volume *= MIX_MAX_VOLUME;
        Mix_SetPanning (freeChannel, (Uint8)(volume * (1.0 - pan)), (Uint8)(volume * pan));
        Mix_PlayChannel (freeChannel, snd_chunks[sndId], 0);
    }
}
