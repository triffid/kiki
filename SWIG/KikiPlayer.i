
// __________________________________________________________________________________________________
%nodefault;

class KikiStatusDisplay 
{
    public: // ........................................................................ PUBLIC
    
    void		show ();
    void		hide ();
};

// __________________________________________________________________________________________________
%nodefault;

class KikiPlayback
{
    public: // ........................................................................ PUBLIC
    
    static void	start		( const std::string filename );
    static void	stop		();
};    

// __________________________________________________________________________________________________
%nodefault;

class KikiPlayer : public KikiBot
{
    public: // ........................................................................ PUBLIC

    void		die			();
    void		reborn			();
    void		reset			();

    void		startRecorder	 	( const std::string & file );    
    void		saveRecorder	 	();
    
    KProjection * 	getProjection 		();
    
    bool 		handleKey 		( const KKey & key );
    bool 		handleKeyRelease	( const KKey & key );
    void 		recordKeyForAction	( const std::string & actionName );
    static std::string	getActionForKey		( const std::string & keyName );
    static std::string	getKeyForAction		( const std::string & actionName );
    static void		setKeyForAction		( const std::string & keyName, const std::string & actionName );
    
    static void		setObjectColor		( const char * color_name, const KColor & color );
};
