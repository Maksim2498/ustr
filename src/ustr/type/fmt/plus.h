#ifndef USTR_TYPE_FMT_PLUS_H
#define USTR_TYPE_FMT_PLUS_H

#include <ustr/util/name.h>

// Name

UEXPORT_NAME(UPLUS_NONE,  "NONE");
UEXPORT_NAME(UPLUS_SIGN,  "SIGN");
UEXPORT_NAME(UPLUS_SPACE, "SPACE");

// Type

enum {
    UPLUS_NONE,
    UPLUS_SIGN,
    UPLUS_SPACE,
    UPLUS_COUNT
};

typedef unsigned char uplus_t;

#endif