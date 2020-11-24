#include "types_py.h"
#include "structmember.h"
#include "defs.h"

static int Sequence_init(Sequence_Data *self, PyObject *args, PyObject *kwds) {

    int nsteps;

    if (!PyArg_ParseTuple(args, "i", &nsteps)) {
        return -1;
    }

    self->seq = sq_sequence_new(nsteps);

    return 0;

}

static PyObject *Sequence_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {

    Sequence_Data *self;
    self = (Sequence_Data *) type->tp_alloc(type, 0);
    return (PyObject *) self;

}

static void Sequence_del(Sequence_Data *self) {

    sq_sequence_delete(self->seq);
    Py_TYPE(self)->tp_free((PyObject *) self);

}

static PyObject *Sequence_repr(Sequence_Data *self, PyObject *unused) {

    PyObject *result = NULL;
    char result_str[96];

    sprintf(result_str, "<sequoia sequence: '%s' with %d steps>",
            sq_sequence_get_name(self->seq), sq_sequence_get_nsteps(self->seq));

    result = FROMSTRING(result_str);

    return result;


}

static PyObject* Sequence_get_name(Sequence_Data *self, void *closure) {

    return FROMSTRING(sq_sequence_get_name(self->seq));

}

static int Sequence_set_name(Sequence_Data *self, PyObject *value, void *closure) {

    const char *name = ASSTRING(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_name(self->seq, name);

    return 0;

}

static PyObject* Sequence_get_transpose(Sequence_Data *self, void *closure) {

    return FROMLONG(sq_sequence_get_transpose(self->seq));

}

static int Sequence_set_transpose(Sequence_Data *self, PyObject *value, void *closure) {

    int transpose = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_transpose(self->seq, transpose);

    return 0;

}

static PyObject* Sequence_get_playhead(Sequence_Data *self, void *closure) {

    return FROMLONG(sq_sequence_get_playhead(self->seq));

}

static int Sequence_set_playhead(Sequence_Data *self, PyObject *value, void *closure) {

    int ph = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_playhead(self->seq, ph);

    return 0;

}

static PyObject* Sequence_get_clockdivide(Sequence_Data *self, void *closure) {

    return FROMLONG(sq_sequence_get_clockdivide(self->seq));

}

static int Sequence_set_clockdivide(Sequence_Data *self, PyObject *value, void *closure) {

    int clockdivide = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_clockdivide(self->seq, clockdivide);

    return 0;

}

static PyObject* Sequence_get_mute(Sequence_Data *self, void *closure) {

    return PyBool_FromLong(sq_sequence_get_mute(self->seq));

}

static int Sequence_set_mute(Sequence_Data *self, PyObject *value, void *closure) {

    bool mute = PyObject_IsTrue(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_mute(self->seq, mute);

    return 0;

}

static PyObject* Sequence_get_first(Sequence_Data *self, void *closure) {

    return FROMLONG(sq_sequence_get_first(self->seq));

}

static int Sequence_set_first(Sequence_Data *self, PyObject *value, void *closure) {

    int first = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_first(self->seq, first);

    return 0;

}

static PyObject* Sequence_get_last(Sequence_Data *self, void *closure) {

    return FROMLONG(sq_sequence_get_last(self->seq));

}

static int Sequence_set_last(Sequence_Data *self, PyObject *value, void *closure) {

    int last = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_sequence_set_last(self->seq, last);

    return 0;

}

static PyObject *Sequence_set_trig(Sequence_Data *self, PyObject *args) {

    int stepIndex;
    PyObject *object;

    if (!PyArg_ParseTuple(args, "iO", &stepIndex, &object)) {
        return NULL;
    }

    sq_sequence_set_trig(self->seq, stepIndex, ((Trigger_Data*)object)->trig);

    Py_RETURN_NONE;

}

static PyObject *Sequence_clear_trig(Sequence_Data *self, PyObject *args) {

    int stepIndex;

    if (!PyArg_ParseTuple(args, "i", &stepIndex)) {
        return NULL;
    }

    sq_sequence_clear_trig(self->seq, stepIndex);

    Py_RETURN_NONE;

}

static PyObject *Sequence_set_outport(Sequence_Data *self, PyObject *args) {

    PyObject *object;

    if (!PyArg_ParseTuple(args, "O", &object)) {
        return NULL;
    }

    sq_sequence_set_outport(self->seq, ((Outport_Data*)object)->outport);

    Py_RETURN_NONE;

}

static PyObject *Sequence_pprint(Sequence_Data *self, PyObject *args) {

    sq_sequence_pprint(self->seq);

    Py_RETURN_NONE;

}

static PyObject *Sequence_get_nsteps(Sequence_Data *self, void *closure) {

    return FROMLONG(sq_sequence_get_nsteps(self->seq));

}

static PyObject *Sequence_set_notifications(Sequence_Data *self, PyObject *args) {

    PyObject *object;

    if (!PyArg_ParseTuple(args, "O", &object)) {
        Py_RETURN_NONE;
    }

    bool set = PyObject_IsTrue(object);
    if (PyErr_Occurred()) {
        Py_RETURN_NONE;
    }

    sq_sequence_set_notifications(self->seq, set);

    Py_RETURN_NONE;

}

static PyObject *Sequence_read_new_playhead(Sequence_Data *self, PyObject *args) {

    int ph;
    bool new;

    new = sq_sequence_read_new_playhead(self->seq, &ph);

    return Py_BuildValue("Oi", PyBool_FromLong(new), ph);

}

static PyMethodDef Sequence_methods[] = {

    {"set_outport", (PyCFunction) Sequence_set_outport, METH_VARARGS, NULL},
    {"set_trig", (PyCFunction) Sequence_set_trig, METH_VARARGS, NULL},
    {"clear_trig", (PyCFunction) Sequence_clear_trig, METH_VARARGS, NULL},
    {"pprint", (PyCFunction) Sequence_pprint, METH_NOARGS, NULL},
    {"set_notifications", (PyCFunction) Sequence_set_notifications, METH_VARARGS, NULL},
    {"read_new_playhead", (PyCFunction) Sequence_read_new_playhead, METH_VARARGS, NULL},
    {NULL}

};

static PyMemberDef Sequence_members[] = {
    {NULL}
};

static PyGetSetDef Sequence_getset[] = {
    {"name", (getter) Sequence_get_name, (setter) Sequence_set_name, NULL, NULL},
    {"nsteps", (getter) Sequence_get_nsteps, NULL, NULL, NULL},  // read-only
    {"transpose", (getter) Sequence_get_transpose, (setter) Sequence_set_transpose, NULL, NULL},
    {"playhead", (getter) Sequence_get_playhead, (setter) Sequence_set_playhead, NULL, NULL},
    {"clockdivide", (getter) Sequence_get_clockdivide, (setter) Sequence_set_clockdivide, NULL, NULL},
    {"mute", (getter) Sequence_get_mute, (setter) Sequence_set_mute, NULL, NULL},
    {"first", (getter) Sequence_get_first, (setter) Sequence_set_first, NULL, NULL},
    {"last", (getter) Sequence_get_last, (setter) Sequence_set_last, NULL, NULL},
    {NULL}
};

PyTypeObject Sequence_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sequoia.sequence",           /* tp_name           */
    sizeof (Sequence_Data),       /* tp_basicsize      */
    0,                            /* tp_itemsize       */
    (destructor) Sequence_del,    /* tp_dealloc        */
    0,                            /* tp_print          */
    0,                            /* tp_getattr        */
    0,                            /* tp_setattr        */
    0,                            /* tp_compare        */
    (reprfunc) Sequence_repr,     /* tp_repr           */
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
    //Sequence_doc,                  /* tp_doc            */
    0,                            /* tp_doc            */

    0,                            /* tp_traverse       */
    0,                            /* tp_clear          */
    0,                            /* tp_richcompare    */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter           */
    0,                            /* tp_iternext       */

    Sequence_methods,             /* tp_methods        */
    Sequence_members,             /* tp_members        */
    Sequence_getset,              /* tp_getset         */

    0,                            /* tp_base           */
    0,                            /* tp_dict           */
    0,                            /* tp_descr_get      */
    0,                            /* tp_descr_set      */
    0,                            /* tp_dictoffset     */
    (initproc) Sequence_init,     /* tp_init           */
    0,                            /* tp_alloc          */
    Sequence_new,                 /* tp_new            */
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
