/*
 *  KLightingProjection.h
 *  kodisein
 */

#ifndef __KLightingProjection
#define __KLightingProjection

#include "KPerspectiveProjection.h"
#include "KLight.h"

// --------------------------------------------------------------------------------------------------------
class KLightingProjection : public KPerspectiveProjection
{
    INTROSPECTION

    KVector		light_offset;
    KLight		light;

    public:
                        KLightingProjection 	( GLfloat = 60.0, GLfloat = 0.1, GLfloat = 300.0 );
                        KLightingProjection 	( const KProjection & );
                        KLightingProjection 	( const KLightingProjection & );
    
    KLight &		getLight		() { return light; }
    void		setLightOffset		( const KVector & offset ) { light_offset = offset; }
    
    KProjection *	copy			() const;
    void 		apply			();
};

#endif


