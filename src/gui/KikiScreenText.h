/*
 *  KikiScreenText.h
 *  kiki
 */

#ifndef __KikiScreenText
#define __KikiScreenText

#include "KikiText.h"
#include "KikiActionObject.h"

#include <KKeyHandler.h>
#include <KPickHandler.h>

// __________________________________________________________________________________________________
class KikiScreenText : public KPickHandler, public KKeyHandler, public KikiText, public KikiActionObject
{
    public: // ........................................................................ PUBLIC
                        KikiScreenText  ();
    virtual            ~KikiScreenText  ();
    
    void                addText         ( const std::string &, float scaleFactor = 1.0 );
    virtual void        display         ( int );
    virtual void        display         ();
    virtual void        show            ();

    virtual void        performAction   ( KikiAction * action );
    virtual void        actionFinished  ( KikiAction * action );

    virtual bool        handleKey       ( const KKey & key );

    protected: // ..................................................................... PROTECTED
    
    float               fade_value;
    
    enum {              ACTION_SHOW, 
                        ACTION_HIDE, 
                        ACTION_DELETE,
                        ACTION_END };
};

#endif

