
// __________________________________________________________________________________________________
%nodefault;

class KikiMutant : public KikiBot
{
    public: // ........................................................................ PUBLIC
                        KikiMutant	();
    void		die		();
    static void		setObjectColor	( const char * color_name, const KColor & color );
};
