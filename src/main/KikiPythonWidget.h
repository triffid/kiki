/*
 *  KikiPythonWidget.h
 *  kiki
 */

#ifndef __KikiPythonWidget
#define __KikiPythonWidget

#include "KikiPos.h"
#include "KikiPython.h"
#include <KTextField.h>

class KikiPythonWidget : public KTextField
{
    friend class	KikiPython;

    protected: // ..................................................................... PROTECTED
    
    void		initPython		();

    public: // ........................................................................ PUBLIC

    KikiPos 		cursorPos;
    KikiPos 		selectionPos;

                        KikiPythonWidget	();
                                                
    bool		execute			( const std::string & cmd, bool eval = false );

    void		clear			();
    void		scrollRelative		( float );    
    void		scrollPageUp		() { execute("scrollPageUp()"); }
    void		scrollPageDown		() { execute("scrollPageDown()"); }
    void		scrollLineUp		() { execute("scrollLineUp()"); }
    void		scrollLineDown		() { execute("scrollLineDown()"); }  
    void		scrollToTop		() { execute("scrollToTop()"); }
    void		scrollToBottom		() { execute("scrollToBottom()"); }
    void		doubleClicked 		() { execute("doubleClicked()"); }
    void		setPicked		( bool );
    void		mouseMoved 		( const KMouseEvent & );
    bool		handleKey		( const KKey & );
    KSize		relayout		( const KSize & );
    
    KikiPython *	getPythonWindow		() const { return (KikiPython*)getWindow(); }

    void		render			();
    void		displayStringAtPos	( const std::string &, const KikiPos & );
};

#endif

