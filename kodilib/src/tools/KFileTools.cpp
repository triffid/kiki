/*
 *  KFileTools.cpp
 *  kodisein
 */

#include "KFileTools.h"
#include "KConsole.h"
#include "KStringTools.h"

#pragma warning(disable:4786)

#include <fcntl.h>     	// open
#include <sys/types.h> 	// stat
#include <sys/stat.h>

#ifndef WIN32
#include <unistd.h>    	// close
#include <dirent.h>		// getdirentries
#include <sys/param.h>	// MAXPATHLEN
#else
#include <windows.h>
#include <winbase.h>
#include <direct.h>
#endif

#include <SDL_image.h>

#ifdef WIN32
const char kPathSep = '\\';
#else
const char kPathSep = '/';
#endif

// --------------------------------------------------------------------------------------------------------
string kFileJoinPaths ( const string & path1, const string & path2 )
{
    string filePath;
	filePath = path1 + kPathSep + path2;
    return filePath;
}

// --------------------------------------------------------------------------------------------------------
string kFileGetCurrentPath ()
{
#ifndef WIN32
    char buffer[MAXPATHLEN+1];
    getwd(buffer);
#else
	char buffer[MAX_PATH+1];
	getcwd(buffer, MAX_PATH+1);
#endif

    return string(buffer);
}

// --------------------------------------------------------------------------------------------------------
string kFileHomeDir ()
{
#ifdef WIN32
	return string(getenv("HOMEDRIVE")) + string(getenv("HOMEPATH"));
#else
	return string(getenv("HOME"));
#endif
}

// --------------------------------------------------------------------------------------------------------
string kFileNativePath ( const string & path )
{
	string replaced(path);
    
#ifdef WIN32
	kStringReplace(replaced, "/", "\\");
#else
	kStringReplace(replaced, "\\", "/");
#endif

	return replaced;
}

// --------------------------------------------------------------------------------------------------------
string kFileSubstitutePath ( const string & path )
{
	string native = kFileNativePath(path);
    string filePath;
    if (native[0] == '~')
    {
        filePath = kFileHomeDir();
		if (native.size() > 1)
			 filePath += native.substr(1);
    }
    else
    {
        filePath = native;
    }

    return filePath;
}

// --------------------------------------------------------------------------------------------------------
bool kFileHasParent ( const string & path )
{
	if (path.size() == 1 && path[0] == kPathSep) return false;
	if (path.size() == 2 && path[1] == ':') return false;
	if (path.size() == 3 && path[1] == ':' && path[2] == kPathSep) return false;
	return true;
}

// --------------------------------------------------------------------------------------------------------
bool kFileIsAbsPath ( const string & path )
{
	if (path.size() > 0 && path[0] == kPathSep) return true;
	if (path.size() > 2 && path[1] == ':' && path[2] == kPathSep) return true;
	return false;
}

// --------------------------------------------------------------------------------------------------------
bool kFileExists ( const string & path )
{
#ifndef WIN32
    int fd = open (kFileSubstitutePath(path).c_str(), O_RDONLY | O_NONBLOCK);
    if (fd >= 0)
    {
        close(fd); 
        return true;
    }
    return false;
#else
	DWORD dwAttr = GetFileAttributes(path.c_str());
	if (dwAttr == 0xffffffff)
		return false;
	else 
		return true;
#endif
}

// --------------------------------------------------------------------------------------------------------
bool kFileIsFile ( const string & path )
{
    if (kFileExists(path) == false) return false;
    return !kFileIsDir(path);
}

// --------------------------------------------------------------------------------------------------------
bool kFileIsImageFile ( const string & filename )
{
    if (kFileIsFile(filename) == false) 
    {
        return false;
    }
    string suffix = kFileSuffix(filename);
    if (suffix == "tga") return true;
    if (suffix == "tif") return true;
    if (suffix == "jpg") return true;
    if (suffix == "png") return true;
    if (suffix == "gif") return true;
    if (suffix == "bmp") return true;    
    if (suffix == "pcx") return true;
    if (suffix == "xcf") return true;
    if (suffix == "lbm") return true;
    if (suffix == "xpm") return true;
    if (suffix == "tiff") return true;
    return false;
}

