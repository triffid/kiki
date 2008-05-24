/*
 *  KDisplayTools.h
 *  kodisein
 */

#ifndef __KDisplayTools
#define __KDisplayTools

#include <string>
#include <vector>
#include <time.h>
#include <SDL_video.h>

#include "KVector.h"

void 		kDisplayString		( const std::string &, const KPosition &, bool = true );
void 		kDisplayString		( const std::string &, const KVector &, void * );
int     kDisplayXPMIcon		( const char ** xpmData, const KPosition & pos );
void		kDisplayWireSphere	( float radius = 0.5, int subdivisions = 8);
void		kDisplaySolidSphere	( float radius = 0.5, int subdivisions = 8);
void		kDisplaySolidCube	( float sidelength = 1.0);
void		kDisplayWireCube	( float sidelength = 1.0);
void		kDisplaySolidCylinder	( float base = 0.5, float top = 0.0, float height = 1.0, int subdivisions = 8);

extern SDL_PixelFormat KDL_PIXEL_FORMAT;

// --------------------------------------------------------------------------------------------------------
#define RECTANGLE_XY(minx, maxx, miny, maxy, z) {	glNormal3f(0.0, 0.0, 1.0); \
                                                        glVertex3f(maxx, maxy, z); \
                                                        glVertex3f(minx, maxy, z); \
                                                        glVertex3f(minx, miny, z); \
                                                        glVertex3f(maxx, miny, z); }
#define RECTANGLE_YX(minx, maxx, miny, maxy, z) {	glNormal3f(0.0,  0.0, -1.0); \
                                                        glVertex3f(maxx, maxy, z); \
                                                        glVertex3f(maxx, miny, z); \
                                                        glVertex3f(minx, miny, z); \
                                                        glVertex3f(minx, maxy, z); }

#define RECTANGLE_XZ(minx, maxx, minz, maxz, y) {	glNormal3f(0.0, -1.0, 0.0); \
                                                        glVertex3f(maxx, y, maxz); \
                                                        glVertex3f(minx, y, maxz); \
                                                        glVertex3f(minx, y, minz); \
                                                        glVertex3f(maxx, y, minz); }
#define RECTANGLE_ZX(minx, maxx, minz, maxz, y) {	glNormal3f(0.0, 1.0, 0.0); \
                                                        glVertex3f(maxx, y, maxz); \
                                                        glVertex3f(maxx, y, minz); \
                                                        glVertex3f(minx, y, minz); \
                                                        glVertex3f(minx, y, maxz); }
                                                        
#define RECTANGLE_ZY(miny, maxy, minz, maxz, x) {	glNormal3f(-1.0, 0.0, 0.0); \
                                                        glVertex3f(x, maxy, maxz); \
                                                        glVertex3f(x, maxy, minz); \
                                                        glVertex3f(x, miny, minz); \
                                                        glVertex3f(x, miny, maxz); }
#define RECTANGLE_YZ(miny, maxy, minz, maxz, x) {	glNormal3f(1.0, 0.0, 0.0); \
                                                        glVertex3f(x, maxy, maxz); \
                                                        glVertex3f(x, miny, maxz); \
                                                        glVertex3f(x, miny, minz); \
                                                        glVertex3f(x, maxy, minz); }

// --------------------------------------------------------------------------------------------------------
#define CLASS_NAME \
    private: \
    static   const std::string class_name; \
    public: \
    virtual  const std::string & getName() const { return class_name; } \
    static   const std::string & name()          { return class_name; } \
    private: \

#define CLASS_NAME_NAME(className, name) \
    const std::string className::class_name(name); \

// --------------------------------------------------------------------------------------------------------
#define OBJECT_ID \
    private: \
    long object_id; \
    void	setObjectId(long i) { object_id = i; } \
    void	initObjectId() { object_id = time(NULL) + random(); } \
    public: \
    long 	getObjectId() const { return object_id; } \
    private:

#endif


