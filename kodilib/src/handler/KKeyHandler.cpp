/*
 *  KKeyHandler.cpp
 *  kodisein
 */

#include "KKeyHandler.h"

KDL_CLASS_INTROSPECTION_1 (KKeyHandler, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KKeyHandler::KKeyHandler ()
{
    flags.resize(KDL_KEYHANDLER_FLAG_END);
    flags[KDL_KEYHANDLER_FLAG_BLOCKABLE] = true; 	// default behaviour is to be blockable
    flags[KDL_KEYHANDLER_FLAG_HANDLES_RELEASE] = false; // doesn't handle release events by default 
}


