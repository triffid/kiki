/*
 *  KButtonBox.h
 *  kodisein
 */

#ifndef __KButtonBox
#define __KButtonBox

#include "KWidgetArray.h"
#include <string>

class KButton;

class KButtonBox : public KWidgetArray
{
    INTROSPECTION
    
    public:
                                        KButtonBox	();
    
    void				addButton	( KButton * );
    void 				buttonCallback  ( const std::string & );
    
    bool				hasSubPickables	() const { return true; }
    const PickableVector *		getSubPickables	() const { return &children; }
};

#endif

