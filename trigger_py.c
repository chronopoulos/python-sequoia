#include "types_py.h"
#include "structmember.h"
#include "defs.h"

static int Trigger_init(Trigger_Data *self, PyObject *args, PyObject *kwds) {

    self->trig = sq_trigger_new();

    return 0;

}

static PyObject *Trigger_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {

    Trigger_Data *self;
    self = (Trigger_Data *) type->tp_alloc(type, 0);
    return (PyObject *) self;

}

static void Trigger_del(Trigger_Data *self) {

    sq_trigger_delete(self->trig);
    Py_TYPE(self)->tp_free((PyObject *) self);

}

static PyObject *Trigger_repr(Trigger_Data *self, PyObject *unused) {

    return FROMSTRING("<sequoia trigger>");

}

static PyObject* Trigger_get_type(Trigger_Data *self, void *closure) {

    return FROMLONG(sq_trigger_get_type(self->trig));

}

static int Trigger_set_type(Trigger_Data *self, PyObject *value, void *closure) {

    int type = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    // TODO constrain to enum TRIG_TYPE

    sq_trigger_set_type(self->trig, type);

    return 0;

}

static PyObject* Trigger_get_note_value(Trigger_Data *self, void *closure) {

    return FROMLONG(sq_trigger_get_note_value(self->trig));

}

static int Trigger_set_note_value(Trigger_Data *self, PyObject *value, void *closure) {

    int note_value = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (note_value < 0) {
        PyErr_SetString(PyExc_ValueError, "note_value must be positive");
        return -1;
    }

    sq_trigger_set_note_value(self->trig, note_value);

    return 0;

}

static PyObject* Trigger_get_note_velocity(Trigger_Data *self, void *closure) {

    return FROMLONG(sq_trigger_get_note_velocity(self->trig));

}

static int Trigger_set_note_velocity(Trigger_Data *self, PyObject *value, void *closure) {

    int note_velocity = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (note_velocity < 0) {
        PyErr_SetString(PyExc_ValueError, "note_velocity must be positive");
        return -1;
    }

    sq_trigger_set_note_velocity(self->trig, note_velocity);

    return 0;

}

static PyObject* Trigger_get_note_length(Trigger_Data *self, void *closure) {

    return PyFloat_FromDouble(sq_trigger_get_note_length(self->trig));

}

static int Trigger_set_note_length(Trigger_Data *self, PyObject *value, void *closure) {

    int note_length = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    // TODO constrain value

    sq_trigger_set_note_length(self->trig, note_length);

    return 0;

}

static PyObject* Trigger_get_cc_number(Trigger_Data *self, void *closure) {

    return FROMLONG(sq_trigger_get_cc_number(self->trig));

}

static int Trigger_set_cc_number(Trigger_Data *self, PyObject *value, void *closure) {

    int cc_number = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    // TODO constrain value

    sq_trigger_set_cc_number(self->trig, cc_number);

    return 0;

}

static PyObject* Trigger_get_cc_value(Trigger_Data *self, void *closure) {

    return FROMLONG(sq_trigger_get_cc_value(self->trig));

}

static int Trigger_set_cc_value(Trigger_Data *self, PyObject *value, void *closure) {

    int cc_value = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    // TODO constrain value

    sq_trigger_set_cc_value(self->trig, cc_value);

    return 0;

}

static PyObject* Trigger_get_probability(Trigger_Data *self, void *closure) {

    return PyFloat_FromDouble(sq_trigger_get_probability(self->trig));

}

static int Trigger_set_probability(Trigger_Data *self, PyObject *value, void *closure) {

    float probability = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_trigger_set_probability(self->trig, probability);

    return 0;

}

static PyObject* Trigger_get_microtime(Trigger_Data *self, void *closure) {

    return PyFloat_FromDouble(sq_trigger_get_microtime(self->trig));

}

static int Trigger_set_microtime(Trigger_Data *self, PyObject *value, void *closure) {

    float microtime = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_trigger_set_microtime(self->trig, microtime);

    return 0;

}

static PyObject* Trigger_get_channel(Trigger_Data *self, void *closure) {

    return FROMLONG(sq_trigger_get_channel(self->trig));

}

static int Trigger_set_channel(Trigger_Data *self, PyObject *value, void *closure) {

    int channel = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_trigger_set_channel(self->trig, channel);

    return 0;

}

static PyMethodDef Trigger_methods[] = {
    {NULL}
};

static PyMemberDef Trigger_members[] = {
    {NULL}
};

static PyGetSetDef Trigger_getset[] = {
    {"type", (getter) Trigger_get_type, (setter) Trigger_set_type, NULL, NULL},
    {"note_value", (getter) Trigger_get_note_value, (setter) Trigger_set_note_value, NULL, NULL},
    {"note_velocity", (getter) Trigger_get_note_velocity, (setter) Trigger_set_note_velocity, NULL, NULL},
    {"note_length", (getter) Trigger_get_note_length, (setter) Trigger_set_note_length, NULL, NULL},
    {"cc_number", (getter) Trigger_get_cc_number, (setter) Trigger_set_cc_number, NULL, NULL},
    {"cc_value", (getter) Trigger_get_cc_value, (setter) Trigger_set_cc_value, NULL, NULL},
    {"probability", (getter) Trigger_get_probability, (setter) Trigger_set_probability, NULL, NULL},
    {"microtime", (getter) Trigger_get_microtime, (setter) Trigger_set_microtime, NULL, NULL},
    {"channel", (getter) Trigger_get_channel, (setter) Trigger_set_channel, NULL, NULL},
    {NULL}
};

PyTypeObject Trigger_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sequoia.trigger",                 /* tp_name           */
    sizeof (Trigger_Data),             /* tp_basicsize      */
    0,                            /* tp_itemsize       */
    (destructor) Trigger_del,     /* tp_dealloc        */
    0,                            /* tp_print          */
    0,                            /* tp_getattr        */
    0,                            /* tp_setattr        */
    0,                            /* tp_compare        */
    (reprfunc) Trigger_repr,      /* tp_repr           */
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
    //Trigger_doc,                  /* tp_doc            */
    0,                  /* tp_doc            */

    0,                            /* tp_traverse       */
    0,                            /* tp_clear          */
    0,                            /* tp_richcompare    */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter           */
    0,                            /* tp_iternext       */

    Trigger_methods,              /* tp_methods        */
    Trigger_members,              /* tp_members        */
    Trigger_getset,               /* tp_getset         */

    0,                            /* tp_base           */
    0,                            /* tp_dict           */
    0,                            /* tp_descr_get      */
    0,                            /* tp_descr_set      */
    0,                            /* tp_dictoffset     */
    (initproc) Trigger_init,      /* tp_init           */
    0,                            /* tp_alloc          */
    Trigger_new,                  /* tp_new            */
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
