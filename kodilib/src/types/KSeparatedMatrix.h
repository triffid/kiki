/*
 *  KSeparatedMatrix.h
 *  kodisein
 */

#ifndef __KSeparatedMatrix
#define __KSeparatedMatrix

#include "KMatrix.h"

class KSeparatedMatrix : public KMatrix
{
    INTROSPECTION
    
    protected:
    
    GLfloat		scl[3];
    GLfloat		rot[3];

    public:
    
                        KSeparatedMatrix 	();
                        KSeparatedMatrix	( const KSeparatedMatrix & );
                                
    KSeparatedMatrix &	operator= ( const KSeparatedMatrix & );
    KSeparatedMatrix &	operator= ( const KMatrix & );
    
    void	reset	();
    
    void	scale	( GLfloat x, GLfloat y, GLfloat z);
    void	rotate	( const GLfloat x, const GLfloat y, const GLfloat z = 0.0 );
                                                          
    void	setSX	( GLfloat x );
    void	setSY	( GLfloat y );
    void	setSZ	( GLfloat z );
    void	setRX	( GLfloat x );
    void	setRY	( GLfloat y );
    void	setRZ	( GLfloat z );
    GLfloat	getSX	( ) const { return scl[X]; }
    GLfloat	getSY	( ) const { return scl[Y]; }
    GLfloat	getSZ	( ) const { return scl[Z]; }
    GLfloat	getRX	( ) const { return rot[X]; }
    GLfloat	getRY	( ) const { return rot[Y]; }
    GLfloat	getRZ	( ) const { return rot[Z]; }
};

#endif
