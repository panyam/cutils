
#include "cutils.h"

/**
 * Initialises an already created object.
 * \param   obj     Object to be initialised.
 * \param   proto   Object's prototype to be set as.
 * \return the original object being initialised.
 */
CUObject *cu_object_init(CUObject *obj, CUPrototype *proto)
{
    obj->__prototype__  = proto;
    return obj;
}

/**
 * Returns the string representation of an object.
 *
 * \param   obj    Input object.
 *
 * \return  String representation of an object.
 */
CUString *cu_object_to_string(const CUObject *obj)
{
    return NULL;
}

/**
 * Returns the hash of an object.
 *
 * \param   obj    Object whose hash is to be returned.
 *
 * \return  Object hash.
 */
int cu_object_hash(const CUObject *obj)
{
    return (int)obj;
}

/**
 * Called before deallocating an object.
 *
 * \param   obj    Object to be deallocated and released.
 */
void cu_object_dealloc(CUObject *obj)
{
}

/**
 * Compares two objects to check their relative order.
 *
 * \param   obj1    First obj in the comparison.
 * \param   obj2    Second obj in the comparison.
 *
 * \return  -ve if obj1 < obj2, 0 if they are equal, +ve otherwise
 */
int cu_objects_compare(const CUObject *obj1, const CUObject *obj2)
{
    if (obj1 == obj2)
    {
        return 0;
    }
    else if (obj1 == NULL || obj2 == NULL)
    {
        return obj1 - obj2;
    }
    else if (obj1->__prototype__ == obj2->__prototype__ && obj1->__prototype__->compareFunc)
    {
        assert("Object prototype cannot be NULL" && obj1->__prototype__ != NULL);
        return obj1->__prototype__->compareFunc(obj1, obj2);
    }
    return obj1->__prototype__ - obj2->__prototype__;
}

/**
 * Compares two objects to see if they are equal.
 *
 * \param   obj1   First node in the comparison.
 * \param   obj2   Second node in the comparison.
 *
 * \return  true if nodes are equal (as defined by their equalsFunc
 * callback), false otherwise.
 */
BOOL cu_objects_are_equal(const CUObject *obj1, const CUObject *obj2)
{
    if (obj1 == obj2)
    {
        return true;
    }
    else if (obj2 == NULL || obj1 == NULL)
    {
        return false;
    }
    else if (obj1->__prototype__ == obj2->__prototype__)
    {
        assert("Object prototype cannot be NULL" && obj1->__prototype__ != NULL);
        if (obj1->__prototype__->equalsFunc)
            return obj1->__prototype__->equalsFunc(obj1, obj2);
        else if (obj1->__prototype__->compareFunc)
            return obj1->__prototype__->compareFunc(obj1, obj2) == 0;
    }
    return false;
}

/**
 * Tells if an object can be casted to a particular prototype.
 */
BOOL cu_object_instanceof(const CUObject *obj, const char *proto)
{
    return false;
}

/**
 * Returns the default laya prototype.
 */
DECLARE_PROTO_FUNC(cu_object_prototype, CUPrototype, NULL,
    __proto__.toStringFunc = cu_object_to_string;
    __proto__.hashFunc = cu_object_hash;
    __proto__.deallocFunc = cu_object_dealloc;
);

