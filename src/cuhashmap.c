
#include "cutils.h"
#include <limits.h>

/**
 * The default initial capacity - MUST be a power of two.
 */
#define DEFAULT_INITIAL_CAPACITY    16

/**
 * The load factor used when none specified in constructor.
 */
#define DEFAULT_LOAD_FACTOR         0.75f

/**
 * The maximum capacity, used if a higher value is implicitly specified
 * by either of the constructors with arguments.
 * MUST be a power of two <= 1<<30.
 */
#define MAXIMUM_CAPACITY            (1 << 30)

typedef struct CUHashMapEntry CUHashMapEntry;

CUPrototype *cu_hashmap_entry_prototype();
CUObject *cu_hashmap_get_item_for_nullkey(CUHashMap *map);
CUObject *cu_hashmap_put_item_for_nullkey(CUHashMap *map, CUObject *value);
void cu_hashmap_resize(CUHashMap *map, int newCapacity);
void cu_hashmap_transfer(CUHashMap *map, CUHashMapEntry **newTable, int newCapacity);
CUHashMapEntry *cu_hashmap_remove_entry_for_key(CUHashMap *map, CUObject *key);
CUHashMapEntry *cu_hashmap_get_entry_for_key(CUHashMap *map, CUObject *key);
void cu_hashmap_addentry(CUHashMap *map, int hash, CUObject *key, CUObject *value, int bucketIndex);

int supplemental_hash(int h)
{
    h ^= (((unsigned int)h) >> 20) ^ (((unsigned int)h) >> 12);
    return h ^ (((unsigned int)h) >> 7) ^ (((unsigned int)h) >> 4);
}

int indexFor(int h, int length) {
    return h & (length-1);
}

DECLARE_CLASS(CUHashMapEntry, CUPrototype,
    int hash;
    CUObject *key;
    CUObject *value;
    struct CUHashMapEntry *next;
);

CUHashMapEntry *cu_hashmap_entry(int hash, CUObject *key, CUObject *value, CUHashMapEntry *next)
{
    CUHashMapEntry *entry = (CUHashMapEntry *)cu_alloc(cu_hashmap_entry_prototype(), sizeof(CUHashMapEntry));
    entry->hash = hash;
    cu_setattr(entry, next, next);
    cu_setattr(entry, key, key);
    cu_setattr(entry, value, value);
    return entry;
}

/**
 * Called before deallocating the hashmap.
 *
 * \param   map    Hashmap to be deallocated and released.
 */
void cu_hashmap_entry_dealloc(CUHashMapEntry *entry)
{
    cu_setattr(entry, key, NULL);
    cu_setattr(entry, value, NULL);
    cu_setattr(entry, next, NULL);
}

/**
 * Array class implementation
 */
DECLARE_CLASS(CUHashMap, CUMapPrototype,
    CUHashMapEntry **table;
    unsigned tableCapacity;
    int size;
    int threshold;
    float loadFactor;
);

/**
 * Creates a new hash map with a given initial capacity and load factor.
 */
CUHashMap *cu_hashmap(int initialCapacity, float loadFactor)
{
    if (initialCapacity < 0)
        initialCapacity = DEFAULT_INITIAL_CAPACITY;
    if (initialCapacity > MAXIMUM_CAPACITY)
        initialCapacity = MAXIMUM_CAPACITY;
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
    map->tableCapacity = capacity;
    cu_setattr(map, table, cu_allocator_alloc(allocator, sizeof(CUHashMapEntry *) * capacity, 0));
    bzero(map, sizeof(CUHashMapEntry *) * capacity);
    return map;
}

/**
 * Rehashes the contents of this map into a new array with a
 * larger capacity.  This method is called automatically when the
 * number of keys in this map reaches its threshold.
 *
 * If current capacity is MAXIMUM_CAPACITY, this method does not
 * resize the map, but sets threshold to Integer.MAX_VALUE.
 * This has the effect of preventing future calls.
 *
 * @param newCapacity the new capacity, MUST be a power of two;
 *        must be greater than current capacity unless current
 *        capacity is MAXIMUM_CAPACITY (in which case value
 *        is irrelevant).
 */
