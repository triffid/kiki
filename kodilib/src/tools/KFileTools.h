/*
 *  KFileTools.h
 *  kodisein
 */

#ifndef __KFileTools
#define __KFileTools

#pragma warning(disable:4786)

#include <string> 
#include <vector> 

using namespace std;

extern const char kPathSep;

// --------------------------------------------------------------------------------------------------------
string		kFileSubstitutePath	( const string & );
string		kFileGetCurrentPath ();
string		kFileNativePath		( const string & );
bool		kFileIsImageFile 	( const string & );
bool		kFileHasParent  	( const string & );
bool		kFileIsAbsPath  	( const string & );
bool 		kFileExists 		( const string & );
bool 		kFileIsFile 		( const string & );
bool 		kFileIsDir 		( const string & );
string 		kFileAbsPathName 	( const string & );
string 		kFileSuffix 		( const string & );
string 		kFileDirName 		( const string & );
string 		kFileBaseName 		( const string &, bool = false );
bool 		kFileGetDirEntries 	( const string &, vector<string> &, bool = false );
string 		kFileReadStringFromFile ( const string &, unsigned int = 0 );
bool 		kFileWriteStringToFile  ( const string &, const string & );
string      kFileJoinPaths      ( const string &, const string & );
string      kFileNativePath     ( const string & );
 
#endif