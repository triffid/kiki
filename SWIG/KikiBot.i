
// __________________________________________________________________________________________________
%nodefault;

class KikiBotStatus
{
    public: // ........................................................................ PUBLIC
    
    int		getMoves	() const;
    void	setMoves	( int moves );
    void	addMoves	( int moves );

    int		getMinMoves	() const;
    void	setMinMoves	( int moves );

    /*
    float 	getEnergy 	() const;
    float	getHealth	() const;
    
    void	setHealth	( float health );
    void	setEnergy	( float	energy );

    void	addHealth	( float health );
    void	addEnergy	( float energy );
    */    
};

// __________________________________________________________________________________________________
%nodefault;

class KikiBotFume : public KikiObject
{
    public: // ........................................................................ PUBLIC
    
    static void	setObjectColor	( const char * color_name, const KColor & color );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiBot : public KikiObject
{
    public: // ........................................................................ PUBLIC
    
    bool	isDead		() const;

    KikiPos	getDown		();
    KikiPos	getUp		();
    KikiPos	getDir		();
    
    void	setMove		( bool );
    
    KikiBotStatus *	getStatus	();
};