#include "types_py.h"
#include "structmember.h"
#include "defs.h"

static int Session_init(Session_Data *self, PyObject *args, PyObject *kwds) {

    char *name;

    if (!PyArg_ParseTuple(args, "s", &name)) {
        return -1;
    }

    self->sesh = sq_session_new(name);

    return 0;

}

static PyObject *Session_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {

    Session_Data *self;
    self = (Session_Data *) type->tp_alloc(type, 0);
    return (PyObject *) self;

}

static void Session_del(Session_Data *self) {

    sq_session_delete(self->sesh);
    Py_TYPE(self)->tp_free((PyObject *) self);

}

static PyObject *Session_repr(Session_Data *self, PyObject *unused) {

    PyObject *result = NULL;
    char result_str[96];

    sprintf(result_str, "<sequoia session: '%s' at %.3f bpm>",
            sq_session_get_name(self->sesh), sq_session_get_bpm(self->sesh));

    result = FROMSTRING(result_str);

    return result;

}

static PyObject *Session_disconnect_jack(Session_Data *self, PyObject *unused) {

    sq_session_disconnect_jack(self->sesh);

    Py_RETURN_NONE;

}

static int Session_set_bpm(Session_Data *self, PyObject *value, void *closure) {

    float bpm = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_session_set_bpm(self->sesh, bpm);

    return 0;

}

static PyObject *Session_start(Session_Data *self, PyObject *unused) {

    sq_session_start(self->sesh);

    Py_RETURN_NONE;

}

static PyObject *Session_stop(Session_Data *self, PyObject *unused) {

    sq_session_stop(self->sesh);

    Py_RETURN_NONE;

}

static PyObject *Session_get_name(Session_Data *self, void *closure) {

    return FROMSTRING(sq_session_get_name(self->sesh));

}

static PyObject *Session_register_outport(Session_Data *self, PyObject *args) {

    PyObject *object;

    if (!PyArg_ParseTuple(args, "O", &object)) {
        return NULL;
    }

    sq_session_register_outport(self->sesh, ((Outport_Data*)object)->outport);

    Py_RETURN_NONE;

}

static PyObject *Session_register_inport(Session_Data *self, PyObject *args) {

    PyObject *object;

    if (!PyArg_ParseTuple(args, "O", &object)) {
        return NULL;
    }

    sq_session_register_inport(self->sesh, ((Inport_Data*)object)->inport);

    Py_RETURN_NONE;

}

static PyObject *Session_add_sequence(Session_Data *self, PyObject *args) {

    PyObject *object;

    if (!PyArg_ParseTuple(args, "O", &object)) {
        return NULL;
    }

    sq_session_add_sequence(self->sesh, ((Sequence_Data*)object)->seq);

    Py_RETURN_NONE;

}

static PyObject *Session_rm_sequence(Session_Data *self, PyObject *args) {

    PyObject *object;

    if (!PyArg_ParseTuple(args, "O", &object)) {
        return NULL;
    }

    sq_session_rm_sequence(self->sesh, ((Sequence_Data*)object)->seq);

    Py_RETURN_NONE;

}

static PyObject *Session_get_bpm(Session_Data *self, void *closure) {

    return PyFloat_FromDouble(sq_session_get_bpm(self->sesh));

}

static PyObject *Session_get_nseqs(Session_Data *self, void *closure) {

    return FROMLONG(sq_session_get_nseqs(self->sesh));

}

static PyObject *Session_get_ninports(Session_Data *self, void *closure) {

    return FROMLONG(sq_session_get_ninports(self->sesh));

}

static PyObject *Session_get_noutports(Session_Data *self, void *closure) {

    return FROMLONG(sq_session_get_noutports(self->sesh));

}

