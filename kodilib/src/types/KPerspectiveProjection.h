/*
 *  KPerspectiveProjection.h
 *  kodisein
 */

#ifndef __KPerspectiveProjection
#define __KPerspectiveProjection

#include "KProjection.h"

// --------------------------------------------------------------------------------------------------------
class KPerspectiveProjection : public KProjection
{
    INTROSPECTION
    
    public:
                                KPerspectiveProjection 	( GLfloat = 60.0, GLfloat = 0.1, GLfloat = 300.0 );
                                KPerspectiveProjection  ( const KProjection & );
                        
    virtual KProjection *	copy			() const;
    virtual void 		apply			();

    virtual void		focusOn			( const KVector & );
    virtual void 		rotate			( const GLfloat, const GLfloat, const GLfloat );

    virtual void		reset			();
    
    virtual KVector 		getLookAtPosition	() const;
    virtual void		setLookAtPosition	( const KVector & lookAtPos );
    virtual void		setEyeDistance		( GLfloat );

    virtual std::string		getXML 			( int = 0 ) const;
    virtual void		setXML			( std::string & );
};

#endif


