#ifndef USTR_FMT_RADIX_H
#define USTR_FMT_RADIX_H

#include <stdbool.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/fmt/radix.h>
#include <ustr/type/cview.h>
#include <ustr/util/export.h>

// Prefix

UEXPORT ucv32_t uradix_prefix_32(uradix_t radix, ucase_t ca);
UEXPORT ucv16_t uradix_prefix_16(uradix_t radix, ucase_t ca);
UEXPORT ucv8_t uradix_prefix_8(uradix_t radix, ucase_t ca);

UEXPORT bool uradix_has_prefix(uradix_t radix);

// Valid

UEXPORT bool uradix_valid(uradix_t radix);

#endif