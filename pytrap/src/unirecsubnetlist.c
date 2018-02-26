#include <Python.h>
#include <structmember.h>
#include "unirecsubnetlist.h"

int
Pokus_init(pytrap_pokus *s, PyObject *args)
{
	int val;

	if (s != NULL) {
        if (!PyArg_ParseTuple(args, "i", &val)) {
            return -1;
        }
    } else {
        return -1;
    }

    s->a = val;

    return 0;
}

static PyObject *
Pokus_dummy_metoda(pytrap_pokus *self)
{
    Py_RETURN_TRUE;
}

static int
Pokus_contains(PyObject *o, PyObject *v)
{
    // if (PyObject_IsInstance(v, (PyObject *) &pytrap_UnirecIPAddr)) {
    //     pytrap_unirecipaddr *object = (pytrap_unirecipaddr *) o;
    //     pytrap_unirecipaddr *value = (pytrap_unirecipaddr *) v;

    //     if (ip_cmp(&object->ip, &value->ip) == 0) {
    //         return 1;
    //     } else {
    //         return 0;
    //     }

    // } else {
    //     PyErr_SetString(PyExc_TypeError, "UnirecIPAddr object expected.");
    //     return -1;
    // }

    return 1;
}

static PyObject *
Pokus_str(pytrap_pokus *self)
{
    return PyUnicode_FromFormat("- %d -", self->a);
}

static PyMethodDef pytrap_pokus_methods[] = {
    {"dummy_metoda", (PyCFunction) Pokus_dummy_metoda, METH_NOARGS,
        "Does nothing.\n\n"
        "Returns:\n"
        "    bool: True\n"
        },

    {NULL}
};


static PySequenceMethods Pokus_seqmethods = {
    0, /* lenfunc sq_length; */
    0, /* binaryfunc sq_concat; */
    0, /* ssizeargfunc sq_repeat; */
    0, /* ssizeargfunc sq_item; */
    0, /* void *was_sq_slice; */
    0, /* ssizeobjargproc sq_ass_item; */
    0, /* void *was_sq_ass_slice; */
    (objobjproc) Pokus_contains, /* objobjproc sq_contains; */
    0, /* binaryfunc sq_inplace_concat; */
    0 /* ssizeargfunc sq_inplace_repeat; */
};

PyTypeObject pytrap_Pokus = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pytrap.Pokus",          /* tp_name */
    sizeof(pytrap_pokus),    /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0, /* tp_repr */
    0, /* tp_as_number */
    &Pokus_seqmethods,  /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    (reprfunc) Pokus_str,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Pokus\n"
    "    Class for nothing.\n\n"
    "    Args: None\n",  /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pytrap_pokus_methods,             /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) Pokus_init,                         /* tp_init */
    0,                         /* tp_alloc */
    PyType_GenericNew,         /* tp_new */
};

