/*
 *  KConsole.cpp
 *  kodisein
 */

#ifndef __KConsole
#define __KConsole

#include "KWindow.h"
#include "KStringTools.h"

class KTextWidget;
class KScrollBar;

class KConsole : public KWindow
{
    INTROSPECTION
    
    protected:
    
                        KConsole		();

    static KConsole *	console;
    KScrollBar * 	scroll_bar;
    KTextWidget * 	text_widget;
    KIconButton *     	maximize_button;
    
    static void		printString		( const std::string & );
    
    public:
    
    static void		create			();
    static KConsole *	getConsole		() { return console; }
                                        
    static void		printf			( const char * fmt ... );
    static void		debugf			( bool, const char * fmt ... );
    static void		print			( const std::string & s ) { printf("%s",s.c_str()); }
    static void		write			( const std::string & s );
    static void		printError		( const std::string &, bool = false );
    static void		checkGLError		( const std::string & = "");
    
    virtual void	relayout		( const KSize & );
    virtual void	clear			();
};

#endif


