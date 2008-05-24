/*
 *  KStringTools.cpp
 *  kodisein
 */

#include "KStringTools.h"
#include "KVector.h"

//#include <sys/types.h> 	// INT_MAX
#include <limits.h> // INT_MAX
#include <stdio.h>

// --------------------------------------------------------------------------------------------------------
void kStringInsertStringBehindTags ( std::string & str, const std::string & insertString, 
                                     const std::string & tag )
{
    unsigned int oldPos = 0;
    while ((oldPos = str.find(tag, oldPos)) != std::string::npos)
    {
        oldPos += tag.size();
        str.insert(oldPos, insertString);
        oldPos += insertString.size();
    }
}

// --------------------------------------------------------------------------------------------------------
void kStringMerge ( std::string & str, const std::string & str2, const std::string & divider )
{
    if (str == "") str = str2;
    else if (str2 != "") str += divider + str2;
}

// --------------------------------------------------------------------------------------------------------
std::vector<std::string> kStringGetComponents ( const std::string & str, const std::string & divider )
{
    std::vector<std::string> components;
    
    unsigned int dividerLength = divider.size();
    unsigned int oldpos = 0, pos;
    
    while ((pos = str.find(divider, oldpos)) != std::string::npos)
    {
        components.push_back(str.substr(oldpos, pos - oldpos));
        oldpos = pos + dividerLength;
    }
    components.push_back(str.substr(oldpos));
    
    return components;
}

// --------------------------------------------------------------------------------------------------------
void kStringReplace ( std::string & str, const std::string & toReplace, const std::string & replacement )
{
    unsigned int pos = 0, chars = toReplace.size();
    while ((pos = str.find(toReplace, pos)) != std::string::npos)
    {
        str.replace(pos, chars, replacement);
    }
}

// --------------------------------------------------------------------------------------------------------
void kStringReplaceTabs ( std::string & str, unsigned int tabWidth )
{
    unsigned int tabPos;
    while ((tabPos = str.find('\t')) != std::string::npos)
    {
        unsigned int lastNewlinePos = str.rfind('\n', tabPos-1);
        unsigned int relPos = (lastNewlinePos == std::string::npos) ? tabPos : tabPos - lastNewlinePos; 
        str.replace(tabPos, 1, std::string(tabWidth-(relPos % tabWidth), ' '));
    }
}

// --------------------------------------------------------------------------------------------------------
std::string kStringGetSharedPrefix ( const std::vector<std::string> & strings )
{
    if (strings.empty()) return "";
    std::vector<std::string>::const_iterator iter = strings.begin();
    unsigned int maxlength = INT_MAX;
    while (iter != strings.end())
    {
        maxlength = kMin(maxlength, iter->size()); 
        iter++;
    }
    if (maxlength == 0) return "";
    
    std::string prefix;
    unsigned int index = 0;
    while (index < maxlength)
    {
        iter = strings.begin();
        char c = (*iter)[index]; 
        iter++;
        while (iter != strings.end())
        {
            if ((*iter)[index] != c) return prefix;
            iter++;
        }
        prefix += c;
        index++;
    }
    return prefix;
}

// --------------------------------------------------------------------------------------------------------
unsigned int kStringCountChars ( const std::string & str, char c )
{
    unsigned int count = 0;
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] == c) count++;
    }
    return count;
}

// --------------------------------------------------------------------------------------------------------
unsigned int kStringNthCharPos ( const std::string & str, unsigned int n, char c )
{
    unsigned int loc = n, oloc = 0;
    while (n > 0 && (loc = str.find(c, oloc)) != std::string::npos)
    { 
        n--; 
        oloc = loc+1; 
    }
    if (n > 0) return INT_MAX; 
    return loc;
}

// --------------------------------------------------------------------------------------------------------
void kStringCropRows ( std::string & str, unsigned int rows )
{        
    unsigned int lines = kStringRows(str);
    if (lines > rows)
    {
        unsigned int loc = kStringNthCharPos(str, (lines-rows), '\n');
        str.erase(0, loc+1);
    }
}

