/*
 *  KikiPyAction.h
 *  kiki
 */

#ifndef __KikiPyAction
#define __KikiPyAction

#include "KikiAction.h"

#include <Python.h>

// --------------------------------------------------------------------------------------------------------
class KikiPyAction : public KikiAction
{
    protected: // ..................................................................... PROTECTED
    
    PyObject *	python_object;
    PyObject *	python_self;
        
    public: // ........................................................................ PUBLIC
                KikiPyAction	( PyObject * self, PyObject * object, const std::string & name, int duration = 0, 
                                    int mode = KikiAction::CONTINUOUS);
                ~KikiPyAction	();
                        
    void	init		();
    void	perform		();
    void	finish		();
    void	finished	();
};

#endif

