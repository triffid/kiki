/*
 *  KXMLTools.cpp
 *  kodisein
 */

#include "KXMLTools.h"
#include "KConsole.h"
#include "KSeparatedMatrix.h"
#include <stdio.h>

// --------------------------------------------------------------------------------------------------------
std::string kXMLTag ( const std::string & name, const std::string & attributes, int depth )
{
    std::string xml(depth, ' ');
    xml += "<";
    xml += name;
    if (attributes.size() > 0) xml += " ";
    xml += attributes;
    xml += " />\n";
    return xml;
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLOpenTag ( const std::string & name, const std::string & attributes, int depth )
{
    std::string xml(depth, ' ');
    xml += "<";
    xml += name;
    if (attributes.size() > 0) xml += " ";
    xml += attributes;
    xml += ">\n";
    return xml; 
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLCloseTag ( const std::string & name, int depth )
{
    std::string xml(depth, ' ');
    xml += "</";
    xml += name;
    xml += ">\n";
    
    return xml; 
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLPrintf ( int depth, const char * fmt ...)
{
    std::string text(depth, ' ');
    va_list argList;
    va_start(argList, fmt);
    text += kStringPrintf(std::string(fmt), &argList);
    va_end(argList);
    return text;
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLParseToTagsInVector ( std::string & xml, const std::vector<std::string> & tags )
{
    std::string open("<");
    unsigned int minLoc = std::string::npos; 
    std::vector<std::string>::const_iterator iter = tags.begin();
    while (iter != tags.end())
    {
        unsigned int loc = xml.find(open+(*iter));
        if (loc < minLoc) minLoc = loc;
        iter++;
    }
    std::string substring = xml.substr(0, minLoc);
    xml.erase(0, minLoc);
    return substring;
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLReadNamedAttribute ( const std::string & xml, const std::string & name )
{
    std::string value;
    std::string nameStr(name);
    nameStr += "='";
    unsigned int loc = xml.find(nameStr);
    if (loc != std::string::npos)
    {	
        loc += nameStr.size();
        value = xml.substr(loc, xml.find("'", loc) - loc);
    }
    
    return value;
}

// --------------------------------------------------------------------------------------------------------
bool kXMLParseNamedCloseTag ( std::string & xml, const std::string & name, bool printError )
{
    unsigned int loc = xml.find('<');
    if (loc == std::string::npos) 
    {
        if (printError) KConsole::printError(kStringPrintf("invalid XML:\nmissing close tag '%s'", 
                                                                                            name.c_str()));
        return false;
    }

    xml.erase(0, loc);
    std::string closeTag;
    closeTag += "</";
    closeTag += name;
    closeTag += ">";
    if ((loc = xml.find(closeTag)) != 0) 
    {
        if (printError) KConsole::printError(kStringPrintf("invalid XML:\nmissing close tag '%s'", 
                                                                                            name.c_str()));
        return false;
    }

    xml.erase(0, closeTag.size());
    return true;
}

// --------------------------------------------------------------------------------------------------------
bool kXMLReadNamedOpenTag ( const std::string & xml, const std::string & name, std::string * attributes )
{
    unsigned int loc = xml.find('<'), endloc;
    
    if (loc == std::string::npos || xml[loc+1] == '/') return false;
    
    loc++;    
    
    endloc = xml.find_first_of(" >", loc);
    
    if (xml.substr(loc, endloc-loc) != name) return false;
    
    if (attributes == NULL || xml[endloc] == '>') return true;

    loc = endloc+1;
    endloc = xml.find(">", loc);
    
    *attributes = xml.substr(loc, endloc-loc);
    
    return true;
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLParseNamedOpenTag ( std::string & xml, const std::string & name, std::string * attributes, bool printError )
{
    unsigned int loc = xml.find('<');
    if (loc == std::string::npos || xml[loc+1] == '/') 
    {
        if (printError) KConsole::printError(kStringPrintf("invalid XML:\nmissing tag '%s'", name.c_str()));
        return "";
    }

    std::string tagString("<");
    xml.erase(0, loc+1);
    
    loc = xml.find_first_of(" >");
    
    if (xml.substr(0, loc) != name)
    {
        xml.insert(0, "<");
        if (printError) KConsole::printError(kStringPrintf("invalid XML:\nmissing tag '%s'", name.c_str()));
        return "";
    }
    
    if (attributes == NULL)
    {
        loc = xml.find(">")+1;
        tagString += xml.substr(0,loc);
        xml.erase(0, loc);
        return tagString;
    }

    tagString += xml.substr(0,loc);
    xml.erase(0, loc);
    
    if (xml[0] == ' ')
    {
        tagString += " ";
        xml.erase(0, 1);
        loc = xml.find('>');
        *attributes = xml.substr(0, loc);
        tagString += xml.substr(0, loc+1);
        xml.erase(0, loc+1);
    }
    else
    {
        tagString += ">";
        xml.erase(0, 1);
    }
        
    return tagString;
}

// --------------------------------------------------------------------------------------------------------
bool kXMLParseOpenTag ( std::string & xml, std::string & name, std::string * attributes, bool printError )
{
    unsigned int loc = xml.find('<');
    if (loc == std::string::npos || xml[loc+1] == '/') 
    {
        if (printError) KConsole::printError("invalid XML:\nmissing open tag");
        return false;
    }

    xml.erase(0, loc+1);
    loc = xml.find_first_of(" >");
    name = xml.substr(0, loc);

    if (attributes == NULL)
    {
        xml.erase(0, xml.find(">")+1);
        return true;
    }

    xml.erase(0, loc);
    
    if (xml[0] == ' ')
    {
        xml.erase(0, 1);
        loc = xml.find('>');
        *attributes = xml.substr(0, loc);
        xml.erase(0, loc+1);
    }
    else
    {
        xml.erase(0, 1);
    }
        
    return true;
}

// --------------------------------------------------------------------------------------------------------
std::string kXMLValue( const std::string & name, int type, const void * value, int depth )
{
    switch (type)
    {
        case KDL_XML_VALUE_FLOAT:	
            return kXMLTag("Value", kStringPrintf("name='%s' type='float' value='%g'", 
                                                name.c_str(), *(float *)value), depth);
        case KDL_XML_VALUE_INT:	
            return kXMLTag("Value", kStringPrintf("name='%s' type='int' value='%d'", 
                                                name.c_str(), *(int *)value), depth);
        case KDL_XML_VALUE_CHAR:	
            return kXMLTag("Value", kStringPrintf("name='%s' type='char' value='%c'", 
                                                name.c_str(), *(char *)value), depth);
        case KDL_XML_VALUE_BOOL:	
            return kXMLTag("Value", kStringPrintf("name='%s' type='bool' value='%s'", 
                                                name.c_str(), *(bool *)value ? "true" : "false"), depth);
        case KDL_XML_VALUE_VERTEX:	
            return kXMLTag("Value", kStringPrintf("name='%s' type='vector' x='%g' y='%g', z='%g'", 
                                                name.c_str(), 
                                                (*(KVector*)value)[0], 
                                                (*(KVector*)value)[1],
                                                (*(KVector*)value)[2]), depth);
        case KDL_XML_VALUE_SIZE:	
            return kXMLTag("Value", kStringPrintf("name='%s' type='size' w='%d' h='%d'", 
                                    name.c_str(), (*(KSize*)value).w, (*(KSize*)value).h), depth);
        case KDL_XML_VALUE_POSITION:
            return kXMLTag("Value", kStringPrintf("name='%s' type='position' x='%d' y='%d'", 
                                    name.c_str(), (*(KPosition*)value).x, (*(KPosition*)value).y), depth);
    }
    
    std::string xml;
    
    if (type == KDL_XML_VALUE_STRING)
    {
        xml += kXMLOpenTag("Value", kStringPrintf("name='%s' type='string'", name.c_str()), depth);
        xml += kXMLPrintf(depth+KDL_XML_INDENT, "\"%s\"\n", ((std::string*)value)->c_str());
    }
    else if (type == KDL_XML_VALUE_MATRIX)
    {
        xml += kXMLOpenTag("Value", kStringPrintf("name='%s' type='matrix'", name.c_str()), depth);
        KMatrix m = *(KMatrix*)value;
        xml += kXMLPrintf  (depth+KDL_XML_INDENT, "%g %g %g %g\n", m[0], m[4], m[8],  m[12]);
        xml += kXMLPrintf  (depth+KDL_XML_INDENT, "%g %g %g %g\n", m[1], m[5], m[9],  m[13]);
        xml += kXMLPrintf  (depth+KDL_XML_INDENT, "%g %g %g %g\n", m[2], m[6], m[10], m[14]);
        xml += kXMLPrintf  (depth+KDL_XML_INDENT, "%g %g %g %g\n", m[3], m[7], m[11], m[15]);    
    }
    else if (type == KDL_XML_VALUE_SEPARATED_MATRIX)
    {
        xml += kXMLOpenTag("Value", kStringPrintf("name='%s' type='transformation'", name.c_str()), depth);
        xml += kXMLPrintf  (depth+KDL_XML_INDENT, "%g %g %g   %g %g %g   %g %g %g\n",
                                                                ((KSeparatedMatrix*)value)->getTX(),
                                                                ((KSeparatedMatrix*)value)->getTY(),
                                                                ((KSeparatedMatrix*)value)->getTZ(),
                                                                ((KSeparatedMatrix*)value)->getRX(),
                                                                ((KSeparatedMatrix*)value)->getRY(),
                                                                ((KSeparatedMatrix*)value)->getRZ(),
                                                                ((KSeparatedMatrix*)value)->getSX(),
                                                                ((KSeparatedMatrix*)value)->getSY(),
                                                                ((KSeparatedMatrix*)value)->getSZ());
    }

    xml += kXMLCloseTag("Value", depth);
    
    return xml;
}

// --------------------------------------------------------------------------------------------------------
bool kXMLParseValue( std::string & xml, const std::string & name, int type, void * value, bool printError )
{
    unsigned int loc = xml.find('<');
    if (loc == std::string::npos || xml[loc+1] == '/')     
    {
        if (printError) KConsole::printError(kStringPrintf("invalid XML:\nmissing value '%s'", name.c_str()));
        return false;
    }
    
    std::string saveString = xml.substr(0, loc);
    xml.erase(0, loc);
    
    std::string valueTag;
    valueTag += "<Value ";
    valueTag += "name='";
    valueTag += name;
    valueTag += "'";
    
    if (xml.find(valueTag) != 0) 
    {
        xml.insert(0, saveString);
        if (printError) KConsole::printError(kStringPrintf("invalid XML:\nmissing value '%s'", name.c_str()));
        return false;
    }
        
    std::string n, attributes;
    kXMLParseOpenTag(xml, n, &attributes);
    
    std::string typeString = kXMLReadNamedAttribute(attributes, "type");
        
    if (typeString == "float")
    {
        *((float*)value) = atof(kXMLReadNamedAttribute(attributes, "value").c_str());
    }
    else if (typeString == "bool")
    {
        *((bool*)value) = (kXMLReadNamedAttribute(attributes, "value") == "true");
    }
    else if (typeString == "int")
    {
        *((int*)value) = atoi(kXMLReadNamedAttribute(attributes, "value").c_str());
    }
    else if (typeString == "char")
    {
        *((char*)value) = kXMLReadNamedAttribute(attributes, "value")[0];
    }
    else if (typeString == "vector")
    {
        *((KVector*)value) = KVector(atof(kXMLReadNamedAttribute(attributes, "x").c_str()),
                                     atof(kXMLReadNamedAttribute(attributes, "y").c_str()),
                                     atof(kXMLReadNamedAttribute(attributes, "z").c_str()));
    }
    else if (typeString == "size")
    {
        *((KSize*)value) = KSize    (atoi(kXMLReadNamedAttribute(attributes, "w").c_str()),
                                     atoi(kXMLReadNamedAttribute(attributes, "h").c_str()));
    }
    else if (typeString == "position")
    {
        *((KPosition*)value) = KPosition(atoi(kXMLReadNamedAttribute(attributes, "x").c_str()),
                                         atoi(kXMLReadNamedAttribute(attributes, "y").c_str()));
    }
    else 
    {
        std::string substring = xml.substr(0, xml.find("</Value>"));
            
        if (typeString == "matrix")
        {
            float m[16];
            sscanf(substring.c_str(), "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g", 
                                        &m[0], &m[4], &m[8],  &m[12], &m[1], &m[5], &m[9],  &m[13],
                                        &m[2], &m[6], &m[10], &m[14], &m[3], &m[7], &m[11], &m[15]);
            *((KMatrix*)value) = KMatrix(m);
        }
        else if (typeString == "transformation")
        {
            float m[9];
            sscanf(substring.c_str(), "%g %g %g %g %g %g %g %g %g", 
                                        &m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7], &m[8]);
            ((KSeparatedMatrix*)value)->reset();
            ((KSeparatedMatrix*)value)->translate(m[0],m[1],m[2]);
            ((KSeparatedMatrix*)value)->rotate   (m[3],m[4],m[5]);
            ((KSeparatedMatrix*)value)->scale    (m[6],m[7],m[8]);
        }
        else if (typeString == "string")
        {
            unsigned int first = substring.find("\"")+1;
            unsigned int last  = substring.rfind("\"", std::string::npos);
            *((std::string*)value) = substring.substr(first, last-first);
        }
        
        std::vector<std::string> tags(1, "/Value");
        kXMLParseToTagsInVector(xml, tags);

        kXMLParseNamedCloseTag(xml, "Value");
    }
    
    return true;
}


