/*
 *  KikiText.h
 *  kiki
 */

#ifndef __KikiText
#define __KikiText

#include <KColor.h>

#include <string>
#include <vector>

class KikiTextLine;

// __________________________________________________________________________________________________
class KikiText
{
    public: // ........................................................................ PUBLIC
    
    enum 		{ base_color, bright_color, dark_color };

    
    // ........................................................................ (con|de)struction
                        KikiText	( const std::string & text = "", 
                                          bool center = true, 
                                          int color = base_color );
    virtual		~KikiText	();
    
    // ........................................................................ 
    virtual void	setText		( const std::string & str, int colorIndex = base_color );
    std::string		getText		() const;
    virtual void	addText		( const std::string &, float scaleFactor = 1.0 );
    
    void		clear		();
    bool		isEmpty		() const;
    
    const KColor & 	getColor	() const { return color; }
    void		setColor	( const KColor & c ) { color = c; }
    void		setAlpha	( float alpha ) { color.setAlpha(alpha); }
    
    bool		isAnimated	() const { return flags[ANIMATE]; }
    void		setAnimated	( bool b ) { flags[ANIMATE] = b; }
    bool		isCentered	() const { return flags[ALIGN_CENTER]; }
    void		setCentered	( bool b ) { flags[ALIGN_CENTER] = b; }
    
    float		getWidth	() const { return width; }
    float		getHeight	() const { return height; }
    virtual void	display		();
    
    // ........................................................................ static color handling
    static void 	setObjectColor	( const char * color_name, const KColor & color );
    static void		reinit		();
    static void		init		();
    static void		invalidateLists ( int index );

    protected: // ..................................................................... PROTECTED 

    friend class 		KikiCharacter;

    // ........................................................................ colors
    static const char * 	color_names[];
    static std::vector<KColor> 	colors;
    KColor			color;
    
    // ........................................................................ display lists
    static unsigned int		display_lists[3][58];
    static int			list_color;
    // ........................................................................ depth
    static float		bevel_depth;
    
    // ........................................................................ text lines
    std::vector<KikiTextLine*>	text_lines;
    float			width, height;
    float			line_spacing;
    std::vector<bool>		flags;

    enum 			{ ANIMATE, ALIGN_CENTER, FLAGS_END };         
};

#endif

