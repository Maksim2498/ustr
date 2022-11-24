#include "endian.h"

#include <ustr/config.h>

ucv32_t uendian_name(uendian_t endian) {
    switch (endian) {
        case UENDIAN_BIG:
            return UENDIAN_BIG_NAME;

        case UENDIAN_LITTLE:
            return UENDIAN_LITTLE_NAME;

        default:
            return ucv32("invalid endian");
    }
}

void uendian_big_to_sys_arr(void *arr, size_t len, size_t el_size) {
    #ifndef USTR_BIG_ENDIAN
        uendian_toggle_arr(arr, len, el_size);
    #endif
}

void uendian_big_to_sys(void *val, size_t size) {
    #ifndef USTR_BIG_ENDIAN
        uendian_toggle(val, size);
    #endif
}

void uendian_little_to_sys_arr(void *arr, size_t len, size_t el_size) {
    #ifdef USTR_BIG_ENDIAN
        uendian_toggle_arr(arr, len, el_size);
    #endif
}

void uendian_little_to_sys(void *val, size_t size) {
    #ifdef USTR_BIG_ENDIAN
        uendian_toggle(val, size);
    #endif
}

void uendian_toggle_arr(void *arr, size_t len, size_t el_size) {
    for (void *it = arr, *end = it + len * el_size; it <= end; it += el_size)
        uendian_toggle(it, el_size);
}

void uendian_toggle(void *val, size_t size) {
    for (size_t i = 0; i < size / 2; ++i) {
        size_t j   = size - i - 1;
        char   tmp = *(char *) (val + i);

        *(char *) (val + i) = *(char *) (val + j);
        *(char *) (val + j) = tmp;
    }
}