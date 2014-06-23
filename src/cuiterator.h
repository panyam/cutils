

#ifndef __CUTILS_ITERATOR_H__
#define __CUTILS_ITERATOR_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

typedef BOOL    (*IteratorHasNextFunc)(CUIterator *iterator);
typedef CUObject *(*IteratorNextFunc)(CUIterator *iterator);

/**
 * Prototypes of iterators.
 */
CU_INHERIT_STRUCT(CUIteratorPrototype, CUPrototype,
    BOOL     (*hasNextFunc)(CUIterator *iterator);
    CUObject *(*nextFunc)(CUIterator *iterator);
);

DECLARE_CLASS(CUIterator, CUIteratorPrototype);

/**
 * The default iterator prototype.
 */
extern CUIteratorPrototype *literator_prototype();

/**
 * Initialises a new iterator object.
 */
extern CUObject *literator_init(CUIterator *iter, CUIteratorPrototype *proto);

/**
 * Tells if there are more items in the iterator.
 * \param   liter   Iterator to peek from.
 * \return  true if more items are to follow, false otherwise.
 */
extern BOOL literator_has_next(CUIterator *liter);

/**
 * Gets the next item pointed by the iterator.
 * \param   liter   Iterator to get the next item from.
 */
extern CUObject *literator_next(CUIterator *liter);

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

