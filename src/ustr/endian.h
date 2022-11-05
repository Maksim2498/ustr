#ifndef USTR_ENDIAN_H
#define USTR_ENDIAN_H

#include <stddef.h>

#include "cview.h"
#include "endian_t.h"

static const ucv32_t UENDIAN_BIG_NAME    = ucv32("BIG-ENDIAN");
static const ucv32_t UENDIAN_LITTLE_NAME = ucv32("LITTLE-ENDIAN");

ucv32_t uendian_name(uendian_t endian);

void uendian_big_to_sys_arr(void *arr, size_t len, size_t el_size);
void uendian_big_to_sys(void *val, size_t size);

void uendian_little_to_sys_arr(void *arr, size_t len, size_t el_size);
void uendian_little_to_sys(void *val, size_t size);

void uendian_toggle_arr(void *arr, size_t len, size_t el_size);
void uendian_toggle(void *val, size_t size);

#endif