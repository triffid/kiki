/*
 *  KikiNeutron.h
 *  kiki
 */

#ifndef __KikiNeutron
#define __KikiNeutron

#include <KQuaternion.h>

// __________________________________________________________________________________________________
class KikiNeutron
{
    protected: // ..................................................................... PROTECTED
    
    float	start_angle;
    float	angle;
    KQuaternion orientation;
    
    public: // ........................................................................ PUBLIC
    
                KikiNeutron 	( const KVector & orbitNormal, float startAngle );
            
    void	display		();
};

#endif

