/*
 *  KSelectionHandler.h
 *  kodisein
 */

#ifndef __KSelectionHandler
#define __KSelectionHandler

#include "KPickHandler.h"

class KSelectable;

class KSelectionHandler : public KPickHandler
{
    INTROSPECTION

    private:
    
    std::vector<std::string>	paste_buffer;
    void			clearPasteBuffer	();

    protected:

    std::vector<KSelectable *> 	selected_selectables;

    public:
                                KSelectionHandler	();
                        
    void 			unselectAllInVector 	( const PickableVector * );
    void			unselect		( KSelectable * );
    void			unselectAll		();    
    bool			isSelected		( KSelectable * );

    virtual void		removePickable		( KPickable * );
    virtual void		select			( KSelectable * );
    
    virtual void		cut			();
    virtual void		copy			();
    virtual void		paste			();
    
    // pickhandler notifications
    virtual void		unpicked		();
    virtual void		picked			();

    // selectionhandler notification
    virtual void		pasted			( const std::string &  ) {}
};

#endif

