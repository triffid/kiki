/*
 *  KSliderButton.h
 *  kodisein
 */

#ifndef __KSliderButton
#define __KSliderButton

#include "KButton.h"
#include "KNotificationObject.h"

class KSliderButton : public KButton
{
    INTROSPECTION

    public:
                        KSliderButton	();
         
    virtual void	moved		( const KMouseEvent & );
    virtual void	setSize		( KSize & s ) { KWidget::setSize(s); }
    virtual void	render		();
};

#endif


