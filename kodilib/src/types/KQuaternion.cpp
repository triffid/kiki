/*
 *  KQuaternion.cpp
 *  kodisein
 */

#include "KQuaternion.h"

// --------------------------------------------------------------------------------------------------------
KQuaternion KQuaternion::slerp ( const KQuaternion & quat, float t ) const
{
    float	to1[4];
    double	omega, cosom, sinom, scale0, scale1;

    // calc cosine
    cosom = x * quat.x + y * quat.y + z * quat.z + w * quat.w;

    // adjust signs (if necessary)
    if ( cosom < 0.0 )
    { 
        cosom = -cosom; 
        to1[0] = - quat.x;
        to1[1] = - quat.y;
        to1[2] = - quat.z;
        to1[3] = - quat.w;
    } 
    else  
    {
        to1[0] = quat.x;
        to1[1] = quat.y;
        to1[2] = quat.z;
        to1[3] = quat.w;
    }

    // calculate coefficients
    if ( (1.0 - cosom) > 0.001 ) // ???
    {
        // standard case (slerp)
        omega = acos(cosom);
        sinom = sin(omega);
        scale0 = sin((1.0 - t) * omega) / sinom;
        scale1 = sin(t * omega) / sinom;
    } 
    else // "from" and "to" quaternions are very close -> we can do a linear interpolation
    {        
        scale0 = 1.0 - t;
        scale1 = t;
    }
    
    // calculate final values
    return KQuaternion (scale0 * w + scale1 * to1[3],
                        scale0 * x + scale1 * to1[0], 
                        scale0 * y + scale1 * to1[1],
                        scale0 * z + scale1 * to1[2]);
}


