/*
 *  KTexture.h
 *  kodisein
 */

#ifndef __KTexture
#define __KTexture

#include "KNotificationObject.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <GL/gl.h>
#endif

class KTexture : public KObject
{
    INTROSPECTION
    
    public:
    
    int 		bpp;
    int 		width;
    int 		height;
    GLuint		texture_id;
    std::string		filename;
 
                        KTexture 		();
                        KTexture 		( const std::string & );
    virtual             ~KTexture		();
                       
    bool		loadFile		();
    void		setFileName		( const std::string & );
    std::string	 	getFileName		() const { return filename; }
    GLuint		getTextureId		() const { return texture_id; }
};

#endif

