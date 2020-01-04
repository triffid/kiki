// __________________________________________________________________________________________________
class KikiPos
{
    public: // ........................................................................ PUBLIC
    
    int x;
    int y;
    int z;
                        KikiPos		();
                        KikiPos		( int, int, int = 0 );
                        KikiPos		( double, double, double = 0 );
                        KikiPos		( const KikiPos & p );
                        KikiPos		( const KVector & v );
    KikiPos		operator-  	( const KikiPos & p ) const;
    KikiPos		operator+  	( const KikiPos & p ) const;
    KikiPos &		operator+= 	( const KikiPos & p );
    KikiPos &		operator-= 	( const KikiPos & p );
    std::string		getString  	() const;
    
    %extend {

    bool 		__eq__		(const KikiPos & p) 
                                            { return (self->x==p.x && self->y==p.y && self->z==p.z); }
    bool 		__ne__		(const KikiPos & p) 
                                            { return (self->x!=p.x || self->y!=p.y || self->z!=p.z); }
                                            
    char *		__str__		()  {
                                                static char temp[256];
                                                sprintf(temp,"[ %d, %d, %d ]", self->x,self->y,self->z);
                                                return &temp[0];
                                            }
    }
};

// __________________________________________________________________________________________________
typedef KikiPos KikiSize; // :-)

// --------------------------------------------------------------------------------------------------------
class KVector
{
    public: // ........................................................................ PUBLIC
                        KVector 		();
                        KVector			( const float x, const float y, 
                                                  const float z = 0.0, const float w = 0.0 );
                        KVector 		( const KVector & v );
                                
    KVector &		reset			();
    KVector &		normalize		();
    KVector &		operator+=		( const KVector & );
    KVector &		operator-=		( const KVector & );    
    KVector &		operator*=		( float );
    KVector &		operator/=		( float );
    KVector		cross			( const KVector & ) const;
    float		operator*		( const KVector & ) const;
    KVector		operator-		( const KVector & ) const;
    KVector		operator+		( const KVector & ) const;
    KVector		operator*		( float ) const;
    KVector		operator/		( float ) const;
    KVector		perpendicular		( const KVector & ) const;
    KVector		parallel		( const KVector & ) const;
    KVector		reflect			( const KVector & ) const;
    KVector		normal			() const;
    float		length			() const;
    float		angle			( const KVector & ) const;
    float		xyangle			( const KVector & ) const;
    KVector		xyperp			() const;
    KVector		round			() const;
    void		glVertex		() const;
    
    %extend {

    bool 		__getitem__	(int key) { return (*self)[key]; }
        
    char *		__str__		()  {
                                                static char temp[256];
                                                sprintf(temp,"(%f, %f, %f)", (*self)[0],(*self)[1],(*self)[2]);
                                                return &temp[0];
                                            }
    }
};

// --------------------------------------------------------------------------------------------------------
class KQuaternion
{
    public: // ........................................................................ PUBLIC

    float 		w, x, y, z;
        
                        KQuaternion	( float w=1.0, float x=0.0,  float y=0.0, float z=0.0 );    
                        KQuaternion 	( const KQuaternion & q );
                        KQuaternion 	( const KVector & v );
    static KQuaternion	rotationAroundVector ( float theta, const KVector & vector );    
    KVector 		rotate		( const KVector & v ) const;
    KQuaternion & 	normalize	();
    KQuaternion & 	invert 		();
    KQuaternion & 	conjugate	();
    KQuaternion 	getNormal	() const;
    KQuaternion 	getConjugate	() const;
    KQuaternion 	getInverse	() const;
    float		length		() const;
    void		glRotate	() const;
    KQuaternion 	slerp		( const KQuaternion & quat, float t ) const;
    KQuaternion 	operator *	( const KQuaternion & quat ) const;

%extend {
        
    char *		__str__		()  
            {
                static char temp[256];
                sprintf(temp,"[ %f: %f, %f, %f ]", self->w, self->x, self->y, self->z);
                return &temp[0];
            }
    }

};        

// --------------------------------------------------------------------------------------------------------
class KColor
{
    public: // ........................................................................ PUBLIC
                        KColor 		();
                        KColor 		( const KColor & object );
                        KColor 		( float r, float g, float b, float a = 1.0 );
                        
    void		setValues	( const float r, const float g, const float b,
                                          const float a = 1.0 );

    void		setRed		( const float r );
    void		setGreen	( const float g );
    void		setBlue		( const float b );
    void		setAlpha	( const float a );
    float		getRed		( ) const;
    float		getGreen	( ) const;
    float		getBlue		( ) const;
    float		getAlpha	( ) const;
    
    void		glColor		() const;

%extend {
        
    char *		__str__		()  
            {
                static char temp[256];
                sprintf (temp,"( r:%f g:%f b:%f a:%f)", self->getRed(), self->getGreen(), 
                                                        self->getBlue(), self->getAlpha());
                return &temp[0];
            }
    }

};

// --------------------------------------------------------------------------------------------------------
%nodefault;

class KProjection
{
    public: // ........................................................................ PUBLIC
    
    void	focusOn		( const KVector & position );
    void	setFov		( float );
    float	getFov		() const;
    void	setViewport	( float left, float bottom, float width, float height );
    void	setPosition	( const KVector & position );
};

// --------------------------------------------------------------------------------------------------------
%nodefault;

struct KKey 
{
    KKey	( std::string keyName );

    std::string	name;
    
    std::string	getUnmodifiedName () const;
    std::string	getModifierName () const;
};


