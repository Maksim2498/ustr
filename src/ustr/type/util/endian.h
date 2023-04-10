#ifndef USTR_TYPE_UTIL_ENDIAN_H
#define USTR_TYPE_UTIL_ENDIAN_H

#include <ustr/util/name.h>
#include <ustr/config.h>

// Name

UEXPORT_NAME(UENDIAN_NONE,   "NONE");
UEXPORT_NAME(UENDIAN_BIG,    "BIG-ENDIAN");
UEXPORT_NAME(UENDIAN_LITTLE, "LITTLE-ENDIAN");

// Type

enum {
    UENDIAN_NONE,
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