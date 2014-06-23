

#ifndef __CUTILS_LINKEDLIST_H__
#define __CUTILS_LINKEDLIST_H__

#include "culist.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Linked list specific prototype extensions.
 */
extern CUListPrototype *cu_linkedlist_prototype();

/**
 * Creates a new list.
 *
 * \returns A new CUList instance.
 */
extern CULinkedList *cu_linkedlist();

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

