# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _kiki

def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name) or (name == "thisown"):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

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
del types


class KikiPos(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPos, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPos, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPos instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_setmethods__["x"] = _kiki.KikiPos_x_set
    __swig_getmethods__["x"] = _kiki.KikiPos_x_get
    if _newclass:x = property(_kiki.KikiPos_x_get, _kiki.KikiPos_x_set)
    __swig_setmethods__["y"] = _kiki.KikiPos_y_set
    __swig_getmethods__["y"] = _kiki.KikiPos_y_get
    if _newclass:y = property(_kiki.KikiPos_y_get, _kiki.KikiPos_y_set)
    __swig_setmethods__["z"] = _kiki.KikiPos_z_set
    __swig_getmethods__["z"] = _kiki.KikiPos_z_get
    if _newclass:z = property(_kiki.KikiPos_z_get, _kiki.KikiPos_z_set)
    def __init__(self, *args):
        _swig_setattr(self, KikiPos, 'this', _kiki.new_KikiPos(*args))
        _swig_setattr(self, KikiPos, 'thisown', 1)
    def __sub__(*args): return _kiki.KikiPos___sub__(*args)
    def __add__(*args): return _kiki.KikiPos___add__(*args)
    def __iadd__(*args): return _kiki.KikiPos___iadd__(*args)
    def __isub__(*args): return _kiki.KikiPos___isub__(*args)
    def getString(*args): return _kiki.KikiPos_getString(*args)
    def __eq__(*args): return _kiki.KikiPos___eq__(*args)
    def __ne__(*args): return _kiki.KikiPos___ne__(*args)
    def __str__(*args): return _kiki.KikiPos___str__(*args)
    def __del__(self, destroy=_kiki.delete_KikiPos):
        try:
            if self.thisown: destroy(self)
        except: pass


class KikiPosPtr(KikiPos):
    def __init__(self, this):
        _swig_setattr(self, KikiPos, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPos, 'thisown', 0)
        _swig_setattr(self, KikiPos,self.__class__,KikiPos)
_kiki.KikiPos_swigregister(KikiPosPtr)

class KVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KVector, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KVector instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KVector, 'this', _kiki.new_KVector(*args))
        _swig_setattr(self, KVector, 'thisown', 1)
    def reset(*args): return _kiki.KVector_reset(*args)
    def normalize(*args): return _kiki.KVector_normalize(*args)
    def __iadd__(*args): return _kiki.KVector___iadd__(*args)
    def __isub__(*args): return _kiki.KVector___isub__(*args)
    def __imul__(*args): return _kiki.KVector___imul__(*args)
    def __idiv__(*args): return _kiki.KVector___idiv__(*args)
    def cross(*args): return _kiki.KVector_cross(*args)
    def __sub__(*args): return _kiki.KVector___sub__(*args)
    def __add__(*args): return _kiki.KVector___add__(*args)
    def __mul__(*args): return _kiki.KVector___mul__(*args)
    def __div__(*args): return _kiki.KVector___div__(*args)
    def perpendicular(*args): return _kiki.KVector_perpendicular(*args)
    def parallel(*args): return _kiki.KVector_parallel(*args)
    def reflect(*args): return _kiki.KVector_reflect(*args)
    def normal(*args): return _kiki.KVector_normal(*args)
    def length(*args): return _kiki.KVector_length(*args)
    def angle(*args): return _kiki.KVector_angle(*args)
    def xyangle(*args): return _kiki.KVector_xyangle(*args)
    def xyperp(*args): return _kiki.KVector_xyperp(*args)
    def round(*args): return _kiki.KVector_round(*args)
    def glVertex(*args): return _kiki.KVector_glVertex(*args)
    def __getitem__(*args): return _kiki.KVector___getitem__(*args)
    def __str__(*args): return _kiki.KVector___str__(*args)
    def __del__(self, destroy=_kiki.delete_KVector):
        try:
            if self.thisown: destroy(self)
        except: pass


class KVectorPtr(KVector):
    def __init__(self, this):
        _swig_setattr(self, KVector, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KVector, 'thisown', 0)
        _swig_setattr(self, KVector,self.__class__,KVector)
_kiki.KVector_swigregister(KVectorPtr)

class KQuaternion(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KQuaternion, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KQuaternion, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KQuaternion instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_setmethods__["w"] = _kiki.KQuaternion_w_set
    __swig_getmethods__["w"] = _kiki.KQuaternion_w_get
    if _newclass:w = property(_kiki.KQuaternion_w_get, _kiki.KQuaternion_w_set)
    __swig_setmethods__["x"] = _kiki.KQuaternion_x_set
    __swig_getmethods__["x"] = _kiki.KQuaternion_x_get
    if _newclass:x = property(_kiki.KQuaternion_x_get, _kiki.KQuaternion_x_set)
    __swig_setmethods__["y"] = _kiki.KQuaternion_y_set
    __swig_getmethods__["y"] = _kiki.KQuaternion_y_get
    if _newclass:y = property(_kiki.KQuaternion_y_get, _kiki.KQuaternion_y_set)
    __swig_setmethods__["z"] = _kiki.KQuaternion_z_set
    __swig_getmethods__["z"] = _kiki.KQuaternion_z_get
    if _newclass:z = property(_kiki.KQuaternion_z_get, _kiki.KQuaternion_z_set)
    def __init__(self, *args):
        _swig_setattr(self, KQuaternion, 'this', _kiki.new_KQuaternion(*args))
        _swig_setattr(self, KQuaternion, 'thisown', 1)
    __swig_getmethods__["rotationAroundVector"] = lambda x: _kiki.KQuaternion_rotationAroundVector
    if _newclass:rotationAroundVector = staticmethod(_kiki.KQuaternion_rotationAroundVector)
    def rotate(*args): return _kiki.KQuaternion_rotate(*args)
    def normalize(*args): return _kiki.KQuaternion_normalize(*args)
    def invert(*args): return _kiki.KQuaternion_invert(*args)
    def conjugate(*args): return _kiki.KQuaternion_conjugate(*args)
    def getNormal(*args): return _kiki.KQuaternion_getNormal(*args)
    def getConjugate(*args): return _kiki.KQuaternion_getConjugate(*args)
    def getInverse(*args): return _kiki.KQuaternion_getInverse(*args)
    def length(*args): return _kiki.KQuaternion_length(*args)
    def glRotate(*args): return _kiki.KQuaternion_glRotate(*args)
    def slerp(*args): return _kiki.KQuaternion_slerp(*args)
    def __mul__(*args): return _kiki.KQuaternion___mul__(*args)
    def __str__(*args): return _kiki.KQuaternion___str__(*args)
    def __del__(self, destroy=_kiki.delete_KQuaternion):
        try:
            if self.thisown: destroy(self)
        except: pass


class KQuaternionPtr(KQuaternion):
    def __init__(self, this):
        _swig_setattr(self, KQuaternion, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KQuaternion, 'thisown', 0)
        _swig_setattr(self, KQuaternion,self.__class__,KQuaternion)
_kiki.KQuaternion_swigregister(KQuaternionPtr)

KQuaternion_rotationAroundVector = _kiki.KQuaternion_rotationAroundVector

class KColor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KColor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KColor, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KColor instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KColor, 'this', _kiki.new_KColor(*args))
        _swig_setattr(self, KColor, 'thisown', 1)
    def setValues(*args): return _kiki.KColor_setValues(*args)
    def setRed(*args): return _kiki.KColor_setRed(*args)
    def setGreen(*args): return _kiki.KColor_setGreen(*args)
    def setBlue(*args): return _kiki.KColor_setBlue(*args)
    def setAlpha(*args): return _kiki.KColor_setAlpha(*args)
    def getRed(*args): return _kiki.KColor_getRed(*args)
    def getGreen(*args): return _kiki.KColor_getGreen(*args)
    def getBlue(*args): return _kiki.KColor_getBlue(*args)
    def getAlpha(*args): return _kiki.KColor_getAlpha(*args)
    def glColor(*args): return _kiki.KColor_glColor(*args)
    def __str__(*args): return _kiki.KColor___str__(*args)
    def __del__(self, destroy=_kiki.delete_KColor):
        try:
            if self.thisown: destroy(self)
        except: pass


