/*
 *  KFileTreeDir.cpp
 *  kodisein
 */

#include "KFileTreeDir.h"
#include "KEventHandler.h"
#include "KFileTreeFile.h"
#include "KConsole.h"
#include "KFileHandler.h"
#include "KFileTools.h"
#include "KTools.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <dirent.h>
#include <sys/param.h>
#endif
#include <errno.h>

KDL_CLASS_INTROSPECTION_1 (KFileTreeDir, KFileTreeNode)

int	KFileTreeDir::max_path_depth = 3;
bool	KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_END] = { false, true };

// --------------------------------------------------------------------------------------------------------
KFileTreeDir::KFileTreeDir ( const KFileTreeDir * d, const std::string & n ) : KFileTreeNode (n)
{
    parent = d;
    if (n.find("kodisein") != std::string::npos) 
    {
        node_color.setValues (1.0, 0.5, 0.0, KDL_FILETREENODE_DEFAULT_ALPHA);
    }
    else if (n[0] == '.' && n != ".") 
    {
        node_color.setValues (0.0, 0.0, 0.5, KDL_FILETREENODE_DEFAULT_ALPHA);
    }
    else                             
    {
        node_color.setValues (0.0, 0.0, 1.0, KDL_FILETREENODE_DEFAULT_ALPHA);
    }

    type = KDL_FILE_TYPE_DIR;
    
    if (getPathLength() < max_path_depth) 
    {	
        createTree();
    }
}

// --------------------------------------------------------------------------------------------------------
KFileTreeDir::KFileTreeDir ( const std::string & n ) : KFileTreeNode (n)
{
    if (n[0] == '.' && n != ".") node_color.setValues (0.0, 0.0, 0.5, KDL_FILETREENODE_DEFAULT_ALPHA);
    else                         node_color.setValues (0.0, 0.0, 1.0, KDL_FILETREENODE_DEFAULT_ALPHA);
    type = KDL_FILE_TYPE_DIR;
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeDir::render ()
{
    kDisplaySolidSphere(0.5, (KEventHandler::flags[KDL_DISPLAY_MODE_FAST] ? 4 : 8));
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeDir::createTree ()
{
    std::vector<std::string> entries;
    std::string pathName = getAbsPathName();
    if (kFileGetDirEntries(pathName, entries, flags[KDL_FILETREEDIR_FLAG_SHOW_DOTFILES]))
    {
        std::vector<std::string>::iterator iter = entries.begin();
        while (iter != entries.end())
        {
            if (kFileIsDir(pathName + "/" + (*iter)))
            {
                addChild (new KFileTreeDir(this, (*iter)));
            }
            else
            {
                std::string suffix = kFileSuffix((*iter));
                if (flags[KDL_FILETREEDIR_FLAG_SHOW_CUBES] || suffix == "kds" || suffix == "kts" ||
                    suffix == "tga" || suffix == "tif" || suffix == "jpg" || suffix == "png" || suffix == "gif")
                {
                    addChild (new KFileTreeFile(this, (*iter)));
                }
            }
            iter++;
        }
    }
}

