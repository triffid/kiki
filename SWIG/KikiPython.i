
// --------------------------------------------------------------------------------------------------------
%nodefault;

class KikiPythonWidget
{
    public: // ........................................................................ PUBLIC
    
    KikiPos		cursorPos;
    KikiPos		selectionPos;

    int			getTextRows	() const;
    int			getTextCols	() const;
    KSize		getTextSize	() const;
    int			getColumnWidth	() const;
    int			getRowHeight	() const;
    KikiPython *	getPythonWindow () const;

    void 		displayStringAtPos ( const std::string & str, const KikiPos & pos );
};

// --------------------------------------------------------------------------------------------------------
%nodefault;

class KikiPython : public KWindow
{
    public: // ........................................................................ PUBLIC
    
    KikiPythonWidget *	getPythonWidget  ();
    void 		setScrollBarUnits( int, int );
    void 		requestUserInput ( const std::string & str );
    void 		setTitle	 ( const std::string & str );
    void 		setStatus	 ( const std::string & str );
    void 		setInput	 ( const std::string & str );
    void		executeFile 	 ( const std::string & pythonFile );
};
