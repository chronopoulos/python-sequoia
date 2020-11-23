#include "types_py.h"
#include "defs.h"

static PyObject* Module_load(PyObject *self, PyObject *args) {

    char *name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }

    Session_Data *session_data;
    session_data = (Session_Data *) Session_Type.tp_alloc(&Session_Type, 0);
    session_data->sesh = sq_session_load(name);
    return (PyObject *) session_data;

}

static PyMethodDef ModuleMethods[] =
{
    {"load", Module_load, METH_VARARGS, "load from .sqa file"},
    {0, 0},
};


static PyObject *initsequoia_worker(void) {

    PyObject *m = NULL;

    if (PyType_Ready(&Session_Type) < 0) {
        return m;
    }

    if (PyType_Ready(&Sequence_Type) < 0) {
        return m;
    }

    if (PyType_Ready(&Trigger_Type) < 0) {
        return m;
    }

    if (PyType_Ready(&Outport_Type) < 0) {
        return m;
    }

    // inport needs special handling for class attributes
    if ( !(Inport_Type.tp_dict = PyDict_New()) ) {
        return m;
    }
    if (PyType_Ready(&Inport_Type) < 0) {
        return m;
    }

    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("NONE"),
                    DEF_LONG(INPORT_NONE));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("TRANSPOSE"),
                    DEF_LONG(INPORT_TRANSPOSE));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("PLAYHEAD"),
                    DEF_LONG(INPORT_PLAYHEAD));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("CLOCKDIVIDE"),
                    DEF_LONG(INPORT_CLOCKDIVIDE));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("DIRECTION"),
                    DEF_LONG(INPORT_DIRECTION));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("MUTE"),
                    DEF_LONG(INPORT_MUTE));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("FIRST"),
                    DEF_LONG(INPORT_FIRST));
    PyDict_SetItem(Inport_Type.tp_dict, DEF_STRING("LAST"),
                    DEF_LONG(INPORT_LAST));

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
       PyModuleDef_HEAD_INIT,
       "sequoia",         /* m_name */
       NULL,              /* m_doc */
       -1,                /* m_size */
       ModuleMethods,     /* m_methods (PyMethodDef*) */
       NULL,              /* m_reload */
       NULL,              /* m_traverse */
       NULL,              /* m_clear */
       NULL,              /* m_free */
    };
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule("sequoia", ModuleMethods);
#endif

    Py_INCREF (&Session_Type);
    PyModule_AddObject (m, "session", (PyObject *) &Session_Type);

    Py_INCREF (&Sequence_Type);
    PyModule_AddObject (m, "sequence", (PyObject *) &Sequence_Type);

    Py_INCREF (&Trigger_Type);
    PyModule_AddObject (m, "trigger", (PyObject *) &Trigger_Type);

    Py_INCREF (&Outport_Type);
    PyModule_AddObject (m, "outport", (PyObject *) &Outport_Type);

    Py_INCREF (&Inport_Type);
    PyModule_AddObject (m, "inport", (PyObject *) &Inport_Type);

    return m;

}

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_sequoia(void) {
    return initsequoia_worker();
}
#else
PyMODINIT_FUNC initsequoia(void) {
    initsequoia_worker();
}
#endif
