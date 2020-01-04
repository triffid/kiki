/*
 *  KikiPos.h
 *  kiki
 */
 
#ifndef __KikiPos
#define __KikiPos
 
#include <KVector.h>
#include <KStringTools.h>

// __________________________________________________________________________________________________
class KikiPos
{
    public: // ........................................................................ PUBLIC

    int x, y, z;

    KikiPos	() { x= y = z = 0; }
    KikiPos 	( const KVector & v ) { x = (int)rint(v[X]); y = (int)rint(v[Y]); z = (int)rint(v[Z]); }
    KikiPos 	( int _x, int _y, int _z = 0 ) { x = _x; y = _y; z = _z; }
    KikiPos 	( double _x, double _y, double _z = 0 ) { x = _x; y = _y; z = _z; }
    KikiPos 	( const KikiPos & p ) { x = p.x; y = p.y; z = p.z; }
    operator	KVector () const { return KVector(x, y, z); }
    KikiPos	operator-  ( const KikiPos & p ) const { return KikiPos(x-p.x,y-p.y,z-p.z); }
    KikiPos	operator+  ( const KikiPos & p ) const { return KikiPos(x+p.x,y+p.y,z+p.z); }
    bool	operator== ( const KikiPos & p ) const { return (x==p.x && y==p.y && z==p.z); }
    bool	operator!= ( const KikiPos & p ) const { return (x!=p.x || y!=p.y || z!=p.z); }
    KikiPos &	operator+= ( const KikiPos & p ) { x+=p.x; y+=p.y; z+=p.z; return (*this); }
    KikiPos &	operator-= ( const KikiPos & p ) { x-=p.x; y-=p.y; z-=p.z; return (*this); }
    std::string	getString  () const { return kStringPrintf("[%d %d %d]", x, y, z); }
    const char * getCString  () const { return kStringPrintf("[%d %d %d]", x, y, z).c_str(); }
};

// __________________________________________________________________________________________________
typedef KikiPos KikiSize; // :-)

#endif

