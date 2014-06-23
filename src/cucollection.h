
#ifndef __CUTILS_COLLECTION_H__
#define __CUTILS_COLLECTION_H__

#include "cuprototype.h"

#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Gets the size of the collection.
 */
typedef size_t (*CUCollectionSizeFunc)(const CUCollection *c);

/**
 * Tells if the collection is empty.
 */
typedef BOOL (*CUCollectionIsEmptyFunc)(const CUCollection *c);

/**
 * Tells if the collection contains a specific object.
 */
typedef BOOL (*CUCollectionContainsFunc)(const CUCollection *c, const CUObject *value);

/**
 * Returns true if the given collection contains all items in another collection.
 */
typedef BOOL (*CUCollectionContainsAllFunc)(const CUCollection *c, const CUCollection *another);

/**
 * Tells if the collection contains a specific object.
 */
typedef CUIterator *(*CUCollectionIteratorFunc)(const CUCollection *c);

/**
 * Adds an object to a collection.
 */
typedef BOOL (*CUCollectionAddFunc)(CUCollection *c, const CUObject *value);

/**
 * Adds all objects from a collection to a given collection.
 */
typedef BOOL (*CUCollectionAddAllFunc)(CUCollection *c, const CUCollection *another);

/**
 * Removes an object to a collection.
 */
typedef BOOL (*CUCollectionRemoveFunc)(CUCollection *c, const CUObject *value);

/**
 * Removes all objects from a collection from the given collection.
 */
typedef BOOL (*CUCollectionRemoveAllFunc)(CUCollection *c, const CUCollection *another);

/**
 * Removes all elements from the collection.
 */
typedef void (*CUCollectionClearFunc)(CUCollection *c);

/**
 * Prototype for collections.
 */
CU_INHERIT_STRUCT(CUCollectionPrototype, CUPrototype,
    CUCollectionSizeFunc sizeFunc;
    CUCollectionIsEmptyFunc isEmptyFunc;
    CUCollectionContainsFunc containsFunc;
    CUCollectionContainsAllFunc containsAllFunc;
    CUCollectionIteratorFunc iteratorFunc;

    // mutable operations
    CUCollectionClearFunc clearFunc;
    CUCollectionAddFunc addFunc;
    CUCollectionAddAllFunc addAllFunc;
    CUCollectionRemoveFunc removeFunc;
    CUCollectionRemoveAllFunc removeAllFunc;
);

DECLARE_CLASS(CUCollection, CUCollectionPrototype);

/**
 * Default collection prototype.
 */
extern CUCollectionPrototype *cu_collection_prototype();

/**
 * The initialiser.
 */
extern CUCollection *cu_collection_init(CUCollection *c, CUCollectionPrototype *prototype);

#define cu_collection_size(c)                   (c ? GET_PROTOTYPE(c, CUCollectionPrototype)->sizeFunc((CUCollection *)(c)) : 0)
#define cu_collection_is_empty(c)               (c ? GET_PROTOTYPE(c, CUCollectionPrototype)->isEmptyFunc((CUCollection *)(c)) : true)
#define cu_collection_contains(c, value)        (c ? GET_PROTOTYPE(c, CUCollectionPrototype)->containsFunc((CUCollection *)(c), (const CUObject *)value) : false)
#define cu_collection_contains_all(c, another)  (c ? GET_PROTOTYPE(c, CUCollectionPrototype)->containsAllFunc((CUCollection *)(c), (const CUCollection *)another) : false)
#define cu_collection_iterator(c)               GET_PROTOTYPE(c, CUCollectionPrototype)->iteratorFunc((CUCollection *)(c))
#define cu_collection_add(c, value)             GET_PROTOTYPE(c, CUCollectionPrototype)->addFunc((CUCollection *)(c), (const CUObject *)value)
#define cu_collection_add_all(c, another)       GET_PROTOTYPE(c, CUCollectionPrototype)->addAllFunc((CUCollection *)(c), (const CUCollection *)another)
#define cu_collection_remove(c, value)          GET_PROTOTYPE(c, CUCollectionPrototype)->removeFunc((CUCollection *)(c), (CUObject *)vvalue)
#define cu_collection_remove_all(c, another)    GET_PROTOTYPE(c, CUCollectionPrototype)->removeAllFunc((CUCollection *)(c), (const CUCollection *)vanother)
#define cu_collection_clear(c)                  GET_PROTOTYPE(c, CUCollectionPrototype)->clearFunc((CUCollection *)(c))

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

