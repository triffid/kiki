/*
 *  KikiSpikes.cpp
 *  kiki
 */

#include "KikiSpikes.h"
#include "KikiWorld.h"
#include "KikiPlayer.h"
#include "KikiSound.h"

#include <KDisplayTools.h>
#include <KConsole.h>

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiSpikes, KikiObject )
KIKI_OBJECT_VALUES 		( KikiSpikes, false )

// __________________________________________________________________________________________________
#define MIN_SPIKE_VALUE	0.00f

// __________________________________________________________________________________________________
unsigned int 	KikiSpikes::spike_list = 0;

// __________________________________________________________________________________________________
KikiSpikes::KikiSpikes ( int f ) : KikiObject()
{                            
    face	= f;
    spiked_bot	= NULL;
    spike	= MIN_SPIKE_VALUE;
     
    addAction (new KikiAction (this, 0, "spike", 2000, KikiAction::REPEAT));
    startTimedAction (actions[0]);
        
    if (spike_list == 0)
    {
        initialize();
    }
}

// __________________________________________________________________________________________________
void KikiSpikes::initialize ()
{
    if (spike_list) 
    {
        glDeleteLists (spike_list, 1);
    }
    
    spike_list = glGenLists(1);
    if (spike_list)
    {
        glNewList (spike_list, GL_COMPILE);

        int subdiv = 8;
        int numSpikes = 3;
        float offset = 1.0/(2.0*numSpikes)-0.5;
        float radius = 0.1;
        
        for (int i = 0; i < numSpikes; i++)
        {
            for (int j = 0; j < numSpikes; j++)
            {
                glPushMatrix();
                glTranslated(i/(float)numSpikes+offset, j/(float)numSpikes+offset, 0.0);
                kDisplaySolidCylinder(radius, 0.0, 1.0, subdiv);
                glPopMatrix();
            }
        }
        
        glEndList();
    }
    else
    {
        KConsole::printError("KikiSpikes::KikiSpikes unable to create display list");
    }
}

// __________________________________________________________________________________________________
void KikiSpikes::performAction ( KikiAction * action )
{
    float relTime = action->getRelativeTime();
    
    if (relTime < 0.33) // ........................... spikes grow
    {
        spike = kMax (relTime, MIN_SPIKE_VALUE);
        if (relTime == 0)
        {
            Controller.sound->playSoundAtPos (KikiSound::SPIKES_START, position);
        }
    }
    else // .......................................... spikes shrink or rest
    {
        spike = kMax(0.66 - relTime, MIN_SPIKE_VALUE);
    }
    
    if (spiked_bot)
    {
	if (relTime == 0) 
        {
            // ......................................................... spike bot
            spikeBot (spiked_bot);
        }
        else if (relTime < 0.66)
        {
            // ......................................................... punish bot
            spiked_bot->getStatus()->addHealth (-action->getRelativeDelta()/5.0);
        }
        else
        {
            // ......................................................... release bot
            spiked_bot->setSpiked(false);
        }
    }
}

// __________________________________________________________________________________________________
void KikiSpikes::spikeBot ( KikiBot * bot )
{
    if (bot->isDead()) 
    {
        spiked_bot = NULL;
    }
    else
    {
        spiked_bot = bot;
        spiked_bot->setSpiked(true);
        
        if (spiked_bot == Controller.player)
        {
            Controller.sound->playSound(KikiSound::BOT_SPIKED);
        }
    }
}

// __________________________________________________________________________________________________
void KikiSpikes::newCellMate ( KikiObject * object )
{
    if (object->getClassId() >= KikiBot::classId()) // bot spiked
    {
        if (spike != MIN_SPIKE_VALUE)
        {
            spikeBot ((KikiBot*)object);
        }
        else
        {
            spiked_bot = (KikiBot*)object;
        }
    }
}

// __________________________________________________________________________________________________
void KikiSpikes::cellMateLeft ( KikiObject * object )
{
    if (object == spiked_bot)
    {
        spiked_bot = NULL;
    }
}

// __________________________________________________________________________________________________
void KikiSpikes::render ()
{
    KikiFace::transformationForFace (face);
    colors[KikiSpikes_base_color].glColor();

    glScalef (1.0, 1.0, spike);

    glCallList(spike_list);    
}
