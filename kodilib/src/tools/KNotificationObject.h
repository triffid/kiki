/*
 *  KNotificationObject.h
 *  kodisein
 */

#ifndef __KNotificationObject
#define __KNotificationObject

#include "KIntrospection.h"
#include "KVector.h"

#include <string>

#define DEBUG_NOTIFICATION	false

// --------------------------------------------------------------------------------------------------------
class KObject
{
    INTROSPECTION
};

// --------------------------------------------------------------------------------------------------------
typedef void 	 (KObject::*KCallbackPtr)	();
typedef void	 (KObject::*KSetDataPtr)	(void*);
typedef void	 (KObject::*KSetFloatPtr)	(float);
typedef void	 (KObject::*KSetIntPtr)		(int);
typedef void	 (KObject::*KSetBoolPtr)	(bool);
typedef void	 (KObject::*KSetStringPtr)	(const std::string &);
typedef void	 (KObject::*KSetSizePtr)	(const KSize &);
typedef void *	 (KObject::*KGetDataPtr)	();
typedef float    (KObject::*KGetFloatPtr)	();
typedef int	 (KObject::*KGetIntPtr)		();
typedef bool	 (KObject::*KGetBoolPtr)	() const;
typedef std::string (KObject::*KGetStringPtr)	();
typedef KSize	 (KObject::*KGetSizePtr)	();

enum {	KDL_NOTIFICATION_TYPE_CALLBACK, 
        KDL_NOTIFICATION_TYPE_SET_DATA, 	KDL_NOTIFICATION_TYPE_GET_DATA,
        KDL_NOTIFICATION_TYPE_SET_FLOAT, 	KDL_NOTIFICATION_TYPE_GET_FLOAT,
        KDL_NOTIFICATION_TYPE_SET_INT,		KDL_NOTIFICATION_TYPE_GET_INT,
        KDL_NOTIFICATION_TYPE_SET_BOOL, 	KDL_NOTIFICATION_TYPE_GET_BOOL,
        KDL_NOTIFICATION_TYPE_SET_STRING, 	KDL_NOTIFICATION_TYPE_GET_STRING,
        KDL_NOTIFICATION_TYPE_SET_SIZE, 	KDL_NOTIFICATION_TYPE_GET_SIZE,
        KDL_NOTIFICATION_TYPE_NOTIFICATION_END };
      
// --------------------------------------------------------------------------------------------------------
union KCallback
{
    KCallbackPtr	callback_ptr;
    KSetDataPtr		set_data_ptr;
    KSetFloatPtr	set_float_ptr;
    KSetIntPtr		set_int_ptr;
    KSetBoolPtr		set_bool_ptr;
    KSetStringPtr	set_string_ptr;
    KSetSizePtr		set_size_ptr;
    KGetDataPtr		get_data_ptr;
    KGetFloatPtr	get_float_ptr;
    KGetIntPtr		get_int_ptr;
    KGetBoolPtr		get_bool_ptr;
    KGetStringPtr	get_string_ptr;
    KGetSizePtr		get_size_ptr;
};     

// --------------------------------------------------------------------------------------------------------
struct KReceiverCallback
{
    int				type;
    KObject *			receiver;
    KCallback			callback;
    
                                KReceiverCallback ( int t, KObject * r ) { type = t; receiver = r; }
                                ~KReceiverCallback() { type=0; receiver=NULL; callback.callback_ptr=NULL; }
};

// --------------------------------------------------------------------------------------------------------
struct KNamedReceiverCallbacks
{
    int	name;
    std::vector<KReceiverCallback*> receiver_callbacks;
    
                                KNamedReceiverCallbacks ( int n ) { name=n; }
};

// --------------------------------------------------------------------------------------------------------
class KNotificationObject
{
    INTROSPECTION
    
    protected:
    
    std::vector<KNamedReceiverCallbacks*> named_receiver_callbacks;
    
    KNamedReceiverCallbacks * getOrCreateNamedReceiverCallbacks ( int );
    KNamedReceiverCallbacks * getNamedReceiverCallbacks		( int ) const;
    virtual void 	      notifyReceiver 			( KReceiverCallback * ) const;
    
