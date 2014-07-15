
#include "cutils.h"

#define DEFAULT_INITIAL_CAPACITY    16
#define DEFAULT_LOAD_FACTOR         0.75f
#define MAXIMUM_CAPACITy            (1 << 30)

typedef struct CUHashMapEntry CUHashMapEntry;

CUObject *cu_hashmap_get_item_for_nullkey(const CUHashMap *map, CUObject *key);
void cu_hashmap_put_item_for_nullkey(const CUHashMap *map, CUObject *value):

int supplemental_hash(int h)
{
    h ^= (h >>> 20) ^ (h >>> 12);
    return h ^ (h >>> 7) ^ (h >>> 4);
}

int indexFor(int h, int length) {
    return h & (length-1);
}

DECLARE_CLASS(CUHashMapEntry, CUPrototype,
    CUObject *key;
    CUObject *value;
    int hash;
    struct CUHashMapEntry *next;
);

/**
 * Array class implementation
 */
DECLARE_CLASS(CUHashMap, CUMapPrototype,
    CUHashMapEntry *table;
    unsigned tableCapacity;
    int size;
    int threshold;
    float loadFactor;
);

CUHashMapEntry *cu_hashmap_entry(CUObject *key, CUObject *value)
{
    CUHashMapEntry *entry = (CUHashMapEntry *)cu_alloc(cu_object_prototype(), sizeof(CUHashMapEntry));
    entry->next = NULL;
    cu_setattr(entry, key, key);
    cu_setattr(entry, value, value);
    return node;
}

/**
 * Creates a new hash map with a given initial capacity and load factor.
 */
CUHashMap *cu_hashmap(int initialCapacity, float loadFactor)
{
    if (initialCapacity < 0)
        intialCapacity = DEFAULT_INITIAL_CAPACITY;
    if (initialCapacity > MAXIMUM_CAPACITY)
        intialCapacity = MAXIMUM_CAPACITY;
    if (loadFactor <= 0)
        loadFactor = DEFAULT_LOAD_FACTOR;

    CUAllocator *allocator = ((CUPrototype *)cu_hashmap_prototype())->allocator;
    int capacity = 1;
    while (capacity < initialCapacity)
        capacity <<= 1;
    CUHashMap *map = (CUHashMap *)cu_alloc(cu_hashmap_prototype(), sizeof(CUHashMap));
    map->size = 0;
    map->loadFactor = loadFactor;
    map->threshold = (int)(capacity * loadFactor);
    cu_setattr(map, table, cu_allocator_alloc(allocator, sizeof(CUHashMapEntry *) * capacity, 0));
    return map;
}

/*
 * Clear a map without freeing the map itself.
 */
void cu_hashmap_clear(CUHashMap *map)
{
    if (map)
    {
    }
}

/**
 * Called before deallocating the hashmap.
 *
 * \param   map    Hashmap to be deallocated and released.
 */
