/*
 *  KXMLTools.h
 *  kodisein
 */

#ifndef __KXMLTools
#define __KXMLTools

#include "KStringTools.h"

#define KDL_XML_INDENT 2

enum {	KDL_XML_VALUE_FLOAT, KDL_XML_VALUE_INT, KDL_XML_VALUE_CHAR, KDL_XML_VALUE_BOOL, 
        KDL_XML_VALUE_STRING, KDL_XML_VALUE_VERTEX, KDL_XML_VALUE_SIZE, KDL_XML_VALUE_POSITION,
        KDL_XML_VALUE_MATRIX, KDL_XML_VALUE_SEPARATED_MATRIX };

// --------------------------------------------------------------------------------------------------------
std::string	kXMLReadNamedAttribute	( const std::string &, const std::string & );
bool		kXMLReadNamedOpenTag	( const std::string &, const std::string &, std::string * = NULL);
std::string	kXMLParseToTagsInVector	( std::string &, const std::vector<std::string> & );
std::string	kXMLParseNamedOpenTag	( std::string &, const std::string &, std::string * = NULL, bool = true );
bool		kXMLParseNamedCloseTag	( std::string &, const std::string &, bool = true );
bool		kXMLParseOpenTag	( std::string &, std::string &, std::string * = NULL, bool = true );
bool 		kXMLParseValue		( std::string &, const std::string &, int, void *, bool = true);

std::string	kXMLTag			( const std::string &, const std::string & = "", int = 0 );
std::string	kXMLOpenTag 		( const std::string &, const std::string & = "", int = 0 );
std::string	kXMLCloseTag 		( const std::string &, int = 0 );
std::string	kXMLPrintf		( int, const char * ...);
std::string	kXMLValue		( const std::string &, int, const void * , int = 0 );

#endif
