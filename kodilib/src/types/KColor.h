/*
 *  KColor.h
 *  kodisein
 */

#ifndef __KColor
#define __KColor

#include "KIntrospection.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#ifdef _WIN32
#include <GL/glut.h>
#endif
#include <GL/gl.h>
#endif

enum { R, G, B, A };

class KColor
{
    protected:
    
    GLfloat		values[4];

    public:
    
                        KColor 		()
                                        {
                                            values[R] = 1.0;
                                            values[G] = 1.0;
                                            values[B] = 1.0;
                                            values[A] = 1.0;
                                        }
                                        
                        KColor 		( const KColor & c )
                                        {
                                            values[R] = c.values[R];
                                            values[G] = c.values[G];
                                            values[B] = c.values[B];
                                            values[A] = c.values[A];
                                        }
                                        
                        KColor 		( GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0 )
                                        {
                                            values[R] = r;
                                            values[G] = g;
                                            values[B] = b;
                                            values[A] = a;
                                        }
                                        
    void		setValues	( const GLfloat r, const GLfloat g, const GLfloat b,
                                            const GLfloat a = 1.0 )
                                        {
                                            values[R] = r; values[G] = g; values[B] = b; values[A] = a;
                                        }
                                        
    void		setValues4fv	( const GLfloat * v )
                                        {
                                            values[R] = v[R]; values[G] = v[G]; 
                                            values[B] = v[B]; values[A] = v[A];
                                        }
                                        
    const GLfloat *	getValues	() const 		{ return values; }
    void		setRed		( const GLfloat r )	{ values[R] = r; }
    void		setGreen	( const GLfloat g ) 	{ values[G] = g; }
    void		setBlue		( const GLfloat b )	{ values[B] = b; }
    void		setAlpha	( const GLfloat a )	{ values[A] = a; }
    GLfloat		getRed		( ) const 		{ return values[R]; }
    GLfloat		getGreen	( ) const		{ return values[G]; }
    GLfloat		getBlue		( ) const		{ return values[B]; }
    GLfloat		getAlpha	( ) const		{ return values[A]; }
    void		operator =	( const KColor & c )
                                        {
                                            values[R] = c.values[R]; values[G] = c.values[G];
                                            values[B] = c.values[B]; values[A] = c.values[A];
                                        }
    bool		operator ==	( const KColor & c ) const
                                        {
                                            return (values[R] == c.values[R] &&
                                                    values[G] == c.values[G] &&
                                                    values[B] == c.values[B] &&
                                                    values[A] == c.values[A]);
                                        }
    bool		operator !=	( const KColor & c ) const { return !((*this) == c); }
    GLfloat 		operator[]	(int i) const		{ return values[i]; }
    void		glColor		() const		{ glColor4fv(values); }
};

#endif

