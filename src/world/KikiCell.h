/*
 *  KikiCell.h
 *  kiki
 */

#ifndef __KikiCell
#define __KikiCell

#include "KikiObject.h"

// __________________________________________________________________________________________________
class KikiCell
{
    friend class 	KikiWorld;

    protected: // ..................................................................... PROTECTED
    
    KikiObjectList	objects;
    
                        KikiCell		();
                        ~KikiCell		();
    
    public: // ........................................................................ PUBLIC
    
    void		removeObject		( KikiObject * object );
    void		addObject		( KikiObject * object );
    KikiObject * 	getOccupant		();
    KikiObject *	getObjectOfType		( const KClassId & );
    KikiObjectList	getObjectsOfType	( const KClassId & );    
    KikiObject *	getRealObjectOfType	( const KClassId & );
    bool		isEmpty			() const { return objects.empty(); }
};

// __________________________________________________________________________________________________

typedef std::vector<KikiCell*> KikiCellList;

#endif