class KColorPtr(KColor):
    def __init__(self, this):
        _swig_setattr(self, KColor, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KColor, 'thisown', 0)
        _swig_setattr(self, KColor,self.__class__,KColor)
_kiki.KColor_swigregister(KColorPtr)

class KProjection(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KProjection, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KProjection, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KProjection instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def focusOn(*args): return _kiki.KProjection_focusOn(*args)
    def setFov(*args): return _kiki.KProjection_setFov(*args)
    def getFov(*args): return _kiki.KProjection_getFov(*args)
    def setViewport(*args): return _kiki.KProjection_setViewport(*args)
    def setPosition(*args): return _kiki.KProjection_setPosition(*args)

class KProjectionPtr(KProjection):
    def __init__(self, this):
        _swig_setattr(self, KProjection, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KProjection, 'thisown', 0)
        _swig_setattr(self, KProjection,self.__class__,KProjection)
_kiki.KProjection_swigregister(KProjectionPtr)

class KKey(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KKey, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KKey, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KKey instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KKey, 'this', _kiki.new_KKey(*args))
        _swig_setattr(self, KKey, 'thisown', 1)
    __swig_setmethods__["name"] = _kiki.KKey_name_set
    __swig_getmethods__["name"] = _kiki.KKey_name_get
    if _newclass:name = property(_kiki.KKey_name_get, _kiki.KKey_name_set)
    def getUnmodifiedName(*args): return _kiki.KKey_getUnmodifiedName(*args)
    def getModifierName(*args): return _kiki.KKey_getModifierName(*args)

class KKeyPtr(KKey):
    def __init__(self, this):
        _swig_setattr(self, KKey, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KKey, 'thisown', 0)
        _swig_setattr(self, KKey,self.__class__,KKey)
_kiki.KKey_swigregister(KKeyPtr)

class KikiAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    ONCE = _kiki.KikiAction_ONCE
    CONTINUOUS = _kiki.KikiAction_CONTINUOUS
    REPEAT = _kiki.KikiAction_REPEAT
    def __init__(self, *args):
        _swig_setattr(self, KikiAction, 'this', _kiki.new_KikiAction(*args))
        _swig_setattr(self, KikiAction, 'thisown', 1)
    def getId(*args): return _kiki.KikiAction_getId(*args)
    def getName(*args): return _kiki.KikiAction_getName(*args)
    def getRelativeTime(*args): return _kiki.KikiAction_getRelativeTime(*args)
    def getRelativeDelta(*args): return _kiki.KikiAction_getRelativeDelta(*args)
    def getDuration(*args): return _kiki.KikiAction_getDuration(*args)
    def setDuration(*args): return _kiki.KikiAction_setDuration(*args)

class KikiActionPtr(KikiAction):
    def __init__(self, this):
        _swig_setattr(self, KikiAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiAction, 'thisown', 0)
        _swig_setattr(self, KikiAction,self.__class__,KikiAction)
_kiki.KikiAction_swigregister(KikiActionPtr)

class KikiPyAction(KikiAction):
    __swig_setmethods__ = {}
    for _s in [KikiAction]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPyAction, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiAction]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPyAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPyAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiPyAction, 'this', _kiki.new_KikiPyAction(*args))
        _swig_setattr(self, KikiPyAction, 'thisown', 1)
    def __del__(self, destroy=_kiki.delete_KikiPyAction):
        try:
            if self.thisown: destroy(self)
        except: pass

    def __init__(self,*args):
        self.this = apply (_kiki.new_KikiPyAction, (self,) + args)
        self.thisown = 1


class KikiPyActionPtr(KikiPyAction):
    def __init__(self, this):
        _swig_setattr(self, KikiPyAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPyAction, 'thisown', 0)
        _swig_setattr(self, KikiPyAction,self.__class__,KikiPyAction)
_kiki.KikiPyAction_swigregister(KikiPyActionPtr)

class KikiEvent(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiEvent, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiEvent, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiEvent, 'this', _kiki.new_KikiEvent(*args))
        _swig_setattr(self, KikiEvent, 'thisown', 1)
    def addAction(*args): return _kiki.KikiEvent_addAction(*args)
    def removeAction(*args): return _kiki.KikiEvent_removeAction(*args)
    def removeAllActions(*args): return _kiki.KikiEvent_removeAllActions(*args)
    def removeActionsOfObject(*args): return _kiki.KikiEvent_removeActionsOfObject(*args)
    def removeActionWithName(*args): return _kiki.KikiEvent_removeActionWithName(*args)
    def triggerActions(*args): return _kiki.KikiEvent_triggerActions(*args)
    def getTime(*args): return _kiki.KikiEvent_getTime(*args)

class KikiEventPtr(KikiEvent):
    def __init__(self, this):
        _swig_setattr(self, KikiEvent, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiEvent, 'thisown', 0)
        _swig_setattr(self, KikiEvent,self.__class__,KikiEvent)
_kiki.KikiEvent_swigregister(KikiEventPtr)

