#include "encoding.h"

#include <assert.h>

uendian_t uencoding_endian(uencoding_t encoding) {
    assert(uencoding_valid(encoding));

    switch (encoding) {
        case UENCODING_UTF16LE:
        case UENCODING_UTF32LE:
            return UENDIAN_LITTLE;

        case UENCODING_UTF16BE:
        case UENCODING_UTF32BE:
            return UENDIAN_BIG;

        default:
            return UENDIAN_NONE;
    }
}

#define UENCODING_NAME_X(encoding, X)          \
    assert(uencoding_valid(encoding));         \
                                               \
    switch (encoding) {                        \
        case UENCODING_UTF8:                   \
            return UENCODING_UTF8_NAME_##X;    \
                                               \
        case UENCODING_UTF16LE:                \
            return UENCODING_UTF16LE_NAME_##X; \
                                               \
        case UENCODING_UTF16BE:                \
            return UENCODING_UTF16BE_NAME_##X; \
                                               \
        case UENCODING_UTF32LE:                \
            return UENCODING_UTF32LE_NAME_##X; \
                                               \
        case UENCODING_UTF32BE:                \
            return UENCODING_UTF32BE_NAME_##X; \
                                               \
        default:                               \
            return ucv##X("unknown encoding"); \
    }

ucv32_t uencoding_name_32(uencoding_t encoding) {
    UENCODING_NAME_X(encoding, 32);
}

ucv16_t uencoding_name_16(uencoding_t encoding) {
    UENCODING_NAME_X(encoding, 16);
}

ucv8_t uencoding_name_8(uencoding_t encoding) {
    UENCODING_NAME_X(encoding, 8);
}

bool uencoding_valid(uencoding_t encoding) {
    return encoding < UENCODING_COUNT;
}