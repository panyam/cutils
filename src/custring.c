
#include "cutils.h"

/**
 * Base class of all string implementations.
 */
DECLARE_CLASS(CUString, CUStringPrototype,
    char data[1];
);

#define DATAOF(obj)     (obj->data)

/**
 * Create a CUString object from a null terminated string.
 */
CUString *cu_string(const char *str)
{
    return cu_string_from_buffer(str, -1);
}

/**
 * Create a CUString object from an abitrary length string buffer.
 */
CUString *cu_string_from_buffer(const char *buffer, int length)
{
    if (length < 0)
        length = strlen(buffer);
    CUString *str = (CUString *)cu_alloc(cu_string_prototype(), sizeof(CUString) + length + 1);
    char *dest = DATAOF(str);
    memcpy(dest, buffer, length);
    dest[length] = 0;
    return str;
}

/**
 * Create a CUString from a formatted string and its parameters.
 */
CUString *cu_string_fmt(const char *fmt, ...)
{
    return cu_string(fmt);
}

/**
 * Gets the native string buffer.
 */
const char *cu_default_string_buffer(const CUString *str)
{
    return DATAOF(str);
}

/**
 * Gets the string size.
 */
size_t cu_default_string_length(const CUString *str)
{
    return strlen(DATAOF(str));
}

/**
 * Method to return the character at a given index.
 */
int cu_default_string_char_at(const CUString *str, unsigned index)
{
    return DATAOF(str)[index];
}

/**
 * Method to compare to a buffer.
 */
int cu_default_string_compare(const CUString *str1, const CUString *str2)
{
    return strcmp(DATAOF(str1), DATAOF(str2));
}

CUString *cu_default_string_to_string(CUString *str)
{
    return str;
}

/**
 * Default string prototype.
 */
DECLARE_PROTO_FUNC(cu_string_prototype, CUStringPrototype, NULL,
    __proto__.bufferFunc = cu_default_string_buffer;
    __proto__.lengthFunc = cu_default_string_length;
    __proto__.charAtFunc = cu_default_string_char_at;
    ((CUPrototype *)(&__proto__))->toStringFunc = cu_default_string_to_string;
    ((CUPrototype *)(&__proto__))->compareFunc = (CUObjectCompareFunc)cu_default_string_compare;
);

