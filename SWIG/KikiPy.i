%module kiki
%{

#include "Kiki.h"

%}

// ......................................................... typemaps
%include "KikiPyTypemaps.i"

// ......................................................... export
%include KikiTypes.i
%include KikiAction.i
%include KikiPyAction.i
%include KikiEvent.i
%include KikiObject.i
%include KikiBot.i
%include KikiPlayer.i
%include KikiMutant.i
%include KikiSound.i
%include KikiWorld.i
%include KEventHandler.i
%include KikiController.i
%include KWindow.i
%include KikiText.i
%include KikiGUI.i
%include KikiItems.i
%include KConsole.i
%include KikiPython.i

