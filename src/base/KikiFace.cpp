/*
 *  KikiFace.cpp
 *  kiki
 */

#include "KikiFace.h"

// __________________________________________________________________________________________________
KQuaternion KikiFace::orientationForFace ( int face )
{
    switch (face % 6)
    {
        case PZ: return KQuaternion();
        case NZ: return KQuaternion::rotationAroundVector(180, KVector(1,0,0));       
        case PX: return KQuaternion::rotationAroundVector( 90, KVector(0,1,0));
        case NX: return KQuaternion::rotationAroundVector(-90, KVector(0,1,0));
        case PY: return KQuaternion::rotationAroundVector(-90, KVector(1,0,0));
        case NY: return KQuaternion::rotationAroundVector( 90, KVector(1,0,0));        
    };
    
    return KQuaternion();
}

// __________________________________________________________________________________________________
KVector KikiFace::normalVectorForFace ( int face )
{
    float o = (face < 3) ? -1 : 1;
    switch (face % 3) 
    {
        case X:	return KVector (o, 0, 0);
        case Y:	return KVector (0, o, 0);
        case Z:	return KVector (0, 0, o);
    }
    return KVector();
}

// __________________________________________________________________________________________________
void KikiFace::transformationForFace ( int face, float offset )
{
    (offset * normalVectorForFace (face)).glTranslate();
    
    switch (face)
    {
        case PZ: break;
        case NZ: glRotatef (180, 0, 1, 0); break;       
        case PX: glRotatef ( 90, 0, 1, 0); break;
        case NX: glRotatef (-90, 0, 1, 0); break;
        case PY: glRotatef (-90, 1, 0, 0); break;
        case NY: glRotatef ( 90, 1, 0, 0); break;        
    }
}

