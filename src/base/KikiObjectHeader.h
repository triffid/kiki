/*
 *  KikiObjectHeader.h
 *  kiki
 */

#ifndef __KikiObjectHeader
#define __KikiObjectHeader

#include "KikiColorObject.h"

#define KIKI_OBJECT_HEADER \
    INTROSPECTION \
    static   	const bool class_space_egoistic; \
    public: \
    virtual  	bool isSpaceEgoistic() const { return class_space_egoistic; } \
    KIKI_COLOR_HEADER

#define KIKI_OBJECT_EGO(className, spaceEgoistic) \
    const bool className::class_space_egoistic(spaceEgoistic);
    
#define KIKI_OBJECT_VALUES(className, spaceEgoistic) \
     KIKI_OBJECT_EGO(className, spaceEgoistic) \
     KIKI_COLOR_VALUES_0(className)

#define KIKI_OBJECT_VALUES_1(className, spaceEgoistic, color1) \
     KIKI_OBJECT_EGO(className, spaceEgoistic) \
     KIKI_COLOR_VALUES_1(className, color1)

#define KIKI_OBJECT_VALUES_2(className, spaceEgoistic, color1, color2) \
     KIKI_OBJECT_EGO(className, spaceEgoistic) \
     KIKI_COLOR_VALUES_2(className, color1, color2)

#define KIKI_OBJECT_VALUES_3(className, spaceEgoistic, color1, color2, color3) \
     KIKI_OBJECT_EGO(className, spaceEgoistic) \
     KIKI_COLOR_VALUES_3(className, color1, color2, color3)

#endif

