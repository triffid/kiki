
// __________________________________________________________________________________________________
%nodefault;

class KikiActionObject
{
    public: // ........................................................................ PUBLIC

    void		addAction		( KikiAction * action );
    void		removeAction		( KikiAction * action );
    void		startTimedAction	( KikiAction * action, int duration = -1 );
    void		startTimer		( int duration, int mode );
    KikiAction *	getActionWithName	( const std::string & name );
    KikiAction *	getActionWithId		( int actionId );

    int			addEventWithName	( const std::string & );
    KikiEvent *		getEventWithName	( const std::string & name );
    KikiEvent *		getEventWithId		( int actionId );

    const char * 	getClassName		() const;
};

// __________________________________________________________________________________________________
%nodefault;

class KikiObject : public KikiActionObject
{
    public: // ........................................................................ PUBLIC

    void		setName			( const std::string & );
    std::string		getName			() const;
    
    KikiPos		getPos			() const;
    virtual void	setPosition		( const KVector & v );
    KVector		getPosition		() const;
    void		setOrientation		( const KQuaternion & q );
    KQuaternion		getOrientation		() const;
    void		setCurrentOrientation	( const KQuaternion & q );
    KQuaternion		getCurrentOrientation	() const;

    virtual bool	isSpaceEgoistic 	() const;
        
    const char * 	getClassName		() const;
};
