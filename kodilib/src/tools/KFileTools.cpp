/*
 *  KFileTools.cpp
 *  kodisein
 */

#include "KFileTools.h"
#include "KConsole.h"
#include "KStringTools.h"

#include <fcntl.h>     	// open

#ifndef WIN32
#	include <unistd.h>    	// close, chdir & getcwd
#	include <dirent.h>	// getdirentries
#	include <sys/param.h>	// MAXPATHLEN
#else
#	include <windows.h>
#	include <io.h>
#	define MAXPATHLEN MAX_PATH
#	define O_NONBLOCK 0
#	include <direct.h>
#	define getwd(x) getcwd(x, MAXPATHLEN)
#endif

#include <sys/types.h> 	// stat
#include <sys/stat.h>

#include <SDL_image.h>

// --------------------------------------------------------------------------------------------------------
std::string kFileCleanPath ( const std::string & path )
{
#ifdef WIN32
    std::string str(path);
    kStringReplace (str, "/", "\\");
    return str;
#endif
    return path;
}

// --------------------------------------------------------------------------------------------------------
std::string kFileGetCurrentPath ()
{
    char buffer[MAXPATHLEN+1];
    return getwd(buffer);
}

// --------------------------------------------------------------------------------------------------------
std::string kFileSubstitutePath ( const std::string & path )
{
    std::string filePath;
    if (path[0] == '~')
    {
        filePath = getenv("HOME") + path.substr(1);
    }
    else
    {
        filePath = path;
    }

    return filePath;
}

// --------------------------------------------------------------------------------------------------------
bool kFileExists ( const std::string & path )
{
    int fd = open (kFileSubstitutePath(path).c_str(), O_RDONLY | O_NONBLOCK);
    if (fd >= 0)
    {
        close(fd); 
        return true;
    }
    return false;
}

// --------------------------------------------------------------------------------------------------------
bool kFileIsFile ( const std::string & path )
{
    if (kFileExists(path) == false) return false;
    return !kFileIsDir(path);
}

// --------------------------------------------------------------------------------------------------------
bool kFileIsImageFile ( const std::string & filename )
{
    if (kFileIsFile(filename) == false) 
    {
        return false;
    }
    std::string suffix = kFileSuffix(filename);
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
bool kFileIsDir ( const std::string & path )
{
    std::string filePath = kFileSubstitutePath(path);
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
}

// --------------------------------------------------------------------------------------------------------
std::string kFileAbsPathName ( const std::string & path )
{
    if (path.size() == 0) return "";
    std::string filePath = kFileSubstitutePath(path);

    if (kFileExists(filePath) == false) return "";
    
#ifndef _WIN32
	char buffer[MAXPATHLEN+1];
    char * result = realpath (filePath.c_str(), buffer);
#else
	const char * result = filePath.c_str();
#endif
    if (result) return result;
    return "";
}

// --------------------------------------------------------------------------------------------------------
std::string kFileSuffix ( const std::string & path )
{
    unsigned int lastDotPos = path.rfind(".");
    unsigned int lastSlashPos = path.rfind("/");

    if (lastDotPos < path.size() - 1 && (lastDotPos > lastSlashPos || lastSlashPos == std::string::npos))
    {
        return path.substr(lastDotPos+1);
    }
    return "";
}

// --------------------------------------------------------------------------------------------------------
std::string kFileDirName ( const std::string & path )
{
    unsigned int lastSlashPos = path.rfind("/");
    if (lastSlashPos < path.size())
    {
        return path.substr(0, lastSlashPos+1);
    }
    return "./";
}

// --------------------------------------------------------------------------------------------------------
std::string kFileBaseName ( const std::string & path, bool removeSuffix )
{
    std::string baseName = path;
    unsigned int lastSlashPos = path.rfind("/");
    if (lastSlashPos < path.size() - 1) 
    {
        baseName = path.substr(lastSlashPos+1);
    }
    else if (lastSlashPos == path.size() - 1)
    {
        return "";
    }
    
    if (removeSuffix)
    {
        std::string suffix = kFileSuffix(baseName);
        baseName = baseName.substr(0, baseName.size()-suffix.size()-1);
    }
    
    return baseName;
}

// --------------------------------------------------------------------------------------------------------
bool kFileGetDirEntries ( const std::string & path, std::vector<std::string> & entries, bool listDotFiles )
{
    std::string dirPath = kFileAbsPathName((path == "") ? "." : path); //(path == "") ? "." : path;
    if (kFileIsDir(dirPath) == false) return false;

    int fd = open (dirPath.c_str(), O_RDONLY | O_NONBLOCK);
    
    struct stat sb;
            
    if (fstat(fd, &sb) == -1)
    {
        KConsole::printError(kStringPrintf
            ("file error:\nunable to read stats of directory\n'%s'", path.c_str()));
        close (fd); return false;
    }

#ifndef _WIN32 

    long   basep;
    char * entry = (char*)malloc(sb.st_blksize);

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
            std::string filename = entryPtr->d_name;
            
            if ((listDotFiles == false && filename[0] == '.') || 
                filename == "." || filename == ".." || (filename == "dev" && dirPath == "/"))
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
#endif
    close(fd);
    return true;
}

// --------------------------------------------------------------------------------------------------------
std::string kFileReadStringFromFile ( const std::string & filename, unsigned int numCharacters )
{
    if (filename == "") return "";
    std::string filePath = kFileSubstitutePath(filename);

    std::string xml;
    
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
bool kFileWriteStringToFile ( const std::string & xml, const std::string & filename )
{    
    std::string filePath = kFileSubstitutePath(filename);
    
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


