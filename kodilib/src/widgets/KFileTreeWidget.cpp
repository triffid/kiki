/*
 *  KFileTreeWidget.cpp
 *  kodisein
 */

#include "KFileTreeWidget.h"
#include "KFileTreeDirCurrent.h"
#include "KFileTreeDirUp.h"
#include "KEventHandler.h"
#include "KPerspectiveProjection.h"
#include "KPopupMenu.h"
#include "KSubMenuItem.h"
#include "KStatusMenuItem.h"
#include "KConsole.h"
#include "KFileTools.h"

KDL_CLASS_INTROSPECTION_2 (KFileTreeWidget, KProjectionWidget, KNotificationObject)

// --------------------------------------------------------------------------------------------------------
KFileTreeWidget::KFileTreeWidget () : KProjectionWidget ()
{
    display_list	= 0;
    popup_menu		= NULL;
    current_dir_node	= NULL;
    up_node 		= new KFileTreeDirUp (); 
    projection->setEyeDistance(6.0);
    projection->translate(0.0, 1.0, 0.0);
    
    KPickHandler::flags[KDL_PICKHANDLER_FLAG_FOCUS_ON_ENABLED] 		= true;
    KPickHandler::flags[KDL_PICKHANDLER_FLAG_MENU_ENABLED]     		= true;
    KPickHandler::flags[KDL_PICKHANDLER_FLAG_AUTOUNPICK_ENABLED] 	= false;
}

// --------------------------------------------------------------------------------------------------------
KFileTreeWidget::~KFileTreeWidget () 
{
    if (current_dir_node) 
    {
        delete current_dir_node;
    }
    delete up_node;
    deleteDisplayList();
}

