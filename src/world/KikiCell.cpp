/*
 *  KikiCell.cpp
 *  kiki
 */

#include "KikiCell.h"
#include <KConsole.h>

#include <algorithm>

// __________________________________________________________________________________________________
KikiCell::KikiCell ()
{
}

// __________________________________________________________________________________________________
KikiCell::~KikiCell ()
{
    if (objects.empty() == false)
    {
        KConsole::printError("KikiCell::~KikiCell not empty!");
    }
}

// __________________________________________________________________________________________________
KikiObjectList KikiCell::getObjectsOfType ( const KClassId & classId )
{
    KikiObjectList object_list;

    for (KikiObjectIter objectIter = objects.begin(); objectIter != objects.end(); objectIter++)
    {
        if ((*objectIter)->getClassId() >= classId)
        {
            object_list.push_back(*objectIter);
        }
    }
    
    return object_list;
}

// __________________________________________________________________________________________________
KikiObject * KikiCell::getObjectOfType ( const KClassId & classId )
{
    for (KikiObjectIter objectIter = objects.begin(); objectIter != objects.end(); objectIter++)
    {
        if ((*objectIter)->getClassId() >= classId)
        {
            return (*objectIter);
        }
    }
    
    return NULL;
}

// __________________________________________________________________________________________________
KikiObject * KikiCell::getRealObjectOfType	( const KClassId & classId )
{
    for (KikiObjectIter objectIter = objects.begin(); objectIter != objects.end(); objectIter++)
    {
        if ((*objectIter)->getClassId() >= classId)
        {
            return (*objectIter);
        }
        else if ((*objectIter)->getClassId() >= KikiTmpObject::classId())
        {
            KikiObject * realObject = ((KikiTmpObject*)(*objectIter))->object;
            if (realObject->getClassId() >= classId)
            {
                return realObject;
            }
        }
    }

    return NULL;
}

// __________________________________________________________________________________________________
KikiObject * KikiCell::getOccupant ()
{
    for (KikiObjectIter objectIter = objects.begin(); objectIter != objects.end(); objectIter++)
    {
        if ((*objectIter)->isSpaceEgoistic())
        {
            return (*objectIter);
        }
    }
    
    return NULL;
}

// __________________________________________________________________________________________________
void KikiCell::removeObject ( KikiObject * object )
{
    KikiObjectIter result = std::find (objects.begin(), objects.end(), object);
    if (result != objects.end())
    {	
        for (KikiObjectIter iter = objects.begin(); iter != objects.end(); iter++)
        {
            if ((*iter) != object)
            {
                (*iter)->cellMateLeft (object);
            }
        }
        objects.erase(result);
    }
}

// __________________________________________________________________________________________________
void KikiCell::addObject ( KikiObject * object )
{
    if (std::find (objects.begin(), objects.end(), object) == objects.end())
    {
        for (KikiObjectIter iter = objects.begin(); iter != objects.end(); iter++)
        {
            (*iter)->newCellMate(object);
        }
        objects.push_back(object);
    }
}
