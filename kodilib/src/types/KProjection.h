/*
 *  KProjection.h
 *  kodisein
 */

#ifndef __KProjection
#define __KProjection

#include "KMatrix.h"
#include <vector>

// --------------------------------------------------------------------------------------------------------
class KProjection : public KMatrix
{
    INTROSPECTION

    protected:

    float			fov;
    float			eye_distance;
    
    float			znear, zfar;
    float			aspect_ratio;
    float			viewport[4];
    unsigned int		border[4];
    int				vp[4];

    public:
    
                           	KProjection 			( float = 0.5, float = 200.0 );
                           	KProjection 			( const KProjection & );
    virtual			~KProjection			();
                            
    virtual void 		initProjection			();
    virtual void 		apply				() = 0;
    virtual KProjection *	copy				() const = 0;
    
    void			getSaveMatrices			( GLdouble *, GLdouble *, GLint * );

    bool			moveObjectRelativeToWindow 	( const KPosition &, KVector & );
    bool			getScreenCoordinates 		( const KVector &, double *, double *);
    
    float			getXValueForScreenDeltasAndMatrix (float, float, const KMatrix &);
    float			getYValueForScreenDeltasAndMatrix (float, float, const KMatrix &);
    float			getZValueForScreenDeltasAndMatrix (float, float, const KMatrix &);
    
    void	  		getXYValuesForScreenDeltasAndMatrix (float, float, 
                                                                const KMatrix &, float *, float *);
    void	  		getXZValuesForScreenDeltasAndMatrix (float, float, 
                                                                const KMatrix &, float *, float *);
    void	  		getYZValuesForScreenDeltasAndMatrix (float, float, 
                                                                const KMatrix &, float *, float *);
                                       
    virtual void		focusOn				( const KVector & ) {}

    float			getZFar				() const 	{ return zfar; }
    float			getZNear			() const 	{ return znear; }
    void			setZFar				( float z )     { zfar = z; }
    void			setZNear			( float z )     { znear = z; }
    virtual void		setViewportRelativePosX		( float x )	{ viewport[0] = x; }
    virtual void		setViewportRelativePosY		( float y )	{ viewport[1] = y; }
    virtual void		setViewportRelativeWidth	( float w )	{ viewport[2] = w; }
    virtual void		setViewportRelativeHeight	( float h )	{ viewport[3] = h; }

    virtual void		setAspectRatio			( float ar )	{ aspect_ratio = ar; }
    virtual void		setViewportBorder		( unsigned int l, unsigned int b, 
                                                                  unsigned int r, unsigned int t );
    virtual void		setViewport			( float l, float b, float w, float h );
    virtual void		setEyeDistance			( float );
    virtual void		setFov				( float );
    virtual void		updateViewport			();
    
    void			setEyeDist			( float f ) { eye_distance = f; }

    KSize			getViewportSize			() const { return KSize(vp[2], vp[3]); }
    KPosition			getViewportScreenPos 		() const { return KPosition(vp[0], vp[1]); }
    int				getViewportTopBorder		() const { return border[3]; }
    virtual KPosition		getLocatorViewportPos		() const;
    float			getViewportRelativePosX		() const { return viewport[0]; }
    float			getViewportRelativePosY		() const { return viewport[1]; }
    float			getViewportRelativeWidth	() const { return viewport[2]; }
    float			getViewportRelativeHeight	() const { return viewport[3]; }
    float			getCurrentAspectRatio		() const;
    float			getAspectRatio			() const { return aspect_ratio; }
    const int *			getViewport			() const { return vp; }
    const float *		getViewportRelative		() const { return viewport; }
    float			getEyeDistance			() const { return eye_distance; }
    float			getFov				() const { return fov; }

    virtual std::string		getXML 				( int = 0 ) const { return ""; }
    virtual void		setXML				( std::string & ) {}
};

#endif


