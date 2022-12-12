#ifndef USTR_TYPE_UTIL_ENDIAN_H
#define USTR_TYPE_UTIL_ENDIAN_H

#include <ustr/config.h>

enum {
    UENDIAN_BIG,
    UENDIAN_LITTLE,
    UENDIAN_COUNT,

    UENDIAN_HOST = 
        #ifdef USTR_BIG_ENDIAN
            UENDIAN_BIG
        #else
            UENDIAN_LITTLE
        #endif
};

typedef unsigned char uendian_t;

#endif