/*
 *  KikiSpikes.h
 *  kiki
 */

#ifndef __KikiSpikes
#define __KikiSpikes

#include "KikiObject.h"

class KikiBot;

// __________________________________________________________________________________________________

class KikiSpikes : public KikiObject
{
    public: // ........................................................................ PUBLIC
    
                        KikiSpikes 	 	( int face = KikiFace::PZ );
    
    void		performAction		( KikiAction * action );
    
    void		newCellMate		( KikiObject * object );
    void		cellMateLeft		( KikiObject * object );
    
    void		render			();
    
    protected: // ..................................................................... PROTECTED

    KIKI_OBJECT_HEADER

    friend class	KikiWorld;
    
    static unsigned int	spike_list;		// display list for spikes
    static void		initialize		();
    int 		face;
    
    float		spike;			// size of spikes    
    KikiBot *		spiked_bot;		// spiked bot (to release it again :-)
    
    void		spikeBot		( KikiBot * bot );
};

#endif

