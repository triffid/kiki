/*
 *  KLight.cpp
 *  kodisein
 */

#include "KLight.h"
#include "KConsole.h"

// --------------------------------------------------------------------------------------------------------
KLight::KLight ( GLenum lightNumber )
{
    light_number   	  = lightNumber;
    
    ambient_color  	  = KColor (0, 0, 0, 1); 
    diffuse_color  	  = KColor (1, 1, 1, 1); 
    specular_color 	  = KColor (1, 1, 1, 1);
    
    spot_direction   	  = KVector (0, -1, 0);
    spot_cutoff		  = 180.0;
    
    constant_attenuation  = 1.0;
    linear_attenuation	  = 0.0;
    quadratic_attenuation = 0.0;

    if (light_number)
    {
        initialize (light_number);
    }
}

// --------------------------------------------------------------------------------------------------------
void KLight::initialize ( GLenum lightNumber )
{
    if (lightNumber == 0 && light_number == 0)
    {
        GLint maxLights; 
        glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
            
        for (light_number = GL_LIGHT1; light_number < (GL_LIGHT0+(GLuint)maxLights); light_number++)
        {
            if (glIsEnabled (light_number) == false)
            {
                break;
            }
        }
        if (light_number == GL_LIGHT0+(GLuint)maxLights)
        {
            KConsole::printError("KLight::initialize unable to enable light ;-)");
            light_number = 0;
            return;
        }
    }
    else if (lightNumber)
    {
        light_number = lightNumber;
    }
    
    glLightfv (light_number, GL_AMBIENT,  ambient_color.getValues());
    glLightfv (light_number, GL_DIFFUSE,  diffuse_color.getValues());
    glLightfv (light_number, GL_SPECULAR, specular_color.getValues());
    
    glLightf  (light_number, GL_CONSTANT_ATTENUATION,  constant_attenuation);
    glLightf  (light_number, GL_LINEAR_ATTENUATION,    linear_attenuation);
    glLightf  (light_number, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);

    glLightfv (light_number, GL_POSITION,    spot_position.getValues());
    glLightf  (light_number, GL_SPOT_CUTOFF, spot_cutoff);

    if (spot_cutoff <= 90.0)
    {
        glLightfv (light_number, GL_SPOT_DIRECTION, spot_direction.getValues());
    }
    
    GLboolean enabled;
    glGetBooleanv (light_number, &enabled);
    if (enabled == GL_FALSE)
    {
        glEnable (light_number);
    }
}

// --------------------------------------------------------------------------------------------------------
void KLight::setPosition ( const KVector & position )
{
    spot_position = position;
    
    if (light_number)
    {
        glLightfv (light_number, GL_POSITION, spot_position.getValues());
    }
}
    
// --------------------------------------------------------------------------------------------------------
void KLight::setDirection ( const KVector & direction )
{
    spot_direction = direction;
    
    if (spot_cutoff <= 90.0 && light_number)
    {
        glLightfv(light_number, GL_SPOT_DIRECTION, spot_direction.getValues());
    }
}
    
// --------------------------------------------------------------------------------------------------------
void KLight::setAttenuation ( float constant, float linear, float quadratic )
{
    constant_attenuation  = constant;
    linear_attenuation	  = linear;
    quadratic_attenuation = quadratic;

    if (light_number)
    {
        glLightf  (light_number, GL_CONSTANT_ATTENUATION,  constant_attenuation);
        glLightf  (light_number, GL_LINEAR_ATTENUATION,    linear_attenuation);
        glLightf  (light_number, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
    }
}
    
// --------------------------------------------------------------------------------------------------------
void KLight::setCutoff ( float cutoff )
{
    spot_cutoff = cutoff;
    
    if (light_number)
    {
        glLightf (light_number, GL_SPOT_CUTOFF, spot_cutoff);
        if (spot_cutoff <= 90.0)
        {
            glLightfv(light_number, GL_SPOT_DIRECTION, spot_direction.getValues());
        }
    }
}
    
// --------------------------------------------------------------------------------------------------------
void KLight::setAmbientColor ( const KColor & ambientColor )
{
    ambient_color = ambientColor;
    
    if (light_number)
    {
        glLightfv (light_number, GL_AMBIENT, ambient_color.getValues());
    }
}

// --------------------------------------------------------------------------------------------------------
void KLight::setDiffuseColor ( const KColor & diffuseColor )
{
    diffuse_color = diffuseColor;
    
    if (light_number)
    {
        glLightfv (light_number, GL_DIFFUSE, diffuse_color.getValues());
    }
}   
    
// --------------------------------------------------------------------------------------------------------
void KLight::setSpecularColor ( const KColor & specularColor )
{
    specular_color = specularColor;
    
    if (light_number)
    {
        glLightfv (light_number, GL_SPECULAR, specular_color.getValues());
    }
}


