/*
 *  KPickHandler.h
 *  kodisein
 */

#ifndef __KPickHandler
#define __KPickHandler

#include "KPickable.h"
#include "KNotificationObject.h"

class KProjection;
class KMouseEvent;

// __________________________________________________________________________________________________

enum {	KDL_PICKHANDLER_FLAG_FOCUS_ON_ENABLED,	
        KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED, 
        KDL_PICKHANDLER_FLAG_DOUBLECLICK_ENABLED, 
        KDL_PICKHANDLER_FLAG_MENU_ENABLED,	
        KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED,
        KDL_PICKHANDLER_FLAG_MOVING_ENABLED, 
        KDL_PICKHANDLER_FLAG_TRANSPARENT_ZERO,
        KDL_PICKHANDLER_FLAG_MOTION_FOCUS,
        KDL_PICKHANDLER_FLAG_END };

// __________________________________________________________________________________________________

class KPickHandler : public KObject
{
    INTROSPECTION

    protected:

    int				last_time;
    PickableVector		pickables;
    KPickable *			picked_pickable;
    KProjection	*		projection;
    KProjection * 		reset_projection;

    void 			initializeIdsInVector 	 ( const PickableVector *, int & ) const;
    const KPickable * 		parentOfPickableInVector ( const KPickable *, const PickableVector * ) const;
    const KPickable *		pickableWithIdInVector	 ( int, const PickableVector * ) const;
    
    public:
    
    std::vector<bool>		flags;
    int				depth;
    
                                KPickHandler		();
    virtual			~KPickHandler		();

            bool		operator <		( const KPickHandler & ph ) { return(depth<ph.depth); }
    
            int			getDepth		() const  { return depth; }
            void		setDepth		( int d ) { depth = d; }

            void		pickPickable		( KPickable * p );
    virtual void		addPickable		( KPickable * p );
    virtual void		removePickable		( KPickable * p );
    virtual void		deletePickable		( KPickable * p );
            void		deleteAllPickables	();
            void		removeAllPickables	();

            void		unpick			();
            void		unpickAll		();
            void		unpickAllInVector	( const PickableVector * );
            
            bool		isPicked		( KPickable * p ) const 
                                                        { return (p == picked_pickable); }
            bool		isPickablePicked	() const 
                                                        { return (picked_pickable); }
            const KPickable *	getPickedPickable	() const { return picked_pickable; }
            void		setResetProjection	();
            const KProjection *	getResetProjection	() const;
    virtual bool		isProjectionEnabled	() const 
                                                        { return flags[KDL_PICKHANDLER_FLAG_PROJECTION_ENABLED]; }
    virtual const KPickable *	getPickableWithId	( int id ) const;
    virtual const KPickable * 	getParentOfPickable	( const KPickable * ) const;
    virtual KProjection *	getProjection		() { return projection; }
    virtual void		setProjection		( const KProjection * );
    
    virtual void		initializeIds		();

    // controller notifications
    virtual bool		pick			( const KMouseEvent & );
    virtual void		release			( const KMouseEvent & );
    virtual bool		mouseMotion		( const KMouseEvent & );
    virtual void		updateProjection	( const KMouseEvent & );
    virtual void		updateProjectionFromEventInMode	( KProjection *, const KMouseEvent &, int );
    virtual void		focusOnPickedPickable	( bool = false ) {}

    virtual void		displayPickables	( int = 0 );
    virtual void		display			( int = 0 );
    virtual void		displayMenu		() {}

    // pickhandler notifications
    virtual bool		shouldPick		( const KPickable * ) { return true; }
    
    virtual void		unpicked		() {}
    virtual void		picked			() {}
    virtual void		doubleClicked		() {}
    virtual void		moved			( const KMouseEvent & ) {}
};

// __________________________________________________________________________________________________

typedef std::vector<KPickHandler*> KPickHandlerList;
typedef KPickHandlerList::iterator  KPickHandlerIter;

#endif



