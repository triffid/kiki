/*
 *  KFileTools.h
 *  kodisein
 */

#ifndef __KFileTools
#define __KFileTools

#include <string> 
#include <vector> 

// --------------------------------------------------------------------------------------------------------
std::string	kFileCleanPath		( const std::string & );
std::string	kFileGetCurrentPath	();
std::string	kFileSubstitutePath	( const std::string & );
bool		kFileIsImageFile 	( const std::string & );
bool		kFileExists 		( const std::string & );
bool		kFileIsFile 		( const std::string & );
bool		kFileIsDir 		( const std::string & );
std::string	kFileAbsPathName 	( const std::string & );
std::string	kFileSuffix 		( const std::string & );
std::string	kFileDirName 		( const std::string & );
std::string	kFileBaseName 		( const std::string &, bool = false );
bool 		kFileGetDirEntries 	( const std::string &, std::vector<std::string> &, bool = false );
std::string	kFileReadStringFromFile ( const std::string &, unsigned int = 0 );
bool 		kFileWriteStringToFile  ( const std::string &, const std::string & );
 
#endif
