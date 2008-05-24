/*
 *  KPickable.h
 *  kodisein
 */

#ifndef __KPickable
#define __KPickable

#include "KIntrospection.h"
#include <vector>
#include <limits.h>

#define DEBUG_PICKING		false

class KPickable;

typedef std::vector<KPickable*>  PickableVector;
typedef PickableVector::iterator PickableIter;

class KPickable
{
    INTROSPECTION
    
    protected:
    
    bool				picked;
    int					pickable_id;
    
    void				loadId			();
    void				unloadId		();

    public:
                                        KPickable		();
    virtual                     	~KPickable		() {}
    
    virtual void			display			( int ) {}
    
    virtual int				getId 			() const  { return pickable_id; }
    virtual void			setId			( int i ) { pickable_id = i; };
    virtual void			setPicked		( bool p ) { picked = p; }
    virtual bool			isPicked		() const  { return picked; }
        
    virtual bool			hasSubPickables		() const { return false; }
    virtual const PickableVector *	getSubPickables		() const { return NULL; }
    virtual void			setMinId		( int )  {}
    virtual void			setMaxId		( int )  {}
    virtual int				getMinId		() { return -INT_MAX; }
    virtual int				getMaxId		() { return  INT_MAX; }
};

#endif



