
// --------------------------------------------------------------------------------------------------------
class KikiAction
{ 
    public: // ........................................................................ PUBLIC
    
    enum {		ONCE, 
                        CONTINUOUS,
                        REPEAT };

                        KikiAction 		( KikiObject * object, int id,
                                                    const std::string & name, 
                                                    int duration = 0, 
                                                    int mode = KikiAction::ONCE );
                        KikiAction 		( KikiObject * object, 
                                                    int mode = KikiAction::ONCE );
 
    int		 	getId	 		() const;
    const std::string & getName 		() const;
    
    float		getRelativeTime		();
    float		getRelativeDelta	();
  
    int			getDuration		() const;
    void		setDuration		( int d );
};
