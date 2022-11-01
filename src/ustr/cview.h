#ifndef USTR_CVIEW_H
#define USTR_CVIEW_H

#include "char_t.h"
#include "cview_t.h"

#define ucv32(literal)                               \
    (ucv32_t) {                                      \
        .chars = (U##literal),                       \
        .len   = sizeof(U##literal) / sizeof(uc32_t) \
    }

#endif