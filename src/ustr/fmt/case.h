#ifndef USTR_FMT_CASE_H
#define USTR_FMT_CASE_H

#include <ustr/type/fmt/case.h>
#include <ustr/cview.h>

static const ucv32_t UCASE_NONE_NAME  = ucv32("NONE");
static const ucv32_t UCASE_UPPER_NAME = ucv32("UPPER");
static const ucv32_t UCASE_LOWER_NAME = ucv32("LOWER");

ucv32_t ucase_name(ucase_t c);
bool ucase_valid(ucase_t c);

#endif