class KikiActionObject(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiActionObject, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiActionObject, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiActionObject instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def addAction(*args): return _kiki.KikiActionObject_addAction(*args)
    def removeAction(*args): return _kiki.KikiActionObject_removeAction(*args)
    def startTimedAction(*args): return _kiki.KikiActionObject_startTimedAction(*args)
    def startTimer(*args): return _kiki.KikiActionObject_startTimer(*args)
    def getActionWithName(*args): return _kiki.KikiActionObject_getActionWithName(*args)
    def getActionWithId(*args): return _kiki.KikiActionObject_getActionWithId(*args)
    def addEventWithName(*args): return _kiki.KikiActionObject_addEventWithName(*args)
    def getEventWithName(*args): return _kiki.KikiActionObject_getEventWithName(*args)
    def getEventWithId(*args): return _kiki.KikiActionObject_getEventWithId(*args)
    def getClassName(*args): return _kiki.KikiActionObject_getClassName(*args)

class KikiActionObjectPtr(KikiActionObject):
    def __init__(self, this):
        _swig_setattr(self, KikiActionObject, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiActionObject, 'thisown', 0)
        _swig_setattr(self, KikiActionObject,self.__class__,KikiActionObject)
_kiki.KikiActionObject_swigregister(KikiActionObjectPtr)

class KikiObject(KikiActionObject):
    __swig_setmethods__ = {}
    for _s in [KikiActionObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiObject, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiActionObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiObject, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiObject instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def setName(*args): return _kiki.KikiObject_setName(*args)
    def getName(*args): return _kiki.KikiObject_getName(*args)
    def getPos(*args): return _kiki.KikiObject_getPos(*args)
    def setPosition(*args): return _kiki.KikiObject_setPosition(*args)
    def getPosition(*args): return _kiki.KikiObject_getPosition(*args)
    def setOrientation(*args): return _kiki.KikiObject_setOrientation(*args)
    def getOrientation(*args): return _kiki.KikiObject_getOrientation(*args)
    def setCurrentOrientation(*args): return _kiki.KikiObject_setCurrentOrientation(*args)
    def getCurrentOrientation(*args): return _kiki.KikiObject_getCurrentOrientation(*args)
    def isSpaceEgoistic(*args): return _kiki.KikiObject_isSpaceEgoistic(*args)
    def getClassName(*args): return _kiki.KikiObject_getClassName(*args)

class KikiObjectPtr(KikiObject):
    def __init__(self, this):
        _swig_setattr(self, KikiObject, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiObject, 'thisown', 0)
        _swig_setattr(self, KikiObject,self.__class__,KikiObject)
_kiki.KikiObject_swigregister(KikiObjectPtr)

class KikiBotStatus(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBotStatus, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBotStatus, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiBotStatus instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def getMoves(*args): return _kiki.KikiBotStatus_getMoves(*args)
    def setMoves(*args): return _kiki.KikiBotStatus_setMoves(*args)
    def addMoves(*args): return _kiki.KikiBotStatus_addMoves(*args)
    def getMinMoves(*args): return _kiki.KikiBotStatus_getMinMoves(*args)
    def setMinMoves(*args): return _kiki.KikiBotStatus_setMinMoves(*args)

class KikiBotStatusPtr(KikiBotStatus):
    def __init__(self, this):
        _swig_setattr(self, KikiBotStatus, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiBotStatus, 'thisown', 0)
        _swig_setattr(self, KikiBotStatus,self.__class__,KikiBotStatus)
_kiki.KikiBotStatus_swigregister(KikiBotStatusPtr)

class KikiBotFume(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBotFume, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBotFume, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiBotFume instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiBotFume_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiBotFume_setObjectColor)

class KikiBotFumePtr(KikiBotFume):
    def __init__(self, this):
        _swig_setattr(self, KikiBotFume, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiBotFume, 'thisown', 0)
        _swig_setattr(self, KikiBotFume,self.__class__,KikiBotFume)
_kiki.KikiBotFume_swigregister(KikiBotFumePtr)

KikiBotFume_setObjectColor = _kiki.KikiBotFume_setObjectColor

class KikiBot(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiBot, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiBot, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiBot instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def isDead(*args): return _kiki.KikiBot_isDead(*args)
    def getDown(*args): return _kiki.KikiBot_getDown(*args)
    def getUp(*args): return _kiki.KikiBot_getUp(*args)
    def getDir(*args): return _kiki.KikiBot_getDir(*args)
    def setMove(*args): return _kiki.KikiBot_setMove(*args)
    def getStatus(*args): return _kiki.KikiBot_getStatus(*args)

class KikiBotPtr(KikiBot):
    def __init__(self, this):
        _swig_setattr(self, KikiBot, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiBot, 'thisown', 0)
        _swig_setattr(self, KikiBot,self.__class__,KikiBot)
_kiki.KikiBot_swigregister(KikiBotPtr)

class KikiStatusDisplay(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiStatusDisplay, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiStatusDisplay, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiStatusDisplay instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def show(*args): return _kiki.KikiStatusDisplay_show(*args)
    def hide(*args): return _kiki.KikiStatusDisplay_hide(*args)

class KikiStatusDisplayPtr(KikiStatusDisplay):
    def __init__(self, this):
        _swig_setattr(self, KikiStatusDisplay, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiStatusDisplay, 'thisown', 0)
        _swig_setattr(self, KikiStatusDisplay,self.__class__,KikiStatusDisplay)
_kiki.KikiStatusDisplay_swigregister(KikiStatusDisplayPtr)

class KikiPlayback(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPlayback, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPlayback, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPlayback instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_getmethods__["start"] = lambda x: _kiki.KikiPlayback_start
    if _newclass:start = staticmethod(_kiki.KikiPlayback_start)
    __swig_getmethods__["stop"] = lambda x: _kiki.KikiPlayback_stop
    if _newclass:stop = staticmethod(_kiki.KikiPlayback_stop)

class KikiPlaybackPtr(KikiPlayback):
    def __init__(self, this):
        _swig_setattr(self, KikiPlayback, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPlayback, 'thisown', 0)
        _swig_setattr(self, KikiPlayback,self.__class__,KikiPlayback)
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
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPlayer instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def die(*args): return _kiki.KikiPlayer_die(*args)
    def reborn(*args): return _kiki.KikiPlayer_reborn(*args)
    def reset(*args): return _kiki.KikiPlayer_reset(*args)
    def startRecorder(*args): return _kiki.KikiPlayer_startRecorder(*args)
    def saveRecorder(*args): return _kiki.KikiPlayer_saveRecorder(*args)
    def getProjection(*args): return _kiki.KikiPlayer_getProjection(*args)
    def handleKey(*args): return _kiki.KikiPlayer_handleKey(*args)
    def handleKeyRelease(*args): return _kiki.KikiPlayer_handleKeyRelease(*args)
    def recordKeyForAction(*args): return _kiki.KikiPlayer_recordKeyForAction(*args)
    __swig_getmethods__["getActionForKey"] = lambda x: _kiki.KikiPlayer_getActionForKey
    if _newclass:getActionForKey = staticmethod(_kiki.KikiPlayer_getActionForKey)
    __swig_getmethods__["getKeyForAction"] = lambda x: _kiki.KikiPlayer_getKeyForAction
    if _newclass:getKeyForAction = staticmethod(_kiki.KikiPlayer_getKeyForAction)
    __swig_getmethods__["setKeyForAction"] = lambda x: _kiki.KikiPlayer_setKeyForAction
    if _newclass:setKeyForAction = staticmethod(_kiki.KikiPlayer_setKeyForAction)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiPlayer_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiPlayer_setObjectColor)

class KikiPlayerPtr(KikiPlayer):
    def __init__(self, this):
        _swig_setattr(self, KikiPlayer, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPlayer, 'thisown', 0)
        _swig_setattr(self, KikiPlayer,self.__class__,KikiPlayer)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiMutant instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiMutant, 'this', _kiki.new_KikiMutant(*args))
        _swig_setattr(self, KikiMutant, 'thisown', 1)
    def die(*args): return _kiki.KikiMutant_die(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMutant_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMutant_setObjectColor)

class KikiMutantPtr(KikiMutant):
    def __init__(self, this):
        _swig_setattr(self, KikiMutant, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiMutant, 'thisown', 0)
        _swig_setattr(self, KikiMutant,self.__class__,KikiMutant)
_kiki.KikiMutant_swigregister(KikiMutantPtr)

KikiMutant_setObjectColor = _kiki.KikiMutant_setObjectColor

class KikiSound(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiSound, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiSound, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiSound instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def toggleMute(*args): return _kiki.KikiSound_toggleMute(*args)
    def setMute(*args): return _kiki.KikiSound_setMute(*args)
    def isMute(*args): return _kiki.KikiSound_isMute(*args)
    def setSoundVolume(*args): return _kiki.KikiSound_setSoundVolume(*args)
    def getSoundVolume(*args): return _kiki.KikiSound_getSoundVolume(*args)
    def playSound(*args): return _kiki.KikiSound_playSound(*args)
    def playSoundAtPos(*args): return _kiki.KikiSound_playSoundAtPos(*args)

class KikiSoundPtr(KikiSound):
    def __init__(self, this):
        _swig_setattr(self, KikiSound, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiSound, 'thisown', 0)
        _swig_setattr(self, KikiSound,self.__class__,KikiSound)
_kiki.KikiSound_swigregister(KikiSoundPtr)

class KikiWorld(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiWorld, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiWorld, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiWorld instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    CAMERA_INSIDE = _kiki.KikiWorld_CAMERA_INSIDE
    CAMERA_BEHIND = _kiki.KikiWorld_CAMERA_BEHIND
    CAMERA_FOLLOW = _kiki.KikiWorld_CAMERA_FOLLOW
    def setSize(*args): return _kiki.KikiWorld_setSize(*args)
    def getSize(*args): return _kiki.KikiWorld_getSize(*args)
    def setName(*args): return _kiki.KikiWorld_setName(*args)
    def getName(*args): return _kiki.KikiWorld_getName(*args)
    def init(*args): return _kiki.KikiWorld_init(*args)
    def setDisplayShadows(*args): return _kiki.KikiWorld_setDisplayShadows(*args)
    def setDisplayRaster(*args): return _kiki.KikiWorld_setDisplayRaster(*args)
    def setDisplayBorder(*args): return _kiki.KikiWorld_setDisplayBorder(*args)
    def setRasterSize(*args): return _kiki.KikiWorld_setRasterSize(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWorld_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWorld_setObjectColor)
    def changeCameraMode(*args): return _kiki.KikiWorld_changeCameraMode(*args)
    def getCameraMode(*args): return _kiki.KikiWorld_getCameraMode(*args)
    def setCameraMode(*args): return _kiki.KikiWorld_setCameraMode(*args)
    def getProjection(*args): return _kiki.KikiWorld_getProjection(*args)
    def addObjectAtPos(*args): return _kiki.KikiWorld_addObjectAtPos(*args)
    def setObjectAtPos(*args): return _kiki.KikiWorld_setObjectAtPos(*args)
    def unsetObject(*args): return _kiki.KikiWorld_unsetObject(*args)
    def removeObject(*args): return _kiki.KikiWorld_removeObject(*args)
    def deleteObject(*args): return _kiki.KikiWorld_deleteObject(*args)
    def deleteAllObjects(*args): return _kiki.KikiWorld_deleteAllObjects(*args)
    def deleteObjectsWithClassName(*args): return _kiki.KikiWorld_deleteObjectsWithClassName(*args)
    def getObjectWithName(*args): return _kiki.KikiWorld_getObjectWithName(*args)
    def moveObjectToPos(*args): return _kiki.KikiWorld_moveObjectToPos(*args)
    def objectWillMoveToPos(*args): return _kiki.KikiWorld_objectWillMoveToPos(*args)
    def objectMovedFromPos(*args): return _kiki.KikiWorld_objectMovedFromPos(*args)
    def getBotAtPos(*args): return _kiki.KikiWorld_getBotAtPos(*args)
    def getOccupantAtPos(*args): return _kiki.KikiWorld_getOccupantAtPos(*args)
    def getRealOccupantAtPos(*args): return _kiki.KikiWorld_getRealOccupantAtPos(*args)
    def getNearestValidPos(*args): return _kiki.KikiWorld_getNearestValidPos(*args)
    def isInvalidPos(*args): return _kiki.KikiWorld_isInvalidPos(*args)
    def isValidPos(*args): return _kiki.KikiWorld_isValidPos(*args)
    def isUnoccupiedPos(*args): return _kiki.KikiWorld_isUnoccupiedPos(*args)
    def isOccupiedPos(*args): return _kiki.KikiWorld_isOccupiedPos(*args)
    def posToIndex(*args): return _kiki.KikiWorld_posToIndex(*args)
    def indexToPos(*args): return _kiki.KikiWorld_indexToPos(*args)
    def getPickedPos(*args): return _kiki.KikiWorld_getPickedPos(*args)

class KikiWorldPtr(KikiWorld):
    def __init__(self, this):
        _swig_setattr(self, KikiWorld, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiWorld, 'thisown', 0)
        _swig_setattr(self, KikiWorld,self.__class__,KikiWorld)
_kiki.KikiWorld_swigregister(KikiWorldPtr)

KikiWorld_setObjectColor = _kiki.KikiWorld_setObjectColor

class KEventHandler(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KEventHandler, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KEventHandler, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KEventHandler instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def quit(*args): return _kiki.KEventHandler_quit(*args)
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
    def setWireframeMode(*args): return _kiki.KEventHandler_setWireframeMode(*args)
    def setDisplayFps(*args): return _kiki.KEventHandler_setDisplayFps(*args)
    def getDisplayFps(*args): return _kiki.KEventHandler_getDisplayFps(*args)

class KEventHandlerPtr(KEventHandler):
    def __init__(self, this):
        _swig_setattr(self, KEventHandler, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KEventHandler, 'thisown', 0)
        _swig_setattr(self, KEventHandler,self.__class__,KEventHandler)
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
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiController instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_setmethods__["gui"] = _kiki.KikiController_gui_set
    __swig_getmethods__["gui"] = _kiki.KikiController_gui_get
    if _newclass:gui = property(_kiki.KikiController_gui_get, _kiki.KikiController_gui_set)
    __swig_setmethods__["sound"] = _kiki.KikiController_sound_set
    __swig_getmethods__["sound"] = _kiki.KikiController_sound_get
    if _newclass:sound = property(_kiki.KikiController_sound_get, _kiki.KikiController_sound_set)
    __swig_setmethods__["world"] = _kiki.KikiController_world_set
    __swig_getmethods__["world"] = _kiki.KikiController_world_get
    if _newclass:world = property(_kiki.KikiController_world_get, _kiki.KikiController_world_set)
    __swig_setmethods__["player"] = _kiki.KikiController_player_set
    __swig_getmethods__["player"] = _kiki.KikiController_player_get
    if _newclass:player = property(_kiki.KikiController_player_get, _kiki.KikiController_player_set)
    __swig_setmethods__["python"] = _kiki.KikiController_python_set
    __swig_getmethods__["python"] = _kiki.KikiController_python_get
    if _newclass:python = property(_kiki.KikiController_python_get, _kiki.KikiController_python_set)
    __swig_setmethods__["player_status"] = _kiki.KikiController_player_status_set
    __swig_getmethods__["player_status"] = _kiki.KikiController_player_status_get
    if _newclass:player_status = property(_kiki.KikiController_player_status_get, _kiki.KikiController_player_status_set)
    __swig_setmethods__["timer_event"] = _kiki.KikiController_timer_event_set
    __swig_getmethods__["timer_event"] = _kiki.KikiController_timer_event_get
    if _newclass:timer_event = property(_kiki.KikiController_timer_event_get, _kiki.KikiController_timer_event_set)
    def getPlayer(*args): return _kiki.KikiController_getPlayer(*args)
    def unmapMsTime(*args): return _kiki.KikiController_unmapMsTime(*args)
    def mapMsTime(*args): return _kiki.KikiController_mapMsTime(*args)
    def setSpeed(*args): return _kiki.KikiController_setSpeed(*args)
    def getSpeed(*args): return _kiki.KikiController_getSpeed(*args)
    def getKikiHome(*args): return _kiki.KikiController_getKikiHome(*args)
    def setGamma(*args): return _kiki.KikiController_setGamma(*args)
    def getGamma(*args): return _kiki.KikiController_getGamma(*args)
    def displayText(*args): return _kiki.KikiController_displayText(*args)
    def getLocalizedString(*args): return _kiki.KikiController_getLocalizedString(*args)
    def isDebugVersion(*args): return _kiki.KikiController_isDebugVersion(*args)

class KikiControllerPtr(KikiController):
    def __init__(self, this):
        _swig_setattr(self, KikiController, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiController, 'thisown', 0)
        _swig_setattr(self, KikiController,self.__class__,KikiController)
_kiki.KikiController_swigregister(KikiControllerPtr)


replaceTabs = _kiki.replaceTabs
class KWindow(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KWindow, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KWindow, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KWindow instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def isVisible(*args): return _kiki.KWindow_isVisible(*args)
    def setVisibility(*args): return _kiki.KWindow_setVisibility(*args)
    def toggleVisibility(*args): return _kiki.KWindow_toggleVisibility(*args)
    def maximize(*args): return _kiki.KWindow_maximize(*args)
    def show(*args): return _kiki.KWindow_show(*args)
    def hide(*args): return _kiki.KWindow_hide(*args)
    def close(*args): return _kiki.KWindow_close(*args)
    def setSize(*args): return _kiki.KWindow_setSize(*args)
    def setPosition(*args): return _kiki.KWindow_setPosition(*args)

class KWindowPtr(KWindow):
    def __init__(self, this):
        _swig_setattr(self, KWindow, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KWindow, 'thisown', 0)
        _swig_setattr(self, KWindow,self.__class__,KWindow)
_kiki.KWindow_swigregister(KWindowPtr)
kiki = _kiki.kiki

class KikiText(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiText, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiText, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiText instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    base_color = _kiki.KikiText_base_color
    bright_color = _kiki.KikiText_bright_color
    dark_color = _kiki.KikiText_dark_color
    def __init__(self, *args):
        _swig_setattr(self, KikiText, 'this', _kiki.new_KikiText(*args))
        _swig_setattr(self, KikiText, 'thisown', 1)
    def setText(*args): return _kiki.KikiText_setText(*args)
    def getText(*args): return _kiki.KikiText_getText(*args)
    def clear(*args): return _kiki.KikiText_clear(*args)
    def isEmpty(*args): return _kiki.KikiText_isEmpty(*args)
    def addText(*args): return _kiki.KikiText_addText(*args)
    def getColor(*args): return _kiki.KikiText_getColor(*args)
    def setColor(*args): return _kiki.KikiText_setColor(*args)
    def setAlpha(*args): return _kiki.KikiText_setAlpha(*args)
    def isAnimated(*args): return _kiki.KikiText_isAnimated(*args)
    def setAnimated(*args): return _kiki.KikiText_setAnimated(*args)
    def isCentered(*args): return _kiki.KikiText_isCentered(*args)
    def setCentered(*args): return _kiki.KikiText_setCentered(*args)
    def getWidth(*args): return _kiki.KikiText_getWidth(*args)
    def getHeight(*args): return _kiki.KikiText_getHeight(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiText_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiText_setObjectColor)

class KikiTextPtr(KikiText):
    def __init__(self, this):
        _swig_setattr(self, KikiText, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiText, 'thisown', 0)
        _swig_setattr(self, KikiText,self.__class__,KikiText)
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
        return "<%s.%s; proxy of C++ KikiGUI instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)

class KikiGUIPtr(KikiGUI):
    def __init__(self, this):
        _swig_setattr(self, KikiGUI, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiGUI, 'thisown', 0)
        _swig_setattr(self, KikiGUI,self.__class__,KikiGUI)
_kiki.KikiGUI_swigregister(KikiGUIPtr)

class KikiScreenText(KikiText,KikiActionObject):
    __swig_setmethods__ = {}
    for _s in [KikiText,KikiActionObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiScreenText, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiText,KikiActionObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiScreenText, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiScreenText instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiScreenText, 'this', _kiki.new_KikiScreenText(*args))
        _swig_setattr(self, KikiScreenText, 'thisown', 1)
    def addText(*args): return _kiki.KikiScreenText_addText(*args)
    def setText(*args): return _kiki.KikiScreenText_setText(*args)
    def show(*args): return _kiki.KikiScreenText_show(*args)
    def getProjection(*args): return _kiki.KikiScreenText_getProjection(*args)

class KikiScreenTextPtr(KikiScreenText):
    def __init__(self, this):
        _swig_setattr(self, KikiScreenText, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiScreenText, 'thisown', 0)
        _swig_setattr(self, KikiScreenText,self.__class__,KikiScreenText)
_kiki.KikiScreenText_swigregister(KikiScreenTextPtr)

class KikiMenu(KikiScreenText):
    __swig_setmethods__ = {}
    for _s in [KikiScreenText]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMenu, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiScreenText]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMenu, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiMenu instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiMenu, 'this', _kiki.new_KikiMenu(*args))
        _swig_setattr(self, KikiMenu, 'thisown', 1)
    def addItem(*args): return _kiki.KikiMenu_addItem(*args)
    def setEscapeActive(*args): return _kiki.KikiMenu_setEscapeActive(*args)

class KikiMenuPtr(KikiMenu):
    def __init__(self, this):
        _swig_setattr(self, KikiMenu, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiMenu, 'thisown', 0)
        _swig_setattr(self, KikiMenu,self.__class__,KikiMenu)
_kiki.KikiMenu_swigregister(KikiMenuPtr)

class KikiScrollMenu(KikiMenu):
    __swig_setmethods__ = {}
    for _s in [KikiMenu]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiScrollMenu, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiMenu]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiScrollMenu, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiScrollMenu instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiScrollMenu, 'this', _kiki.new_KikiScrollMenu(*args))
        _swig_setattr(self, KikiScrollMenu, 'thisown', 1)
    def addItem(*args): return _kiki.KikiScrollMenu_addItem(*args)

class KikiScrollMenuPtr(KikiScrollMenu):
    def __init__(self, this):
        _swig_setattr(self, KikiScrollMenu, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiScrollMenu, 'thisown', 0)
        _swig_setattr(self, KikiScrollMenu,self.__class__,KikiScrollMenu)
_kiki.KikiScrollMenu_swigregister(KikiScrollMenuPtr)

class KikiColumnMenu(KikiMenu):
    __swig_setmethods__ = {}
    for _s in [KikiMenu]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiColumnMenu, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiMenu]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiColumnMenu, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiColumnMenu instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiColumnMenu, 'this', _kiki.new_KikiColumnMenu(*args))
        _swig_setattr(self, KikiColumnMenu, 'thisown', 1)

class KikiColumnMenuPtr(KikiColumnMenu):
    def __init__(self, this):
        _swig_setattr(self, KikiColumnMenu, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiColumnMenu, 'thisown', 0)
        _swig_setattr(self, KikiColumnMenu,self.__class__,KikiColumnMenu)
_kiki.KikiColumnMenu_swigregister(KikiColumnMenuPtr)

class KikiPageText(KikiScreenText):
    __swig_setmethods__ = {}
    for _s in [KikiScreenText]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPageText, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiScreenText]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPageText, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPageText instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiPageText, 'this', _kiki.new_KikiPageText(*args))
        _swig_setattr(self, KikiPageText, 'thisown', 1)

class KikiPageTextPtr(KikiPageText):
    def __init__(self, this):
        _swig_setattr(self, KikiPageText, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPageText, 'thisown', 0)
        _swig_setattr(self, KikiPageText,self.__class__,KikiPageText)
_kiki.KikiPageText_swigregister(KikiPageTextPtr)

class KikiFace(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiFace, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KikiFace, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiFace instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    PX = _kiki.KikiFace_PX
    X = _kiki.KikiFace_X
    PY = _kiki.KikiFace_PY
    Y = _kiki.KikiFace_Y
    PZ = _kiki.KikiFace_PZ
    Z = _kiki.KikiFace_Z
    NX = _kiki.KikiFace_NX
    NY = _kiki.KikiFace_NY
    NZ = _kiki.KikiFace_NZ

class KikiFacePtr(KikiFace):
    def __init__(self, this):
        _swig_setattr(self, KikiFace, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiFace, 'thisown', 0)
        _swig_setattr(self, KikiFace,self.__class__,KikiFace)
_kiki.KikiFace_swigregister(KikiFacePtr)

class KikiWire(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiWire, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiWire, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiWire instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    UP = _kiki.KikiWire_UP
    RIGHT = _kiki.KikiWire_RIGHT
    DOWN = _kiki.KikiWire_DOWN
    VERTICAL = _kiki.KikiWire_VERTICAL
    LEFT = _kiki.KikiWire_LEFT
    HORIZONTAL = _kiki.KikiWire_HORIZONTAL
    ALL = _kiki.KikiWire_ALL
    def __init__(self, *args):
        _swig_setattr(self, KikiWire, 'this', _kiki.new_KikiWire(*args))
        _swig_setattr(self, KikiWire, 'thisown', 1)
    def setActive(*args): return _kiki.KikiWire_setActive(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWire_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWire_setObjectColor)

class KikiWirePtr(KikiWire):
    def __init__(self, this):
        _swig_setattr(self, KikiWire, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiWire, 'thisown', 0)
        _swig_setattr(self, KikiWire,self.__class__,KikiWire)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiGear instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiGear, 'this', _kiki.new_KikiGear(*args))
        _swig_setattr(self, KikiGear, 'thisown', 1)
    def setActive(*args): return _kiki.KikiGear_setActive(*args)
    def updateActive(*args): return _kiki.KikiGear_updateActive(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiGear_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiGear_setObjectColor)

class KikiGearPtr(KikiGear):
    def __init__(self, this):
        _swig_setattr(self, KikiGear, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiGear, 'thisown', 0)
        _swig_setattr(self, KikiGear,self.__class__,KikiGear)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiValve instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiValve, 'this', _kiki.new_KikiValve(*args))
        _swig_setattr(self, KikiValve, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiValve_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiValve_setObjectColor)

class KikiValvePtr(KikiValve):
    def __init__(self, this):
        _swig_setattr(self, KikiValve, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiValve, 'thisown', 0)
        _swig_setattr(self, KikiValve,self.__class__,KikiValve)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiMotorCylinder instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiMotorCylinder, 'this', _kiki.new_KikiMotorCylinder(*args))
        _swig_setattr(self, KikiMotorCylinder, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMotorCylinder_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMotorCylinder_setObjectColor)

