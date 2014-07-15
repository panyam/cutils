

#ifndef __CUTILS_HASHMAP_H__
#define __CUTILS_HASHMAP_H__

#include "cumap.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Hash map specific prototype extensions.
 */
extern CUMapPrototype *cu_hashmap_prototype();

/**
 * Creates a new hash map
 *
 * \returns A new CUMap instance.
 */
extern CUHashMap *cu_hashmap(int initialCapacity, float loadFactor);

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

