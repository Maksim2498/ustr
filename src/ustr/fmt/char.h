#ifndef USTR_FMT_CHAR_H
#define USTR_FMT_CHAR_H

#include <stddef.h>

#include <ustr/type/util/write.h>
#include <ustr/type/char.h>
#include <ustr/util/export.h>

UEXPORT size_t uwrite_uc32_32(uc32_t c, size_t n, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uc16_32(uc16_t c, size_t n, uwrite_uc32_t write, void *write_arg);
UEXPORT size_t uwrite_uc8_32(uc8_t c, size_t n, uwrite_uc32_t write, void *write_arg);

UEXPORT size_t uwrite_uc32_16(uc32_t c, size_t n, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uc16_16(uc16_t c, size_t n, uwrite_uc16_t write, void *write_arg);
UEXPORT size_t uwrite_uc8_16(uc8_t c, size_t n, uwrite_uc16_t write, void *write_arg);

UEXPORT size_t uwrite_uc32_8(uc32_t c, size_t n, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uc16_8(uc16_t c, size_t n, uwrite_uc8_t write, void *write_arg);
UEXPORT size_t uwrite_uc8_8(uc8_t c, size_t n, uwrite_uc8_t write, void *write_arg);

#endif