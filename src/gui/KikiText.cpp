/*
 *  KikiText.cpp
 *  kiki
 */
 
#include "KikiText.h"
#include "KikiTextLine.h"
#include "KikiCharacter.h"
#include "KikiController.h"

#include <KConsole.h>
#include <KDisplayTools.h>
#include <KStringTools.h>

// __________________________________________________________________________________________________
unsigned int 	KikiText::display_lists[3][58];
std::vector<KColor> KikiText::colors(3);
const char *	KikiText::color_names[] = { "base", "bright", "dark" };
int		KikiText::list_color = -1;
float		KikiText::bevel_depth = 4.0;

// __________________________________________________________________________________________________
KikiText::KikiText ( const std::string & text, bool centered, int colorIndex )
{
    color = colors[colorIndex];
    line_spacing = 4.0;
    width = height = 0.0;

    flags.resize(FLAGS_END);
    flags[ANIMATE]      = false;
    flags[ALIGN_CENTER] = centered;
    
    if (text != "") 
    {
        addText (text);
    }
}

// __________________________________________________________________________________________________
KikiText::~KikiText ()
{
    clear();
}

// __________________________________________________________________________________________________
void KikiText::setText ( const std::string & str, int colorIndex )
{ 
    clear();
    color = colors[colorIndex];
    addText (str, 1.0); 
}

// __________________________________________________________________________________________________
void KikiText::clear ()
{
    while (text_lines.empty() == false)
    {	
        delete text_lines.back();
        text_lines.pop_back();
    }
    width = height = 0.0;
}

// __________________________________________________________________________________________________
bool KikiText::isEmpty () const
{
    return text_lines.empty();
}

// __________________________________________________________________________________________________
std::string KikiText::getText () const
{
    std::string text;
    for (std::vector<KikiTextLine*>::const_iterator iter = text_lines.begin(); 
         iter != text_lines.end(); iter++)
    {
        if (text != "\n") text += "\n";
        text += (*iter)->getText();
    }
    return text;
}

// __________________________________________________________________________________________________
void KikiText::invalidateLists ( int index )
{
    for (int c = 0; c < 58; c++)
    {
        if (display_lists[index][c])
        {
            glDeleteLists(display_lists[index][c], 1);
            display_lists[index][c] = 0;
        }
    } 
}

// __________________________________________________________________________________________________
void KikiText::reinit ()
{
    invalidateLists(0); invalidateLists(1); invalidateLists(2);
}

// __________________________________________________________________________________________________
void KikiText::init ()
{
    for (int i = 0; i < 3; i++)
    {
        for (int c = 0; c < 58; c++)
        {
            display_lists[i][c] = 0;
        }
    }
}

// __________________________________________________________________________________________________
void KikiText::setObjectColor ( const char * color_name, const KColor & color )
{
    for (int i = 0; i < 3; i++) 
    {
        if (strcmp(color_names[i], color_name) == 0)
        { 
            if (colors[i] != color)
            {
                invalidateLists(i);
            }
            
            colors[i] = color; 
            return; 
        }
    }
}

// __________________________________________________________________________________________________
void KikiText::addText ( const std::string & str, float scaleFactor )
{
    std::vector<std::string> lines = kStringGetComponents ( str, "\n" );
    for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); iter++)
    {
        text_lines.push_back (new KikiTextLine((*iter), scaleFactor));
    }

    // ............................................................................ align text lines
    int numLines = text_lines.size();
    width  = 0.0;
    height = 0.0;
    
    for (std::vector<KikiTextLine*>::iterator tliter = text_lines.begin(); tliter != text_lines.end(); tliter++)
    {
        if ((*tliter)->getWidth() > width) 
        {
            width = (*tliter)->getWidth();
        }
        height += (*tliter)->getHeight() + line_spacing;
    }

    float currentHeight = text_lines[0]->getHeight();

    for (int lineIndex = 0; lineIndex < numLines; lineIndex++)
    {
        float yOffset = -(currentHeight - height/2.0);
        currentHeight += text_lines[lineIndex]->getHeight() + line_spacing;
        
        if (flags[ALIGN_CENTER])
        {
            text_lines[lineIndex]->setPosition (KVector(-text_lines[lineIndex]->getWidth()/2.0,
                                                        yOffset, 0.0));
        }
        else
        {
            text_lines[lineIndex]->setPosition (KVector (0.0, yOffset, 0.0));
        }
    }
}

// __________________________________________________________________________________________________
void KikiText::display ()
{
    color.glColor();
    list_color = -1;
    for (int i = 0; i < 3; i++) 
    { 
        if (color == colors[i]) 
        {
            list_color = i; 
            break; 
        } 
    }

    for (std::vector<KikiTextLine*>::iterator iter = text_lines.begin(); iter != text_lines.end(); iter++)
    {
        (*iter)->display();
    }
}
