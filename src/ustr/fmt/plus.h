#ifndef USTR_FMT_PLUS_H
#define USTR_FMT_PLUS_H

#include <stdbool.h>

#include <ustr/type/fmt/plus.h>
#include <ustr/type/char.h>
#include <ustr/type/cview.h>
#include <ustr/util/export.h>

// Name

UEXPORT ucv32_t uplus_name_32(uplus_t plus);
UEXPORT ucv16_t uplus_name_16(uplus_t plus);
UEXPORT ucv8_t uplus_name_8(uplus_t plus);

// Char

UEXPORT uc32_t uplus_uc32(uplus_t plus);
UEXPORT uc16_t uplus_uc16(uplus_t plus);
UEXPORT uc8_t uplus_uc8(uplus_t plus);

// Valid

UEXPORT bool uplus_valid(uplus_t plus);

#endif