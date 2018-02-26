
#ifndef UNIRECSUBNETLIST_H
#define UNIRECSUBNETLIST_H

typedef struct 
{
	PyObject_HEAD
	network_list_t * network_list;
	unsigned network_list_alloc_size;
	ipps_context_t * context;
} pytrap_unirecsubnetlist;

PyAPI_DATA(PyTypeObject) pytrap_UnirecSubnetList;

#endif /* UNIRECIPADDR_H */