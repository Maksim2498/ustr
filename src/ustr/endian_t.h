#ifndef USTR_ENDIAN_T_H
#define USTR_ENDIAN_T_H

#include "config.h"

typedef enum {
    UENDIAN_BIG,
    UENDIAN_LITTLE,
    UENDIAN_COUNT,

    UENDIAN_SYS = 
        #ifdef USTR_BIG_ENDIAN
            UENDIAN_BIG
        #else
            UENDIAN_LITTLE
        #endif
} uendian_t;

#endif