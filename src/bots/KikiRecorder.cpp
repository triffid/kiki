/*
 *  KikiRecorder.cpp
 *  kiki
 */

#include "KikiRecorder.h"

#include "KikiController.h"
#include "KikiWorld.h"
#include "KikiPlayer.h"

#include <KConsole.h>
#include <KFileTools.h>

// __________________________________________________________________________________________________
KikiRecorder::KikiRecorder ( const std::string & file )
{
    file_name = file;
    start_time = 0;
    
    if (start_time == 0) 
    {
        start_time = Controller.getTime();
        key_records.push_back (new KikiKeyRecord ("world: " + Controller.world->getName()));
        key_records.push_back (new KikiKeyRecord 
                                    (kStringPrintf ("camera: %d", Controller.world->getCameraMode())));
        KikiPos pos = Controller.player->getPos();
        std::string position_string =  kStringPrintf ("pos: [%d %d %d]", pos.x, pos.y, pos.z);
        key_records.push_back (new KikiKeyRecord (position_string));        
        KQuaternion orientation = Controller.player->getOrientation();
        std::string orientation_string =  kStringPrintf ("orientation: <%f %f %f %f>", 
                                        orientation.w, orientation.x, orientation.y, orientation.z);
        key_records.push_back (new KikiKeyRecord (orientation_string));        
    }
}

// __________________________________________________________________________________________________
void KikiRecorder::recordKey ( const KKey & key )
{
    if (key_records.back()->key_name != key.name || 
        key_records.back()->type != KikiKeyRecord::KEY_PRESS)
    {
        key_records.push_back (new KikiKeyRecord (Controller.getTime() - start_time, 
                                                    key.name, KikiKeyRecord::KEY_PRESS));
    }
}

// __________________________________________________________________________________________________
void KikiRecorder::recordKeyRelease ( const KKey & key )
{
    if (key_records.back()->key_name != key.name || 
        key_records.back()->type != KikiKeyRecord::KEY_RELEASE)
    {
        key_records.push_back (new KikiKeyRecord (Controller.getTime() - start_time, 
                                                    key.name, KikiKeyRecord::KEY_RELEASE));
    }
}

// __________________________________________________________________________________________________
void KikiRecorder::reset ()
{
    while (key_records.empty() == false)
    {
        delete key_records.back();
        key_records.pop_back();
    }
    start_time = 0;
}

// __________________________________________________________________________________________________
void KikiRecorder::save ()
{    
    //............................................................ 'serialize' the records
    std::string key_record_string;
    std::vector<KikiKeyRecord*>::iterator iter;
    for (iter = key_records.begin(); iter != key_records.end(); iter++)
    {
        if ((*iter)->type < KikiKeyRecord::OTHER)
        {
            key_record_string.append (kStringPrintf ("%d %s %d\n", (*iter)->time, 
                                                    (*iter)->key_name.c_str(), (*iter)->type));
        }
        else
        {
            key_record_string.append (kStringPrintf ("%s\n", (*iter)->key_name.c_str()));
        }
    }
    
    //............................................................ save the file
    if (kFileWriteStringToFile (key_record_string, file_name)) 
    {
        KConsole::printf ("key record saved to file %s", kFileAbsPathName (file_name).c_str());
    }
    else // ooops...
    {
        KConsole::printf ("WARNING unable to write record to file %s", kFileAbsPathName (file_name).c_str());
    }

    reset ();
}
