/*
 *  KVector.h
 *  kodisein
 */

#ifndef __KVector
#define __KVector

#include <math.h>
#include <vector>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#define rint(x) (((x) < 0.0) ? (double)(int)((x) - 0.5) : (double)(int)((x) + 0.5))
#include <glut.h>
#endif
#include <GL/gl.h>
#endif

// --------------------------------------------------------------------------------------------------------
typedef GLfloat GLmat[16];
typedef GLfloat GLvec[4];

// --------------------------------------------------------------------------------------------------------
class KSize
{
    public:
    
    int w, h;
    
    KSize (int _w = 0, int _h = 0) { w=_w; h=_h; }
    KSize operator/ ( float d ) const { return KSize((int)(w/d), (int)(h/d)); }
    KSize operator* ( float d ) const { return KSize((int)(w*d), (int)(h*d)); }
    KSize operator- ( KSize s ) const { return KSize(w-s.w,h-s.h); }
    KSize operator+ ( KSize s ) const { return KSize(w+s.w,h+s.h); }
    bool  operator==( KSize s ) const { return (w==s.w && h==s.h); }
};

// --------------------------------------------------------------------------------------------------------

#define DEG2RAD(d)			(M_PI*(d)/180.0)
#define RAD2DEG(r)			((r)*180.0/M_PI)

#define kMin(a,b) 			(((a) <= (b)) ? (a) : (b))
#define kMax(a,b) 			(((a) >= (b)) ? (a) : (b))
#define kMinMax(a,b,c)			(kMax((a), kMin((b), (c))))
#define kAbs(d) 			(((d) >= 0) ? (d) : -(d))
#define kAbsMax(a,b)			((kAbs((a)) >= kAbs((b))) ? (a) : (b))
#define kAbsMin(a,b)			((kAbs((a)) < kAbs((b))) ? (a) : (b))

// --------------------------------------------------------------------------------------------------------
               
enum {	X = 0, SX = 0, Y, Z, W, SY = 5, SZ = 10, TX = 12, TY, TZ };

class KVector
{
    friend class KMatrix;
    friend KVector operator* (const GLfloat, const KVector &);
    friend KVector operator- (const KVector &);

    protected:
    
    GLvec			values;
    
    public:
    
                                KVector 		() { values[X]=values[Y]=values[Z]=values[W] = 0.0; }
                                KVector			( const GLfloat x, const GLfloat y, 
                                                          const GLfloat z = 0.0, const GLfloat w = 0.0 )
                                                        {
                                                        values[X]=x; values[Y]=y; values[Z]=z; values[W]=w;
                                                        }
                                KVector 		( const KVector & v )
                                                        {
                                                        values[X]=v.values[X]; values[Y]=v.values[Y]; 
                                                        values[Z]=v.values[Z]; values[W]=v.values[W];
                                                        }
                                
    inline KVector &		reset			();
    inline KVector &		normalize		();
    inline KVector &		operator=		( const KVector & );
    inline KVector &		operator+=		( const KVector & );
    inline KVector &		operator-=		( const KVector & );    
    inline KVector &		operator*=		( GLfloat );
    inline KVector &		operator/=		( GLfloat );
    inline KVector		cross			( const KVector & ) const;
    inline GLfloat		operator*		( const KVector & ) const;
    inline KVector		operator-		( const KVector & ) const;
    inline KVector		operator+		( const KVector & ) const;
    inline KVector		operator*		( GLfloat ) const;
    inline KVector		operator/		( GLfloat ) const;
    inline GLfloat		operator[] 		(int i) const { return values[i]; }
    inline GLfloat &		operator[] 		(int i) { return values[i]; }
    inline KVector		perpendicular		( const KVector & ) const;
    inline KVector		parallel		( const KVector & ) const;
    inline KVector		reflect			( const KVector & ) const;
    inline KVector		normal			() const { return KVector(*this).normalize(); }
    inline GLfloat		length			() const;
    inline GLfloat		angle			( const KVector & ) const;
    inline GLfloat		xyangle			( const KVector & ) const;
    inline KVector		xyperp			() const;
    inline KVector		round			() const;
    inline const GLfloat *	getValues		() const { return values; }
    inline void			glVertex		() const { glVertex3fv(values); }
    inline void			glTranslate		() const 
                                                        { 
                                                            glTranslatef(values[X],values[Y],values[Z]); 
                                                        }
};

