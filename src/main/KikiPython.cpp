/*
 *  KikiPython.cpp
 *  kiki
 */

#include "KikiPython.h"
#include "KikiWorld.h"
#include "KikiBot.h"
#include "KikiPy_wrap.h"
#include "KikiPythonWidget.h"

#include <KConsole.h>
#include <KIconButton.h>
#include <KTextField.h>
#include <KScrollBar.h>
#include <KFileTools.h>

// __________________________________________________________________________________________________
KikiPython::KikiPython () : KWindow ()
{
    depth 	  = INT_MAX-9; // one above console 

    // ................................................................. editor and scrollbar array
    KWidgetArray * editorArray = new KWidgetArray();
    editorArray->setFrameSpacing	(0);
    editorArray->setChildSpacing	(2);

    // ................................................................. python editor widget
    python_widget = new KikiPythonWidget();
    addPickable(python_widget);

    python_widget->setTextSize(KSize(20,20));
    //python_widget->setMinSize(python_widget->getSize());
    python_widget->KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    python_widget->KWidget::flags[KDL_WIDGET_FLAG_FILL_Y] = true;
    
    // ................................................................. scrollbar
    scroll_bar = new KScrollBar(this);

    scroll_bar->addReceiverCallback(python_widget, (KSetFloatPtr)&KikiPythonWidget::scrollRelative);
    scroll_bar->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollLineDown,
                                            KDL_NOTIFICATION_TYPE_SCROLL_LINE_DOWN);
    scroll_bar->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollLineUp,
                                            KDL_NOTIFICATION_TYPE_SCROLL_LINE_UP);
    scroll_bar->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollPageDown,
                                            KDL_NOTIFICATION_TYPE_SCROLL_PAGE_DOWN);
    scroll_bar->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollPageUp,
                                            KDL_NOTIFICATION_TYPE_SCROLL_PAGE_UP);
    scroll_bar->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollPageUp,
                                            KDL_NOTIFICATION_TYPE_SCROLL_PAGE_UP);
    
    // insert into widget array
    editorArray->addChild(python_widget);
    editorArray->addChild(scroll_bar);
    
    // ................................................................. buttons
    KButton * button;
    button = new KIconButton(KDL_ICONBUTTON_CLEAR);
    button->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::clear);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(KDL_ICONBUTTON_TOP);
    button->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollToTop);
    button_widget->addChild(button);
    addPickable(button);

    button = new KIconButton(KDL_ICONBUTTON_BOTTOM);
    button->addReceiverCallback(python_widget, (KCallbackPtr)&KikiPythonWidget::scrollToBottom);
    button_widget->addChild(button);
    addPickable(button);

    // ................................................................. titel
    titel_label = new KLabel("");
    button_widget->addChild(titel_label);

    // ................................................................. input line
    KWidgetArray * inputArray = new KWidgetArray();
    inputArray->setFrameSpacing	(0);
    inputArray->setChildSpacing	(2);

    input_label = new KLabel("");
    input_label->KWidget::flags[KDL_WIDGET_FLAG_FIXED_SIZE] = false;

    input_field = new KTextField("");
    addPickable(input_field);
    input_field->setMinSize(KSize(0,0));
    input_field->KWidget::flags[KDL_WIDGET_FLAG_FILL_X] = true;
    input_field->KWidget::flags[KDL_WIDGET_FLAG_FIXED_SIZE] = false;
    input_field->KWidget::flags[KDL_TEXTFIELD_FLAG_NOTIFY_ON_UNPICK] = false;
    input_field->addReceiverCallback(this, (KSetStringPtr)&KikiPython::userInput);

    inputArray->addChild(input_label);
    inputArray->addChild(new KLabel (":"));
    inputArray->addChild(input_field);
    
    widget->addChild(editorArray);
    widget->addChild(inputArray);
    widget->layout();
    widget->hide();
    
    Controller.addPickHandler(this);
}

