/*
 *  KikiBotStatus.h
 *  kiki
 */

#ifndef __KikiBotStatus
#define __KikiBotStatus

class KikiBot;

// __________________________________________________________________________________________________
class KikiBotStatus
{
    protected: // ..................................................................... PROTECTED
    
    int				moves;
    int				min_moves;
	int             par_moves;

    //float 			energy;
    float 			health;

    KikiBot *			bot;
    
    public: // ........................................................................ PUBLIC
    
                KikiBotStatus	( KikiBot * b ) { bot = b; moves = 0; min_moves = 100; /*energy =*/ health = 1.0; }
            
    int 	getMoves 	() const { return moves; }
    void	setMoves	( int m )   { moves  = m; }
    void	addMoves	( int m )   { moves += m; }
    
    int 	getMinMoves 	() const { return min_moves; }
    void	setMinMoves	( int m )   { min_moves  = m; }

	float   getHealth () const { return health; }
	void    addHealth (float h) { health = kMax(0.0, health + h); }

	//float   getEnergy () const { return energy; }
	//void    addEnergy (float e) { energy += e; }
};

#endif

