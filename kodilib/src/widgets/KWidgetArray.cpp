 /*
 *  KWidgetArray.cpp
 *  kodisein
 */

#include "KWidgetArray.h"
#include "KLabel.h"
#include "KConsole.h"

KDL_CLASS_INTROSPECTION_1 (KWidgetArray, KWidget)

// --------------------------------------------------------------------------------------------------------
KWidgetArray::KWidgetArray () : KWidget ()
{  
    flags.resize(KDL_WIDGETARRAY_FLAG_END);
    flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL] = true;
    spacing	  = KDL_WIDGET_DEFAULT_CHILD_SPACING;
    frame_spacing = KDL_WIDGET_DEFAULT_FRAME_SPACING;
}

// --------------------------------------------------------------------------------------------------------
KSize KWidgetArray::layout ()
{
    min_size = KSize(frame_spacing, frame_spacing);

    std::vector<KWidget*> fillWidgets;
    
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        KWidget * child = (KWidget*)*iter;
        if (child->flags[KDL_WIDGET_FLAG_VISIBLE])
        {
            child->reset();
            KSize childSize = child->layout();
            
            // check if array will fill available space
            if (child->flags[KDL_WIDGET_FLAG_FILL_X]) flags[KDL_WIDGET_FLAG_FILL_X] = true;
            if (child->flags[KDL_WIDGET_FLAG_FILL_Y]) flags[KDL_WIDGET_FLAG_FILL_Y] = true;
            
            // translate widgets according to layout style
            if (flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL])
            {
                if (child->flags[KDL_WIDGET_FLAG_FILL_Y]) fillWidgets.push_back(child);
                
                child->translate(min_size.w, -frame_spacing);
                min_size.w += childSize.w + spacing;
                min_size.h = kMax(min_size.h, childSize.h + frame_spacing);
            }
            else 
            {
                if (child->flags[KDL_WIDGET_FLAG_FILL_X]) fillWidgets.push_back(child);

                child->translate(frame_spacing, -min_size.h);
                min_size.h += childSize.h + spacing;
                min_size.w = kMax(min_size.w, childSize.w + frame_spacing);
            }
        } 
        iter++;
    }
    
    if (flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL]) 
    {
        min_size.w += (frame_spacing - spacing); 
        min_size.h += frame_spacing;

        while (fillWidgets.empty() == false)
        {
            fillWidgets.back()->relayout(KSize(fillWidgets.back()->getSize().w, min_size.h-2*frame_spacing));
            fillWidgets.pop_back();
        }
    }
    else 
    {
        min_size.w += frame_spacing;
        min_size.h += (frame_spacing - spacing);

        while (fillWidgets.empty() == false)
        {
            fillWidgets.back()->relayout(KSize(min_size.w-2*frame_spacing, fillWidgets.back()->getSize().h));
            fillWidgets.pop_back();
        }
    }
    
    size = min_size;
    return min_size;
}

// --------------------------------------------------------------------------------------------------------
KSize KWidgetArray::relayout ( const KSize & newSize )
{
    KSize sizeDiff = newSize - size;
    
    if (flags[KDL_WIDGET_FLAG_FILL_X] == false && flags[KDL_WIDGET_FLAG_FILL_Y] == false || 
        sizeDiff.w == 0 && sizeDiff.h == 0)
    {
        // nothing to resize or minimum size reached -> return
        size = KSize(kMax(min_size.w, size.w), kMax(min_size.h, size.h));
        return size;
    }
    
    int xFillWidgets = 0, yFillWidgets = 0;
    PickableVector::iterator iter = children.begin();
    while (iter != children.end())
    {
        KWidget * child = (KWidget*)*iter;
        if (child->flags[KDL_WIDGET_FLAG_VISIBLE])
        {
            if (child->flags[KDL_WIDGET_FLAG_FILL_X]) xFillWidgets++;
            if (child->flags[KDL_WIDGET_FLAG_FILL_Y]) yFillWidgets++;
        }
        iter++;
    }
    
    KSize maxSize = newSize;

    if (flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL]) 
    {
        maxSize.h -= (2 * frame_spacing);
        if (xFillWidgets > 1)
        {
            sizeDiff.w /= xFillWidgets;
        }
    }
    else // vertical layout
    {
        maxSize.w -= (2 * frame_spacing);
        if (yFillWidgets > 1)
        {
            sizeDiff.h /= yFillWidgets;
        }
    }

    size.w = frame_spacing;
    size.h = frame_spacing;
    
    iter = children.begin();
    while (iter != children.end())
    {
        KWidget * child = (KWidget*)*iter;
        if (child->flags[KDL_WIDGET_FLAG_VISIBLE])
        {
            child->reset();
            KSize childSize = child->getSize();
            
            // translate widgets according to layout style
            if (flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL])
            {
                maxSize.w = childSize.w + sizeDiff.w;
                childSize = child->relayout(maxSize);
                child->translate(size.w, -frame_spacing);
                size.w += childSize.w + spacing;
                size.h = kMax(size.h, childSize.h + frame_spacing);
            }
            else 
            {
                maxSize.h = childSize.h + sizeDiff.h;
                childSize = child->relayout(maxSize);
                child->translate(frame_spacing, -size.h);
                size.h += childSize.h + spacing;
                size.w = kMax(size.w, childSize.w + frame_spacing);
            }
        } 
        iter++;
    }
    
    if (flags[KDL_WIDGETARRAY_FLAG_HORIZONTAL]) 
    {
        size.w += (frame_spacing - spacing); 
        size.h += frame_spacing;
    }
    else 
    {
        size.w += frame_spacing;
        size.h += (frame_spacing - spacing);
    }

    return size;
}

// --------------------------------------------------------------------------------------------------------
void KWidgetArray::clear ()
{  
    while (children.empty() == false)
    {
        delete children.back();
        children.pop_back();
    }
    size.w = size.h = 0;
    getRootWidget()->layout();
}

// --------------------------------------------------------------------------------------------------------
void KWidgetArray::alignLabels ()
{
    // find and store all labels which are the first child of a a widget array child
    // also keep track of the maximum width of these labels
    int maxLabelWidth = 0;
    std::vector<KLabel*> labelWidgets;
    PickableVector::const_iterator iter = children.begin();
    while (iter != children.end())
    {
        if ((*iter)->getClassId() >= KWidgetArray::classId())
        {
            KPickable * firstChild = ((KWidgetArray*)*iter)->getChildren()->front();
            if (firstChild->getClassId() == KLabel::classId())
            {
                int size = ((KLabel*)firstChild)->getText().size();
                if (size >= maxLabelWidth) 
                {
                    maxLabelWidth = size;
                }
                labelWidgets.push_back((KLabel*)firstChild);
            }
        }
        iter++;
    }
    
    // iterate through the labels and resize them (actually adding spaces to their text)
    std::vector<KLabel*>::iterator labelIter = labelWidgets.begin();
    while (labelIter != labelWidgets.end())
    {
        std::string labelText = (*labelIter)->getText();
        (*labelIter)->setText(labelText + std::string(maxLabelWidth - labelText.size(), ' '));
        labelIter++;
    }
}


