/*
 *  KIntrospection.cpp
 *  kodisein
 */

#include "KIntrospection.h"

// --------------------------------------------------------------------------------------------------------
bool KClassInfo::canCastTo( const KClassInfo * cip ) const
{
    if (sameClass(cip)) return true;
    return (hasBase(cip));
}

// --------------------------------------------------------------------------------------------------------
bool KClassInfo::hasBase ( const KClassInfo * cip ) const
{
    KClassInfo ** b = (KClassInfo **)bases; if (!b) return false;
    for (KClassInfo * p = *b; p != 0; p = *(++b))
    {
        if (p->sameClass(cip)) return true;
        if (p->hasBase(cip)) return true;
    }
    return false;
}

// --------------------------------------------------------------------------------------------------------
bool KClassInfo::hasDirectBase ( const KClassInfo * cip ) const
{
    KClassInfo ** b = (KClassInfo **)bases; if (!b) return false;
    for (KClassInfo * p = *b; p != 0; p = *(++b))
    {
        if (p->sameClass(cip)) return true;
    }
    return false;
}

// --------------------------------------------------------------------------------------------------------
void KClassInfo::getHierarchy ( std::string & hierarchy ) const
{
    KClassInfo ** b = (KClassInfo **)bases;
    
    hierarchy += "[";
    hierarchy += getName();
    hierarchy + " ";
    
    if (!b) 
    {
        hierarchy += "]";
        return;
    }
     
    for (KClassInfo * p = *b; p != 0; p = *(++b))
    {
       hierarchy +=  "->";
       p->getHierarchy(hierarchy);
    }
    
    hierarchy += "]";
}


