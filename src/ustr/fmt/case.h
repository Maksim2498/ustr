#ifndef USTR_FMT_CASE_H
#define USTR_FMT_CASE_H

#include <stdbool.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/cview.h>
#include <ustr/util/export.h>

// Name

UEXPORT ucv32_t ucase_name_32(ucase_t c);
UEXPORT ucv16_t ucase_name_16(ucase_t c);
UEXPORT ucv8_t ucase_name_8(ucase_t c);

// Valid

UEXPORT bool ucase_valid(ucase_t c);
UEXPORT bool ucase_valid_output(ucase_t c);

#endif