/*
 *  KikiTest.cpp
 *  kiki
 */

#include "KikiTest.h"
//#include "test.h"

#include <KDisplayTools.h>
#if defined(__APPLE__) && defined(__MACH__) || defined(_WIN32)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiTest1, KikiObject )
KIKI_OBJECT_VALUES 		( KikiTest1, true )

// __________________________________________________________________________________________________
KDL_CLASS_INTROSPECTION_1 	( KikiTest2, KikiObject )
KIKI_OBJECT_VALUES 		( KikiTest2, true )

// __________________________________________________________________________________________________
void KikiTest1::render ()
{
    glColor3f(1.0, 1.0, 1.0);
    //render_test;
}

// __________________________________________________________________________________________________
void KikiTest2::render ()
{
}

