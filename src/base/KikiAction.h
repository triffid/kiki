/*
 *  KikiAction.h
 *  kiki
 */

#ifndef __KikiAction
#define __KikiAction

#include <vector>
#include <string>

class KikiActionObject;
class KikiEvent;

// --------------------------------------------------------------------------------------------------------
class KikiAction
{
    public: // ........................................................................ PUBLIC

    enum {              ONCE, 
                        CONTINUOUS,
                        REPEAT };

                        KikiAction 		( KikiActionObject * object, 
                                                    int id, 
                                                    const std::string & name, 
                                                    int _duration = 0, 
                                                    int _mode = KikiAction::ONCE );
                        KikiAction 		( KikiActionObject * object, 
                                                    int id = 0, 
                                                    int _mode = KikiAction::ONCE );
    virtual		~KikiAction		();
    
    virtual void	init			();
    virtual void	perform			();
    virtual void	finish			();
    virtual void	finished		();

    void		performWithEvent	( KikiEvent & event );

    int		 	getId	 		() const { return action_id; }
    const std::string & getName 		() const { return action_name; }
    KikiActionObject * 	getObject		() { return action_object; }
    
    float		getRelativeTime		();
    float		getRelativeDelta	() { return (current-last)/(float)getDuration(); }
    
    void		takeRest		( KikiAction * );
    void		keepRest		();
    void		reset			();
    
    unsigned int	getStart		() const { return start; }
    int			getDuration		() const;
    void		setDuration		( int d ) { duration = d; }

    protected: // ..................................................................... PROTECTED

    friend class 	KikiEvent;
    
    int			action_id;
    std::string 	action_name;
    KikiActionObject * 	action_object;

    unsigned int 	start;
    int			rest;
    int			current;
    int			last;
    int			duration;
    int			mode;
    KikiEvent * event;
    bool      * delete_flag_ptr;
};

// __________________________________________________________________________________________________
typedef std::vector<KikiAction*>	KikiActionList;
typedef KikiActionList::iterator	KikiActionIter;

#endif

