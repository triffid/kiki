/*
 *  KSubMenuItem.h
 *  kodisein
 */

#ifndef __KSubMenuItem
#define __KSubMenuItem

#include "KMenuItem.h"
#include "KMenu.h"

class KSubMenuItem : public KMenuItem
{
    INTROSPECTION
    
    protected:
    
    KMenu *				child_menu;

    public:

                                        KSubMenuItem		( const std::string &, KMenu * );
                                        
    virtual void			render			();
    virtual void			setParent		( KWidget * );
    virtual KMenu *			getChildMenu 		() const { return child_menu; }
    virtual void			setChildMenu 		( KMenu * menu ) { child_menu = menu; }
    virtual void			deactivate 		();
    virtual KSize			getSize			() const;
    virtual KSize			layout			() { child_menu->layout(); return getSize(); }

    virtual bool			hasSubPickables		() const { return true; }
    virtual const PickableVector *	getSubPickables		() const { return child_menu->getChildren(); }

    virtual void			setXML			( std::string & );
    virtual std::string			getXML 			( int = 0 ) const;
};

#endif
