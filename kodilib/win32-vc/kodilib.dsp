# Microsoft Developer Studio Project File - Name="kodilib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=kodilib - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "kodilib.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "kodilib.mak" CFG="kodilib - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "kodilib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "kodilib - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kodilib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I ".\SDL\include" /I ".\SDL_image\include" /I "..\src\handler" /I "..\src\tools" /I "..\src\types" /I "..\src\windows" /I "..\src\widgets" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "kodilib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /I "." /I ".\SDL\include" /I ".\SDL_image\include" /I "..\src\handler" /I "..\src\tools" /I "..\src\types" /I "..\src\windows" /I "..\src\widgets" /D "_WIN32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "kodilib - Win32 Release"
# Name "kodilib - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\widgets\KButton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KButtonBox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\windows\KConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KDisplayTools.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KFileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileNameField.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KFileTools.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeDir.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeDirCurrent.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeDirUp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeFile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeNode.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\src\windows\KFileTreeWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KIconButton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KIntrospection.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KKey.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KKeyActionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KKeyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KKeyRecorder.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KKeySequenceField.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KKeyTools.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KLight.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KLightingProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\windows\KMenuWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\windows\KMessagePanel.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KNotificationObject.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KNumberField.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KOrthographicProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KPerspectiveProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KPickable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KPickHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\windows\KPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KProjectionWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KQuaternion.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KSelectable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handler\KSelectionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KSeparatedMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KSliderButton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KStatusMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KStringTools.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KSubMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KTextField.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KTextWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KToggleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\types\KTrash.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KWidgetArray.cpp
# End Source File
# Begin Source File

SOURCE=..\src\windows\KWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tools\KXMLTools.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\widgets\KButton.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KButtonBox.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KButtonSymbols.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KColor.h
# End Source File
# Begin Source File

SOURCE=..\src\windows\KConsole.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KDisplayTools.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KEventHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KFileHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileNameField.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KFileTools.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeDir.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeDirCurrent.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeDirUp.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeFile.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeNode.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KFileTreeWidget.h
# End Source File
# Begin Source File

SOURCE=..\src\windows\KFileTreeWindow.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KIconButton.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KIntrospection.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KKey.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KKeyActionHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KKeyHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KKeyRecorder.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KKeySequenceField.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KKeySymbols.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KKeyTools.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KLabel.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KLight.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KLightingProjection.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KMatrix.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KMenu.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\src\windows\KMenuWindow.h
# End Source File
# Begin Source File

SOURCE=..\src\windows\KMessagePanel.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KNotificationObject.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KNumberField.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KOrthographicProjection.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KPerspectiveProjection.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KPickable.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KPickHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\windows\KPopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KProjection.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KProjectionWidget.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KQuaternion.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KScrollBar.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KSelectable.h
# End Source File
# Begin Source File

SOURCE=..\src\handler\KSelectionHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KSeparatedMatrix.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KSliderButton.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KStatusMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KStringTools.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KSubMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KTextField.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KTexture.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KTextWidget.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KToggleButton.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KTools.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KTrash.h
# End Source File
# Begin Source File

SOURCE=..\src\types\KVector.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KWidget.h
# End Source File
# Begin Source File

SOURCE=..\src\widgets\KWidgetArray.h
# End Source File
# Begin Source File

SOURCE=..\src\windows\KWindow.h
# End Source File
# Begin Source File

SOURCE=..\src\tools\KXMLTools.h
# End Source File
# End Group
# End Target
# End Project
