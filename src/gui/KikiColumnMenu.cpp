/*
 *  KikiColumnMenu.cpp
 *  kiki
 */

#include "KikiColumnMenu.h"
#include <KLightingProjection.h>

// __________________________________________________________________________________________________
KikiColumnMenu::KikiColumnMenu ( int maxColumnItems, int activeItem ) : KikiMenu (activeItem)
{
    max_column_items = maxColumnItems;
    column_spacing = 6.0;
    KikiText::flags[ALIGN_CENTER] = false;
}

// __________________________________________________________________________________________________
void KikiColumnMenu::alignItems ()
{ 
    // ............................................................................ align text lines
    int numLines   = menu_items.size();
    
    width  = 0.0;
    height = 0.0;
    
    float value_offset = 0.0;
    float value_width  = 0.0;
	float extra_width  = 0.0;
    
    for (std::vector<KikiMenuItem*>::iterator iter = menu_items.begin(); iter != menu_items.end(); iter++)
    {
        if ((*iter)->getWidth() > width) width = (*iter)->getWidth();
        height += (*iter)->getHeight() + line_spacing;
        
        if ((*iter)->value_text)
        {
            value_offset = kMax ((*iter)->item_text->getWidth(), value_offset);
            value_width  = kMax ((*iter)->value_text->getWidth(), value_width);
        }
        if ((*iter)->extra_text)
        {
            extra_width  = kMax ((*iter)->extra_text->getWidth(), extra_width);
        }
    }

    if (value_offset == 0.0)
    {
        value_offset = width/2.0;
    }
    else
    {
        width = kMax (width, value_offset + value_width + extra_width);
    }
    
    float 	currentHeight;
    
    int 	columns = (int)ceil (numLines / (float)max_column_items);
    int 	column_items = (int) ceil (numLines / (float)columns);
    float 	column_offset;
    int 	column_line_index = 0;
    int 	column_index = -1;
    float	column_width = width + column_spacing;
    
    width = columns * column_width;
    height = height / columns + 2 * column_spacing;

    for (int lineIndex = 0; lineIndex < numLines; lineIndex++)
    {        
        if (column_line_index % column_items == 0)
        {
            column_index++;
            
            column_offset = - columns * column_width / 2.0 + column_index * column_width + column_width / 2.0;
            
            column_line_index = 0;
            
            currentHeight = menu_items[lineIndex]->getHeight() + column_spacing;
        }
        else
        {
            currentHeight += menu_items[lineIndex]->getHeight() + line_spacing;
        }

        float yOffset = -(currentHeight - height/2.0);
        
        column_line_index++;
        
        if (KikiText::flags[ALIGN_CENTER])
        {
            if (menu_items[lineIndex]->value_text)
            {
                menu_items[lineIndex]->item_text->setPosition
                        (KVector (-column_width/2.0 + value_offset + column_offset - 
                                    menu_items[lineIndex]->item_text->getWidth(), 
                                    yOffset, 0.0));
                menu_items[lineIndex]->value_text->setPosition 
                        (KVector (-column_width/2.0 + value_offset + column_offset, 
									yOffset, 0.0));            
            }
            else
            {
                menu_items[lineIndex]->item_text->setPosition
                        (KVector (menu_items[lineIndex]->item_text->getWidth()/2.0 + column_offset, 
                                    yOffset, 0.0));
            }
        }
        else
        {
            menu_items[lineIndex]->item_text->setPosition 
                        (KVector (column_offset - column_width / 2.0, 
                                    yOffset, 0.0));
            if (menu_items[lineIndex]->value_text)
            {
                menu_items[lineIndex]->value_text->setPosition 
                        (KVector (column_offset - column_width / 2.0 + value_offset, 
                                    yOffset, 0.0));
            }
			if (menu_items[lineIndex]->extra_text)
			{
				menu_items[lineIndex]->extra_text->setPosition
						(KVector (column_offset + column_width / 2.0 - extra_width, 
                                    yOffset, 0.0));
			}
        }
    }

    // ............................................................................ adjust projection    
    float distance = kMax (width / projection->getCurrentAspectRatio(), height);
    projection->KMatrix::reset();
    projection->translate (0.0, 0.0, distance);
    ((KLightingProjection*)projection)->setLightOffset 
                        (KVector (-width / (projection->getCurrentAspectRatio() * 2.0), height, 0.0));
    projection->setZFar (distance + 10);
    projection->setZNear (distance - 10);
}

