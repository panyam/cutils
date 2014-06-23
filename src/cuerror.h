
#ifndef __CUTILS_ERROR_H__
#define __CUTILS_ERROR_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

/**
 * An error object.
 */
struct LError
{
    int     errorCode;
    char *  errorMessage;
};

/**
 * Creates a new error message.
 *
 * \param   code    Code of the error.
 * \param   msg     Message.
 *
 * \returns A LError instance that must be freed with lerror_destroy.
 */
extern LError *lerror_create(int code, const char *msg);

/**
 * Destroys an error.
 */
extern void lerror_destroy(LError *merror);

/**
 * Sets the message in an error if it is not null.
 */
extern int lerror_set(LError **error, int code, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

