/*
 *  KMenuItem.h
 *  kodisein
 */

#ifndef __KMenuItem
#define __KMenuItem

#include "KButton.h"

class KMenuItem : public KButton
{
    INTROSPECTION
    
    protected:
    
    std::string 			shortcut;

    public:	
                                KMenuItem 	 	( const std::string &, const std::string & = "" );
         
    virtual void		setShortcut	 	( const std::string & );
    virtual std::string		getShortcut	 	() const { return shortcut; }
    virtual void        	setPicked 	 	( bool );
    virtual void		activate	 	();
    virtual void		activateItem	 	();
    virtual void		deactivate	 	();
    virtual void		highlight	 	();
    virtual void		render		 	();
    virtual void		renderShortCut	 	();

    virtual std::string		getText			() const;
    virtual KSize		getSize 		() const;
    virtual void		setXMLAttributes	( const std::string & );
    virtual std::string		getXMLAttributes	() const;
    virtual void		setXML			( std::string & );
    virtual std::string		getXML 			( int = 0 ) const;
};

#endif
