/*
 *  KikiStatusDisplay.cpp
 *  kiki
 */

#include "KikiStatusDisplay.h" 
#include "KikiBotStatus.h"
#include "KikiCellText.h"
#include "KikiAtom.h"

#include <KLightingProjection.h>
#include <KEventHandler.h>
#include <KDisplayTools.h>
#include <KConsole.h>

// __________________________________________________________________________________________________
KikiStatusDisplay::KikiStatusDisplay () : KPickHandler ()
{
    depth = INT_MAX - 100; // some below gui and text
    player_status = NULL;
    visible 	= false;
    
    projection  = new KLightingProjection (45.0, 0.1, 100.0);
    moves_atom = new KikiMovesAtom ();
    moves_text = new KikiCellText ("", 0.25);
}

// __________________________________________________________________________________________________
KikiStatusDisplay::~KikiStatusDisplay ()
{
    hide();
    delete projection;
    delete moves_atom;
    delete moves_text;
}

// __________________________________________________________________________________________________
void KikiStatusDisplay::setStatus ( KikiBotStatus * botStatus )
{ 
    player_status = botStatus;
    
    if (player_status)
    {
        show ();
    }
    else
    {
        hide ();
    }
}

// __________________________________________________________________________________________________
void KikiStatusDisplay::display ( int mode )
{
    if (visible && player_status)
    {
        projection->initProjection();
    
        glClear(GL_DEPTH_BUFFER_BIT);
        
        glTranslatef (-projection->getCurrentAspectRatio()*10.0, -10.0, -30.0);
        glScalef(4.0,4.0,4.0);
   
        float moves_value = (float)(player_status->getMinMoves()-player_status->getMoves())/8.0;

        moves_atom->setValue (moves_value);
        moves_atom->display();
        
        glTranslatef (0.0, 0.6, 0.0);
        moves_text->setText (kStringPrintf("%d (%d)", player_status->getMinMoves()-player_status->getMoves(), player_status->getMinMoves()));
        moves_text->display();
    }
}

