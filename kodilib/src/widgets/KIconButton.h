/*
 *  KIconButton.h
 *  kodisein
 */

#ifndef __KIconButton
#define __KIconButton

#include "KButton.h"

enum {	KDL_ICONBUTTON_CROSS, 
        KDL_ICONBUTTON_ARROW_UP, 
        KDL_ICONBUTTON_ARROW_DOWN, 
        KDL_ICONBUTTON_ARROW_LEFT, 
        KDL_ICONBUTTON_ARROW_RIGHT, 
        KDL_ICONBUTTON_CLEAR,
        KDL_ICONBUTTON_DOUBLE_DOWN, 
        KDL_ICONBUTTON_DOUBLE_UP, 
        KDL_ICONBUTTON_SINGLE_UP, 
        KDL_ICONBUTTON_SINGLE_DOWN, 
        KDL_ICONBUTTON_BOTTOM, 
        KDL_ICONBUTTON_TOP 
    };

class KIconButton : public KButton
{
    INTROSPECTION

    protected:
    
    int			type;
    
    public:

                        KIconButton		( int );
                    
    virtual void	setType			( int t ) { type = t; }
    virtual int		getType			() const { return type; }
    virtual void	render			();    
};

#endif

