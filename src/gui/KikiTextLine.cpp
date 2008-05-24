/*
 *  KikiTextLine.cpp
 *  kiki
 */

#include "KikiTextLine.h"
#include "KikiCharacter.h"
#include "KikiText.h"
#include "KikiController.h"

#include <KConsole.h>

// __________________________________________________________________________________________________
KikiTextLine::KikiTextLine ( const std::string & str, float scaleFactor )
{ 
    scale_factor	= scaleFactor;
    width		= 0.0;
    character_spacing	= 1.0;
    space_width		= 5.0;

    if (str != "") setText(str);
}

// __________________________________________________________________________________________________
KikiTextLine::~KikiTextLine ()
{
    while (characters.empty() == false)
    {
        delete characters.back();
        characters.pop_back();
    }
}

// __________________________________________________________________________________________________
void KikiTextLine::addCharacter ( char c )
{
    KikiCharacter * newCharacter = new KikiCharacter(c);
    characters.push_back(newCharacter);
    
    width += character_spacing;
    newCharacter->setPosition(KVector(width, 0.0, 0.0));
    width += newCharacter->getWidth();
}

// __________________________________________________________________________________________________
void KikiTextLine::setText ( const std::string & str )
{
    text = str;
    std::string::size_type pos;
 
    if ((pos = text.find ("$scale(")) != std::string::npos)
    {
        text.erase (pos, pos+7);
        scale_factor = atof (text.substr (pos, text.find (")", pos)).c_str());
        text.erase (pos, text.find (")", pos)+1);
    }
    
    for (int i = 0; i < (int)text.size(); i++)
    {
        if (text[i] == ' ')
        {
            width += space_width;
        }
        else
        {
			if (text[i] != -61)
				addCharacter (text[i]);
        }
    }
}

// __________________________________________________________________________________________________
void KikiTextLine::display ()
{
    glPushMatrix();
    matrix.glMultMatrix();
    glScalef(scale_factor, scale_factor, scale_factor);
    for (std::vector<KikiCharacter*>::iterator iter = characters.begin(); iter != characters.end(); iter++)
    {
        (*iter)->display();
    }
    glPopMatrix();
}
