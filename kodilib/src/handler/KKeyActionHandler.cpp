/*
 *  KKeyActionHandler.cpp
 *  kodisein
 */

#include "KKeyActionHandler.h"
#include "KConsole.h"
#include "KKey.h"

KDL_CLASS_INTROSPECTION_1	(KKeyActionHandler, KKeyHandler)

// --------------------------------------------------------------------------------------------------------
KKeyActionHandler::~KKeyActionHandler ()
{
    for (KeyActionHash::iterator iter = key_handlers.begin(); iter != key_handlers.end(); iter++)
    {
        delete iter->second;
    }
    key_handlers.clear();
}

// --------------------------------------------------------------------------------------------------------
KKeyAction * KKeyActionHandler::getActionForSequence ( const std::string & sequence, bool create )
{
    KKeyAction * keyHandler = NULL;
    KeyActionHash::iterator result = key_handlers.find(sequence.c_str());
    
    if (result != key_handlers.end())
    {
        keyHandler = (*result).second;
    }
    else if (create)
    {
        keyHandler = new KKeyAction(sequence);
        key_handlers[sequence.c_str()] = keyHandler;
    }
    
    return keyHandler;
}

// --------------------------------------------------------------------------------------------------------
bool KKeyActionHandler::isSaveSequenceCallback (const std::string & sequence)
{
    // returns false if there is already an action defined for any prefix of the sequence
    // or the sequence itself.
    std::vector<std::string> sequenceKeys = kStringGetComponents(sequence, " ");
    std::string checkKey;
    for (int index = 0; index < (int)sequenceKeys.size(); index++)
    {	
        kStringMerge(checkKey, sequenceKeys[index], " ");
        KKeyAction * action = getActionForSequence(checkKey);
        if (action)
        {
            // we found an action, check, if it's empty
            if (action->hasReceivers() != false)
            {
                return false;
            }
        }
    }
    // no action found for the sequence or any prefix of it ... it's save
    return true;
}

// --------------------------------------------------------------------------------------------------------
bool KKeyActionHandler::setSequenceCallback ( const std::string sequence, KObject * rec, KCallbackPtr cb )
{
    if (sequence == "") return false;

    if (!isSaveSequenceCallback(sequence))
    {
        std::string errorMessage;
        errorMessage = kStringPrintf
            ("There is already an action bound\nto the key sequence %s (or any prefix of it)",
             sequence.c_str());
        KConsole::printError(errorMessage, true);
        return false;
    }

    getActionForSequence(sequence, true)->addReceiverCallback(rec, cb);
    return true;
}    

// --------------------------------------------------------------------------------------------------------
bool KKeyActionHandler::addSequenceCallback ( const std::string sequence, KObject * rec, KCallbackPtr cb )
{
    if (sequence == "") return false;
    
    getActionForSequence(sequence, true)->addReceiverCallback(rec, cb);
    return true;
}

// --------------------------------------------------------------------------------------------------------
void KKeyActionHandler::removeSequenceCallback ( const std::string sequence, KObject * rec, KCallbackPtr cb )
{
    if (sequence == "") return;
    KKeyAction * keyHandler = getActionForSequence(sequence);
    if (keyHandler) 
    {	
        keyHandler->removeReceiverCallback(rec, cb);
        if (keyHandler->hasReceivers() == false)
        {
            key_handlers.erase(sequence.c_str());
            delete keyHandler;
        }
    }
}

// --------------------------------------------------------------------------------------------------------
bool KKeyActionHandler::handleKey ( const KKey & key )
{
    KKeyAction * keyHandler = getActionForSequence(last_key + " " + key.name);
 
    if (keyHandler)
    {
        keyHandler->notifyReceivers();
        last_key = ""; // sequence matched -> start new one
        return true;
    }
    else
    {
        keyHandler = getActionForSequence(key.name);    
        if (keyHandler)
        {
            keyHandler->notifyReceivers(); // key matched
            return true;
        }
    }
    
    last_key = key.name; // nothing matched
    return false;
}


