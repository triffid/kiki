/*
 *  KStatusMenuItem.h
 *  kodisein
 */

#ifndef __KStatusMenuItem
#define __KStatusMenuItem

#include "KMenuItem.h"

class KStatusMenuItem : public KMenuItem
{
    INTROSPECTION
    
    protected:
    
    std::string 		true_text;
    std::string 		false_text;
    
    public:
    
                        KStatusMenuItem 	( const std::string & , const std::string &, const std::string & = "" );
                
    void		setState		( bool );
    bool		getState 		() const;
    void		activateItem		();
    void		render			();
    const std::string &	getTrueText		() const { return true_text; }

    void		setXMLAttributes	( const std::string & );
    std::string		getXMLAttributes	() const;
};

#endif


