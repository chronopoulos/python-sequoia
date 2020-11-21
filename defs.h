#ifndef DEFS_H
#define DEFS_H

#if PY_MAJOR_VERSION >= 3
    #define DEF_LONG PyLong_FromLong
    #define DEF_STRING PyUnicode_FromString
#else
    #define DEF_LONG PyInt_FromLong
    #define DEF_STRING PyString_FromString
#endif

#endif
