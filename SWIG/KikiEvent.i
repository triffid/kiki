
// --------------------------------------------------------------------------------------------------------
%nodefault;

class KikiEvent
{
    public: // ........................................................................ PUBLIC
                        KikiEvent		( KikiObject *, const std::string & name );
    
    void		addAction		( KikiAction * action );
    void		removeAction		( KikiAction * action );
    void		removeAllActions	();
    void		removeActionsOfObject	( KikiObject * object );
    void		removeActionWithName	( const std::string & actionName );
    
    void		triggerActions		();
    
    unsigned int	getTime			() const;
};
