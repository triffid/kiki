
// --------------------------------------------------------------------------------------------------------
%nodefault;

class KConsole : public KWindow
{
    public: // ........................................................................ PUBLIC
    
    %rename(_print) print;
    static void		print			( const std::string & s );
    static void		write			( const std::string & s );
    static void		printError		( const std::string &, bool = false );
    static KConsole *	getConsole		();
    void		clear			();

%pythoncode %{

    def out (self, *args):
        _kiki.KConsole__print(" ".join(map(str, args)))
    %}
    
};
