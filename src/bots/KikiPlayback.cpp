/*
 *  KikiPlayback.cpp
 *  kiki
 */

#include "KikiPlayback.h"
#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiPlayer.h"
#include "KikiPython.h"

#include <KConsole.h>
#include <KFileTools.h>
#include <KKeyTools.h>


SDL_Thread * KikiPlayback::thread = NULL;
bool KikiPlayback::halt = false;
std::string KikiPlayback::next_world = "";

// __________________________________________________________________________________________________
int KikiPlayback::playback ( void * data )
{
    int last_event = 0;
    std::vector<KikiKeyRecord*> * records = (std::vector<KikiKeyRecord*>*)data;
    std::vector<KikiKeyRecord*>::iterator iter;
    for (iter = records->begin(); iter != records->end(); iter++)
    {
        SDL_Delay ((*iter)->time - last_event);

        if (halt) 
        {
            KConsole::printf ("playback stopped");
            return 0;
        }
        
        KKey key ((*iter)->key_name);
        
        if ((*iter)->type)
            Controller.player->handleKeyRelease (key);
        else
            Controller.player->handleKey (key);
        
        last_event = (*iter)->time;
    }
    
    if (next_world != "")
    {
        Controller.python->execute (kStringPrintf ("loadIntroWorld (\"%s\")", next_world.c_str())); // hack alert!
    }
    
    return 0;
} 

// __________________________________________________________________________________________________
void KikiPlayback::start (const std::string filename)
{
    static std::vector<KikiKeyRecord*> key_records;
    std::string record_string;
    record_string = kFileReadStringFromFile (filename);
    std::vector<std::string> lines = kStringGetComponents (record_string, "\n");
    std::vector<std::string>::iterator iter;
    
    if (thread) SDL_KillThread (thread);
    key_records.clear();
    
    iter = lines.begin();
    std::string world_name = (*iter).substr ((*iter).find (":") + 2);
    if (world_name != Controller.world->getName())
    {
        Controller.python->execute (kStringPrintf ("KikiPyWorld().create (\"%s\")", 
                                    world_name.substr (0,world_name.size()-1).c_str())); // hack alert!
    }
    iter++;

    Controller.world->setCameraMode (atoi ((*iter).substr ((*iter).find (":") + 2).c_str()));
    iter++;

    unsigned int open  = (*iter).find("[")+1;
    unsigned int close = (*iter).find("]");
    
    std::vector<std::string> values = kStringGetComponents ((*iter).substr(open, close-open), " ");
    KikiPos pos (atoi(values[0].c_str()), atoi(values[1].c_str()), atoi(values[2].c_str()));
    Controller.world->moveObjectToPos (Controller.player, pos);
    iter++;

    open = (*iter).find("<")+1;
    close = (*iter).find(">");
    values = kStringGetComponents ((*iter).substr(open, close-open), " ");
    KQuaternion orientation (atof(values[0].c_str()), atof(values[1].c_str()), 
                             atof(values[2].c_str()), atof(values[3].c_str()));
    Controller.player->setOrientation (orientation);
    iter++;
    
    for (; iter != lines.end(); iter++)
    {
        if (iter->empty() == false)
        {
            if (iter->find("world:") == 0)
            {
                next_world = (*iter).substr ((*iter).find (":") + 2);
            }
            else
            {
                std::vector<std::string> v = kStringGetComponents ((*iter), " ");
                key_records.push_back (new KikiKeyRecord (atoi(v[0].c_str()), v[1], atoi(v[2].c_str())));
            }
        }
    }

    halt = false;
    thread = SDL_CreateThread (KikiPlayback::playback, &key_records);
}

// __________________________________________________________________________________________________
void KikiPlayback::stop ()
{
    halt = true;
    thread = NULL;
}