// __________________________________________________________________________________________________
void KikiPython::initPython ()
{
#if defined(__APPLE__) && defined(__MACH__)
    //putenv ("PYTHONDEBUG=1");
    //putenv ("PYTHONVERBOSE=1");
    putenv ("PYTHONPATH=./py:../Frameworks/Python.framework/Versions/A/lib/python2.2");
#endif

    Py_Initialize();

    std::string kikipy_path = kFileCleanPath(Controller.getKikiHome() + "py/kiki.py");
    
    init_kiki();
    
    FILE * pythonFile = fopen (kikipy_path.c_str(), "r");
    
    if (pythonFile)
    {
        if (PyRun_SimpleFile (pythonFile, (char *)kikipy_path.c_str()) == 0)
        {
            // ........................................................ python environment    
            executeFile (kFileCleanPath (Controller.getKikiHome() + "py/env.py"));
            python_widget->initPython();
        }
        else
        {
            KConsole::printError (kStringPrintf("KikiPython::initPython error while executing %s", kikipy_path.c_str()));
        }
    }
    else
    {
        KConsole::printError (kStringPrintf("KikiPython::initPython unable to open %s", kikipy_path.c_str()));
    }
}

// __________________________________________________________________________________________________
KikiPython::~KikiPython ()
{
    Controller.removePickHandler(this);
}

// __________________________________________________________________________________________________
void KikiPython::finalize ()
{
    Py_Finalize();
}

// --------------------------------------------------------------------------------------------------------
void KikiPython::setScrollBarUnits ( int currentLine, int lines )
{
    scroll_bar->setUnits( currentLine, python_widget->getTextRows(), lines);
}

// --------------------------------------------------------------------------------------------------------
void KikiPython::setTitle ( const std::string & t )
{
    titel_label->setText(t);
}

// --------------------------------------------------------------------------------------------------------
void KikiPython::setStatus ( const std::string & t )
{
    input_field->setSize(KSize(0,0));
    input_label->setText(t);
    widget->layout();
}

// --------------------------------------------------------------------------------------------------------
void KikiPython::setInput ( const std::string & t )
{
    input_field->setText(t);
}

// --------------------------------------------------------------------------------------------------------
void KikiPython::requestUserInput ( const std::string & message )
{
    python_widget->setPicked(false);
    input_field->setPicked(true);
    input_field->setSize(KSize(0,0));
    input_label->setText(message);
    input_field->selectAll();
}

// --------------------------------------------------------------------------------------------------------
void KikiPython::userInput ( const std::string & input)
{
    input_field->setPicked(false);
    python_widget->setPicked(true);
    execute(kStringPrintf("pythonConsole.userInput('%s')\n", input.c_str()));
}

// __________________________________________________________________________________________________
void KikiPython::setVisibility ( bool v )
{
    KWindow::setVisibility(v);
    python_widget->setPicked(v);
}

// __________________________________________________________________________________________________
void KikiPython::close ()
{
    KWindow::close();
    python_widget->setPicked(false);
}

// __________________________________________________________________________________________________
bool KikiPython::execute ( const std::string & pythonCode, bool eval )
{
    PyObject * mainModule, * mainDict;
    mainModule = PyImport_AddModule("__main__");
    
    if (mainModule == NULL)
    {
        KConsole::printError("KikiPython::execute no __main__ module");
	return false;
    }
    
    mainDict = PyModule_GetDict(mainModule);

    PyObject * result = PyRun_String((char*)pythonCode.c_str(), eval ? Py_eval_input : Py_file_input, 
                                        mainDict, mainDict);
    
    if (result == NULL)
    {
        KConsole::printError(kStringPrintf("KikiPython::execute '%s'", pythonCode.c_str()));
        PyErr_Print();
        return false;
    }
    
    bool retval = PyObject_IsTrue(result);
    
    Py_DECREF(result);

    return retval;
}

// __________________________________________________________________________________________________
bool KikiPython::executeFile ( const std::string & pythonFile )
{
    FILE * filePtr = fopen(pythonFile.c_str(), "r");
    if (filePtr)
    {
        return (PyRun_SimpleFile(filePtr, (char *)pythonFile.c_str()) == 0);
    }
    else
    {
        KConsole::printError(kStringPrintf("KikiPython::executeFile unable to open file '%s'", 
                                                                            pythonFile.c_str()));
    }
    return false;
}

