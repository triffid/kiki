/*
 *  KFileHandler.h
 *  kodisein
 */
 
#ifndef __KFileHandler
#define __KFileHandler

#include <string>
#include <vector>

class KFileHandler
{
    protected:
    
    static std::vector<std::string> current_dir_stack;

    public:

    static void		init			();
    static bool		changeCurrentDir	( const std::string & );
    static bool		pushCurrentDir		( const std::string & );  
    static void		popCurrentDir		();
    static std::string	getCurrentDir		();
};

#endif
