/*
 *  KMessagePanel.h
 *  kodisein
 */

#ifndef __KMessagePanel
#define __KMessagePanel

#include "KWindow.h"

class KMessagePanel : public KWindow
{
    public:
                        KMessagePanel 	( const std::string & title, const std::string & message );
    static void 	displayMessage	( const std::string & title, const std::string & message );
    void		close		();
};

#endif
