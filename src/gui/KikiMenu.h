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
	KikiTextLine *  extra_text;
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
    virtual void addItem	( const std::string & itemText, KikiAction * action = 0, bool option = false);
	virtual KikiMenuItem * currentItem ();
	virtual void setCurrentIndex (int index);

    // ........................................................................ 
    void	display		();
    void	performAction	( KikiAction * action );
    void	actionFinished	( KikiAction * action );
    virtual bool	handleKey	( const KKey & key );
    void	setEscapeActive ( bool active = true ) { escape_active = active; }
    virtual void alignItems	();

	bool    circular; 

    protected: // ..................................................................... PROTECTED
    
    int				index_offset;
	int				active_index;
    std::vector<KikiMenuItem*>	menu_items;
    bool			escape_active;

    KikiMenuItem * newItem	( const std::string & itemText, KikiAction * action = 0 );
    virtual void nextItem	();
    virtual void previousItem	();
};

#endif