void cu_hashmap_resize(CUHashMap *map, int newCapacity)
{
    int oldCapacity = map->tableCapacity;
    if (oldCapacity == MAXIMUM_CAPACITY) {
        map->threshold = INT_MAX;
        return;
    }

    CUAllocator *allocator = ((CUPrototype *)cu_hashmap_prototype())->allocator;
    CUHashMapEntry **newtable = cu_allocator_alloc(allocator, sizeof(CUHashMapEntry *) * newCapacity, 0);
    bzero(newtable, sizeof(CUHashMapEntry *) * newCapacity);
    cu_hashmap_transfer(map, newtable, newCapacity);
    cu_setattr(map, table, newtable);
    map->tableCapacity = newCapacity;
    map->threshold = (int)(newCapacity * map->loadFactor);
}

/**
 * Transfers all entries from current table to newTable.
 */
void cu_hashmap_transfer(CUHashMap *map, CUHashMapEntry **newTable, int newCapacity) {
    CUHashMapEntry **src = map->table;
    for (int j = 0; j < map->tableCapacity; j++) {
        CUHashMapEntry *e = src[j];
        if (e != NULL) {
            src[j] = NULL;
            do {
                CUHashMapEntry *next = e->next;
                int i = indexFor(e->hash, newCapacity);
                e->next = newTable[i];
                newTable[i] = e;
                e = next;
            } while (e != NULL);
        }
    }
}

/*
 * Returns the map iterator.
 */
CUIterator *cu_hashmap_iterator(CUHashMap *map)
{
    NOT_IMPLEMENTED
    return NULL;
}

CUSet *cu_hashmap_key_set(CUHashMap *map)
{
    return NULL;
}

CUCollection *cu_hashmap_values(CUHashMap *map)
{
    return NULL;
}

/*
 * Clear a map without freeing the map itself.
 */