class KikiMotorCylinderPtr(KikiMotorCylinder):
    def __init__(self, this):
        _swig_setattr(self, KikiMotorCylinder, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiMotorCylinder, 'thisown', 0)
        _swig_setattr(self, KikiMotorCylinder,self.__class__,KikiMotorCylinder)
_kiki.KikiMotorCylinder_swigregister(KikiMotorCylinderPtr)

KikiMotorCylinder_setObjectColor = _kiki.KikiMotorCylinder_setObjectColor

class KikiMotorGear(KikiGear):
    __swig_setmethods__ = {}
    for _s in [KikiGear]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMotorGear, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiGear]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMotorGear, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiMotorGear instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiMotorGear, 'this', _kiki.new_KikiMotorGear(*args))
        _swig_setattr(self, KikiMotorGear, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMotorGear_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMotorGear_setObjectColor)

class KikiMotorGearPtr(KikiMotorGear):
    def __init__(self, this):
        _swig_setattr(self, KikiMotorGear, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiMotorGear, 'thisown', 0)
        _swig_setattr(self, KikiMotorGear,self.__class__,KikiMotorGear)
_kiki.KikiMotorGear_swigregister(KikiMotorGearPtr)

KikiMotorGear_setObjectColor = _kiki.KikiMotorGear_setObjectColor

