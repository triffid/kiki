/*
 *  KikiRecorder.h
 *  kiki
 */

#ifndef __KikiRecorder
#define __KikiRecorder

#include <KKey.h>
#include <vector>

// __________________________________________________________________________________________________
typedef struct _KikiKeyRecord
{
    enum { KEY_PRESS, KEY_RELEASE, OTHER };
    
                        _KikiKeyRecord ( unsigned int t, const std::string keyName, bool r = KEY_PRESS ) 
                                        { time = t; key_name = keyName; type = r ? 1 : 0; }
                        _KikiKeyRecord ( const std::string str ) 
                                        { key_name = str; type = OTHER; }
                        
    int 		type;
    unsigned int	time;
    std::string		key_name;
    
} KikiKeyRecord;

// __________________________________________________________________________________________________
class KikiRecorder
{
    public: // ........................................................................ PUBLIC
    
                KikiRecorder	( const std::string & file );
    
    void	recordKey	( const KKey & key );
    void	recordKeyRelease( const KKey & key );

    void	save		();
    void	reset		();
    
    protected: // ..................................................................... PROTECTED
    
    unsigned int start_time;

    std::string file_name;
    std::vector<KikiKeyRecord*> key_records;
};

#endif
