#
# kiki makefile for linux
#
#
# you might have to change these to match your system
#

PYTHON_INCLUDES = $(subst -specs=/usr/share/dpkg/no-pie-compile.specs,,$(shell python3-config --cflags))

SDLCFLAGS = $(shell sdl-config --cflags)
SDLLIBS = $(shell sdl-config --libs) $(shell pkg-config SDL_image SDL_mixer --libs)

GLCFLAGS = $(shell pkg-config glu --cflags)
GLLIBS = -lglut $(shell pkg-config glu gl --libs)

PYTHONLIBS = $(shell python3-config --ldflags --embed)

# change this, if the kodilib directory isn't parallel to the kiki directory

KODILIBDIR = ../kodilib

#
# the following should be ok on most machines
#
# please let me know, if you had a hard time compiling kiki (monsterkodi@gmx.net)
#

KODILIB = $(KODILIBDIR)/linux/libkodi.a

KODILIBINC =	-I $(KODILIBDIR)/src/handler \
		-I $(KODILIBDIR)/src/tools   \
		-I $(KODILIBDIR)/src/types   \
		-I $(KODILIBDIR)/src/widgets \
		-I $(KODILIBDIR)/src/windows

KIKISRC = ../src

KIKI_INCLUDES = -I ../SWIG $(KODILIBINC) \
	-I $(KIKISRC)/base -I $(KIKISRC)/bots -I $(KIKISRC)/gui -I $(KIKISRC)/items \
	-I $(KIKISRC)/main -I $(KIKISRC)/sound -I $(KIKISRC)/world \

INCLUDES = $(KIKI_INCLUDES) $(X11_INCLUDES) $(PYTHON_INCLUDES)

CXXOPTS = $(INCLUDES) $(SDLCFLAGS) $(CXXFLAGS) $(GLCFLAGS)

src =  \
	$(KIKISRC)/base/KikiAction.cpp \
	$(KIKISRC)/base/KikiActionObject.cpp \
	$(KIKISRC)/base/KikiEvent.cpp \
	$(KIKISRC)/base/KikiFace.cpp \
	$(KIKISRC)/base/KikiObject.cpp \
	$(KIKISRC)/base/KikiPyAction.cpp \
	$(KIKISRC)/base/KikiTools.cpp \
	$(KIKISRC)/bots/KikiBot.cpp \
	$(KIKISRC)/bots/KikiBotFume.cpp \
	$(KIKISRC)/bots/KikiMutant.cpp \
	$(KIKISRC)/bots/KikiPlayback.cpp \
	$(KIKISRC)/bots/KikiPlayer.cpp \
	$(KIKISRC)/bots/KikiRecorder.cpp \
	$(KIKISRC)/bots/KikiStatusDisplay.cpp \
	$(KIKISRC)/gui/KikiCharacter.cpp \
	$(KIKISRC)/gui/KikiColumnMenu.cpp \
	$(KIKISRC)/gui/KikiGUI.cpp \
	$(KIKISRC)/gui/KikiMenu.cpp \
	$(KIKISRC)/gui/KikiPageText.cpp \
	$(KIKISRC)/gui/KikiScreenText.cpp \
	$(KIKISRC)/gui/KikiScrollMenu.cpp \
	$(KIKISRC)/gui/KikiText.cpp \
	$(KIKISRC)/gui/KikiTextLine.cpp \
	$(KIKISRC)/items/KikiAtom.cpp \
	$(KIKISRC)/items/KikiBillBoard.cpp \
	$(KIKISRC)/items/KikiBomb.cpp \
	$(KIKISRC)/items/KikiBullet.cpp \
	$(KIKISRC)/items/KikiCellText.cpp \
	$(KIKISRC)/items/KikiGate.cpp \
	$(KIKISRC)/items/KikiGear.cpp \
	$(KIKISRC)/items/KikiGenerator.cpp \
	$(KIKISRC)/items/KikiLight.cpp \
	$(KIKISRC)/items/KikiMotorCylinder.cpp \
	$(KIKISRC)/items/KikiMotorGear.cpp \
	$(KIKISRC)/items/KikiNeutron.cpp \
	$(KIKISRC)/items/KikiPushable.cpp \
	$(KIKISRC)/items/KikiSpikes.cpp \
	$(KIKISRC)/items/KikiStone.cpp \
	$(KIKISRC)/items/KikiSwitch.cpp \
	$(KIKISRC)/items/KikiTest.cpp \
	$(KIKISRC)/items/KikiValve.cpp \
	$(KIKISRC)/items/KikiWall.cpp \
	$(KIKISRC)/items/KikiWire.cpp \
	$(KIKISRC)/items/KikiWireStone.cpp \
	$(KIKISRC)/main/KikiController.cpp \
	$(KIKISRC)/main/main.cpp \
	$(KIKISRC)/sound/KikiSound.cpp \
	$(KIKISRC)/world/KikiCell.cpp \
	$(KIKISRC)/world/KikiWorld.cpp \
	$(KIKISRC)/main/KikiPythonWidget.cpp \
	$(KIKISRC)/main/KikiPython.cpp \
	$(KIKISRC)/../SWIG/KikiPy_wrap.cpp

obj = $(src:.cpp=.o)

kiki: $(KIKISRC)/../SWIG/KikiPy_wrap.cpp $(obj)
	$(CXX) $(CXXOPTS) $(obj) $(KODILIB) -o kiki $(GLLIBS) $(SDLLIBS) $(PYTHONLIBS)

$(KIKISRC)/../SWIG/KikiPy_wrap.cpp: $(wildcard ../SWIG/*.i)
	-(cd ../SWIG && swig -c++ -python -modern -py3 -globals kiki -o KikiPy_wrap.cpp KikiPy.i && cp kiki.py ../py)

obj-clean:
	$(RM) -f $(obj)

clean:
	$(RM) -f $(obj) kiki

%.o:    %.cpp
	$(CXX) -c $(CXXOPTS) -o $@ $<

