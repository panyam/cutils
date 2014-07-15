
#ifndef __CUTILS_MAP_H__
#define __CUTILS_MAP_H__

#include "cucollection.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Returns true if the map contains a particular key.
 */
typedef BOOL (*CUMapContainsKeyFunc)(const CUMap *map, CUString *key);

/**
 * Gets the value for a particular key.
 */
typedef CUObject *(*CUMapGetItemForKeyFunc)(const CUMap *map, CUObject *key);

/**
 * Puts the value for a particular key.
 */
typedef CUObject *(*CUMapPutItemForKeyFunc)(const CUMap *map, CUObject *key, void *value);

/**
 * Puts all values from a map into this map.
 */
typedef void (*CUMapPutAllItemsFunc)(const CUMap *map, const CUMap *another);

/**
 * Removes a value given by the particular key.
 */
typedef CUObject *(*CUMapRemoveItemForKeyFunc)(const CUMap *map, CUObject *key);

/**
 * Returns the keys as a set.
 */
typedef CUSet *(*CUMapKeySetFunc)(const CUMap *map);

/**
 * Returns all values as a collection.
 */
typedef CUCollection *(*CUMapValuesFunc)(const CUMap *map);

CU_INHERIT_STRUCT(CUMapPrototype, CUCollectionPrototype,
    CUMapContainsKeyFunc containsKeyFunc;
    CUMapGetItemForKeyFunc getItemForKeyFunc;
    CUMapPutItemForKeyFunc putItemForKeyFunc;
    CUMapRemoveItemForKeyFunc removeItemForKeyFunc;
    CUMapKeySetFunc keySetFunc;
    CUMapValuesFunc valuesFunc;
);

/**
 * Creates an empty map.
 */
extern CUMap *cu_map_create();

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

