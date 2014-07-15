
#include "cutils.h"

/**
 * Array class implementation
 */
DECLARE_CLASS(CUArray, CUListPrototype,
    unsigned capacity;
    unsigned length;
    CUObject **items;
);

/**
 * Creates a new array with a given capacity.
 */
CUArray *cu_array_with_capacity(int capacity)
{
    if (capacity <= 0)
        capacity = 0;
    CUAllocator *allocator = ((CUPrototype *)cu_array_prototype())->allocator;
    CUArray *array = (CUArray *)cu_alloc(cu_array_prototype(), sizeof(CUArray));
    array->capacity = capacity;
    array->length = 0;
    array->items = NULL;
    if (capacity > 0)
    {
        cu_setattr(array, items, cu_allocator_alloc(allocator, sizeof(CUObject *) * capacity, 0));
    }
    return array;
}

/*
 * Clear an array without freeing the array itself.
 */
void cu_array_clear(CUArray *array)
{
    if (array && array->items)
    {
        for (int i = 0;i < array->length;i++)
        {
            cu_setattr(array, items[i], NULL);
        }
        array->length   = 0;
    }
}

/**
 * Called before deallocating the array.
 *
 * \param   obj    Array to be deallocated and released.
 */
void cu_array_dealloc(CUArray *array)
{
    cu_array_clear(array);
    // call the parent deallocator?
}

/*
 * Initialise an array.
 */
void cu_array_reserve(CUArray *array, int capacity)
{
    assert(array != NULL);

    if (capacity > array->capacity)
    {
        array->items    = realloc(array->items, sizeof(CUObject *) * capacity);
        array->capacity = capacity;
    }
}

/*
 * Return the index of an object if it exists in the array.
 */
int cu_array_index_of(const CUArray *array, const CUObject *value)
{
    if (array && value)
    {
        for (int i = 0;i < array->length;i++)
        {
            if (cu_equals(array->items[i], value))
                return i;
        }
    }
    return -1;
}

/*
 * Return the element at a given index.
 */
CUObject *cu_array_get_item_at(const CUArray *array, int index)
{
    return array->items[index];
}

/*
 * Sets the item at a given index and returns the old item.
 */
void cu_array_set_item_at(CUArray *array, CUObject *newitem, int index)
{
    cu_setattr(array, items[index], newitem);
}

/*
 * Return the number of items in the array.
 */
unsigned cu_array_size(const CUArray *array)
{
    return array->length;
}

/*
 * Tells if the array is empty or not.
 */
unsigned cu_array_is_empty(const CUArray *array)
{
    return array->length == 0;
}

/*
 * Tells if the array contains an item.
 */
BOOL cu_array_contains(const CUArray *array, const CUObject *item)
{
    for (int i = 0;i < array->length;i++)
    {
        if (cu_equals(array->items[i], item))
            return true;
    }
    return false;
}

/*
 * Tells if the array contains all the given items.
 */
BOOL cu_array_contains_all(const CUArray *array, const CUCollection *another)
{
    NOT_IMPLEMENTED
    return false;
}

/*
 * Returns the array iterator.
 */
CUIterator *cu_array_iterator(CUArray *array)
{
    NOT_IMPLEMENTED
    return NULL;
}

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
void cu_array_add_item_at(CUArray *array, CUObject *item, int index)
{
    cu_array_reserve(array, array->length + 1);
    if (index < 0 || index >= array->length)
    {
        array->items[array->length] = item;
    }
    else
    {
        memmove(array->items + index + 1, array->items + index, sizeof(CUObject *) * (array->length - index));
        array->items[index] = item;
    }
    array->length++;
}

/*
 * Insert a set of value at a given index.
 *
 * -ve index indicates an append operation
 */
void cu_array_sinsert(CUArray *array, int index, CUObject **src, int srclen)
{
    cu_array_reserve(array, array->length + srclen);
    if (index >= 0 && index < array->length)
    {
        memmove(array->items + index + srclen, array->items + index, array->length - index);
    }
    memcpy(array + index, src, srclen * sizeof(CUObject *));
    array->length += srclen;
}

/*
 * Adds an item to the end of the list.
 *
 * -ve index indicates an append operation
 */
