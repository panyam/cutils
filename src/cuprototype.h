

#ifndef __CUTILS_PROTOTYPE_H__
#define __CUTILS_PROTOTYPE_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Deallocator function.
 */
typedef void (*CUObjectDeallocFunc)(CUObject *object);

/**
 * Returns the hash of an object.
 */
typedef int (*CUObjectHashFunc)(const CUObject *object);

/**
 * Tells if two objects are equal.
 */
typedef BOOL (*CUObjectEqualsFunc)(const CUObject *obj1, const CUObject *obj2);

/**
 * Compares the data of two objects.
 */
typedef int (*CUObjectCompareFunc)(const CUObject *obj1, const CUObject *obj2);

/**
 * Returns the string representation of an object.
 */
typedef CUString *(*CUObjectToStringFunc)(const CUObject *object);

/**
 * Prototypes are the blueprints for objects.  Almost like classes.
 */
struct CUPrototype
{
    /**
     * Prototype meta data.
     */
    CUPrototypeInfo *protoinfo;
    CUAllocator *allocator;

    CUObjectDeallocFunc deallocFunc;
    CUObjectEqualsFunc equalsFunc;
    CUObjectHashFunc hashFunc;
    CUObjectCompareFunc compareFunc;

    CUObjectToStringFunc toStringFunc;
};

/**
 * "Inherits" a struct by including an instance of it as the first member of
 * the new struct.
 */
#define CU_INHERIT_STRUCT(STRUCT_NAME, BASE_STRUCT, ...)   \
    struct STRUCT_NAME                                  \
    {                                                   \
        /**                                             \
         * Base class                                   \
         */                                             \
        BASE_STRUCT __base__;                           \
                                                        \
        /**                                             \
         * The object specific data.                    \
         */                                             \
        __VA_ARGS__                                     \
    }

/**
 * Macro for generating a function that returns a prototype that is
 * not inheriting but only overriding certain methods of a prototype.
 */
#define DECLARE_PROTO_FUNC(FUNC_NAME, PROTO_TYPE, PROTO_PARENT, ...)            \
    PROTO_TYPE *FUNC_NAME() {                                                   \
        static PROTO_TYPE __proto__;                                            \
        static PROTO_TYPE *__protoptr__ = NULL;                                 \
        if (__protoptr__ == NULL)                                               \
        {                                                                       \
            __protoptr__ = &__proto__;                                          \
            bzero(__protoptr__, sizeof(__proto__));                             \
            ((CUPrototype *)__protoptr__)->allocator = cu_default_allocator();  \
            cu_inherit((CUPrototype *)(__protoptr__),                           \
                       sizeof(__proto__),                                       \
                       (PROTO_PARENT) == NULL ?                                 \
                                cu_object_prototype() :                         \
                                (CUPrototype *)PROTO_PARENT);                   \
            __VA_ARGS__                                                         \
        }                                                                       \
        return __protoptr__;                                                    \
    }                                                                           \

#define GET_PROTOTYPE(obj, prototype)   ((prototype *)(((CUObject *)(obj))->__prototype__))

/**
 * Returns the default prototype.
 */
extern CUPrototype *cu_object_prototype();

/**
 * Initialises a prototype object with a name and default methods.
 * \param   proto       Prototype type object to initialise.
 * \param   size        Size of the prototype.
 * \param   parent      Parent of the prototype if any.
 */
extern void cu_inherit(CUPrototype *proto, size_t size, CUPrototype *parent);

/**
 * Tells if two prototypes can be casted to each other.
 *
 * \param   proto1  First prototype.
 * \param   proto2  Second prototype.
 * \return  true if proto1 and proto2 can be casted to each other.
 */
extern BOOL cu_implements(CUPrototype *proto1, CUPrototype *proto2);

/**
 * Allocate an object of a given size with a prototype.
 */
extern CUObject *cu_prototype_alloc(CUPrototype *proto, size_t objSize, unsigned initial_refcount);

/**
 * Replaces the value pointed by target with value, taking care of ref counts and links.
 */
extern void cu_prototype_setattr(CUObject **target, CUObject *value, CUObject *parent);

/**
 * Decrements the ref count of an object and calling its destructor if the ref counts hits 0.
 */
extern BOOL cu_prototype_decref(CUObject *obj);

#define cu_alloc1(proto, size)          cu_prototype_alloc((CUPrototype *)(proto), size, 1)
#define cu_alloc(proto, size)           cu_prototype_alloc((CUPrototype *)(proto), size, 0)
#define cu_dealloc(obj)                 cu_allocator_dealloc(GET_PROTOTYPE(obj, CUPrototype)->allocator, obj)
#define cu_incref(obj)                  cu_allocator_incref(GET_PROTOTYPE(obj, CUPrototype)->allocator, obj)
#define cu_decref(obj)                  cu_prototype_decref((CUObject *)(obj))
#define cu_setattr(parent, attrib, value)  cu_prototype_setattr((CUObject **)(&((parent)->attrib)), (CUObject *)(value), (CUObject *)(parent))
#define cu_refcount(obj)                cu_allocator_refcount(GET_PROTOTYPE(obj, CUPrototype)->allocator, obj)
#define cu_hash(proto)                  GET_PROTOTYPE(obj, CUPrototype)->hashFunc(obj)
#define cu_equals(obj1, obj2)           cu_objects_are_equal((CUObject *)(obj1), (CUObject *)(obj2))
#define cu_compare(obj1, obj2)          cu_objects_compare((CUObject *)(obj1), (CUObject *)(obj2))
#define cu_tostring(obj)                GET_PROTOTYPE(obj, CUPrototype)->toStringFunc((CUObject *)obj)

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif
