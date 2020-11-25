#include "types_py.h"
#include "structmember.h"
#include "defs.h"

static int Outport_init(Outport_Data *self, PyObject *args, PyObject *kwds) {

    char *name;

    if (!PyArg_ParseTuple(args, "s", &name)) {
        return -1;
    }

    self->outport = sq_outport_new(name);

    return 0;

}

static PyObject *Outport_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {

    Outport_Data *self;
    self = (Outport_Data *) type->tp_alloc(type, 0);
    return (PyObject *) self;

}

static void Outport_del(Outport_Data *self) {

    sq_outport_delete(self->outport);
    Py_TYPE(self)->tp_free((PyObject *) self);

}

static PyObject *Outport_repr(Outport_Data *self, PyObject *unused) {

    PyObject *result = NULL;
    char result_str[96];

    sprintf(result_str, "<sequoia out-port: %s>", sq_outport_get_name(self->outport));
    result = FROMSTRING(result_str);

    return result;

}

static PyObject* Outport_get_name(Outport_Data *self, void *closure) {

    return FROMSTRING(sq_outport_get_name(self->outport));

}

static int Outport_set_name(Outport_Data *self, PyObject *value, void *closure) {

    const char *name = ASSTRING(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    sq_outport_set_name(self->outport, name);

    return 0;

}

static PyMethodDef Outport_methods[] = {
    {NULL}
};

static PyMemberDef Outport_members[] = {
    {NULL}
};

static PyGetSetDef Outport_getset[] = {
    {"name", (getter) Outport_get_name, (setter) Outport_set_name, NULL, NULL},
    {NULL}
};

PyTypeObject Outport_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sequoia.Outport",                 /* tp_name           */
    sizeof (Outport_Data),             /* tp_basicsize      */
    0,                            /* tp_itemsize       */
    (destructor) Outport_del,     /* tp_dealloc        */
    0,                            /* tp_print          */
    0,                            /* tp_getattr        */
    0,                            /* tp_setattr        */
    0,                            /* tp_compare        */
    (reprfunc) Outport_repr,      /* tp_repr           */
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
    //Outport_doc,                  /* tp_doc            */
    0,                  /* tp_doc            */

    0,                            /* tp_traverse       */
    0,                            /* tp_clear          */
    0,                            /* tp_richcompare    */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter           */
    0,                            /* tp_iternext       */

    Outport_methods,              /* tp_methods        */
    Outport_members,              /* tp_members        */
    Outport_getset,               /* tp_getset         */

    0,                            /* tp_base           */
    0,                            /* tp_dict           */
    0,                            /* tp_descr_get      */
    0,                            /* tp_descr_set      */
    0,                            /* tp_dictoffset     */
    (initproc) Outport_init,      /* tp_init           */
    0,                            /* tp_alloc          */
    Outport_new,                  /* tp_new            */
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
