#ifndef USTR_UTIL_ENDIAN_H
#define USTR_UTIL_ENDIAN_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/util/endian.h>
#include <ustr/type/attr.h>
#include <ustr/type/cview.h>

#include "export.h"

// Endian conversion

UEXPORT void uendian_toggle_array_if_big(UINOUT void *array, size_t array_len, size_t el_size);
UEXPORT void uendian_toggle_if_big(UINOUT void *val, size_t size);

UEXPORT void uendian_toggle_array_if_little(UINOUT void *array, size_t array_len, size_t el_size);
UEXPORT void uendian_toggle_if_little(UINOUT void *val, size_t size);

UEXPORT void uendian_toggle_array(UINOUT void *array, size_t array_len, size_t el_size);
UEXPORT void uendian_toggle(UINOUT void *val, size_t size);

// Name

UEXPORT ucv32_t uendian_name_32(uendian_t endian);
UEXPORT ucv16_t uendian_name_16(uendian_t endian);
UEXPORT ucv8_t uendian_name_8(uendian_t endian);

// Valid

UEXPORT bool uendian_valid(uendian_t endian);

#endif