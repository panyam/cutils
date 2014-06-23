
#include "cutils.h"

typedef struct CULinkedListNode CULinkedListNode;

DECLARE_CLASS(CULinkedListNode, CUPrototype,
    struct CULinkedListNode *next;
    struct CULinkedListNode *prev;
    CUObject *value;
);

/**
 * Array class implementation
 */
DECLARE_CLASS(CULinkedList, CUListPrototype,
    CULinkedListNode *head;
    CULinkedListNode *tail;
    unsigned length;
);

CULinkedListNode *cu_linkedlistnode(CUObject *value)
{
    CULinkedListNode *node = (CULinkedListNode *)cu_alloc(cu_object_prototype(), sizeof(CULinkedListNode));
    node->next = node->prev = NULL;
    node->value = value;
    cu_incref(value);
    return node;
}

/**
 * Creates a new list with a given capacity.
 */
CULinkedList *cu_linkedlist()
{
    CULinkedList *list = (CULinkedList *)cu_alloc(cu_linkedlist_prototype(), sizeof(CULinkedList));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/*
 * Clear an list without freeing the list itself.
 */
void cu_linkedlist_clear(CULinkedList *list)
{
    if (list)
    {
        for (CULinkedListNode *temp = list->head;temp;temp = temp->next)
        {
            cu_decref(temp->value);
            cu_decref(temp);
        }
        list->head = list->tail = NULL;
        list->length = 0;
    }
}

CULinkedListNode *cu_linkedlist_node_at_index(const CULinkedList *list, int index)
{
    if (list && index >= 0)
    {
        for (CULinkedListNode *temp = list->head;temp;temp = temp->next)
        {
            if (index == 0)
                return temp;
            index--;
        }
    }
    return NULL;
}

/**
 * Called before deallocating the list.
 *
 * \param   obj    Array to be deallocated and released.
 */
void cu_linkedlist_dealloc(CULinkedList *list)
{
    cu_linkedlist_clear(list);
}

/*
 * Return the index of an object if it exists in the list.
 */
int cu_linkedlist_index_of(const CULinkedList *list, const CUObject *value)
{
    if (list && value)
    {
        int index = 0;
        for (CULinkedListNode *temp = list->head;temp;temp = temp->next)
        {
            if (cu_equals(temp->value, value))
                return index;
            index++;
        }
    }
    return -1;
}

/*
 * Return the element at a given index.
 */
CUObject *cu_linkedlist_get_item_at(const CULinkedList *list, int index)
{
    CULinkedListNode *node = cu_linkedlist_node_at_index(list, index);
    return node ? node->value : NULL;
}

/*
 * Sets the item at a given index and returns the old item.
 */
void cu_linkedlist_set_item_at(CULinkedList *list, CUObject *newitem, int index)
{
    CULinkedListNode *node = cu_linkedlist_node_at_index(list, index);
    if (node)
    {
        cu_setattr(node, value, newitem);
    }
}

/*
 * Return the number of items in the list.
 */
unsigned cu_linkedlist_size(const CULinkedList *list)
{
    return list->length;
}

/*
 * Tells if the list is empty or not.
 */
unsigned cu_linkedlist_is_empty(const CULinkedList *list)
{
    return list->length == 0;
}

/*
 * Tells if the list contains an item.
 */
BOOL cu_linkedlist_contains(const CULinkedList *list, const CUObject *item)
{
    return cu_linkedlist_index_of(list, item) < 0;
}

/*
 * Tells if the list contains all the given items.
 */
BOOL cu_linkedlist_contains_all(const CULinkedList *list, const CUCollection *another)
{
    NOT_IMPLEMENTED
    return false;
}

/*
 * Returns the list iterator.
 */
CUIterator *cu_linkedlist_iterator(CULinkedList *list)
{
    NOT_IMPLEMENTED
    return NULL;
}

/*
 * Insert an item at a given index in the list
 *
 * -ve index indicates an append operation
 */
void cu_linkedlist_add_item_at(CULinkedList *list, CUObject *item, int index)
{
    if (!list || !item) return ;
    CULinkedListNode *node = cu_linkedlistnode(item);
    if (list->head == NULL)
    {
        list->head = list->tail = node;
    }
    else if (index == 0)
    {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    else if (index < 0 || index >= list->length)
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    else
    {
        CULinkedListNode *temp = cu_linkedlist_node_at_index(list, index);
        CULinkedListNode *prev = temp->prev;
        CULinkedListNode *next = temp->next;
        if (prev) prev->next = node;
        if (next) next->prev = node;
        node->prev = prev;
        node->next = next;
    }
    list->length++;
}

/*
 * Adds an item to the end of the list.
 *
 * -ve index indicates an append operation
 */
void cu_linkedlist_add(CULinkedList *list, CUObject *item)
{
    cu_linkedlist_add_item_at(list, item, -1);
}

/*
 * Adds all items from a collection to the list.
 */
void cu_linkedlist_add_all(CULinkedList *list, CUCollection *another)
{
    NOT_IMPLEMENTED
}

/*
 * Remove an item at a given index
 */
BOOL cu_linkedlist_remove_item_at(CULinkedList *list, int index)
{
    CULinkedListNode *node = cu_linkedlist_node_at_index(list, index);
    if (node)
    {
        CULinkedListNode *prev = node->prev;
        CULinkedListNode *next = node->next;
        if (prev) prev->next = next;
        if (next) next->prev = prev;
        if (node == list->head)
            list->head = next;
        if (node == list->tail)
            list->tail = prev;
        node->prev = node->next = NULL;
        cu_decref(node);
        list->length--;
        return true;
    }
    return false;
}

/*
 * Remove an item from the end of the list.
 */
BOOL cu_linkedlist_remove(CULinkedList *list, CUObject *value)
{
    int index = cu_linkedlist_index_of(list, value);
    if (index >= 0)
    {
        return cu_linkedlist_remove_item_at(list, index);
    }
    return false;
}

/*
 * Removes all items from another collection from this list.
 */
void cu_linkedlist_remove_all(CULinkedList *list, CUCollection *another)
{
    NOT_IMPLEMENTED
}

/*
 * Splices an list and returns a new list.
 */
CULinkedList *cu_linkedlist_splice(CULinkedList *list, int from, int to)
{
    CULinkedList *out = NULL;
    if (list)
    {
        if (from < 0 || from >= list->length) from = 0;
        if (to < 0 || to >= list->length) to = list->length - 1;
        if (from > to)
        {
            int a = to;
            to = from;
            from = a;
        }
        CULinkedListNode *fromnode = cu_linkedlist_node_at_index(list, from);
        if (fromnode)
        {
            out = cu_linkedlist();
            int i = from;
            for (CULinkedListNode *temp = fromnode;temp && i <= to;temp = temp->next, i++)
            {
                cu_linkedlist_add(out, temp->value);
            }
        }
    }
    return out;
}

/**
 * Default string prototype.
 */
DECLARE_PROTO_FUNC(cu_linkedlist_prototype, CUListPrototype, NULL,
    ((CUCollectionPrototype *)__protoptr__)->sizeFunc = (CUCollectionSizeFunc)cu_linkedlist_size;
    ((CUCollectionPrototype *)__protoptr__)->isEmptyFunc = (CUCollectionIsEmptyFunc)cu_linkedlist_is_empty;
    ((CUCollectionPrototype *)__protoptr__)->containsFunc = (CUCollectionContainsFunc)cu_linkedlist_contains;
    ((CUCollectionPrototype *)__protoptr__)->containsAllFunc = (CUCollectionContainsAllFunc)cu_linkedlist_contains_all;
    ((CUCollectionPrototype *)__protoptr__)->iteratorFunc = (CUCollectionIteratorFunc)cu_linkedlist_iterator;

    // mutable operations
    ((CUCollectionPrototype *)__protoptr__)->clearFunc = (CUCollectionClearFunc)cu_linkedlist_clear;
    ((CUCollectionPrototype *)__protoptr__)->addFunc = (CUCollectionAddFunc)cu_linkedlist_add;
    ((CUCollectionPrototype *)__protoptr__)->addAllFunc = (CUCollectionAddAllFunc)cu_linkedlist_add_all;
    ((CUCollectionPrototype *)__protoptr__)->removeFunc = (CUCollectionRemoveFunc)cu_linkedlist_remove;
    ((CUCollectionPrototype *)__protoptr__)->removeAllFunc = (CUCollectionRemoveAllFunc)cu_linkedlist_remove_all;

    ((CUListPrototype *)__protoptr__)->getItemAtFunc = (CUListGetItemAtFunc)cu_linkedlist_get_item_at;
    ((CUListPrototype *)__protoptr__)->setItemAtFunc = (CUListSetItemAtFunc)cu_linkedlist_set_item_at;
    ((CUListPrototype *)__protoptr__)->addItemAtFunc = (CUListAddItemAtFunc)cu_linkedlist_add_item_at;
    ((CUListPrototype *)__protoptr__)->removeItemAtFunc = (CUListRemoveItemAtFunc)cu_linkedlist_remove_item_at;
    ((CUListPrototype *)__protoptr__)->indexOfFunc = (CUListIndexOfFunc)cu_linkedlist_index_of;
    ((CUListPrototype *)__protoptr__)->spliceFunc = (CUListSpliceFunc)cu_linkedlist_splice;

    ((CUPrototype *)__protoptr__)->deallocFunc = (CUObjectDeallocFunc)cu_linkedlist_dealloc;
);

