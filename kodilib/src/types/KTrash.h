/*
 *  KTrash.h
 *  kodisein
 */

#ifndef __KTrash
#define __KTrash

#include <vector>

class KObject;

class KTrash
{
    static std::vector<KObject*> trash_can;
    
    public:
    
                                ~KTrash		() { recycle(); }
                                    
    static void			addObject	( KObject * );
    static void			recycle		();	
};

#endif

