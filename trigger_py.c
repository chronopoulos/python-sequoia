#include "types_py.h"

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

    return PyUnicode_FromString("<sequoia trigger>");

}

static PyObject *Trigger_set_type(Trigger_Data *self, PyObject *args) {

    int type;

    if (!PyArg_ParseTuple(args, "i", &type)) {
        return NULL;
    }

    sq_trigger_set_type(self->trig, type);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_note_value(Trigger_Data *self, PyObject *args) {

    int note;

    if (!PyArg_ParseTuple(args, "i", &note)) {
        return NULL;
    }

    sq_trigger_set_note_value(self->trig, note);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_note_velocity(Trigger_Data *self, PyObject *args) {

    int vel;

    if (!PyArg_ParseTuple(args, "i", &vel)) {
        return NULL;
    }

    sq_trigger_set_note_velocity(self->trig, vel);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_note_length(Trigger_Data *self, PyObject *args) {

    float length;

    if (!PyArg_ParseTuple(args, "f", &length)) {
        return NULL;
    }

    sq_trigger_set_note_length(self->trig, length);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_cc_number(Trigger_Data *self, PyObject *args) {

    int cc_number;

    if (!PyArg_ParseTuple(args, "i", &cc_number)) {
        return NULL;
    }

    sq_trigger_set_cc_number(self->trig, cc_number);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_cc_value(Trigger_Data *self, PyObject *args) {

    int cc_value;

    if (!PyArg_ParseTuple(args, "i", &cc_value)) {
        return NULL;
    }

    sq_trigger_set_cc_value(self->trig, cc_value);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_probability(Trigger_Data *self, PyObject *args) {

    float probability;

    if (!PyArg_ParseTuple(args, "f", &probability)) {
        return NULL;
    }

    sq_trigger_set_probability(self->trig, probability);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_microtime(Trigger_Data *self, PyObject *args) {

    float microtime;

    if (!PyArg_ParseTuple(args, "f", &microtime)) {
        return NULL;
    }

    sq_trigger_set_microtime(self->trig, microtime);

    Py_RETURN_NONE;

}

static PyObject *Trigger_set_channel(Trigger_Data *self, PyObject *args) {

    int channel;

    if (!PyArg_ParseTuple(args, "i", &channel)) {
        return NULL;
    }

    sq_trigger_set_channel(self->trig, channel);

    Py_RETURN_NONE;

}

static PyMethodDef Trigger_methods[] = {

    {"set_type", (PyCFunction) Trigger_set_type, METH_VARARGS, NULL},
    {"set_note_value", (PyCFunction) Trigger_set_note_value, METH_VARARGS, NULL},
    {"set_note_velocity", (PyCFunction) Trigger_set_note_velocity, METH_VARARGS, NULL},
    {"set_note_length", (PyCFunction) Trigger_set_note_length, METH_VARARGS, NULL},
    {"set_cc_number", (PyCFunction) Trigger_set_cc_number, METH_VARARGS, NULL},
    {"set_cc_value", (PyCFunction) Trigger_set_cc_value, METH_VARARGS, NULL},
    {"set_probability", (PyCFunction) Trigger_set_probability, METH_VARARGS, NULL},
    {"set_microtime", (PyCFunction) Trigger_set_microtime, METH_VARARGS, NULL},
    {"set_channel", (PyCFunction) Trigger_set_channel, METH_VARARGS, NULL},
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

    // TODO
    Trigger_methods,              /* tp_methods        */
    //Trigger_members,              /* tp_members        */
    //Trigger_getseters,            /* tp_getset         */
    0,              /* tp_members        */
    0,            /* tp_getset         */

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
