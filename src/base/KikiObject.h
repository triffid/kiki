/*
 *  KikiObject.h
 *  kiki
 */

#ifndef __KikiObject
#define __KikiObject

#include "KikiObjectHeader.h"
#include "KikiActionObject.h"
#include "KikiFace.h"
#include "KikiPos.h"

#include <KNotificationObject.h>
#include <KPickable.h>
#include <KIntrospection.h>
#include <KVector.h>
#include <KQuaternion.h>

#ifndef WIN32
#define RANDOM 		((float)random()/RAND_MAX)
#else
#pragma warning		( disable : 4800 4305 4267 ) // Disable warnings
#define RANDOM		((float)rand()/RAND_MAX)
#endif

enum { KIKI_NOTIFICATION_OBJECT_DELETED = KDL_NOTIFICATION_TYPE_NOTIFICATION_END };

// __________________________________________________________________________________________________

class KikiObject : public KObject, public KikiActionObject, public KNotificationObject, public KPickable
{
    public: // ........................................................................ PUBLIC
    
                        KikiObject	();
    virtual             ~KikiObject	();
    
    virtual void	initAction		( KikiAction * action ) {}
    virtual void	performAction		( KikiAction * action ) {}
    virtual void	finishAction		( KikiAction * action ) {}
    virtual void	actionFinished		( KikiAction * action ) {}
    
    virtual void	newCellMate		( KikiObject * object ) {}
    virtual void	cellMateLeft		( KikiObject * object ) {}
    virtual void	bulletImpact		() {}
    
    virtual void	preDisplay		();
    virtual void	display			();
    virtual void	postDisplay		();
    
    virtual void	render 			() {}

    KikiPos		getPos			() const { return current_position; }
    virtual void	setPosition		( const KVector & pos ) { position = current_position = pos; }
    virtual void	setCurrentPosition	( const KVector & pos ) { current_position = pos; }
    KVector		getPosition		() const { return position; }
    
    void		setOrientation		( const KQuaternion & q ) 
                                                { 
                                                    orientation = q; current_orientation = q; 
                                                }
                                                
    void		setName			( const std::string & n ) 
                                                { 
                                                    if (name) *name = n; else name = new std::string(n); 
                                                }
    std::string		getName			() const { if (name) return *name; else return "noname"; }
    
    KQuaternion		getOrientation		() const { return orientation; }
    void		setCurrentOrientation	( const KQuaternion & q ) { current_orientation = q; }
    KQuaternion		getCurrentOrientation	() const { return current_orientation; }

    protected: // ..................................................................... PROTECTED

    KIKI_OBJECT_HEADER

    friend class 	KikiWorld;

    KikiAction * 	move_action;
    
    std::string * 	name;

    KVector		direction;		// push/fall,spikes,bullet
    KVector		position;
    KVector		current_position;
    KQuaternion		orientation;
    KQuaternion		current_orientation;
};

// __________________________________________________________________________________________________
class KikiTmpObject : public KikiObject
{
    KIKI_OBJECT_HEADER

    public: 
     
    KikiObject * object;
    int		time;
   
                KikiTmpObject	( KikiObject * o ) : KikiObject() { object = o; }
    void 	render		();
};

// __________________________________________________________________________________________________

typedef std::vector<KikiObject*>	KikiObjectList;
typedef KikiObjectList::iterator  	KikiObjectIter;

#endif