// --------------------------------------------------------------------------------------------------------
inline KVector & KVector::operator= ( const KVector & v )
{
    values[X] = v.values[X]; values[Y] = v.values[Y]; values[Z] = v.values[Z]; values[W] = v.values[W];
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
// returns the projection of this vector on ray with normized normalized vector n to this vector.  
inline KVector KVector::parallel ( const KVector & n ) const
{
    float dot = values[X]*n.values[X] + values[Y]*n.values[Y] + values[Z]*n.values[Z];
    return KVector(dot*n.values[X], dot*n.values[Y], dot*n.values[Z]);
}

// --------------------------------------------------------------------------------------------------------
// returns the projection of normalized vector n to vector that is perpendicular to this
inline KVector KVector::perpendicular ( const KVector & n ) const
{
    float dot = values[X]*n.values[X] + values[Y]*n.values[Y] + values[Z]*n.values[Z];
    return KVector(values[X]-dot*n.values[X], values[Y]-dot*n.values[Y], values[Z]-dot*n.values[Z]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::reflect ( const KVector & n ) const
{
    float dot = 2.0*(values[X]*n.values[X] + values[Y]*n.values[Y] + values[Z]*n.values[Z]);
    return KVector(values[X]-dot*n.values[X], values[Y]-dot*n.values[Y], values[Z]-dot*n.values[Z]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::cross ( const KVector & v ) const
{
    return KVector( values[Y]*v.values[Z]-values[Z]*v.values[Y],
                    values[Z]*v.values[X]-values[X]*v.values[Z],
                    values[X]*v.values[Y]-values[Y]*v.values[X]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector & KVector::normalize ()
{
    float l = length();
    if (l != 0.0) 
    {
        l = 1.0/l; 
        values[X] *= l; values[Y] *= l; values[Z] *= l; values[W] *= l;
    }
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::xyperp () const
{
    return KVector(-values[Y], values[X]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::round () const
{
    return KVector(rint(values[X]), rint(values[Y]), rint(values[Z]), values[W]);
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::xyangle ( const KVector & v ) const
{
    KVector thisXY  = KVector(values[X], values[Y]).normal();
    KVector otherXY = KVector(v[X], v[Y]).normal();
    if (thisXY.xyperp() * otherXY >= 0) return RAD2DEG(acos(thisXY * otherXY));
    return -RAD2DEG(acos(thisXY * otherXY));
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::angle ( const KVector & v ) const
{
    return RAD2DEG(acos(this->normal()*v.normal()));
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::length () const
{
    return sqrt(values[X]*values[X]+values[Y]*values[Y]+values[Z]*values[Z]+values[W]*values[W]);
}

// -------------------------------------------------------------------------------------------------------- 
inline KVector & KVector::operator+= ( const KVector & v )
{
    values[X]+=v.values[X]; values[Y]+=v.values[Y]; values[Z]+=v.values[Z]; values[W]+=v.values[W];
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
inline KVector & KVector::operator-= ( const KVector & v )
{
    values[X]-=v.values[X]; values[Y]-=v.values[Y]; values[Z]-=v.values[Z]; values[W]-=v.values[W];
    return (*this);
} 

// --------------------------------------------------------------------------------------------------------
inline KVector & KVector::operator*= ( const GLfloat f )
{
    values[X] *= f; values[Y] *= f; values[Z] *= f; values[W] *= f;
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
inline KVector & KVector::operator/= ( const GLfloat f )
{
    values[X] /= f; values[Y] /= f; values[Z] /= f; values[W] /= f;
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
inline GLfloat KVector::operator* ( const KVector & v ) const
{
    return values[X]*v.values[X] + values[Y]*v.values[Y] + values[Z]*v.values[Z] + values[W]*v.values[W];
}

// --------------------------------------------------------------------------------------------------------
inline KVector operator* ( const GLfloat f, const KVector & v )
{
    return KVector (f*v.values[X], f*v.values[Y], f*v.values[Z], f*v.values[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector operator- ( const KVector & v )
{
    return KVector (-v.values[X], -v.values[Y], -v.values[Z], -v.values[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator* ( const GLfloat f ) const
{
    return KVector(values[X]*f, values[Y]*f, values[Z]*f, values[W]*f);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator/ ( const GLfloat f ) const
{
    return KVector(values[X]/f, values[Y]/f, values[Z]/f, values[W]/f);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator- ( const KVector & v ) const
{
    return KVector(values[X]-v.values[X],values[Y]-v.values[Y],values[Z]-v.values[Z],values[W]-v.values[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector KVector::operator+ ( const KVector & v ) const
{
    return KVector(values[X]+v.values[X],values[Y]+v.values[Y],values[Z]+v.values[Z],values[W]+v.values[W]);
}

// --------------------------------------------------------------------------------------------------------
inline KVector & KVector::reset ()
{
    values[X] = 0.0; values[Y] = 0.0; values[Z] = 0.0; values[W] = 0.0;
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
class KPosition
{
    public:
    
    int x, y;
    
    KPosition (int _x = 0, int _y = 0) { x=_x; y=_y; }
    KPosition operator+ ( KPosition p ) const { return KPosition(x+p.x,y+p.y); }
    KPosition operator- ( KPosition p ) const { return KPosition(x-p.x,y-p.y); }
    KPosition operator+ ( KSize p ) const { return KPosition(x+p.w,y+p.h); }
    KPosition operator- ( KSize p ) const { return KPosition(x-p.w,y-p.h); }
    operator KVector () const { return KVector(x,y); }
    bool  operator==( KPosition p ) const { return (x==p.x && y==p.y); }
};

#endif
