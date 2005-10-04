/*
 *  KikiMenu.h
 *  kiki
 */

#ifndef __KikiMenu
#define __KikiMenu

#include "KikiScreenText.h"
#include "KikiTextLine.h"

// __________________________________________________________________________________________________
class KikiMenuItem
{
    public:
    
    KikiMenuItem ();
    
    bool ignore;
	bool option;
    KikiTextLine * 	item_text;
    KikiTextLine * 	value_text;
    std::string		event_name;
    
    float	getWidth	() const;
    float	getHeight	() const;
};

// __________________________________________________________________________________________________
class KikiMenu : public KikiScreenText
{
    public: // ........................................................................ PUBLIC
    
    // ........................................................................ (con|de)struction
                KikiMenu	( int selectedItem = -1 );
    
    // ........................................................................ menu items
    virtual void addItem	( const std::string & itemText, KikiAction * action = 0 );    
	virtual void addOption	( const std::string & itemText, KikiAction * action = 0 );    

    // ........................................................................ 
    void	display		();
    void	performAction	( KikiAction * action );
    void	actionFinished	( KikiAction * action );
    bool	handleKey	( const KKey & key );
    void	setEscapeActive ( bool active = true ) { escape_active = active; }

    protected: // ..................................................................... PROTECTED
    
    int				active_index;
    int				index_offset;
    std::vector<KikiMenuItem*>	menu_items;
    bool			escape_active;

    KikiMenuItem * newItem	( const std::string & itemText, KikiAction * action = 0 );
    virtual void nextItem	();
    virtual void previousItem	();
    virtual void alignItems	();
};

#endif

