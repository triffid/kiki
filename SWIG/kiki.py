# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.
import _kiki
def _swig_setattr(self,class_type,name,value):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    self.__dict__[name] = value

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class KikiPos(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPos, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPos, name)
    __swig_setmethods__["x"] = _kiki.KikiPos_x_set
    __swig_getmethods__["x"] = _kiki.KikiPos_x_get
    if _newclass:x = property(_kiki.KikiPos_x_get,_kiki.KikiPos_x_set)
    __swig_setmethods__["y"] = _kiki.KikiPos_y_set
    __swig_getmethods__["y"] = _kiki.KikiPos_y_get
    if _newclass:y = property(_kiki.KikiPos_y_get,_kiki.KikiPos_y_set)
    __swig_setmethods__["z"] = _kiki.KikiPos_z_set
    __swig_getmethods__["z"] = _kiki.KikiPos_z_get
    if _newclass:z = property(_kiki.KikiPos_z_get,_kiki.KikiPos_z_set)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiPos,args)
        self.thisown = 1
    def __sub__(*args): return apply(_kiki.KikiPos___sub__,args)
    def __add__(*args): return apply(_kiki.KikiPos___add__,args)
    def __iadd__(*args): return apply(_kiki.KikiPos___iadd__,args)
    def __isub__(*args): return apply(_kiki.KikiPos___isub__,args)
    def getString(*args): return apply(_kiki.KikiPos_getString,args)
    def __eq__(*args): return apply(_kiki.KikiPos___eq__,args)
    def __ne__(*args): return apply(_kiki.KikiPos___ne__,args)
    def __str__(*args): return apply(_kiki.KikiPos___str__,args)
    def __del__(self, destroy= _kiki.delete_KikiPos):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C KikiPos instance at %s>" % (self.this,)

class KikiPosPtr(KikiPos):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPos
_kiki.KikiPos_swigregister(KikiPosPtr)

class KVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KVector, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KVector,args)
        self.thisown = 1
    def reset(*args): return apply(_kiki.KVector_reset,args)
    def normalize(*args): return apply(_kiki.KVector_normalize,args)
    def __iadd__(*args): return apply(_kiki.KVector___iadd__,args)
    def __isub__(*args): return apply(_kiki.KVector___isub__,args)
    def __imul__(*args): return apply(_kiki.KVector___imul__,args)
    def __idiv__(*args): return apply(_kiki.KVector___idiv__,args)
    def cross(*args): return apply(_kiki.KVector_cross,args)
    def __sub__(*args): return apply(_kiki.KVector___sub__,args)
    def __add__(*args): return apply(_kiki.KVector___add__,args)
    def __mul__(*args): return apply(_kiki.KVector___mul__,args)
    def __div__(*args): return apply(_kiki.KVector___div__,args)
    def perpendicular(*args): return apply(_kiki.KVector_perpendicular,args)
    def parallel(*args): return apply(_kiki.KVector_parallel,args)
    def reflect(*args): return apply(_kiki.KVector_reflect,args)
    def normal(*args): return apply(_kiki.KVector_normal,args)
    def length(*args): return apply(_kiki.KVector_length,args)
    def angle(*args): return apply(_kiki.KVector_angle,args)
    def xyangle(*args): return apply(_kiki.KVector_xyangle,args)
    def xyperp(*args): return apply(_kiki.KVector_xyperp,args)
    def round(*args): return apply(_kiki.KVector_round,args)
    def glVertex(*args): return apply(_kiki.KVector_glVertex,args)
    def __getitem__(*args): return apply(_kiki.KVector___getitem__,args)
    def __str__(*args): return apply(_kiki.KVector___str__,args)
    def __del__(self, destroy= _kiki.delete_KVector):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C KVector instance at %s>" % (self.this,)

class KVectorPtr(KVector):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KVector
_kiki.KVector_swigregister(KVectorPtr)

class KQuaternion(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KQuaternion, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KQuaternion, name)
    __swig_setmethods__["w"] = _kiki.KQuaternion_w_set
    __swig_getmethods__["w"] = _kiki.KQuaternion_w_get
    if _newclass:w = property(_kiki.KQuaternion_w_get,_kiki.KQuaternion_w_set)
    __swig_setmethods__["x"] = _kiki.KQuaternion_x_set
    __swig_getmethods__["x"] = _kiki.KQuaternion_x_get
    if _newclass:x = property(_kiki.KQuaternion_x_get,_kiki.KQuaternion_x_set)
    __swig_setmethods__["y"] = _kiki.KQuaternion_y_set
    __swig_getmethods__["y"] = _kiki.KQuaternion_y_get
    if _newclass:y = property(_kiki.KQuaternion_y_get,_kiki.KQuaternion_y_set)
    __swig_setmethods__["z"] = _kiki.KQuaternion_z_set
    __swig_getmethods__["z"] = _kiki.KQuaternion_z_get
    if _newclass:z = property(_kiki.KQuaternion_z_get,_kiki.KQuaternion_z_set)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KQuaternion,args)
        self.thisown = 1
    __swig_getmethods__["rotationAroundVector"] = lambda x: _kiki.KQuaternion_rotationAroundVector
    if _newclass:rotationAroundVector = staticmethod(_kiki.KQuaternion_rotationAroundVector)
    def rotate(*args): return apply(_kiki.KQuaternion_rotate,args)
    def normalize(*args): return apply(_kiki.KQuaternion_normalize,args)
    def invert(*args): return apply(_kiki.KQuaternion_invert,args)
    def conjugate(*args): return apply(_kiki.KQuaternion_conjugate,args)
    def getNormal(*args): return apply(_kiki.KQuaternion_getNormal,args)
    def getConjugate(*args): return apply(_kiki.KQuaternion_getConjugate,args)
    def getInverse(*args): return apply(_kiki.KQuaternion_getInverse,args)
    def length(*args): return apply(_kiki.KQuaternion_length,args)
    def glRotate(*args): return apply(_kiki.KQuaternion_glRotate,args)
    def slerp(*args): return apply(_kiki.KQuaternion_slerp,args)
    def __mul__(*args): return apply(_kiki.KQuaternion___mul__,args)
    def __str__(*args): return apply(_kiki.KQuaternion___str__,args)
    def __del__(self, destroy= _kiki.delete_KQuaternion):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C KQuaternion instance at %s>" % (self.this,)

class KQuaternionPtr(KQuaternion):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KQuaternion
_kiki.KQuaternion_swigregister(KQuaternionPtr)
KQuaternion_rotationAroundVector = _kiki.KQuaternion_rotationAroundVector


