
// __________________________________________________________________________________________________
%nodefault;

class KikiSound
{
    public: // ........................................................................ PUBLIC

    void	toggleMute	();
    void	setMute		( bool b );
    bool	isMute		() const;
    
    void	setSoundVolume	( int v );
    int		getSoundVolume	() const;
    
    void	playSound	( int sndId, float volume = -1.0, int loops = 0 );
    void	playSoundAtPos	( int sndId, const KikiPos & pos );
};
