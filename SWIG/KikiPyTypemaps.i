
%include "typemaps.i"

//%include "std_vector.i"

// ......................................................... string
%include "std_string.i" // doesn't work for me :-(
/*
%typemap(in) const std::string &  {
   $1 = new std::string(PyString_AsString($input));
   if (PyErr_Occurred()) return NULL;
}

%typemap(out) const std::string & {
   $result = PyString_FromString($1->c_str());
}

%typemap(out) std::string {
   $result = PyString_FromString($1.c_str());
}

%typemap(freearg) const std::string & {
   if ($1) delete $1;
}
*/
// ......................................................... KSize
%typemap(in) const KSize & {
    $1 = new KSize(PyInt_AsLong(PyTuple_GetItem($input, 0)), PyInt_AsLong(PyTuple_GetItem($input, 1)));
    if (PyErr_Occurred()) return NULL;
}

%typemap(in) KSize {
    $1 = KSize(PyInt_AsLong(PyTuple_GetItem($input, 0)), PyInt_AsLong(PyTuple_GetItem($input, 1)));
    if (PyErr_Occurred()) return NULL;
}

%typemap(out) const KSize & {
   $result = PyTuple_New(2);
   PyTuple_SetItem($result, 0, PyInt_FromLong($1.w));
   PyTuple_SetItem($result, 1, PyInt_FromLong($1.h));
}

%typemap(out) KSize {
   $result = PyTuple_New(2);
   PyTuple_SetItem($result, 0, PyInt_FromLong($1.w));
   PyTuple_SetItem($result, 1, PyInt_FromLong($1.h));
}

%typemap(freearg) const KSize & {
   if ($1) delete $1;
}

// ......................................................... KPosition
%typemap(in) const KPosition &  {
    $1 = new KPosition(PyInt_AsLong(PyTuple_GetItem($input, 0)), PyInt_AsLong(PyTuple_GetItem($input, 1)));
    if (PyErr_Occurred()) return NULL;
}

%typemap(in) KPosition {
    $1 = KPosition(PyInt_AsLong(PyTuple_GetItem($input, 0)), PyInt_AsLong(PyTuple_GetItem($input, 1)));
    if (PyErr_Occurred()) return NULL;
}

%typemap(out) const KPosition & {
   $result = PyTuple_New(2);
   PyTuple_SetItem($result, 0, PyInt_FromLong($1.x));
   PyTuple_SetItem($result, 1, PyInt_FromLong($1.y));
}

%typemap(out) KPosition {
   $result = PyTuple_New(2);
   PyTuple_SetItem($result, 0, PyInt_FromLong($1.x));
   PyTuple_SetItem($result, 1, PyInt_FromLong($1.y));
}

%typemap(freearg) const KPosition & {
   if ($1) delete $1;
}
