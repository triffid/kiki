/*
 *  KMatrix.h
 *  kodisein
 */

#ifndef __KMatrix
#define __KMatrix

#include "KVector.h"
#include "KNotificationObject.h"

class KQuaternion;

class KMatrix : public KObject
{
    INTROSPECTION
    
    protected:
    
    GLmat			matrix;

    public:
    
                                KMatrix		();
                                KMatrix		( const KMatrix & );
                                KMatrix		( const GLmat );
                                KMatrix		( const GLdouble * );
                                KMatrix		( const KVector &, const KVector &, const KVector & );
                                KMatrix		( const KQuaternion & );
    virtual		       ~KMatrix		() {}
                                    
    KQuaternion 		getQuaternion	() const;
    virtual void		transform	( const KMatrix & );
    virtual void		scale		( GLfloat, GLfloat, GLfloat = 1.0 );
    virtual void		rotate		( const GLfloat, const GLfloat, const GLfloat = 0.0 );
    virtual void		reset		();
    
    inline  void		translate	( GLfloat, GLfloat, GLfloat = 0.0 );
    inline  void		translate	( const KVector & );
    
            KMatrix &		invert		();
                                                          
            void		setTX		( GLfloat x ) { matrix[TX] = x; }
            void		setTY		( GLfloat y ) { matrix[TY] = y; }
            void		setTZ		( GLfloat z ) { matrix[TZ] = z; }
            GLfloat		getTX		() const { return matrix[TX]; }
            GLfloat		getTY		() const { return matrix[TY]; }
            GLfloat		getTZ		() const { return matrix[TZ]; }
            GLfloat		getDepthValue	() const;
            
    inline  virtual void	setPosition	( const KPosition & );
    inline  virtual void	setPosition	( GLfloat, GLfloat, GLfloat = 0.0 );
    inline  virtual void	setPosition	( const KVector & );
    inline  KVector		getPosition	() const;
    inline  KVector		getXVector	() const;
    inline  KVector		getYVector	() const;
    inline  KVector		getZVector	() const;
    inline  void		setXVector	( const KVector & );
    inline  void		setYVector	( const KVector & );
    inline  void		setZVector	( const KVector & );

            KMatrix &		operator =	( const KMatrix & );
            KMatrix &		operator *=	( const KMatrix & );
            KMatrix		operator *	( const KMatrix & ) const;
            KVector		operator *	( const KVector & ) const;
            GLfloat 		operator []	(int i) const { return matrix[i]; }
            
            void		glMultMatrix	() const { glMultMatrixf(matrix); }
            KMatrix		getInverse	() const { return KMatrix(*this).invert(); }
};

// --------------------------------------------------------------------------------------------------------
void KMatrix::translate ( const KVector & v ) 
{
    translate(v.values[X], v.values[Y], v.values[Z]);
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::translate ( GLfloat x, GLfloat y, GLfloat z )
{
    matrix[12] += matrix[0]*x+matrix[4]*y+matrix[8]*z;
    matrix[13] += matrix[1]*x+matrix[5]*y+matrix[9]*z;
    matrix[14] += matrix[2]*x+matrix[6]*y+matrix[10]*z;
    matrix[15] += matrix[3]*x+matrix[7]*y+matrix[11]*z;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setPosition ( const KPosition & pos  ) 
{
    matrix[TX] = pos.x; matrix[TY] = pos.y;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setPosition ( GLfloat x, GLfloat y, GLfloat z ) 
{
    matrix[TX] = x; matrix[TY] = y; matrix[TZ] = z;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setPosition ( const KVector & p ) 
{
    matrix[TX] = p.values[X]; matrix[TY] = p.values[Y]; matrix[TZ] = p.values[Z];
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getPosition () const
{
    return KVector(matrix[TX], matrix[TY], matrix[TZ]);
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setXVector ( const KVector & v )
{
    matrix[0] = v[0]; matrix[1] = v[1]; matrix[2] = v[2];
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getXVector () const
{
    return KVector(matrix[0], matrix[1], matrix[2]);
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setYVector ( const KVector & v )
{
    matrix[4] = v[0]; matrix[5] = v[1]; matrix[6] = v[2];
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getYVector () const
{
    return KVector(matrix[4], matrix[5], matrix[6]);
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::setZVector ( const KVector & v )
{
    matrix[8] = v[0]; matrix[9] = v[1]; matrix[10] = v[2];
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::getZVector () const
{
    return KVector(matrix[8], matrix[9], matrix[10]);
}

#endif
