/*
 *  KKeyActionHandler.h
 *  kodisein
 */

#ifndef __KKeyActionHandler
#define __KKeyActionHandler

#include "KKeyHandler.h"
#include "KStringTools.h"

#include <map>

// --------------------------------------------------------------------------------------------------------
class KKeyAction : public KNotificationObject
{
    protected:
    
    std::string			key_name;
    
    public:
    
                                KKeyAction	( const std::string & keyName )
                                                : KNotificationObject ()
                                                { key_name = keyName; }
    virtual                    ~KKeyAction	() {}
                               
    virtual const std::string &	getKeyName	() const { return key_name; }
};

typedef std::map<const char *, KKeyAction *, ltstr> KeyActionHash;

// --------------------------------------------------------------------------------------------------------
class KKeyActionHandler : public KKeyHandler
{
    INTROSPECTION

    protected:

    KeyActionHash	key_handlers;
    std::string		last_key;

    public:
    
                        KKeyActionHandler	() : KKeyHandler () {}
    virtual		~KKeyActionHandler	();

    KKeyAction *	getActionForSequence	( const std::string &, bool = false );
    bool		addSequenceCallback	( const std::string, KObject *, KCallbackPtr );
    bool		setSequenceCallback	( const std::string, KObject *, KCallbackPtr );
    void		removeSequenceCallback	( const std::string, KObject *, KCallbackPtr );

    bool		isSaveSequenceCallback	( const std::string & );

    bool		handleKey	 	( const KKey & );
};

#endif

