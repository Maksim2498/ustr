#ifndef USTR_UTIL_ENDIAN_H
#define USTR_UTIL_ENDIAN_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/util/endian.h>
#include <ustr/cview.h>

static const ucv32_t UENDIAN_BIG_NAME    = ucv32("BIG-ENDIAN");
static const ucv32_t UENDIAN_LITTLE_NAME = ucv32("LITTLE-ENDIAN");

void uendian_big_to_host_arr(void *arr, size_t len, size_t el_size);
void uendian_big_to_host(void *val, size_t size);

void uendian_little_to_host_arr(void *arr, size_t len, size_t el_size);
void uendian_little_host_sys(void *val, size_t size);

void uendian_toggle_arr(void *arr, size_t len, size_t el_size);
void uendian_toggle(void *val, size_t size);

ucv32_t uendian_name(uendian_t endian);
bool uendian_valid(uendian_t endian);

#endif