static PyObject *Session_save(Session_Data *self, PyObject *args) {

    char *filename;

    if (!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    sq_session_save(self->sesh, filename);

    Py_RETURN_NONE;

}

static PyObject *Session_get_seq(Session_Data *self, PyObject *args) {

    int index;

    if (!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    Sequence_Data *sequence_data;
    sequence_data = (Sequence_Data *) Sequence_Type.tp_alloc(&Sequence_Type, 0);
    sequence_data->seq = sq_session_get_seq(self->sesh, index);
    return (PyObject *) sequence_data;

}

static PyObject *Session_get_inport(Session_Data *self, PyObject *args) {

    int index;

    if (!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    Inport_Data *inport_data;
    inport_data = (Inport_Data *) Inport_Type.tp_alloc(&Inport_Type, 0);
    inport_data->inport = sq_session_get_inport(self->sesh, index);
    return (PyObject *) inport_data;

}

static PyObject *Session_get_outport(Session_Data *self, PyObject *args) {

    int index;

    if (!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    Outport_Data *outport_data;
    outport_data = (Outport_Data *) Outport_Type.tp_alloc(&Outport_Type, 0);
    outport_data->outport = sq_session_get_outport(self->sesh, index);
    return (PyObject *) outport_data;

}

static PyMethodDef Session_methods[] = {

    {"disconnect_jack", (PyCFunction) Session_disconnect_jack, METH_NOARGS, NULL},
    {"register_outport", (PyCFunction) Session_register_outport, METH_VARARGS, NULL},
    {"register_inport", (PyCFunction) Session_register_inport, METH_VARARGS, NULL},
    {"add_sequence", (PyCFunction) Session_add_sequence, METH_VARARGS, NULL},
    {"rm_sequence", (PyCFunction) Session_rm_sequence, METH_VARARGS, NULL},
    {"start", (PyCFunction) Session_start, METH_NOARGS, NULL},
    {"stop", (PyCFunction) Session_stop, METH_NOARGS, NULL},
    {"get_seq", (PyCFunction) Session_get_seq, METH_VARARGS, NULL},
    {"get_inport", (PyCFunction) Session_get_inport, METH_VARARGS, NULL},
    {"get_outport", (PyCFunction) Session_get_outport, METH_VARARGS, NULL},
    {"save", (PyCFunction) Session_save, METH_VARARGS, NULL},
    {NULL}

};

static PyMemberDef Session_members[] = {
    {NULL}
};

static PyGetSetDef Session_getset[] = {
    {"bpm", (getter) Session_get_bpm, (setter) Session_set_bpm, NULL, NULL},
    {"name", (getter) Session_get_name, NULL, NULL, NULL},  // read-only (for now)
    {"nseqs", (getter) Session_get_nseqs, NULL, NULL, NULL},  // read-only
    {"ninports", (getter) Session_get_ninports, NULL, NULL, NULL},  // read-only
    {"noutports", (getter) Session_get_noutports, NULL, NULL, NULL},  // read-only
    {NULL}
};

PyTypeObject Session_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sequoia.Session",                 /* tp_name           */
    sizeof (Session_Data),             /* tp_basicsize      */
    0,                            /* tp_itemsize       */
    (destructor) Session_del,     /* tp_dealloc        */
    0,                            /* tp_print          */
    0,                            /* tp_getattr        */
    0,                            /* tp_setattr        */
    0,                            /* tp_compare        */
    (reprfunc) Session_repr,      /* tp_repr           */
    0,                            /* tp_as_number      */
    0, //&Py_cvec_tp_as_sequence, /* tp_as_sequence    */
    0,                            /* tp_as_mapping     */
    0,                            /* tp_hash           */
    0,                            /* tp_call           */
    0,                            /* tp_str            */
    0,                            /* tp_getattro       */
    0,                            /* tp_setattro       */
    0,                            /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT,           /* tp_flags          */

    // TODO
    //Session_doc,                  /* tp_doc            */
    0,                  /* tp_doc            */

    0,                            /* tp_traverse       */
    0,                            /* tp_clear          */
    0,                            /* tp_richcompare    */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter           */
    0,                            /* tp_iternext       */

    Session_methods,              /* tp_methods        */
    Session_members,              /* tp_members        */
    Session_getset,               /* tp_getset         */

    0,                            /* tp_base           */
    0,                            /* tp_dict           */
    0,                            /* tp_descr_get      */
    0,                            /* tp_descr_set      */
    0,                            /* tp_dictoffset     */
    (initproc) Session_init,      /* tp_init           */
    0,                            /* tp_alloc          */
    Session_new,                  /* tp_new            */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
