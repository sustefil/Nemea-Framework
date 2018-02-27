
#ifndef UNIRECSUBNETLIST_H
#define UNIRECSUBNETLIST_H

#include <unirec/ip_prefix_search.h>

typedef struct 
{
	PyObject_HEAD
	ipps_network_list_t network_list;
	ipps_context_t *context;
} pytrap_unirecsubnetlist;

PyAPI_DATA(PyTypeObject) pytrap_UnirecSubnetList;

#endif /* UNIRECIPADDR_H */