void cu_array_add(CUArray *array, CUObject *item)
{
    cu_array_add_item_at(array, item, -1);
}

/*
 * Adds all items from a collection to the array.
 */
void cu_array_add_all(CUArray *array, CUCollection *another)
{
    NOT_IMPLEMENTED
}

/*
 * Remove an item at a given index
 */
BOOL cu_array_remove_item_at(CUArray *array, int index)
{
    if (array != NULL && index >= 0)
    {
        cu_setattr(array, items[index], NULL);
        memmove(array->items + index, array->items + index + 1, array->length - (index + 1));
        array->length--;
        return true;
    }
    return false;
}

/*
 * Remove an item from the end of the array.
 */
BOOL cu_array_remove(CUArray *array, CUObject *value)
{
    int index = cu_array_index_of(array, value);
    if (index >= 0)
    {
        return cu_array_remove_item_at(array, index);
    }
    return false;
}

/*
 * Removes all items from another collection from this array.
 */
void cu_array_remove_all(CUArray *array, CUCollection *another)
{
    NOT_IMPLEMENTED
}

/*
 * Splices an array and returns a new array.
 */
CUArray *cu_array_splice(CUArray *array, int from, int to)
{
    CUArray *out = NULL;
    if (array)
    {
        if (from < 0 || from >= array->length) from = 0;
        if (to < 0 || to >= array->length) to = array->length - 1;
        if (from > to)
        {
            int a = to;
            to = from;
            from = a;
        }
        out = cu_array_with_capacity(1 + from - to);
        for (int i = from;i <= to;i++)
            cu_array_add(out, array->items[i]);
    }
    return out;
}

/**
 * Default array prototype.
 */
DECLARE_PROTO_FUNC(cu_array_prototype, CUListPrototype, NULL,
    ((CUCollectionPrototype *)__protoptr__)->sizeFunc = (CUCollectionSizeFunc)cu_array_size;
    ((CUCollectionPrototype *)__protoptr__)->isEmptyFunc = (CUCollectionIsEmptyFunc)cu_array_is_empty;
    ((CUCollectionPrototype *)__protoptr__)->containsFunc = (CUCollectionContainsFunc)cu_array_contains;
    ((CUCollectionPrototype *)__protoptr__)->containsAllFunc = (CUCollectionContainsAllFunc)cu_array_contains_all;
    ((CUCollectionPrototype *)__protoptr__)->iteratorFunc = (CUCollectionIteratorFunc)cu_array_iterator;

    // mutable operations
    ((CUCollectionPrototype *)__protoptr__)->clearFunc = (CUCollectionClearFunc)cu_array_clear;
    ((CUCollectionPrototype *)__protoptr__)->addFunc = (CUCollectionAddFunc)cu_array_add;
    ((CUCollectionPrototype *)__protoptr__)->addAllFunc = (CUCollectionAddAllFunc)cu_array_add_all;
    ((CUCollectionPrototype *)__protoptr__)->removeFunc = (CUCollectionRemoveFunc)cu_array_remove;
    ((CUCollectionPrototype *)__protoptr__)->removeAllFunc = (CUCollectionRemoveAllFunc)cu_array_remove_all;

    ((CUListPrototype *)__protoptr__)->getItemAtFunc = (CUListGetItemAtFunc)cu_array_get_item_at;
    ((CUListPrototype *)__protoptr__)->setItemAtFunc = (CUListSetItemAtFunc)cu_array_set_item_at;
    ((CUListPrototype *)__protoptr__)->addItemAtFunc = (CUListAddItemAtFunc)cu_array_add_item_at;
    ((CUListPrototype *)__protoptr__)->removeItemAtFunc = (CUListRemoveItemAtFunc)cu_array_remove_item_at;
    ((CUListPrototype *)__protoptr__)->indexOfFunc = (CUListIndexOfFunc)cu_array_index_of;
    ((CUListPrototype *)__protoptr__)->spliceFunc = (CUListSpliceFunc)cu_array_splice;

    ((CUPrototype *)__protoptr__)->deallocFunc = (CUObjectDeallocFunc)cu_array_dealloc;
);