class KikiGenerator(KikiGear):
    __swig_setmethods__ = {}
    for _s in [KikiGear]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiGenerator, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiGear]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiGenerator, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiGenerator instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiGenerator, 'this', _kiki.new_KikiGenerator(*args))
        _swig_setattr(self, KikiGenerator, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiGenerator_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiGenerator_setObjectColor)

class KikiGeneratorPtr(KikiGenerator):
    def __init__(self, this):
        _swig_setattr(self, KikiGenerator, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiGenerator, 'thisown', 0)
        _swig_setattr(self, KikiGenerator,self.__class__,KikiGenerator)
_kiki.KikiGenerator_swigregister(KikiGeneratorPtr)

KikiGenerator_setObjectColor = _kiki.KikiGenerator_setObjectColor

class KikiLight(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiLight, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiLight, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiLight instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiLight, 'this', _kiki.new_KikiLight(*args))
        _swig_setattr(self, KikiLight, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiLight_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiLight_setObjectColor)

class KikiLightPtr(KikiLight):
    def __init__(self, this):
        _swig_setattr(self, KikiLight, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiLight, 'thisown', 0)
        _swig_setattr(self, KikiLight,self.__class__,KikiLight)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiCellText instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiCellText, 'this', _kiki.new_KikiCellText(*args))
        _swig_setattr(self, KikiCellText, 'thisown', 1)
    def setOffset(*args): return _kiki.KikiCellText_setOffset(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiCellText_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiCellText_setObjectColor)

