
#ifndef __CUTILS_STRING_H__
#define __CUTILS_STRING_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * Gets the native string buffer.
 */
typedef const char *(*CUStringBufferFunc)(const CUString *str);

/**
 * Gets the string size.
 */
typedef size_t (*CUStringLengthFunc)(const CUString *str);

/**
 * Method to return the character at a given index.
 */
typedef int (*CUStringCharAtFunc)(const CUString *str, unsigned index);

/**
 * A string prototype is like a class for a string.
 * This contains the implementation specific function pointers to
 * manipulate and query strings.  This is stored outside the CUString
 * because the pattern for using strings will be by copy/value so copying
 * CUStrings should be quick and cheap.  This obviously comes at the
 * expense of an extra redirection (when accessing the prototype) but we
 * will let the compiler/OS worry about caching that.
 */
CU_INHERIT_STRUCT(CUStringPrototype, CUPrototype,
    CUStringBufferFunc bufferFunc;
    CUStringLengthFunc lengthFunc;
    CUStringCharAtFunc charAtFunc;
);

/**
 * Default string prototype.
 */
extern CUStringPrototype *cu_string_prototype();

/**
 * Create a CUString object from a null terminated string.
 */
extern CUString *cu_string(const char *str);

/**
 * Create a CUString object from an abitrary length string buffer.
 */
extern CUString *cu_string_from_buffer(const char *str, int length);

/**
 * Create a CUString from a formatted string and its parameters.
 */
extern CUString *cu_string_fmt(const char *str, ...);

#define cu_string_buffer(str)           GET_PROTOTYPE(str, CUStringPrototype)->bufferFunc((CUString *)(str))
#define cu_string_char_at(str, index)   GET_PROTOTYPE(str, CUStringPrototype)->charAtFunc((CUString *)(str), index)
#define cu_string_length(str)           GET_PROTOTYPE(str, CUStringPrototype)->lengthFunc((CUString *)(str))
#define cu_string_compare_to_buffer(str, buffer, length) \
                                        GET_PROTOTYPE(str, CUStringPrototype)->compareToBuffer((CUString *)(str), buffer, length)

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