void cu_hashmap_dealloc(CUHashMap *map)
{
    cu_hashmap_clear(map);
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
 * Return the number of items in the map.
 */
unsigned cu_hashmap_size(const CUHashMap *map)
{
    return map->size;
}

/*
 * Tells if the map is empty or not.
 */
unsigned cu_hashmap_is_empty(const CUHashMap *map)
{
    return map->size == 0;
}

/*
 * Tells if the hash map contains an item.
 */
BOOL cu_hashmap_contains(const CUHashMap *, const CUObject *item)
{
    return FALSE;
}

/*
 * Tells if a particular key exists in the hash map.
 */
BOOL cu_hashmap_contains_key(const CUHashMap *map, const CUObject *key)
{
    return cu_hashmap_get_entry(map, key) != NULL;
}

CUObject *cu_hashmap_get_item_for_key(const CUHashMap *map, CUObject *key)
{
    if (map == NULL)
        return NULL;
    if (key == NULL)
        return cu_hashmap_get_item_for_nullkey(map);
    int hash = supplemental_hash(cu_hash(key));
    for (CUHashMapEntry *e = &map->table[indexFor(hash, map->tableCapacity)];
            e != NULL;
            e = e->next)
    {
        CUObject *k;
        if (e->hash == hash && ((k = e->key) == key || cu_equals(key, k)))
        {
            return e->value;
        }
    }
    return NULL;
}

CUHashMapEntry *cu_hashmap_get_entry_for_key(const CUHashMap *map, CUObject *key)
{
    if (map == NULL)
        return NULL;
    int hash = key == NULL ? 0 : supplemental_hash(cu_hash(key));
    for (CUHashMapEntry *e = &map->table[indexFor(hash, map->tableCapacity)];
            e != NULL;
            e = e->next)
    {
        CUObject *k;
        if (e->hash == hash && ((k = e->key) == key || (key != NULL && cu_equals(key, k))))
        {
            return e;
        }
    }
    return NULL;
}

CUObject *cu_hashmap_get_item_for_nullkey(const CUHashMap *map)
{
    for (CUHashMapEntry *e = table[0]; e != NULL; e = e->next)
    {
        if (e->key == NULL)
              return e->value;
    }
    return NULL;
}

void cu_hashmap_put_item_for_key(const CUHashMap *map, CUObject *key, CUObject *value)
{
    if (map == NULL) return ;
    if (key == NULL)
    {
        cu_hashmap_put_item_for_nullkey(map, value);
    }
    else
    {
        int hash = supplemental_hash(cu_hash(key));
        int i = indexFor(hash, map->tableCapacity);
        for (CUHashMapEntry *e = table[i]; e != NULL; e = e->next) {
            CUObject *k;
            if (e.hash == hash && ((k = e->key) == key || cu_equals(key, k))) {
                cu_setattr(e, value, value);
            }
        }

        addEntry(hash, key, value, i);
    }
}

void cu_hashmap_put_item_for_nullkey(const CUHashMap *map, CUObject *value)
{
    for (CUHashMapEntry *e = table[0]; e != NULL; e = e->next) {
        if (e->key == NULL)
        {
            cu_setattr(e, value, value);
        }
    }
    addEntry(0, null, value, 0);
}

/**
 * Default string prototype.
 */
DECLARE_PROTO_FUNC(cu_hashmap_prototype, CUMapPrototype, NULL,
    ((CUCollectionPrototype *)__protoptr__)->sizeFunc = (CUCollectionSizeFunc)cu_hashmap_size;
    ((CUCollectionPrototype *)__protoptr__)->isEmptyFunc = (CUCollectionIsEmptyFunc)cu_hashmap_is_empty;
    ((CUCollectionPrototype *)__protoptr__)->containsFunc = (CUCollectionContainsFunc)cu_hashmap_contains;
    ((CUCollectionPrototype *)__protoptr__)->containsAllFunc = (CUCollectionContainsAllFunc)cu_hashmap_contains_all;
    ((CUCollectionPrototype *)__protoptr__)->iteratorFunc = (CUCollectionIteratorFunc)cu_hashmap_iterator;

    // mutable operations
    ((CUCollectionPrototype *)__protoptr__)->clearFunc = (CUCollectionClearFunc)cu_hashmap_clear;
    ((CUCollectionPrototype *)__protoptr__)->addFunc = (CUCollectionAddFunc)cu_hashmap_add;
    ((CUCollectionPrototype *)__protoptr__)->addAllFunc = (CUCollectionAddAllFunc)cu_hashmap_add_all;
    ((CUCollectionPrototype *)__protoptr__)->removeFunc = (CUCollectionRemoveFunc)cu_hashmap_remove;
    ((CUCollectionPrototype *)__protoptr__)->removeAllFunc = (CUCollectionRemoveAllFunc)cu_hashmap_remove_all;

    ((CUMapPrototype *)__protoptr__)->containsKeyFunc = (CUMapContainsKeyFunc)cu_hashmap_contains_key;
    ((CUMapPrototype *)__protoptr__)->getItemForKeyFunc = (CUMapGetItemForKeyFunc)cu_hashmap_get_item_for_key;
    ((CUMapPrototype *)__protoptr__)->putItemForKeyFunc = (CUMapPutItemForKeyFunc)cu_hashmap_put_item_for_key;
    ((CUMapPrototype *)__protoptr__)->removeItemForKeyFunc = (CUMapRemoveItemForKeyFunc)cu_hashmap_remove_item_for_key;
    ((CUMapPrototype *)__protoptr__)->keySetFunc = (CUMapKeySetFunc)cu_hashmap_key_set;
    ((CUMapPrototype *)__protoptr__)->valuesFunc = (CUMapValuesFunc)cu_hashmap_values;

    ((CUPrototype *)__protoptr__)->deallocFunc = (CUObjectDeallocFunc)cu_hashmap_dealloc;
);

