
// --------------------------------------------------------------------------------------------------------
%nodefault;

class KWindow
{
    public: // ........................................................................ PUBLIC
            
    bool	isVisible		() const;
    void	setVisibility		( bool v );
    void	toggleVisibility	();
    void	maximize		();
    void	show			();
    void	hide			();
    void	close			();

    void	setSize			( KSize );
    void	setPosition		( const KPosition & );
};