class KColor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KColor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KColor, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KColor,args)
        self.thisown = 1
    def setValues(*args): return apply(_kiki.KColor_setValues,args)
    def setRed(*args): return apply(_kiki.KColor_setRed,args)
    def setGreen(*args): return apply(_kiki.KColor_setGreen,args)
    def setBlue(*args): return apply(_kiki.KColor_setBlue,args)
    def setAlpha(*args): return apply(_kiki.KColor_setAlpha,args)
    def getRed(*args): return apply(_kiki.KColor_getRed,args)
    def getGreen(*args): return apply(_kiki.KColor_getGreen,args)
    def getBlue(*args): return apply(_kiki.KColor_getBlue,args)
    def getAlpha(*args): return apply(_kiki.KColor_getAlpha,args)
    def glColor(*args): return apply(_kiki.KColor_glColor,args)
    def __str__(*args): return apply(_kiki.KColor___str__,args)
    def __del__(self, destroy= _kiki.delete_KColor):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C KColor instance at %s>" % (self.this,)

class KColorPtr(KColor):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KColor
_kiki.KColor_swigregister(KColorPtr)

class KProjection(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KProjection, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KProjection, name)
    def focusOn(*args): return apply(_kiki.KProjection_focusOn,args)
    def setFov(*args): return apply(_kiki.KProjection_setFov,args)
    def getFov(*args): return apply(_kiki.KProjection_getFov,args)
    def setViewport(*args): return apply(_kiki.KProjection_setViewport,args)
    def setPosition(*args): return apply(_kiki.KProjection_setPosition,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KProjection instance at %s>" % (self.this,)

class KProjectionPtr(KProjection):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KProjection
_kiki.KProjection_swigregister(KProjectionPtr)

class KKey(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KKey, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KKey, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KKey,args)
        self.thisown = 1
    __swig_setmethods__["name"] = _kiki.KKey_name_set
    __swig_getmethods__["name"] = _kiki.KKey_name_get
    if _newclass:name = property(_kiki.KKey_name_get,_kiki.KKey_name_set)
    def getUnmodifiedName(*args): return apply(_kiki.KKey_getUnmodifiedName,args)
    def getModifierName(*args): return apply(_kiki.KKey_getModifierName,args)
    def __repr__(self):
        return "<C KKey instance at %s>" % (self.this,)

class KKeyPtr(KKey):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KKey
_kiki.KKey_swigregister(KKeyPtr)

class KikiAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiAction, name)
    ONCE = _kiki.KikiAction_ONCE
    CONTINUOUS = _kiki.KikiAction_CONTINUOUS
    REPEAT = _kiki.KikiAction_REPEAT
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiAction,args)
        self.thisown = 1
    def getId(*args): return apply(_kiki.KikiAction_getId,args)
    def getName(*args): return apply(_kiki.KikiAction_getName,args)
    def getRelativeTime(*args): return apply(_kiki.KikiAction_getRelativeTime,args)
    def getRelativeDelta(*args): return apply(_kiki.KikiAction_getRelativeDelta,args)
    def getDuration(*args): return apply(_kiki.KikiAction_getDuration,args)
    def setDuration(*args): return apply(_kiki.KikiAction_setDuration,args)
    def __repr__(self):
        return "<C KikiAction instance at %s>" % (self.this,)

class KikiActionPtr(KikiAction):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiAction
_kiki.KikiAction_swigregister(KikiActionPtr)

class KikiPyAction(KikiAction):
    __swig_setmethods__ = {}
    for _s in [KikiAction]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPyAction, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiAction]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPyAction, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiPyAction,args)
        self.thisown = 1
    def __del__(self, destroy= _kiki.delete_KikiPyAction):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __init__(self,*args):
        self.this = apply (_kiki.new_KikiPyAction, (self,) + args)
        self.thisown = 1


    def __repr__(self):
        return "<C KikiPyAction instance at %s>" % (self.this,)

class KikiPyActionPtr(KikiPyAction):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPyAction
_kiki.KikiPyAction_swigregister(KikiPyActionPtr)

class KikiEvent(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiEvent, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiEvent, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiEvent,args)
        self.thisown = 1
    def addAction(*args): return apply(_kiki.KikiEvent_addAction,args)
    def removeAction(*args): return apply(_kiki.KikiEvent_removeAction,args)
    def removeAllActions(*args): return apply(_kiki.KikiEvent_removeAllActions,args)
    def removeActionsOfObject(*args): return apply(_kiki.KikiEvent_removeActionsOfObject,args)
    def removeActionWithName(*args): return apply(_kiki.KikiEvent_removeActionWithName,args)
    def triggerActions(*args): return apply(_kiki.KikiEvent_triggerActions,args)
    def getTime(*args): return apply(_kiki.KikiEvent_getTime,args)
    def __repr__(self):
        return "<C KikiEvent instance at %s>" % (self.this,)

class KikiEventPtr(KikiEvent):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiEvent
_kiki.KikiEvent_swigregister(KikiEventPtr)