class KikiCellTextPtr(KikiCellText):
    def __init__(self, this):
        _swig_setattr(self, KikiCellText, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiCellText, 'thisown', 0)
        _swig_setattr(self, KikiCellText,self.__class__,KikiCellText)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiStone instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiStone, 'this', _kiki.new_KikiStone(*args))
        _swig_setattr(self, KikiStone, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiStone_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiStone_setObjectColor)

class KikiStonePtr(KikiStone):
    def __init__(self, this):
        _swig_setattr(self, KikiStone, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiStone, 'thisown', 0)
        _swig_setattr(self, KikiStone,self.__class__,KikiStone)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiWireStone instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiWireStone, 'this', _kiki.new_KikiWireStone(*args))
        _swig_setattr(self, KikiWireStone, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWireStone_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWireStone_setObjectColor)

class KikiWireStonePtr(KikiWireStone):
    def __init__(self, this):
        _swig_setattr(self, KikiWireStone, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiWireStone, 'thisown', 0)
        _swig_setattr(self, KikiWireStone,self.__class__,KikiWireStone)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiWall instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiWall, 'this', _kiki.new_KikiWall(*args))
        _swig_setattr(self, KikiWall, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiWall_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiWall_setObjectColor)

class KikiWallPtr(KikiWall):
    def __init__(self, this):
        _swig_setattr(self, KikiWall, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiWall, 'thisown', 0)
        _swig_setattr(self, KikiWall,self.__class__,KikiWall)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiBomb instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiBomb, 'this', _kiki.new_KikiBomb(*args))
        _swig_setattr(self, KikiBomb, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiBomb_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiBomb_setObjectColor)

