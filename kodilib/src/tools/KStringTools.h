/*
 *  KStringTools.h
 *  kodisein
 */

#ifndef __KStringTools
#define __KStringTools

#include <string>
#include <vector>
#include <stdarg.h>
#include <string.h>

// --------------------------------------------------------------------------------------------------------

void		kStringInsertStringBehindTags	( std::string & str, const std::string & insertString,
                                                    const std::string & tag);
void		kStringMerge			( std::string & str, const std::string & str2, 
                                                    const std::string & divider );
std::vector<std::string> kStringGetComponents	( const std::string & str, const std::string & divider );
void 		kStringReplace			( std::string &, const std::string & , 
                                                    const std::string & );
void		kStringReplaceTabs		( std::string &, unsigned int = 4 );
std::string	kStringGetSharedPrefix		( const std::vector<std::string> & );
void 		kStringCropCols 		( std::string & , unsigned int );
void 		kStringCropRows			( std::string & , unsigned int );
unsigned int	kStringNthCharPos		( const std::string & , unsigned int, char );
unsigned int	kStringRows 			( const std::string & );
unsigned int	kStringCols 			( const std::string & );
unsigned int	kStringWidth 			( const std::string & , bool = true);
unsigned int	kStringHeight 			( const std::string & , bool = true);
unsigned int 	kStringCountChars 		( const std::string &, char );
std::string	kStringPrintf			( const char * ... );
std::string	kStringPrintf			( const std::string &, va_list * );
bool		kStringHasSuffix		( const std::string &, const std::string & );

// --------------------------------------------------------------------------------------------------------
struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

// --------------------------------------------------------------------------------------------------------
struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

#endif