// --------------------------------------------------------------------------------------------------------
bool kFileIsDir ( const string & path )
{
#ifdef WIN32
	return ((GetFileAttributes(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY) != 0);
#else
    string filePath = kFileSubstitutePath(path);
    if (kFileExists(filePath) == false) return false;
    bool   isDir = false;
    struct stat sb;
    int    fd = open (filePath.c_str(), O_RDONLY | O_NONBLOCK);
    if (fstat(fd, &sb) != -1)
    {
        isDir = (sb.st_mode & S_IFDIR);
    }
    else
    {
        KConsole::printError(kStringPrintf("file error:\nunable to read stats of file\n'%s'", filePath.c_str()));
    }
    close(fd);
    return isDir;
#endif
}

// --------------------------------------------------------------------------------------------------------
string kFileAbsPathName ( const string & path )
{
	string native = kFileNativePath(path);
#ifdef WIN32
	char buffer[MAX_PATH];
	DWORD result = GetFullPathName(native.c_str(), MAX_PATH, buffer, NULL);
	if (result > 0 && result < MAX_PATH)
	{
		return string(buffer);
	}
	return "";
#else
    if (native.size() == 0) return "";
    string filePath = kFileSubstitutePath(native);

    if (kFileExists(filePath) == false) return "";
    
    char buffer[MAXPATHLEN+1];
    char * result = realpath(filePath.c_str(), buffer);
    if (result) return result;
    return "";
#endif
}

// --------------------------------------------------------------------------------------------------------
string kFileSuffix ( const string & path )
{
    unsigned int lastDotPos = path.rfind(".");
    unsigned int lastSlashPos = path.rfind(kPathSep);

    if (lastDotPos < path.size() - 1 && (lastDotPos > lastSlashPos || lastSlashPos == string::npos))
    {
        return path.substr(lastDotPos+1);
    }
    return "";
}

// --------------------------------------------------------------------------------------------------------
string kFileDirName ( const string & path )
{
	string native = kFileNativePath(path);
    unsigned int lastSlashPos = native.rfind(kPathSep);
    if (lastSlashPos < native.size())
    {
        return native.substr(0, lastSlashPos+1);
    }
    return string(".") + kPathSep;
}

// --------------------------------------------------------------------------------------------------------
string kFileBaseName ( const string & path, bool removeSuffix )
{
	string native = kFileNativePath(path);
    string baseName = native;
    unsigned int lastSlashPos = native.rfind(kPathSep);
    if (lastSlashPos < native.size() - 1) 
    {
        baseName = native.substr(lastSlashPos+1);
    }
    else if (lastSlashPos == native.size() - 1)
    {
        return "";
    }
    
    if (removeSuffix)
    {
        string suffix = kFileSuffix(baseName);
        baseName = baseName.substr(0, baseName.size()-suffix.size()-1);
    }
    
    return baseName;
}

// --------------------------------------------------------------------------------------------------------
bool kFileGetDirEntries ( const string & path, vector<string> & entries, bool listDotFiles )
{
	string dirPath = kFileAbsPathName((path == "") ? "." : path); //(path == "") ? "." : path;
    if (kFileIsDir(dirPath) == false) return false;

#ifdef WIN32
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;
	bool finished = false;

	hSearch = FindFirstFile((dirPath + "\\*").c_str(), &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{ 
		return false;
	} 

	while (!finished) 
	{  
		if (listDotFiles || FileData.cFileName[0] != '.')
		{
			entries.push_back(string(FileData.cFileName));
		}

		if (!FindNextFile(hSearch, &FileData)) 
		{
			finished = TRUE; 
		}
	} 
 
	// Close the search handle. 
 
	FindClose(hSearch);

	return true;
#else
    int fd = open (dirPath.c_str(), O_RDONLY | O_NONBLOCK);
    
    struct stat sb;
    long   basep;
    char * entry;
            
    if (fstat(fd, &sb) == -1)
    {
        KConsole::printError(kStringPrintf
            ("file error:\nunable to read stats of directory\n'%s'", path.c_str()));
        close (fd); return false;
    }
    
    entry = (char*)malloc(sb.st_blksize);
    if (entry == NULL)
    {
        KConsole::printError(kStringPrintf
            ("file error:\nunable to allocate memory for directory entries\n'%s'", path.c_str()));
        close(fd); return false;
    }
    
    int bytesRead;
    while ((bytesRead = getdirentries(fd, entry, sb.st_blksize, &basep)) > 0)
    {
        int pos = 0;
        while (pos < bytesRead)
        {
            struct dirent * entryPtr = (struct dirent *)(entry+pos);
            string filename = entryPtr->d_name;
            
            if ((listDotFiles == false && filename[0] == '.') || 
                filename == "." || filename == ".." || (filename == "dev" && dirPath[0] == kPathSep))
            {
            }
            else
            {
                entries.push_back(filename);
            }
            pos += entryPtr->d_reclen;
        }
    }
    
    free (entry);
    close(fd);
    return true;
#endif
}

// --------------------------------------------------------------------------------------------------------
string kFileReadStringFromFile ( const string & filename, unsigned int numCharacters )
{
    if (filename == "") return "";
    string filePath = kFileSubstitutePath(filename);

    string xml;
    
    FILE * file = fopen (filePath.c_str(), "r");
    if (file == NULL)
    {
        KConsole::printError(kStringPrintf("could not open file '%s'\n", filePath.c_str()));
        return "";
    }
    
    unsigned int charactersRead = 0;
    char character;
    while ((numCharacters == 0 || charactersRead < numCharacters) && 
            fread (&character, sizeof(char), 1, file) != 0)
    {
        xml += character;
        charactersRead++;
    }
    if (ferror(file))
    {
        KConsole::printError(kStringPrintf("error reading from file '%s'", filePath.c_str()));
	fclose (file);
	return "";
    }
    
    return xml;
}

// --------------------------------------------------------------------------------------------------------
bool kFileWriteStringToFile ( const string & xml, const string & filename )
{    
    string filePath = kFileSubstitutePath(filename);
    
    FILE * file = fopen (filePath.c_str(), "w+");
    if (file == NULL)
    {
        KConsole::printError (kStringPrintf("could not open file '%s'", filePath.c_str()));
        return false;
    }

    if (fwrite (xml.c_str(), xml.size(), sizeof(char), file) == 0)
    {
        KConsole::printError (kStringPrintf("could not write to file '%s'", filePath.c_str()));
        if (file) fclose (file);
        return false;
    }

    fclose (file);
    
    return true;
}