class KikiActionObject(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiActionObject, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiActionObject, name)
    def addAction(*args): return apply(_kiki.KikiActionObject_addAction,args)
    def removeAction(*args): return apply(_kiki.KikiActionObject_removeAction,args)
    def startTimedAction(*args): return apply(_kiki.KikiActionObject_startTimedAction,args)
    def startTimer(*args): return apply(_kiki.KikiActionObject_startTimer,args)
    def getActionWithName(*args): return apply(_kiki.KikiActionObject_getActionWithName,args)
    def getActionWithId(*args): return apply(_kiki.KikiActionObject_getActionWithId,args)
    def addEventWithName(*args): return apply(_kiki.KikiActionObject_addEventWithName,args)
    def getEventWithName(*args): return apply(_kiki.KikiActionObject_getEventWithName,args)
    def getEventWithId(*args): return apply(_kiki.KikiActionObject_getEventWithId,args)
    def getClassName(*args): return apply(_kiki.KikiActionObject_getClassName,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiActionObject instance at %s>" % (self.this,)

class KikiActionObjectPtr(KikiActionObject):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiActionObject
_kiki.KikiActionObject_swigregister(KikiActionObjectPtr)

class KikiObject(KikiActionObject):
    __swig_setmethods__ = {}
    for _s in [KikiActionObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiObject, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiActionObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiObject, name)
    def setName(*args): return apply(_kiki.KikiObject_setName,args)
    def getName(*args): return apply(_kiki.KikiObject_getName,args)
    def getPos(*args): return apply(_kiki.KikiObject_getPos,args)
    def setPosition(*args): return apply(_kiki.KikiObject_setPosition,args)
    def getPosition(*args): return apply(_kiki.KikiObject_getPosition,args)
    def setOrientation(*args): return apply(_kiki.KikiObject_setOrientation,args)
    def getOrientation(*args): return apply(_kiki.KikiObject_getOrientation,args)
    def setCurrentOrientation(*args): return apply(_kiki.KikiObject_setCurrentOrientation,args)
    def getCurrentOrientation(*args): return apply(_kiki.KikiObject_getCurrentOrientation,args)
    def isSpaceEgoistic(*args): return apply(_kiki.KikiObject_isSpaceEgoistic,args)
    def getClassName(*args): return apply(_kiki.KikiObject_getClassName,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiObject instance at %s>" % (self.this,)

class KikiObjectPtr(KikiObject):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiObject
_kiki.KikiObject_swigregister(KikiObjectPtr)

class KikiBotStatus(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBotStatus, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBotStatus, name)
    def getMoves(*args): return apply(_kiki.KikiBotStatus_getMoves,args)
    def setMoves(*args): return apply(_kiki.KikiBotStatus_setMoves,args)
    def addMoves(*args): return apply(_kiki.KikiBotStatus_addMoves,args)
    def getMinMoves(*args): return apply(_kiki.KikiBotStatus_getMinMoves,args)
    def setMinMoves(*args): return apply(_kiki.KikiBotStatus_setMinMoves,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiBotStatus instance at %s>" % (self.this,)

class KikiBotStatusPtr(KikiBotStatus):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiBotStatus
_kiki.KikiBotStatus_swigregister(KikiBotStatusPtr)

class KikiBotFume(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBotFume, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBotFume, name)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiBotFume_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiBotFume_setObjectColor)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiBotFume instance at %s>" % (self.this,)

class KikiBotFumePtr(KikiBotFume):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiBotFume
_kiki.KikiBotFume_swigregister(KikiBotFumePtr)
KikiBotFume_setObjectColor = _kiki.KikiBotFume_setObjectColor


class KikiBot(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBot, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBot, name)
    def isDead(*args): return apply(_kiki.KikiBot_isDead,args)
    def getDown(*args): return apply(_kiki.KikiBot_getDown,args)
    def getUp(*args): return apply(_kiki.KikiBot_getUp,args)
    def getDir(*args): return apply(_kiki.KikiBot_getDir,args)
    def setMove(*args): return apply(_kiki.KikiBot_setMove,args)
    def getStatus(*args): return apply(_kiki.KikiBot_getStatus,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiBot instance at %s>" % (self.this,)

class KikiBotPtr(KikiBot):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiBot
_kiki.KikiBot_swigregister(KikiBotPtr)

class KikiStatusDisplay(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiStatusDisplay, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiStatusDisplay, name)
    def show(*args): return apply(_kiki.KikiStatusDisplay_show,args)
    def hide(*args): return apply(_kiki.KikiStatusDisplay_hide,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiStatusDisplay instance at %s>" % (self.this,)

class KikiStatusDisplayPtr(KikiStatusDisplay):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiStatusDisplay
_kiki.KikiStatusDisplay_swigregister(KikiStatusDisplayPtr)

class KikiPlayback(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPlayback, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPlayback, name)
    __swig_getmethods__["start"] = lambda x: _kiki.KikiPlayback_start
    if _newclass:start = staticmethod(_kiki.KikiPlayback_start)
    __swig_getmethods__["stop"] = lambda x: _kiki.KikiPlayback_stop
    if _newclass:stop = staticmethod(_kiki.KikiPlayback_stop)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiPlayback instance at %s>" % (self.this,)

class KikiPlaybackPtr(KikiPlayback):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPlayback
_kiki.KikiPlayback_swigregister(KikiPlaybackPtr)
KikiPlayback_start = _kiki.KikiPlayback_start

KikiPlayback_stop = _kiki.KikiPlayback_stop


class KikiPlayer(KikiBot):
    __swig_setmethods__ = {}
    for _s in [KikiBot]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPlayer, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiBot]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPlayer, name)
    def die(*args): return apply(_kiki.KikiPlayer_die,args)
    def reborn(*args): return apply(_kiki.KikiPlayer_reborn,args)
    def reset(*args): return apply(_kiki.KikiPlayer_reset,args)
    def startRecorder(*args): return apply(_kiki.KikiPlayer_startRecorder,args)
    def saveRecorder(*args): return apply(_kiki.KikiPlayer_saveRecorder,args)
    def getProjection(*args): return apply(_kiki.KikiPlayer_getProjection,args)
    def handleKey(*args): return apply(_kiki.KikiPlayer_handleKey,args)
    def handleKeyRelease(*args): return apply(_kiki.KikiPlayer_handleKeyRelease,args)
    def recordKeyForAction(*args): return apply(_kiki.KikiPlayer_recordKeyForAction,args)
    __swig_getmethods__["getActionForKey"] = lambda x: _kiki.KikiPlayer_getActionForKey
    if _newclass:getActionForKey = staticmethod(_kiki.KikiPlayer_getActionForKey)
    __swig_getmethods__["getKeyForAction"] = lambda x: _kiki.KikiPlayer_getKeyForAction
    if _newclass:getKeyForAction = staticmethod(_kiki.KikiPlayer_getKeyForAction)
    __swig_getmethods__["setKeyForAction"] = lambda x: _kiki.KikiPlayer_setKeyForAction
    if _newclass:setKeyForAction = staticmethod(_kiki.KikiPlayer_setKeyForAction)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiPlayer_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiPlayer_setObjectColor)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiPlayer instance at %s>" % (self.this,)

class KikiPlayerPtr(KikiPlayer):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPlayer
_kiki.KikiPlayer_swigregister(KikiPlayerPtr)
KikiPlayer_getActionForKey = _kiki.KikiPlayer_getActionForKey

KikiPlayer_getKeyForAction = _kiki.KikiPlayer_getKeyForAction

KikiPlayer_setKeyForAction = _kiki.KikiPlayer_setKeyForAction

KikiPlayer_setObjectColor = _kiki.KikiPlayer_setObjectColor


class KikiMutant(KikiBot):
    __swig_setmethods__ = {}
    for _s in [KikiBot]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMutant, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiBot]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMutant, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiMutant,args)
        self.thisown = 1
    def die(*args): return apply(_kiki.KikiMutant_die,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMutant_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMutant_setObjectColor)
    def __repr__(self):
        return "<C KikiMutant instance at %s>" % (self.this,)

