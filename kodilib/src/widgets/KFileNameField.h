/*
 *  KFileNameField.h
 *  kodisein
 */

#ifndef __KFileNameField
#define __KFileNameField

#include "KTextField.h"

enum {	KDL_FILENAMEFIELD_FLAG_OPEN_FILE_MODE = KDL_TEXTFIELD_FLAG_END,
        KDL_FILENAMEFIELD_FLAG_SELECT_DIR_MODE,
        KDL_FILENAMEFIELD_FLAG_END};

enum {	KDL_NOTIFICATION_TYPE_SELECTED_FILE_CHANGED = KDL_NOTIFICATION_TYPE_NOTIFICATION_END,
        KDL_NOTIFICATION_TYPE_CURRENT_DIRECTORY_CHANGED,
        KDL_NOTIFICATION_TYPE_FILENAMEFIELD_ACTIVATED,
        KDL_NOTIFICATION_TYPE_FILENAMEFIELD_END};

class KFileNameField : public KTextField
{
    INTROSPECTION
    
    protected:
    
    std::vector<std::string>	dir_entries;
    std::string		last_dir;
    std::string		current_dir_path;

    public:
                        KFileNameField		( const std::string & = "" );
                                
    void		selectLastPathComponent ();
    void		setCurrentDirPath	( const std::string & s ) { current_dir_path = s; setText(""); }
    bool		handleKey		( const KKey & );
};

#endif

