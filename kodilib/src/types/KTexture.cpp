/*
 *  KTexture.cpp
 *  kodisein
 */

#include "KTexture.h"
#include "KConsole.h"
#include "KTools.h"

#include <SDL_image.h>
#include <SDL_opengl.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

KDL_CLASS_INTROSPECTION (KTexture)

// --------------------------------------------------------------------------------------------------------
KTexture::KTexture () : KObject ()
{
    texture_id	= 0;
    width 	= 0;
    height	= 0;
    bpp		= 0;
    filename	= "";
}

// --------------------------------------------------------------------------------------------------------
KTexture::KTexture ( const std::string & fn) : KObject ()
{
    texture_id	= 0;
    width 	= 0;
    height	= 0;
    bpp		= 0;
    filename	= "";
    setFileName(fn);
}

// --------------------------------------------------------------------------------------------------------
KTexture::~KTexture ()
{
    if (texture_id)
    {
        glDeleteTextures(1, &texture_id);
    }
}

// --------------------------------------------------------------------------------------------------------
void KTexture::setFileName ( const std::string & fn )
{
    if (fn != filename)
    {
        filename = fn;
        if (!loadFile())
        {
            KConsole::printError(kStringPrintf("unable to load texture file %s", filename.c_str()));
        }
    }
}

// --------------------------------------------------------------------------------------------------------
bool KTexture::loadFile ()
{
    SDL_Surface * imageSurface = IMG_Load (filename.c_str());

    if (imageSurface)
    {
        SDL_Surface * surface = SDL_ConvertSurface(imageSurface, &KDL_PIXEL_FORMAT, SDL_SWSURFACE);
        SDL_FreeSurface(imageSurface);
        
        if (surface)
        {
            if (texture_id)
            {
                glDeleteTextures(1, &texture_id);
            }
            glGenTextures	(1, &texture_id);
            if (!texture_id)
            {
                SDL_FreeSurface	(surface);
                return false;
            }
            
            // ...................................................... map width & height to power of 2
            void * scaleImageBuffer = NULL;
            width = 2; 
            height = 2;
            while (width  <= surface->w/2) width  *= 2;
            while (height <= surface->h/2) height *= 2;
            
            // ...................................................... check size before scaling
            bool foundValidSize = false;
            while (foundValidSize == false)
            {
                GLint checkWidth, checkHeight;
                glTexImage2D (GL_PROXY_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                                                GL_UNSIGNED_INT_8_8_8_8, surface->pixels);
                
                glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &checkWidth);
                glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &checkHeight);
                
                if (checkHeight != height || checkWidth != width)
                {
                    KConsole::printf("WARNING cannot handle texture size (%dx%d)", width, height);
                    width /= 2; height /= 2;
                    if (width == 1 || height == 1)
                    {
                        // paranoid -> maybe another problem than size occured
                        KConsole::printError("unable to handle texture!");
                        SDL_FreeSurface	(surface);
                        return false;
                    }
                    KConsole::printf("WARNING trying texture size (%dx%d)", width, height);
                }
                else
                {
                    foundValidSize = true;
                }
            }
                        
            // ...................................................... power of 2 scaling
            if (width != surface->w || height != surface->h)
            {
                KConsole::printf("WARNING texture file %s:", filename.c_str());
                KConsole::printf("WARNING    size (%dx%d) not a power of 2!", surface->w, surface->h);
                KConsole::printf("WARNING    scaling to size (%dx%d)", width, height);
                                
                if ((scaleImageBuffer = malloc (width * height * sizeof(GLuint))) == NULL)
                {
                    KConsole::printError("unable to allocate memory for scaling ");
                    return false;
                }
                
                if (gluScaleImage(GL_RGBA, surface->w, surface->h, GL_UNSIGNED_INT_8_8_8_8,
                                    surface->pixels, width, height, GL_UNSIGNED_INT_8_8_8_8, 
                                    scaleImageBuffer) != 0)
                {
                    KConsole::printError("unable to scale texture file %s!", filename.c_str());
                    free (scaleImageBuffer);
                    SDL_FreeSurface	(surface);
                    return false;
                }
                
                glBindTexture	(GL_TEXTURE_2D, texture_id);
                glTexImage2D	(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                                        GL_UNSIGNED_INT_8_8_8_8, scaleImageBuffer);
                                    
                free (scaleImageBuffer);
            }
            else
            {
                glBindTexture	(GL_TEXTURE_2D, texture_id);
                glTexImage2D	(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                                    GL_UNSIGNED_INT_8_8_8_8, surface->pixels);
            }
            
            glTexParameteri	(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri	(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            SDL_FreeSurface	(surface);
            
            return true;
        }
    }
    
    return false;
}


