/*
 *  KikiStatusDisplay.h
 *  kiki
 */

#ifndef __KikiStatusDisplay
#define __KikiStatusDisplay

#include <KPickHandler.h>

class KikiBotStatus;
class KikiCellText;
class KikiMovesAtom;

// __________________________________________________________________________________________________
class KikiStatusDisplay : public KPickHandler
{
    protected: // ..................................................................... PROTECTED

    KikiMovesAtom *	moves_atom;
    KikiCellText *	moves_text;
    KikiBotStatus *	player_status;
    bool		visible;

    public: // ........................................................................ PUBLIC
    
                        KikiStatusDisplay ();
                        ~KikiStatusDisplay ();
                        
    void		setStatus	( KikiBotStatus * botStatus );
    void		display 	( int mode );
    void		show 		() { visible = true; }
    void		hide 		() { visible = false; }
    bool		isVisible	() const { return visible; }
};

#endif

