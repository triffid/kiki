/*
 *  KikiPageText.h
 *  kiki
 */

#ifndef __KikiPageText
#define __KikiPageText

#include "KikiScreenText.h"

// __________________________________________________________________________________________________
class KikiPageText : public KikiScreenText
{
    public: // ........................................................................ PUBLIC
    
    // ........................................................................ (con|de)struction
                KikiPageText	( const std::string & pageText, 
                                    bool nextPage, bool previousPage = false );
    
    // ........................................................................ 
    void	display		();
    void	actionFinished	( KikiAction * action );
    bool	handleKey	( const KKey & key );
    
    protected: // ..................................................................... PROTECTED
    
        enum {		ACTION_NEXT_PAGE = KikiScreenText::ACTION_END,
                        ACTION_PREVIOUS_PAGE,
                        ACTINO_END };
};

#endif

