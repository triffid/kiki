/*
 *  KikiColorObject.h
 *  kiki
 */

#ifndef __KikiColorObject
#define __KikiColorObject

#include <KColor.h>
#include <vector>

#define KIKI_COLOR_HEADER \
    protected: \
    static	const char * color_names[]; \
    static 	std::vector<KColor> colors; \
    public: \
    static	void setObjectColor (const char *color_name, const KColor & color); \
    static	const KColor & getObjectColor (const char *color_name); \
    static	const KColor & getObjectColor (int color_index);

#define KIKI_COLOR_VALUES(className, number) \
    void className::setObjectColor (const char * color_name, const KColor & color) \
    { 	for (int i = 0; i < number; i++) { \
            if (strcmp(color_names[i], color_name) == 0) { colors[i] = color; return; } \
        } \
    } \
    const KColor & className::getObjectColor (const char * color_name) \
    { 	for (int i = 0; i < number; i++) { \
            if (strcmp(color_names[i], color_name) == 0) { return colors[i]; } \
        } \
        return colors[0]; \
    } \
    const KColor & className::getObjectColor (int color_index) \
    { \
        return colors[color_index]; \
    }

#define KIKI_COLOR_VALUES_0(className) \
    std::vector<KColor> className::colors(1); \
    const char * className::color_names[] = { "base" }; \
    enum { className ## _base_color, className ## _dummy }; \
    KIKI_COLOR_VALUES(className, 1)

#define KIKI_COLOR_VALUES_1(className, color1) \
    std::vector<KColor> className::colors(2); \
    const char * className::color_names[] = { "base", #color1 }; \
    enum { className ## _base_color, className ## _ ## color1 ## _color }; \
    KIKI_COLOR_VALUES(className, 2)

#define KIKI_COLOR_VALUES_2(className,color1,color2) \
    std::vector<KColor> className::colors(3); \
    const char * className::color_names[] = { "base", #color1, #color2 }; \
    enum { className ## _base_color, className ## _ ## color1 ## _color, \
           className ## _ ## color2 ## _color}; \
    KIKI_COLOR_VALUES(className, 3)

#define KIKI_COLOR_VALUES_3(className,color1,color2,color3) \
    std::vector<KColor> className::colors(4); \
    const char * className::color_names[] = { "base", #color1, #color2, #color3 }; \
    enum { className ## _base_color, className ## _ ## color1 ## _color, \
           className ## _ ## color2 ## _color, className ## _ ## color3 ## _color}; \
    KIKI_COLOR_VALUES(className, 4)

#endif

