
// __________________________________________________________________________________________________
%nodefault;

class KikiController : public KEventHandler, public KikiActionObject
{
    public: // ........................................................................ PUBLIC
    
    KikiGUI * 			gui;
    KikiSound *			sound;
    KikiWorld *			world;
    KikiPlayer *		player;
    KikiPython *		python;
    KikiStatusDisplay *		player_status;
    KikiEvent *			timer_event;
    
    KikiPlayer *		getPlayer		();
    
    int				unmapMsTime		( int ms );
    int				mapMsTime		( int ms );

    void			setSpeed		( int s );
    int				getSpeed		() const;

    std::string                 getKikiHome             ();

    void			setGamma		( int g );
    int				getGamma		() const;
    
    void			displayText		( const std::string & text, int color );
    std::string			getLocalizedString	( const std::string & key );

    bool 			isDebugVersion		();
};

// __________________________________________________________________________________________________

extern KikiController Controller;

// __________________________________________________________________________________________________
%{
    const char * replaceTabs	( const std::string & str, int tabWidth )
    {
        static std::string tmpStr;
        tmpStr = str;
        kStringReplaceTabs (tmpStr, tabWidth);
        return tmpStr.c_str();
    } 
%}

const char * replaceTabs	( const std::string & str, int tabWidth );