// --------------------------------------------------------------------------------------------------------
std::string KFileTreeWidget::getCurrentDir () const
{
    if (current_dir_node)
    {	
        return current_dir_node->getAbsPathName();
    }
    return kFileAbsPathName(".");
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::setCurrentDir ( const std::string & dirName )
{
    std::string absDirPath;
    
    if (dirName[0] == '.' && current_dir_node) 
    {
        // path relative to the current directory should begin with a dot
        absDirPath = current_dir_node->getAbsPathName() + "/" + dirName;
    }
    else
    {
        absDirPath = kFileAbsPathName(dirName);
    }

    if (kFileIsDir(absDirPath) && (current_dir_node == NULL || (current_dir_node->getAbsPathName() != absDirPath)))
    {
        removeAllPickables();
        if (current_dir_node) 
        {
            delete current_dir_node;
        }
        current_dir_node = new KFileTreeDirCurrent(absDirPath);
        
        addPickable(up_node);
        addPickable(current_dir_node);
        current_dir_node->createTree();
        up_node->setCurrentDir(current_dir_node);
        initializeIds();
        deleteDisplayList();
        
        notifyReceivers (current_dir_node->getAbsPathName(), KDL_NOTIFICATION_TYPE_OPEN_DIRECTORY);
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::refresh ()
{
    if (current_dir_node) // redisplay the current directory
    {
        std::string currentDirPath = current_dir_node->getAbsPathName();
        removeAllPickables();
        delete current_dir_node;
        current_dir_node = NULL;
        setCurrentDir(currentDirPath);
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::doubleClicked ()
{
    if (picked_pickable == current_dir_node) return;
    if (((KFileTreeNode*)picked_pickable)->getType() == KDL_FILE_TYPE_DIR)
    {
        setCurrentDir (((KFileTreeNode*)picked_pickable)->getAbsPathName());
    }
    else
    {
        notifyReceivers (((KFileTreeNode*)picked_pickable)->getAbsPathName(), KDL_NOTIFICATION_TYPE_OPEN_FILE);
        notifyReceivers ();
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::picked ()
{
    deleteDisplayList();
    notifyReceivers (((KFileTreeNode*)picked_pickable)->getPathName(), KDL_NOTIFICATION_TYPE_SELECT_NODE);
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::unpicked ()
{
    deleteDisplayList();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::deleteDisplayList ()
{
    if (display_list)
    {
        glDeleteLists(display_list, 1);
        display_list = 0;
    }
}

// --------------------------------------------------------------------------------------------------------
bool KFileTreeWidget::pick ( const KMouseEvent & event )
{
    if (KWidget::flags[KDL_WIDGET_FLAG_VISIBLE] == false) return false;
    
    KPosition mouseWidgetPos = event.pos - getScreenPos();

    if ((mouseWidgetPos.x > 0) && (mouseWidgetPos.x < size.w) && 
        (mouseWidgetPos.y > 0) && (mouseWidgetPos.y < size.h))
    {
        deleteDisplayList();
        getWindow()->unpick();
	KPickHandler::pick(event);
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::displayContent ()
{
    if (current_dir_node == NULL) return; 
    
    if (display_list)
    {
        glCallList(display_list);
        return;
    }

    display_list = glGenLists(1);
    if (display_list)
    {
        glNewList(display_list, GL_COMPILE_AND_EXECUTE);
    }
    
    if (kFileAbsPathName(current_dir_node->getName()) != "/")
    {
        up_node->display();
    }
    
    current_dir_node->display();
    
    if (display_list)
    {
        glEndList();
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::setShowDotFiles ( bool b )
{
    if (KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_SHOW_DOTFILES] != b)
    {
        KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_SHOW_DOTFILES] = b;
        refresh();
    }
}

// --------------------------------------------------------------------------------------------------------
bool KFileTreeWidget::getShowDotFiles () const
{
    return KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_SHOW_DOTFILES];
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::setShowCubes ( bool b )
{
    if (KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_SHOW_CUBES] != b)
    {
        KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_SHOW_CUBES] = b;
        refresh();
    }
}

// --------------------------------------------------------------------------------------------------------
bool KFileTreeWidget::getShowCubes () const
{
    return KFileTreeDir::flags[KDL_FILETREEDIR_FLAG_SHOW_CUBES];
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::menuCallback ( const std::string & itemText )
{
    if (itemText == "show more")
    {
        KFileTreeDir::max_path_depth++;
        refresh();
        return;
    }
    else if (itemText == "show less")
    {
        if (KFileTreeDir::max_path_depth <= 1) return;
        KFileTreeDir::max_path_depth--;
        refresh();
        return;
    }    

    KFileTreeDir * dir;
    if (picked_pickable)
    {
        if (((KFileTreeNode*)picked_pickable)->getType() == KDL_FILE_TYPE_DIR)
        {
            dir = (KFileTreeDir*)picked_pickable;
    
            if (itemText == "cd")
            {
                if (dir != current_dir_node) 
                {
                    setCurrentDir(dir->getAbsPathName());
                }
                return;
            }
            else if (itemText == "show texture(s)")
            {
            }
        }
        else
        {
            if (itemText == "show texture(s)")
            {
                
            }
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::displayMenu ()
{
    if (popup_menu == NULL)
    {
        KMenuItem * item;
        popup_menu = new KPopupMenu();

        popup_menu->addMenuItem(item = new KMenuItem ("cd"));
        item->addReceiverCallback((KWidget*)this, 
                (KSetStringPtr)(void (KWidget::*)(const std::string &))&KFileTreeWidget::menuCallback );

        popup_menu->addMenuItem(item = new KMenuItem ("show more"));
        item->addReceiverCallback((KWidget*)this, 
                (KSetStringPtr)(void (KWidget::*)(const std::string &))&KFileTreeWidget::menuCallback );

        popup_menu->addMenuItem(item = new KMenuItem ("show less"));
        item->addReceiverCallback((KWidget*)this,
                (KSetStringPtr)(void (KWidget::*)(const std::string &))&KFileTreeWidget::menuCallback );
        
        popup_menu->addMenuItem(item = new KStatusMenuItem ("hide dotfiles", "show dotfiles"));
        item->addReceiverCallback((KWidget*)this, 
                (KSetBoolPtr)(void (KWidget::*)(bool))&KFileTreeWidget::setShowDotFiles );
        item->setProviderCallback((KWidget*)this, 
                (KGetBoolPtr)(bool (KWidget::*)(void) const)&KFileTreeWidget::getShowDotFiles );
        
        popup_menu->addMenuItem(item = new KStatusMenuItem ("hide cubes", "show cubes"));
        item->addReceiverCallback((KWidget*)this, 
                (KSetBoolPtr)(void (KWidget::*)(bool))&KFileTreeWidget::setShowCubes );
        item->setProviderCallback((KWidget*)this, 
                (KGetBoolPtr)(bool (KWidget::*)(void) const)&KFileTreeWidget::getShowCubes );

        popup_menu->addMenuItem(item = new KMenuItem ("show texture(s)"));
        item->addReceiverCallback((KWidget*)this, (KSetStringPtr)(void (KWidget::*)(const std::string &))&KFileTreeWidget::menuCallback );

        
        popup_menu->layout();
        popup_menu->initializeIds();
    }

    KPosition popupPos = getWindow()->mapScreenPos(KEventHandler::getMousePos());
    popupPos.y -= KDL_MENU_DEFAULT_ITEM_HEIGHT;

    popup_menu->setPosition(popupPos);
    popup_menu->show();
}

// --------------------------------------------------------------------------------------------------------
void KFileTreeWidget::focusOnPickedPickable ( bool zoom )
{
    if (picked_pickable == NULL) return;
    projection->focusOn(((KFileTreeNode*)picked_pickable)->getPosition());
    if (zoom) projection->setEyeDistance(2.0);
}