class KikiMutantPtr(KikiMutant):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiMutant
_kiki.KikiMutant_swigregister(KikiMutantPtr)
KikiMutant_setObjectColor = _kiki.KikiMutant_setObjectColor


class KikiSound(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiSound, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiSound, name)
    def toggleMute(*args): return apply(_kiki.KikiSound_toggleMute,args)
    def setMute(*args): return apply(_kiki.KikiSound_setMute,args)
    def isMute(*args): return apply(_kiki.KikiSound_isMute,args)
    def setSoundVolume(*args): return apply(_kiki.KikiSound_setSoundVolume,args)
    def getSoundVolume(*args): return apply(_kiki.KikiSound_getSoundVolume,args)
    def playSound(*args): return apply(_kiki.KikiSound_playSound,args)
    def playSoundAtPos(*args): return apply(_kiki.KikiSound_playSoundAtPos,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiSound instance at %s>" % (self.this,)

class KikiSoundPtr(KikiSound):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiSound
_kiki.KikiSound_swigregister(KikiSoundPtr)

class KikiWorld(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiWorld, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiWorld, name)
    CAMERA_INSIDE = _kiki.KikiWorld_CAMERA_INSIDE
    CAMERA_BEHIND = _kiki.KikiWorld_CAMERA_BEHIND
    CAMERA_FOLLOW = _kiki.KikiWorld_CAMERA_FOLLOW
    def setSize(*args): return apply(_kiki.KikiWorld_setSize,args)
    def getSize(*args): return apply(_kiki.KikiWorld_getSize,args)
    def setName(*args): return apply(_kiki.KikiWorld_setName,args)
    def getName(*args): return apply(_kiki.KikiWorld_getName,args)
    def init(*args): return apply(_kiki.KikiWorld_init,args)
    def setDisplayShadows(*args): return apply(_kiki.KikiWorld_setDisplayShadows,args)
    def setDisplayRaster(*args): return apply(_kiki.KikiWorld_setDisplayRaster,args)
    def setDisplayBorder(*args): return apply(_kiki.KikiWorld_setDisplayBorder,args)
    def setRasterSize(*args): return apply(_kiki.KikiWorld_setRasterSize,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWorld_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWorld_setObjectColor)
    def changeCameraMode(*args): return apply(_kiki.KikiWorld_changeCameraMode,args)
    def getCameraMode(*args): return apply(_kiki.KikiWorld_getCameraMode,args)
    def setCameraMode(*args): return apply(_kiki.KikiWorld_setCameraMode,args)
    def getProjection(*args): return apply(_kiki.KikiWorld_getProjection,args)
    def addObjectAtPos(*args): return apply(_kiki.KikiWorld_addObjectAtPos,args)
    def setObjectAtPos(*args): return apply(_kiki.KikiWorld_setObjectAtPos,args)
    def unsetObject(*args): return apply(_kiki.KikiWorld_unsetObject,args)
    def removeObject(*args): return apply(_kiki.KikiWorld_removeObject,args)
    def deleteObject(*args): return apply(_kiki.KikiWorld_deleteObject,args)
    def deleteAllObjects(*args): return apply(_kiki.KikiWorld_deleteAllObjects,args)
    def deleteObjectsWithClassName(*args): return apply(_kiki.KikiWorld_deleteObjectsWithClassName,args)
    def getObjectWithName(*args): return apply(_kiki.KikiWorld_getObjectWithName,args)
    def moveObjectToPos(*args): return apply(_kiki.KikiWorld_moveObjectToPos,args)
    def objectWillMoveToPos(*args): return apply(_kiki.KikiWorld_objectWillMoveToPos,args)
    def objectMovedFromPos(*args): return apply(_kiki.KikiWorld_objectMovedFromPos,args)
    def getBotAtPos(*args): return apply(_kiki.KikiWorld_getBotAtPos,args)
    def getOccupantAtPos(*args): return apply(_kiki.KikiWorld_getOccupantAtPos,args)
    def getRealOccupantAtPos(*args): return apply(_kiki.KikiWorld_getRealOccupantAtPos,args)
    def getNearestValidPos(*args): return apply(_kiki.KikiWorld_getNearestValidPos,args)
    def isInvalidPos(*args): return apply(_kiki.KikiWorld_isInvalidPos,args)
    def isValidPos(*args): return apply(_kiki.KikiWorld_isValidPos,args)
    def isUnoccupiedPos(*args): return apply(_kiki.KikiWorld_isUnoccupiedPos,args)
    def isOccupiedPos(*args): return apply(_kiki.KikiWorld_isOccupiedPos,args)
    def posToIndex(*args): return apply(_kiki.KikiWorld_posToIndex,args)
    def indexToPos(*args): return apply(_kiki.KikiWorld_indexToPos,args)
    def getPickedPos(*args): return apply(_kiki.KikiWorld_getPickedPos,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiWorld instance at %s>" % (self.this,)

class KikiWorldPtr(KikiWorld):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiWorld
_kiki.KikiWorld_swigregister(KikiWorldPtr)
KikiWorld_setObjectColor = _kiki.KikiWorld_setObjectColor


class KEventHandler(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KEventHandler, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KEventHandler, name)
    def quit(*args): return apply(_kiki.KEventHandler_quit,args)
    __swig_getmethods__["getMouseState"] = lambda x: _kiki.KEventHandler_getMouseState
    if _newclass:getMouseState = staticmethod(_kiki.KEventHandler_getMouseState)
    __swig_getmethods__["getMousePos"] = lambda x: _kiki.KEventHandler_getMousePos
    if _newclass:getMousePos = staticmethod(_kiki.KEventHandler_getMousePos)
    __swig_getmethods__["getMouseDelta"] = lambda x: _kiki.KEventHandler_getMouseDelta
    if _newclass:getMouseDelta = staticmethod(_kiki.KEventHandler_getMouseDelta)
    __swig_getmethods__["getScreenSize"] = lambda x: _kiki.KEventHandler_getScreenSize
    if _newclass:getScreenSize = staticmethod(_kiki.KEventHandler_getScreenSize)
    __swig_getmethods__["setScreenSize"] = lambda x: _kiki.KEventHandler_setScreenSize
    if _newclass:setScreenSize = staticmethod(_kiki.KEventHandler_setScreenSize)
    __swig_getmethods__["getFullscreen"] = lambda x: _kiki.KEventHandler_getFullscreen
    if _newclass:getFullscreen = staticmethod(_kiki.KEventHandler_getFullscreen)
    __swig_getmethods__["setFullscreen"] = lambda x: _kiki.KEventHandler_setFullscreen
    if _newclass:setFullscreen = staticmethod(_kiki.KEventHandler_setFullscreen)
    __swig_getmethods__["getTime"] = lambda x: _kiki.KEventHandler_getTime
    if _newclass:getTime = staticmethod(_kiki.KEventHandler_getTime)
    def setWireframeMode(*args): return apply(_kiki.KEventHandler_setWireframeMode,args)
    def setDisplayFps(*args): return apply(_kiki.KEventHandler_setDisplayFps,args)
    def getDisplayFps(*args): return apply(_kiki.KEventHandler_getDisplayFps,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KEventHandler instance at %s>" % (self.this,)

class KEventHandlerPtr(KEventHandler):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KEventHandler
_kiki.KEventHandler_swigregister(KEventHandlerPtr)
KEventHandler_getMouseState = _kiki.KEventHandler_getMouseState

KEventHandler_getMousePos = _kiki.KEventHandler_getMousePos

KEventHandler_getMouseDelta = _kiki.KEventHandler_getMouseDelta

KEventHandler_getScreenSize = _kiki.KEventHandler_getScreenSize

KEventHandler_setScreenSize = _kiki.KEventHandler_setScreenSize

KEventHandler_getFullscreen = _kiki.KEventHandler_getFullscreen

KEventHandler_setFullscreen = _kiki.KEventHandler_setFullscreen

KEventHandler_getTime = _kiki.KEventHandler_getTime


class KikiController(KEventHandler,KikiActionObject):
    __swig_setmethods__ = {}
    for _s in [KEventHandler,KikiActionObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiController, name, value)
    __swig_getmethods__ = {}
    for _s in [KEventHandler,KikiActionObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiController, name)
    __swig_setmethods__["gui"] = _kiki.KikiController_gui_set
    __swig_getmethods__["gui"] = _kiki.KikiController_gui_get
    if _newclass:gui = property(_kiki.KikiController_gui_get,_kiki.KikiController_gui_set)
    __swig_setmethods__["sound"] = _kiki.KikiController_sound_set
    __swig_getmethods__["sound"] = _kiki.KikiController_sound_get
    if _newclass:sound = property(_kiki.KikiController_sound_get,_kiki.KikiController_sound_set)
    __swig_setmethods__["world"] = _kiki.KikiController_world_set
    __swig_getmethods__["world"] = _kiki.KikiController_world_get
    if _newclass:world = property(_kiki.KikiController_world_get,_kiki.KikiController_world_set)
    __swig_setmethods__["player"] = _kiki.KikiController_player_set
    __swig_getmethods__["player"] = _kiki.KikiController_player_get
    if _newclass:player = property(_kiki.KikiController_player_get,_kiki.KikiController_player_set)
    __swig_setmethods__["python"] = _kiki.KikiController_python_set
    __swig_getmethods__["python"] = _kiki.KikiController_python_get
    if _newclass:python = property(_kiki.KikiController_python_get,_kiki.KikiController_python_set)
    __swig_setmethods__["player_status"] = _kiki.KikiController_player_status_set
    __swig_getmethods__["player_status"] = _kiki.KikiController_player_status_get
    if _newclass:player_status = property(_kiki.KikiController_player_status_get,_kiki.KikiController_player_status_set)
    __swig_setmethods__["timer_event"] = _kiki.KikiController_timer_event_set
    __swig_getmethods__["timer_event"] = _kiki.KikiController_timer_event_get
    if _newclass:timer_event = property(_kiki.KikiController_timer_event_get,_kiki.KikiController_timer_event_set)
    def getPlayer(*args): return apply(_kiki.KikiController_getPlayer,args)
    def unmapMsTime(*args): return apply(_kiki.KikiController_unmapMsTime,args)
    def mapMsTime(*args): return apply(_kiki.KikiController_mapMsTime,args)
    def setSpeed(*args): return apply(_kiki.KikiController_setSpeed,args)
    def getSpeed(*args): return apply(_kiki.KikiController_getSpeed,args)
    def getKikiHome(*args): return apply(_kiki.KikiController_getKikiHome,args)
    def setGamma(*args): return apply(_kiki.KikiController_setGamma,args)
    def getGamma(*args): return apply(_kiki.KikiController_getGamma,args)
    def displayText(*args): return apply(_kiki.KikiController_displayText,args)
    def getLocalizedString(*args): return apply(_kiki.KikiController_getLocalizedString,args)
    def isDebugVersion(*args): return apply(_kiki.KikiController_isDebugVersion,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiController instance at %s>" % (self.this,)

class KikiControllerPtr(KikiController):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiController
_kiki.KikiController_swigregister(KikiControllerPtr)

replaceTabs = _kiki.replaceTabs

class KWindow(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KWindow, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KWindow, name)
    def isVisible(*args): return apply(_kiki.KWindow_isVisible,args)
    def setVisibility(*args): return apply(_kiki.KWindow_setVisibility,args)
    def toggleVisibility(*args): return apply(_kiki.KWindow_toggleVisibility,args)
    def maximize(*args): return apply(_kiki.KWindow_maximize,args)
    def show(*args): return apply(_kiki.KWindow_show,args)
    def hide(*args): return apply(_kiki.KWindow_hide,args)
    def close(*args): return apply(_kiki.KWindow_close,args)
    def setSize(*args): return apply(_kiki.KWindow_setSize,args)
    def setPosition(*args): return apply(_kiki.KWindow_setPosition,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KWindow instance at %s>" % (self.this,)

class KWindowPtr(KWindow):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KWindow
_kiki.KWindow_swigregister(KWindowPtr)
kiki = _kiki.kiki

class KikiText(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiText, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiText, name)
    base_color = _kiki.KikiText_base_color
    bright_color = _kiki.KikiText_bright_color
    dark_color = _kiki.KikiText_dark_color
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiText,args)
        self.thisown = 1
    def setText(*args): return apply(_kiki.KikiText_setText,args)
    def getText(*args): return apply(_kiki.KikiText_getText,args)
    def clear(*args): return apply(_kiki.KikiText_clear,args)
    def isEmpty(*args): return apply(_kiki.KikiText_isEmpty,args)
    def addText(*args): return apply(_kiki.KikiText_addText,args)
    def getColor(*args): return apply(_kiki.KikiText_getColor,args)
    def setColor(*args): return apply(_kiki.KikiText_setColor,args)
    def setAlpha(*args): return apply(_kiki.KikiText_setAlpha,args)
    def isAnimated(*args): return apply(_kiki.KikiText_isAnimated,args)
    def setAnimated(*args): return apply(_kiki.KikiText_setAnimated,args)
    def isCentered(*args): return apply(_kiki.KikiText_isCentered,args)
    def setCentered(*args): return apply(_kiki.KikiText_setCentered,args)
    def getWidth(*args): return apply(_kiki.KikiText_getWidth,args)
    def getHeight(*args): return apply(_kiki.KikiText_getHeight,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiText_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiText_setObjectColor)
    def __repr__(self):
        return "<C KikiText instance at %s>" % (self.this,)

class KikiTextPtr(KikiText):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiText
_kiki.KikiText_swigregister(KikiTextPtr)
KikiText_setObjectColor = _kiki.KikiText_setObjectColor


class KikiGUI(KWindow):
    __swig_setmethods__ = {}
    for _s in [KWindow]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiGUI, name, value)
    __swig_getmethods__ = {}
    for _s in [KWindow]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiGUI, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiGUI instance at %s>" % (self.this,)

class KikiGUIPtr(KikiGUI):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiGUI
_kiki.KikiGUI_swigregister(KikiGUIPtr)

class KikiScreenText(KikiText,KikiActionObject):
    __swig_setmethods__ = {}
    for _s in [KikiText,KikiActionObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiScreenText, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiText,KikiActionObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiScreenText, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiScreenText,args)
        self.thisown = 1
    def addText(*args): return apply(_kiki.KikiScreenText_addText,args)
    def setText(*args): return apply(_kiki.KikiScreenText_setText,args)
    def show(*args): return apply(_kiki.KikiScreenText_show,args)
    def getProjection(*args): return apply(_kiki.KikiScreenText_getProjection,args)
    def __repr__(self):
        return "<C KikiScreenText instance at %s>" % (self.this,)

class KikiScreenTextPtr(KikiScreenText):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiScreenText
_kiki.KikiScreenText_swigregister(KikiScreenTextPtr)

class KikiMenu(KikiScreenText):
    __swig_setmethods__ = {}
    for _s in [KikiScreenText]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMenu, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiScreenText]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMenu, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiMenu,args)
        self.thisown = 1
    def addItem(*args): return apply(_kiki.KikiMenu_addItem,args)
    def setEscapeActive(*args): return apply(_kiki.KikiMenu_setEscapeActive,args)
    def __repr__(self):
        return "<C KikiMenu instance at %s>" % (self.this,)

class KikiMenuPtr(KikiMenu):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiMenu
_kiki.KikiMenu_swigregister(KikiMenuPtr)

class KikiScrollMenu(KikiMenu):
    __swig_setmethods__ = {}
    for _s in [KikiMenu]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiScrollMenu, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiMenu]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiScrollMenu, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiScrollMenu,args)
        self.thisown = 1
    def addItem(*args): return apply(_kiki.KikiScrollMenu_addItem,args)
    def __repr__(self):
        return "<C KikiScrollMenu instance at %s>" % (self.this,)

