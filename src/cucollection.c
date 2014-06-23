
#include "cutils.h"

/**
 * The initialiser.
 */
CUCollection *cu_collection_init(CUCollection *c, CUCollectionPrototype *proto)
{
    if (!proto)
        proto = cu_collection_prototype();
    cu_object_init((CUObject *)c, (CUPrototype *)proto);
    return c;
}

/*******
 * Default methods.
 *******/

size_t cu_collection_default_size_func(const CUCollection *c)
{
    return 0;
}

BOOL cu_collection_default_isempty_func(const CUCollection *c)
{
    return true;
}

BOOL cu_collection_default_contains_func(const CUCollection *c, const CUObject *value)
{
    return false;
}

BOOL cu_collection_default_containsall_func(const CUCollection *c, const CUCollection *another)
{
    return false;
}

CUIterator *cu_collection_default_iterator_func(const CUCollection *c)
{
    return NULL;
}

BOOL cu_collection_default_add_func(CUCollection *c, const CUObject *value)
{
    return false;
}

BOOL cu_collection_default_addall_func(CUCollection *c, const CUCollection *another)
{
    return false;
}

BOOL cu_collection_default_remove_func(CUCollection *c, const CUObject *value)
{
    return false;
}

BOOL cu_collection_default_removeall_func(CUCollection *c, const CUCollection *another)
{
    return false;
}

void cu_collection_default_clear_func(CUCollection *c)
{
}

/**
 * Default collection prototype.
 */
DECLARE_PROTO_FUNC(cu_collection_prototype, CUCollectionPrototype, NULL,
    __proto__.sizeFunc = cu_collection_default_size_func;
    __proto__.isEmptyFunc = cu_collection_default_isempty_func;
    __proto__.containsFunc = cu_collection_default_contains_func;
    __proto__.containsAllFunc = cu_collection_default_containsall_func;
    __proto__.iteratorFunc = cu_collection_default_iterator_func;

    __proto__.clearFunc = cu_collection_default_clear_func;
    __proto__.addFunc = cu_collection_default_add_func;
    __proto__.addAllFunc = cu_collection_default_addall_func;
    __proto__.removeFunc = cu_collection_default_remove_func;
    __proto__.removeAllFunc = cu_collection_default_removeall_func;
);

