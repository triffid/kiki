/*
 *  KButton.h
 *  kodisein
 */

#ifndef __KButton
#define __KButton

#include "KLabel.h"
#include "KNotificationObject.h"

class KButton : public KLabel, public KNotificationObject
{
    INTROSPECTION

    public:
                                KButton			( const std::string & = "" );
         
    virtual void		setPicked		( bool );
    virtual void		render			();
    virtual void		activate		();
    virtual void		deactivate		();
    virtual KColor *		getFGColor		() const;
    virtual KColor *		getBGColor		() const;
};

#endif

