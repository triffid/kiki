/*
 *  KTrash.cpp
 *  kodisein
 */

#include "KTrash.h"
#include "KNotificationObject.h"

#include <algorithm>

std::vector<KObject*> KTrash::trash_can;

// --------------------------------------------------------------------------------------------------------
void KTrash::addObject ( KObject * object ) 
{
    std::vector<KObject*>::iterator result = std::find (KTrash::trash_can.begin(), KTrash::trash_can.end(), object);
    if (result == KTrash::trash_can.end())
    {
        KTrash::trash_can.push_back(object);
    }
}

// --------------------------------------------------------------------------------------------------------
void KTrash::recycle () 
{
    std::vector<KObject*>::iterator iter = KTrash::trash_can.begin();
    if (iter != KTrash::trash_can.end())
    {
        delete (*iter);
        iter++;
    }
    trash_can.clear();
}