class KikiScrollMenuPtr(KikiScrollMenu):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiScrollMenu
_kiki.KikiScrollMenu_swigregister(KikiScrollMenuPtr)

class KikiColumnMenu(KikiMenu):
    __swig_setmethods__ = {}
    for _s in [KikiMenu]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiColumnMenu, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiMenu]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiColumnMenu, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiColumnMenu,args)
        self.thisown = 1
    def __repr__(self):
        return "<C KikiColumnMenu instance at %s>" % (self.this,)

class KikiColumnMenuPtr(KikiColumnMenu):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiColumnMenu
_kiki.KikiColumnMenu_swigregister(KikiColumnMenuPtr)

class KikiPageText(KikiScreenText):
    __swig_setmethods__ = {}
    for _s in [KikiScreenText]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPageText, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiScreenText]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPageText, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiPageText,args)
        self.thisown = 1
    def __repr__(self):
        return "<C KikiPageText instance at %s>" % (self.this,)

class KikiPageTextPtr(KikiPageText):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPageText
_kiki.KikiPageText_swigregister(KikiPageTextPtr)

class KikiFace(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiFace, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiFace, name)
    PX = _kiki.KikiFace_PX
    X = _kiki.KikiFace_X
    PY = _kiki.KikiFace_PY
    Y = _kiki.KikiFace_Y
    PZ = _kiki.KikiFace_PZ
    Z = _kiki.KikiFace_Z
    NX = _kiki.KikiFace_NX
    NY = _kiki.KikiFace_NY
    NZ = _kiki.KikiFace_NZ
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiFace instance at %s>" % (self.this,)

