#ifndef USTR_FMT_RADIX_H
#define USTR_FMT_RADIX_H

#include <stdbool.h>

#include <ustr/fmt/case.h>
#include <ustr/type/fmt/radix.h>
#include <ustr/cview.h>

static const ucv32_t UBIN_PREFIX_UPPER = ucv32("0B");
static const ucv32_t UBIN_PREFIX_LOWER = ucv32("0b");

static const ucv32_t UOCT_PREFIX_UPPER = ucv32("0O");
static const ucv32_t UOCT_PREFIX_LOWER = ucv32("0o");

static const ucv32_t UHEX_PREFIX_UPPER = ucv32("0X");
static const ucv32_t UHEX_PREFIX_LOWER = ucv32("0x");

ucv32_t uradix_prefix(uradix_t radix, ucase_t ca);
bool uradix_has_prefix(uradix_t radix);
bool uradix_valid(uradix_t radix);

#endif