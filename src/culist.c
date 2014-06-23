
#include "cutils.h"

CUObject *cu_list_default_getitemat_func(const CUList *list, int index);
void cu_list_default_setitemat_func(const CUList *list, const CUObject *value, int index);
void cu_list_default_additemat_func(const CUList *list, const CUObject *value, int index);
void cu_list_default_removeitemat_func(const CUList *list, int index);
int cu_list_default_indexof_func(const CUList *list, const CUObject *value);
CUList *cu_list_default_splice_func(const CUList *list, int startIndex, int endIndex);

/**
 * Default list prototype.
 */
DECLARE_PROTO_FUNC(cu_list_prototype, CUListPrototype, NULL,
    __proto__.getItemAtFunc = cu_list_default_getitemat_func;
    __proto__.setItemAtFunc = cu_list_default_setitemat_func;
    __proto__.addItemAtFunc = cu_list_default_additemat_func;
    __proto__.removeItemAtFunc = cu_list_default_removeitemat_func;
    __proto__.indexOfFunc = cu_list_default_indexof_func;
    __proto__.spliceFunc = cu_list_default_splice_func;
);

/**************
 * Default prototype methods
 **************/

CUObject *cu_list_default_getitemat_func(const CUList *list, int index)
{
    return NULL;
}

void cu_list_default_setitemat_func(const CUList *list, const CUObject *value, int index)
{
}

void cu_list_default_additemat_func(const CUList *list, const CUObject *value, int index)
{
}

void cu_list_default_removeitemat_func(const CUList *list, int index)
{
}

int cu_list_default_indexof_func(const CUList *list, const CUObject *value)
{
    return -1;
}

CUList *cu_list_default_splice_func(const CUList *list, int startIndex, int endIndex)
{
    return NULL;
}

