#!/bin/sh

swig -c++ -python -o KikiPy_wrap.cpp KikiPy.i
cp kiki.py ../py
