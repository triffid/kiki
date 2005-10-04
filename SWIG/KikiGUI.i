
// __________________________________________________________________________________________________
%nodefault;

class KikiGUI : public KWindow
{
};

// __________________________________________________________________________________________________
%nodefault;

class KikiScreenText : public KikiText, public KikiActionObject
{
    public: // ........................................................................ PUBLIC
                KikiScreenText	();

    void	addText ( const std::string & text, float scaleFactor = 1.0 );
    void	setText ( const std::string & text, int colorIndex = 0 );
    void	show    ();
    KProjection * getProjection ();
};

// __________________________________________________________________________________________________
%nodefault;

class KikiMenu : public KikiScreenText
{
    public: // ........................................................................ PUBLIC
                KikiMenu	( int selectedItem = -1 );
                
    virtual void addItem	( const std::string & itemText, KikiAction * action = NULL );
    virtual void addOption	( const std::string & itemText, KikiAction * action = NULL );
    void	setEscapeActive ( bool active = true );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiScrollMenu : public KikiMenu 
{
    public: // ........................................................................ PUBLIC

                KikiScrollMenu	( int visibleItems = 10, int selectedItem = -1 );
    
    virtual void addItem	( const std::string & itemText, KikiAction * action = 0 );    
};

// __________________________________________________________________________________________________
%nodefault;

class KikiColumnMenu : public KikiMenu 
{
    public: // ........................................................................ PUBLIC

                KikiColumnMenu	( int maxColumnItems = 10, int selectedItem = -1 );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiPageText : public KikiScreenText
{
    public: // ........................................................................ PUBLIC
                KikiPageText	( const std::string & pageText, 	
                                    bool nextPage, bool previousPage = true );
};
