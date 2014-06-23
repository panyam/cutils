
#ifndef __CUTILS_ARRAY_H__
#define __CUTILS_ARRAY_H__

#include "cucollection.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Array specific prototype extensions.
 */
extern CUListPrototype *cu_array_prototype();

/**
 * Creates a new array.
 */
extern CUArray *cu_array_with_capacity(int capacity);

/*
 * Initialise an array.
 */
extern void cu_array_reserve(CUArray *array, int capacity);

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

