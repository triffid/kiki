
// --------------------------------------------------------------------------------------------------------
%nodefault;

class KEventHandler
{
    public: // ........................................................................ PUBLIC

    virtual void	quit				();

    static int		getMouseState			();
    static KPosition	getMousePos			();
    static KPosition	getMouseDelta 			();
    
    static KSize	getScreenSize 			();
    static bool		setScreenSize			( int width, int height, bool fullscreen = false );

    static bool		getFullscreen			();
    static void		setFullscreen			( bool );
    
    static unsigned int getTime				();
    
    void		setWireframeMode		( bool );
    
    void		setDisplayFps			( bool );
    bool		getDisplayFps			() const;
};
