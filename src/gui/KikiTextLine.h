/*
 *  KikiTextLine.h
 *  kiki
 */

#ifndef __KikiTextLine
#define __KikiTextLine

#include <KMatrix.h>
#include <vector>

class KikiCharacter;

// __________________________________________________________________________________________________
class KikiTextLine
{
    protected: // ..................................................................... PROTECTED
    
    KMatrix			matrix;
    std::vector<KikiCharacter*> characters;
    std::string			text;
    float			width;
    float			scale_factor;

    void 		addCharacter	( char );
    
    public: // ........................................................................ PUBLIC

    float		space_width;
    float		character_spacing;
    
                        KikiTextLine 	(   const std::string & str = "", float scaleFactor = 1.0 );
                        ~KikiTextLine 	();

    void 		setText		( const std::string & str );
    std::string 	getText		() const { return text; }
    
    void		setPosition	( const KVector & v ) { matrix.setPosition(v); }
    float 		getWidth	() const { return width * scale_factor; }
    float 		getHeight	() const { return 8.0 * scale_factor; }
    void		setScaleFactor  ( float scaleFactor ) { scale_factor = scaleFactor; }
    float		getScaleFactor  () const { return scale_factor; }
    void		display		();
};

#endif


