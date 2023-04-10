#ifndef USTR_FMT_BOOL_H
#define USTR_FMT_BOOL_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/util/write.h>
#include <ustr/util/export.h>

UEXPORT size_t uwrite_bool_32(bool val, ucase_t ca, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_bool_16(bool val, ucase_t ca, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_bool_8(bool val, ucase_t ca, uwrite_uc8_t write, void *write_arg);

#endif