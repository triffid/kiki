/*
 *  KMatrix.cpp
 *  kodisein
 */

#include "KMatrix.h"
#include "KQuaternion.h"
#include "KConsole.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION_1 (KMatrix, KObject)

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix () : KObject ()
{
    reset();
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const KMatrix & m ) : KObject ()
{
    matrix[0]=m.matrix[0];matrix[1]=m.matrix[1];matrix[2]=m.matrix[2];matrix[3]=m.matrix[3];
    matrix[4]=m.matrix[4];matrix[5]=m.matrix[5];matrix[6]=m.matrix[6];matrix[7]=m.matrix[7];
    matrix[8]=m.matrix[8];matrix[9]=m.matrix[9];matrix[10]=m.matrix[10];matrix[11]=m.matrix[11];
    matrix[12]=m.matrix[12];matrix[13]=m.matrix[13];matrix[14]=m.matrix[14];matrix[15]=m.matrix[15];
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const GLdouble * m ) : KObject ()
{
    matrix[0]=m[0];matrix[1]=m[1];matrix[2]=m[2];matrix[3]=m[3];
    matrix[4]=m[4];matrix[5]=m[5];matrix[6]=m[6];matrix[7]=m[7];
    matrix[8]=m[8];matrix[9]=m[9];matrix[10]=m[10];matrix[11]=m[11];
    matrix[12]=m[12];matrix[13]=m[13];matrix[14]=m[14];matrix[15]=m[15];
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const GLmat m ) : KObject ()
{
    matrix[0]=m[0];matrix[1]=m[1];matrix[2]=m[2];matrix[3]=m[3];
    matrix[4]=m[4];matrix[5]=m[5];matrix[6]=m[6];matrix[7]=m[7];
    matrix[8]=m[8];matrix[9]=m[9];matrix[10]=m[10];matrix[11]=m[11];
    matrix[12]=m[12];matrix[13]=m[13];matrix[14]=m[14];matrix[15]=m[15];
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const KVector & x, const KVector & y, const KVector & z ) : KObject ()
{
    matrix[0] = x.values[X]; matrix[4] = y.values[X]; matrix[8]  = z.values[X]; matrix[12] = 0.0;
    matrix[1] = x.values[Y]; matrix[5] = y.values[Y]; matrix[9]  = z.values[Y]; matrix[13] = 0.0; 
    matrix[2] = x.values[Z]; matrix[6] = y.values[Z]; matrix[10] = z.values[Z]; matrix[14] = 0.0;
    matrix[3] = x.values[W]; matrix[7] = y.values[W]; matrix[11] = z.values[W]; matrix[15] = 1.0;
}

// --------------------------------------------------------------------------------------------------------
KMatrix::KMatrix ( const KQuaternion & quat ) : KObject ()
{
    float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

    // calculate coefficients
    x2 = quat.x + quat.x; y2 = quat.y + quat.y;
    z2 = quat.z + quat.z;
    xx = quat.x * x2; xy = quat.x * y2; xz = quat.x * z2;
    yy = quat.y * y2; yz = quat.y * z2; zz = quat.z * z2;
    wx = quat.w * x2; wy = quat.w * y2; wz = quat.w * z2;
    
    matrix[0] = 1.0 - (yy + zz); 
    matrix[1] = xy + wz;
    matrix[2] = xz - wy; 
    matrix[3] = 0.0;
    matrix[4] = xy - wz;    
    matrix[5] = 1.0 - (xx + zz);
    matrix[6] = yz + wx;
    matrix[7] = 0.0;
    matrix[8] = xz + wy; 
    matrix[9] = yz - wx; 
    matrix[10] = 1.0 - (xx + yy); 
    matrix[11] = 0.0; 
    matrix[12] = 0.0;    
    matrix[13] = 0.0;
    matrix[14] = 0.0;
    matrix[15] = 1.0;
}

