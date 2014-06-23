

#ifndef __CUTILS_STREAMS_H__
#define __CUTILS_STREAMS_H__

#include "cuprototype.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

typedef int (*CUStreamCloseFunc)(CUStream *astream);
typedef int (*CUIStreamReadFunc)(CUIStream *instream, void *buffer, int nbytes);
typedef int (*CUIStreamReadByteFunc)(CUIStream *instream);
typedef int (*CUOStreamWriteFunc)(CUOStream *outstream, void *buffer, int nbytes);
typedef int (*CUOStreamWriteByteFunc)(CUOStream *outstream, int data);

CU_INHERIT_STRUCT(CUStreamPrototype, CUPrototype,
    CUStreamCloseFunc closeFunc;
);

CU_INHERIT_STRUCT(CUIStreamPrototype, CUStreamPrototype,
    CUIStreamReadFunc readFunc;
    CUIStreamReadByteFunc readByteFunc;
);

CU_INHERIT_STRUCT(CUOStreamPrototype, CUStreamPrototype,
    CUOStreamWriteFunc writeFunc;
    CUOStreamWriteByteFunc writeByteFunc;
);

#define cu_stream_close(astream)                    GET_PROTOTYPE(astream, CUStreamPrototype)->closeFunc((CUStream *)astream)
#define cu_istream_read(instream, buffer, nbytes)   GET_PROTOTYPE(instream, CUIStreamPrototype)->readFunc((CUIStream *)instream, buffer, nbytes)
#define cu_istream_read_byte(instream)              GET_PROTOTYPE(instream, CUIStreamPrototype)->readByteFunc((CUIStream *)instream)
#define cu_ostream_write(outstream, buffer, nbytes) GET_PROTOTYPE(outstream, CUOStreamPrototype)->writeFunc((CUOStream *)outstream, buffer, nbytes)
#define cu_ostream_write_byte(outstream, value)      GET_PROTOTYPE(outstream, CUOStreamPrototype)->writeByteFunc((CUOStream *)outstream, value)

extern CUIStream *cu_fileistream_create_with_stream(FILE *instream);
extern CUIStream *cu_fileistream_create(const char *path);
extern CUOStream *cu_fileostream_create_with_stream(FILE *outstream);
extern CUOStream *cu_fileostream_create(const char *path, BOOL append);

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

