/*
 *  KikiActionObject.h
 *  kiki
 */

#ifndef __KikiActionObject
#define __KikiActionObject

#include "KikiAction.h"
#include "KikiEvent.h"

#include <KIntrospection.h>

// __________________________________________________________________________________________________
class KikiActionObject
{
    public: // ........................................................................ PUBLIC
    
                        KikiActionObject	() {}
    virtual             ~KikiActionObject	();
    
    virtual void	initAction		( KikiAction * action ) {}
    virtual void	performAction		( KikiAction * action ) {}
    virtual void	finishAction		( KikiAction * action ) {}
    virtual void	actionFinished		( KikiAction * action ) {}
    
    void		startTimer		( int duration, int mode = KikiAction::ONCE );
    void		addAction		( KikiAction * action );
    void		startTimedAction	( KikiAction * action, int duration = -1 );
    void		stopAction		( KikiAction * action );
    void		removeAction		( KikiAction * action );
    KikiAction *	getActionWithName	( const std::string & name );
    KikiAction *	getActionWithId		( int actionId );
    
    int			addEventWithName	( const std::string & name );    
    KikiEvent *		getEventWithName	( const std::string & name );
    KikiEvent *		getEventWithId		( int eventId );
    
    INTROSPECTION

    protected: // ..................................................................... PROTECTED
    
    KikiActionList	actions;
    KikiEventList	events;
    
    void 		deleteActions	();
};

#endif
