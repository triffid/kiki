/*
 *  KikiCellText.h
 *  kiki
 */

#ifndef __KikiCellText
#define __KikiCellText

#include "KikiObject.h"
#include "KikiText.h"

// __________________________________________________________________________________________________
class KikiCellText : public KikiObject, public KikiText
{
    KIKI_OBJECT_HEADER
    
    protected: // ..................................................................... PROTECTED
    
    KVector *	offset;
    float	cell_height;

    public: // ........................................................................ PUBLIC
                KikiCellText	( const std::string & text, float height = 1.0,  
                                  bool center = true, int colorIndex = base_color );
                
    void	setOffset	( const KVector & offset );
    void	display		();
};

#endif

