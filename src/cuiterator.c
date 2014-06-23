
#include "cutils.h"

DECLARE_PROTO_FUNC(cu_iterator_prototype, CUIteratorPrototype, cu_object_prototype());

/**
 * Tells if there are more items in the iterator.
 * \param   liter   Iterator to peek from.
 * \return  true if more items are to follow, false otherwise.
 */
BOOL cu_iterator_has_next(CUIterator *liter)
{
    return liter != NULL && 
           liter->__prototype__->hasNextFunc != NULL &&
           liter->__prototype__->hasNextFunc(liter);
}

/**
 * Gets the next item pointed by the iterator.
 * \param   liter   Iterator to get the next item from.
 */
CUObject *cu_iterator_next(CUIterator *liter)
{
    if (liter != NULL && liter->__prototype__->nextFunc != NULL)
        return liter->__prototype__->nextFunc(liter);
    return NULL;
}