class KikiBombPtr(KikiBomb):
    def __init__(self, this):
        _swig_setattr(self, KikiBomb, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiBomb, 'thisown', 0)
        _swig_setattr(self, KikiBomb,self.__class__,KikiBomb)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiSwitch instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiSwitch, 'this', _kiki.new_KikiSwitch(*args))
        _swig_setattr(self, KikiSwitch, 'thisown', 1)
    def toggle(*args): return _kiki.KikiSwitch_toggle(*args)
    def setActive(*args): return _kiki.KikiSwitch_setActive(*args)
    def isActive(*args): return _kiki.KikiSwitch_isActive(*args)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiSwitch_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiSwitch_setObjectColor)

class KikiSwitchPtr(KikiSwitch):
    def __init__(self, this):
        _swig_setattr(self, KikiSwitch, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiSwitch, 'thisown', 0)
        _swig_setattr(self, KikiSwitch,self.__class__,KikiSwitch)
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
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiGate instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiGate, 'this', _kiki.new_KikiGate(*args))
        _swig_setattr(self, KikiGate, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiGate_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiGate_setObjectColor)

class KikiGatePtr(KikiGate):
    def __init__(self, this):
        _swig_setattr(self, KikiGate, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiGate, 'thisown', 0)
        _swig_setattr(self, KikiGate,self.__class__,KikiGate)
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
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiAtom instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def setValue(*args): return _kiki.KikiAtom_setValue(*args)
    def getValue(*args): return _kiki.KikiAtom_getValue(*args)

class KikiAtomPtr(KikiAtom):
    def __init__(self, this):
        _swig_setattr(self, KikiAtom, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiAtom, 'thisown', 0)
        _swig_setattr(self, KikiAtom,self.__class__,KikiAtom)
_kiki.KikiAtom_swigregister(KikiAtomPtr)

class KikiMovesAtom(KikiAtom):
    __swig_setmethods__ = {}
    for _s in [KikiAtom]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiMovesAtom, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiAtom]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiMovesAtom, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiMovesAtom instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiMovesAtom_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiMovesAtom_setObjectColor)

