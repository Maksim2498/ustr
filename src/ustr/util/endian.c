#include "endian.h"

#include <assert.h>

#include <ustr/config.h>

void uendian_toggle_array_if_big(UINOUT void *array, size_t array_len, size_t el_size) {
    assert(array && el_size);

    #ifdef USTR_BIG_ENDIAN
        uendian_toggle_array(array, array_len, el_size);
    #endif
}

void uendian_toggle_if_big(UINOUT void *val, size_t size) {
    assert(val && size);

    #ifdef USTR_BIG_ENDIAN
        uendian_toggle(val, size);
    #endif
}

void uendian_toggle_array_if_little(UINOUT void *array, size_t array_len, size_t el_size) {
    assert(array && el_size);

    #ifndef USTR_BIG_ENDIAN
        uendian_toggle_array(array, array_len, el_size);
    #endif
}

void uendian_toggle_if_little(UINOUT void *val, size_t size) {
    assert(val && size);

    #ifndef USTR_BIG_ENDIAN
        uendian_toggle(val, size);
    #endif
}

void uendian_toggle_array(UINOUT void *array, size_t array_len, size_t el_size) {
    assert(array && el_size);

    for (void *it = array, *end = it + array_len * el_size; it <= end; it += el_size)
        uendian_toggle(it, el_size);
}

void uendian_toggle(UINOUT void *val, size_t size) {
    assert(val && size);

    for (size_t i = 0, j = size - 1; i < size / 2; ++i, --j) {
        char tmp = *(char *) (val + i);

        *(char *) (val + i) = *(char *) (val + j);
        *(char *) (val + j) = tmp;
    }
}

#define UENDIAN_NAME_X(endian, X)           \
    assert(uendian_valid(endian));          \
                                            \
    switch (endian) {                       \
        case UENDIAN_NONE:                  \
            return UENDIAN_NONE_NAME_##X;   \
                                            \
        case UENDIAN_BIG:                   \
            return UENDIAN_BIG_NAME_##X;    \
                                            \
        case UENDIAN_LITTLE:                \
            return UENDIAN_LITTLE_NAME_##X; \
                                            \
        default:                            \
            return ucv##X("not an endian"); \
    }

ucv32_t uendian_name_32(uendian_t endian) {
    UENDIAN_NAME_X(endian, 32);
}

ucv16_t uendian_name_16(uendian_t endian) {
    UENDIAN_NAME_X(endian, 16);
}

ucv8_t uendian_name_8(uendian_t endian) {
    UENDIAN_NAME_X(endian, 8);
}

bool uendian_valid(uendian_t endian) {
    return endian < UENDIAN_COUNT;
}