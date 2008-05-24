#
# kodilib for linux
#
#
# you might have to change these to match your system
#

X11_INCLUDES = -I /usr/X11/include
SDL_INCLUDES = -I /usr/include/SDL
SDL_CFLAGS = -D_REENTRANT

#
# the following should be ok on most machines
#
# please let me know, if you had a hard time compiling kodilib (monsterkodi@gmx.net)
#

KODISRCDIR = ../src

KODI_INCLUDES = -I $(KODISRCDIR)/handler -I $(KODISRCDIR)/tools -I $(KODISRCDIR)/types -I $(KODISRCDIR)/widgets -I $(KODISRCDIR)/windows

INCLUDES = $(KODI_INCLUDES) $(X11_INCLUDES) $(SDL_INCLUDES)

CXXOPTS = $(INCLUDES) $(SDL_CFLAGS) $(CXXFLAGS)

src =  \
	$(KODISRCDIR)/handler/KEventHandler.cpp \
	$(KODISRCDIR)/handler/KFileHandler.cpp \
	$(KODISRCDIR)/handler/KKeyActionHandler.cpp \
	$(KODISRCDIR)/handler/KKeyHandler.cpp \
	$(KODISRCDIR)/handler/KKeyRecorder.cpp \
	$(KODISRCDIR)/handler/KPickable.cpp \
	$(KODISRCDIR)/handler/KPickHandler.cpp \
	$(KODISRCDIR)/handler/KSelectable.cpp \
	$(KODISRCDIR)/handler/KSelectionHandler.cpp \
	$(KODISRCDIR)/tools/KDisplayTools.cpp \
	$(KODISRCDIR)/tools/KFileTools.cpp \
	$(KODISRCDIR)/tools/KIntrospection.cpp \
	$(KODISRCDIR)/tools/KKeyTools.cpp \
	$(KODISRCDIR)/tools/KNotificationObject.cpp \
	$(KODISRCDIR)/tools/KStringTools.cpp \
	$(KODISRCDIR)/tools/KXMLTools.cpp \
	$(KODISRCDIR)/types/KKey.cpp \
	$(KODISRCDIR)/types/KLight.cpp \
	$(KODISRCDIR)/types/KLightingProjection.cpp \
	$(KODISRCDIR)/types/KMatrix.cpp \
	$(KODISRCDIR)/types/KOrthographicProjection.cpp \
	$(KODISRCDIR)/types/KPerspectiveProjection.cpp \
	$(KODISRCDIR)/types/KProjection.cpp \
	$(KODISRCDIR)/types/KQuaternion.cpp \
	$(KODISRCDIR)/types/KSeparatedMatrix.cpp \
	$(KODISRCDIR)/types/KTexture.cpp \
	$(KODISRCDIR)/types/KTrash.cpp \
	$(KODISRCDIR)/widgets/KButton.cpp \
	$(KODISRCDIR)/widgets/KButtonBox.cpp \
	$(KODISRCDIR)/widgets/KFileNameField.cpp \
	$(KODISRCDIR)/widgets/KFileTreeFile.cpp \
	$(KODISRCDIR)/widgets/KFileTreeDir.cpp \
	$(KODISRCDIR)/widgets/KFileTreeDirCurrent.cpp \
	$(KODISRCDIR)/widgets/KFileTreeDirUp.cpp \
	$(KODISRCDIR)/widgets/KFileTreeNode.cpp \
	$(KODISRCDIR)/widgets/KFileTreeWidget.cpp \
	$(KODISRCDIR)/widgets/KIconButton.cpp \
	$(KODISRCDIR)/widgets/KKeySequenceField.cpp \
	$(KODISRCDIR)/widgets/KLabel.cpp \
	$(KODISRCDIR)/widgets/KMenu.cpp \
	$(KODISRCDIR)/widgets/KMenuItem.cpp \
	$(KODISRCDIR)/widgets/KNumberField.cpp \
	$(KODISRCDIR)/widgets/KProjectionWidget.cpp \
	$(KODISRCDIR)/widgets/KScrollBar.cpp \
	$(KODISRCDIR)/widgets/KSliderButton.cpp \
	$(KODISRCDIR)/widgets/KStatusMenuItem.cpp \
	$(KODISRCDIR)/widgets/KSubMenuItem.cpp \
	$(KODISRCDIR)/widgets/KTextField.cpp \
	$(KODISRCDIR)/widgets/KTextWidget.cpp \
	$(KODISRCDIR)/widgets/KToggleButton.cpp \
	$(KODISRCDIR)/widgets/KWidget.cpp \
	$(KODISRCDIR)/widgets/KWidgetArray.cpp \
	$(KODISRCDIR)/windows/KConsole.cpp \
	$(KODISRCDIR)/windows/KFileTreeWindow.cpp \
	$(KODISRCDIR)/windows/KMenuWindow.cpp \
	$(KODISRCDIR)/windows/KMessagePanel.cpp \
	$(KODISRCDIR)/windows/KPopupMenu.cpp \
	$(KODISRCDIR)/windows/KWindow.cpp

obj = $(src:.cpp=.o)

libkodi.a: $(obj)
	$(AR) r $@ $(filter-out %.h, $^)

obj-clean:
	$(RM) -f $(obj)

clean:
	$(RM) -f $(obj) libkodi.a

%.o:    %.cpp
	$(CXX) -c $(CXXOPTS) -o $@ $<
