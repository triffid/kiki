/*
 *  KikiEvent.h
 *  kiki
 */

#ifndef __KikiEvent
#define __KikiEvent

#include "KikiAction.h"

// --------------------------------------------------------------------------------------------------------
class KikiEvent
{
    public: // ........................................................................ PUBLIC

                        KikiEvent		( KikiActionObject *, const std::string & name );
                        ~KikiEvent		();
    
    bool		hasAction		( KikiAction * action );
    void		addAction		( KikiAction * action );
    void		removeAction		( KikiAction * action );
    void		removeAllActions	();
    void		removeActionWithName	( const std::string & actionName );
    void		removeActionsOfObject	( KikiActionObject * object );
    KikiActionList	getActionsOfObject	( KikiActionObject * object );
    void		addFinishedAction	( KikiAction * action );

    const std::string & getName 		() const { return event_name; }
    
    void		triggerActions		();
    void		finishActions		();
    
    unsigned int	getTime			() const { return time; }

    KikiActionList	save_actions;

    protected: // ..................................................................... PROTECTED

    std::string 	event_name;
    KikiActionObject * 	event_object;
    
    KikiActionList	actions;
    KikiActionList	finished_actions;
    
    unsigned int    	time;
};

// --------------------------------------------------------------------------------------------------------
typedef std::vector<KikiEvent*>		KikiEventList;
typedef KikiEventList::iterator		KikiEventIter;

#endif

