
#ifndef __CUTILS_UTILS_FWDDEFS_H__
#define __CUTILS_UTILS_FWDDEFS_H__

#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

#include <inttypes.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char BOOL;
#define TRUE  1
#define FALSE 0
#define true  1
#define false 0

#define NOT_IMPLEMENTED     assert(0 && "Not Implemented");

typedef uint16_t    REG;
typedef uint16_t    HWORD;
typedef uint32_t    SWORD;
typedef uint64_t    DWORD;
typedef int32_t     INT;
typedef int64_t     LONG;
typedef float       FLOAT;
typedef double      DOUBLE;

#define NEW(TYPE)               (TYPE *)malloc(sizeof(TYPE))
#define NEW_ARRAY(TYPE, size)   (TYPE *)malloc(size * sizeof(TYPE))

#define ZNEW(TYPE)              (TYPE *)calloc(1, sizeof(TYPE))
#define ZNEW_ARRAY(TYPE, size)  (TYPE *)calloc(size, sizeof(TYPE))

typedef struct CUAllocator CUAllocator;
typedef struct CUPrototype CUPrototype;
typedef struct CUPrototypeInfo CUPrototypeInfo;
typedef struct LError LError;
typedef struct CUCollection CUCollection;
typedef struct CUArray CUArray;
typedef struct CULinkedList CULinkedList;
typedef struct CUList CUList;
typedef struct CUMap CUMap;
typedef struct CUSet CUSet;
typedef struct CUTreeSet CUTreeSet;
typedef struct CUHashSet CUHashSet;
typedef struct CUTreeMap CUTreeMap;
typedef struct CUHashMap CUHashMap;
typedef struct CUCollectionPrototype CUCollectionPrototype;
typedef struct CUListPrototype CUListPrototype;
typedef struct CUMapPrototype CUMapPrototype;
typedef struct CUHashMapPrototype CUHashMapPrototype;
typedef struct CUObject CUObject;
typedef struct CUStringPrototype CUStringPrototype;
typedef struct CUString CUString;
typedef struct CUIteratorPrototype CUIteratorPrototype;
typedef struct CUIterator CUIterator;
typedef struct CULock CULock;
typedef struct CRWLock CRWLock;
typedef struct CUSemaphore CUSemaphore;
typedef struct CUCondition CUCondition;

// IO prototypes
typedef struct CUStreamPrototype CUStreamPrototype;
typedef struct CUIStreamPrototype CUIStreamPrototype;
typedef struct CUOStreamPrototype CUOStreamPrototype;
typedef struct CUStream CUStream;
typedef struct CUIStream CUIStream;
typedef struct CUOStream CUOStream;
typedef struct CUMemIStream CUMemIStream;
typedef struct CUMemOStream CUMemOStream;
typedef struct CUFileIStream CUFileIStream;
typedef struct CUFileOStream CUFileOStream;

/**
 * Tells if a string is an integer, optionally returning the integer value
 * if it is an integer.
 *
 * \param   buffer      The buffer that is being checked.
 * \param   length      Length of the buffer (if -ve, then it is a null
 *                      terminated string).
 * \param   outValue    Stores the int value (if not NULL).
 *
 * \return  true if the value is an integer, false otherwise.  If value is
 * an integer and outValue is non-null then the int value is stored in
 * outValue.
 */
extern BOOL is_integer(const char *buffer, int length, int *outValue);

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Inlined Macro Functions
///////////////////////////////////////////////////////////////////////////////////////////////////

// For more in inlining see - http://www.greenend.org.uk/rjk/2003/03/inline.html

/**
 * Casts a void* to an object.
 */
// extern inline CUObject *OBJ(void *obj) { return (CUObject *)obj; }
#define OBJ(x)      ((CUObject *)(x))

/**
 * Get the prototype of an object.
 */
#define PROTO(obj)          (OBJ((obj))->__prototype__)

/**
 * Initialises a object's refcount and prototype.
 */
// extern inline CUObject *OBJ_INIT(void *obj, void *proto) { return cu_object_init(OBJ(obj), (CUPrototype *)proto); }
#define OBJ_INIT(obj, proto)        cu_object_init(OBJ(obj), (CUPrototype *)proto)

/**
 * Tells if an object is instance of a particular prototype.
 */
#define OBJ_IMPLEMENTS(obj, proto)  cu_object_implements((CUObject *)(obj), PROTO(proto))

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