class KikiFacePtr(KikiFace):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiFace
_kiki.KikiFace_swigregister(KikiFacePtr)

class KikiWire(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiWire, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiWire, name)
    UP = _kiki.KikiWire_UP
    RIGHT = _kiki.KikiWire_RIGHT
    DOWN = _kiki.KikiWire_DOWN
    VERTICAL = _kiki.KikiWire_VERTICAL
    LEFT = _kiki.KikiWire_LEFT
    HORIZONTAL = _kiki.KikiWire_HORIZONTAL
    ALL = _kiki.KikiWire_ALL
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiWire,args)
        self.thisown = 1
    def setActive(*args): return apply(_kiki.KikiWire_setActive,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWire_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWire_setObjectColor)
    def __repr__(self):
        return "<C KikiWire instance at %s>" % (self.this,)

class KikiWirePtr(KikiWire):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiWire
_kiki.KikiWire_swigregister(KikiWirePtr)
KikiWire_setObjectColor = _kiki.KikiWire_setObjectColor


kikiObjectToWire = _kiki.kikiObjectToWire

class KikiGear(KikiObject,KikiFace):
    __swig_setmethods__ = {}
    for _s in [KikiObject,KikiFace]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiGear, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject,KikiFace]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiGear, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiGear,args)
        self.thisown = 1
    def setActive(*args): return apply(_kiki.KikiGear_setActive,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiGear_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiGear_setObjectColor)
    def __repr__(self):
        return "<C KikiGear instance at %s>" % (self.this,)

class KikiGearPtr(KikiGear):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiGear
_kiki.KikiGear_swigregister(KikiGearPtr)
KikiGear_setObjectColor = _kiki.KikiGear_setObjectColor


kikiObjectToGear = _kiki.kikiObjectToGear

class KikiValve(KikiObject,KikiFace):
    __swig_setmethods__ = {}
    for _s in [KikiObject,KikiFace]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiValve, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject,KikiFace]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiValve, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiValve,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiValve_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiValve_setObjectColor)
    def __repr__(self):
        return "<C KikiValve instance at %s>" % (self.this,)

