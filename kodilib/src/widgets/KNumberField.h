/*
 *  KNumberField.h
 *  kodisein
 */

#ifndef __KNumberField
#define __KNumberField

#include "KTextField.h"

class KNumberField : public KTextField
{
    INTROSPECTION

    public:
                                KNumberField		( GLfloat );
                                
    virtual GLfloat		getValue		();
    virtual void		notify			();

    virtual bool		handleKey		( const KKey & );
};

#endif

