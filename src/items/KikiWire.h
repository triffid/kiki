/*
 *  KikiWire.h
 *  kiki
 */

#ifndef __KikiWire
#define __KikiWire

#include "KikiObject.h"

// __________________________________________________________________________________________________

class KikiWire : public KikiObject
{
    public: // ........................................................................ PUBLIC
    
    enum {	UP=1, RIGHT, DOWN=4, VERTICAL, LEFT=8, HORIZONTAL=10, ALL=15 };
    
                        KikiWire	( int face = KikiFace::PZ, int connections = ALL );
    
            void	display		();

    virtual void	setActive	( bool active = true );
    virtual void	updateActive	();
    
    protected: // ..................................................................... PROTECTED
    
    KIKI_OBJECT_HEADER

    bool	active;
    int		connections;
    int		face;
    float	value;

    std::vector<KikiWire*>	getNeighborWires ();
    std::vector<KVector>	getConnectionPoints ();
};

#endif

