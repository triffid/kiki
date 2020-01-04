
// --------------------------------------------------------------------------------------------------------

class KikiPyAction : public KikiAction
{
    public: // ........................................................................ PUBLIC

            KikiPyAction 	( PyObject * pyself, PyObject * object, const std::string & name, 
                                    int duration = 0, int mode = KikiAction::CONTINUOUS );
            ~KikiPyAction	();

%pythoncode %{

    def __init__(self,*args):
        self.this = _kiki.new_KikiPyAction(self, *args)
        self.thisown = 1
    %}
};
