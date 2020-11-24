#include "types_py.h"
#include "structmember.h"
#include "defs.h"

static int Inport_init(Inport_Data *self, PyObject *args, PyObject *kwds) {

    char *name;

    if (!PyArg_ParseTuple(args, "s", &name)) {
        return -1;
    }

    self->inport = sq_inport_new(name);

    return 0;

}

static PyObject *Inport_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {

    Inport_Data *self;
    self = (Inport_Data *) type->tp_alloc(type, 0);
    return (PyObject *) self;

}

static void Inport_del(Inport_Data *self) {

    sq_inport_delete(self->inport);
    Py_TYPE(self)->tp_free((PyObject *) self);

}

static PyObject *Inport_repr(Inport_Data *self, PyObject *unused) {

    PyObject *result = NULL;
    char result_str[96];

    sprintf(result_str, "<sequoia in-port: %s>", sq_inport_get_name(self->inport));
    result = FROMSTRING(result_str);

    return result;

}

static PyObject* Inport_get_name(Inport_Data *self, void *closure) {

    return FROMSTRING(sq_inport_get_name(self->inport));

}

static int Inport_set_name(Inport_Data *self, PyObject *value, void *closure) {

    const char *name = ASSTRING(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_inport_set_name(self->inport, name);

    return 0;

}

static PyObject* Inport_get_type(Inport_Data *self, void *closure) {

    return FROMLONG(sq_inport_get_type(self->inport));

}

static int Inport_set_type(Inport_Data *self, PyObject *value, void *closure) {

    int type = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_inport_set_type(self->inport, type);

    return 0;

}

static PyMethodDef Inport_methods[] = {
    {NULL}
};

static PyMemberDef Inport_members[] = {
    {NULL}
};

static PyGetSetDef Inport_getset[] = {
    {"name", (getter) Inport_get_name, (setter) Inport_set_name, NULL, NULL},
    {"type", (getter) Inport_get_type, (setter) Inport_set_type, NULL, NULL},
    {NULL}
};

PyTypeObject Inport_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sequoia.inport",             /* tp_name           */
    sizeof (Inport_Data),         /* tp_basicsize      */
    0,                            /* tp_itemsize       */
    (destructor) Inport_del,      /* tp_dealloc        */
    0,                            /* tp_print          */
    0,                            /* tp_getattr        */
    0,                            /* tp_setattr        */
    0,                            /* tp_compare        */
    (reprfunc) Inport_repr,       /* tp_repr           */
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
    //Inport_doc,                  /* tp_doc            */
    0,                  /* tp_doc            */

    0,                            /* tp_traverse       */
    0,                            /* tp_clear          */
    0,                            /* tp_richcompare    */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter           */
    0,                            /* tp_iternext       */

    Inport_methods,               /* tp_methods        */
    Inport_members,               /* tp_members        */
    Inport_getset,                /* tp_getset         */

    0,                            /* tp_base           */
    0,                            /* tp_dict           */
    0,                            /* tp_descr_get      */
    0,                            /* tp_descr_set      */
    0,                            /* tp_dictoffset     */
    (initproc) Inport_init,      /* tp_init           */
    0,                            /* tp_alloc          */
    Inport_new,                  /* tp_new            */
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
