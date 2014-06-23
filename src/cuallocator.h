

#ifndef __CUTILS_ALLOCATOR_H__
#define __CUTILS_ALLOCATOR_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

// These defines specify whether garbage collection should be defined or not.
// By disabling these variables, these can be made into no-ops so that run 
// time performance is not affected.
#define ENABLE_REFERENCE_COUNTING
// #define ENABLE_GARBAGE_COLLECTION

/**
 * Allocates a given number of bytes of memory.
 */
typedef void *(*CUAllocatorAllocFunc)(CUAllocator *allocator, size_t size, unsigned initial_refcount);

/**
 * Reallocates a given address to the new size.
 * This MUST have been allocated with CUAllocatorAllocFunc or CUAllocatorReallocFunc.
 */
typedef void *(*CUAllocatorReallocFunc)(CUAllocator *allocator, void *memory, size_t newsize);

/**
 * Deallocates a bit of memory.  
 * This MUST have been allocated with CUAllocatorAllocFunc or CUAllocatorReallocFunc.
 */
typedef void (*CUAllocatorDeallocFunc)(CUAllocator *allocator, void *object);

/**
 * Increments the ref count of a particular object and returns the same object.
 */
typedef void *(*CUAllocatorIncrefFunc)(CUAllocator *allocator, void *object);

/**
 * Decrements the ref count of a particular object and returns its new ref count.
 */
typedef int (*CUAllocatorDecrefFunc)(CUAllocator *allocator, void *object);

/**
 * Returns the refcount of an object.
 */
typedef unsigned (*CUAllocatorRefcountFunc)(CUAllocator *allocator, void *object);

/**
 * Memory allocators responsible for allocations, deallocations, and optionally
 * garbage collection and/or reference counting.
 */
struct CUAllocator
{
    // Memory allocators and deallocators
    CUAllocatorAllocFunc allocFunc;
    CUAllocatorReallocFunc reallocFunc;
    CUAllocatorDeallocFunc deallocFunc;

    // The following 3 functions are used for ref counted environments.
    CUAllocatorIncrefFunc increfFunc;
    CUAllocatorDecrefFunc decrefFunc;
    CUAllocatorRefcountFunc refcountFunc;
};

/**
 * Creates the default memory allocator with basic reference counting.
 */
extern CUAllocator *cu_default_allocator();

#define cu_allocator_alloc(a, size, rc)         ((CUAllocator *)(a))->allocFunc((CUAllocator *)a, size, rc)
#define cu_allocator_dealloc(a, obj)            ((CUAllocator *)(a))->deallocFunc((CUAllocator *)a, obj)

#ifdef ENABLE_REFERENCE_COUNTING
#define cu_allocator_incref(allocator, obj)     ((CUAllocator *)(allocator))->increfFunc((CUAllocator *)allocator, obj)
#define cu_allocator_decref(allocator, obj)     ((CUAllocator *)(allocator))->decrefFunc((CUAllocator *)allocator, obj)
#define cu_allocator_refcount(allocator, obj)   ((CUAllocator *)(allocator))->refcountFunc((CUAllocator *)allocator, obj)
#else
#define cu_allocator_incref(allocator, obj)     (obj)
#define cu_allocator_decref(allocator, obj)     (true)
#define cu_allocator_refcount(allocator, obj)   1
#endif

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif
