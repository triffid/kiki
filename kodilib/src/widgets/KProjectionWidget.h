/*
 *  KProjectionWidget.h
 *  kodisein
 */

#ifndef __KProjectionWidget
#define __KProjectionWidget

#include "KWidget.h"
#include "KPickHandler.h"

class KProjectionWidget : public KWidget, public KPickHandler
{
    INTROSPECTION

    public:
                                        KProjectionWidget	();
    
    virtual void			display			();
    virtual void			display			( int mode ) {}
    virtual void			displayPickables	( int mode );
    virtual void			displayContent		() = 0;
    virtual bool 			pick 			( const KMouseEvent &  );
};

#endif

