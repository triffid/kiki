/*
 *  KFileNameField.cpp
 *  kodisein
 */

#include "KFileNameField.h"
#include "KFileHandler.h"
#include "KFileTools.h"
#include "KKey.h"
#include "KConsole.h"

#include <algorithm>

#define DEBUG false

KDL_CLASS_INTROSPECTION_1 (KFileNameField, KTextField)

// --------------------------------------------------------------------------------------------------------
KFileNameField::KFileNameField ( const std::string & fn ) : KTextField (fn)
{
    KWidget::flags.resize(KDL_FILENAMEFIELD_FLAG_END);
    KWidget::flags[KDL_FILENAMEFIELD_FLAG_OPEN_FILE_MODE] = false;
    
    last_dir = ".!@#$%^&}";
}

// --------------------------------------------------------------------------------------------------------
bool KFileNameField::handleKey ( const KKey & key )
{
    selection_color.setValues(0.0, 0.0, 1.0, 0.25);
    
    if (current_dir_path == "")
    {
        // nobody set the current dir -> get it from file handler
        current_dir_path = KFileHandler::getCurrentDir ();
    }
    
    if (key.sym == SDLK_TAB) // completion
    {
        std::string croppedPath = text.substr(0, cursor_pos); // path before cursor
        std::string restPath; 				 // path behind cursor
        
        // map cropped path to current directory and rest path to file prefix
        unsigned int lastSlashPos = croppedPath.rfind("/");
        if (lastSlashPos < croppedPath.size()-1)
        {
            restPath = croppedPath.substr(lastSlashPos+1);
            croppedPath.erase(lastSlashPos+1);
        }
        else if (lastSlashPos == std::string::npos)
        {
            restPath = croppedPath;
            croppedPath = "";
        }
        
        // now, rest path contains the prefix that is to complete
        // and cropped path the absolute or relative path
        // of the directory which is to search for possible completions

        KConsole::debugf(DEBUG, "KFileNameField::handleKey croppedPath %s", croppedPath.c_str());

        // store absolute path in searchDir
        std::string searchDir = kFileSubstitutePath(croppedPath); // replaces leading ~
        if (searchDir[0] != '/') // no absolute path -> prepend current_dir_path
        {
            searchDir = current_dir_path + "/" + searchDir;
        } 

        KConsole::debugf(DEBUG, "KFileNameField::handleKey current_dir_path %s", current_dir_path.c_str());
        KConsole::debugf(DEBUG, "KFileNameField::handleKey searchDir %s", searchDir.c_str());
        KConsole::debugf(DEBUG, "KFileNameField::handleKey last_dir %s", last_dir.c_str());

        if (last_dir != searchDir) // directory changed since last completion
        {
            KConsole::debugf(DEBUG, "KFileNameField::handleKey tab new dir");
            dir_entries.clear();
            
            // get entries of new directory
            if (kFileGetDirEntries(searchDir, dir_entries))             
            {
                KConsole::debugf(DEBUG, "KFileNameField::handleKey setting last_dir to searchDir");
                last_dir = searchDir;
            }
            else 
            {
                return true;
            }
        }

        // ............................collect list of entries in searchDir that match prefix restPath
        unsigned int restLength = restPath.size();
        std::vector<std::string> matchingEntries;
        std::vector<std::string>::iterator iter = dir_entries.begin();
        while (iter != dir_entries.end())
        {
            if (iter->compare((unsigned int)0, restLength, restPath) == 0)
            {
                matchingEntries.push_back(*iter);
            }
            iter++;
        }
        
        int numMatches = matchingEntries.size();
        
        KConsole::debugf(DEBUG, "KFileNameField::handleKey found %d matches for prefix %s", numMatches, restPath.c_str());
        
        if (numMatches == 0) // no matches, reset path to croppedPath (last valid path part)
        {
            setText(croppedPath);
        }
        else if (numMatches == 1) // exactly one match -> if directory, append slash
        {
            KConsole::debugf(DEBUG, "KFileNameField::handleKey matchingEntries[0] %s", matchingEntries[0].c_str());
            if (kFileIsDir(searchDir+matchingEntries[0]))
            {
                KConsole::debugf(DEBUG, "KFileNameField::handleKey matchingEntry is dir");
                setText(croppedPath+matchingEntries[0]+"/");
            }
            else
            {
                KConsole::debugf(DEBUG, "KFileNameField::handleKey matchingEntry is file");
                setText(croppedPath+matchingEntries[0]);
                notifyReceivers(text, KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED);
            }
        }
        else // more than one match
        {
            std::string sharedPrefix = kStringGetSharedPrefix(matchingEntries);
            if (sharedPrefix != restPath)
            {
                setText(croppedPath+sharedPrefix);
            }
            else
            {
                std::string selection = getSelection();
                std::vector<std::string>::iterator lastPos;
				lastPos = std::find (matchingEntries.begin(), matchingEntries.end(), sharedPrefix+selection);
                if (key.mod & KMOD_SHIFT) 
                {
                    lastPos--; 
                }
                else 
                {
                    lastPos++;
                }
                if (lastPos >= matchingEntries.end()) 
                {
                    lastPos = matchingEntries.begin();
                }
                else if (lastPos < matchingEntries.begin()) 
                {
                    lastPos = matchingEntries.end()-1;
                }
                
                int saveCursorPos = cursor_pos;
                setText(croppedPath+(*lastPos));
                cursor_pos = saveCursorPos;
                notifyReceivers(text, KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED);
            }
        }
        
        update();
        return true;
    }
    else if (key.sym == SDLK_RETURN)
    {
        // store absolute path in currentPath
        std::string currentPath = kFileSubstitutePath(text); // replaces leading ~
        if (currentPath[0] != '/') // no absolute path -> prepend current_dir_path
        {
            currentPath = current_dir_path + "/" + currentPath;
        } 

        KConsole::debugf(DEBUG, "KFileNameField::handleKey RETURN currentPath %s", currentPath.c_str());
        KConsole::debugf(DEBUG, "KFileNameField::handleKey RETURN exists %d", kFileExists(currentPath));
    
        // file doesn't exist && open mode -> highlight last path component in red
        if (kFileExists(currentPath) == false && KWidget::flags[KDL_FILENAMEFIELD_FLAG_OPEN_FILE_MODE])
        {
            KConsole::debugf(DEBUG, "KFileNameField::handleKey red alert!");
            selection_color.setValues(1.0, 0.5, 0.0, 0.5);
            selectLastPathComponent();
            return true;
        }

        if (kFileIsDir(currentPath)) // file exists and is directory ...
        {
            KConsole::debugf(DEBUG, "KFileNameField::handleKey is dir");
            if (KWidget::flags[KDL_FILENAMEFIELD_FLAG_SELECT_DIR_MODE] == false)
            {
                if (text == "" || text == ".") // switch to absolute mode if current directory
                {
                    KConsole::debugf(DEBUG, "KFileNameField::handleKey switch to absolute");
                    setText(kFileAbsPathName(currentPath));
                    return true;
                }
                
                // change to directory
                KConsole::debugf(DEBUG, "KFileNameField::handleKey switch to relative");
                setText("");
                notifyReceivers(kFileAbsPathName(currentPath), KDL_NOTIFICATION_TYPE_CURRENT_DIRECTORY_CHANGED);
            }
            else // notify receivers in select directory mode
            {
                KConsole::debugf(DEBUG, "KFileNameField::handleKey notify (dir)");
                setPicked(false);
                notify();
            }
        }
        else // file is file or (it doesn't exists and not in open mode)
        {
            KConsole::debugf(DEBUG, "KFileNameField::handleKey notify (file)");
            setPicked(false);
            notify();
        }
        
        return true;
    }

    return KTextField::handleKey (key);
}

// --------------------------------------------------------------------------------------------------------
void KFileNameField::selectLastPathComponent ()
{
    unsigned int lastSlashPos = text.rfind("/");
    if (lastSlashPos == text.size()-1) lastSlashPos = text.rfind("/", lastSlashPos-1);
    if (lastSlashPos < text.size()) cursor_pos = lastSlashPos+1;
    else cursor_pos = 0;
    selection_pos = text.size();
}
