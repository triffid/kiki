
Building kodilib on Linux

Prerequisites

  kodilib depends on some libraries and development tools which have
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

    If you install the binary packages, make sure you get the
    development versions: package-names ending with '-devel' or '-dev'.


Building the kodilib

  enter make.
  If you are lucky, the library will be build immediately,
  otherwise you might have to adjust the paths at the top
  of the Makefile. On success, the library will be
  created kodilib/linux/libkodi.a




  