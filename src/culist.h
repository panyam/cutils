
#ifndef __CUTILS_LIST_H__
#define __CUTILS_LIST_H__

#include "cucollection.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Gets the item at a given index in the list.
 */
typedef CUObject *(*CUListGetItemAtFunc)(const CUList *list, int index);

/**
 * Sets the item at a given index in the list.
 */
typedef void (*CUListSetItemAtFunc)(const CUList *list, const CUObject *value, int index);

/**
 * Adds an item at a given index in the list.
 */
typedef void (*CUListAddItemAtFunc)(const CUList *list, const CUObject *value, int index);

/**
 * Removes an item at a given index in the list.
 */
typedef void (*CUListRemoveItemAtFunc)(const CUList *list, int index);

/**
 * Returns the index of a given object in the list.
 */
typedef int (*CUListIndexOfFunc)(const CUList *list, const CUObject *value);

/**
 * Splices a list.
 */
typedef CUList *(*CUListSpliceFunc)(const CUList *list, int startIndex, int endIndex);

CU_INHERIT_STRUCT(CUListPrototype, CUCollectionPrototype,
    CUListGetItemAtFunc getItemAtFunc;
    CUListSetItemAtFunc setItemAtFunc;
    CUListAddItemAtFunc addItemAtFunc;
    CUListRemoveItemAtFunc removeItemAtFunc;
    CUListIndexOfFunc indexOfFunc;
    CUListSpliceFunc spliceFunc;
);

#define cu_list_get_item_at(list, index)            GET_PROTOTYPE(list, CUListPrototype)->getItemAtFunc((CUList *)(list), index)
#define cu_list_set_item_at(list, value, index)     GET_PROTOTYPE(list, CUListPrototype)->setItemAtFunc((CUList *)(list), (const CUObject *)value, index)
#define cu_list_add_item_at(list, value, index)     GET_PROTOTYPE(list, CUListPrototype)->addItemAtFunc((CUList *)(list), (const CUObject *)value, index)
#define cu_list_remove_item_at(list, index)         GET_PROTOTYPE(list, CUListPrototype)->removeItemAtFunc((CUList *)(list), index)
#define cu_list_index_of(list, item)                GET_PROTOTYPE(list, CUListPrototype)->indexOfFunc((CUList *)(list), (const CUObject *)item)
#define cu_list_splice(list, startIndex, endIndex)  GET_PROTOTYPE(list, CUListPrototype)->spliceFunc((CUList *)(list), startIndex, endIndex)
#define cu_list_push_back(list, value)              cu_list_add_item_at(list, value, -1)
#define cu_list_push_front(list, value)             cu_list_add_item_at(list, value, 0)

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

