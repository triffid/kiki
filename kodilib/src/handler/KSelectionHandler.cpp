/*
 *  KSelectionHandler.cpp
 *  kodisein
 */

#include "KSelectionHandler.h"
#include "KSelectable.h"
#include "KConsole.h"

#include <algorithm>
#include <SDL.h>

KDL_CLASS_INTROSPECTION_1 (KSelectionHandler, KPickHandler)

// --------------------------------------------------------------------------------------------------------
KSelectionHandler::KSelectionHandler () : KPickHandler ()
{
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::removePickable( KPickable * pickable )
{
    unselect((KSelectable*)pickable);
    KPickHandler::removePickable(pickable);
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::cut ()
{
    copy();
    std::vector<KSelectable*>::iterator iter = selected_selectables.begin();
    while (iter != selected_selectables.end())
    {
        (*iter)->setSelected(false); 
        iter++;
    } 
    iter = selected_selectables.begin();
    while (iter != selected_selectables.end())
    {
        if ((*iter)->isCutCopyPasteable())
        {
            KSelectable * removedItem = *iter;
            iter = selected_selectables.erase(iter);
            deletePickable(removedItem);
        }
        else
        {
            iter++;
        }
    }
    selected_selectables.clear();
    unpick();
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::copy ()
{
    clearPasteBuffer();
    
    std::vector<KSelectable*>::iterator iter = selected_selectables.begin();
    while (iter != selected_selectables.end())
    {
        if ((*iter)->isCutCopyPasteable())
        {
            paste_buffer.push_back((*iter)->getPasteBufferString());
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::paste ()
{
    std::vector<std::string>::iterator iter = paste_buffer.begin();
    while (iter != paste_buffer.end())
    {
        pasted(*iter);
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::clearPasteBuffer ()
{
    paste_buffer.clear();
}
    
// --------------------------------------------------------------------------------------------------------
bool KSelectionHandler::isSelected (KSelectable * selectable)
{
    std::vector<KSelectable *>::iterator result;
    result = std::find(selected_selectables.begin(), selected_selectables.end(), selectable);
    return (result != selected_selectables.end());
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::select(KSelectable * selectable)
{
    std::vector<KSelectable*>::iterator result;
    result = std::find (selected_selectables.begin(), selected_selectables.end(), selectable);
    if (result == selected_selectables.end())
    {
        selected_selectables.push_back(selectable);
        selectable->setSelected(true);
    }
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::unselectAllInVector (const PickableVector * pv)
{
    PickableVector::const_iterator iter = pv->begin();
    while (iter != pv->end())
    {
        if ((*iter)->getClassId() >= KSelectable::classId())
        {
            unselect((KSelectable*)(*iter));
        }
        iter++;
    }
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::unselect(KSelectable * selectable)
{
    std::vector<KSelectable*>::iterator result;
    result = std::find (selected_selectables.begin(), selected_selectables.end(), selectable);
    if (result != selected_selectables.end())
    {
        selectable->setSelected(false);
        if (selectable->hasSubPickables())
        {
            unselectAllInVector(selectable->getSubPickables());    
        }
        selected_selectables.erase(result);
    }
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::unselectAll()
{
    std::vector<KSelectable*>::iterator iter = selected_selectables.begin();
    while (iter != selected_selectables.end())
    {
        (*iter)->setSelected(false); 
        iter++;
    }        
    selected_selectables.clear();
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::picked ()
{
    KSelectable * selectable;

    if (picked_pickable->getClassId() >= KSelectable::classId())
    {
        selectable = (KSelectable *)picked_pickable;
    }
    else // try to find selectable parent
    {
        const KPickable * parent = picked_pickable; 
        while (parent = getParentOfPickable(parent))
        {
            if (parent->getClassId() >= KSelectable::classId())
            {
                break;
            }
        }
        
        if (!parent) return;
        selectable = (KSelectable*)parent;
    }
    
    if (selectable->isSelected()) 
    {
        unselect(selectable);
    } 
    else 
    {
        if ((SDL_GetModState() & KMOD_SHIFT) == false) 
        {
            unselectAll();
        }
        select(selectable);
    }
}

// --------------------------------------------------------------------------------------------------------
void KSelectionHandler::unpicked ()
{
    if ((SDL_GetModState() & KMOD_SHIFT) == false) 
    {
        unselectAll();
    }
}


