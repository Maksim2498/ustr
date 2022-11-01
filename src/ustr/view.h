#ifndef USTR_VIEW_H
#define USTR_VIEW_H

#include "view_t.h"

#define uv32(literal)                                \
    (uv32_t) {                                       \
        .chars = (U##literal),                       \
        .len   = sizeof(U##literal) / sizeof(uc32_t) \
    }

#endif