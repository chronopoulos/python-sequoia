#ifndef DEFS_H
#define DEFS_H

#if PY_MAJOR_VERSION >= 3
    #define FROMLONG PyLong_FromLong
    #define FROMSTRING PyUnicode_FromString
    #define ASSTRING PyUnicode_AsUTF8
#else
    #define FROMLONG PyInt_FromLong
    #define FROMSTRING PyString_FromString
    #define ASSTRING PyString_AsString
#endif

#endif
