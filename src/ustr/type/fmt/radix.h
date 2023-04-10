#ifndef USTR_TYPE_FMT_RADIX_H
#define USTR_TYPE_FMT_RADIX_H

#include <ustr/type/cview.h>
#include <ustr/util/export.h>

// Prefix

// - Lower

UEXPORT static const ucv32_t UBIN_PREFIX_LOWER_32 = ucv32("0b");
UEXPORT static const ucv16_t UBIN_PREFIX_LOWER_16 = ucv16("0b");
UEXPORT static const ucv8_t  UBIN_PREFIX_LOWER_8  =  ucv8("0b");

UEXPORT static const ucv32_t UOCT_PREFIX_LOWER_32 = ucv32("0o");
UEXPORT static const ucv16_t UOCT_PREFIX_LOWER_16 = ucv16("0o");
UEXPORT static const ucv8_t  UOCT_PREFIX_LOWER_8  =  ucv8("0o");

UEXPORT static const ucv32_t UHEX_PREFIX_LOWER_32 = ucv32("0x");
UEXPORT static const ucv16_t UHEX_PREFIX_LOWER_16 = ucv16("0x");
UEXPORT static const ucv8_t  UHEX_PREFIX_LOWER_8  =  ucv8("0x");

// - Upper

UEXPORT static const ucv32_t UBIN_PREFIX_UPPER_32 = ucv32("0B");
UEXPORT static const ucv16_t UBIN_PREFIX_UPPER_16 = ucv16("0B");
UEXPORT static const ucv8_t  UBIN_PREFIX_UPPER_8  =  ucv8("0B");

UEXPORT static const ucv32_t UOCT_PREFIX_UPPER_32 = ucv32("0O");
UEXPORT static const ucv16_t UOCT_PREFIX_UPPER_16 = ucv16("0O");
UEXPORT static const ucv8_t  UOCT_PREFIX_UPPER_8  =  ucv8("0O");

UEXPORT static const ucv32_t UHEX_PREFIX_UPPER_32 = ucv32("0X");
UEXPORT static const ucv16_t UHEX_PREFIX_UPPER_16 = ucv16("0X");
UEXPORT static const ucv8_t  UHEX_PREFIX_UPPER_8  =  ucv8("0X");

// Type

enum {
    URADIX_MAX = 36
};

typedef unsigned char uradix_t;

#endif