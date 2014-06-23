
#include "cutils.h"

typedef struct CUMemHeader
{
    CUAllocator *allocator;
    int refCount;
} CUMemHeader;

#define HEADER_SIZE     sizeof(CUMemHeader)
#define HEADER(mem)     ((CUMemHeader *)(((char *)mem) - HEADER_SIZE))

static void *cu_default_allocator_alloc(CUAllocator *allocator, size_t size, unsigned initial_refcount);
static void *cu_default_allocator_realloc(CUAllocator *allocator, void *obj, size_t newsize);
static void cu_default_allocator_dealloc(CUAllocator *allocator, void *obj);
static void *cu_default_allocator_incref(CUAllocator *allocator, void *obj);
static int cu_default_allocator_decref(CUAllocator *allocator, void *obj);
static unsigned cu_default_allocator_refcount(CUAllocator *allocator, void *obj);

CUAllocator *cu_default_allocator()
{
    static BOOL initialised = false;
    static CUAllocator allocator;
    if (!initialised)
    {
        allocator.increfFunc = cu_default_allocator_incref;
        allocator.decrefFunc = cu_default_allocator_decref;
        allocator.allocFunc = cu_default_allocator_alloc;
        allocator.deallocFunc = cu_default_allocator_dealloc;
        allocator.reallocFunc = cu_default_allocator_realloc;
        allocator.refcountFunc = cu_default_allocator_refcount;
        initialised = TRUE;
    }
    return &allocator;
}

/**
 * Allocates memory of a given size.
 */
void *cu_default_allocator_alloc(CUAllocator *allocator, size_t size, unsigned initial_refcount)
{
    size_t total_size = size + HEADER_SIZE;
    char *out = (char *)malloc(total_size);
    ((CUMemHeader *)out)->refCount = initial_refcount;
    ((CUMemHeader *)out)->allocator = allocator;
    return out + HEADER_SIZE;
}

/**
 * Reallocates memory to the new size.
 */
void *cu_default_allocator_realloc(CUAllocator *allocator, void *memory, size_t newsize)
{
    return realloc(HEADER(memory), newsize + HEADER_SIZE);
}

/**
 * Destroy an object.
 */
void cu_default_allocator_dealloc(CUAllocator *allocator, void *obj)
{
    if (obj)
    {
        free(HEADER(obj));
    }
}

/**
 * Increases the reference count of the object and returns int.
 */
void *cu_default_allocator_incref(CUAllocator *allocator, void *obj)
{
    if (obj != NULL)
    {
        HEADER(obj)->refCount++;
    }
    return obj;
}

/**
 * Decreases the reference count of the object and deletes it if the
 * reference count reaches 0.
 */
int cu_default_allocator_decref(CUAllocator *allocator, void *obj)
{
    if (obj == NULL)
    {
        return false;
    }
    HEADER(obj)->refCount--;
    return HEADER(obj)->refCount;
}

unsigned cu_default_allocator_refcount(CUAllocator *allocator, void *obj)
{
    return HEADER(obj)->refCount;
}