class KikiMovesAtomPtr(KikiMovesAtom):
    def __init__(self, this):
        _swig_setattr(self, KikiMovesAtom, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiMovesAtom, 'thisown', 0)
        _swig_setattr(self, KikiMovesAtom,self.__class__,KikiMovesAtom)
_kiki.KikiMovesAtom_swigregister(KikiMovesAtomPtr)

KikiMovesAtom_setObjectColor = _kiki.KikiMovesAtom_setObjectColor

class KikiValueAtom(KikiAtom):
    __swig_setmethods__ = {}
    for _s in [KikiAtom]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiValueAtom, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiAtom]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiValueAtom, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiValueAtom instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiValueAtom, 'this', _kiki.new_KikiValueAtom(*args))
        _swig_setattr(self, KikiValueAtom, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiValueAtom_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiValueAtom_setObjectColor)

class KikiValueAtomPtr(KikiValueAtom):
    def __init__(self, this):
        _swig_setattr(self, KikiValueAtom, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiValueAtom, 'thisown', 0)
        _swig_setattr(self, KikiValueAtom,self.__class__,KikiValueAtom)
_kiki.KikiValueAtom_swigregister(KikiValueAtomPtr)

KikiValueAtom_setObjectColor = _kiki.KikiValueAtom_setObjectColor

class KikiSpikes(KikiObject):
    __swig_setmethods__ = {}
    for _s in [KikiObject]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiSpikes, name, value)
    __swig_getmethods__ = {}
    for _s in [KikiObject]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiSpikes, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiSpikes instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, KikiSpikes, 'this', _kiki.new_KikiSpikes(*args))
        _swig_setattr(self, KikiSpikes, 'thisown', 1)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiSpikes_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiSpikes_setObjectColor)

class KikiSpikesPtr(KikiSpikes):
    def __init__(self, this):
        _swig_setattr(self, KikiSpikes, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiSpikes, 'thisown', 0)
        _swig_setattr(self, KikiSpikes,self.__class__,KikiSpikes)
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
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiBullet instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_getmethods__["setObjectColor"] = lambda x: _kiki.KikiBullet_setObjectColor
    if _newclass:setObjectColor = staticmethod(_kiki.KikiBullet_setObjectColor)

class KikiBulletPtr(KikiBullet):
    def __init__(self, this):
        _swig_setattr(self, KikiBullet, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiBullet, 'thisown', 0)
        _swig_setattr(self, KikiBullet,self.__class__,KikiBullet)
_kiki.KikiBullet_swigregister(KikiBulletPtr)

KikiBullet_setObjectColor = _kiki.KikiBullet_setObjectColor

class KConsole(KWindow):
    __swig_setmethods__ = {}
    for _s in [KWindow]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KConsole, name, value)
    __swig_getmethods__ = {}
    for _s in [KWindow]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KConsole, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KConsole instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_getmethods__["_print"] = lambda x: _kiki.KConsole__print
    if _newclass:_print = staticmethod(_kiki.KConsole__print)
    __swig_getmethods__["write"] = lambda x: _kiki.KConsole_write
    if _newclass:write = staticmethod(_kiki.KConsole_write)
    __swig_getmethods__["printError"] = lambda x: _kiki.KConsole_printError
    if _newclass:printError = staticmethod(_kiki.KConsole_printError)
    __swig_getmethods__["getConsole"] = lambda x: _kiki.KConsole_getConsole
    if _newclass:getConsole = staticmethod(_kiki.KConsole_getConsole)
    def clear(*args): return _kiki.KConsole_clear(*args)
    def out (self, *args):
        _kiki.KConsole__print(" ".join(map(str, args)))


class KConsolePtr(KConsole):
    def __init__(self, this):
        _swig_setattr(self, KConsole, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KConsole, 'thisown', 0)
        _swig_setattr(self, KConsole,self.__class__,KConsole)
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
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPythonWidget instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_setmethods__["cursorPos"] = _kiki.KikiPythonWidget_cursorPos_set
    __swig_getmethods__["cursorPos"] = _kiki.KikiPythonWidget_cursorPos_get
    if _newclass:cursorPos = property(_kiki.KikiPythonWidget_cursorPos_get, _kiki.KikiPythonWidget_cursorPos_set)
    __swig_setmethods__["selectionPos"] = _kiki.KikiPythonWidget_selectionPos_set
    __swig_getmethods__["selectionPos"] = _kiki.KikiPythonWidget_selectionPos_get
    if _newclass:selectionPos = property(_kiki.KikiPythonWidget_selectionPos_get, _kiki.KikiPythonWidget_selectionPos_set)
    def getTextRows(*args): return _kiki.KikiPythonWidget_getTextRows(*args)
    def getTextCols(*args): return _kiki.KikiPythonWidget_getTextCols(*args)
    def getTextSize(*args): return _kiki.KikiPythonWidget_getTextSize(*args)
    def getColumnWidth(*args): return _kiki.KikiPythonWidget_getColumnWidth(*args)
    def getRowHeight(*args): return _kiki.KikiPythonWidget_getRowHeight(*args)
    def getPythonWindow(*args): return _kiki.KikiPythonWidget_getPythonWindow(*args)
    def displayStringAtPos(*args): return _kiki.KikiPythonWidget_displayStringAtPos(*args)

class KikiPythonWidgetPtr(KikiPythonWidget):
    def __init__(self, this):
        _swig_setattr(self, KikiPythonWidget, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPythonWidget, 'thisown', 0)
        _swig_setattr(self, KikiPythonWidget,self.__class__,KikiPythonWidget)
_kiki.KikiPythonWidget_swigregister(KikiPythonWidgetPtr)

class KikiPython(KWindow):
    __swig_setmethods__ = {}
    for _s in [KWindow]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, KikiPython, name, value)
    __swig_getmethods__ = {}
    for _s in [KWindow]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, KikiPython, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ KikiPython instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def getPythonWidget(*args): return _kiki.KikiPython_getPythonWidget(*args)
    def setScrollBarUnits(*args): return _kiki.KikiPython_setScrollBarUnits(*args)
    def requestUserInput(*args): return _kiki.KikiPython_requestUserInput(*args)
    def setTitle(*args): return _kiki.KikiPython_setTitle(*args)
    def setStatus(*args): return _kiki.KikiPython_setStatus(*args)
    def setInput(*args): return _kiki.KikiPython_setInput(*args)
    def executeFile(*args): return _kiki.KikiPython_executeFile(*args)

class KikiPythonPtr(KikiPython):
    def __init__(self, this):
        _swig_setattr(self, KikiPython, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, KikiPython, 'thisown', 0)
        _swig_setattr(self, KikiPython,self.__class__,KikiPython)
_kiki.KikiPython_swigregister(KikiPythonPtr)


