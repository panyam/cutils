
#ifndef __CUTILS_POOLED_STRING_H__
#define __CUTILS_POOLED_STRING_H__

#include "custring.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

CU_INHERIT_STRUCT(CUPooledString, CUString
    int stringId;
    CUStringPool *pool;
    const char *strPtr;
);

/**
 * Creates a new immutale string.
 * \param   value   Value of the string.
 * \param   length  Length of the string.  If -ve then string is assumed to be null terminated.
 * \param   pool    The String pool from which the string is to be
 *                  sourced.  If NULL, then the default table is used.
 *
 * \return  A new instance of the immutable string.
 */
extern CUPooledString *cu_pooled_string_create(const char *value, int length, CUStringPool *pool);

/**
 * Destroys a string.
 *
 * \param   str String to be destroyed.
 */
extern void cu_pooled_string_destroy(CUPooledString *str);

/**
 * Compares the string contents with another buffer.
 *
 * \param   str    String being compared.
 * \param   value   String being compared to.
 * \param   length  Length of the string being compared to.
 *
 * \return -1 if str < value, 0 if equal else +1
 */
extern int cu_pooled_string_compare(const CUPooledString *str1, const CUPooledString *str2);

/**
 * Tells if two strings are equal.
 */
extern BOOL cu_pooled_strings_are_equal(const CUPooledString *str1, const CUPooledString *str2);

/**
 * Gets the buffer value of the string.
 */
extern const char *cu_pooled_string_buffer(const CUPooledString *str);

/**
 * Gets the length of the string.
 */
extern size_t cu_pooled_string_length(const CUPooledString *str);

/**
 * Compares a string with the contents of a buffer.
 *
 * \param   str     String being compared.
 * \param   buff    Value being compared to.
 * \param   length  Length of the buffer.  If -ve, then buff is null terminated.
 *
 * \return  -ve if str < buff, 0 if they are equal, +ve otherwise
 */
extern int cu_pooled_string_compare_to_buffer(const CUPooledString *str, const char *buffer, int length);


#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

