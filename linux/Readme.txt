
Building kiki on Linux

Prerequisites

  kiki depends on some libraries and development tools which have
  to be installed on your system before you will be able to build it.
  I will just list these dependencies here,
  please check the net or your distribution's documentation
  how to obtain and install these tools and libraries.

  Development Tools

    You will need a version 3 gcc compiler to build kiki.
    
    The environment variable CXX should point to the location
    of the c++-compiler, e.g: /usr/bin/g++-3.2
  
  SDL libraries

    SDL             http://www.libsdl.org
    SDL_image       http://www.libsdl.org/projects/SDL_image/
    SDL_mixer       http://www.libsdl.org/projects/SDL_mixer/

    If you install the binary packages, make sure you get the
    development versions: package-names ending with '-devel' or '-dev'.

  Python            http://www.python.org

    kiki works with python versions 2.2.x and 2.3a.x but it will
    probably work with older versions as well.
  
    You won't need it if you are just building the unchanged sources,
    but if interested, you could also obtain swig from
    
  SWIG              http://www.swig.org
    

Building the kodilib

  Go to the directory kiki_src/kodilib/linux and enter make.
  If you are lucky, the library will be build immediately,
  otherwise you might have to adjust the paths at the top
  of the Makefile. On success, the library will be
  created as kiki_src/kodilib/linux/libkodi.a

  
Building kiki

  Go back to the directory kiki_src/kiki/linux and enter make.
  Here you might have to adjust the Makefile as well.
  The executable will be named kiki and written to the linux
  directory which contains the Makefile.

  
Running kiki

  kiki depends on the resources found in kiki_src/kiki/py and
  kiki_src/kiki/sounds. You should set the environment variable
  KIKI_HOME to the directory which contains the subdirectories
  py and sounds, e.g. setenv KIKI_HOME kiki_src/kiki
  Otherwise you have to start kiki from this directory:

    kiki_src/kiki% linux/kiki
  
Installing kiki

  Sorry, but the Makefile contains no install target.
  Just move the executable and the resources manually wherever you like
  and adjust the KIKI_HOME variable accordingly.

Feedback

  Please let me know if you had problems compiling kiki and/or how it
  performed on your system.
  Send the feedback to monsterkodi@gmx.net

Have fun,
yours kodi

    



  