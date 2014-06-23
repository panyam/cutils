
#include "cutils.h"

/**
 * Stores the non-interface data for a prototype.
 */
struct CUPrototypeInfo
{
    /**
     * Prototype this is the details for.
     */
    CUPrototype *prototype;

    /**
     * Size in bytes of the prototype.
     */
    size_t              protoSize;

    /**
     * Level in the prototype hiearchy starting from the root.
     */
    int                 protoLevel;

    /**
     * ID of the parent prototype if any.
     */
    CUPrototypeInfo *parent;
};

/**
 * Creates a new laya prototype info.
 * \param   size    Size of the Prototype structure.
 * \param   parent  Parent prototype (NULL if none).
 * \return NULL if name already exists, otherwise a new Prototype.  No
 * duplicates allowed.
 */
CUPrototypeInfo *cu_protoinfo_new(size_t size, CUPrototypeInfo *parent, CUPrototype *prototype)
{
    CUPrototypeInfo *protoinfo  = ZNEW(CUPrototypeInfo);
    protoinfo->prototype        = prototype;
    protoinfo->parent           = parent;
    protoinfo->protoSize        = size;
    protoinfo->protoLevel       = parent == NULL ? 0 : parent->protoLevel + 1;
    return protoinfo;
}

/**
 * Allocate an object of a given size with a prototype.
 */
CUObject *cu_prototype_alloc(CUPrototype *proto, size_t size, unsigned initial_refcount)
{
    CUObject *obj = (CUObject *)cu_allocator_alloc(proto->allocator, size, initial_refcount);
    obj->__prototype__ = proto;
    return obj;
}

/**
 * Initialises a prototype object with a name and default methods.
 * \param   proto       Prototype type object to initialise.
 * \param   size        Size of the prototype.
 * \param   parent      Parent of the prototype if any.
 */
void cu_inherit(CUPrototype *proto, size_t size, CUPrototype *parent)
{
    if (parent != NULL && parent->protoinfo != NULL)
    {
        // copy all methods from the parent to the child prototype
        memcpy(proto, parent, parent->protoinfo->protoSize);
    }
    proto->protoinfo = cu_protoinfo_new(size, parent == NULL ? NULL : parent->protoinfo, proto);
}


/**
 * Tells if two prototypes can be casted to each other.
 *
 * \param   proto1  First prototype.
 * \param   proto2  Second prototype.
 * \return  true if proto1 and proto2 can be casted to each other.
 */
BOOL cu_implements(CUPrototype *proto1, CUPrototype *proto2)
{
    CUPrototypeInfo *protoInfo1 = proto1->protoinfo;
    CUPrototypeInfo *protoInfo2 = proto2->protoinfo;

    if (protoInfo1->protoLevel < protoInfo2->protoLevel)
    {
        CUPrototypeInfo *ptemp = protoInfo1;
        protoInfo1 = protoInfo2;
        protoInfo2 = ptemp;
    }

    // only bother doing this if level of first proto is lower than
    // level of second proto
    for (CUPrototypeInfo *temp = protoInfo1; temp != NULL && temp->protoLevel >= protoInfo2->protoLevel;temp = temp->parent)
    {
        if (temp == protoInfo2)
            return true;
    }
    return false;
}

/**
 * Decrements the ref count of an object and calling its destructor if the ref counts hits 0.
 */
BOOL cu_prototype_decref(CUObject *obj)
{
    if (obj)
    {
        CUPrototype *proto = GET_PROTOTYPE(obj, CUPrototype);
        CUAllocator *allocator = proto->allocator;
        if (cu_allocator_decref(allocator, obj) == 0)
        {
            if (GET_PROTOTYPE(obj, CUPrototype)->deallocFunc)
                GET_PROTOTYPE(obj, CUPrototype)->deallocFunc(obj);
            cu_dealloc(obj);
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * Replaces the value pointed by target with value, taking care of ref counts and links.
 */
void cu_prototype_setattr(CUObject **target, CUObject *value, CUObject *parent)
{
    assert(target != NULL && "Target cannot be null");
    if (*target != value)
    {
        if (*target)
            cu_decref(*target);
        *target = value;
        if (value)
            cu_incref(value);
    }
}

