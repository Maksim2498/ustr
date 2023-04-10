#ifndef USTR_TYPE_UTIL_WRITE_H
#define USTR_TYPE_UTIL_WRITE_H

#include <stdbool.h>

#include <ustr/type/char.h>

typedef bool (*uwrite_uc32_t)(uc32_t, void *);
typedef bool (*uwrite_uc16_t)(uc16_t, void *);
typedef bool (*uwrite_uc8_t)(uc8_t, void *);

#endif