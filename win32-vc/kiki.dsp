# Microsoft Developer Studio Project File - Name="kiki" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=kiki - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "kiki.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "kiki.mak" CFG="kiki - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "kiki - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "kiki - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kiki - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\kodilib\src\windows" /I "..\kodilib\src\widgets" /I "..\kodilib\src\types" /I "..\kodilib\src\handler" /I "..\kodilib\src\tools" /I "..\SWIG" /I "..\src\base" /I "..\src\bots" /I "..\src\gui" /I "..\src\items" /I "..\src\main" /I "..\src\sound" /I "..\src\world" /I "..\kodilib\win32-vc" /I "..\kodilib\win32-vc\SDL\include" /I "..\kodilib\win32-vc\SDL_mixer\include" /I "..\kodilib\win32-vc\SDL_image\include" /I "C:\Python\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kodilib.lib python23.lib SDL.lib SDLmain.lib SDL_image.lib SDL_mixer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /libpath:"../kodilib/win32-vc/Release/" /libpath:"../kodilib/win32-vc/GLUT" /libpath:"../kodilib/win32-vc/SDL/lib" /libpath:"../kodilib/win32-vc/SDL_image/lib" /libpath:"../kodilib/win32-vc/SDL_mixer/lib" /libpath:"C:\Python\libs"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\kodilib\win32-vc\SDL\lib\SDL.dll Release	copy ..\kodilib\win32-vc\SDL_image\lib\*.dll Release	copy ..\kodilib\win32-vc\SDL_mixer\lib\SDL_mixer.dll Release	copy ..\kodilib\win32-vc\GLUT\glut32.dll Release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /I "..\kodilib\src\windows" /I "..\kodilib\src\widgets" /I "..\kodilib\src\types" /I "..\kodilib\src\handler" /I "..\kodilib\src\tools" /I "..\SWIG" /I "..\src\base" /I "..\src\bots" /I "..\src\gui" /I "..\src\items" /I "..\src\main" /I "..\src\sound" /I "..\src\world" /I "..\kodilib\win32-vc" /I "..\kodilib\win32-vc\SDL\include" /I "..\kodilib\win32-vc\SDL_mixer\include" /I "..\kodilib\win32-vc\SDL_image\include" /I "C:\Python\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kodilib.lib python23.lib SDL.lib SDLmain.lib SDL_image.lib SDL_mixer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../kodilib/win32-vc/Debug/" /libpath:"../kodilib/win32-vc/GLUT" /libpath:"../kodilib/win32-vc/SDL/lib" /libpath:"../kodilib/win32-vc/SDL_image/lib" /libpath:"../kodilib/win32-vc/SDL_mixer/lib" /libpath:"C:\Python\libs"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\kodilib\win32-vc\SDL\lib\SDL.dll Debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "kiki - Win32 Release"
# Name "kiki - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "base"

# PROP Default_Filter ""
# Begin Group "base_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\base\KikiAction.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiActionObject.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiBase.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiColorObject.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiEvent.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiFace.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiObject.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiObjectHeader.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiPos.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiPyAction.h
# End Source File
# Begin Source File

SOURCE=..\src\base\KikiTools.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\base\KikiAction.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\base\KikiActionObject.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\base\KikiEvent.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\base\KikiFace.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\base\KikiObject.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\base\KikiPyAction.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\base\KikiTools.cpp

!IF  "$(CFG)" == "kiki - Win32 Release"

!ELSEIF  "$(CFG)" == "kiki - Win32 Debug"

# ADD CPP /I "..\base" /I "..\bots" /I "..\gui"

!ENDIF 

# End Source File
# End Group
# Begin Group "bots"

# PROP Default_Filter ""
# Begin Group "bots_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\bots\body.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiBot.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiBotFume.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiBots.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiBotStatus.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiMutant.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiPlayback.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiPlayer.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiRecorder.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiStatusDisplay.h
# End Source File
# Begin Source File

SOURCE=..\src\bots\tire.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\bots\KikiBot.cpp
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiBotFume.cpp
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiMutant.cpp
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiPlayback.cpp
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiRecorder.cpp
# End Source File
# Begin Source File

SOURCE=..\src\bots\KikiStatusDisplay.cpp
# End Source File
# End Group
# Begin Group "gui"

# PROP Default_Filter ""
# Begin Group "gui_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\gui\KikiCharacter.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiColumnMenu.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiGUI.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiMenu.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiPageText.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiScreenText.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiScrollMenu.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiText.h
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiTextLine.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\gui\KikiCharacter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiColumnMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiGUI.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiPageText.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiScreenText.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiScrollMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiText.cpp
# End Source File
# Begin Source File

SOURCE=..\src\gui\KikiTextLine.cpp
# End Source File
# End Group
# Begin Group "items"

# PROP Default_Filter ""
# Begin Group "items_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\items\cylinder.h
# End Source File
# Begin Source File

SOURCE=..\src\items\gear.h
# End Source File
# Begin Source File

SOURCE=..\src\items\generator.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiAtom.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiBillBoard.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiBomb.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiBullet.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiCellText.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiGate.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiGear.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiGenerator.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiItems.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiLight.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiMotorCylinder.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiMotorGear.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiNeutron.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiPushable.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiSpikes.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiStone.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiSwitch.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiTest.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiValve.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiWall.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiWire.h
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiWireStone.h
# End Source File
# Begin Source File

SOURCE=..\src\items\kolben.h
# End Source File
# Begin Source File

SOURCE=..\src\items\motor.h
# End Source File
# Begin Source File

SOURCE=..\src\items\valve.h
# End Source File
# Begin Source File

SOURCE=..\src\items\wire.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\items\KikiAtom.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiBillBoard.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiBomb.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiBullet.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiCellText.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiGate.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiGear.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiLight.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiMotorCylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiMotorGear.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiNeutron.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiPushable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiSpikes.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiStone.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiSwitch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiTest.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiValve.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiWall.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiWire.cpp
# End Source File
# Begin Source File

SOURCE=..\src\items\KikiWireStone.cpp
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Group "main_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\main\Kiki.h
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiController.h
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiLocalization.h
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiMain.h
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiPython.h
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiPythonWidget.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\main\KikiController.cpp
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiPython.cpp
# End Source File
# Begin Source File

SOURCE=..\src\main\KikiPythonWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\src\main\main.cpp
# End Source File
# End Group
# Begin Group "sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\sound\KikiSound.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sound\KikiSound.h
# End Source File
# End Group
# Begin Group "world"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\world\KikiCell.cpp
# End Source File
# Begin Source File

SOURCE=..\src\world\KikiCell.h
# End Source File
# Begin Source File

SOURCE=..\src\world\KikiWorld.cpp
# End Source File
# Begin Source File

SOURCE=..\src\world\KikiWorld.h
# End Source File
# End Group
# Begin Group "kikipy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SWIG\KikiPy_wrap.cpp
# End Source File
# Begin Source File

SOURCE=..\SWIG\KikiPy_wrap.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\kiki.rc
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
