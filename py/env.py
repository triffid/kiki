from __future__ import nested_scopes

# .................................................................................................................
#................................ imports

import sys
import os
import re
import getpass

# .................................................................................................................
#................................ redirect interpreter output to console

sys.stdout = KConsole
sys.stderr = KConsole

# print '[env.py]'

# .................................................................................................................
#................................ globals

true  = 1
false = 0

def minmax (minValue, maxValue, value):
    """returns the value if it lies in the range [minValue, maxValue], the range borders otherwise"""
    return max(minValue, min(maxValue, value))

# ................................................................................. disable interactive help

def help (request):
    """overrided help function to prevent accidentally using the interactive help, which would hang kikipy"""
    pydoc.help(request)

def dirn (arg):
    """prints the result of a dir(arg) call in seperate lines"""
    print "\n".join(dir(arg))
    
# .................................................................................................................
# ............................... shortcuts

Controller     = kiki.Controller
world          = Controller.world
sound          = Controller.sound
gui            = Controller.gui
console        = KConsole.getConsole()
kikipy_path    = Controller.getKikiHome() + "/py/"

# .................................................................................................................
# ............................... position and size of console

console.setSize ((0,0))
console.setPosition ((0,-325))
console.setSize ((1024,290))

# .................................................................................................................        
# ............................... some standard rotations

rot0    = KQuaternion()
rotz180 = KQuaternion.rotationAroundVector(180, KVector(0,0,1))
rotz90  = KQuaternion.rotationAroundVector(90,  KVector(0,0,1))
roty270 = KQuaternion.rotationAroundVector(270, KVector(0,1,0))
roty180 = KQuaternion.rotationAroundVector(180, KVector(0,1,0))
roty90  = KQuaternion.rotationAroundVector(90,  KVector(0,1,0))
roty0   = KQuaternion.rotationAroundVector(0,   KVector(0,1,0))
rotx180 = KQuaternion.rotationAroundVector(180, KVector(1,0,0))
rotx90  = KQuaternion.rotationAroundVector(90,  KVector(1,0,0))

# .................................................................................................................
# ............................... load files

execfile(kikipy_path + "world.py")