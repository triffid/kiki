/*
 *  KDisplayTools.cpp
 *  kodisein
 */

#include "KDisplayTools.h"

#include "KSeparatedMatrix.h"
#include "KVector.h"
#include "KConsole.h"

#include <SDL_video.h>
#include <SDL_image.h>

// --------------------------------------------------------------------------------------------------------
SDL_PixelFormat KDL_PIXEL_FORMAT = { 
    0x0, 		// palette
    0x20,   		// bits per pixel
    0x04,    		// bytes per pixel
    0x0,0x0,0x0,0x0,	// loss
    0x18,0x10,0x08,0x0, // shift
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    0xff000000, 	// rmask 
    0x00ff0000, 	// gmask
    0x0000ff00, 	// bmask
    0x000000ff, 	// amask
//#else
//    0x000000ff,
//    0x0000ff00,
//    0x00ff0000,
//    0xff000000,
//#endif
    0x0,		// color key
    0xff 		// alpha
};

// --------------------------------------------------------------------------------------------------------
int kDisplayXPMIcon ( char ** xpmData, const KPosition & pos )
{
    glPushAttrib(GL_PIXEL_MODE_BIT);
    
    float color[4];
    glGetFloatv(GL_CURRENT_COLOR, color);
    
    glPixelTransferf(GL_RED_SCALE, color[0]);
    glPixelTransferf(GL_GREEN_SCALE, color[1]);
    glPixelTransferf(GL_BLUE_SCALE, color[2]);
    
    SDL_Surface * xpmSurface = IMG_ReadXPMFromArray (xpmData);
    if (xpmSurface == NULL) 
    {
        KConsole::printError("kDisplayXPMIcon: IMG_ReadXPMFromArray failed");
        glPopAttrib();
        return 0;
    }
    SDL_Surface * surface = SDL_ConvertSurface(xpmSurface, &KDL_PIXEL_FORMAT, SDL_SWSURFACE);
    if (surface == NULL) 
    {
        KConsole::printError("kDisplayXPMIcon: SDL_ConvertSurface failed");
        glPopAttrib();
        SDL_FreeSurface(xpmSurface);
        return 0;
    }
    SDL_FreeSurface(xpmSurface);
    
    int width = surface->w;
    glRasterPos2f(pos.x-0.5, pos.y+0.5);
#ifndef _WIN32
    glDrawPixels(surface->w, surface->h, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, surface->pixels);
#else
	glDrawPixels(surface->w, surface->h, GL_RGBA, GL_4_BYTES, surface->pixels);
#endif

    SDL_FreeSurface(surface);
    
    glPopAttrib();
    return width;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

float kScreenUnitPerWorldUnitAtPos ( const KVector & pos )
{
    GLdouble ox, oy, xx, xy, yx, yy, zx, zy, z, model[16], proj[16]; GLint view[4];
    GLdouble px = pos[X], py = pos[Y], pz = pos[Z];
    
    glGetDoublev(GL_PROJECTION_MATRIX, proj); 
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetIntegerv(GL_VIEWPORT, (GLint*)view);

    gluProject(px, py, pz, 	 model, proj, view, &ox, &oy, &z);
    gluProject(px + 1.0, py, pz, model, proj, view, &xx, &xy, &z);
    gluProject(px, py + 1.0, pz, model, proj, view, &yx, &yy, &z);
    gluProject(px, py, pz + 1.0, model, proj, view, &zx, &zy, &z);
    
    return (kMax(kMax(kAbs(xx-ox)+kAbs(xy-oy),kAbs(yx-ox)+kAbs(yy-oy)),kAbs(zx-ox)+kAbs(zy-oy)));
}

// --------------------------------------------------------------------------------------------------------
void kStrokeString ( const std::string & str, const KVector & position, void * font )
{
    glPushMatrix();
    glTranslatef(position[X], position[Y], position[Z]);
    glScaled(1.0/155.0, 1.0/155.0, 1.0/155.0);
    glPushMatrix();
    for ( int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] == '\n')
        {
            glPopMatrix();
            glTranslatef(0, -155.0, 0);
            glPushMatrix();
        }
        else
        {
            glutStrokeCharacter(font, str[i]);
        }
    }
    glPopMatrix();
    glPopMatrix();
}

// --------------------------------------------------------------------------------------------------------
void kBitmapString ( const std::string & str, const KVector & position, void * font )
{
    float units = kScreenUnitPerWorldUnitAtPos(position);

    float x = position[X], ox = position[X], y = position[Y];
    
    for ( int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] == '\n')
        {
            y -= (15.0 / units);
            x  = ox;
        }
        else
        {
            glRasterPos2d(x, y);
            glutBitmapCharacter(font, str[i]);
            x += (9.0 / units);
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void kDisplayString ( const std::string & str, const KVector & position, void * font )
{
    std::string replaced(str);
    kStringReplace(replaced, "\\n", "\n");
        
    if (font == GLUT_STROKE_ROMAN || font == GLUT_STROKE_MONO_ROMAN)
    {
        kStrokeString(replaced, position, font);
    }
    else
    {
        glRasterPos2fv(position.getValues());
        kBitmapString(replaced, position, font);
    }
}

// --------------------------------------------------------------------------------------------------------
void kDisplayString ( const std::string & str, const KPosition & pos, bool largeFont )
{
    int x = pos.x, ox = pos.x, y = pos.y;
    
    for ( int i = 0; i < (int)str.size(); i++)
    {
        if (str.c_str()[i] == '\n')
        {
            y -= largeFont ? 15 : 13;
            x  = ox;
        }
        else
        {
            glRasterPos2i(x, y);   
            glutBitmapCharacter(largeFont ? GLUT_BITMAP_9_BY_15 : GLUT_BITMAP_8_BY_13, str.c_str()[i]);
            x += largeFont ? 9 : 8;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void kDisplaySolidCube ( float sidelength )
{
    glutSolidCube(sidelength);
}

// __________________________________________________________________________________________________
void kDisplayWireCube ( float sidelength )
{
    glutWireCube(sidelength);
}

// --------------------------------------------------------------------------------------------------------
void kDisplaySolidSphere ( float radius, int subdivisions )
{
    GLUquadric * quad = gluNewQuadric();
    gluSphere(quad, radius, subdivisions, subdivisions);
    gluDeleteQuadric(quad);
}

// --------------------------------------------------------------------------------------------------------
void kDisplayWireSphere ( float radius, int subdivisions )
{
    GLUquadric * quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, radius, subdivisions, subdivisions);
    gluDeleteQuadric(quad);
}

// --------------------------------------------------------------------------------------------------------
void kDisplaySolidCylinder ( float base, float top, float height, int subdivisions )
{
    GLUquadric * quad = gluNewQuadric();
    gluCylinder(quad, base, top, height, subdivisions, 1);
    gluDeleteQuadric(quad);
}