class KikiValvePtr(KikiValve):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiValve
_kiki.KikiValve_swigregister(KikiValvePtr)
KikiValve_setObjectColor = _kiki.KikiValve_setObjectColor


kikiObjectToValve = _kiki.kikiObjectToValve

class KikiMotorCylinder(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMotorCylinder, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMotorCylinder, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiMotorCylinder,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMotorCylinder_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMotorCylinder_setObjectColor)
    def __repr__(self):
        return "<C KikiMotorCylinder instance at %s>" % (self.this,)

class KikiMotorCylinderPtr(KikiMotorCylinder):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiMotorCylinder
_kiki.KikiMotorCylinder_swigregister(KikiMotorCylinderPtr)
KikiMotorCylinder_setObjectColor = _kiki.KikiMotorCylinder_setObjectColor


class KikiMotorGear(KikiGear):
    __swig_setmethods__ = {}
    for _s in [KikiGear]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMotorGear, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiGear]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMotorGear, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiMotorGear,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMotorGear_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMotorGear_setObjectColor)
    def __repr__(self):
        return "<C KikiMotorGear instance at %s>" % (self.this,)

class KikiMotorGearPtr(KikiMotorGear):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiMotorGear
_kiki.KikiMotorGear_swigregister(KikiMotorGearPtr)
KikiMotorGear_setObjectColor = _kiki.KikiMotorGear_setObjectColor


class KikiGenerator(KikiGear):
    __swig_setmethods__ = {}
    for _s in [KikiGear]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiGenerator, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiGear]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiGenerator, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiGenerator,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiGenerator_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiGenerator_setObjectColor)
    def __repr__(self):
        return "<C KikiGenerator instance at %s>" % (self.this,)

class KikiGeneratorPtr(KikiGenerator):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiGenerator
_kiki.KikiGenerator_swigregister(KikiGeneratorPtr)
KikiGenerator_setObjectColor = _kiki.KikiGenerator_setObjectColor


class KikiLight(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiLight, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiLight, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiLight,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiLight_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiLight_setObjectColor)
    def __repr__(self):
        return "<C KikiLight instance at %s>" % (self.this,)

class KikiLightPtr(KikiLight):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiLight
_kiki.KikiLight_swigregister(KikiLightPtr)
KikiLight_setObjectColor = _kiki.KikiLight_setObjectColor


kikiObjectToLight = _kiki.kikiObjectToLight

class KikiCellText(KikiObject,KikiText):
    __swig_setmethods__ = {}
    for _s in [KikiObject,KikiText]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiCellText, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject,KikiText]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiCellText, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiCellText,args)
        self.thisown = 1
    def setOffset(*args): return apply(_kiki.KikiCellText_setOffset,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiCellText_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiCellText_setObjectColor)
    def __repr__(self):
        return "<C KikiCellText instance at %s>" % (self.this,)

class KikiCellTextPtr(KikiCellText):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiCellText
_kiki.KikiCellText_swigregister(KikiCellTextPtr)
KikiCellText_setObjectColor = _kiki.KikiCellText_setObjectColor


kikiObjectToCellText = _kiki.kikiObjectToCellText

class KikiStone(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiStone, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiStone, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiStone,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiStone_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiStone_setObjectColor)
    def __repr__(self):
        return "<C KikiStone instance at %s>" % (self.this,)

class KikiStonePtr(KikiStone):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiStone
_kiki.KikiStone_swigregister(KikiStonePtr)
KikiStone_setObjectColor = _kiki.KikiStone_setObjectColor


kikiObjectToStone = _kiki.kikiObjectToStone

class KikiWireStone(KikiStone):
    __swig_setmethods__ = {}
    for _s in [KikiStone]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiWireStone, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiStone]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiWireStone, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiWireStone,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWireStone_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWireStone_setObjectColor)
    def __repr__(self):
        return "<C KikiWireStone instance at %s>" % (self.this,)

class KikiWireStonePtr(KikiWireStone):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiWireStone
_kiki.KikiWireStone_swigregister(KikiWireStonePtr)
KikiWireStone_setObjectColor = _kiki.KikiWireStone_setObjectColor


kikiObjectToWireStone = _kiki.kikiObjectToWireStone

class KikiWall(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiWall, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiWall, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiWall,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWall_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWall_setObjectColor)
    def __repr__(self):
        return "<C KikiWall instance at %s>" % (self.this,)

class KikiWallPtr(KikiWall):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiWall
_kiki.KikiWall_swigregister(KikiWallPtr)
KikiWall_setObjectColor = _kiki.KikiWall_setObjectColor


kikiObjectToWall = _kiki.kikiObjectToWall

class KikiBomb(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBomb, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBomb, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiBomb,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiBomb_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiBomb_setObjectColor)
    def __repr__(self):
        return "<C KikiBomb instance at %s>" % (self.this,)

class KikiBombPtr(KikiBomb):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiBomb
_kiki.KikiBomb_swigregister(KikiBombPtr)
KikiBomb_setObjectColor = _kiki.KikiBomb_setObjectColor


kikiObjectToBomb = _kiki.kikiObjectToBomb

class KikiSwitch(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiSwitch, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiSwitch, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiSwitch,args)
        self.thisown = 1
    def toggle(*args): return apply(_kiki.KikiSwitch_toggle,args)
    def setActive(*args): return apply(_kiki.KikiSwitch_setActive,args)
    def isActive(*args): return apply(_kiki.KikiSwitch_isActive,args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiSwitch_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiSwitch_setObjectColor)
    def __repr__(self):
        return "<C KikiSwitch instance at %s>" % (self.this,)

class KikiSwitchPtr(KikiSwitch):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiSwitch
_kiki.KikiSwitch_swigregister(KikiSwitchPtr)
KikiSwitch_setObjectColor = _kiki.KikiSwitch_setObjectColor


kikiObjectToSwitch = _kiki.kikiObjectToSwitch

class KikiGate(KikiSwitch):
    __swig_setmethods__ = {}
    for _s in [KikiSwitch]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiGate, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiSwitch]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiGate, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiGate,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiGate_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiGate_setObjectColor)
    def __repr__(self):
        return "<C KikiGate instance at %s>" % (self.this,)

class KikiGatePtr(KikiGate):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiGate
_kiki.KikiGate_swigregister(KikiGatePtr)
KikiGate_setObjectColor = _kiki.KikiGate_setObjectColor


kikiObjectToGate = _kiki.kikiObjectToGate

