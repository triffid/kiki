/*
 *  KikiTools.h
 *  kiki
 */

#ifndef __KikiTools
#define __KikiTools

#include <KVector.h>

// --------------------------------------------------------------------------------------------------------

KVector kRayPlaneIntersection ( const KVector & rayPos, const KVector & rayDirection, 
                                const KVector & planePos, const KVector & planeNormal );

KVector kPointMappedToPlane   ( const KVector & point,  
                                const KVector & planePos, const KVector & planeNormal );

float   kRayPlaneIntersectionFactor ( const KVector & rayPos, const KVector & rayDirection, 
                                      const KVector & planePos, const KVector & planeNormal );

// --------------------------------------------------------------------------------------------------------
#endif


