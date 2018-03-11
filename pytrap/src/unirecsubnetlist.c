#include <Python.h>
#include <structmember.h>
#include <unirec/ip_prefix_search.h>
#include "unirecsubnetlist.h"
#include "unirecipaddr.h"
#include "pytrapexceptions.h"

int
UnirecSubnetList_init(pytrap_unirecsubnetlist *s, PyObject *args)
{
   if (s != NULL) {
        s->context = NULL;
        s->network_list.networks = NULL;
        s->network_list.net_count = 0;

    } else {
        return -1;
    }

    return 0;
}

static PyObject *
UnirecSubnetList_addNetwork(pytrap_unirecsubnetlist *self, PyObject *args, PyObject *kwds)
{
    char *cidr = NULL;
    char buf[50];
    ip_addr_t ip;

    if (!PyArg_ParseTuple(args, "s", &cidr)) {
        return NULL;
    }

    char *mask_ptr = strchr(cidr, '/');
    if (mask_ptr == NULL) {
        PyErr_SetString(TrapError, "Expected IP/mask format.");
        return NULL;
    }

    strncpy(buf, cidr, mask_ptr - cidr);
    buf[mask_ptr - cidr] = 0;

    ip_from_str(buf, &ip);

    uint32_t cur_count = self->network_list.net_count;

    if (self->network_list.networks == NULL) {
        self->network_list.networks = calloc(1, sizeof(ipps_network_t));
        if (self->network_list.networks == NULL) {
            PyErr_SetString(PyExc_MemoryError, "Allocation of end address failed.");
            return NULL;
        }
    } else {
        void *ret = realloc(self->network_list.networks, (cur_count + 1) * sizeof(ipps_network_t));
        if (ret == NULL) {
            /* error */
            PyErr_SetString(PyExc_MemoryError, "Allocation of end address failed.");
            return NULL;
        }
        self->network_list.networks = ret;
    }

    /* insert new subnet into array */
    memcpy(&self->network_list.networks[cur_count].addr, &ip, sizeof(ip_addr_t));
    self->network_list.networks[cur_count].mask = atoi(++mask_ptr);
    self->network_list.networks[cur_count].data = 0;
    self->network_list.networks[cur_count].data_len = 0;

    self->network_list.net_count++;

    Py_RETURN_NONE;
}

static int
UnirecSubnetList_createContext(pytrap_unirecsubnetlist *self)
{
	self->context = ipps_init(&self->network_list);
    
    Py_RETURN_NONE;
}

static int
UnirecSubnetList_contains(PyObject *o, PyObject *v)
{
    pytrap_unirecsubnetlist *self = (pytrap_unirecsubnetlist *) o;
    void **pdata;

    if (PyObject_IsInstance(v, (PyObject *) &pytrap_UnirecIPAddr)) {
        pytrap_unirecipaddr *value = (pytrap_unirecipaddr *) v;

        if (ipps_search(&value->ip, self->context, &pdata)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "UnirecIPAddr object expected.");
        return -1;
    }
}

static PyObject *
UnirecSubnetList_str(pytrap_unirecsubnetlist *self)
{
    // TODO
}

static PyMethodDef pytrap_unirecsubnetlist_methods[] = {
    {"addNetwork", (PyCFunction) UnirecSubnetList_addNetwork, METH_VARARGS | METH_KEYWORDS,
        "TODO\n\n"
        "Returns:\n"
        "    bool: True\n"
        },
    {"createContext", (PyCFunction) UnirecSubnetList_createContext, METH_NOARGS,
        "TODO.\n\n"
        "Returns:\n"
        "    bool: True\n"
        },

    {NULL}
};


static PySequenceMethods UnirecSubnetList_seqmethods = {
    0, /* lenfunc sq_length; */
    0, /* binaryfunc sq_concat; */
    0, /* ssizeargfunc sq_repeat; */
    0, /* ssizeargfunc sq_item; */
    0, /* void *was_sq_slice; */
    0, /* ssizeobjargproc sq_ass_item; */
    0, /* void *was_sq_ass_slice; */
    (objobjproc) UnirecSubnetList_contains, /* objobjproc sq_contains; */
    0, /* binaryfunc sq_inplace_concat; */
    0 /* ssizeargfunc sq_inplace_repeat; */
};

PyTypeObject pytrap_UnirecSubnetList = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pytrap.UnirecSubnetList",          /* tp_name */
    sizeof(pytrap_unirecsubnetlist),    /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0, /* tp_repr */
    0, /* tp_as_number */
    &UnirecSubnetList_seqmethods,  /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,//TODO (reprfunc) UnirecSubnetList_str,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "UnirecSubnetList\n"
    "    Class for nothing.\n\n"
    "    Args: None\n",  /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pytrap_unirecsubnetlist_methods,             /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) UnirecSubnetList_init,                         /* tp_init */
    0,                         /* tp_alloc */
    PyType_GenericNew,         /* tp_new */
};

