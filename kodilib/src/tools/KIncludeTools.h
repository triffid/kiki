/*
 *  KIncludeTools.h
 *  kodisein
 */

#ifndef __KIncludeTools
#define __KIncludeTools

#ifdef WIN32
#pragma warning ( disable : 4800 4305 4267 ) // Disable warnings
#endif

#ifdef K_INCLUDE_GLUT
#	if defined(__APPLE__) && defined(__MACH__)
#		include <GLUT/glut.h>
#	else
#		include <GL/glut.h>
#	endif
#endif

#endif