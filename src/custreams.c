
#include "cutils.h"

DECLARE_CLASS(CUStream, CUStreamPrototype);
DECLARE_CLASS(CUIStream, CUIStreamPrototype);
DECLARE_CLASS(CUOStream, CUOStreamPrototype);

DECLARE_CLASS(CUFileIStream, CUIStream, FILE *infile;);
DECLARE_CLASS(CUFileOStream, CUOStream, FILE *outfile;);

CUIStreamPrototype *cu_fileistream_prototype();
CUOStreamPrototype *cu_fileostream_prototype();

CUIStream *cu_fileistream_create_with_stream(FILE *astream)
{
    CUFileIStream *fis = (CUFileIStream *)cu_alloc(cu_fileistream_prototype(), sizeof(CUFileIStream));
    fis->infile = astream;
    return (CUIStream *)fis;
}

CUIStream *cu_fileistream_create(const char *path)
{
    FILE *infile = fopen(path, "r");
    if (!infile)
        return NULL;
    return cu_fileistream_create_with_stream(infile);
}

CUOStream *cu_fileostream_create_with_stream(FILE *outstream)
{
    CUFileOStream *fos = (CUFileOStream *)cu_alloc(cu_fileostream_prototype(), sizeof(CUFileOStream));
    fos->outfile = outstream;
    return (CUOStream *)fos;
}

CUOStream *cu_fileostream_create(const char *path, BOOL append)
{
    FILE *fout = fopen(path, (append ? "a" : "w"));
    if (!fout)
        return NULL;
    return cu_fileostream_create_with_stream(fout);
}

DECLARE_PROTO_FUNC(cu_stream_prototype, CUStreamPrototype, NULL,
);

DECLARE_PROTO_FUNC(cu_istream_prototype, CUIStreamPrototype, NULL,
);

DECLARE_PROTO_FUNC(cu_ostream_prototype, CUOStreamPrototype, NULL,
);

int fstream_close_func(CUStream *astream)
{
    return fclose(((CUFileIStream *)astream)->infile);
}
int fistream_read_func(CUIStream *instream, void *buffer, int nbytes)
{
    return fread(buffer, 1, nbytes, ((CUFileIStream *)instream)->infile);
}
int fistream_read_byte_func(CUIStream *instream)
{
    char c;
    return fread(&c, 1, 1, ((CUFileIStream *)instream)->infile);
}
int fostream_write_func(CUOStream *outstream, void *buffer, int nbytes)
{
    return fwrite(buffer, 1, nbytes, ((CUFileOStream *)outstream)->outfile);
}
int fostream_write_byte_func(CUOStream *outstream, int data)
{
    char c = data & 0xff;
    return fwrite(&c, 1, 1, ((CUFileOStream *)outstream)->outfile);
}

DECLARE_PROTO_FUNC(cu_fileistream_prototype, CUIStreamPrototype, NULL,
    ((CUStreamPrototype *)__protoptr__)->closeFunc = fstream_close_func;
    __protoptr__->readFunc = fistream_read_func;
    __protoptr__->readByteFunc = fistream_read_byte_func;
);
DECLARE_PROTO_FUNC(cu_fileostream_prototype, CUOStreamPrototype, NULL,
    ((CUStreamPrototype *)__protoptr__)->closeFunc = fstream_close_func;
    __protoptr__->writeFunc = fostream_write_func;
    __protoptr__->writeByteFunc = fostream_write_byte_func;
);

