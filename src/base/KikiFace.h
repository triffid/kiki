/*
 *  KikiFace.h
 *  kiki
 */

#ifndef __KikiFace
#define __KikiFace

#include <KVector.h>
#include <KQuaternion.h>

// __________________________________________________________________________________________________

class KikiFace
{
    public: // ........................................................................ PUBLIC
    
    enum {		PX=0, X=0, PY, Y=1, PZ, Z=2, NX, NY, NZ };
    
    static void		transformationForFace 	( int face, float offset = 0.5 );
    static KQuaternion	orientationForFace  	( int face );
    static KVector	normalVectorForFace 	( int face );    
};

#endif

