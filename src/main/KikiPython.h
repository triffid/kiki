/*
 *  KikiPython.h
 *  kiki
 */

#ifndef __KikiPython
#define __KikiPython

#include <KWindow.h>

#include <Python.h>
#include <string>

class KLabel;
class KTextField;
class KScrollBar;
class KIconButton;
class KikiPythonWidget;

// __________________________________________________________________________________________________
class KikiPython : public KWindow
{
    protected: // ..................................................................... PROTECTED

    KikiPythonWidget * 	python_widget;
    KScrollBar * 	scroll_bar;
    KLabel *		titel_label;
    KLabel * 		input_label;
    KTextField * 	input_field;
    KIconButton *     	maximize_button;    

    public: // ........................................................................ PUBLIC
                        KikiPython 		();
                        ~KikiPython 		();
    
    void		initPython		();
    void		finalize 		();
    bool		execute 		( const std::string & pythonCode, bool eval = false );
    bool		executeFile		( const std::string & pythonFile );
    KikiPythonWidget *	getPythonWidget 	() { return python_widget; }

    //void		display			( int mode ) { KWindow::display(mode); }
    void		setVisibility		( bool v );
    void		close			();
    void 		setScrollBarUnits	( int currentLine, int lines );
    void 		setTitle		( const std::string & );
    void 		setStatus		( const std::string & );
    void 		setInput		( const std::string & );
    void		userInput		( const std::string & );
    void		requestUserInput	( const std::string & message );
};

#endif

