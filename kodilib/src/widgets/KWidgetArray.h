/*
 *  KWidgetArray.h
 *  kodisein
 */
 
#ifndef __KWidgetArray
#define __KWidgetArray
 
#include "KWidget.h"

enum {  KDL_WIDGETARRAY_FLAG_HORIZONTAL = KDL_WIDGET_FLAG_END,
        KDL_WIDGETARRAY_FLAG_END };
 
class KWidgetArray : public KWidget
{
    INTROSPECTION
    
    protected:
    
    int			spacing;
    int			frame_spacing;
    
    public:		
                        KWidgetArray	();
    void		clear		();
    
    virtual KSize	layout		();
    virtual KSize	relayout	( const KSize & s );
    
    void		setFrameSpacing	( int s ) { frame_spacing = s; }
    void		setChildSpacing	( int s ) { spacing = s; }
    int 		getSpacing	() const { return spacing; }
    int 		getFrameSpacing	() const { return frame_spacing; }

    void		alignLabels	();
};

#endif
