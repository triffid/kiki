/*
 *  KikiTools.cpp
 *  kiki
 */

#include "KikiTools.h"

#include <KConsole.h>

// --------------------------------------------------------------------------------------------------------
KVector kRayPlaneIntersection ( const KVector & rayPos, const KVector & rayDirection, 
                                const KVector & planePos, const KVector & planeNormal )
{
    float x = ((planePos - rayPos) * planeNormal) / (rayDirection * planeNormal);
    return rayPos + x * rayDirection;
}

// --------------------------------------------------------------------------------------------------------
KVector kPointMappedToPlane   ( const KVector & point,  
                                const KVector & planePos, const KVector & planeNormal )
{
    return (point - planeNormal * ((point - planePos) * planeNormal));
}

// --------------------------------------------------------------------------------------------------------
float kRayPlaneIntersectionFactor ( const KVector & rayPos, const KVector & rayDirection, 
                                    const KVector & planePos, const KVector & planeNormal )
{
    return ((planePos - rayPos) * planeNormal) / (rayDirection * planeNormal);
}
