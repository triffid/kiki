
// __________________________________________________________________________________________________
%nodefault;

class KikiFace
{
    public: // ........................................................................ PUBLIC
    
    enum {		PX, X=0, PY, Y=1, PZ, Z=2, NX, NY, NZ };
};

// __________________________________________________________________________________________________
%nodefault;

class KikiWire : public KikiObject
{
    public: // ........................................................................ PUBLIC

    enum {		UP=1, RIGHT, DOWN=4, VERTICAL, LEFT=8, HORIZONTAL=10, ALL=15 };

                        KikiWire	( int face = KikiFace::PZ, int directions = ALL );

    virtual void	setActive	( bool active = true );
    static  void	setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{

    KikiWire *		kikiObjectToWire ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiWire*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiGear : public KikiObject, public KikiFace
{
    public: // ........................................................................ PUBLIC
                        KikiGear	( int face = KikiFace::PZ );

    void		setActive	( bool active = true );

    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{

    KikiGear *		kikiObjectToGear ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiGear*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiValve : public KikiObject, public KikiFace
{
    public: // ........................................................................ PUBLIC
                        KikiValve	( int face = KikiFace::PZ );

    static void		setObjectColor	( const char * color_name, const KColor & color );
};
    
%inline %{

    KikiValve *		kikiObjectToValve ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiValve*>(o);
                        }
%}
    
// __________________________________________________________________________________________________
%nodefault;

class KikiMotorCylinder : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiMotorCylinder 	( int face = KikiFace::PZ );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiMotorGear : public KikiGear
{
    public: // ........................................................................ PUBLIC
                        KikiMotorGear 	( int face = KikiFace::PZ );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiGenerator : public KikiGear
{
    public: // ........................................................................ PUBLIC
                        KikiGenerator 	( int face = KikiFace::PZ );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiLight : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiLight	();
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{

    KikiLight *		kikiObjectToLight ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiLight*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiCellText : public KikiObject, public KikiText
{
    public: // ........................................................................ PUBLIC
                        KikiCellText	( const std::string & text, float cell_height = 1.0, 
                                          bool center = true, int colorIndex = 0 );
                                          
    void		setOffset	( const KVector & );
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiCellText *	kikiObjectToCellText ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiCellText*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiStone : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiStone 	 ();

    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiStone *	kikiObjectToStone ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiStone*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiWireStone : public KikiStone
{
    public: // ........................................................................ PUBLIC
                        KikiWireStone 	 ();

    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiWireStone *	kikiObjectToWireStone ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiWireStone*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiWall : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiWall 	 ();
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiWall *	kikiObjectToWall ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiWall*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiBomb : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiBomb 	 ();

    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiBomb *	kikiObjectToBomb ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiBomb*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiSwitch : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiSwitch	( bool on = false );
                        
    void		toggle		();
    void		setActive	( bool active );
    bool		isActive	() const;
    
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiSwitch *	kikiObjectToSwitch ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiSwitch*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiGate : public KikiSwitch
{
    public: // ........................................................................ PUBLIC
                        KikiGate	( bool open = false );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiGate * 		kikiObjectToGate ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiGate*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiAtom : public KikiObject
{
    public: // ........................................................................ PUBLIC
    
    void		setValue	( float value );
    float		getValue	() const;
};

// __________________________________________________________________________________________________
%nodefault;

class KikiMovesAtom : public KikiAtom
{
    public: // ........................................................................ PUBLIC
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

// __________________________________________________________________________________________________
/*
%nodefault;

class KikiHealthAtom : public KikiAtom
{
    public: // ........................................................................ PUBLIC
                        KikiHealthAtom	( int neutrons = 9 );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiHealthAtom *	kikiObjectToHealthAtom ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiHealthAtom*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiEnergyAtom : public KikiAtom
{
    public: // ........................................................................ PUBLIC
                        KikiEnergyAtom	( int neutrons = 9 );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiEnergyAtom *	kikiObjectToEnergyAtom ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiEnergyAtom*>(o);
                        }
%}
*/
// __________________________________________________________________________________________________
class KikiValueAtom : public KikiAtom
{
    public: // ........................................................................ PUBLIC
                        KikiValueAtom	( float range_start = 0.0, float range_end = 1.0, 
                                          float start_value = 1.0, int levels = 9 );
                                          
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

// __________________________________________________________________________________________________
%nodefault;

class KikiSpikes : public KikiObject
{
    public: // ........................................................................ PUBLIC
                        KikiSpikes	( int face = KikiFace::PZ );
                        
    static void		setObjectColor	( const char * color_name, const KColor & color );
};

%inline %{
    KikiSpikes *	kikiObjectToSpikes ( KikiObject * o ) 
                        {
                            return reinterpret_cast<KikiSpikes*>(o);
                        }
%}

// __________________________________________________________________________________________________
%nodefault;

class KikiBullet : public KikiObject
{
    public: // ........................................................................ PUBLIC
    
    static void		setObjectColor	( const char * color_name, const KColor & color );
};
