/*
 *  KikiCharacter.h
 *  kiki
 */

#ifndef __KikiCharacter
#define __KikiCharacter

#include <KVector.h>

// __________________________________________________________________________________________________
class KikiCharacter
{
    protected: // ..................................................................... PROTECTED
    
    char		character;
    char		addon;
    KVector		position;

    public: // ........................................................................ PUBLIC
    
                        KikiCharacter	( char );
    
    virtual void 	display 	();
    virtual void	render	 	();
    virtual void	renderAddon	();
    virtual void	renderCharacter	( char );
    
    char		getCharacter	() const { return character + 33; }
    void		setPosition	( const KVector & pos ) { position = pos; }
    
    virtual float	getWidth	() const;
};

#endif
