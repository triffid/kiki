/*
 *  KKeyHandler.h
 *  kodisein
 */

#ifndef __KKeyHandler
#define __KKeyHandler

#include "KNotificationObject.h"
#include <vector>

struct KKey;

// --------------------------------------------------------------------------------------------------------

enum { 	KDL_KEYHANDLER_FLAG_BLOCKABLE,
        KDL_KEYHANDLER_FLAG_HANDLES_RELEASE,
        KDL_KEYHANDLER_FLAG_END };

// --------------------------------------------------------------------------------------------------------

class KKeyHandler : public KNotificationObject
{
    INTROSPECTION

    public:

    std::vector<bool>	flags;
    
                        KKeyHandler		();

    virtual bool	handleKey		( const KKey & ) = 0;
    virtual bool	handleKeyRelease	( const KKey & ) { return false; }
};

// --------------------------------------------------------------------------------------------------------

typedef std::vector<KKeyHandler*> KKeyHandlerList;
typedef KKeyHandlerList::iterator KKeyHandlerIter;

#endif


