/*
 *  KNotificationObject.cpp
 *  kodisein
 */

#include "KNotificationObject.h"

KDL_CLASS_INTROSPECTION (KObject)
KDL_CLASS_INTROSPECTION (KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KNotificationObject::~KNotificationObject ()
{ 
    removeAllReceivers(); 
}

// --------------------------------------------------------------------------------------------------------
KNamedReceiverCallbacks * KNotificationObject::getOrCreateNamedReceiverCallbacks ( int name )
{
    KNamedReceiverCallbacks * namedReceiverCallbacks = getNamedReceiverCallbacks (name);
    if (namedReceiverCallbacks == NULL)
    { 
        namedReceiverCallbacks = new KNamedReceiverCallbacks(name);
        named_receiver_callbacks.push_back(namedReceiverCallbacks);
    }
    return namedReceiverCallbacks;
}

// --------------------------------------------------------------------------------------------------------
KNamedReceiverCallbacks * KNotificationObject::getNamedReceiverCallbacks ( int name ) const
{
    std::vector<KNamedReceiverCallbacks*>::const_iterator iter = named_receiver_callbacks.begin();
    while (iter != named_receiver_callbacks.end())
    {
        if ((*iter)->name == name)
        {
            return (*iter);
        }
        iter++;
    }
    return NULL;
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::removeReceiverCallback ( KObject * rec, KCallbackPtr cbPtr )
{
    KNamedReceiverCallbacks * namedReceiverCallbacks = 
                                            getNamedReceiverCallbacks(KDL_NOTIFICATION_TYPE_CALLBACK);
    if (namedReceiverCallbacks == NULL) return; // there is no receiver registered for callback
    std::vector<KReceiverCallback*>::iterator iter = namedReceiverCallbacks->receiver_callbacks.begin();
    while (iter != namedReceiverCallbacks->receiver_callbacks.end())
    {
        if ((*iter)->receiver == rec && (*iter)->callback.callback_ptr == cbPtr)
        {
            delete (*iter);
            iter = namedReceiverCallbacks->receiver_callbacks.erase(iter); iter--;
            receivers_removed = true;
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::removeReceiver ( KObject * rec, int name )
{
    KNamedReceiverCallbacks * namedReceiverCallbacks = getNamedReceiverCallbacks(name);
    if (namedReceiverCallbacks == NULL) return;
    std::vector<KReceiverCallback*>::iterator iter = namedReceiverCallbacks->receiver_callbacks.begin();
    while (iter != namedReceiverCallbacks->receiver_callbacks.end())
    {
        if ((*iter)->receiver == rec)
        {
            delete (*iter);
            iter = namedReceiverCallbacks->receiver_callbacks.erase(iter); iter--;
            receivers_removed = true;
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::removeReceiver ( KObject * rec )
{
    std::vector<KNamedReceiverCallbacks*>::iterator iter = named_receiver_callbacks.begin();
    while (iter != named_receiver_callbacks.end())
    {
        removeReceiver(rec, (*iter)->name);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void removeReceiversInReceiverCallbackVector ( std::vector<KReceiverCallback*> * receiverCallbacks )
{
    while (receiverCallbacks->empty() == false)
    {
        delete receiverCallbacks->back();
        receiverCallbacks->pop_back();
    }
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::removeReceivers ( int name )
{
    KNamedReceiverCallbacks * namedReceiverCallbacks = getNamedReceiverCallbacks(name);
    if (namedReceiverCallbacks)
    {
        while (namedReceiverCallbacks->receiver_callbacks.empty() == false)
        {
            delete namedReceiverCallbacks->receiver_callbacks.back();
            namedReceiverCallbacks->receiver_callbacks.pop_back();
            receivers_removed = true;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::removeAllReceivers ()
{
    while (named_receiver_callbacks.empty() == false)
    {
        KNamedReceiverCallbacks * namedReceiverCallbacks = named_receiver_callbacks.back();
        while (namedReceiverCallbacks->receiver_callbacks.empty() == false)
        {
            delete namedReceiverCallbacks->receiver_callbacks.back();
            namedReceiverCallbacks->receiver_callbacks.pop_back();
        }
        delete namedReceiverCallbacks;
        named_receiver_callbacks.pop_back();
        receivers_removed = true;
    }
}

// --------------------------------------------------------------------------------------------------------
// is there any receiver with callback registered?
bool KNotificationObject::hasCallback ( KCallbackPtr callback )
{
    KNamedReceiverCallbacks * namedReceiverCallbacks;
    namedReceiverCallbacks = getNamedReceiverCallbacks(KDL_NOTIFICATION_TYPE_CALLBACK);
    if (namedReceiverCallbacks == NULL) return false;
    std::vector<KReceiverCallback*>::iterator iter = namedReceiverCallbacks->receiver_callbacks.begin();
    while (iter != namedReceiverCallbacks->receiver_callbacks.end())
    {
        if ((*iter)->callback.callback_ptr == callback)
        {
            return true;
        }
        iter++;
    }
    return false;
}

// --------------------------------------------------------------------------------------------------------
// is there any receiver registered?
bool KNotificationObject::hasReceivers () const
{
    for (int index = 0; index < (int)named_receiver_callbacks.size(); index++)
    {
        if (named_receiver_callbacks[index]->receiver_callbacks.size() != 0)
        {
            // found at least one receiver
            return true;
        }
    }
    // found no receiver for no notificationType
    return false;
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

#define ADD_RECEIVER_CALLBACK(cbType, notificationType, cbPtr) \
void KNotificationObject::addReceiverCallback ( KObject * rec, cbType cb, int name ) \
{ \
    KNamedReceiverCallbacks * namedReceiverCallbacks = getOrCreateNamedReceiverCallbacks(name); \
    KReceiverCallback * newReceiverCallback = new KReceiverCallback(notificationType, rec); \
    newReceiverCallback->callback.cbPtr = cb; \
    namedReceiverCallbacks->receiver_callbacks.push_back(newReceiverCallback); \
}

#define SET_PROVIDER_CALLBACK(cbType, notificationType, cbPtr) \
void KNotificationObject::setProviderCallback ( KObject * rec, cbType cb, int name ) \
{ \
    KNamedReceiverCallbacks * namedReceiverCallbacks = getOrCreateNamedReceiverCallbacks(name); \
    KReceiverCallback * newReceiverCallback = new KReceiverCallback(notificationType, rec); \
    newReceiverCallback->callback.cbPtr = cb; \
    namedReceiverCallbacks->receiver_callbacks.clear(); \
    namedReceiverCallbacks->receiver_callbacks.push_back(newReceiverCallback); \
    providerSet(); \
}

#define NOTIFY_RECEIVERS(valueType, notificationType, cbPtr) \
void KNotificationObject::notifyReceivers ( valueType value, int name ) const \
{ \
    KNamedReceiverCallbacks * namedReceiverCallbacks = getNamedReceiverCallbacks(name); \
    if (namedReceiverCallbacks == NULL) return; \
    ((KNotificationObject*)this)->receivers_removed = false; \
    std::vector<KReceiverCallback*>::const_iterator iter = namedReceiverCallbacks->receiver_callbacks.begin(); \
    while (iter != namedReceiverCallbacks->receiver_callbacks.end()) \
    { \
        if ((*iter)->type == notificationType) \
        { \
            (((*iter)->receiver)->*((*iter)->callback.cbPtr))(value); \
        } \
        if (receivers_removed) return; \
        iter++; \
    } \
}

#define RECEIVE_VALUE(valueType, notificationType, cbPtr) \
bool KNotificationObject::receiveValue ( valueType * value, int name ) const \
{ \
    KNamedReceiverCallbacks * namedReceiverCallbacks = getNamedReceiverCallbacks(name); \
    if (namedReceiverCallbacks == NULL) return false; \
    if (namedReceiverCallbacks->receiver_callbacks.empty()) return false; \
    KReceiverCallback * receiverCallback = namedReceiverCallbacks->receiver_callbacks[0]; \
    if (receiverCallback->type != notificationType) return false; \
    *value = ((receiverCallback->receiver)->*(receiverCallback->callback.cbPtr))(); \
    return true; \
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::notifyReceiver ( KReceiverCallback * recCbPtr ) const
{
   ((recCbPtr->receiver)->*(recCbPtr->callback.callback_ptr))(); 
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::notifyReceiversType ( int name ) const
{
    KNamedReceiverCallbacks * namedReceiverCallbacks=getNamedReceiverCallbacks(name);
    if (namedReceiverCallbacks == NULL) return;
    ((KNotificationObject*)this)->receivers_removed = false;
    std::vector<KReceiverCallback*>::iterator iter = namedReceiverCallbacks->receiver_callbacks.begin();
    while (iter != namedReceiverCallbacks->receiver_callbacks.end())
    {
        notifyReceiver(*iter);
        if (receivers_removed) return;
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KNotificationObject::notifyReceivers () const
{
    notifyReceiversType(KDL_NOTIFICATION_TYPE_CALLBACK);
}

ADD_RECEIVER_CALLBACK(KCallbackPtr,  KDL_NOTIFICATION_TYPE_CALLBACK,	callback_ptr)
ADD_RECEIVER_CALLBACK(KSetDataPtr,   KDL_NOTIFICATION_TYPE_SET_DATA,	set_data_ptr)
ADD_RECEIVER_CALLBACK(KSetFloatPtr,  KDL_NOTIFICATION_TYPE_SET_FLOAT,	set_float_ptr)
ADD_RECEIVER_CALLBACK(KSetIntPtr,    KDL_NOTIFICATION_TYPE_SET_INT,	set_int_ptr)
ADD_RECEIVER_CALLBACK(KSetBoolPtr,   KDL_NOTIFICATION_TYPE_SET_BOOL,	set_bool_ptr)
ADD_RECEIVER_CALLBACK(KSetStringPtr, KDL_NOTIFICATION_TYPE_SET_STRING,	set_string_ptr)
ADD_RECEIVER_CALLBACK(KSetSizePtr,   KDL_NOTIFICATION_TYPE_SET_SIZE,	set_size_ptr)

SET_PROVIDER_CALLBACK(KGetDataPtr,   KDL_NOTIFICATION_TYPE_GET_DATA,	get_data_ptr)
SET_PROVIDER_CALLBACK(KGetFloatPtr,  KDL_NOTIFICATION_TYPE_GET_FLOAT,	get_float_ptr)
SET_PROVIDER_CALLBACK(KGetIntPtr,    KDL_NOTIFICATION_TYPE_GET_INT,	get_int_ptr)
SET_PROVIDER_CALLBACK(KGetBoolPtr,   KDL_NOTIFICATION_TYPE_GET_BOOL,	get_bool_ptr)
SET_PROVIDER_CALLBACK(KGetStringPtr, KDL_NOTIFICATION_TYPE_GET_STRING,	get_string_ptr)
SET_PROVIDER_CALLBACK(KGetSizePtr,   KDL_NOTIFICATION_TYPE_GET_SIZE,	get_size_ptr)

NOTIFY_RECEIVERS(void*, 	 KDL_NOTIFICATION_TYPE_SET_DATA,	set_data_ptr)
NOTIFY_RECEIVERS(float, 	 KDL_NOTIFICATION_TYPE_SET_FLOAT,	set_float_ptr)
NOTIFY_RECEIVERS(int, 		 KDL_NOTIFICATION_TYPE_SET_INT, 	set_int_ptr)
NOTIFY_RECEIVERS(bool, 		 KDL_NOTIFICATION_TYPE_SET_BOOL,	set_bool_ptr)
NOTIFY_RECEIVERS(const std::string &, KDL_NOTIFICATION_TYPE_SET_STRING,	set_string_ptr)
NOTIFY_RECEIVERS(const KSize &,  KDL_NOTIFICATION_TYPE_SET_SIZE,	set_size_ptr)

RECEIVE_VALUE(void*, 		KDL_NOTIFICATION_TYPE_GET_DATA,		get_data_ptr)
RECEIVE_VALUE(float, 		KDL_NOTIFICATION_TYPE_GET_FLOAT,	get_float_ptr)
RECEIVE_VALUE(int, 		KDL_NOTIFICATION_TYPE_GET_INT,		get_int_ptr)
RECEIVE_VALUE(bool, 		KDL_NOTIFICATION_TYPE_GET_BOOL,		get_bool_ptr)
RECEIVE_VALUE(std::string, 	KDL_NOTIFICATION_TYPE_GET_STRING,	get_string_ptr)
RECEIVE_VALUE(KSize, 		KDL_NOTIFICATION_TYPE_GET_SIZE,		get_size_ptr)

