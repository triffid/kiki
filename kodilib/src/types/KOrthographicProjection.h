/*
 *  KOrthographicProjection.h
 *  kodisein
 */

#ifndef __KOrthographicProjection
#define __KOrthographicProjection

#include "KProjection.h"

// --------------------------------------------------------------------------------------------------------
class KOrthographicProjection : public KProjection
{
    INTROSPECTION
    
    public:
                        KOrthographicProjection ( GLfloat = -1.0, GLfloat = 1.0 );
                        KOrthographicProjection ( const KProjection & );
                        
    KProjection *	copy			() const;
    void		apply			();
};

#endif

