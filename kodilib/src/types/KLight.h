/*
 *  KLight.h
 *  kodisein
 */

#include "KColor.h"
#include "KVector.h"

#ifndef __KLight
#define __KLight

// --------------------------------------------------------------------------------------------------------
class KLight
{
    protected:
    
    GLenum		light_number;
    
    KVector		spot_position;
    KVector		spot_direction;
    
    float		spot_cutoff;
    
    float		constant_attenuation;
    float		linear_attenuation;
    float		quadratic_attenuation;
    
    KColor		ambient_color;
    KColor		diffuse_color;
    KColor		specular_color;
    
    public:
                        KLight 		( GLenum lightNumber = 0 );
    
    void		initialize	( GLenum lightNumber = 0 );
        
    void		setPosition	( const KVector & position );
    void		setDirection	( const KVector & direction );
    
    void		setAttenuation	( float constant, float linear = 0.0, float quadratic = 0.0 ); 
    void		setCutoff	( float cutoff );
    
    void		setAmbientColor	( const KColor & ambientColor );
    void		setDiffuseColor	( const KColor & diffuseColor );    
    void		setSpecularColor( const KColor & specularColor );
};

#endif
    

