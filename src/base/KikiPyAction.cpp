/*
 *  KikiPyAction.cpp
 *  kiki
 */

#include "KikiPyAction.h"
#include "KikiEvent.h"

#include <KConsole.h>

// --------------------------------------------------------------------------------------------------------
KikiPyAction::KikiPyAction ( PyObject * self, PyObject * object, const std::string & name, int duration, int mode )
    : KikiAction (NULL, 0, name, duration, mode)
{
    python_self   = self;
    python_object = object;
    Py_INCREF(python_object);
}

// --------------------------------------------------------------------------------------------------------
KikiPyAction::~KikiPyAction ()
{
    Py_DECREF(python_object); 
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::init ()
{ 
    Py_INCREF(python_self);
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::perform ()
{
    PyObject * result = NULL;
    if (PyFunction_Check(python_object))
    {
        result = PyObject_CallFunctionObjArgs (python_object, NULL);
    }
    else if (PyMethod_Check(python_object))
    {
        result = PyObject_CallFunctionObjArgs (PyMethod_Function(python_object), 
                                               PyMethod_Self(python_object), NULL); 
    }
    else if (PyInstance_Check(python_object))
    {
        result = PyObject_CallMethod (python_object, "performAction", "sf", action_name.c_str(),
                                                                            getRelativeTime());
    }
    if (result)
    {
        Py_DECREF(result);
    }
    else
    {
        KConsole::printError (kStringPrintf ("KikiPyAction::perform failed \"%s\"", action_name.c_str()));        
        PyErr_Print();
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::finish ()
{
    if (PyObject_TypeCheck(python_object, &PyInstance_Type))
    {
        if (PyObject_CallMethod(python_object, "finishAction", "s", action_name.c_str()) == NULL)
        {
            KConsole::printError("KikiPyAction::finish failed");
        }
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::finished ()
{ 
    if (PyObject_TypeCheck(python_object, &PyInstance_Type))
    {
        if (PyObject_CallMethod(python_object, "actionFinished", "s", action_name.c_str()) == NULL)
        {
            KConsole::printError("KikiPyAction::finished failed");
        }
    }
    reset();
   
    if (mode == KikiAction::ONCE)
    {
        Py_DECREF(python_self);
    }
}

