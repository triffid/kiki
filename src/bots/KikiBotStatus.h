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

    float 			energy;
    float 			health;

    KikiBot *			bot;
    
    public: // ........................................................................ PUBLIC
    
                KikiBotStatus	( KikiBot * b ) { bot = b; moves = 0; min_moves = 100; energy = health = 1.0; }
            
    int 	getMoves 	() const { return moves; }
    void	setMoves	( int m )   { moves  = m; }
    void	addMoves	( int m )   { moves += m; }
    
    int 	getMinMoves 	() const { return min_moves; }
    void	setMinMoves	( int m )   { min_moves  = m; }
    
    float 	getEnergy 	() const { return energy; }
    float	getHealth	() const { return health; }

    void	setHealth	( float h ) { health = kMinMax (0.0, 1.0, h); }
    void	setEnergy	( float e ) { energy = kMax (e, 0.0); }
    
    void	addHealth	( float h ) { health = kMinMax (0.0, 1.0, health+h); }
    void	addEnergy	( float e ) { energy = kMax (energy+e, 0.0); }
};

#endif