// --------------------------------------------------------------------------------------------------------
void kStringCropCols ( std::string & str, unsigned int columns )
{        
    unsigned int oloc = 0, nloc = 0;
    while ((nloc = str.find('\n', oloc)) != std::string::npos)
    {
        if ((nloc - oloc) > columns)
        {
            str.erase(oloc + columns, nloc - (oloc + columns));
            nloc = oloc + columns;
        }
        oloc = nloc + 1;
    }
    nloc = (str.size() < nloc) ? str.size() : nloc;
    int d = nloc - (oloc + columns);
    if (d > 0)
    {
        str.erase(oloc + columns, d);
    }
}

// --------------------------------------------------------------------------------------------------------
unsigned int kStringCols ( const std::string & str )
{
    if (str.size() == 0) return 0;
    int oloc = 0, nloc;
    std::string substring;
    int maxlength = 0, length;
    while ((nloc = str.find('\n', oloc)) != (int)std::string::npos) 
    {
        substring = str.substr(oloc, nloc - oloc);
        length = substring.size();
        maxlength = (length > maxlength) ? length : maxlength;
        oloc = nloc + 1;
    }
    substring = str.substr(oloc);
    length = substring.size();
    maxlength = (length > maxlength) ? length : maxlength;
    
    return maxlength;
}

// --------------------------------------------------------------------------------------------------------
unsigned int kStringRows ( const std::string & str )
{
    if (str.size() == 0) return 1;
    unsigned int loc = 0, lines = 0;
    while ((loc = str.find('\n', loc)) != std::string::npos) { lines++; loc++; }
    if (str[str.size()-1] == '\n') return lines;
    return lines+1;
}

// --------------------------------------------------------------------------------------------------------
unsigned int kStringWidth ( const std::string & str, bool largeFont )
{
    return ((largeFont ? 9 : 8) * kStringCols(str));
}

// --------------------------------------------------------------------------------------------------------
unsigned int kStringHeight ( const std::string & str, bool largeFont )
{
    return ((largeFont ? 15 : 13) * kStringRows(str));
}

// --------------------------------------------------------------------------------------------------------
std::string kStringPrintf ( const std::string & fmt, va_list * argList )
{
    static char str[256];
    std::string format(fmt), subformat, text;
    unsigned int oloc = 0;
    unsigned int nloc = 0;
    
    kStringReplaceTabs(format);
    
    while ((nloc = format.find('%', oloc)) != std::string::npos)
    {
        text += format.substr(oloc, nloc - oloc);
        oloc = nloc;
        nloc = format.find_first_of("diouXxfeEgGbcs", oloc);
        if (nloc == std::string::npos) break; // should not happen
        subformat = format.substr(oloc, nloc - oloc + 1);
        
        if (format[nloc] == 's' || format[nloc] == 'b')
        {
           text += (char *)va_arg(*argList, const char *);
        }
        else
        {
            switch (format[nloc])
            {
                case 'c':
                case 'd':
                case 'i':
                case 'o':
                case 'u':
                case 'X':
                case 'x':	sprintf(str, subformat.c_str(), va_arg(*argList, int));		break;
                case 'f':
                case 'e':
                case 'E':
                case 'g':
                case 'G':	sprintf(str, subformat.c_str(), va_arg(*argList, double));	break;
            }
            text += str;
        }
        oloc = nloc+1;
    }
    
    text += format.substr(oloc);
    return text;
}

// --------------------------------------------------------------------------------------------------------
std::string kStringPrintf ( const char * fmt ...)
{
    va_list argList;
    va_start(argList, fmt);
    std::string text(kStringPrintf(std::string(fmt), &argList));
    va_end(argList);
    return text;
}

// --------------------------------------------------------------------------------------------------------
bool kStringHasSuffix ( const std::string & str, const std::string & suffix )
{
    unsigned int result = str.rfind(suffix);
    if (result == std::string::npos) return false;
    return (result == str.size()-suffix.size());
}

