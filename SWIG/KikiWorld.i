
// __________________________________________________________________________________________________
%nodefault;

class KikiWorld
{
    public: // ........................................................................ PUBLIC

    enum {  	CAMERA_INSIDE, CAMERA_BEHIND, CAMERA_FOLLOW };
        
    // ........................................................................ world size
    void	setSize 		(int x, int y, int z = 0);
    KikiSize	getSize			() const;
    
    void	setName			( const std::string & name );
    std::string getName			() const;
    
    void	init			();
    
    void	setDisplayShadows	( bool );
    void	setDisplayRaster	( bool );
    void	setDisplayBorder	( bool );

    void	setRasterSize		( float rasterSize );

    static void	setObjectColor		( const char * color_name, const KColor & color );

    // ........................................................................ camera & projection
    void	changeCameraMode	();
    int		getCameraMode		() const;
    void	setCameraMode		( int mode );

    KProjection * getProjection		();

    // ........................................................................ object handling
    void      	addObjectAtPos   	( KikiObject * object, const KikiPos & pos );
    void      	setObjectAtPos   	( KikiObject * object, const KikiPos & pos );
    void  	unsetObject	 	( KikiObject * object );
    void  	removeObject	 	( KikiObject * object );
    
    void  	deleteObject	 	( KikiObject * object );
    void	deleteAllObjects	();
    void	deleteObjectsWithClassName	( const std::string & className );
    KikiObject* getObjectWithName	( const std::string & objectName );

    bool	moveObjectToPos 	( KikiObject * object, const KikiPos & pos );
    void	objectWillMoveToPos 	( KikiObject * object, const KikiPos & pos, int duration );	
    void	objectMovedFromPos	( KikiObject * object, const KikiPos & pos );

    // ........................................................................ pos accessors
    KikiBot * 		getBotAtPos 		( const KikiPos & pos ) const;
    KikiObject * 	getOccupantAtPos 	( const KikiPos & pos ) const;
    KikiObject * 	getRealOccupantAtPos 	( const KikiPos & pos ) const;

    // ........................................................................ position helpers
    KikiPos	getNearestValidPos	( const KikiPos & pos ) const;
    bool	isInvalidPos		( const KikiPos & pos ) const;
    bool	isValidPos		( const KikiPos & pos ) const;
    bool	isUnoccupiedPos		( const KikiPos & pos ) const;
    bool	isOccupiedPos		( const KikiPos & pos ) const;
    int		posToIndex 		( const KikiPos & pos ) const;
    KikiPos	indexToPos 		( int index ) const;
    
%extend {

    KikiPos 	getPickedPos		() 
                                        {    
                                            if (self->getPickedPickable())
                                            {
                                                return ((KikiObject*)self->getPickedPickable())->getPos(); 
                                            }
                                            return KikiPos ();
                                        }
    }

};
