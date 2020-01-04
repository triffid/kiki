
// __________________________________________________________________________________________________
%nodefault;

class KikiText
{
    public: // ........................................................................ PUBLIC
    enum 		{ base_color, bright_color, dark_color };
    
                        KikiText	( const std::string & = "", bool center = true, int colorIndex = 0 );
    
    void		setText		( const std::string & str, int colorIndex = base_color );
    std::string 	getText		() const;
    
    void		clear		();
    bool		isEmpty		() const;
    
    virtual void	addText		( const std::string &, float scaleFactor = 1.0 );
                                                    
    const KColor & 	getColor	() const;
    void		setColor	( const KColor & c );
    void		setAlpha	( float alpha );

    bool		isAnimated	() const;
    void		setAnimated	( bool );
    
    bool		isCentered	() const;
    void		setCentered	( bool );
    
    float		getWidth	() const;
    float		getHeight	() const;

    static void		setObjectColor	( const char * color_name, const KColor & color );
};