void cu_hashmap_clear(CUHashMap *map)
{
    if (map)
    {
        CUHashMapEntry **tab = map->table;
        for (int i = 0; i < map->tableCapacity; i++)
        {
            if (tab[i] != NULL)
            {
                cu_decref(tab[i]);
                tab[i] = NULL;
            }
        }
        map->size = 0;
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
 * Return the number of items in the map.
 */
unsigned cu_hashmap_size(CUHashMap *map)
{
    return map->size;
}

/*
 * Tells if the map is empty or not.
 */
unsigned cu_hashmap_is_empty(CUHashMap *map)
{
    return map->size == 0;
}


void cu_hashmap_add_all(CUHashMap *map, CUCollection *values)
{
    NOT_IMPLEMENTED
}

void cu_hashmap_add(CUHashMap *map, CUObject *value)
{
    NOT_IMPLEMENTED
}

void cu_hashmap_remove_all(CUHashMap *map, CUCollection *values)
{
    NOT_IMPLEMENTED
}

CUObject *cu_hashmap_remove(CUHashMap *map, CUObject *value)
{
    NOT_IMPLEMENTED
    return NULL;
}

/**
 * Special-case code for containsValue with null argument
 */
BOOL cu_hashmap_contains_nullvalue(CUHashMap *map)
{
    CUHashMapEntry **tab = map->table;
    for (int i = 0; i < map->tableCapacity; i++)
        for (CUHashMapEntry *e = tab[i] ; e != NULL; e = e->next)
            if (e->value == NULL)
                return TRUE;
    return FALSE;
}

/*
 * Tells if the hash map contains an item.
 */
BOOL cu_hashmap_contains(CUHashMap *map, CUObject *value)
{
    if (value == NULL)
        return cu_hashmap_contains_nullvalue(map);

    CUHashMapEntry **tab = map->table;
    for (int i = 0; i < map->tableCapacity; i++)
        for (CUHashMapEntry *e = tab[i] ; e != NULL; e = e->next)
            if (cu_equals(value, e->value))
                return TRUE;
    return FALSE;
}

/*
 * Tells if the hash map contains all items from another collection.
 */
BOOL cu_hashmap_contains_all(CUHashMap *map, CUCollection *values)
{
    NOT_IMPLEMENTED
    return FALSE;
}

/*
 * Tells if a particular key exists in the hash map.
 */
BOOL cu_hashmap_contains_key(CUHashMap *map, CUObject *key)
{
    return cu_hashmap_get_entry_for_key(map, key) != NULL;
}

CUObject *cu_hashmap_get_item_for_key(CUHashMap *map, CUObject *key)
{
    if (map == NULL)
        return NULL;
    if (key == NULL)
        return cu_hashmap_get_item_for_nullkey(map);
    int hash = supplemental_hash(cu_hash(key));
    for (CUHashMapEntry *e = map->table[indexFor(hash, map->tableCapacity)];
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

CUObject *cu_hashmap_get_item_for_nullkey(CUHashMap *map)
{
    for (CUHashMapEntry *e = map->table[0]; e != NULL; e = e->next)
    {
        if (e->key == NULL)
              return e->value;
    }
    return NULL;
}

CUHashMapEntry *cu_hashmap_get_entry_for_key(CUHashMap *map, CUObject *key)
{
    if (map == NULL) return NULL;
    int hash = key == NULL ? 0 : supplemental_hash(cu_hash(key));
    for (CUHashMapEntry *e = map->table[indexFor(hash, map->tableCapacity)];
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

CUObject *cu_hashmap_put_item_for_nullkey(CUHashMap *map, CUObject *value)
{
    for (CUHashMapEntry *e = map->table[0]; e != NULL; e = e->next) {
        if (e->key == NULL)
        {
            CUObject *oldvalue = cu_incref(e->value);
            cu_setattr(e, value, value);
            return oldvalue;
        }
    }
    cu_hashmap_addentry(map, 0, NULL, value, 0);
    return NULL;
}

/**
 * Adds a new entry with the specified key, value and hash code to
 * the specified bucket.  It is the responsibility of this
 * method to resize the table if appropriate.
 *
 * Subclass overrides this to alter the behavior of put method.
 */
void cu_hashmap_addentry(CUHashMap *map, int hash, CUObject *key, CUObject *value, int bucketIndex) {
    CUHashMapEntry *e = map->table[bucketIndex];
    map->table[bucketIndex] = cu_hashmap_entry(hash, key, value, e);
    if (map->size++ >= map->threshold)
        cu_hashmap_resize(map, 2 * map->tableCapacity);
}

CUObject *cu_hashmap_put_item_for_key(CUHashMap *map, CUObject *key, CUObject *value)
{
    if (map == NULL) return NULL;
    if (key == NULL)
    {
        return cu_hashmap_put_item_for_nullkey(map, value);
    }
    else
    {
        int hash = supplemental_hash(cu_hash(key));
        int i = indexFor(hash, map->tableCapacity);
        for (CUHashMapEntry *e = map->table[i]; e != NULL; e = e->next) {
            CUObject *k;
            if (e->hash == hash && ((k = e->key) == key || cu_equals(key, k))) {
                CUObject *oldvalue = cu_incref(e->value);
                cu_setattr(e, value, value);
                return oldvalue;
            }
        }

        cu_hashmap_addentry(map, hash, key, value, i);
        return NULL;
    }
}

/**
 * Removes the mapping for the specified key from this map if present.
 *
 * @param  key key whose mapping is to be removed from the map
 * @return the previous value associated with <tt>key</tt>, or
 *         <tt>null</tt> if there was no mapping for <tt>key</tt>.
 *         (A <tt>NULL</tt> return can also indicate that the map
 *         previously associated <tt>null</tt> with <tt>key</tt>.)
 */
CUObject *cu_hashmap_remove_item_for_key(CUHashMap *map, CUObject *key) {
    CUHashMapEntry *e = cu_hashmap_remove_entry_for_key(map, key);
    return (e == NULL ? NULL : e->value);
}

/**
 * Removes and returns the entry associated with the specified key
 * in the HashMap.  Returns null if the HashMap contains no mapping
 * for this key.
 */
CUHashMapEntry *cu_hashmap_remove_entry_for_key(CUHashMap *map, CUObject *key) {
    int hash = (key == NULL) ? 0 : supplemental_hash(cu_hash(key));
    int i = indexFor(hash, map->tableCapacity);
    CUHashMapEntry *prev = map->table[i];
    CUHashMapEntry *e = prev;

    while (e != NULL) {
        CUHashMapEntry *next = e->next;
        CUObject *k;
        if (e->hash == hash &&
            ((k = e->key) == key || (key != NULL && cu_equals(key,k)))) {
            map->size--;
            if (prev == e)
                map->table[i] = next;
            else
                prev->next = next;
            return e;
        }
        prev = e;
        e = next;
    }

    return e;
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

DECLARE_PROTO_FUNC(cu_hashmap_entry_prototype, CUPrototype, NULL,
    ((CUPrototype *)__protoptr__)->deallocFunc = (CUObjectDeallocFunc)cu_hashmap_entry_dealloc;
);

