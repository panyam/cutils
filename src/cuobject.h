
#ifndef __CUTILS_OBJECT_H__
#define __CUTILS_OBJECT_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Declares a class of name CLASS_NAME, which has a specific prototype and
 * a reference count.
 */
#define DECLARE_CLASS(CLASS_NAME, PROTOTYPE_NAME, ...)  \
    struct CLASS_NAME                                   \
    {                                                   \
        /**                                             \
         * Base prototype.                              \
         */                                             \
        PROTOTYPE_NAME *__prototype__;                  \
                                                        \
        /**                                             \
         * The object specific data.                    \
         */                                             \
        __VA_ARGS__                                     \
    }

/**
 * Default class of all objects.
 */
DECLARE_CLASS(CUObject, CUPrototype);

/**
 * Initialises an already created object.
 * \param   obj     Object to be initialised.
 * \param   proto   Object's prototype to be set as.
 * \return  Pointer to the same object to simplify copy semantics.
 */
extern CUObject *cu_object_init(CUObject *obj, CUPrototype *proto);

/**
 * Deallocs an object.
 */
extern void cu_object_dealloc(CUObject *obj);

/**
 * Compares two objects to see if they are equal.
 *
 * \param   obj1    First obj in the comparison.
 * \param   obj2    Second obj in the comparison.
 *
 * \return  true if objects are equal (as defined by their objDataEquals
 * callback), false otherwise.
 */
extern BOOL cu_objects_are_equal(const CUObject *obj1, const CUObject *obj2);

/**
 * Compares two objects to check their relative order.
 *
 * \param   obj1    First obj in the comparison.
 * \param   obj2    Second obj in the comparison.
 *
 * \return  -ve if obj1 < obj2, 0 if they are equal, +ve otherwise
 */
extern int cu_objects_compare(const CUObject *obj1, const CUObject *obj2);

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