class KikiAtom(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiAtom, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiAtom, name)
    def setValue(*args): return apply(_kiki.KikiAtom_setValue,args)
    def getValue(*args): return apply(_kiki.KikiAtom_getValue,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiAtom instance at %s>" % (self.this,)

class KikiAtomPtr(KikiAtom):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiAtom
_kiki.KikiAtom_swigregister(KikiAtomPtr)

class KikiMovesAtom(KikiAtom):
    __swig_setmethods__ = {}
    for _s in [KikiAtom]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMovesAtom, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiAtom]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMovesAtom, name)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMovesAtom_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMovesAtom_setObjectColor)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiMovesAtom instance at %s>" % (self.this,)

class KikiMovesAtomPtr(KikiMovesAtom):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiMovesAtom
_kiki.KikiMovesAtom_swigregister(KikiMovesAtomPtr)
KikiMovesAtom_setObjectColor = _kiki.KikiMovesAtom_setObjectColor


class KikiValueAtom(KikiAtom):
    __swig_setmethods__ = {}
    for _s in [KikiAtom]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiValueAtom, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiAtom]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiValueAtom, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiValueAtom,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiValueAtom_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiValueAtom_setObjectColor)
    def __repr__(self):
        return "<C KikiValueAtom instance at %s>" % (self.this,)

class KikiValueAtomPtr(KikiValueAtom):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiValueAtom
_kiki.KikiValueAtom_swigregister(KikiValueAtomPtr)
KikiValueAtom_setObjectColor = _kiki.KikiValueAtom_setObjectColor


class KikiSpikes(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiSpikes, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiSpikes, name)
    def __init__(self,*args):
        self.this = apply(_kiki.new_KikiSpikes,args)
        self.thisown = 1
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiSpikes_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiSpikes_setObjectColor)
    def __repr__(self):
        return "<C KikiSpikes instance at %s>" % (self.this,)

class KikiSpikesPtr(KikiSpikes):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiSpikes
_kiki.KikiSpikes_swigregister(KikiSpikesPtr)
KikiSpikes_setObjectColor = _kiki.KikiSpikes_setObjectColor


kikiObjectToSpikes = _kiki.kikiObjectToSpikes

class KikiBullet(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBullet, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBullet, name)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiBullet_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiBullet_setObjectColor)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiBullet instance at %s>" % (self.this,)

class KikiBulletPtr(KikiBullet):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiBullet
_kiki.KikiBullet_swigregister(KikiBulletPtr)
KikiBullet_setObjectColor = _kiki.KikiBullet_setObjectColor


class KConsole(KWindow):
    __swig_setmethods__ = {}
    for _s in [KWindow]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KConsole, name, value)
    __swig_getmethods__ = {}
    for _s in [KWindow]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KConsole, name)
    __swig_getmethods__["_print"] = lambda x: _kiki.KConsole__print
    if _newclass:_print = staticmethod(_kiki.KConsole__print)
    __swig_getmethods__["write"] = lambda x: _kiki.KConsole_write
    if _newclass:write = staticmethod(_kiki.KConsole_write)
    __swig_getmethods__["printError"] = lambda x: _kiki.KConsole_printError
    if _newclass:printError = staticmethod(_kiki.KConsole_printError)
    __swig_getmethods__["getConsole"] = lambda x: _kiki.KConsole_getConsole
    if _newclass:getConsole = staticmethod(_kiki.KConsole_getConsole)
    def clear(*args): return apply(_kiki.KConsole_clear,args)
    def out (self, *args):
        _kiki.KConsole__print(" ".join(map(str, args)))


    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KConsole instance at %s>" % (self.this,)

class KConsolePtr(KConsole):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KConsole
_kiki.KConsole_swigregister(KConsolePtr)
KConsole__print = _kiki.KConsole__print

KConsole_write = _kiki.KConsole_write

KConsole_printError = _kiki.KConsole_printError

KConsole_getConsole = _kiki.KConsole_getConsole


class KikiPythonWidget(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPythonWidget, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPythonWidget, name)
    __swig_setmethods__["cursorPos"] = _kiki.KikiPythonWidget_cursorPos_set
    __swig_getmethods__["cursorPos"] = _kiki.KikiPythonWidget_cursorPos_get
    if _newclass:cursorPos = property(_kiki.KikiPythonWidget_cursorPos_get,_kiki.KikiPythonWidget_cursorPos_set)
    __swig_setmethods__["selectionPos"] = _kiki.KikiPythonWidget_selectionPos_set
    __swig_getmethods__["selectionPos"] = _kiki.KikiPythonWidget_selectionPos_get
    if _newclass:selectionPos = property(_kiki.KikiPythonWidget_selectionPos_get,_kiki.KikiPythonWidget_selectionPos_set)
    def getTextRows(*args): return apply(_kiki.KikiPythonWidget_getTextRows,args)
    def getTextCols(*args): return apply(_kiki.KikiPythonWidget_getTextCols,args)
    def getTextSize(*args): return apply(_kiki.KikiPythonWidget_getTextSize,args)
    def getColumnWidth(*args): return apply(_kiki.KikiPythonWidget_getColumnWidth,args)
    def getRowHeight(*args): return apply(_kiki.KikiPythonWidget_getRowHeight,args)
    def getPythonWindow(*args): return apply(_kiki.KikiPythonWidget_getPythonWindow,args)
    def displayStringAtPos(*args): return apply(_kiki.KikiPythonWidget_displayStringAtPos,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiPythonWidget instance at %s>" % (self.this,)

class KikiPythonWidgetPtr(KikiPythonWidget):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPythonWidget
_kiki.KikiPythonWidget_swigregister(KikiPythonWidgetPtr)

class KikiPython(KWindow):
    __swig_setmethods__ = {}
    for _s in [KWindow]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPython, name, value)
    __swig_getmethods__ = {}
    for _s in [KWindow]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPython, name)
    def getPythonWidget(*args): return apply(_kiki.KikiPython_getPythonWidget,args)
    def setScrollBarUnits(*args): return apply(_kiki.KikiPython_setScrollBarUnits,args)
    def requestUserInput(*args): return apply(_kiki.KikiPython_requestUserInput,args)
    def setTitle(*args): return apply(_kiki.KikiPython_setTitle,args)
    def setStatus(*args): return apply(_kiki.KikiPython_setStatus,args)
    def setInput(*args): return apply(_kiki.KikiPython_setInput,args)
    def executeFile(*args): return apply(_kiki.KikiPython_executeFile,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C KikiPython instance at %s>" % (self.this,)

class KikiPythonPtr(KikiPython):
    def __init__(self,this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = KikiPython
_kiki.KikiPython_swigregister(KikiPythonPtr)


