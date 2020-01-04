#!/bin/sh

swig -c++ -python -modern -py3 -o KikiPy_wrap.cpp KikiPy.i
cp kiki.py ../py