    bool	receivers_removed;
    
    public:
           
                KNotificationObject () {}
    virtual    ~KNotificationObject ();
                                                                          
    void addReceiverCallback 	( KObject *, KCallbackPtr, 	int = KDL_NOTIFICATION_TYPE_CALLBACK);
    void addReceiverCallback 	( KObject *, KSetDataPtr, 	int = KDL_NOTIFICATION_TYPE_SET_DATA);
    void addReceiverCallback 	( KObject *, KSetFloatPtr, 	int = KDL_NOTIFICATION_TYPE_SET_FLOAT);
    void addReceiverCallback 	( KObject *, KSetIntPtr,   	int = KDL_NOTIFICATION_TYPE_SET_INT);
    void addReceiverCallback 	( KObject *, KSetBoolPtr,   	int = KDL_NOTIFICATION_TYPE_SET_BOOL);
    void addReceiverCallback 	( KObject *, KSetStringPtr, 	int = KDL_NOTIFICATION_TYPE_SET_STRING);
    void addReceiverCallback 	( KObject *, KSetSizePtr, 	int = KDL_NOTIFICATION_TYPE_SET_SIZE);
    void setProviderCallback 	( KObject *, KGetDataPtr, 	int = KDL_NOTIFICATION_TYPE_GET_DATA);
    void setProviderCallback 	( KObject *, KGetFloatPtr, 	int = KDL_NOTIFICATION_TYPE_GET_FLOAT);
    void setProviderCallback 	( KObject *, KGetIntPtr,   	int = KDL_NOTIFICATION_TYPE_GET_INT);
    void setProviderCallback 	( KObject *, KGetBoolPtr,   	int = KDL_NOTIFICATION_TYPE_GET_BOOL);
    void setProviderCallback 	( KObject *, KGetStringPtr, 	int = KDL_NOTIFICATION_TYPE_GET_STRING);
    void setProviderCallback 	( KObject *, KGetSizePtr, 	int = KDL_NOTIFICATION_TYPE_GET_SIZE);
    void removeReceiver	     	( KObject *, 			int);
    void removeReceiver	     	( KObject * );
    void removeReceivers     	(				int);
    void removeAllReceivers  	();
    void removeReceiverCallback ( KObject *, KCallbackPtr );
    
    virtual void providerSet	() {}
    bool hasCallback	     	( KCallbackPtr );
    
    void	notifyReceiversType (				int = KDL_NOTIFICATION_TYPE_CALLBACK ) 	const;
    void	notifyReceivers () 									const;
    void	notifyReceivers ( void *,			int = KDL_NOTIFICATION_TYPE_SET_DATA )	const;
    void	notifyReceivers ( float,			int = KDL_NOTIFICATION_TYPE_SET_FLOAT )	const;
    void	notifyReceivers ( int,				int = KDL_NOTIFICATION_TYPE_SET_INT )	const;
    void	notifyReceivers ( bool,				int = KDL_NOTIFICATION_TYPE_SET_BOOL )	const;
    void	notifyReceivers ( const std::string &,		int = KDL_NOTIFICATION_TYPE_SET_STRING ) const;
    void	notifyReceivers ( const KSize &,		int = KDL_NOTIFICATION_TYPE_SET_SIZE )	const;
    bool	receiveValue   	( void **, 			int = KDL_NOTIFICATION_TYPE_GET_DATA )  const;
    bool	receiveValue   	( float *, 			int = KDL_NOTIFICATION_TYPE_GET_FLOAT ) const;
    bool	receiveValue    ( int *, 			int = KDL_NOTIFICATION_TYPE_GET_INT ) const;
    bool	receiveValue    ( bool *, 			int = KDL_NOTIFICATION_TYPE_GET_BOOL ) const;
    bool	receiveValue    ( std::string *, 		int = KDL_NOTIFICATION_TYPE_GET_STRING ) const;
    bool	receiveValue    ( KSize *, 			int = KDL_NOTIFICATION_TYPE_GET_SIZE ) 	const;
    bool	hasReceivers	() const;
};

#endif


