#ifndef USTR_FMT_RADIX_H
#define USTR_FMT_RADIX_H

#include <stdbool.h>

#include <ustr/fmt/case.h>
#include <ustr/cview.h>

enum {
    URADIX_MAX = 36
};

static const ucv32_t UBIN_PREFIX_UPPER = ucv32("0B");
static const ucv32_t UBIN_PREFIX_LOWER = ucv32("0b");

static const ucv32_t UOCT_PREFIX_UPPER = ucv32("0O");
static const ucv32_t UOCT_PREFIX_LOWER = ucv32("0o");

static const ucv32_t UHEX_PREFIX_UPPER = ucv32("0H");
static const ucv32_t UHEX_PREFIX_LOWER = ucv32("0h");

ucv32_t uradix_prefix(unsigned radix, ucase_t ca);
bool uradix_valid(unsigned radix);

#endif