// --------------------------------------------------------------------------------------------------------
KMatrix &  KMatrix::operator= ( const KMatrix & m )
{
    matrix[0]=m.matrix[0];matrix[1]=m.matrix[1];matrix[2]=m.matrix[2];matrix[3]=m.matrix[3];
    matrix[4]=m.matrix[4];matrix[5]=m.matrix[5];matrix[6]=m.matrix[6];matrix[7]=m.matrix[7];
    matrix[8]=m.matrix[8];matrix[9]=m.matrix[9];matrix[10]=m.matrix[10];matrix[11]=m.matrix[11];
    matrix[12]=m.matrix[12];matrix[13]=m.matrix[13];matrix[14]=m.matrix[14];matrix[15]=m.matrix[15];
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
KMatrix & KMatrix::operator*= ( const KMatrix & m )
{
    *this = (*this * m);
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
KMatrix KMatrix::operator* ( const KMatrix & m ) const
{
    KMatrix mm;
    mm.matrix[0]=matrix[0]*m.matrix[0]+matrix[4]*m.matrix[1]+matrix[8]*m.matrix[2]+matrix[12]*m.matrix[3];
    mm.matrix[1]=matrix[1]*m.matrix[0]+matrix[5]*m.matrix[1]+matrix[9]*m.matrix[2]+matrix[13]*m.matrix[3];
    mm.matrix[2]=matrix[2]*m.matrix[0]+matrix[6]*m.matrix[1]+matrix[10]*m.matrix[2]+matrix[14]*m.matrix[3];
    mm.matrix[3]=matrix[3]*m.matrix[0]+matrix[7]*m.matrix[1]+matrix[11]*m.matrix[2]+matrix[15]*m.matrix[3];
    mm.matrix[4]=matrix[0]*m.matrix[4]+matrix[4]*m.matrix[5]+matrix[8]*m.matrix[6]+matrix[12]*m.matrix[7];
    mm.matrix[5]=matrix[1]*m.matrix[4]+matrix[5]*m.matrix[5]+matrix[9]*m.matrix[6]+matrix[13]*m.matrix[7];
    mm.matrix[6]=matrix[2]*m.matrix[4]+matrix[6]*m.matrix[5]+matrix[10]*m.matrix[6]+matrix[14]*m.matrix[7];
    mm.matrix[7]=matrix[3]*m.matrix[4]+matrix[7]*m.matrix[5]+matrix[11]*m.matrix[6]+matrix[15]*m.matrix[7];
    mm.matrix[8]=matrix[0]*m.matrix[8]+matrix[4]*m.matrix[9]+matrix[8]*m.matrix[10]+matrix[12]*m.matrix[11];
    mm.matrix[9]=matrix[1]*m.matrix[8]+matrix[5]*m.matrix[9]+matrix[9]*m.matrix[10]+matrix[13]*m.matrix[11];
    mm.matrix[10]=matrix[2]*m.matrix[8]+matrix[6]*m.matrix[9]+matrix[10]*m.matrix[10]+matrix[14]*m.matrix[11]; 
    mm.matrix[11]=matrix[3]*m.matrix[8]+matrix[7]*m.matrix[9]+matrix[11]*m.matrix[10]+matrix[15]*m.matrix[11]; 
    mm.matrix[12]=matrix[0]*m.matrix[12]+matrix[4]*m.matrix[13]+matrix[8]*m.matrix[14]+matrix[12]*m.matrix[15]; 
    mm.matrix[13]=matrix[1]*m.matrix[12]+matrix[5]*m.matrix[13]+matrix[9]*m.matrix[14]+matrix[13]*m.matrix[15]; 
    mm.matrix[14]=matrix[2]*m.matrix[12]+matrix[6]*m.matrix[13]+matrix[10]*m.matrix[14]+matrix[14]*m.matrix[15]; 
    mm.matrix[15]=matrix[3]*m.matrix[12]+matrix[7]*m.matrix[13]+matrix[11]*m.matrix[14]+matrix[15]*m.matrix[15]; 
    return mm;
}

// --------------------------------------------------------------------------------------------------------
KVector KMatrix::operator* ( const KVector & v ) const
{
    return KVector( 
        matrix[0]*v.values[0] + matrix[4]*v.values[1] + matrix[8] *v.values[2] + matrix[12]*v.values[3],
        matrix[1]*v.values[0] + matrix[5]*v.values[1] + matrix[9] *v.values[2] + matrix[13]*v.values[3],
	matrix[2]*v.values[0] + matrix[6]*v.values[1] + matrix[10]*v.values[2] + matrix[14]*v.values[3],
	matrix[3]*v.values[0] + matrix[7]*v.values[1] + matrix[11]*v.values[2] + matrix[15]*v.values[3] );
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::reset()
{
    matrix[0]=matrix[5]=matrix[10]=matrix[15]=1.0; 
    matrix[1]=matrix[4]=matrix[8] =matrix[12]=0.0;
    matrix[2]=matrix[6]=matrix[9] =matrix[13]=0.0; 
    matrix[3]=matrix[7]=matrix[11]=matrix[14]=0.0;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::transform ( const KMatrix & m ) 
{
    *this *= m;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::rotate ( GLfloat x, GLfloat y, GLfloat z )		
{
    GLfloat rx = DEG2RAD(x), ry = DEG2RAD(y), rz = DEG2RAD(z);
    GLfloat cx=cos(rx), sx=sin(rx), cy=cos(ry), sy=sin(ry), cz = cos(rz), sz = sin(rz);

    GLfloat b0 = cy*cz, b1 = sx*sy*cz+cx*sz, b2 = -cx*sy*cz+sx*sz, b4 = -cy*sz; 
    GLfloat b5 = -sx*sy*sz+cx*cz, b6 = cx*sy*sz+sx*cz, b8 = sy, b9 = -sx*cy, b10 = cx*cy; 
    GLfloat a0 = matrix[0], a1 = matrix[1], a2  = matrix[2],   a3 = matrix[3]; 
    GLfloat a4 = matrix[4], a5 = matrix[5], a6  = matrix[6],   a7 = matrix[7];
    GLfloat a8 = matrix[8], a9 = matrix[9], a10 = matrix[10], a11 = matrix[11];
    
    matrix[0]=a0*b0+a4*b1+a8*b2;
    matrix[1]=a1*b0+a5*b1+a9*b2;
    matrix[2]=a2*b0+a6*b1+a10*b2;
    matrix[3]=a3*b0+a7*b1+a11*b2;
    matrix[4]=a0*b4+a4*b5+a8*b6;
    matrix[5]=a1*b4+a5*b5+a9*b6;
    matrix[6]=a2*b4+a6*b5+a10*b6;
    matrix[7]=a3*b4+a7*b5+a11*b6;
    matrix[8]=a0*b8+a4*b9+a8*b10;
    matrix[9]=a1*b8+a5*b9+a9*b10;
    matrix[10]=a2*b8+a6*b9+a10*b10;
    matrix[11]=a3*b8+a7*b9+a11*b10;
}

// --------------------------------------------------------------------------------------------------------
void KMatrix::scale ( GLfloat x, GLfloat y, GLfloat z )		
{
    matrix[0] *= x; matrix[1] *= x; matrix[2]  *= x; matrix[3]  *= x;
    matrix[4] *= y; matrix[5] *= y; matrix[6]  *= y; matrix[7]  *= y;
    matrix[8] *= z; matrix[9] *= z; matrix[10] *= z; matrix[11] *= z;
}

#define COFACTOR_4X4_IJ(fac,m,i,j) 				\
{								\
   int ii[4], jj[4], k;						\
								\
   /* compute which row, columnt to skip */			\
   for (k=0; k<i; k++) ii[k] = k;				\
   for (k=i; k<3; k++) ii[k] = k+1;				\
   for (k=0; k<j; k++) jj[k] = k;				\
   for (k=j; k<3; k++) jj[k] = k+1;				\
								\
   (fac) = m[ii[0]][jj[0]] * (m[ii[1]][jj[1]]*m[ii[2]][jj[2]] 	\
                            - m[ii[1]][jj[2]]*m[ii[2]][jj[1]]); \
   (fac) -= m[ii[0]][jj[1]] * (m[ii[1]][jj[0]]*m[ii[2]][jj[2]]	\
                             - m[ii[1]][jj[2]]*m[ii[2]][jj[0]]);\
   (fac) += m[ii[0]][jj[2]] * (m[ii[1]][jj[0]]*m[ii[2]][jj[1]]	\
                             - m[ii[1]][jj[1]]*m[ii[2]][jj[0]]);\
								\
   /* compute sign */						\
   k = i+j;							\
   if ( k != (k/2)*2) {						\
      (fac) = -(fac);						\
   }								\
}

#define DETERMINANT_4X4(d,m)					\
{								\
   double cofac;						\
   COFACTOR_4X4_IJ (cofac, m, 0, 0);				\
   d = m[0][0] * cofac;						\
   COFACTOR_4X4_IJ (cofac, m, 0, 1);				\
   d += m[0][1] * cofac;					\
   COFACTOR_4X4_IJ (cofac, m, 0, 2);				\
   d += m[0][2] * cofac;					\
   COFACTOR_4X4_IJ (cofac, m, 0, 3);				\
   d += m[0][3] * cofac;					\
}

#define SCALE_ADJOINT_4X4(a,s,m)				\
{								\
   int i,j;							\
								\
   for (i=0; i<4; i++) {					\
      for (j=0; j<4; j++) {					\
         COFACTOR_4X4_IJ (a[j][i], m, i, j);			\
         a[j][i] *= s;						\
      }								\
   }								\
}

#define INVERT_4X4(b,det,a)			\
{						\
   double tmp;					\
   DETERMINANT_4X4 (det, a);			\
   tmp = 1.0 / (det);				\
   SCALE_ADJOINT_4X4 (b, tmp, a);		\
}

// --------------------------------------------------------------------------------------------------------
KMatrix & KMatrix::invert ()
{
    GLfloat t[4][4], inv[4][4], det;
    t[0][0] = matrix[0];  t[0][1] = matrix[1];  t[0][2] = matrix[2];  t[0][3] = matrix[3];
    t[1][0] = matrix[4];  t[1][1] = matrix[5];  t[1][2] = matrix[6];  t[1][3] = matrix[7]; 
    t[2][0] = matrix[8];  t[2][1] = matrix[9];  t[2][2] = matrix[10]; t[2][3] = matrix[11]; 
    t[3][0] = matrix[12]; t[3][1] = matrix[13]; t[3][2] = matrix[14]; t[3][3] = matrix[15]; 
    INVERT_4X4(inv,det,t);
    matrix[0]  = inv[0][0]; matrix[1]  = inv[0][1]; matrix[2]  = inv[0][2]; matrix[3]  = inv[0][3];
    matrix[4]  = inv[1][0]; matrix[5]  = inv[1][1]; matrix[6]  = inv[1][2]; matrix[7]  = inv[1][3];
    matrix[8]  = inv[2][0]; matrix[9]  = inv[2][1]; matrix[10] = inv[2][2]; matrix[11] = inv[2][3];
    matrix[12] = inv[3][0]; matrix[13] = inv[3][1]; matrix[14] = inv[3][2]; matrix[15] = inv[3][3];
    return (*this);
}

// --------------------------------------------------------------------------------------------------------
KQuaternion KMatrix::getQuaternion () const
{
    float  tr, s, ss;
        
    tr = matrix[0] + matrix[5] + matrix[10];
    
    // check the diagonal
    if (tr > 0.0) 
    {
        s = sqrt (tr + 1.0);
        ss = 0.5 / s;
        return KQuaternion(s/2.0,   (matrix[6]-matrix[9])*ss, 
                                    (matrix[8]-matrix[2])*ss, 
                                    (matrix[1]-matrix[4])*ss);
    } 
    else // diagonal is negative
    {
        int   i = 0, j, k, nxt[3] = {1, 2, 0};
        float q[4];

        if (matrix[5] > matrix[0]) i = 1;
        if (matrix[10] > matrix[i*4+i]) i = 2;
        j = nxt[i];
        k = nxt[j];

        s = sqrt ((matrix[i*4+i] - (matrix[j*4+j] + matrix[k*4+k])) + 1.0);
    
            q[i] = s * 0.5;
        
        if (s != 0.0) s = 0.5 / s;


        q[3] = (matrix[j*4+k] - matrix[k*4+j]) * s;
        q[j] = (matrix[i*4+j] + matrix[j*4+i]) * s;
        q[k] = (matrix[i*4+k] + matrix[k*4+i]) * s;

        return KQuaternion(q[3], q[0], q[1], q[2]);
    }
}

// --------------------------------------------------------------------------------------------------------
GLfloat KMatrix::getDepthValue () const
{
    GLdouble	model[16], proj[16], wx, wy, wz;
    GLint	view[4];
    
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);
    
    if (gluProject(matrix[TX], matrix[TY], matrix[TZ], model, proj, view, &wx, &wy, &wz) == false)
    {
        KConsole::printError("unable to calculate depth value"); return 0.0;
    }
    
    return wz;
}


