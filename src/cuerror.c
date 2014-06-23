
#include "cutils.h"

/**
 * Creates a new error message.
 *
 * \param   code    Code of the error.
 * \param   msg     Message.
 *
 * \returns A LError instance that must be freed with lerror_free.
 */
LError *lerror_new(int code, const char *msg)
{
    LError *lerror = (LError *)calloc(1, sizeof(LError));
    lerror_set(&lerror, code, msg);
    return lerror;
}

/**
 * Destroys an error.
 */
void lerror_free(LError *lerror)
{
    if (lerror != NULL)
    {
        if (lerror->errorMessage != NULL)
            free(lerror->errorMessage);
        free(lerror);
    }
}

/**
 * Sets the message in an error if it is not null.
 */
int lerror_set(LError **error, int code, const char *format, ...)
{
    const size_t MAX_MESSAGE_SIZE = 256;
    if (error != NULL)
    {
        if (*error == NULL)
        {
            *error = (LError *)calloc(1, sizeof(LError));
        }
        va_list ap;
        va_start(ap, format);
        char buffer[MAX_MESSAGE_SIZE];
        int result = vsnprintf(buffer, MAX_MESSAGE_SIZE, format, ap);
        va_end(ap);
        (*error)->errorCode     = code;
        (*error)->errorMessage  = strdup(buffer);
        return result;
    }
    return 0;
}

