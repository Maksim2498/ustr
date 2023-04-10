#include "cstr.h"

#include <assert.h>

#include "fmt/case.h"
#include "fmt/float.h"
#include "fmt/fmt.h"
#include "fmt/int.h"
#include "util/endian.h"
#include "util/mem.h"
#include "char.h"
#include "cview.h"
#include "encoding.h"
#include "str.h"
#include "view.h"

#define UZX_FROM_UZX(to, from, X) \
    assert(from);                 \
                                  \
    if (!to)                      \
        return uz##X##_len(from); \
                                  \
    size_t len = 0;               \
                                  \
    while (*from) {               \
        *to++ = *from++;          \
        ++len;                    \
    }                             \
                                  \
	return len

#define UZX_FROM_UZY_RANGE(to, from, begin, len, X, Y)  \
    assert(uz##Y##_ebounds_range(from, begin, len));    \
    return uz##X##_from_uz##Y##n(to, from + begin, len)

#define UZX_FROM_UZXN(to, from, from_len, X) \
    assert(from);                            \
                                             \
    size_t len = from_len;                   \
                                             \
    if (to)                                  \
        while (from_len--)                   \
            *to++ = *from++;                 \
                                             \
	return len

#define UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, X, Y) \
    assert(uebounds_range(from_len, begin, len));                 \
    return uz##X##_from_uz##Y##n(to, from + begin, len)

#define UZX_FROM_UZYN(to, from, from_len, X, Y)        \
    assert(from);                                      \
                                                       \
    if (!to)                                           \
        return uz##Y##n_len_##X(from, from_len);       \
                                                       \
    size_t len = 0;                                    \
                                                       \
    for (size_t i = 0; i < from_len;) {                \
        unsigned clen = uc##Y##_len(from[i]);          \
                                                       \
        /* Incomplete symbol */                        \
        if (i + clen > from_len)                       \
            break;                                     \
                                                       \
        len += uc##X##_from_uc##Y(to + len, from + i); \
        i   += clen;                                   \
    }                                                  \
                                                       \
    return len

#define UZX_FROM_UZ16(to, from, X)                 \
    assert(from);                                  \
                                                   \
    if (!to)                                       \
        return uz16_len_##X(from);                 \
                                                   \
    size_t len = 0;                                \
                                                   \
    while (*from) {                                \
        unsigned clen = uc16_len(*from);           \
                                                   \
        /* Incomplete symbol */                    \
        if (!from[1] && clen == 2)                 \
            break;                                 \
                                                   \
        len  += uc##X##_from_uc16(to + len, from); \
        from += clen;                              \
    }                                              \
                                                   \
    return len

#define UZX_FORM_UZ32(to, from, X)                       \
    assert(from);                                        \
                                                         \
    if (!to)                                             \
        return uz32_len_##X(from);                       \
                                                         \
    size_t len = 0;                                      \
                                                         \
    while (*from)                                        \
        len += uc##X##_from_uc32_imm(to + len, *from++); \
                                                         \
    return len

#define UZX_FORM_UZ32N(to, from, from_len, X)            \
    assert(from);                                        \
                                                         \
    if (!to)                                             \
        return uz32_len_##X(from);                       \
                                                         \
    size_t len = 0;                                      \
                                                         \
    while (from_len--)                                   \
        len += uc##X##_from_uc32_imm(to + len, *from++); \
                                                         \
    return len

#define UZX_FROM_BYTES(to, from, encoding, X)     \
    assert(uencoding_valid(encoding));            \
                                                  \
    switch (encoding) {                           \
        case UENCODING_UTF32LE:                   \
            return uz##X##_from_uz32le(to, from); \
                                                  \
        case UENCODING_UTF32BE:                   \
            return uz##X##_from_uz32be(to, from); \
                                                  \
        case UENCODING_UTF16LE:                   \
            return uz##X##_from_uz16le(to, from); \
                                                  \
        case UENCODING_UTF16BE:                   \
            return uz##X##_from_uz16be(to, from); \
                                                  \
        case UENCODING_UTF8:                      \
            return uz##X##_from_uz8(to, from);    \
                                                  \
        default:                                  \
            assert(false);                        \
            return 0;                             \
    }

#define UZX_FROM_BYTESN(to, from, from_size, encoding, X)                      \
    assert(uencoding_valid(encoding));                                         \
                                                                               \
    switch (encoding) {                                                        \
        case UENCODING_UTF32LE:                                                \
            return uz##X##_from_uz32len(to, from, from_size / sizeof(uc32_t)); \
                                                                               \
        case UENCODING_UTF32BE:                                                \
            return uz##X##_from_uz32ben(to, from, from_size / sizeof(uc32_t)); \
                                                                               \
        case UENCODING_UTF16LE:                                                \
            return uz##X##_from_uz16len(to, from, from_size / sizeof(uc16_t)); \
                                                                               \
        case UENCODING_UTF16BE:                                                \
            return uz##X##_from_uz16ben(to, from, from_size / sizeof(uc16_t)); \
                                                                               \
        case UENCODING_UTF8:                                                   \
            return uz##X##_from_uz8n(to, from, from_size / sizeof(uc8_t));     \
                                                                               \
        default:                                                               \
            assert(false);                                                     \
            return 0;                                                          \
    }

#define UZXSE_FROM_BYTES(to, from, encoding, X, S)    \
    assert(uencoding_valid(encoding));                \
                                                      \
    switch (encoding) {                               \
        case UENCODING_UTF32LE:                       \
            return uz##X##S##e_from_uz32le(to, from); \
                                                      \
        case UENCODING_UTF32BE:                       \
            return uz##X##S##e_from_uz32be(to, from); \
                                                      \
        case UENCODING_UTF16LE:                       \
            return uz##X##S##e_from_uz16le(to, from); \
                                                      \
        case UENCODING_UTF16BE:                       \
            return uz##X##S##e_from_uz16be(to, from); \
                                                      \
        case UENCODING_UTF8:                          \
            return uz##X##S##e_from_uz8(to, from);    \
                                                      \
        default:                                      \
            assert(false);                            \
            return 0;                                 \
    }

#define UZXSE_FROM_BYTESN(to, from, from_size, encoding, X, S)                     \
    assert(uencoding_valid(encoding));                                             \
                                                                                   \
    switch (encoding) {                                                            \
        case UENCODING_UTF32LE:                                                    \
            return uz##X##S##e_from_uz32len(to, from, from_size / sizeof(uc32_t)); \
                                                                                   \
        case UENCODING_UTF32BE:                                                    \
            return uz##X##S##e_from_uz32ben(to, from, from_size / sizeof(uc32_t)); \
                                                                                   \
        case UENCODING_UTF16LE:                                                    \
            return uz##X##S##e_from_uz16len(to, from, from_size / sizeof(uc16_t)); \
                                                                                   \
        case UENCODING_UTF16BE:                                                    \
            return uz##X##S##e_from_uz16ben(to, from, from_size / sizeof(uc16_t)); \
                                                                                   \
        case UENCODING_UTF8:                                                       \
            return uz##X##S##e_from_uz8n(to, from, from_size / sizeof(uc8_t));     \
                                                                                   \
        default:                                                                   \
            assert(false);                                                         \
            return 0;                                                              \
    }

#define UZXOE_FROM_UZY(to, from, X, Y, OE)                        \
    size_t len = uz##X##_from_uz##Y(to, from);                    \
                                                                  \
    if (to)                                                       \
        uendian_toggle_array_if_##OE(to, len, sizeof(uc##X##_t)); \
                                                                  \
    return len

#define UZXOE_FROM_UZYN(to, from, from_len, X, Y, OE)             \
    size_t len = uz##X##_from_uz##Y##n(to, from, from_len);       \
                                                                  \
    if (to)                                                       \
        uendian_toggle_array_if_##OE(to, len, sizeof(uc##X##_t)); \
                                                                  \
    return len
    
#define UZX_FROM_UZXOE(to, from, X, OE)                             \
    assert(from);                                                   \
                                                                    \
    if (!to)                                                        \
        return uz##X##_len(from);                                   \
                                                                    \
    uc##X##_t *to_begin = to;                                       \
                                                                    \
    while (*from)                                                   \
        *to++ = *from++;                                            \
                                                                    \
    size_t len = to - to_begin;                                     \
                                                                    \
    uendian_toggle_array_if_##OE(to_begin, len, sizeof(uc##X##_t)); \
                                                                    \
    return len

#define UZX_FROM_UZXOEN(to, from, from_len, X, OE)                  \
    assert(from);                                                   \
                                                                    \
    if (!to)                                                        \
        return uz##X##_len(from);                                   \
                                                                    \
    uc##X##_t *to_begin = to;                                       \
                                                                    \
    while (from_len--)                                              \
        *to++ = *from++;                                            \
                                                                    \
    size_t len = to - to_begin;                                     \
                                                                    \
    uendian_toggle_array_if_##OE(to_begin, len, sizeof(uc##X##_t)); \
                                                                    \
    return len
    
#define UZX_FROM_UZYSEN(to, from, from_len, X, Y, S)                        \
    assert(from);                                                           \
                                                                            \
    if (!to)                                                                \
        return uz##Y##S##en_len_##X(from, from_len);                        \
                                                                            \
    size_t len = 0;                                                         \
                                                                            \
    for (size_t i = 0; i < from_len;) {                                     \
        len += uc##X##_from_uc##Y##S##en(to + len, from + i, from_len - i); \
        i   += uc##Y##S##e_len(from[i]);                                    \
    }                                                                       \
                                                                            \
    return len
    
#define UZXSE_FROM_UZXTE(to, from, X)                       \
    assert(from);                                           \
                                                            \
    if (!to)                                                \
        return uz##X##_len(from);                           \
                                                            \
    uc##X##_t *to_begin = to;                               \
                                                            \
    while (*from)                                           \
        *to++ = *from++;                                    \
                                                            \
    size_t len = to - to_begin;                             \
                                                            \
    uendian_toggle_array(to_begin, len, sizeof(uc##X##_t)); \
                                                            \
    return len

#define UZXSE_FROM_UZXTEN(to, from, from_len, X)            \
    assert(from);                                           \
                                                            \
    if (!to)                                                \
        return uz##X##_len(from);                           \
                                                            \
    uc##X##_t *to_begin = to;                               \
    size_t     len      = from_len;                         \
                                                            \
    while (from_len--)                                      \
        *to++ = *from++;                                    \
                                                            \
    uendian_toggle_array(to_begin, len, sizeof(uc##X##_t)); \
                                                            \
    return len
    
#define UZXSE_FROM_UZ32TE(to, from, X, S, T)                       \
    assert(from);                                                  \
                                                                   \
    if (!to)                                                       \
        return uz32##T##e_len_##X(from);                           \
                                                                   \
    size_t len = 0;                                                \
                                                                   \
    while (*from)                                                  \
        len += uc##X##S##e_from_uc32##T##e_imm(to + len, *from++); \
                                                                   \
    return len

#define UZXSE_FROM_UZ32TEN(to, from, from_len, X, S, T)            \
    assert(from);                                                  \
                                                                   \
    if (!to)                                                       \
        return uz32##T##en_len_##X(from, from_len);                \
                                                                   \
    size_t len = 0;                                                \
                                                                   \
    while (from_len--)                                             \
        len += uc##X##S##e_from_uc32##T##e_imm(to + len, *from++); \
                                                                   \
    return len
    
#define UZ32SE_FROM_UZXTEN(to, from, from_len, S, X, T)                        \
    assert(from);                                                              \
                                                                               \
    if (!to)                                                                   \
        return uz##X##T##en_len_32(from, from_len);                            \
                                                                               \
    size_t len = 0;                                                            \
                                                                               \
    for (size_t i = 0; i < from_len;) {                                        \
        len += uc32##S##e_from_uc##X##T##en(to + len, from + i, from_len - i); \
        i   += uc##X##T##e_len(from[i]);                                       \
    }                                                                          \
                                                                               \
    return len

size_t uz32_from_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZX_FROM_UZX(to, from, 32);
}

size_t uz32_from_uz32_range(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 32, 32);
}

size_t uz32_from_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 32);
}

size_t uz32_from_uz32n_range(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 32, 32);
}

size_t uz32_from_ucv32(UNULLABLE UOUT uc32_t *to, ucv32_t from) {
    return uz32_from_uz32n(to, UCV32_CEXPAND(from));
}

size_t uz32_from_ucv32_range(UNULLABLE UOUT uc32_t *to, ucv32_t from, size_t begin, size_t len) {
	return uz32_from_uz32n_range(to, UCV32_CEXPAND(from), begin, len);
}

size_t uz32_from_uv32(UNULLABLE UOUT uc32_t *to, uv32_t from) {
	return uz32_from_uz32n(to, UV32_CEXPAND(from));
}

size_t uz32_from_uv32_range(UNULLABLE UOUT uc32_t *to, uv32_t from, size_t begin, size_t len) {
	return uz32_from_uz32n_range(to, UV32_CEXPAND(from), begin, len);
}

size_t uz32_from_us32(UNULLABLE UOUT uc32_t *to, const us32_t *from) {
	return uz32_from_uz32n(to, US32_CEXPAND(from));
}

size_t uz32_from_us32_range(UNULLABLE UOUT uc32_t *to, const us32_t *from, size_t begin, size_t len) {
	return uz32_from_uz32n_range(to, US32_CEXPAND(from), begin, len);
}

size_t uz32_from_uz16(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    UZX_FROM_UZ16(to, from, 32);
}

size_t uz32_from_uz16_range(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 32, 16);
}

size_t uz32_from_uz16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZYN(to, from, from_len, 32, 16);
}

size_t uz32_from_uz16n_range(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 32, 16);
}

size_t uz32_from_ucv16(UNULLABLE UOUT uc32_t *to, ucv16_t from) {
	return uz32_from_uz16n(to, UCV16_CEXPAND(from));
}

size_t uz32_from_ucv16_range(UNULLABLE UOUT uc32_t *to, ucv16_t from, size_t begin, size_t len) {
	return uz32_from_uz16n_range(to, UCV16_CEXPAND(from), begin, len);
}

size_t uz32_from_uv16(UNULLABLE UOUT uc32_t *to, uv16_t from) {
	return uz32_from_uz16n(to, UV16_CEXPAND(from));
}

size_t uz32_from_uv16_range(UNULLABLE UOUT uc32_t *to, uv16_t from, size_t begin, size_t len) {
	return uz32_from_uz16n_range(to, UV16_CEXPAND(from), begin, len);
}

size_t uz32_from_us16(UNULLABLE UOUT uc32_t *to, const us16_t *from) {
    return uz32_from_uz16n(to, US16_CEXPAND(from));
}

size_t uz32_from_us16_range(UNULLABLE UOUT uc32_t *to, const us16_t *from, size_t begin, size_t len) {
    return uz32_from_uz16n_range(to, US16_CEXPAND(from), begin, len);
}

size_t uz32_from_uz8(UNULLABLE UOUT uc32_t *to, const uc8_t *from) {
    return uz32_from_uz8n(to, from, uz8_len(from));
}

size_t uz32_from_uz8_range(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 32, 8);
}

size_t uz32_from_uz8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len) {
    UZX_FROM_UZYN(to, from, from_len, 32, 8);
}

size_t uz32_from_uz8n_range(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 32, 8);
}

size_t uz32_from_ucv8(UNULLABLE UOUT uc32_t *to, ucv8_t from) {
    return uz32_from_uz8n(to, UCV8_CEXPAND(from));
}

size_t uz32_from_ucv8_range(UNULLABLE UOUT uc32_t *to, ucv8_t from, size_t begin, size_t len) {
    return uz32_from_uz8n_range(to, UCV8_CEXPAND(from), begin, len);
}

size_t uz32_from_uv8(UNULLABLE UOUT uc32_t *to, uv8_t from) {
    return uz32_from_uz8n(to, UV8_CEXPAND(from));
}

size_t uz32_from_uv8_range(UNULLABLE UOUT uc32_t *to, uv8_t from, size_t begin, size_t len) {
    return uz32_from_uz8n_range(to, UV8_CEXPAND(from), begin, len);
}

size_t uz32_from_us8(UNULLABLE UOUT uc32_t *to, const us8_t *from) {
	return uz32_from_uz8n(to, US8_CEXPAND(from));
}

size_t uz32_from_us8_range(UNULLABLE UOUT uc32_t *to, const us8_t *from, size_t begin, size_t len) {
	return uz32_from_uz8n_range(to, US8_CEXPAND(from), begin, len);
}

size_t uz32_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding) {
    UZX_FROM_BYTES(to, from, encoding, 32);
}

size_t uz32_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZX_FROM_BYTESN(to, from, from_size, encoding, 32);
}

size_t uz32_from_uz32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZX_FROM_UZXOE(to, from, 32, big);
}

size_t uz32_from_uz32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZXOEN(to, from, from_len, 32, big);
}

size_t uz32_from_uz16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    return uz32_from_uz16len(to, from, uz16_len(from));
}

size_t uz32_from_uz16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 32, 16, l);
}

size_t uz32_from_uz32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZX_FROM_UZXOE(to, from, 32, little);
}

size_t uz32_from_uz32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZXOEN(to, from, from_len, 32, little);
}

size_t uz32_from_uz16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    return uz32_from_uz16ben(to, from, uz16_len(from));
}

size_t uz32_from_uz16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 32, 16, b);
}

size_t uz32le_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding) {
    UZXSE_FROM_BYTES(to, from, encoding, 32, l);
}

size_t uz32le_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZXSE_FROM_BYTESN(to, from, from_size, encoding, 32, l);
}

size_t uz32le_from_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZXOE_FROM_UZY(to, from, 32, 32, big);
}

size_t uz32le_from_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 32, 32, big);
}

size_t uz32le_from_uz16(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    UZXOE_FROM_UZY(to, from, 32, 16, big);
}

size_t uz32le_from_uz16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 32, 16, big);
}

size_t uz32le_from_uz8(UNULLABLE UOUT uc32_t *to, const uc8_t *from) {
    UZXOE_FROM_UZY(to, from, 32, 8, big);
}

size_t uz32le_from_uz8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 32, 8, big);
}

size_t uz32le_from_uz32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZX_FROM_UZX(to, from, 32);
}

size_t uz32le_from_uz32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 32);
}

size_t uz32le_from_uz16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    return uz32le_from_uz16len(to, from, uz16_len(from));
}

size_t uz32le_from_uz16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZ32SE_FROM_UZXTEN(to, from, from_len, l, 16, l);
}

size_t uz32le_from_uz32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZXSE_FROM_UZXTE(to, from, 32);
}

size_t uz32le_from_uz32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZXSE_FROM_UZXTEN(to, from, from_len, 32);
}

size_t uz32le_from_uz16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    return uz32le_from_uz16ben(to, from, uz16_len(from));
}

size_t uz32le_from_uz16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZ32SE_FROM_UZXTEN(to, from, from_len, l, 16, b);
}

size_t uz32be_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding) {
    UZXSE_FROM_BYTES(to, from, encoding, 32, b);
}

size_t uz32be_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZXSE_FROM_BYTESN(to, from, from_size, encoding, 32, b);
}

size_t uz32be_from_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZXOE_FROM_UZY(to, from, 32, 32, little);
}

size_t uz32be_from_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 32, 32, little);
}

size_t uz32be_from_uz16(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    UZXOE_FROM_UZY(to, from, 32, 16, little);
}

size_t uz32be_from_uz16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 32, 16, little);
}

size_t uz32be_from_uz8(UNULLABLE UOUT uc32_t *to, const uc8_t *from) {
    UZXOE_FROM_UZY(to, from, 32, 8, little);
}

size_t uz32be_from_uz8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 32, 8, little);
}

size_t uz32be_from_uz32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZXSE_FROM_UZXTE(to, from, 32);
}

size_t uz32be_from_uz32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZXSE_FROM_UZXTEN(to, from, from_len, 32);
}

size_t uz32be_from_uz16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    return uz32be_from_uz16len(to, from, uz16_len(from));
}

size_t uz32be_from_uz16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZ32SE_FROM_UZXTEN(to, from, from_len, b, 16, l);
}

size_t uz32be_from_uz32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from) {
    UZX_FROM_UZX(to, from, 32);
}

size_t uz32be_from_uz32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 32);
}

size_t uz32be_from_uz16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from) {
    return uz32be_from_uz16ben(to, from, uz16_len(from));
}

size_t uz32be_from_uz16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len) {
    UZ32SE_FROM_UZXTEN(to, from, from_len, b, 16, b);
}

size_t uz16_from_uz32(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZX_FORM_UZ32(to, from, 16);
}

size_t uz16_from_uz32_range(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 16, 32);
}

size_t uz16_from_uz32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZX_FORM_UZ32N(to, from, from_len, 16);
}

size_t uz16_from_uz32n_range(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 16, 32);
}

size_t uz16_from_ucv32(UNULLABLE UOUT uc16_t *to, ucv32_t from) {
    return uz16_from_uz32n(to, UCV32_CEXPAND(from));
}

size_t uz16_from_ucv32_range(UNULLABLE UOUT uc16_t *to, ucv32_t from, size_t begin, size_t len) {
    return uz16_from_uz32n_range(to, UCV32_CEXPAND(from), begin, len);
}

size_t uz16_from_uv32(UNULLABLE UOUT uc16_t *to, uv32_t from) {
    return uz16_from_uz32n(to, UV32_CEXPAND(from));
}

size_t uz16_from_uv32_range(UNULLABLE UOUT uc16_t *to, uv32_t from, size_t begin, size_t len) {
    return uz16_from_uz32n_range(to, UV32_CEXPAND(from), begin, len);
}

size_t uz16_from_us32(UNULLABLE UOUT uc16_t *to, const us32_t *from) {
    return uz16_from_uz32n(to, US32_CEXPAND(from));
}

size_t uz16_from_us32_range(UNULLABLE UOUT uc16_t *to, const us32_t *from, size_t begin, size_t len) {
    return uz16_from_uz32n_range(to, US32_CEXPAND(from), begin, len);
}

size_t uz16_from_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZX_FROM_UZX(to, from, 16);
}

size_t uz16_from_uz16_range(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 16, 16);
}

size_t uz16_from_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 16);
}

size_t uz16_from_uz16n_range(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 16, 16);
}

size_t uz16_from_ucv16(UNULLABLE UOUT uc16_t *to, ucv16_t from) {
	return uz16_from_uz16n(to, UCV16_CEXPAND(from));
}

size_t uz16_from_ucv16_range(UNULLABLE UOUT uc16_t *to, ucv16_t from, size_t begin, size_t len) {
	return uz16_from_uz16n_range(to, UCV16_CEXPAND(from), begin, len);
}

size_t uz16_from_uv16(UNULLABLE UOUT uc16_t *to, uv16_t from) {
	return uz16_from_uz16n(to, UV16_CEXPAND(from));
}

size_t uz16_from_uv16_range(UNULLABLE UOUT uc16_t *to, uv16_t from, size_t begin, size_t len) {
	return uz16_from_uz16n_range(to, UV16_CEXPAND(from), begin, len);
}

size_t uz16_from_us16(UNULLABLE UOUT uc16_t *to, const us16_t *from) {
	return uz16_from_uz16n(to, US16_CEXPAND(from));
}

size_t uz16_from_us16_range(UNULLABLE UOUT uc16_t *to, const us16_t *from, size_t begin, size_t len) {
	return uz16_from_uz16n_range(to, US16_CEXPAND(from), begin, len);
}

size_t uz16_from_uz8(UNULLABLE UOUT uc16_t *to, const uc8_t *from) {
    return uz16_from_uz8n(to, from, uz8_len(from));
}

size_t uz16_from_uz8_range(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 16, 8);
}

size_t uz16_from_uz8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len) {
    UZX_FROM_UZYN(to, from, from_len, 16, 8);
}

size_t uz16_from_uz8n_range(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 16, 8);
}

size_t uz16_from_ucv8(UNULLABLE UOUT uc16_t *to, ucv8_t from) {
	return uz16_from_uz8n(to, UCV8_CEXPAND(from));
}

size_t uz16_from_ucv8_range(UNULLABLE UOUT uc16_t *to, ucv8_t from, size_t begin, size_t len) {
	return uz16_from_uz8n_range(to, UCV8_CEXPAND(from), begin, len);
}

size_t uz16_from_uv8(UNULLABLE UOUT uc16_t *to, uv8_t from) {
	return uz16_from_uz8n(to, UV8_CEXPAND(from));
}

size_t uz16_from_uv8_range(UNULLABLE UOUT uc16_t *to, uv8_t from, size_t begin, size_t len) {
	return uz16_from_uz8n_range(to, UV8_CEXPAND(from), begin, len);
}

size_t uz16_from_us8(UNULLABLE UOUT uc16_t *to, const us8_t *from) {
	return uz16_from_uz8n(to, US8_CEXPAND(from));
}

size_t uz16_from_us8_range(UNULLABLE UOUT uc16_t *to, const us8_t *from, size_t begin, size_t len) {
	return uz16_from_uz8n_range(to, US8_CEXPAND(from), begin, len);
}

size_t uz16_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding) {
    UZX_FROM_BYTES(to, from, encoding, 16);
}

size_t uz16_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZX_FROM_BYTESN(to, from, from_size, encoding, 16);
}

size_t uz16_from_uz32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    return uz16_from_uz32len(to, from, uz32_len(from));
}

size_t uz16_from_uz32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 16, 32, l);
}

size_t uz16_from_uz16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZX_FROM_UZXOE(to, from, 16, big);
}

size_t uz16_from_uz16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZXOEN(to, from, from_len, 16, big);
}

size_t uz16_from_uz32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    return uz16_from_uz32ben(to, from, uz32_len(from));
}

size_t uz16_from_uz32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 16, 32, b);
}

size_t uz16_from_uz16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZX_FROM_UZXOE(to, from, 16, little);
}

size_t uz16_from_uz16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZXOEN(to, from, from_len, 16, little);
}

size_t uz16le_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding) {
    UZXSE_FROM_BYTES(to, from, encoding, 16, l);
}

size_t uz16le_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZXSE_FROM_BYTESN(to, from, from_size, encoding, 16, l);
}

size_t uz16le_from_uz32(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZXOE_FROM_UZY(to, from, 16, 32, big);
}

size_t uz16le_from_uz32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 16, 32, big);
}

size_t uz16le_from_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZXOE_FROM_UZY(to, from, 16, 16, big);
}

size_t uz16le_from_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 16, 16, big);
}

size_t uz16le_from_uz8(UNULLABLE UOUT uc16_t *to, const uc8_t *from) {
    UZXOE_FROM_UZY(to, from, 16, 8, big);
}

size_t uz16le_from_uz8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 16, 8, big);
}

size_t uz16le_from_uz32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZXSE_FROM_UZ32TE(to, from, 16, l, l);
}

size_t uz16le_from_uz32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZXSE_FROM_UZ32TEN(to, from, from_len, 16, l, l);
}

size_t uz16le_from_uz16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZX_FROM_UZX(to, from, 16);
}

size_t uz16le_from_uz16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 16);
}

size_t uz16le_from_uz32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZXSE_FROM_UZ32TE(to, from, 16, l, b);
}

size_t uz16le_from_uz32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZXSE_FROM_UZ32TEN(to, from, from_len, 16, l, b);
}

size_t uz16le_from_uz16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZXSE_FROM_UZXTE(to, from, 16);
}

size_t uz16le_from_uz16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZXSE_FROM_UZXTEN(to, from, from_len, 16);
}

size_t uz16be_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding) {
    UZXSE_FROM_BYTES(to, from, encoding, 16, b);
}

size_t uz16be_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZXSE_FROM_BYTESN(to, from, from_size, encoding, 16, b);
}

size_t uz16be_from_uz32(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZXOE_FROM_UZY(to, from, 16, 32, little);
}

size_t uz16be_from_uz32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 16, 32, little);
}

size_t uz16be_from_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZXOE_FROM_UZY(to, from, 16, 16, little);
}

size_t uz16be_from_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 16, 16, little);
}

size_t uz16be_from_uz8(UNULLABLE UOUT uc16_t *to, const uc8_t *from) {
    UZXOE_FROM_UZY(to, from, 16, 8, little);
}

size_t uz16be_from_uz8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len) {
    UZXOE_FROM_UZYN(to, from, from_len, 16, 8, little);
}

size_t uz16be_from_uz32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZXSE_FROM_UZ32TE(to, from, 16, b, l);
}

size_t uz16be_from_uz32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZXSE_FROM_UZ32TEN(to, from, from_len, 16, b, l);
}

size_t uz16be_from_uz16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZXSE_FROM_UZXTE(to, from, 16);
}

size_t uz16be_from_uz16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZXSE_FROM_UZXTEN(to, from, from_len, 16);
}

size_t uz16be_from_uz32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from) {
    UZXSE_FROM_UZ32TE(to, from, 16, b, b);
}

size_t uz16be_from_uz32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len) {
    UZXSE_FROM_UZ32TEN(to, from, from_len, 16, b, b);
}

size_t uz16be_from_uz16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from) {
    UZX_FROM_UZX(to, from, 16);
}

size_t uz16be_from_uz16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 16);
}

size_t uz8_from_uz32(UNULLABLE UOUT uc8_t *to, const uc32_t *from) {
    UZX_FORM_UZ32(to, from, 8);
}

size_t uz8_from_uz32_range(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 8, 32);
}

size_t uz8_from_uz32n(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len) {
    UZX_FORM_UZ32N(to, from, from_len, 8);
}

size_t uz8_from_uz32n_range(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 8, 32);
}

size_t uz8_from_ucv32(UNULLABLE UOUT uc8_t *to, ucv32_t from) {
	return uz8_from_uz32n(to, UCV32_CEXPAND(from));
}

size_t uz8_from_ucv32_range(UNULLABLE UOUT uc8_t *to, ucv32_t from, size_t begin, size_t len) {
	return uz8_from_uz32n_range(to, UCV32_CEXPAND(from), begin, len);
}

size_t uz8_from_uv32(UNULLABLE UOUT uc8_t *to, uv32_t from) {
	return uz8_from_uz32n(to, UV32_CEXPAND(from));
}

size_t uz8_from_uv32_range(UNULLABLE UOUT uc8_t *to, uv32_t from, size_t begin, size_t len) {
	return uz8_from_uz32n_range(to, UV32_CEXPAND(from), begin, len);
}

size_t uz8_from_us32(UNULLABLE UOUT uc8_t *to, const us32_t *from) {
	return uz8_from_uz32n(to, US32_CEXPAND(from));
}

size_t uz8_from_us32_range(UNULLABLE UOUT uc8_t *to, const us32_t *from, size_t begin, size_t len) {
	return uz8_from_uz32n_range(to, US32_CEXPAND(from), begin, len);
}

size_t uz8_from_uz16(UNULLABLE UOUT uc8_t *to, const uc16_t *from) {
    UZX_FROM_UZ16(to, from, 8);
}

size_t uz8_from_uz16_range(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 8, 16);
}

size_t uz8_from_uz16n(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZYN(to, from, from_len, 8, 16);
}

size_t uz8_from_uz16n_range(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 8, 16);
}

size_t uz8_from_ucv16(UNULLABLE UOUT uc8_t *to, ucv16_t from) {
    return uz8_from_uz16n(to, UCV16_CEXPAND(from));
}

size_t uz8_from_ucv16_range(UNULLABLE UOUT uc8_t *to, ucv16_t from, size_t begin, size_t len) {
    return uz8_from_uz16n_range(to, UCV16_CEXPAND(from), begin, len);
}

size_t uz8_from_uv16(UNULLABLE UOUT uc8_t *to, uv16_t from) {
    return uz8_from_uz16n(to, UV16_CEXPAND(from));
}

size_t uz8_from_uv16_range(UNULLABLE UOUT uc8_t *to, uv16_t from, size_t begin, size_t len) {
    return uz8_from_uz16n_range(to, UV16_CEXPAND(from), begin, len);
}

size_t uz8_from_us16(UNULLABLE UOUT uc8_t *to, const us16_t *from) {
    return uz8_from_uz16n(to, US16_CEXPAND(from));
}

size_t uz8_from_us16_range(UNULLABLE UOUT uc8_t *to, const us16_t *from, size_t begin, size_t len) {
    return uz8_from_uz16n_range(to, US16_CEXPAND(from), begin, len);
}

size_t uz8_from_uz8(UNULLABLE UOUT uc8_t *to, const uc8_t *from) {
    UZX_FROM_UZX(to, from, 8);
}

size_t uz8_from_uz8_range(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t begin, size_t len) {
    UZX_FROM_UZY_RANGE(to, from, begin, len, 8, 8);
}

size_t uz8_from_uz8n(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len) {
    UZX_FROM_UZXN(to, from, from_len, 8);
}

size_t uz8_from_uz8n_range(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, size_t begin, size_t len) {
    UZX_FROM_UZYN_RANGE(to, from, from_len, begin, len, 8, 8);
}

size_t uz8_from_ucv8(UNULLABLE UOUT uc8_t *to, ucv8_t from) {
    return uz8_from_uz8n(to, UCV8_CEXPAND(from));
}

size_t uz8_from_ucv8_range(UNULLABLE UOUT uc8_t *to, ucv8_t from, size_t begin, size_t len) {
    return uz8_from_uz8n_range(to, UCV8_CEXPAND(from), begin, len);
}

size_t uz8_from_uv8(UNULLABLE UOUT uc8_t *to, uv8_t from) {
    return uz8_from_uz8n(to, UV8_CEXPAND(from));
}

size_t uz8_from_uv8_range(UNULLABLE UOUT uc8_t *to, uv8_t from, size_t begin, size_t len) {
    return uz8_from_uz8n_range(to, UV8_CEXPAND(from), begin, len);
}

size_t uz8_from_us8(UNULLABLE UOUT uc8_t *to, const us8_t *from) {
    return uz8_from_uz8n(to, US8_CEXPAND(from));
}

size_t uz8_from_us8_range(UNULLABLE UOUT uc8_t *to, const us8_t *from, size_t begin, size_t len) {
    return uz8_from_uz8n_range(to, US8_CEXPAND(from), begin, len);
}

size_t uz8_from_bytes(UNULLABLE UOUT uc8_t *to, const void *from, uencoding_t encoding) {
    UZX_FROM_BYTES(to, from, encoding, 8);
}

size_t uz8_from_bytesn(UNULLABLE UOUT uc8_t *to, const void *from, size_t from_size, uencoding_t encoding) {
    UZX_FROM_BYTESN(to, from, from_size, encoding, 8);
}

size_t uz8_from_uz32le(UNULLABLE UOUT uc8_t *to, const uc32_t *from) {
    return uz8_from_uz32len(to, from, uz32_len(from));
}

size_t uz8_from_uz32len(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 8, 32, l);
}

size_t uz8_from_uz16le(UNULLABLE UOUT uc8_t *to, const uc16_t *from) {
    return uz8_from_uz16len(to, from, uz16_len(from));
}

size_t uz8_from_uz16len(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 8, 16, l);
}

size_t uz8_from_uz32be(UNULLABLE UOUT uc8_t *to, const uc32_t *from) {
    return uz8_from_uz32ben(to, from, uz32_len(from));
}

size_t uz8_from_uz32ben(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 8, 32, b);
}

size_t uz8_from_uz16be(UNULLABLE UOUT uc8_t *to, const uc16_t *from) {
    return uz8_from_uz16ben(to, from, uz16_len(from));
}

size_t uz8_from_uz16ben(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len) {
    UZX_FROM_UZYSEN(to, from, from_len, 8, 16, b);
}

#define UWRITE_UCX_TO_UZX(c, arg, X) \
        uc##X##_t **cstr = arg;      \
                                     \
        if (*cstr)                   \
            *(*cstr)++ = c;          \
                                     \
        return false

static bool uwrite_uc32_to_uz32(uc32_t c, void *arg) {
    UWRITE_UCX_TO_UZX(c, arg, 32);
}

static bool uwrite_uc16_to_uz16(uc16_t c, void *arg) {
    UWRITE_UCX_TO_UZX(c, arg, 16);
}

static bool uwrite_uc8_to_uz8(uc8_t c, void *arg) {
    UWRITE_UCX_TO_UZX(c, arg, 8);
}

#define UZX_FROM_FMT_T(to, from, X, T)                      \
    va_list args;                                           \
    va_start(args, from);                                   \
    size_t len = uz##X##_from_fmt_##T##_v(to, from, &args); \
    va_end(args);                                           \
    return len

#define UZX_FROM_FMT_UZXN(to, from, from_len, X)                           \
    va_list args;                                                          \
    va_start(args, from_len);                                              \
    size_t len = uz##X##_from_fmt_uz##X##n##_v(to, from, from_len, &args); \
    va_end(args);                                                          \
    return len

size_t uz32_from_fmt_uz32(UNULLABLE UOUT uc32_t *to, const uc32_t *from, ...) {
    UZX_FROM_FMT_T(to, from, 32, uz32);
}

size_t uz32_from_fmt_uz32_v(UNULLABLE UOUT uc32_t *to, const uc32_t *from, va_list *args) {
    return uz32_from_fmt_uz32n_v(to, from, uz32_len(from), args);
}

size_t uz32_from_fmt_uz32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len, ...) {
    UZX_FROM_FMT_UZXN(to, from, from_len, 32);
}

size_t uz32_from_fmt_uz32n_v(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len, va_list *args) {
    return uwrite_fmt_uz32n_32_v(from, from_len, uwrite_uc32_to_uz32, &to, args);
}

size_t uz32_from_fmt_ucv32(UNULLABLE UOUT uc32_t *to, ucv32_t from, ...) {
    UZX_FROM_FMT_T(to, from, 32, ucv32);
}

size_t uz32_from_fmt_ucv32_v(UNULLABLE UOUT uc32_t *to, ucv32_t from, va_list *args) {
	return uz32_from_fmt_uz32n_v(to, UCV32_CEXPAND(from), args);
}

size_t uz32_from_fmt_uv32(UNULLABLE UOUT uc32_t *to, uv32_t from, ...) {
    UZX_FROM_FMT_T(to, from, 32, uv32);
}

size_t uz32_from_fmt_uv32_v(UNULLABLE UOUT uc32_t *to, uv32_t from, va_list *args) {
	return uz32_from_fmt_uz32n_v(to, UV32_CEXPAND(from), args);
}

size_t uz32_from_fmt_us32(UNULLABLE UOUT uc32_t *to, const us32_t *from, ...) {
    UZX_FROM_FMT_T(to, from, 32 ,us32);
}

size_t uz32_from_fmt_us32_v(UNULLABLE UOUT uc32_t *to, const us32_t *from, va_list *args) {
	return uz32_from_fmt_uz32n_v(to, US32_CEXPAND(from), args);
}

size_t uz16_from_fmt_uz16(UNULLABLE UOUT uc16_t *to, const uc16_t *from, ...) {
    UZX_FROM_FMT_T(to, from, 16, uz16);
}

size_t uz16_from_fmt_uz16_v(UNULLABLE UOUT uc16_t *to, const uc16_t *from, va_list *args) {
    return uz16_from_fmt_uz16n_v(to, from, uz16_len(from), args);
}

size_t uz16_from_fmt_uz16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len, ...) {
    UZX_FROM_FMT_UZXN(to, from, from_len, 16);
}

size_t uz16_from_fmt_uz16n_v(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len, va_list *args) {
    return uwrite_fmt_uz16n_16_v(from, from_len, uwrite_uc16_to_uz16, &to, args);
}

size_t uz16_from_fmt_ucv16(UNULLABLE UOUT uc16_t *to, ucv16_t from, ...) {
    UZX_FROM_FMT_T(to, from, 16, ucv16);
}

size_t uz16_from_fmt_ucv16_v(UNULLABLE UOUT uc16_t *to, ucv16_t from, va_list *args) {
	return uz16_from_fmt_uz16n_v(to, UCV16_CEXPAND(from), args);
}

size_t uz16_from_fmt_uv16(UNULLABLE UOUT uc16_t *to, uv16_t from, ...) {
    UZX_FROM_FMT_T(to, from, 16, uv16);
}

size_t uz16_from_fmt_uv16_v(UNULLABLE UOUT uc16_t *to, uv16_t from, va_list *args) {
	return uz16_from_fmt_uz16n_v(to, UV16_CEXPAND(from), args);
}

size_t uz16_from_fmt_us16(UNULLABLE UOUT uc16_t *to, const us16_t *from, ...) {
    UZX_FROM_FMT_T(to, from, 16, us16);
}

size_t uz16_from_fmt_us16_v(UNULLABLE UOUT uc16_t *to, const us16_t *from, va_list *args) {
	return uz16_from_fmt_uz16n_v(to, US16_CEXPAND(from), args);
}

size_t uz8_from_fmt_uz8(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ...) {
    UZX_FROM_FMT_T(to, from, 8, uz8);
}

size_t uz8_from_fmt_uz8_v(UNULLABLE UOUT uc8_t *to, const uc8_t *from, va_list *args) {
    return uz8_from_fmt_uz8n_v(to, from, uz8_len(from), args);
}

size_t uz8_from_fmt_uz8n(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ...) {
    UZX_FROM_FMT_UZXN(to, from, from_len, 8);
}

size_t uz8_from_fmt_uz8n_v(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, va_list *args) {
    return uwrite_fmt_uz8n_8_v(from, from_len, uwrite_uc8_to_uz8, &to, args);
}

size_t uz8_from_fmt_ucv8(UNULLABLE UOUT uc8_t *to, ucv8_t from, ...) {
    UZX_FROM_FMT_T(to, from, 8, ucv8);
}

size_t uz8_from_fmt_ucv8_v(UNULLABLE UOUT uc8_t *to, ucv8_t from, va_list *args) {
	return uz8_from_fmt_uz8n_v(to, UCV8_CEXPAND(from), args);
}

size_t uz8_from_fmt_uv8(UNULLABLE UOUT uc8_t *to, uv8_t from, ...) {
    UZX_FROM_FMT_T(to, from, 8, uv8);
}

size_t uz8_from_fmt_uv8_v(UNULLABLE UOUT uc8_t *to, uv8_t from, va_list *args) {
	return uz8_from_fmt_uz8n_v(to, UV8_CEXPAND(from), args);
}

size_t uz8_from_fmt_us8(UNULLABLE UOUT uc8_t *to, const us8_t *from, ...) {
    UZX_FROM_FMT_T(to, from, 8, us8);
}

size_t uz8_from_fmt_us8_v(UNULLABLE UOUT uc8_t *to, const us8_t *from, va_list *args) {
	return uz8_from_fmt_uz8n_v(to, US8_CEXPAND(from), args);
}

#define UZX_FROM_T_FMT(to, from, fmt, T, X)                       \
    return uwrite_##T##_##X(from, fmt, uwrite_uc##X##_to_uz##X, &to)

size_t uz32_from_float(UNULLABLE UOUT uc32_t *to, double from) {
    return uz32_from_float_fmt(to, from, &UFMT32_FLOAT_OUTPUT);
}

size_t uz32_from_float_fmt(UNULLABLE UOUT uc32_t *to, double from, const struct ufmt32_float_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, float, 32);
}

size_t uz16_from_float(UNULLABLE UOUT uc16_t *to, double from) {
    return uz16_from_float_fmt(to, from, &UFMT16_FLOAT_OUTPUT);
}

size_t uz16_from_float_fmt(UNULLABLE UOUT uc16_t *to, double from, const struct ufmt16_float_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, float, 16);
}

size_t uz8_from_float(UNULLABLE UOUT uc8_t *to, double from) {
	return uz8_from_float_fmt(to, from, &UFMT8_FLOAT_OUTPUT);
}

size_t uz8_from_float_fmt(UNULLABLE UOUT uc8_t *to, double from, const struct ufmt8_float_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, float, 8);
}

size_t uz32_from_int(UNULLABLE UOUT uc32_t *to, intmax_t from) {
	return uz32_from_int_fmt(to, from, &UFMT32_INT_OUTPUT_DEC);
}

size_t uz32_from_int_fmt(UNULLABLE UOUT uc32_t *to, intmax_t from, const struct ufmt32_int_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, int, 32);
}

size_t uz32_from_uint(UNULLABLE UOUT uc32_t *to, uintmax_t from) {
	return uz32_from_uint_fmt(to, from, &UFMT32_INT_OUTPUT_DEC);
}

size_t uz32_from_uint_fmt(UNULLABLE UOUT uc32_t *to, uintmax_t from, const struct ufmt32_int_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, uint, 32);
}

size_t uz16_from_int(UNULLABLE UOUT uc16_t *to, intmax_t from) {
	return uz16_from_int_fmt(to, from, &UFMT16_INT_OUTPUT_DEC);
}

size_t uz16_from_int_fmt(UNULLABLE UOUT uc16_t *to, intmax_t from, const struct ufmt16_int_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, int, 16);
}

size_t uz16_from_uint(UNULLABLE UOUT uc16_t *to, uintmax_t from) {
	return uz16_from_uint_fmt(to, from, &UFMT16_INT_OUTPUT_DEC);
}

size_t uz16_from_uint_fmt(UNULLABLE UOUT uc16_t *to, uintmax_t from, const struct ufmt16_int_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, uint, 16);
}

size_t uz8_from_int(UNULLABLE UOUT uc8_t *to, intmax_t from) {
	return uz8_from_int_fmt(to, from, &UFMT8_INT_OUTPUT_DEC);
}

size_t uz8_from_int_fmt(UNULLABLE UOUT uc8_t *to, intmax_t from, const struct ufmt8_int_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, int, 8);
}

size_t uz8_from_uint(UNULLABLE UOUT uc8_t *to, uintmax_t from) {
	return uz8_from_uint_fmt(to, from, &UFMT8_INT_OUTPUT_DEC);
}

size_t uz8_from_uint_fmt(UNULLABLE UOUT uc8_t *to, uintmax_t from, const struct ufmt8_int_output *fmt) {
    UZX_FROM_T_FMT(to, from, fmt, uint, 8);
}

#define UZX_FROM_CASE_BOOL(to, ca, from, X)                      \
    assert(ucase_valid_output(ca));                              \
                                                                 \
    return UCASE_UPPER == ca ? uz##X##_from_upper_bool(to, from) \
                             : uz##X##_from_lower_bool(to, from)

#define UZX_FROM_LOWER_BOOL(to, from, X)                                    \
    return uz##X##_from_ucv##X(to, from ? ucv##X("true") : ucv##X("false"))

#define UZX_FROM_UPPER_BOOL(to, from, X)                                    \
    return uz##X##_from_ucv##X(to, from ? ucv##X("TRUE") : ucv##X("FALSE"))

size_t uz32_from_bool(UNULLABLE UOUT uc32_t *to, bool from) {
    return uz32_from_lower_bool(to, from);
}

size_t uz32_from_case_bool(UNULLABLE UOUT uc32_t *to, ucase_t ca, bool from) {
    UZX_FROM_CASE_BOOL(to, ca, from, 32);
}

size_t uz32_from_lower_bool(UNULLABLE UOUT uc32_t *to, bool from) {
    UZX_FROM_LOWER_BOOL(to, from, 32);
}

size_t uz32_from_upper_bool(UNULLABLE UOUT uc32_t *to, bool from) {
    UZX_FROM_UPPER_BOOL(to, from, 32);
}

size_t uz16_from_bool(UNULLABLE UOUT uc16_t *to, bool from) {
    return uz16_from_lower_bool(to, from);
}

size_t uz16_from_case_bool(UNULLABLE UOUT uc16_t *to, ucase_t ca, bool from) {
    UZX_FROM_CASE_BOOL(to, ca, from, 16);
}

size_t uz16_from_lower_bool(UNULLABLE UOUT uc16_t *to, bool from) {
    UZX_FROM_LOWER_BOOL(to, from, 16);
}

size_t uz16_from_upper_bool(UNULLABLE UOUT uc16_t *to, bool from) {
    UZX_FROM_UPPER_BOOL(to, from, 16);
}

size_t uz8_from_bool(UNULLABLE UOUT uc8_t *to, bool from) {
    return uz8_from_lower_bool(to, from);
}

size_t uz8_from_case_bool(UNULLABLE UOUT uc8_t *to, ucase_t ca, bool from) {
    UZX_FROM_CASE_BOOL(to, ca, from, 8);
}

size_t uz8_from_lower_bool(UNULLABLE UOUT uc8_t *to, bool from) {
    UZX_FROM_LOWER_BOOL(to, from, 8);
}

size_t uz8_from_upper_bool(UNULLABLE UOUT uc8_t *to, bool from) {
    UZX_FROM_UPPER_BOOL(to, from, 8);
}

#define UZX_TO_BYTES(to, encoding, from, X)     \
    assert(uencoding_valid(encoding));          \
                                                \
    switch (encoding) {                         \
        case UENCODING_UTF32LE:                 \
            return uz32le_from_uz##X(to, from); \
                                                \
        case UENCODING_UTF32BE:                 \
            return uz32be_from_uz##X(to, from); \
                                                \
        case UENCODING_UTF16LE:                 \
            return uz16le_from_uz##X(to, from); \
                                                \
        case UENCODING_UTF16BE:                 \
            return uz16be_from_uz##X(to, from); \
                                                \
        case UENCODING_UTF8:                    \
            return uz8_from_uz##X(to, from);    \
                                                \
        default:                                \
            assert(false);                      \
            return 0;                           \
    }

#define UZXSE_TO_BYTES(to, encoding, from, X, S)      \
    assert(uencoding_valid(encoding));                \
                                                      \
    switch (encoding) {                               \
        case UENCODING_UTF32LE:                       \
            return uz32le_from_uz##X##S##e(to, from); \
                                                      \
        case UENCODING_UTF32BE:                       \
            return uz32be_from_uz##X##S##e(to, from); \
                                                      \
        case UENCODING_UTF16LE:                       \
            return uz16le_from_uz##X##S##e(to, from); \
                                                      \
        case UENCODING_UTF16BE:                       \
            return uz16be_from_uz##X##S##e(to, from); \
                                                      \
        case UENCODING_UTF8:                          \
            return uz8_from_uz##X##S##e(to, from);    \
                                                      \
        default:                                      \
            assert(false);                            \
            return 0;                                 \
    }

#define UZXN_TO_BYTES(to, encoding, from, from_len, X)       \
    assert(uencoding_valid(encoding));                       \
                                                             \
    switch (encoding) {                                      \
        case UENCODING_UTF32LE:                              \
            return uz32le_from_uz##X##n(to, from, from_len); \
                                                             \
        case UENCODING_UTF32BE:                              \
            return uz32be_from_uz##X##n(to, from, from_len); \
                                                             \
        case UENCODING_UTF16LE:                              \
            return uz16le_from_uz##X##n(to, from, from_len); \
                                                             \
        case UENCODING_UTF16BE:                              \
            return uz16be_from_uz##X##n(to, from, from_len); \
                                                             \
        case UENCODING_UTF8:                                 \
            return uz8_from_uz##X##n(to, from, from_len);    \
                                                             \
        default:                                             \
            assert(false);                                   \
            return 0;                                        \
    }

#define UZXSEN_TO_BYTES(to, encoding, from, from_len, X, S)      \
    assert(uencoding_valid(encoding));                           \
                                                                 \
    switch (encoding) {                                          \
        case UENCODING_UTF32LE:                                  \
            return uz32le_from_uz##X##S##en(to, from, from_len); \
                                                                 \
        case UENCODING_UTF32BE:                                  \
            return uz32be_from_uz##X##S##en(to, from, from_len); \
                                                                 \
        case UENCODING_UTF16LE:                                  \
            return uz16le_from_uz##X##S##en(to, from, from_len); \
                                                                 \
        case UENCODING_UTF16BE:                                  \
            return uz16be_from_uz##X##S##en(to, from, from_len); \
                                                                 \
        case UENCODING_UTF8:                                     \
            return uz8_from_uz##X##S##en(to, from, from_len);    \
                                                                 \
        default:                                                 \
            assert(false);                                       \
            return 0;                                            \
    }

size_t uz32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from) {
    UZX_TO_BYTES(to, encoding, from, 32);
}

size_t uz32le_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from) {
    UZXSE_TO_BYTES(to, encoding, from, 32, l);
}

size_t uz32be_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from) {
    UZXSE_TO_BYTES(to, encoding, from, 32, b);
}

size_t uz32n_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from, size_t from_len) {
    UZXN_TO_BYTES(to, encoding, from, from_len, 32);
}

size_t uz32len_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from, size_t from_len) {
    UZXSEN_TO_BYTES(to, encoding, from, from_len, 32, l);
}

size_t uz32ben_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from, size_t from_len) {
    UZXSEN_TO_BYTES(to, encoding, from, from_len, 32, b);
}

size_t uz16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from) {
    UZX_TO_BYTES(to, encoding, from, 16);
}

size_t uz16le_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from) {
    UZXSE_TO_BYTES(to, encoding, from, 16, l);
}

size_t uz16be_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from) {
    UZXSE_TO_BYTES(to, encoding, from, 16, b);
}

size_t uz16n_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from, size_t from_len) {
    UZXN_TO_BYTES(to, encoding, from, from_len, 16);
}

size_t uz16len_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from, size_t from_len) {
    UZXSEN_TO_BYTES(to, encoding, from, from_len, 16, l);
}

size_t uz16ben_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from, size_t from_len) {
    UZXSEN_TO_BYTES(to, encoding, from, from_len, 16, b);
}

size_t uz8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc8_t *from) {
    UZX_TO_BYTES(to, encoding, from, 8);
}

size_t uz8n_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc8_t *from, size_t from_len) {
    UZXN_TO_BYTES(to, encoding, from, from_len, 8);
}

#define UZX_LEN_N(cstr, n, X)            \
    assert(cstr);                        \
                                         \
    switch (n) {                         \
        case 8:                          \
            return uz##X##_len_8(cstr);  \
                                         \
        case 16:                         \
            return uz##X##_len_16(cstr); \
                                         \
        case 32:                         \
            return uz##X##_len_32(cstr); \
                                         \
        default:                         \
            assert(false);               \
            return 0;                    \
    }

#define UZXN_LEN_N(cstr, cstr_len, n, X)            \
    assert(cstr);                                   \
                                                    \
    switch (n) {                                    \
        case 8:                                     \
            return uz##X##n_len_8(cstr, cstr_len);  \
                                                    \
        case 16:                                    \
            return uz##X##n_len_16(cstr, cstr_len); \
                                                    \
        case 32:                                    \
            return uz##X##n_len_32(cstr, cstr_len); \
                                                    \
        default:                                    \
            assert(false);                          \
            return 0;                               \
    }

#define UZX_LEN_X(cstr, X)         \
    assert(cstr);                  \
                                   \
    const uc##X##_t *begin = cstr; \
                                   \
    while (*cstr)                  \
        ++cstr;                    \
                                   \
    return cstr - begin;

#define UZ32_LEN_X(cstr, X)           \
    assert(cstr);                     \
                                      \
    size_t len = 0;                   \
                                      \
    while (*cstr)                     \
        len += uc32_len_##X(*cstr++); \
                                      \
    return len

#define UZ32N_LEN_X(cstr, cstr_len, X) \
    assert(cstr);                      \
                                       \
    size_t len = 0;                    \
                                       \
    while (cstr_len--)                 \
        len += uc32_len_##X(*cstr++);  \
                                       \
    return len

#define UZXN_LEN_Y(cstr, cstr_len, X, Y) \
    assert(cstr);                        \
                                         \
    size_t len = 0;                      \
                                         \
    for (size_t i = 0; i < cstr_len;) {  \
        uc##X##_t c = cstr[i];           \
                                         \
        len += uc##X##_len_##Y(c);       \
        i   += uc##X##_len(c);           \
    }                                    \
                                         \
    return len

#define UZXSE_LEN_N(cstr, n, X, S)           \
    assert(cstr);                            \
                                             \
    switch (n) {                             \
        case 8:                              \
            return uz##X##S##e_len_8(cstr);  \
                                             \
        case 16:                             \
            return uz##X##S##e_len_16(cstr); \
                                             \
        case 32:                             \
            return uz##X##S##e_len_32(cstr); \
                                             \
        default:                             \
            assert(false);                   \
            return 0;                        \
    }

#define UZXSEN_LEN_N(cstr, cstr_len, n, X, S)           \
    assert(cstr);                                       \
                                                        \
    switch (n) {                                        \
        case 8:                                         \
            return uz##X##S##en_len_8(cstr, cstr_len);  \
                                                        \
        case 16:                                        \
            return uz##X##S##en_len_16(cstr, cstr_len); \
                                                        \
        case 32:                                        \
            return uz##X##S##en_len_32(cstr, cstr_len); \
                                                        \
        default:                                        \
            assert(false);                              \
            return 0;                                   \
    }

#define UZ32SE_LEN_X(cstr, X, S)            \
    assert(cstr);                           \
                                            \
    size_t len = 0;                         \
                                            \
    while (*cstr)                           \
        len += uc32##S##e_len_##X(*cstr++); \
                                            \
    return len

#define UZ32SEN_LEN_X(cstr, cstr_len, X, S) \
    assert(cstr);                           \
                                            \
    size_t len = 0;                         \
                                            \
    while (cstr_len--)                      \
        len += uc32##S##e_len_##X(*cstr++); \
                                            \
    return len

#define UZXSEN_LEN_Y(cstr, cstr_len, X, S, Y) \
    assert(cstr);                             \
                                              \
    size_t len = 0;                           \
                                              \
    for (size_t i = 0; i < cstr_len;) {       \
        uc##X##_t c = cstr[i];                \
                                              \
        len += uc##X##S##e_len_##Y(c);        \
        i   += uc##X##S##e_len(c);            \
    }                                         \
                                              \
    return len


size_t uz32_len(const uc32_t *cstr) {
    return uz32_len_32(cstr);
}

size_t uz32_len_n(const uc32_t *cstr, unsigned n) {
    UZX_LEN_N(cstr, n, 32);
}

size_t uz32_len_32(const uc32_t *cstr) {
    UZX_LEN_X(cstr, 32);
}

size_t uz32_len_16(const uc32_t *cstr) {
    UZ32_LEN_X(cstr, 16);
}

size_t uz32_len_8(const uc32_t *cstr) {
    UZ32_LEN_X(cstr, 8);
}

size_t uz32n_len(const uc32_t *cstr, size_t cstr_len) {
    return uz32n_len_32(cstr, cstr_len);
}

size_t uz32n_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n) {
    UZXN_LEN_N(cstr, cstr_len, n, 32);
}

size_t uz32n_len_32(const uc32_t *cstr, size_t cstr_len) {
    assert(cstr);
	return cstr_len;
}

size_t uz32n_len_16(const uc32_t *cstr, size_t cstr_len) {
    UZ32N_LEN_X(cstr, cstr_len, 16);
}

size_t uz32n_len_8(const uc32_t *cstr, size_t cstr_len) {
    UZ32N_LEN_X(cstr, cstr_len, 8);
}

size_t uz32le_len(const uc32_t *cstr) {
	return uz32le_len_32(cstr);
}

size_t uz32le_len_n(const uc32_t *cstr, unsigned n) {
    UZXSE_LEN_N(cstr, n, 32, l);
}

size_t uz32le_len_32(const uc32_t *cstr) {
    UZX_LEN_X(cstr, 32);
}

size_t uz32le_len_16(const uc32_t *cstr) {
    UZ32SE_LEN_X(cstr, 16, l);
}

size_t uz32le_len_8(const uc32_t *cstr) {
    UZ32SE_LEN_X(cstr, 8, l);
}

size_t uz32len_len(const uc32_t *cstr, size_t cstr_len) {
	return uz32len_len_32(cstr, cstr_len);
}

size_t uz32len_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n) {
    UZXSEN_LEN_N(cstr, cstr_len, n, 32, l);
}

size_t uz32len_len_32(const uc32_t *cstr, size_t cstr_len) {
    assert(cstr);
    return cstr_len;
}

size_t uz32len_len_16(const uc32_t *cstr, size_t cstr_len) {
    UZ32SEN_LEN_X(cstr, cstr_len, 16, l);
}

size_t uz32len_len_8(const uc32_t *cstr, size_t cstr_len) {
    UZ32SEN_LEN_X(cstr, cstr_len, 8, l);
}

size_t uz32be_len(const uc32_t *cstr) {
	return uz32be_len_32(cstr);
}

size_t uz32be_len_n(const uc32_t *cstr, unsigned n) {
    UZXSE_LEN_N(cstr, n, 32, b);
}

size_t uz32be_len_32(const uc32_t *cstr) {
    UZX_LEN_X(cstr, 32);
}

size_t uz32be_len_16(const uc32_t *cstr) {
    UZ32SE_LEN_X(cstr, 16, b);
}

size_t uz32be_len_8(const uc32_t *cstr) {
    UZ32SE_LEN_X(cstr, 8, b);
}

size_t uz32ben_len(const uc32_t *cstr, size_t cstr_len) {
	return uz32ben_len_32(cstr, cstr_len);
}

size_t uz32ben_len_n(const uc32_t *cstr, size_t cstr_len, unsigned n) {
    UZXSEN_LEN_N(cstr, cstr_len, n, 32, b);
}

size_t uz32ben_len_32(const uc32_t *cstr, size_t cstr_len) {
    assert(cstr);
    return cstr_len;
}

size_t uz32ben_len_16(const uc32_t *cstr, size_t cstr_len) {
    UZ32SEN_LEN_X(cstr, cstr_len, 16, b);
}

size_t uz32ben_len_8(const uc32_t *cstr, size_t cstr_len) {
    UZ32SEN_LEN_X(cstr, cstr_len, 8, b);
}

size_t uz16_len(const uc16_t *cstr) {
	return uz16_len_16(cstr);
}

size_t uz16_len_n(const uc16_t *cstr, unsigned n) {
    UZX_LEN_N(cstr, n, 16);
}

size_t uz16_len_32(const uc16_t *cstr) {
    return uz16n_len_32(cstr, uz16_len(cstr));
}

size_t uz16_len_16(const uc16_t *cstr) {
    UZX_LEN_X(cstr, 16);
}

size_t uz16_len_8(const uc16_t *cstr) {
	return uz16n_len_8(cstr, uz16_len(cstr));
}

size_t uz16n_len(const uc16_t *cstr, size_t cstr_len) {
	return uz16n_len_16(cstr, cstr_len);
}

size_t uz16n_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n) {
    UZXN_LEN_N(cstr, cstr_len, n, 16);
}

size_t uz16n_len_32(const uc16_t *cstr, size_t cstr_len) {
    UZXN_LEN_Y(cstr, cstr_len, 16, 32);
}

size_t uz16n_len_16(const uc16_t *cstr, size_t cstr_len) {
    assert(cstr);
	return cstr_len;
}

size_t uz16n_len_8(const uc16_t *cstr, size_t cstr_len) {
    UZXN_LEN_Y(cstr, cstr_len, 16, 8);
}

size_t uz16le_len(const uc16_t *cstr) {
	return uz16le_len_16(cstr);
}

size_t uz16le_len_n(const uc16_t *cstr, unsigned n) {
    UZXSE_LEN_N(cstr, n, 16, l);
}

size_t uz16le_len_32(const uc16_t *cstr) {
	return uz16len_len_32(cstr, uz16_len(cstr));
}

size_t uz16le_len_16(const uc16_t *cstr) {
    UZX_LEN_X(cstr, 16);
}

size_t uz16le_len_8(const uc16_t *cstr) {
	return uz16len_len_8(cstr, uz16_len(cstr));
}

size_t uz16len_len(const uc16_t *cstr, size_t cstr_len) {
	return uz16len_len_16(cstr, cstr_len);
}

size_t uz16len_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n) {
    UZXSEN_LEN_N(cstr, cstr_len, n, 16, l);
}

size_t uz16len_len_32(const uc16_t *cstr, size_t cstr_len) {
    UZXSEN_LEN_Y(cstr, cstr_len, 16, l, 32);
}

size_t uz16len_len_16(const uc16_t *cstr, size_t cstr_len) {
    assert(cstr);
    return cstr_len;
}

size_t uz16len_len_8(const uc16_t *cstr, size_t cstr_len) {
    UZXSEN_LEN_Y(cstr, cstr_len, 16, l, 8);
}

size_t uz16be_len(const uc16_t *cstr) {
	return uz16be_len_16(cstr);
}

size_t uz16be_len_n(const uc16_t *cstr, unsigned n) {
    UZXSE_LEN_N(cstr, n, 16, b);
}

size_t uz16be_len_32(const uc16_t *cstr) {
	return uz16ben_len_32(cstr, uz16_len(cstr));
}

size_t uz16be_len_16(const uc16_t *cstr) {
    UZX_LEN_X(cstr, 16);
}

size_t uz16be_len_8(const uc16_t *cstr) {
	return uz16ben_len_8(cstr, uz16_len(cstr));
}

size_t uz16ben_len(const uc16_t *cstr, size_t cstr_len) {
	return uz16ben_len_16(cstr, cstr_len);
}

size_t uz16ben_len_n(const uc16_t *cstr, size_t cstr_len, unsigned n) {
    UZXSEN_LEN_N(cstr, cstr_len, n, 16, b);
}

size_t uz16ben_len_32(const uc16_t *cstr, size_t cstr_len) {
    UZXSEN_LEN_Y(cstr, cstr_len, 16, b, 32);
}

size_t uz16ben_len_16(const uc16_t *cstr, size_t cstr_len) {
    assert(cstr);
    return cstr_len;
}

size_t uz16ben_len_8(const uc16_t *cstr, size_t cstr_len) {
    UZXSEN_LEN_Y(cstr, cstr_len, 16, b, 8);
}

size_t uz8_len(const uc8_t *cstr) {
    return uz8_len_8(cstr);
}

size_t uz8_len_n(const uc8_t *cstr, unsigned n) {
    UZX_LEN_N(cstr, n, 8);
}

size_t uz8_len_32(const uc8_t *cstr) {
	return uz8n_len_32(cstr, uz8_len(cstr));
}

size_t uz8_len_16(const uc8_t *cstr) {
	return uz8n_len_16(cstr, uz8_len(cstr));
}

size_t uz8_len_8(const uc8_t *cstr) {
    UZX_LEN_X(cstr, 8);
}

size_t uz8n_len(const uc8_t *cstr, size_t cstr_len) {
	return uz8n_len_8(cstr, cstr_len);
}

size_t uz8n_len_n(const uc8_t *cstr, size_t cstr_len, unsigned n) {
    UZXN_LEN_N(cstr, cstr_len, n, 8);
}

size_t uz8n_len_32(const uc8_t *cstr, size_t cstr_len) {
    UZXN_LEN_Y(cstr, cstr_len, 8, 32);
}

size_t uz8n_len_16(const uc8_t *cstr, size_t cstr_len) {
    UZXN_LEN_Y(cstr, cstr_len, 8, 16);
}

size_t uz8n_len_8(const uc8_t *cstr, size_t cstr_len) {
    assert(cstr);
	return cstr_len;
}

size_t uz8_trail(const uc8_t *cstr) {
    assert(cstr);

	const uc8_t *begin = cstr;

    while (*cstr && uc8_trail(*cstr))
        ++cstr;

    return cstr - begin;
}

size_t uz8n_trail(const uc8_t *cstr, size_t cstr_len) {
    assert(cstr);

	const uc8_t *begin = cstr;

    while (cstr_len-- && uc8_trail(*cstr))
		++cstr;

    return cstr - begin;
}

#define UZX_CMP_UCX(lhs, rhs)  \
    assert(lhs);               \
    return *lhs && *lhs == rhs

#define UZXN_CMP_UCX(lhs, lhs_len, rhs) \
    assert(lhs);                        \
    return 1 == lhs_len && *lhs == rhs

#define UZX_CMP_UZX(lhs, rhs)            \
    assert(lhs && rhs);                  \
                                         \
    for (; *lhs && *rhs; ++lhs, ++rhs) { \
        if (*lhs > *rhs)                 \
            return 1;                    \
                                         \
        if (*lhs < *rhs)                 \
            return -1;                   \
    }                                    \
                                         \
    if (*lhs && !*rhs)                   \
        return 1;                        \
                                         \
    if (!*lhs && *rhs)                   \
        return -1;                       \
                                         \
    return 0

#define UZX_CMP_UZXN(lhs, rhs, rhs_len)       \
    assert(lhs && rhs);                       \
                                              \
    for (; *lhs && rhs_len--; ++lhs, ++rhs) { \
        if (*lhs > *rhs)                      \
            return 1;                         \
                                              \
        if (*lhs < *rhs)                      \
            return -1;                        \
    }                                         \
                                              \
    if (*lhs && !rhs_len)                     \
        return 1;                             \
                                              \
    if (!*lhs && rhs_len)                     \
        return -1;                            \
                                              \
    return 0

#define UZXN_CMP_UZX(lhs, lhs_len, rhs)       \
    assert(lhs && rhs);                       \
                                              \
    for (; lhs_len-- && *rhs; ++lhs, ++rhs) { \
        if (*lhs > *rhs)                      \
            return 1;                         \
                                              \
        if (*lhs < *rhs)                      \
            return -1;                        \
    }                                         \
                                              \
    if (lhs_len && !*rhs)                     \
        return 1;                             \
                                              \
    if (!lhs_len && *rhs)                     \
        return -1;                            \
                                              \
    return 0

#define UZXN_CMP_UZXN(lhs, lhs_len, rhs, rhs_len)  \
    assert(lhs && rhs);                            \
                                                   \
    for (; lhs_len-- && rhs_len--; ++lhs, ++rhs) { \
        if (*lhs > *rhs)                           \
            return 1;                              \
                                                   \
        if (*lhs < *rhs)                           \
            return -1;                             \
    }                                              \
                                                   \
    if (lhs_len && !rhs_len)                       \
        return 1;                                  \
                                                   \
    if (!lhs_len && rhs_len)                       \
        return -1;                                 \
                                                   \
    return 0

int uz32_cmp_uc32(const uc32_t *lhs, uc32_t rhs) {
    UZX_CMP_UCX(lhs, rhs);
}

int uz32_cmp_uz32(const uc32_t *lhs, const uc32_t *rhs) {
    UZX_CMP_UZX(lhs, rhs);
}

int uz32_cmp_uz32n(const uc32_t *lhs, const uc32_t *rhs, size_t rhs_len) {
    UZX_CMP_UZXN(lhs, rhs, rhs_len);
}

int uz32_cmp_ucv32(const uc32_t *lhs, ucv32_t rhs) {
	return uz32_cmp_uz32n(lhs, UCV32_CEXPAND(rhs));
}

int uz32_cmp_uv32(const uc32_t *lhs, uv32_t rhs) {
	return uz32_cmp_uz32n(lhs, UV32_CEXPAND(rhs));
}

int uz32_cmp_us32(const uc32_t *lhs, const us32_t *rhs) {
	return uz32_cmp_uz32n(lhs, US32_CEXPAND(rhs));
}

int uz32n_cmp_uc32(const uc32_t *lhs, size_t lhs_len, uc32_t rhs) {
    UZXN_CMP_UCX(lhs, lhs_len, rhs);
}

int uz32n_cmp_uz32(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs) {
    UZXN_CMP_UZX(lhs, lhs_len, rhs);
}

int uz32n_cmp_uz32n(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len) {
    UZXN_CMP_UZXN(lhs, lhs_len, rhs, rhs_len);
}

int uz32n_cmp_ucv32(const uc32_t *lhs, size_t lhs_len, ucv32_t rhs) {
    return uz32n_cmp_uz32n(lhs, lhs_len, UCV32_CEXPAND(rhs));
}

int uz32n_cmp_uv32(const uc32_t *lhs, size_t lhs_len, uv32_t rhs) {
    return uz32n_cmp_uz32n(lhs, lhs_len, UV32_CEXPAND(rhs));
}

int uz32n_cmp_us32(const uc32_t *lhs, size_t lhs_len, const us32_t *rhs) {
    return uz32n_cmp_uz32n(lhs, lhs_len, US32_CEXPAND(rhs));
}

int uz16_cmp_uc16(const uc16_t *lhs, uc16_t rhs) {
    UZX_CMP_UCX(lhs, rhs);
}

int uz16_cmp_uz16(const uc16_t *lhs, const uc16_t *rhs) {
    UZX_CMP_UZX(lhs, rhs);
}

int uz16_cmp_uz16n(const uc16_t *lhs, const uc16_t *rhs, size_t rhs_len) {
    UZX_CMP_UZXN(lhs, rhs, rhs_len);
}

int uz16_cmp_ucv16(const uc16_t *lhs, ucv16_t rhs) {
	return uz16_cmp_uz16n(lhs, UCV16_CEXPAND(rhs));
}

int uz16_cmp_uv16(const uc16_t *lhs, uv16_t rhs) {
	return uz16_cmp_uz16n(lhs, UV16_CEXPAND(rhs));
}

int uz16_cmp_us16(const uc16_t *lhs, const us16_t *rhs) {
	return uz16_cmp_uz16n(lhs, US16_CEXPAND(rhs));
}

int uz16n_cmp_uc16(const uc16_t *lhs, size_t lhs_len, uc16_t rhs) {
    UZXN_CMP_UCX(lhs, lhs_len, rhs);
}

int uz16n_cmp_uz16(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs) {
    UZXN_CMP_UZX(lhs, lhs_len, rhs);
}

int uz16n_cmp_uz16n(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len) {
    UZXN_CMP_UZXN(lhs, lhs_len, rhs, rhs_len);
}

int uz16n_cmp_ucv16(const uc16_t *lhs, size_t lhs_len, ucv16_t rhs) {
	return uz16n_cmp_uz16n(lhs, lhs_len, UCV16_CEXPAND(rhs));
}

int uz16n_cmp_uv16(const uc16_t *lhs, size_t lhs_len, uv16_t rhs) {
	return uz16n_cmp_uz16n(lhs, lhs_len, UV16_CEXPAND(rhs));
}

int uz16n_cmp_us16(const uc16_t *lhs, size_t lhs_len, const us16_t *rhs) {
	return uz16n_cmp_uz16n(lhs, lhs_len, US16_CEXPAND(rhs));
}

int uz8_cmp_uc8(const uc8_t *lhs, uc8_t rhs) {
    UZX_CMP_UCX(lhs, rhs);
}

int uz8_cmp_uz8(const uc8_t *lhs, const uc8_t *rhs) {
    UZX_CMP_UZX(lhs, rhs);
}

int uz8_cmp_uz8n(const uc8_t *lhs, const uc8_t *rhs, size_t rhs_len) {
    UZX_CMP_UZXN(lhs, rhs, rhs_len);
}

int uz8_cmp_ucv8(const uc8_t *lhs, ucv8_t rhs) {
	return uz8_cmp_uz8n(lhs, UCV8_CEXPAND(rhs));
}

int uz8_cmp_uv8(const uc8_t *lhs, uv8_t rhs) {
	return uz8_cmp_uz8n(lhs, UV8_CEXPAND(rhs));
}

int uz8_cmp_us8(const uc8_t *lhs, const us8_t *rhs) {
	return uz8_cmp_uz8n(lhs, US8_CEXPAND(rhs));
}

int uz8n_cmp_uc8(const uc8_t *lhs, size_t lhs_len, uc8_t rhs) {
    UZXN_CMP_UCX(lhs, lhs_len, rhs);
}

int uz8n_cmp_uz8(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs) {
    UZXN_CMP_UZX(lhs, lhs_len, rhs);
}

int uz8n_cmp_uz8n(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len) {
    UZXN_CMP_UZXN(lhs, lhs_len, rhs, rhs_len);
}

int uz8n_cmp_ucv8(const uc8_t *lhs, size_t lhs_len, ucv8_t rhs) {
	return uz8n_cmp_uz8n(lhs, lhs_len, UCV8_CEXPAND(rhs));
}

int uz8n_cmp_uv8(const uc8_t *lhs, size_t lhs_len, uv8_t rhs) {
	return uz8n_cmp_uz8n(lhs, lhs_len, UV8_CEXPAND(rhs));
}

int uz8n_cmp_us8(const uc8_t *lhs, size_t lhs_len, const us8_t *rhs) {
	return uz8n_cmp_uz8n(lhs, lhs_len, US8_CEXPAND(rhs));
}

#define UZX_FILL_UCX(cstr, with) \
    assert(cstr);                \
                                 \
    while (*cstr)                \
        *cstr++ = with
 
#define UZX_FILL_UZX(cstr, with, X)                   \
    assert(cstr && with);                             \
                                                      \
    while (*cstr)                                     \
        for (const uc##X##_t *i = with; *cstr && *i;) \
            *cstr++ = *i++

#define UZX_FILL_UZXN(cstr, with, with_len)            \
    assert(cstr && with);                              \
                                                       \
    while (*cstr)                                      \
        for (size_t i = 0; *cstr && i < with_len; ++i) \
            *cstr++ = with[i]

#define UZXN_FILL_UCX(cstr, cstr_len, with) \
    assert(cstr);                           \
                                            \
    while (cstr_len--)                      \
        *cstr++ = with

#define UZXN_FILL_UZX(cstr, cstr_len, with, X)             \
    assert(cstr && with);                                  \
                                                           \
    while (cstr_len)                                       \
        for (const uc##X##_t *i = with; cstr_len-- && *i;) \
            *cstr++ = *i++
    
#define UZXN_FILL_UZXN(cstr, cstr_len, with, with_len)      \
    assert(cstr && with);                                   \
                                                            \
    while (cstr_len)                                        \
        for (size_t i = 0; cstr_len-- && i < with_len; ++i) \
            *cstr++ = with[i]

void uz32_fill_uc32(UINOUT uc32_t *cstr, uc32_t with) {
    UZX_FILL_UCX(cstr, with);
}

void uz32_fill_uz32(UINOUT uc32_t *cstr, const uc32_t *with) {
    UZX_FILL_UZX(cstr, with, 32);
}

void uz32_fill_uz32n(UINOUT uc32_t *cstr, const uc32_t *with, size_t with_len) {
    UZX_FILL_UZXN(cstr, with, with_len);
}

void uz32_fill_ucv32(UINOUT uc32_t *cstr, ucv32_t with) {
    uz32_fill_uz32n(cstr, UCV32_CEXPAND(with));
}

void uz32_fill_uv32(UINOUT uc32_t *cstr, uv32_t with) {
    uz32_fill_uz32n(cstr, UV32_CEXPAND(with));
}

void uz32_fill_us32(UINOUT uc32_t *cstr, const us32_t *with) {
    uz32_fill_uz32n(cstr, US32_CEXPAND(with));
}

void uz32n_fill_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t with) {
    UZXN_FILL_UCX(cstr, cstr_len, with);
}

void uz32n_fill_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *with) {
    UZXN_FILL_UZX(cstr, cstr_len, with, 32);
}

void uz32n_fill_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *with, size_t with_len) {
    UZXN_FILL_UZXN(cstr, cstr_len, with, with_len);
}

void uz32n_fill_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t with) {
    uz32n_fill_uz32n(cstr, cstr_len, UCV32_CEXPAND(with));
}

void uz32n_fill_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t with) {
    uz32n_fill_uz32n(cstr, cstr_len, UV32_CEXPAND(with));
}

void uz32n_fill_us32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *with) {
    uz32n_fill_uz32n(cstr, cstr_len, US32_CEXPAND(with));
}

void uz16_fill_uc16(UINOUT uc16_t *cstr, uc16_t with) {
    UZX_FILL_UCX(cstr, with);
}

void uz16_fill_uz16(UINOUT uc16_t *cstr, const uc16_t *with) {
    UZX_FILL_UZX(cstr, with, 16);
}

void uz16_fill_uz16n(UINOUT uc16_t *cstr, const uc16_t *with, size_t with_len) {
    UZX_FILL_UZXN(cstr, with, with_len);
}

void uz16_fill_ucv16(UINOUT uc16_t *cstr, ucv16_t with) {
    uz16_fill_uz16n(cstr, UCV16_CEXPAND(with));
}

void uz16_fill_uv16(UINOUT uc16_t *cstr, uv16_t with) {
    uz16_fill_uz16n(cstr, UV16_CEXPAND(with));
}

void uz16_fill_us16(UINOUT uc16_t *cstr, const us16_t *with) {
    uz16_fill_uz16n(cstr, US16_CEXPAND(with));
}

void uz16n_fill_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t with) {
    UZXN_FILL_UCX(cstr, cstr_len, with);
}

void uz16n_fill_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *with) {
    UZXN_FILL_UZX(cstr, cstr_len, with, 16);
}

void uz16n_fill_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *with, size_t with_len) {
    UZXN_FILL_UZXN(cstr, cstr_len, with, with_len);
}

void uz16n_fill_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t with) {
    uz16n_fill_uz16n(cstr, cstr_len, UCV16_CEXPAND(with));
}

void uz16n_fill_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t with) {
    uz16n_fill_uz16n(cstr, cstr_len, UV16_CEXPAND(with));
}

void uz16n_fill_us16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *with) {
    uz16n_fill_uz16n(cstr, cstr_len, US16_CEXPAND(with));
}

void uz8_fill_uc8(UINOUT uc8_t *cstr, uc8_t with) {
    UZX_FILL_UCX(cstr, with);
}

void uz8_fill_uz8(UINOUT uc8_t *cstr, const uc8_t *with) {
    UZX_FILL_UZX(cstr, with, 8);
}

void uz8_fill_uz8n(UINOUT uc8_t *cstr, const uc8_t *with, size_t with_len) {
    UZX_FILL_UZXN(cstr, with, with_len);
}

void uz8_fill_ucv8(UINOUT uc8_t *cstr, ucv8_t with) {
    uz8_fill_uz8n(cstr, UCV8_CEXPAND(with));
}

void uz8_fill_uv8(UINOUT uc8_t *cstr, uv8_t with) {
    uz8_fill_uz8n(cstr, UV8_CEXPAND(with));
}

void uz8_fill_us8(UINOUT uc8_t *cstr, const us8_t *with) {
    uz8_fill_uz8n(cstr, US8_CEXPAND(with));
}

void uz8n_fill_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t with) {
    UZXN_FILL_UCX(cstr, cstr_len, with);
}

void uz8n_fill_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *with) {
    UZXN_FILL_UZX(cstr, cstr_len, with, 8);
}

void uz8n_fill_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *with, size_t with_len) {
    UZXN_FILL_UZXN(cstr, cstr_len, with, with_len);
}

void uz8n_fill_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t with) {
    uz8n_fill_uz8n(cstr, cstr_len, UCV8_CEXPAND(with));
}

void uz8n_fill_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t with) {
    uz8n_fill_uz8n(cstr, cstr_len, UV8_CEXPAND(with));
}

void uz8n_fill_us8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *with) {
    uz8n_fill_uz8n(cstr, cstr_len, US8_CEXPAND(with));
}

#define UZX_MOVE(to, from, n)                  \
    assert(to && from);                        \
                                               \
    if (to < from)                             \
        while (n--)                            \
            *to++ = *from++;                   \
    else                                       \
        for (ptrdiff_t i = n - 1; i >= 0; --i) \
            to[i] = from[i]

void uz32_move(UOUT uc32_t *to, const uc32_t *from, size_t n) {
    UZX_MOVE(to, from, n);
}

void uz16_move(UOUT uc16_t *to, const uc16_t *from, size_t n) {
    UZX_MOVE(to, from, n);
}

void uz8_move(UOUT uc8_t *to, const uc8_t *from, size_t n) {
    UZX_MOVE(to, from, n);
}

#define UZX_WSPACE_LEN(cstr, X)     \
    assert(cstr);                   \
                                    \
    size_t len = 0;                 \
                                    \
    while (*cstr)                   \
        if (uc##X##_wspace(cstr++)) \
            ++len;                  \
        else                        \
            break;                  \
                                    \
    return len

#define UZXN_WSPACE_LEN(cstr, cstr_len, X) \
    assert(cstr);                          \
                                           \
    size_t len = 0;                        \
                                           \
    while (cstr_len--)                     \
        if (uc##X##_wspace(cstr++))        \
            ++len;                         \
        else                               \
            break;                         \
                                           \
    return len

size_t uz32_wspace_len(const uc32_t *cstr) {
    UZX_WSPACE_LEN(cstr, 32);
}

size_t uz32n_wspace_len(const uc32_t *cstr, size_t cstr_len) {
    UZXN_WSPACE_LEN(cstr, cstr_len, 32);
}

size_t uz16_wspace_len(const uc16_t *cstr) {
    UZX_WSPACE_LEN(cstr, 16);
}

size_t uz16n_wspace_len(const uc16_t *cstr, size_t cstr_len) {
    UZXN_WSPACE_LEN(cstr, cstr_len, 16);
}

size_t uz8_wspace_len(const uc8_t *cstr) {
    UZX_WSPACE_LEN(cstr, 8);
}

size_t uz8n_wspace_len(const uc8_t *cstr, size_t cstr_len) {
    UZXN_WSPACE_LEN(cstr, cstr_len, 8);
}

#define UZXN_RTRIM(cstr, cstr_len, X)           \
    assert(cstr);                               \
                                                \
    size_t wspace_len = 0;                      \
                                                \
    for (ptrdiff_t i = cstr_len - 1; i >= 0;) { \
        if (uc##X##_wspace(cstr + i))           \
            ++wspace_len;                       \
        else                                    \
            break;                              \
                                                \
        i -= uc##X##_len(cstr[i]);              \
    }                                           \
                                                \
	return cstr_len - wspace_len

#define UZXN_LTRIM(cstr, cstr_len, X)       \
    assert(cstr);                           \
                                            \
    size_t wspace_len = 0;                  \
                                            \
    for (size_t i = 0; i < cstr_len;) {     \
        if (uc##X##_wspace(cstr + i))       \
            ++wspace_len;                   \
        else                                \
            break;                          \
                                            \
        i += uc##X##_len(cstr[i]);          \
    }                                       \
                                            \
    size_t new_len = cstr_len - wspace_len; \
                                            \
    for (size_t i = 0; i < new_len; ++i)    \
        cstr[i] = cstr[i + wspace_len];     \
                                            \
    return new_len;

size_t uz32_trim(uc32_t *cstr) {
	return uz32n_trim(cstr, uz32_len(cstr));
}

size_t uz32_ltrim(UINOUT uc32_t *cstr) {
	return uz32n_ltrim(cstr, uz32_len(cstr));
}

size_t uz32_rtrim(const uc32_t *cstr) {
	return uz32n_rtrim(cstr, uz32_len(cstr));
}

size_t uz32n_trim(uc32_t *cstr, size_t cstr_len) {
	return uz32n_ltrim(cstr, uz32n_rtrim(cstr, cstr_len));
}

size_t uz32n_ltrim(UINOUT uc32_t *cstr, size_t cstr_len) {
    UZXN_LTRIM(cstr, cstr_len, 32);
}

size_t uz32n_rtrim(const uc32_t *cstr, size_t cstr_len) {
    UZXN_RTRIM(cstr, cstr_len, 32);
}

size_t uz16_trim(uc16_t *cstr) {
	return uz16n_trim(cstr, uz16_len(cstr));
}

size_t uz16_ltrim(UINOUT uc16_t *cstr) {
	return uz16n_ltrim(cstr, uz16_len(cstr));
}

size_t uz16_rtrim(const uc16_t *cstr) {
	return uz16n_rtrim(cstr, uz16_len(cstr));
}

size_t uz16n_trim(uc16_t *cstr, size_t cstr_len) {
	return uz16n_ltrim(cstr, uz16n_rtrim(cstr, cstr_len));
}

size_t uz16n_ltrim(UINOUT uc16_t *cstr, size_t cstr_len) {
    UZXN_LTRIM(cstr, cstr_len, 16);
}

size_t uz16n_rtrim(const uc16_t *cstr, size_t cstr_len) {
    UZXN_RTRIM(cstr, cstr_len, 16);
}

size_t uz8_trim(uc8_t *cstr) {
	return uz8n_trim(cstr, uz8_len(cstr));
}

size_t uz8_ltrim(UINOUT uc8_t *cstr) {
	return uz8n_ltrim(cstr, uz8_len(cstr));
}

size_t uz8_rtrim(const uc8_t *cstr) {
	return uz8n_rtrim(cstr, uz8_len(cstr));
}

size_t uz8n_trim(uc8_t *cstr, size_t cstr_len) {
	return uz8n_ltrim(cstr, uz8n_rtrim(cstr, cstr_len));
}

size_t uz8n_ltrim(UINOUT uc8_t *cstr, size_t cstr_len) {
    UZXN_LTRIM(cstr, cstr_len, 8);
}

size_t uz8n_rtrim(const uc8_t *cstr, size_t cstr_len) {
    UZXN_RTRIM(cstr, cstr_len, 8);
}

#define UZX_TO_CASE(to, from, ca, X)           \
    assert(to && ucase_valid(ca));     \
                                               \
    switch (ca) {                              \
        case UCASE_LOWER:                      \
            return uz##X##_to_lower(to, from); \
                                               \
        case UCASE_UPPER:                      \
            return uz##X##_to_upper(to, from); \
                                               \
        default:                               \
            uz##X##_from_uz##X(to, from);      \
    }

#define UZXN_TO_CASE(to, from, from_len, ca, X)           \
    assert(to && ucase_valid(ca));                \
                                                          \
    switch (ca) {                                         \
        case UCASE_LOWER:                                 \
            return uz##X##n_to_lower(to, from, from_len); \
                                                          \
        case UCASE_UPPER:                                 \
            return uz##X##n_to_upper(to, from, from_len); \
                                                          \
        default:                                          \
            uz##X##_from_uz##X##n(to, from, from_len);    \
    }

#define UZ32_TO_C(to, from, C)             \
    assert(to && from);                    \
                                           \
    while (*from)                          \
        *to++ = uc32_to_##C##_imm(*from++)

#define UZ32N_TO_C(to, from, from_len, C)  \
    assert(to && from);                    \
                                           \
    while (from_len--)                     \
        *to++ = uc32_to_##C##_imm(*from++)

#define UZ16N_TO_C(to, from, from_len, C) \
    assert(to && from);                   \
                                          \
    for (size_t i = 0; i < from_len;) {   \
        to += uc16_to_##C(to, from + i);  \
        i  += uc16_len(from[i]);          \
    }

#define UZ8N_TO_C_E(to, from, from_len, error, C)             \
    assert(from);                                             \
                                                              \
    if (!to)                                                  \
        return uz8n_lower_len(from, from_len);                \
                                                              \
    /* String copying is needed because in contrast to     */ \
    /* UTF-16 and UTF-32 strings UTF-8 strings can         */ \
    /* drastically change thair length after case change   */ \
    /* and if <to> and <from> overlap <to> will be invalid */ \
                                                              \
    uc8_t *from_copy = ualloc(from_len * sizeof(uc8_t));      \
                                                              \
    if (!from_copy) {                                         \
        if (error)                                            \
            *error = true;                                    \
                                                              \
        return 0;                                             \
    }                                                         \
                                                              \
    uz8_from_uz8n(from_copy, from, from_len);                 \
                                                              \
    size_t len = uz8n_to_##C##_copy(to, from_copy, from_len); \
                                                              \
    ufree(from_copy);                                         \
                                                              \
	return len

#define UZ8N_TO_C_COPY(to, from, from_len, C)  \
    assert(to && from);                        \
                                               \
    size_t len = 0;                            \
                                               \
    for (size_t i = 0; i < from_len;) {        \
        len += uc8_to_##C(to + len, from + i); \
        i   += uc8_len(from[i]);               \
    }                                          \
                                               \
    return len;
    
#define UZ8N_C_LEN(from, from_len, C)   \
    assert(from);                       \
                                        \
    size_t len = 0;                     \
                                        \
    for (size_t i = 0; i < from_len;) { \
        len += uc8_##C##_len(from + i); \
        i   += uc8_len(from[i]);        \
    }                                   \
                                        \
    return len

void uz32_to_case(UOUT uc32_t *to, const uc32_t *from, ucase_t ca) {
    UZX_TO_CASE(to, from, ca, 32);
}

void uz32_to_lower(UOUT uc32_t *to, const uc32_t *from) {
    UZ32_TO_C(to, from, lower);
}

void uz32_to_upper(UOUT uc32_t *to, const uc32_t *from) {
    UZ32_TO_C(to, from, upper);
}

void uz32n_to_case(UOUT uc32_t *to, const uc32_t *from, size_t from_len, ucase_t ca) {
    UZXN_TO_CASE(to, from, from_len, ca, 32);
}

void uz32n_to_lower(UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZ32N_TO_C(to, from, from_len, lower);
}

void uz32n_to_upper(UOUT uc32_t *to, const uc32_t *from, size_t from_len) {
    UZ32N_TO_C(to, from, from_len, upper);
}

void uz16_to_case(UOUT uc16_t *to, const uc16_t *from, ucase_t ca) {
    UZX_TO_CASE(to, from, ca, 16);
}

void uz16_to_lower(UOUT uc16_t *to, const uc16_t *from) {
    return uz16n_to_lower(to, from, uz16_len(from));
}

void uz16_to_upper(UOUT uc16_t *to, const uc16_t *from) {
    return uz16n_to_upper(to, from, uz16_len(from));
}

void uz16n_to_case(UOUT uc16_t *to, const uc16_t *from, size_t from_len, ucase_t ca) {
    UZXN_TO_CASE(to, from, from_len, ca, 16);
}

void uz16n_to_lower(UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZ16N_TO_C(to, from, from_len, lower);
}

void uz16n_to_upper(UOUT uc16_t *to, const uc16_t *from, size_t from_len) {
    UZ16N_TO_C(to, from, from_len, upper);
}

size_t uz8_to_case(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca) {
    return uz8_to_case_e(to, from, ca, NULL);
}

size_t uz8_to_case_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca, bool *error) {
    assert(ucase_valid(ca));

    switch (ca) {
        case UCASE_LOWER:
            return uz8_to_lower_e(to, from, error);

        case UCASE_UPPER:
            return uz8_to_upper_e(to, from, error);

        default:
            return uz8_from_uz8(to, from);
    }
}

size_t uz8_to_lower(UNULLABLE UOUT uc8_t *to, const uc8_t *from) {
	return uz8_to_lower_e(to, from, NULL);
}

size_t uz8_to_lower_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, bool *error) {
    return uz8n_to_lower_e(to, from, uz8_len(from), error);
}

size_t uz8_to_upper(UNULLABLE UOUT uc8_t *to, const uc8_t *from) {
	return uz8_to_upper_e(to, from, NULL);
}

size_t uz8_to_upper_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, bool *error) {
    return uz8n_to_upper_e(to, from, uz8_len(from), error);
}

size_t uz8n_to_case(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ucase_t ca) {
	return uz8n_to_case_e(to, from, from_len, ca, NULL);
}

size_t uz8n_to_case_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ucase_t ca, bool *error) {
    assert(ucase_valid(ca));

    switch (ca) {
        case UCASE_LOWER:
            return uz8n_to_lower_e(to, from, from_len, error);

        case UCASE_UPPER:
            return uz8n_to_upper_e(to, from, from_len, error);

        default:
            return uz8_from_uz8n(to, from, from_len);
    }
}

size_t uz8n_to_lower(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len) {
	return uz8n_to_lower_e(to, from, from_len, NULL);
}

size_t uz8n_to_lower_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, bool *error) {
    UZ8N_TO_C_E(to, from, from_len, error, lower);
}

size_t uz8n_to_upper(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len) {
	return uz8n_to_upper_e(to, from, from_len, NULL);
}

size_t uz8n_to_upper_e(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, bool *error) {
    UZ8N_TO_C_E(to, from, from_len, error, upper);
}

size_t uz8_to_case_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca) {
    assert(ucase_valid(ca));

    switch (ca) {
        case UCASE_LOWER:
            return uz8_to_lower_copy(to, from);

        case UCASE_UPPER:
            return uz8_to_upper_copy(to, from);

        default:
            return uz8_from_uz8(to, from);
    }
}

size_t uz8_to_lower_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from) {
	return uz8n_to_lower_copy(to, from, uz8_len(from));
}

size_t uz8_to_upper_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from) {
	return uz8n_to_upper_copy(to, from, uz8_len(from));
}

size_t uz8n_to_case_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len, ucase_t ca) {
    assert(ucase_valid(ca));

    switch (ca) {
        case UCASE_LOWER:
            return uz8n_to_lower_copy(to, from, from_len);

        case UCASE_UPPER:
            return uz8n_to_upper_copy(to, from, from_len);

        default:
            return uz8_from_uz8n(to, from, from_len);
    }
}

size_t uz8n_to_lower_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len) {
    UZ8N_TO_C_COPY(to, from, from_len, lower);
}

size_t uz8n_to_upper_copy(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len) {
    UZ8N_TO_C_COPY(to, from, from_len, upper);
}

size_t uz8_case_len(const uc8_t *from, ucase_t ca) {
    assert(ucase_valid(ca));

    switch (ca) {
        case UCASE_LOWER:
            return uz8_lower_len(from);

        case UCASE_UPPER:
            return uz8_upper_len(from);

        default:
            return uz8_len(from);
    }
}

size_t uz8_lower_len(const uc8_t *from) {
	return uz8n_lower_len(from, uz8_len(from));
}

size_t uz8_upper_len(const uc8_t *from) {
	return uz8n_upper_len(from, uz8_len(from));
}

size_t uz8n_case_len(const uc8_t *from, size_t from_len, ucase_t ca) {
    assert(ucase_valid(ca));

    switch (ca) {
        case UCASE_LOWER:
            return uz8n_lower_len(from, from_len);

        case UCASE_UPPER:
            return uz8n_upper_len(from, from_len);

        default:
            return from_len;
    }
}

size_t uz8n_lower_len(const uc8_t *from, size_t from_len) {
    UZ8N_C_LEN(from, from_len, lower);
}

size_t uz8n_upper_len(const uc8_t *from, size_t from_len) {
    UZ8N_C_LEN(from, from_len, upper);
}

void uz32_reverse(uc32_t *cstr) {
    return uz32n_reverse(cstr, uz32_len(cstr));
}

void uz32n_reverse(uc32_t *cstr, size_t cstr_len) {
    assert(cstr);

    for (size_t i = 0, j = cstr_len - 1; i < cstr_len / 2; ++i, --j) {
        uc32_t tmp = cstr[i];

        cstr[i] = cstr[j];
        cstr[j] = tmp;
    }
}

void uz16_reverse(uc16_t *cstr) {
    return uz16n_reverse(cstr, uz16_len(cstr));
}

void uz16n_reverse(uc16_t *cstr, size_t cstr_len) {
    assert(cstr);

    // Reverse words

    for (size_t i = 0, j = cstr_len - 1; i < cstr_len / 2; ++i, --j) {
        uc16_t tmp = cstr[i];

        cstr[i] = cstr[j];
        cstr[j] = tmp;
    }

    // Fix surrogate pairs

    for (size_t i = 0; i < cstr_len;) {
        uc16_t c = cstr[i];

        if (!uc16_hsrgt(c)) {
            ++i;
            continue;
        }

        size_t j = i + 1;

        cstr[i] = cstr[j];
        cstr[j] = c;

        i += 2;
    }
}

void uz8_reverse(uc8_t *cstr) {
    return uz8n_reverse(cstr, uz8_len(cstr));
}

void uz8n_reverse(uc8_t *cstr, size_t cstr_len) {
    assert(cstr);

    // Reverse bytes

    for (size_t i = 0, j = cstr_len - 1; i < cstr_len / 2; ++i, --j) {
        uc8_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }

    // Fix sequences

    for (size_t i = 0; i < cstr_len;) {
        unsigned trail = uz8n_trail(cstr + i, cstr_len - i);
        unsigned clen  = trail + 1;

        for (size_t j = i, k = j + trail, mid = j + clen / 2; j < mid; ++j, --k) {
            uc8_t tmp = cstr[j];

            cstr[j] = cstr[k];
            cstr[k] = tmp;
        }
    
        i += clen;
    }
}

#define UZX_ADVANCE(cstr, n)     \
    assert(cstr);                \
                                 \
    while (n--)                  \
        cstr += uc16_len(*cstr); \
                                 \
	return cstr

uc32_t *uz32_advance(uc32_t *cstr, size_t n) {
	return (uc32_t *) uz32_cadvance(cstr, n);
}

const uc32_t *uz32_cadvance(const uc32_t *cstr, size_t n) {
    assert(cstr);
	return cstr + n;
}

uc16_t *uz16_advance(uc16_t *cstr, size_t n) {
	return (uc16_t *) uz16_cadvance(cstr, n);
}

const uc16_t *uz16_cadvance(const uc16_t *cstr, size_t n) {
    UZX_ADVANCE(cstr, n);
}

uc8_t *uz8_advance(uc8_t *cstr, size_t n) {
	return (uc8_t *) uz8_cadvance(cstr, n);
}

const uc8_t *uz8_cadvance(const uc8_t *cstr, size_t n) {
    UZX_ADVANCE(cstr, n);
}

uc32_t *uz32_retreat(uc32_t *cstr, size_t n) {
	return (uc32_t *) uz32_cretreat(cstr, n);
}

const uc32_t *uz32_cretreat(const uc32_t *cstr, size_t n) {
    assert(cstr);
	return cstr - n;
}

uc16_t *uz16_retreat(uc16_t *cstr, size_t n) {
	return (uc16_t *) uz16_cretreat(cstr, n);
}

const uc16_t *uz16_cretreat(const uc16_t *cstr, size_t n) {
    assert(cstr);

    while (n--)
        cstr -= uc16_hsrgt(cstr[-1]) ? 2 : 1;

	return cstr;
}

uc8_t *uz8_retreat(uc8_t *cstr, size_t n) {
	return (uc8_t *) uz8_cretreat(cstr, n);
}

const uc8_t *uz8_cretreat(const uc8_t *cstr, size_t n) {
    assert(cstr);

    while (n--)
        while (uc8_trail(*--cstr));

	return cstr;
}

#define UZX_NEW_SPLIT_UCX_E(cstr, sep, array, error, X)         \
    size_t count = uz##X##_split_uc##X(cstr, sep, NULL, 0);     \
                                                                \
    if (!count)                                                 \
        return 0;                                               \
                                                                \
    if (!array)                                                 \
        return count;                                           \
                                                                \
    uv##X##_t *inner_array = ualloc(count * sizeof(uv##X##_t)); \
                                                                \
    if (!inner_array) {                                         \
        if (error)                                              \
            *error = true;                                      \
                                                                \
        return count;                                           \
    }                                                           \
                                                                \
    *array = inner_array;                                       \
                                                                \
    return uz##X##_split_uc##X(cstr, sep, inner_array, count)

#define UZX_SPLIT_UCX(cstr, sep, array, array_len, X)                                  \
    assert(cstr);                                                                      \
                                                                                       \
    if (!array) {                                                                      \
        size_t count = 0;                                                              \
                                                                                       \
        while (*cstr)                                                                  \
            if (*cstr++ == sep)                                                        \
                ++count;                                                               \
                                                                                       \
        return ++count;                                                                \
    }                                                                                  \
                                                                                       \
    size_t count    = 0;                                                               \
    size_t prev_pos = 0;                                                               \
    size_t i        = 0;                                                               \
                                                                                       \
    for (; cstr[i]; ++i)                                                               \
        if (cstr[i] == sep) {                                                          \
            if (count < array_len)                                                     \
                array[count++] = uv##X##_from_uz##X##n(cstr + prev_pos, i - prev_pos); \
                                                                                       \
            prev_pos = i + 1;                                                          \
        }                                                                              \
                                                                                       \
    if (count < array_len)                                                             \
        array[count++] = uv##X##_from_uz##X##n(cstr + prev_pos, i - prev_pos);         \
                                                                                       \
	return count

#define UZX_NEW_SPLIT_UZX_E(cstr, sep, array, error, X)         \
    size_t count = uz##X##_split_uz##X(cstr, sep, NULL, 0);     \
                                                                \
    if (!count)                                                 \
        return 0;                                               \
                                                                \
    if (!array)                                                 \
        return count;                                           \
                                                                \
    uv##X##_t *inner_array = ualloc(count * sizeof(uv##X##_t)); \
                                                                \
    if (!inner_array) {                                         \
        if (error)                                              \
            *error = true;                                      \
                                                                \
        return count;                                           \
    }                                                           \
                                                                \
    *array = inner_array;                                       \
                                                                \
    return uz##X##_split_uz##X(cstr, sep, inner_array, count)

#define UZX_NEW_SPLIT_UZXN_E(cstr, sep, sep_len, array, error, X)         \
    size_t count = uz##X##_split_uz##X##n(cstr, sep, sep_len, NULL, 0);   \
                                                                          \
    if (!count)                                                           \
        return 0;                                                         \
                                                                          \
    if (!array)                                                           \
        return count;                                                     \
                                                                          \
    uv##X##_t *inner_array = ualloc(count * sizeof(uv##X##_t));           \
                                                                          \
    if (!inner_array) {                                                   \
        if (error)                                                        \
            *error = true;                                                \
                                                                          \
        return count;                                                     \
    }                                                                     \
                                                                          \
    *array = inner_array;                                                 \
                                                                          \
    return uz##X##_split_uz##X##n(cstr, sep, sep_len, inner_array, count)

#define UZXN_NEW_SPLIT_UCX_E(cstr, cstr_len, sep, array, error, X)       \
    size_t count = uz##X##n_split_uc##X(cstr, cstr_len, sep, NULL, 0);   \
                                                                         \
    if (!count)                                                          \
        return 0;                                                        \
                                                                         \
    if (!array)                                                          \
        return count;                                                    \
                                                                         \
    uv##X##_t *inner_array = ualloc(count * sizeof(uv##X##_t));          \
                                                                         \
    if (!inner_array) {                                                  \
        if (error)                                                       \
            *error = true;                                               \
                                                                         \
        return count;                                                    \
    }                                                                    \
                                                                         \
    *array = inner_array;                                                \
                                                                         \
    return uz##X##n_split_uc##X(cstr, cstr_len, sep, inner_array, count)

#define UZXN_SPLIT_UCX(cstr, cstr_len, sep, array, array_len, X)                                  \
    assert(cstr);                                                                      \
                                                                                       \
    if (!array) {                                                                      \
        size_t count = 0;                                                              \
                                                                                       \
        while (cstr_len--)                                                             \
            if (*cstr++ == sep)                                                        \
                ++count;                                                               \
                                                                                       \
        return ++count;                                                                \
    }                                                                                  \
                                                                                       \
    size_t count    = 0;                                                               \
    size_t prev_pos = 0;                                                               \
                                                                                       \
    for (size_t i = 0; i < cstr_len; ++i)                                              \
        if (cstr[i] == sep) {                                                          \
            if (count < array_len)                                                     \
                array[count++] = uv##X##_from_uz##X##n(cstr + prev_pos, i - prev_pos); \
                                                                                       \
            prev_pos       = i + 1;                                                    \
        }                                                                              \
                                                                                       \
    if (count < array_len)                                                             \
        array[count++] = uv##X##_from_uz##X##n(cstr + prev_pos, cstr_len - prev_pos);  \
                                                                                       \
	return count

#define UZXN_NEW_SPLIT_UZX_E(cstr, cstr_len, sep, array, error, X)       \
    size_t count = uz##X##n_split_uz##X(cstr, cstr_len, sep, NULL, 0);   \
                                                                         \
    if (!count)                                                          \
        return 0;                                                        \
                                                                         \
    if (!array)                                                          \
        return count;                                                    \
                                                                         \
    uv##X##_t *inner_array = ualloc(count * sizeof(uv##X##_t));          \
                                                                         \
    if (!inner_array) {                                                  \
        if (error)                                                       \
            *error = true;                                               \
                                                                         \
        return count;                                                    \
    }                                                                    \
                                                                         \
    *array = inner_array;                                                \
                                                                         \
    return uz##X##n_split_uz##X(cstr, cstr_len, sep, inner_array, count)

#define UZXN_NEW_SPLIT_UZXN_E(cstr, cstr_len, sep, sep_len, array, error, X)         \
    size_t count = uz##X##n_split_uz##X##n(cstr, cstr_len, sep, sep_len, NULL, 0);   \
                                                                                     \
    if (!count)                                                                      \
        return 0;                                                                    \
                                                                                     \
    if (!array)                                                                      \
        return count;                                                                \
                                                                                     \
    uv##X##_t *inner_array = ualloc(count * sizeof(uv##X##_t));                      \
                                                                                     \
    if (!inner_array) {                                                              \
        if (error)                                                                   \
            *error = true;                                                           \
                                                                                     \
        return count;                                                                \
    }                                                                                \
                                                                                     \
    *array = inner_array;                                                            \
                                                                                     \
    return uz##X##n_split_uz##X##n(cstr, cstr_len, sep, sep_len, inner_array, count)
    
#define UZXN_SPLIT_UZXN(cstr, cstr_len, sep, sep_len, array, array_len, X)                   \
    assert(cstr && sep);                                                                     \
                                                                                             \
    size_t    count    = 0;                                                                  \
    ptrdiff_t prev_pos = 0;                                                                  \
                                                                                             \
    while (prev_pos < cstr_len) {                                                            \
        ptrdiff_t pos = uz##X##n_find_uz##X##n_from(cstr, cstr_len, sep, sep_len, prev_pos); \
                                                                                             \
        if (pos < 0)                                                                         \
            break;                                                                           \
                                                                                             \
        if (array && count < array_len)                                                      \
            array[count] = uv##X##_from_uz##X##n(cstr + prev_pos, pos - prev_pos);           \
                                                                                             \
        ++count;                                                                             \
                                                                                             \
        prev_pos = pos + sep_len;                                                            \
    }                                                                                        \
                                                                                             \
    if (array && count < array_len)                                                          \
        array[count] = uv##X##_from_uz##X##n(cstr + prev_pos, cstr_len - prev_pos);          \
                                                                                             \
    return ++count

size_t uz32_new_csplit_uc32(const uc32_t *cstr, uc32_t sep, UNULLABLE ucv32_t **array) {
    return uz32_new_csplit_uc32_e(cstr, sep, array, NULL);
}

size_t uz32_new_csplit_uc32_e(const uc32_t *cstr, uc32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32_new_split_uc32_e((uc32_t *) cstr, sep, (uv32_t **) array, error);
}

size_t uz32_csplit_uc32(const uc32_t *cstr, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32_split_uc32((uc32_t *) cstr, sep, (uv32_t *) array, array_len);
}

size_t uz32_new_csplit_uz32(const uc32_t *cstr, const uc32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32_new_csplit_uz32_e(cstr, sep, array, NULL);
}

size_t uz32_new_csplit_uz32_e(const uc32_t *cstr, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32_new_split_uz32_e((uc32_t *) cstr, sep, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32(const uc32_t *cstr, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32_split_uz32((uc32_t *) cstr, sep, (uv32_t *) array, array_len);
}

size_t uz32_new_csplit_uz32n(const uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array) {
    return uz32_new_csplit_uz32n_e(cstr, sep, sep_len, array, NULL);
}

size_t uz32_new_csplit_uz32n_e(const uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error) {
    return uz32_new_split_uz32n_e((uc32_t *) cstr, sep, sep_len, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32n(const uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32_split_uz32n((uc32_t *) cstr, sep, sep_len, (uv32_t *) array, array_len);
}

size_t uz32_new_csplit_ucv32(const uc32_t *cstr, ucv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32_new_csplit_uz32n(cstr, UCV32_CEXPAND(sep), array);
}

size_t uz32_new_csplit_ucv32_e(const uc32_t *cstr, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32_new_csplit_uz32n_e(cstr, UCV32_CEXPAND(sep), array, error);
}

size_t uz32_csplit_ucv32(const uc32_t *cstr, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32_csplit_uz32n(cstr, UCV32_CEXPAND(sep), array, array_len);
}

size_t uz32_new_csplit_uv32(const uc32_t *cstr, uv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32_new_csplit_uz32n(cstr, UV32_CEXPAND(sep), array);
}

size_t uz32_new_csplit_uv32_e(const uc32_t *cstr, uv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32_new_csplit_uz32n_e(cstr, UV32_CEXPAND(sep), array, error);
}

size_t uz32_csplit_uv32(const uc32_t *cstr, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32_csplit_uz32n(cstr, UV32_CEXPAND(sep), array, array_len);
}

size_t uz32_new_csplit_us32(const uc32_t *cstr, const us32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32_new_csplit_uz32n(cstr, US32_CEXPAND(sep), array);
}

size_t uz32_new_csplit_us32_e(const uc32_t *cstr, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32_new_csplit_uz32n_e(cstr, US32_CEXPAND(sep), array, error);
}

size_t uz32_csplit_us32(const uc32_t *cstr, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32_csplit_uz32n(cstr, US32_CEXPAND(sep), array, array_len);
}

size_t uz32_new_split_uc32(uc32_t *cstr, uc32_t sep, UNULLABLE uv32_t **array) {
    return uz32_new_split_uc32_e(cstr, sep, array, NULL);
}

size_t uz32_new_split_uc32_e(uc32_t *cstr, uc32_t sep, UNULLABLE uv32_t **array, bool *error) {
    UZX_NEW_SPLIT_UCX_E(cstr, sep, array, error, 32);
}

size_t uz32_split_uc32(uc32_t *cstr, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
    UZX_SPLIT_UCX(cstr, sep, array, array_len, 32);
}

size_t uz32_new_split_uz32(uc32_t *cstr, const uc32_t *sep, UNULLABLE uv32_t **array) {
    return uz32_new_split_uz32_e(cstr, sep, array, NULL);
}

size_t uz32_new_split_uz32_e(uc32_t *cstr, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error) {
    UZX_NEW_SPLIT_UZX_E(cstr, sep, array, error, 32);
}

size_t uz32_split_uz32(uc32_t *cstr, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32_split_uz32n(cstr, sep, uz32_len(sep), array, array_len);
}

size_t uz32_new_split_uz32n(uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array) {
    return uz32_new_split_uz32n_e(cstr, sep, sep_len, array, NULL);
}

size_t uz32_new_split_uz32n_e(uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error) {
    UZX_NEW_SPLIT_UZXN_E(cstr, sep, sep_len, array, error, 32);
}

size_t uz32_split_uz32n(uc32_t *cstr, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(cstr, uz32_len(cstr), sep, sep_len, array, array_len);
}

size_t uz32_new_split_ucv32(uc32_t *cstr, ucv32_t sep, UNULLABLE uv32_t **array) {
	return uz32_new_split_uz32n(cstr, UCV32_CEXPAND(sep), array);
}

size_t uz32_new_split_ucv32_e(uc32_t *cstr, ucv32_t sep, UNULLABLE uv32_t **array, bool *error) {
	return uz32_new_split_uz32n_e(cstr, UCV32_CEXPAND(sep), array, error);
}

size_t uz32_split_ucv32(uc32_t *cstr, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
	return uz32_split_uz32n(cstr, UCV32_CEXPAND(sep), array, array_len);
}

size_t uz32_new_split_uv32(uc32_t *cstr, uv32_t sep, UNULLABLE uv32_t **array) {
	return uz32_new_split_uz32n(cstr, UV32_CEXPAND(sep), array);
}

size_t uz32_new_split_uv32_e(uc32_t *cstr, uv32_t sep, UNULLABLE uv32_t **array, bool *error) {
	return uz32_new_split_uz32n_e(cstr, UV32_CEXPAND(sep), array, error);
}

size_t uz32_split_uv32(uc32_t *cstr, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
	return uz32_split_uz32n(cstr, UV32_CEXPAND(sep), array, array_len);
}

size_t uz32_new_split_us32(uc32_t *cstr, const us32_t *sep, UNULLABLE uv32_t **array) {
	return uz32_new_split_uz32n(cstr, US32_CEXPAND(sep), array);
}

size_t uz32_new_split_us32_e(uc32_t *cstr, const us32_t *sep, UNULLABLE uv32_t **array, bool *error) {
	return uz32_new_split_uz32n_e(cstr, US32_CEXPAND(sep), array, error);
}

size_t uz32_split_us32(uc32_t *cstr, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len) {
	return uz32_split_uz32n(cstr, US32_CEXPAND(sep), array, array_len);
}

size_t uz32n_new_csplit_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uc32_e(cstr, sep, cstr_len, array, NULL);
}

size_t uz32n_new_csplit_uc32_e(const uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_split_uc32_e((uc32_t *) cstr, cstr_len, sep, (uv32_t **) array, error);
}

size_t uz32n_csplit_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_split_uc32((uc32_t *) cstr, cstr_len, sep, (uv32_t *) array, array_len);
}

size_t uz32n_new_csplit_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz32n_new_csplit_uz32_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_split_uz32_e((uc32_t *) cstr, cstr_len, sep, (uv32_t **) array, error);
}

size_t uz32n_csplit_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_split_uz32((uc32_t *) cstr, cstr_len, sep, (uv32_t *) array, array_len);
}

size_t uz32n_new_csplit_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32n_e(cstr, cstr_len, sep, sep_len, array, NULL);
}

size_t uz32n_new_csplit_uz32n_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e((uc32_t *) cstr, cstr_len, sep, sep_len, (uv32_t **) array, error);
}

size_t uz32n_csplit_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_split_uz32n((uc32_t *) cstr, cstr_len, sep, sep_len, (uv32_t *) array, array_len);
}

size_t uz32n_new_csplit_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32n(cstr, cstr_len, UCV32_CEXPAND(sep), array);
}

size_t uz32n_new_csplit_ucv32_e(const uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(cstr, cstr_len, UCV32_CEXPAND(sep), array, error);
}

size_t uz32n_csplit_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(cstr, cstr_len, UCV32_CEXPAND(sep), array, array_len);
}

size_t uz32n_new_csplit_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32n(cstr, cstr_len, UV32_CEXPAND(sep), array);
}

size_t uz32n_new_csplit_uv32_e(const uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(cstr, cstr_len, UV32_CEXPAND(sep), array, error);
}

size_t uz32n_csplit_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(cstr, cstr_len, UV32_CEXPAND(sep), array, array_len);
}

size_t uz32n_new_csplit_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE ucv32_t **array) {
    return uz32n_new_csplit_uz32n(cstr, cstr_len, US32_CEXPAND(sep), array);
}

size_t uz32n_new_csplit_us32_e(const uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(cstr, cstr_len, US32_CEXPAND(sep), array, error);
}

size_t uz32n_csplit_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(cstr, cstr_len, US32_CEXPAND(sep), array, array_len);
}

size_t uz32n_new_split_uc32(uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uc32_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz32n_new_split_uc32_e(uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE uv32_t **array, bool *error) {
    UZXN_NEW_SPLIT_UCX_E(cstr, cstr_len, sep, array, error, 32);
}

size_t uz32n_split_uc32(uc32_t *cstr, size_t cstr_len, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
    UZXN_SPLIT_UCX(cstr, cstr_len, sep, array, array_len, 32);
}

size_t uz32n_new_split_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uz32_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz32n_new_split_uz32_e(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error) {
    UZXN_NEW_SPLIT_UZX_E(cstr, cstr_len, sep, array, error, 32);
}

size_t uz32n_split_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(cstr, cstr_len, sep, uz32_len(sep), array, array_len);
}

size_t uz32n_new_split_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array) {
    return uz32n_new_split_uz32n_e(cstr, cstr_len, sep, sep_len, array, NULL);
}

size_t uz32n_new_split_uz32n_e(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error) {
    UZXN_NEW_SPLIT_UZXN_E(cstr, cstr_len, sep, sep_len, array, error, 32);
}

size_t uz32n_split_uz32n(uc32_t *cstr, size_t cstr_len, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len) {
    UZXN_SPLIT_UZXN(cstr, cstr_len, sep, sep_len, array, array_len, 32);
}

size_t uz32n_new_split_ucv32(uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE uv32_t **array) {
	return uz32n_new_split_uz32n(cstr, cstr_len, UCV32_CEXPAND(sep), array);
}

size_t uz32n_new_split_ucv32_e(uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE uv32_t **array, bool *error) {
	return uz32n_new_split_uz32n_e(cstr, cstr_len, UCV32_CEXPAND(sep), array, error);
}

size_t uz32n_split_ucv32(uc32_t *cstr, size_t cstr_len, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
	return uz32n_split_uz32n(cstr, cstr_len, UCV32_CEXPAND(sep), array, array_len);
}

size_t uz32n_new_split_uv32(uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE uv32_t **array) {
	return uz32n_new_split_uz32n(cstr, cstr_len, UV32_CEXPAND(sep), array);
}

size_t uz32n_new_split_uv32_e(uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE uv32_t **array, bool *error) {
	return uz32n_new_split_uz32n_e(cstr, cstr_len, UV32_CEXPAND(sep), array, error);
}

size_t uz32n_split_uv32(uc32_t *cstr, size_t cstr_len, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len) {
	return uz32n_split_uz32n(cstr, cstr_len, UV32_CEXPAND(sep), array, array_len);
}

size_t uz32n_new_split_us32(uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE uv32_t **array) {
	return uz32n_new_split_uz32n(cstr, cstr_len, US32_CEXPAND(sep), array);
}

size_t uz32n_new_split_us32_e(uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE uv32_t **array, bool *error) {
	return uz32n_new_split_uz32n_e(cstr, cstr_len, US32_CEXPAND(sep), array, error);
}

size_t uz32n_split_us32(uc32_t *cstr, size_t cstr_len, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len) {
	return uz32n_split_uz32n(cstr, cstr_len, US32_CEXPAND(sep), array, array_len);
}

size_t uz16_new_csplit_uc16(const uc16_t *cstr, uc16_t sep, UNULLABLE ucv16_t **array) {
    return uz16_new_csplit_uc16_e(cstr, sep, array, NULL);
}

size_t uz16_new_csplit_uc16_e(const uc16_t *cstr, uc16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16_new_split_uc16_e((uc16_t *) cstr, sep, (uv16_t **) array, error);
}

size_t uz16_csplit_uc16(const uc16_t *cstr, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16_split_uc16((uc16_t *) cstr, sep, (uv16_t *) array, array_len);
}

size_t uz16_new_csplit_uz16(const uc16_t *cstr, const uc16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16_new_csplit_uz16_e(cstr, sep, array, NULL);
}

size_t uz16_new_csplit_uz16_e(const uc16_t *cstr, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16_new_split_uz16_e((uc16_t *) cstr, sep, (uv16_t **) array, error);
}

size_t uz16_csplit_uz16(const uc16_t *cstr, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16_split_uz16((uc16_t *) cstr, sep, (uv16_t *) array, array_len);
}

size_t uz16_new_csplit_uz16n(const uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array) {
    return uz16_new_csplit_uz16n_e(cstr, sep, sep_len, array, NULL);
}

size_t uz16_new_csplit_uz16n_e(const uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error) {
    return uz16_new_split_uz16n_e((uc16_t *) cstr, sep, sep_len, (uv16_t **) array, error);
}

size_t uz16_csplit_uz16n(const uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16_split_uz16n((uc16_t *) cstr, sep, sep_len, (uv16_t *) array, array_len);
}

size_t uz16_new_csplit_ucv16(const uc16_t *cstr, ucv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16_new_csplit_uz16n(cstr, UCV16_CEXPAND(sep), array);
}

size_t uz16_new_csplit_ucv16_e(const uc16_t *cstr, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16_new_csplit_uz16n_e(cstr, UCV16_CEXPAND(sep), array, error);
}

size_t uz16_csplit_ucv16(const uc16_t *cstr, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16_csplit_uz16n(cstr, UCV16_CEXPAND(sep), array, array_len);
}

size_t uz16_new_csplit_uv16(const uc16_t *cstr, uv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16_new_csplit_uz16n(cstr, UV16_CEXPAND(sep), array);
}

size_t uz16_new_csplit_uv16_e(const uc16_t *cstr, uv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16_new_csplit_uz16n_e(cstr, UV16_CEXPAND(sep), array, error);
}

size_t uz16_csplit_uv16(const uc16_t *cstr, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16_csplit_uz16n(cstr, UV16_CEXPAND(sep), array, array_len);
}

size_t uz16_new_csplit_us16(const uc16_t *cstr, const us16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16_new_csplit_uz16n(cstr, US16_CEXPAND(sep), array);
}

size_t uz16_new_csplit_us16_e(const uc16_t *cstr, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16_new_csplit_uz16n_e(cstr, US16_CEXPAND(sep), array, error);
}

size_t uz16_csplit_us16(const uc16_t *cstr, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16_csplit_uz16n(cstr, US16_CEXPAND(sep), array, array_len);
}

size_t uz16_new_split_uc16(uc16_t *cstr, uc16_t sep, UNULLABLE uv16_t **array) {
    return uz16_new_split_uc16_e(cstr, sep, array, NULL);
}

size_t uz16_new_split_uc16_e(uc16_t *cstr, uc16_t sep, UNULLABLE uv16_t **array, bool *error) {
    UZX_NEW_SPLIT_UCX_E(cstr, sep, array, error, 16);
}

size_t uz16_split_uc16(uc16_t *cstr, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
    UZX_SPLIT_UCX(cstr, sep, array, array_len, 16);
}

size_t uz16_new_split_uz16(uc16_t *cstr, const uc16_t *sep, UNULLABLE uv16_t **array) {
    return uz16_new_split_uz16_e(cstr, sep, array, NULL);
}

size_t uz16_new_split_uz16_e(uc16_t *cstr, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error) {
    UZX_NEW_SPLIT_UZX_E(cstr, sep, array, error, 16);
}

size_t uz16_split_uz16(uc16_t *cstr, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16_split_uz16n(cstr, sep, uz16_len(sep), array, array_len);
}

size_t uz16_new_split_uz16n(uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array) {
    return uz16_new_split_uz16n_e(cstr, sep, sep_len, array, NULL);
}

size_t uz16_new_split_uz16n_e(uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error) {
    UZX_NEW_SPLIT_UZXN_E(cstr, sep, sep_len, array, error, 16);
}

size_t uz16_split_uz16n(uc16_t *cstr, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_uz16n(cstr, uz16_len(cstr), sep, sep_len, array, array_len);
}

size_t uz16_new_split_ucv16(uc16_t *cstr, ucv16_t sep, UNULLABLE uv16_t **array) {
	return uz16_new_split_uz16n(cstr, UCV16_CEXPAND(sep), array);
}

size_t uz16_new_split_ucv16_e(uc16_t *cstr, ucv16_t sep, UNULLABLE uv16_t **array, bool *error) {
	return uz16_new_split_uz16n_e(cstr, UCV16_CEXPAND(sep), array, error);
}

size_t uz16_split_ucv16(uc16_t *cstr, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
	return uz16_split_uz16n(cstr, UCV16_CEXPAND(sep), array, array_len);
}

size_t uz16_new_split_uv16(uc16_t *cstr, uv16_t sep, UNULLABLE uv16_t **array) {
	return uz16_new_split_uz16n(cstr, UV16_CEXPAND(sep), array);
}

size_t uz16_new_split_uv16_e(uc16_t *cstr, uv16_t sep, UNULLABLE uv16_t **array, bool *error) {
	return uz16_new_split_uz16n_e(cstr, UV16_CEXPAND(sep), array, error);
}

size_t uz16_split_uv16(uc16_t *cstr, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
	return uz16_split_uz16n(cstr, UV16_CEXPAND(sep), array, array_len);
}

size_t uz16_new_split_us16(uc16_t *cstr, const us16_t *sep, UNULLABLE uv16_t **array) {
	return uz16_new_split_uz16n(cstr, US16_CEXPAND(sep), array);
}

size_t uz16_new_split_us16_e(uc16_t *cstr, const us16_t *sep, UNULLABLE uv16_t **array, bool *error) {
	return uz16_new_split_uz16n_e(cstr, US16_CEXPAND(sep), array, error);
}

size_t uz16_split_us16(uc16_t *cstr, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len) {
	return uz16_split_uz16n(cstr, US16_CEXPAND(sep), array, array_len);
}

size_t uz16n_new_csplit_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uc16_e(cstr, sep, cstr_len, array, NULL);
}

size_t uz16n_new_csplit_uc16_e(const uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_split_uc16_e((uc16_t *) cstr, cstr_len, sep, (uv16_t **) array, error);
}

size_t uz16n_csplit_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_split_uc16((uc16_t *) cstr, cstr_len, sep, (uv16_t *) array, array_len);
}

size_t uz16n_new_csplit_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz16n_new_csplit_uz16_e(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_split_uz16_e((uc16_t *) cstr, cstr_len, sep, (uv16_t **) array, error);
}

size_t uz16n_csplit_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_split_uz16((uc16_t *) cstr, cstr_len, sep, (uv16_t *) array, array_len);
}

size_t uz16n_new_csplit_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16n_e(cstr, cstr_len, sep, sep_len, array, NULL);
}

size_t uz16n_new_csplit_uz16n_e(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_split_uz16n_e((uc16_t *) cstr, cstr_len, sep, sep_len, (uv16_t **) array, error);
}

size_t uz16n_csplit_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_split_uz16n((uc16_t *) cstr, cstr_len, sep, sep_len, (uv16_t *) array, array_len);
}

size_t uz16n_new_csplit_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16n(cstr, cstr_len, UCV16_CEXPAND(sep), array);
}

size_t uz16n_new_csplit_ucv16_e(const uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16n_e(cstr, cstr_len, UCV16_CEXPAND(sep), array, error);
}

size_t uz16n_csplit_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16n(cstr, cstr_len, UCV16_CEXPAND(sep), array, array_len);
}

size_t uz16n_new_csplit_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16n(cstr, cstr_len, UV16_CEXPAND(sep), array);
}

size_t uz16n_new_csplit_uv16_e(const uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16n_e(cstr, cstr_len, UV16_CEXPAND(sep), array, error);
}

size_t uz16n_csplit_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16n(cstr, cstr_len, UV16_CEXPAND(sep), array, array_len);
}

size_t uz16n_new_csplit_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE ucv16_t **array) {
    return uz16n_new_csplit_uz16n(cstr, cstr_len, US16_CEXPAND(sep), array);
}

size_t uz16n_new_csplit_us16_e(const uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error) {
    return uz16n_new_csplit_uz16n_e(cstr, cstr_len, US16_CEXPAND(sep), array, error);
}

size_t uz16n_csplit_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len) {
    return uz16n_csplit_uz16n(cstr, cstr_len, US16_CEXPAND(sep), array, array_len);
}

size_t uz16n_new_split_uc16(uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uc16_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz16n_new_split_uc16_e(uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE uv16_t **array, bool *error) {
    UZXN_NEW_SPLIT_UCX_E(cstr, cstr_len, sep, array, error, 16);
}

size_t uz16n_split_uc16(uc16_t *cstr, size_t cstr_len, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
    UZXN_SPLIT_UCX(cstr, cstr_len, sep, array, array_len, 16);
}

size_t uz16n_new_split_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uz16_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz16n_new_split_uz16_e(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error) {
    UZXN_NEW_SPLIT_UZX_E(cstr, cstr_len, sep, array, error, 16);
}

size_t uz16n_split_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len) {
    return uz16n_split_uz16n(cstr, cstr_len, sep, uz16_len(sep), array, array_len);
}

size_t uz16n_new_split_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array) {
    return uz16n_new_split_uz16n_e(cstr, cstr_len, sep, sep_len, array, NULL);
}

size_t uz16n_new_split_uz16n_e(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error) {
    UZXN_NEW_SPLIT_UZXN_E(cstr, cstr_len, sep, sep_len, array, error, 16);
}

size_t uz16n_split_uz16n(uc16_t *cstr, size_t cstr_len, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len) {
    UZXN_SPLIT_UZXN(cstr, cstr_len, sep, sep_len, array, array_len, 16);
}

size_t uz16n_new_split_ucv16(uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE uv16_t **array) {
	return uz16n_new_split_uz16n(cstr, cstr_len, UCV16_CEXPAND(sep), array);
}

size_t uz16n_new_split_ucv16_e(uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE uv16_t **array, bool *error) {
	return uz16n_new_split_uz16n_e(cstr, cstr_len, UCV16_CEXPAND(sep), array, error);
}

size_t uz16n_split_ucv16(uc16_t *cstr, size_t cstr_len, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
	return uz16n_split_uz16n(cstr, cstr_len, UCV16_CEXPAND(sep), array, array_len);
}

size_t uz16n_new_split_uv16(uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE uv16_t **array) {
	return uz16n_new_split_uz16n(cstr, cstr_len, UV16_CEXPAND(sep), array);
}

size_t uz16n_new_split_uv16_e(uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE uv16_t **array, bool *error) {
	return uz16n_new_split_uz16n_e(cstr, cstr_len, UV16_CEXPAND(sep), array, error);
}

size_t uz16n_split_uv16(uc16_t *cstr, size_t cstr_len, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len) {
	return uz16n_split_uz16n(cstr, cstr_len, UV16_CEXPAND(sep), array, array_len);
}

size_t uz16n_new_split_us16(uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE uv16_t **array) {
	return uz16n_new_split_uz16n(cstr, cstr_len, US16_CEXPAND(sep), array);
}

size_t uz16n_new_split_us16_e(uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE uv16_t **array, bool *error) {
	return uz16n_new_split_uz16n_e(cstr, cstr_len, US16_CEXPAND(sep), array, error);
}

size_t uz16n_split_us16(uc16_t *cstr, size_t cstr_len, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len) {
	return uz16n_split_uz16n(cstr, cstr_len, US16_CEXPAND(sep), array, array_len);
}

size_t uz8_new_csplit_uc8(const uc8_t *cstr, uc8_t sep, UNULLABLE ucv8_t **array) {
    return uz8_new_csplit_uc8_e(cstr, sep, array, NULL);
}

size_t uz8_new_csplit_uc8_e(const uc8_t *cstr, uc8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8_new_split_uc8_e((uc8_t *) cstr, sep, (uv8_t **) array, error);
}

size_t uz8_csplit_uc8(const uc8_t *cstr, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8_split_uc8((uc8_t *) cstr, sep, (uv8_t *) array, array_len);
}

size_t uz8_new_csplit_uz8(const uc8_t *cstr, const uc8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8_new_csplit_uz8_e(cstr, sep, array, NULL);
}

size_t uz8_new_csplit_uz8_e(const uc8_t *cstr, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8_new_split_uz8_e((uc8_t *) cstr, sep, (uv8_t **) array, error);
}

size_t uz8_csplit_uz8(const uc8_t *cstr, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8_split_uz8((uc8_t *) cstr, sep, (uv8_t *) array, array_len);
}

size_t uz8_new_csplit_uz8n(const uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array) {
    return uz8_new_csplit_uz8n_e(cstr, sep, sep_len, array, NULL);
}

size_t uz8_new_csplit_uz8n_e(const uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error) {
    return uz8_new_split_uz8n_e((uc8_t *) cstr, sep, sep_len, (uv8_t **) array, error);
}

size_t uz8_csplit_uz8n(const uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8_split_uz8n((uc8_t *) cstr, sep, sep_len, (uv8_t *) array, array_len);
}

size_t uz8_new_csplit_ucv8(const uc8_t *cstr, ucv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8_new_csplit_uz8n(cstr, UCV8_CEXPAND(sep), array);
}

size_t uz8_new_csplit_ucv8_e(const uc8_t *cstr, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8_new_csplit_uz8n_e(cstr, UCV8_CEXPAND(sep), array, error);
}

size_t uz8_csplit_ucv8(const uc8_t *cstr, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8_csplit_uz8n(cstr, UCV8_CEXPAND(sep), array, array_len);
}

size_t uz8_new_csplit_uv8(const uc8_t *cstr, uv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8_new_csplit_uz8n(cstr, UV8_CEXPAND(sep), array);
}

size_t uz8_new_csplit_uv8_e(const uc8_t *cstr, uv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8_new_csplit_uz8n_e(cstr, UV8_CEXPAND(sep), array, error);
}

size_t uz8_csplit_uv8(const uc8_t *cstr, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8_csplit_uz8n(cstr, UV8_CEXPAND(sep), array, array_len);
}

size_t uz8_new_csplit_us8(const uc8_t *cstr, const us8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8_new_csplit_uz8n(cstr, US8_CEXPAND(sep), array);
}

size_t uz8_new_csplit_us8_e(const uc8_t *cstr, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8_new_csplit_uz8n_e(cstr, US8_CEXPAND(sep), array, error);
}

size_t uz8_csplit_us8(const uc8_t *cstr, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8_csplit_uz8n(cstr, US8_CEXPAND(sep), array, array_len);
}

size_t uz8_new_split_uc8(uc8_t *cstr, uc8_t sep, UNULLABLE uv8_t **array) {
    return uz8_new_split_uc8_e(cstr, sep, array, NULL);
}

size_t uz8_new_split_uc8_e(uc8_t *cstr, uc8_t sep, UNULLABLE uv8_t **array, bool *error) {
    UZX_NEW_SPLIT_UCX_E(cstr, sep, array, error, 8);
}

size_t uz8_split_uc8(uc8_t *cstr, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
    UZX_SPLIT_UCX(cstr, sep, array, array_len, 8);
}

size_t uz8_new_split_uz8(uc8_t *cstr, const uc8_t *sep, UNULLABLE uv8_t **array) {
    return uz8_new_split_uz8_e(cstr, sep, array, NULL);
}

size_t uz8_new_split_uz8_e(uc8_t *cstr, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error) {
    UZX_NEW_SPLIT_UZX_E(cstr, sep, array, error, 8);
}

size_t uz8_split_uz8(uc8_t *cstr, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8_split_uz8n(cstr, sep, uz8_len(sep), array, array_len);
}

size_t uz8_new_split_uz8n(uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array) {
    return uz8_new_split_uz8n_e(cstr, sep, sep_len, array, NULL);
}

size_t uz8_new_split_uz8n_e(uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error) {
    UZX_NEW_SPLIT_UZXN_E(cstr, sep, sep_len, array, error, 8);
}

size_t uz8_split_uz8n(uc8_t *cstr, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_uz8n(cstr, uz8_len(cstr), sep, sep_len, array, array_len);
}

size_t uz8_new_split_ucv8(uc8_t *cstr, ucv8_t sep, UNULLABLE uv8_t **array) {
	return uz8_new_split_uz8n(cstr, UCV8_CEXPAND(sep), array);
}

size_t uz8_new_split_ucv8_e(uc8_t *cstr, ucv8_t sep, UNULLABLE uv8_t **array, bool *error) {
	return uz8_new_split_uz8n_e(cstr, UCV8_CEXPAND(sep), array, error);
}

size_t uz8_split_ucv8(uc8_t *cstr, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
	return uz8_split_uz8n(cstr, UCV8_CEXPAND(sep), array, array_len);
}

size_t uz8_new_split_uv8(uc8_t *cstr, uv8_t sep, UNULLABLE uv8_t **array) {
	return uz8_new_split_uz8n(cstr, UV8_CEXPAND(sep), array);
}

size_t uz8_new_split_uv8_e(uc8_t *cstr, uv8_t sep, UNULLABLE uv8_t **array, bool *error) {
	return uz8_new_split_uz8n_e(cstr, UV8_CEXPAND(sep), array, error);
}

size_t uz8_split_uv8(uc8_t *cstr, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
	return uz8_split_uz8n(cstr, UV8_CEXPAND(sep), array, array_len);
}

size_t uz8_new_split_us8(uc8_t *cstr, const us8_t *sep, UNULLABLE uv8_t **array) {
	return uz8_new_split_uz8n(cstr, US8_CEXPAND(sep), array);
}

size_t uz8_new_split_us8_e(uc8_t *cstr, const us8_t *sep, UNULLABLE uv8_t **array, bool *error) {
	return uz8_new_split_uz8n_e(cstr, US8_CEXPAND(sep), array, error);
}

size_t uz8_split_us8(uc8_t *cstr, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len) {
	return uz8_split_uz8n(cstr, US8_CEXPAND(sep), array, array_len);
}

size_t uz8n_new_csplit_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uc8_e(cstr, sep, cstr_len, array, NULL);
}

size_t uz8n_new_csplit_uc8_e(const uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_split_uc8_e((uc8_t *) cstr, cstr_len, sep, (uv8_t **) array, error);
}

size_t uz8n_csplit_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_split_uc8((uc8_t *) cstr, cstr_len, sep, (uv8_t *) array, array_len);
}

size_t uz8n_new_csplit_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz8n_new_csplit_uz8_e(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_split_uz8_e((uc8_t *) cstr, cstr_len, sep, (uv8_t **) array, error);
}

size_t uz8n_csplit_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_split_uz8((uc8_t *) cstr, cstr_len, sep, (uv8_t *) array, array_len);
}

size_t uz8n_new_csplit_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8n_e(cstr, cstr_len, sep, sep_len, array, NULL);
}

size_t uz8n_new_csplit_uz8n_e(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_split_uz8n_e((uc8_t *) cstr, cstr_len, sep, sep_len, (uv8_t **) array, error);
}

size_t uz8n_csplit_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_split_uz8n((uc8_t *) cstr, cstr_len, sep, sep_len, (uv8_t *) array, array_len);
}

size_t uz8n_new_csplit_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8n(cstr, cstr_len, UCV8_CEXPAND(sep), array);
}

size_t uz8n_new_csplit_ucv8_e(const uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8n_e(cstr, cstr_len, UCV8_CEXPAND(sep), array, error);
}

size_t uz8n_csplit_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8n(cstr, cstr_len, UCV8_CEXPAND(sep), array, array_len);
}

size_t uz8n_new_csplit_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8n(cstr, cstr_len, UV8_CEXPAND(sep), array);
}

size_t uz8n_new_csplit_uv8_e(const uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8n_e(cstr, cstr_len, UV8_CEXPAND(sep), array, error);
}

size_t uz8n_csplit_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8n(cstr, cstr_len, UV8_CEXPAND(sep), array, array_len);
}

size_t uz8n_new_csplit_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE ucv8_t **array) {
    return uz8n_new_csplit_uz8n(cstr, cstr_len, US8_CEXPAND(sep), array);
}

size_t uz8n_new_csplit_us8_e(const uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error) {
    return uz8n_new_csplit_uz8n_e(cstr, cstr_len, US8_CEXPAND(sep), array, error);
}

size_t uz8n_csplit_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len) {
    return uz8n_csplit_uz8n(cstr, cstr_len, US8_CEXPAND(sep), array, array_len);
}

size_t uz8n_new_split_uc8(uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uc8_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz8n_new_split_uc8_e(uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE uv8_t **array, bool *error) {
    UZXN_NEW_SPLIT_UCX_E(cstr, cstr_len, sep, array, error, 8);
}

size_t uz8n_split_uc8(uc8_t *cstr, size_t cstr_len, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
    UZXN_SPLIT_UCX(cstr, cstr_len, sep, array, array_len, 8);
}

size_t uz8n_new_split_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uz8_e(cstr, cstr_len, sep, array, NULL);
}

size_t uz8n_new_split_uz8_e(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error) {
    UZXN_NEW_SPLIT_UZX_E(cstr, cstr_len, sep, array, error, 8);
}

size_t uz8n_split_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len) {
    return uz8n_split_uz8n(cstr, cstr_len, sep, uz8_len(sep), array, array_len);
}

size_t uz8n_new_split_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array) {
    return uz8n_new_split_uz8n_e(cstr, cstr_len, sep, sep_len, array, NULL);
}

size_t uz8n_new_split_uz8n_e(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error) {
    UZXN_NEW_SPLIT_UZXN_E(cstr, cstr_len, sep, sep_len, array, error, 8);
}

size_t uz8n_split_uz8n(uc8_t *cstr, size_t cstr_len, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len) {
    UZXN_SPLIT_UZXN(cstr, cstr_len, sep, sep_len, array, array_len, 8);
}

size_t uz8n_new_split_ucv8(uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE uv8_t **array) {
	return uz8n_new_split_uz8n(cstr, cstr_len, UCV8_CEXPAND(sep), array);
}

size_t uz8n_new_split_ucv8_e(uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE uv8_t **array, bool *error) {
	return uz8n_new_split_uz8n_e(cstr, cstr_len, UCV8_CEXPAND(sep), array, error);
}

size_t uz8n_split_ucv8(uc8_t *cstr, size_t cstr_len, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
	return uz8n_split_uz8n(cstr, cstr_len, UCV8_CEXPAND(sep), array, array_len);
}

size_t uz8n_new_split_uv8(uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE uv8_t **array) {
	return uz8n_new_split_uz8n(cstr, cstr_len, UV8_CEXPAND(sep), array);
}

size_t uz8n_new_split_uv8_e(uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE uv8_t **array, bool *error) {
	return uz8n_new_split_uz8n_e(cstr, cstr_len, UV8_CEXPAND(sep), array, error);
}

size_t uz8n_split_uv8(uc8_t *cstr, size_t cstr_len, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len) {
	return uz8n_split_uz8n(cstr, cstr_len, UV8_CEXPAND(sep), array, array_len);
}

size_t uz8n_new_split_us8(uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE uv8_t **array) {
	return uz8n_new_split_uz8n(cstr, cstr_len, US8_CEXPAND(sep), array);
}

size_t uz8n_new_split_us8_e(uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE uv8_t **array, bool *error) {
	return uz8n_new_split_uz8n_e(cstr, cstr_len, US8_CEXPAND(sep), array, error);
}

size_t uz8n_split_us8(uc8_t *cstr, size_t cstr_len, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len) {
	return uz8n_split_uz8n(cstr, cstr_len, US8_CEXPAND(sep), array, array_len);
}

bool uz32_contains_uc32(const uc32_t *cstr, uc32_t target) {
	return uz32_find_uc32(cstr, target) >= 0;
}

bool uz32_contains_uz32(const uc32_t *cstr, const uc32_t *target) {
	return uz32_find_uz32(cstr, target) >= 0;
}

bool uz32_contains_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len) {
    return uz32_find_uz32n(cstr, target, target_len) >= 0;
}

bool uz32_contains_ucv32(const uc32_t *cstr, ucv32_t target) {
	return uz32_find_ucv32(cstr, target) >= 0;
}

bool uz32_contains_uv32(const uc32_t *cstr, uv32_t target) {
	return uz32_find_uv32(cstr, target) >= 0;
}

bool uz32_contains_us32(const uc32_t *cstr, const us32_t *target) {
	return uz32_find_us32(cstr, target) >= 0;
}

bool uz32n_contains_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target) {
	return uz32n_find_uc32(cstr, cstr_len, target) >= 0;
}

bool uz32n_contains_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
	return uz32n_find_uz32(cstr, cstr_len, target) >= 0;
}

bool uz32n_contains_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
	return uz32n_find_uz32n(cstr, cstr_len, target, target_len) >= 0;
}

bool uz32n_contains_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target) {
	return uz32n_find_ucv32(cstr, cstr_len, target) >= 0;
}

bool uz32n_contains_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target) {
	return uz32n_find_uv32(cstr, cstr_len, target) >= 0;
}

bool uz32n_contains_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target) {
	return uz32n_find_us32(cstr, cstr_len, target) >= 0;
}

bool uz16_contains_uc16(const uc16_t *cstr, uc16_t target) {
	return uz16_find_uc16(cstr, target) >= 0;
}

bool uz16_contains_uz16(const uc16_t *cstr, const uc16_t *target) {
	return uz16_find_uz16(cstr, target) >= 0;
}

bool uz16_contains_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len) {
	return uz16_find_uz16n(cstr, target, target_len) >= 0;
}

bool uz16_contains_ucv16(const uc16_t *cstr, ucv16_t target) {
	return uz16_find_ucv16(cstr, target) >= 0;
}

bool uz16_contains_uv16(const uc16_t *cstr, uv16_t target) {
	return uz16_find_uv16(cstr, target) >= 0;
}

bool uz16_contains_us16(const uc16_t *cstr, const us16_t *target) {
	return uz16_find_us16(cstr, target) >= 0;
}

bool uz16n_contains_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target) {
	return uz16n_find_uc16(cstr, cstr_len, target) >= 0;
}

bool uz16n_contains_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
	return uz16n_find_uz16(cstr, cstr_len, target) >= 0;
}

bool uz16n_contains_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
	return uz16n_find_uz16n(cstr, cstr_len, target, target_len) >= 0;
}

bool uz16n_contains_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target) {
	return uz16n_find_ucv16(cstr, cstr_len, target) >= 0;
}

bool uz16n_contains_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target) {
	return uz16n_find_uv16(cstr, cstr_len, target) >= 0;
}

bool uz16n_contains_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target) {
	return uz16n_find_us16(cstr, cstr_len, target) >= 0;
}

bool uz8_contains_uc8(const uc8_t *cstr, uc8_t target) {
	return uz8_find_uc8(cstr, target) >= 0;
}

bool uz8_contains_uz8(const uc8_t *cstr, const uc8_t *target) {
	return uz8_find_uz8(cstr, target) >= 0;
}

bool uz8_contains_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len) {
	return uz8_find_uz8n(cstr, target, target_len) >= 0;
}

bool uz8_contains_ucv8(const uc8_t *cstr, ucv8_t target) {
	return uz8_find_ucv8(cstr, target) >= 0;
}

bool uz8_contains_uv8(const uc8_t *cstr, uv8_t target) {
	return uz8_find_uv8(cstr, target) >= 0;
}

bool uz8_contains_us8(const uc8_t *cstr, const us8_t *target) {
	return uz8_find_us8(cstr, target) >= 0;
}

bool uz8n_contains_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target) {
	return uz8n_find_uc8(cstr, cstr_len, target) >= 0;
}

bool uz8n_contains_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
	return uz8n_find_uz8(cstr, cstr_len, target) >= 0;
}

bool uz8n_contains_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
	return uz8n_find_uz8n(cstr, cstr_len, target, target_len) >= 0;
}

bool uz8n_contains_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target) {
	return uz8n_find_ucv8(cstr, cstr_len, target) >= 0;
}

bool uz8n_contains_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target) {
	return uz8n_find_uv8(cstr, cstr_len, target) >= 0;
}

bool uz8n_contains_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target) {
	return uz8n_find_us8(cstr, cstr_len, target) >= 0;
}

#define UZX_FIND_UCX_FROM(cstr, target, from, X) \
    assert(uz##X##_bounds(cstr, from));          \
                                                 \
    for (size_t i = from; cstr[i]; ++i)          \
        if (cstr[i] == target)                   \
            return i;                            \
                                                 \
    return -1

#define UZX_FIND_UZX_FROM(cstr, target, from, X)          \
    assert(uz##X##_bounds(cstr, from) && target);         \
                                                          \
    if (!*target)                                         \
        return -1;                                        \
                                                          \
    for (size_t i = from; cstr[i]; ++i) {                 \
        bool found = true;                                \
                                                          \
        for (size_t j = 0; cstr[i + j] && target[j]; ++j) \
            if (cstr[i + j] != target[j]) {               \
                found = false;                            \
                break;                                    \
            }                                             \
                                                          \
        if (found)                                        \
            return i;                                     \
    }                                                     \
                                                          \
	return -1

#define UZX_FIND_UZXN_FROM(cstr, target, target_len, from, X)  \
    assert(uz##X##_bounds(cstr, from) && target);              \
                                                               \
    if (!target_len)                                           \
        return -1;                                             \
                                                               \
    for (size_t i = from; cstr[i]; ++i) {                      \
        bool found = true;                                     \
                                                               \
        for (size_t j = 0; cstr[i + j] && j < target_len; ++j) \
            if (cstr[i + j] != target[j]) {                    \
                found = false;                                 \
                break;                                         \
            }                                                  \
                                                               \
        if (found)                                             \
            return i;                                          \
    }                                                          \
                                                               \
	return -1

#define UZXN_FIND_UCX_FROM(cstr, cstr_len, target, from) \
    assert(cstr && from < cstr_len);                     \
                                                         \
    for (size_t i = from; i < cstr_len; ++i)             \
        if (cstr[i] == target)                           \
            return i;                                    \
                                                         \
    return -1

#define UZXN_FIND_UZX_FROM(cstr, cstr_len, target, from)       \
    assert(cstr && from < cstr_len  && target);                \
                                                               \
    if (!*target)                                              \
        return -1;                                             \
                                                               \
    for (size_t i = from; i < cstr_len; ++i) {                 \
        bool found = true;                                     \
                                                               \
        for (size_t j = 0; i + j < cstr_len && target[j]; ++j) \
            if (cstr[i + j] != target[j]) {                    \
                found = false;                                 \
                break;                                         \
            }                                                  \
                                                               \
        if (found)                                             \
            return i;                                          \
    }                                                          \
                                                               \
	return -1

#define UZXN_FIND_UZXN_FROM(cstr, cstr_len, target, target_len, from) \
    assert(cstr && from < cstr_len && target);                        \
                                                                      \
    if (!target_len)                                                  \
        return -1;                                                    \
                                                                      \
    for (size_t i = from; i <= cstr_len - target_len; ++i) {          \
        bool found = true;                                            \
                                                                      \
        for (size_t j = 0; j < target_len; ++j)                       \
            if (cstr[i + j] != target[j]) {                           \
                found = false;                                        \
                break;                                                \
            }                                                         \
                                                                      \
        if (found)                                                    \
            return i;                                                 \
    }                                                                 \
                                                                      \
	return -1

ptrdiff_t uz32_find_uc32(const uc32_t *cstr, uc32_t target) {
    return uz32_find_uc32_from(cstr, target, 0);
}

ptrdiff_t uz32_find_uc32_from(const uc32_t *cstr, uc32_t target, size_t from) {
    UZX_FIND_UCX_FROM(cstr, target, from, 32);
}

ptrdiff_t uz32_find_uz32(const uc32_t *cstr, const uc32_t *target) {
	return uz32_find_uz32_from(cstr, target, 0);
}

ptrdiff_t uz32_find_uz32_from(const uc32_t *cstr, const uc32_t *target, size_t from) {
    UZX_FIND_UZX_FROM(cstr, target, from, 32);
}

ptrdiff_t uz32_find_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len) {
	return uz32_find_uz32n_from(cstr, target, target_len, 0);
}

ptrdiff_t uz32_find_uz32n_from(const uc32_t *cstr, const uc32_t *target, size_t target_len, size_t from) {
    UZX_FIND_UZXN_FROM(cstr, target, target_len, from, 32);
}

ptrdiff_t uz32_find_ucv32(const uc32_t *cstr, ucv32_t target) {
	return uz32_find_ucv32_from(cstr, target, 0);
}

ptrdiff_t uz32_find_ucv32_from(const uc32_t *cstr, ucv32_t target, size_t from) {
    return uz32_find_uz32n_from(cstr, UCV32_CEXPAND(target), from);
}

ptrdiff_t uz32_find_uv32(const uc32_t *cstr, uv32_t target) {
	return uz32_find_uv32_from(cstr, target, 0);
}

ptrdiff_t uz32_find_uv32_from(const uc32_t *cstr, uv32_t target, size_t from) {
    return uz32_find_uz32n_from(cstr, UV32_CEXPAND(target), from);
}

ptrdiff_t uz32_find_us32(const uc32_t *cstr, const us32_t *target) {
	return uz32_find_us32_from(cstr, target, 0);
}

ptrdiff_t uz32_find_us32_from(const uc32_t *cstr, const us32_t *target, size_t from) {
    return uz32_find_uz32n_from(cstr, US32_CEXPAND(target), from);
}

ptrdiff_t uz32n_find_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target) {
    return uz32n_find_uc32_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz32n_find_uc32_from(const uc32_t *cstr, size_t cstr_len, uc32_t target, size_t from) {
    UZXN_FIND_UCX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz32n_find_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
	return uz32n_find_uz32_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz32n_find_uz32_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t from) {
    UZXN_FIND_UZX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz32n_find_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
	return uz32n_find_uz32n_from(cstr, cstr_len, target, target_len, 0);
}

ptrdiff_t uz32n_find_uz32n_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len, size_t from) {
    UZXN_FIND_UZXN_FROM(cstr, cstr_len, target, target_len, from);
}

ptrdiff_t uz32n_find_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target) {
	return uz32n_find_ucv32_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz32n_find_ucv32_from(const uc32_t *cstr, size_t cstr_len, ucv32_t target, size_t from) {
    return uz32n_find_uz32n_from(cstr, cstr_len, UCV32_CEXPAND(target), from);
}

ptrdiff_t uz32n_find_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target) {
	return uz32n_find_uv32_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz32n_find_uv32_from(const uc32_t *cstr, size_t cstr_len, uv32_t target, size_t from) {
    return uz32n_find_uz32n_from(cstr, cstr_len, UV32_CEXPAND(target), from);
}

ptrdiff_t uz32n_find_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target) {
	return uz32n_find_us32_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz32n_find_us32_from(const uc32_t *cstr, size_t cstr_len, const us32_t *target, size_t from) {
    return uz32n_find_uz32n_from(cstr, cstr_len, US32_CEXPAND(target), from);
}

ptrdiff_t uz16_find_uc16(const uc16_t *cstr, uc16_t target) {
    return uz16_find_uc16_from(cstr, target, 0);
}

ptrdiff_t uz16_find_uc16_from(const uc16_t *cstr, uc16_t target, size_t from) {
    UZX_FIND_UCX_FROM(cstr, target, from, 16);
}

ptrdiff_t uz16_find_uz16(const uc16_t *cstr, const uc16_t *target) {
	return uz16_find_uz16_from(cstr, target, 0);
}

ptrdiff_t uz16_find_uz16_from(const uc16_t *cstr, const uc16_t *target, size_t from) {
    UZX_FIND_UZX_FROM(cstr, target, from, 16);
}

ptrdiff_t uz16_find_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len) {
	return uz16_find_uz16n_from(cstr, target, target_len, 0);
}

ptrdiff_t uz16_find_uz16n_from(const uc16_t *cstr, const uc16_t *target, size_t target_len, size_t from) {
    UZX_FIND_UZXN_FROM(cstr, target, target_len, from, 16);
}

ptrdiff_t uz16_find_ucv16(const uc16_t *cstr, ucv16_t target) {
	return uz16_find_ucv16_from(cstr, target, 0);
}

ptrdiff_t uz16_find_ucv16_from(const uc16_t *cstr, ucv16_t target, size_t from) {
	return uz16_find_uz16n_from(cstr, UCV16_CEXPAND(target), from);
}

ptrdiff_t uz16_find_uv16(const uc16_t *cstr, uv16_t target) {
	return uz16_find_uv16_from(cstr, target, 0);
}

ptrdiff_t uz16_find_uv16_from(const uc16_t *cstr, uv16_t target, size_t from) {
	return uz16_find_uz16n_from(cstr, UV16_CEXPAND(target), from);
}

ptrdiff_t uz16_find_us16(const uc16_t *cstr, const us16_t *target) {
	return uz16_find_us16_from(cstr, target, 0);
}

ptrdiff_t uz16_find_us16_from(const uc16_t *cstr, const us16_t *target, size_t from) {
    return uz16_find_uz16n_from(cstr, US16_CEXPAND(target), from);
}

ptrdiff_t uz16n_find_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target) {
    return uz16n_find_uc16_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz16n_find_uc16_from(const uc16_t *cstr, size_t cstr_len, uc16_t target, size_t from) {
    UZXN_FIND_UCX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz16n_find_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
    return uz16n_find_uz16_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz16n_find_uz16_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t from) {
    UZXN_FIND_UZX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz16n_find_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
    return uz16n_find_uz16n_from(cstr, cstr_len, target, target_len, 0);
}

ptrdiff_t uz16n_find_uz16n_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len, size_t from) {
    UZXN_FIND_UZXN_FROM(cstr, cstr_len, target, target_len, from);
}

ptrdiff_t uz16n_find_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target) {
    return uz16n_find_ucv16_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz16n_find_ucv16_from(const uc16_t *cstr, size_t cstr_len, ucv16_t target, size_t from) {
    return uz16n_find_uz16n_from(cstr, cstr_len, UCV16_CEXPAND(target), from);
}

ptrdiff_t uz16n_find_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target) {
    return uz16n_find_uv16_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz16n_find_uv16_from(const uc16_t *cstr, size_t cstr_len, uv16_t target, size_t from) {
    return uz16n_find_uz16n_from(cstr, cstr_len, UV16_CEXPAND(target), from);
}

ptrdiff_t uz16n_find_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target) {
    return uz16n_find_us16_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz16n_find_us16_from(const uc16_t *cstr, size_t cstr_len, const us16_t *target, size_t from) {
    return uz16n_find_uz16n_from(cstr, cstr_len, US16_CEXPAND(target), from);
}

ptrdiff_t uz8_find_uc8(const uc8_t *cstr, uc8_t target) {
    return uz8_find_uc8_from(cstr, target, 0);
}

ptrdiff_t uz8_find_uc8_from(const uc8_t *cstr, uc8_t target, size_t from) {
    UZX_FIND_UCX_FROM(cstr, target, from, 8);
}

ptrdiff_t uz8_find_uz8(const uc8_t *cstr, const uc8_t *target) {
	return uz8_find_uz8_from(cstr, target, 0);
}

ptrdiff_t uz8_find_uz8_from(const uc8_t *cstr, const uc8_t *target, size_t from) {
    UZX_FIND_UZX_FROM(cstr, target, from, 8);
}

ptrdiff_t uz8_find_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len) {
	return uz8_find_uz8n_from(cstr, target, target_len, 0);
}

ptrdiff_t uz8_find_uz8n_from(const uc8_t *cstr, const uc8_t *target, size_t target_len, size_t from) {
    UZX_FIND_UZXN_FROM(cstr, target, target_len, from, 8);
}

ptrdiff_t uz8_find_ucv8(const uc8_t *cstr, ucv8_t target) {
	return uz8_find_ucv8_from(cstr, target, 0);
}

ptrdiff_t uz8_find_ucv8_from(const uc8_t *cstr, ucv8_t target, size_t from) {
    return uz8_find_uz8n_from(cstr, UCV8_CEXPAND(target), from);
}

ptrdiff_t uz8_find_uv8(const uc8_t *cstr, uv8_t target) {
	return uz8_find_uv8_from(cstr, target, 0);
}

ptrdiff_t uz8_find_uv8_from(const uc8_t *cstr, uv8_t target, size_t from) {
    return uz8_find_uz8n_from(cstr, UV8_CEXPAND(target), from);
}

ptrdiff_t uz8_find_us8(const uc8_t *cstr, const us8_t *target) {
	return uz8_find_us8_from(cstr, target, 0);
}

ptrdiff_t uz8_find_us8_from(const uc8_t *cstr, const us8_t *target, size_t from) {
    return uz8_find_uz8n_from(cstr, US8_CEXPAND(target), from);
}

ptrdiff_t uz8n_find_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target) {
    return uz8n_find_uc8_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz8n_find_uc8_from(const uc8_t *cstr, size_t cstr_len, uc8_t target, size_t from) {
    UZXN_FIND_UCX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz8n_find_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
	return uz8n_find_uz8_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz8n_find_uz8_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t from) {
    UZXN_FIND_UZX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz8n_find_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
	return uz8n_find_uz8n_from(cstr, cstr_len, target, target_len, 0);
}

ptrdiff_t uz8n_find_uz8n_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len, size_t from) {
    UZXN_FIND_UZXN_FROM(cstr, cstr_len, target, target_len, from);
}

ptrdiff_t uz8n_find_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target) {
	return uz8n_find_ucv8_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz8n_find_ucv8_from(const uc8_t *cstr, size_t cstr_len, ucv8_t target, size_t from) {
	return uz8n_find_uz8n_from(cstr, cstr_len, UCV8_CEXPAND(target), from);
}

ptrdiff_t uz8n_find_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target) {
	return uz8n_find_uv8_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz8n_find_uv8_from(const uc8_t *cstr, size_t cstr_len, uv8_t target, size_t from) {
	return uz8n_find_uz8n_from(cstr, cstr_len, UV8_CEXPAND(target), from);
}

ptrdiff_t uz8n_find_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target) {
	return uz8n_find_us8_from(cstr, cstr_len, target, 0);
}

ptrdiff_t uz8n_find_us8_from(const uc8_t *cstr, size_t cstr_len, const us8_t *target, size_t from) {
	return uz8n_find_uz8n_from(cstr, cstr_len, US8_CEXPAND(target), from);
}
    
#define UZXN_RFIND_UCX_FROM(cstr, cstr_len, target, from) \
    assert(cstr && from < cstr_len);                      \
                                                          \
    for (ptrdiff_t i = from; i >= 0; --i)                 \
        if (cstr[i] == target)                            \
            return i;                                     \
                                                          \
    return -1
    
#define UZXN_RFIND_UZXN_FROM(cstr, cstr_len, target, target_len, from) \
    assert(cstr && from < cstr_len && target);                         \
                                                                       \
    if (!target_len)                                                   \
        return -1;                                                     \
                                                                       \
    for (ptrdiff_t i = from; i >= target_len - 1; --i) {               \
        ptrdiff_t j     = i;                                           \
        bool      found = true;                                        \
                                                                       \
        for (ptrdiff_t k = target_len - 1; k >= 0; --k, --j)           \
            if (cstr[j] != target[k]) {                                \
                found = false;                                         \
                break;                                                 \
            }                                                          \
                                                                       \
        if (found)                                                     \
            return j + 1;                                              \
    }                                                                  \
                                                                       \
	return -1

ptrdiff_t uz32_rfind_uc32(const uc32_t *cstr, uc32_t target) {
    return uz32n_rfind_uc32(cstr, uz32_len(cstr), target);
}

ptrdiff_t uz32_rfind_uc32_from(const uc32_t *cstr, uc32_t target, size_t from) {
    return uz32n_rfind_uc32_from(cstr, uz32_len(cstr), target, from);
}

ptrdiff_t uz32_rfind_uz32(const uc32_t *cstr, const uc32_t *target) {
    return uz32n_rfind_uz32(cstr, uz32_len(cstr), target);
}

ptrdiff_t uz32_rfind_uz32_from(const uc32_t *cstr, const uc32_t *target, size_t from) {
    return uz32n_rfind_uz32_from(cstr, uz32_len(cstr), target, from);
}

ptrdiff_t uz32_rfind_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len) {
    return uz32n_rfind_uz32n(cstr, uz32_len(cstr), target, target_len);
}

ptrdiff_t uz32_rfind_uz32n_from(const uc32_t *cstr, const uc32_t *target, size_t target_len, size_t from) {
    return uz32n_rfind_uz32n_from(cstr, uz32_len(cstr), target, target_len, from);
}

ptrdiff_t uz32_rfind_ucv32(const uc32_t *cstr, ucv32_t target) {
    return uz32n_rfind_ucv32(cstr, uz32_len(cstr), target);
}

ptrdiff_t uz32_rfind_ucv32_from(const uc32_t *cstr, ucv32_t target, size_t from) {
    return uz32n_rfind_ucv32_from(cstr, uz32_len(cstr), target, from);
}

ptrdiff_t uz32_rfind_uv32(const uc32_t *cstr, uv32_t target) {
    return uz32n_rfind_uv32(cstr, uz32_len(cstr), target);
}

ptrdiff_t uz32_rfind_uv32_from(const uc32_t *cstr, uv32_t target, size_t from) {
    return uz32n_rfind_uv32_from(cstr, uz32_len(cstr), target, from);
}

ptrdiff_t uz32_rfind_us32(const uc32_t *cstr, const us32_t *target) {
    return uz32n_rfind_us32(cstr, uz32_len(cstr), target);
}

ptrdiff_t uz32_rfind_us32_from(const uc32_t *cstr, const us32_t *target, size_t from) {
    return uz32n_rfind_us32_from(cstr, uz32_len(cstr), target, from);
}

ptrdiff_t uz32n_rfind_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target) {
	return uz32n_rfind_uc32_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz32n_rfind_uc32_from(const uc32_t *cstr, size_t cstr_len, uc32_t target, size_t from) {
    UZXN_RFIND_UCX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz32n_rfind_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
	return uz32n_rfind_uz32_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz32n_rfind_uz32_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t from) {
    return uz32n_rfind_uz32n_from(cstr, cstr_len, target, uz32_len(target), from);
}

ptrdiff_t uz32n_rfind_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
	return uz32n_rfind_uz32n_from(cstr, cstr_len, target, target_len, cstr_len - 1);
}

ptrdiff_t uz32n_rfind_uz32n_from(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len, size_t from) {
    UZXN_RFIND_UZXN_FROM(cstr, cstr_len, target, target_len, from);
}

ptrdiff_t uz32n_rfind_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target) {
	return uz32n_rfind_ucv32_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz32n_rfind_ucv32_from(const uc32_t *cstr, size_t cstr_len, ucv32_t target, size_t from) {
	return uz32n_rfind_uz32n_from(cstr, cstr_len, UCV32_CEXPAND(target), from);
}

ptrdiff_t uz32n_rfind_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target) {
	return uz32n_rfind_uv32_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz32n_rfind_uv32_from(const uc32_t *cstr, size_t cstr_len, uv32_t target, size_t from) {
	return uz32n_rfind_uz32n_from(cstr, cstr_len, UV32_CEXPAND(target), from);
}

ptrdiff_t uz32n_rfind_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target) {
	return uz32n_rfind_us32_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz32n_rfind_us32_from(const uc32_t *cstr, size_t cstr_len, const us32_t *target, size_t from) {
	return uz32n_rfind_uz32n_from(cstr, cstr_len, US32_CEXPAND(target), from);
}

ptrdiff_t uz16_rfind_uc16(const uc16_t *cstr, uc16_t target) {
    return uz16n_rfind_uc16(cstr, uz16_len(cstr), target);
}

ptrdiff_t uz16_rfind_uc16_from(const uc16_t *cstr, uc16_t target, size_t from) {
    return uz16n_rfind_uc16_from(cstr, uz16_len(cstr), target, from);
}

ptrdiff_t uz16_rfind_uz16(const uc16_t *cstr, const uc16_t *target) {
    return uz16n_rfind_uz16(cstr, uz16_len(cstr), target);
}

ptrdiff_t uz16_rfind_uz16_from(const uc16_t *cstr, const uc16_t *target, size_t from) {
    return uz16n_rfind_uz16_from(cstr, uz16_len(cstr), target, from);
}

ptrdiff_t uz16_rfind_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len) {
    return uz16n_rfind_uz16n(cstr, uz16_len(cstr), target, target_len);
}

ptrdiff_t uz16_rfind_uz16n_from(const uc16_t *cstr, const uc16_t *target, size_t target_len, size_t from) {
    return uz16n_rfind_uz16n_from(cstr, uz16_len(cstr), target, target_len, from);
}

ptrdiff_t uz16_rfind_ucv16(const uc16_t *cstr, ucv16_t target) {
    return uz16n_rfind_ucv16(cstr, uz16_len(cstr), target);
}

ptrdiff_t uz16_rfind_ucv16_from(const uc16_t *cstr, ucv16_t target, size_t from) {
    return uz16n_rfind_ucv16_from(cstr, uz16_len(cstr), target, from);
}

ptrdiff_t uz16_rfind_uv16(const uc16_t *cstr, uv16_t target) {
    return uz16n_rfind_uv16(cstr, uz16_len(cstr), target);
}

ptrdiff_t uz16_rfind_uv16_from(const uc16_t *cstr, uv16_t target, size_t from) {
    return uz16n_rfind_uv16_from(cstr, uz16_len(cstr), target, from);
}

ptrdiff_t uz16_rfind_us16(const uc16_t *cstr, const us16_t *target) {
    return uz16n_rfind_us16(cstr, uz16_len(cstr), target);
}

ptrdiff_t uz16_rfind_us16_from(const uc16_t *cstr, const us16_t *target, size_t from) {
    return uz16n_rfind_us16_from(cstr, uz16_len(cstr), target, from);
}

ptrdiff_t uz16n_rfind_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target) {
	return uz16n_rfind_uc16_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz16n_rfind_uc16_from(const uc16_t *cstr, size_t cstr_len, uc16_t target, size_t from) {
    UZXN_RFIND_UCX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz16n_rfind_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
	return uz16n_rfind_uz16_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz16n_rfind_uz16_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t from) {
    return uz16n_rfind_uz16n_from(cstr, cstr_len, target, uz16_len(target), from);
}

ptrdiff_t uz16n_rfind_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
	return uz16n_rfind_uz16n_from(cstr, cstr_len, target, target_len, cstr_len - 1);
}

ptrdiff_t uz16n_rfind_uz16n_from(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len, size_t from) {
    UZXN_RFIND_UZXN_FROM(cstr, cstr_len, target, target_len, from);
}

ptrdiff_t uz16n_rfind_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target) {
	return uz16n_rfind_ucv16_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz16n_rfind_ucv16_from(const uc16_t *cstr, size_t cstr_len, ucv16_t target, size_t from) {
	return uz16n_rfind_uz16n_from(cstr, cstr_len, UCV16_CEXPAND(target), from);
}

ptrdiff_t uz16n_rfind_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target) {
	return uz16n_rfind_uv16_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz16n_rfind_uv16_from(const uc16_t *cstr, size_t cstr_len, uv16_t target, size_t from) {
	return uz16n_rfind_uz16n_from(cstr, cstr_len, UV16_CEXPAND(target), from);
}

ptrdiff_t uz16n_rfind_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target) {
	return uz16n_rfind_us16_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz16n_rfind_us16_from(const uc16_t *cstr, size_t cstr_len, const us16_t *target, size_t from) {
	return uz16n_rfind_uz16n_from(cstr, cstr_len, US16_CEXPAND(target), from);
}

ptrdiff_t uz8_rfind_uc8(const uc8_t *cstr, uc8_t target) {
    return uz8n_rfind_uc8(cstr, uz8_len(cstr), target);
}

ptrdiff_t uz8_rfind_uc8_from(const uc8_t *cstr, uc8_t target, size_t from) {
    return uz8n_rfind_uc8_from(cstr, uz8_len(cstr), target, from);
}

ptrdiff_t uz8_rfind_uz8(const uc8_t *cstr, const uc8_t *target) {
    return uz8n_rfind_uz8(cstr, uz8_len(cstr), target);
}

ptrdiff_t uz8_rfind_uz8_from(const uc8_t *cstr, const uc8_t *target, size_t from) {
    return uz8n_rfind_uz8_from(cstr, uz8_len(cstr), target, from);
}

ptrdiff_t uz8_rfind_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len) {
    return uz8n_rfind_uz8n(cstr, uz8_len(cstr), target, target_len);
}

ptrdiff_t uz8_rfind_uz8n_from(const uc8_t *cstr, const uc8_t *target, size_t target_len, size_t from) {
    return uz8n_rfind_uz8n_from(cstr, uz8_len(cstr), target, target_len, from);
}

ptrdiff_t uz8_rfind_ucv8(const uc8_t *cstr, ucv8_t target) {
    return uz8n_rfind_ucv8(cstr, uz8_len(cstr), target);
}

ptrdiff_t uz8_rfind_ucv8_from(const uc8_t *cstr, ucv8_t target, size_t from) {
    return uz8n_rfind_ucv8_from(cstr, uz8_len(cstr), target, from);
}

ptrdiff_t uz8_rfind_uv8(const uc8_t *cstr, uv8_t target) {
    return uz8n_rfind_uv8(cstr, uz8_len(cstr), target);
}

ptrdiff_t uz8_rfind_uv8_from(const uc8_t *cstr, uv8_t target, size_t from) {
    return uz8n_rfind_uv8_from(cstr, uz8_len(cstr), target, from);
}

ptrdiff_t uz8_rfind_us8(const uc8_t *cstr, const us8_t *target) {
    return uz8n_rfind_us8(cstr, uz8_len(cstr), target);
}

ptrdiff_t uz8_rfind_us8_from(const uc8_t *cstr, const us8_t *target, size_t from) {
    return uz8n_rfind_us8_from(cstr, uz8_len(cstr), target, from);
}

ptrdiff_t uz8n_rfind_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target) {
	return uz8n_rfind_uc8_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz8n_rfind_uc8_from(const uc8_t *cstr, size_t cstr_len, uc8_t target, size_t from) {
    UZXN_RFIND_UCX_FROM(cstr, cstr_len, target, from);
}

ptrdiff_t uz8n_rfind_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
	return uz8n_rfind_uz8_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz8n_rfind_uz8_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t from) {
    return uz8n_rfind_uz8n_from(cstr, cstr_len, target, uz8_len(target), from);
}

ptrdiff_t uz8n_rfind_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
	return uz8n_rfind_uz8n_from(cstr, cstr_len, target, target_len, cstr_len - 1);
}

ptrdiff_t uz8n_rfind_uz8n_from(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len, size_t from) {
    UZXN_RFIND_UZXN_FROM(cstr, cstr_len, target, target_len, from);
}

ptrdiff_t uz8n_rfind_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target) {
	return uz8n_rfind_ucv8_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz8n_rfind_ucv8_from(const uc8_t *cstr, size_t cstr_len, ucv8_t target, size_t from) {
	return uz8n_rfind_uz8n_from(cstr, cstr_len, UCV8_CEXPAND(target), from);
}

ptrdiff_t uz8n_rfind_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target) {
	return uz8n_rfind_uv8_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz8n_rfind_uv8_from(const uc8_t *cstr, size_t cstr_len, uv8_t target, size_t from) {
	return uz8n_rfind_uz8n_from(cstr, cstr_len, UV8_CEXPAND(target), from);
}

ptrdiff_t uz8n_rfind_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target) {
	return uz8n_rfind_us8_from(cstr, cstr_len, target, cstr_len - 1);
}

ptrdiff_t uz8n_rfind_us8_from(const uc8_t *cstr, size_t cstr_len, const us8_t *target, size_t from) {
	return uz8n_rfind_uz8n_from(cstr, cstr_len, US8_CEXPAND(target), from);
}

size_t uz32_erase_uc32(UINOUT uc32_t *cstr, uc32_t target) {
    return uz32_replace_uc32_ucv32(cstr, target, UCV32_EMPTY);
}

size_t uz32_erase_uz32(UINOUT uc32_t *cstr, const uc32_t *target) {
    return uz32_replace_uz32_ucv32(cstr, target, UCV32_EMPTY);
}

size_t uz32_erase_uz32n(UINOUT uc32_t *cstr, const uc32_t *target, size_t target_len) {
    return uz32_replace_uz32n_ucv32(cstr, target, target_len, UCV32_EMPTY);
}

size_t uz32_erase_ucv32(UINOUT uc32_t *cstr, ucv32_t target) {
    return uz32_replace_ucv32_ucv32(cstr, target, UCV32_EMPTY);
}

size_t uz32_erase_uv32(UINOUT uc32_t *cstr, uv32_t target) {
    return uz32_replace_uv32_ucv32(cstr, target, UCV32_EMPTY);
}

size_t uz32_erase_us32(UINOUT uc32_t *cstr, const us32_t *target) {
    return uz32_replace_us32_ucv32(cstr, target, UCV32_EMPTY);
}

size_t uz32n_erase_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t target) {
    return uz32n_replace_uc32_ucv32(cstr, cstr_len, target, UCV32_EMPTY);
}

size_t uz32n_erase_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
    return uz32n_replace_uz32_ucv32(cstr, cstr_len, target, UCV32_EMPTY);
}

size_t uz32n_erase_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
    return uz32n_replace_uz32n_ucv32(cstr, cstr_len, target, target_len, UCV32_EMPTY);
}

size_t uz32n_erase_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t target) {
    return uz32n_replace_ucv32_ucv32(cstr, cstr_len, target, UCV32_EMPTY);
}

size_t uz32n_erase_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t target) {
    return uz32n_replace_uv32_ucv32(cstr, cstr_len, target, UCV32_EMPTY);
}

size_t uz32n_erase_us32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *target) {
    return uz32n_replace_us32_ucv32(cstr, cstr_len, target, UCV32_EMPTY);
}

size_t uz16_erase_uc16(UINOUT uc16_t *cstr, uc16_t target) {
    return uz16_replace_uc16_ucv16(cstr, target, UCV16_EMPTY);
}

size_t uz16_erase_uz16(UINOUT uc16_t *cstr, const uc16_t *target) {
    return uz16_replace_uz16_ucv16(cstr, target, UCV16_EMPTY);
}

size_t uz16_erase_uz16n(UINOUT uc16_t *cstr, const uc16_t *target, size_t target_len) {
    return uz16_replace_uz16n_ucv16(cstr, target, target_len, UCV16_EMPTY);
}

size_t uz16_erase_ucv16(UINOUT uc16_t *cstr, ucv16_t target) {
    return uz16_replace_ucv16_ucv16(cstr, target, UCV16_EMPTY);
}

size_t uz16_erase_uv16(UINOUT uc16_t *cstr, uv16_t target) {
    return uz16_replace_uv16_ucv16(cstr, target, UCV16_EMPTY);
}

size_t uz16_erase_us16(UINOUT uc16_t *cstr, const us16_t *target) {
    return uz16_replace_us16_ucv16(cstr, target, UCV16_EMPTY);
}

size_t uz16n_erase_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t target) {
    return uz16n_replace_uc16_ucv16(cstr, cstr_len, target, UCV16_EMPTY);
}

size_t uz16n_erase_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
    return uz16n_replace_uz16_ucv16(cstr, cstr_len, target, UCV16_EMPTY);
}

size_t uz16n_erase_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
    return uz16n_replace_uz16n_ucv16(cstr, cstr_len, target, target_len, UCV16_EMPTY);
}

size_t uz16n_erase_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t target) {
    return uz16n_replace_ucv16_ucv16(cstr, cstr_len, target, UCV16_EMPTY);
}

size_t uz16n_erase_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t target) {
    return uz16n_replace_uv16_ucv16(cstr, cstr_len, target, UCV16_EMPTY);
}

size_t uz16n_erase_us16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *target) {
    return uz16n_replace_us16_ucv16(cstr, cstr_len, target, UCV16_EMPTY);
}

size_t uz8_erase_uc8(UINOUT uc8_t *cstr, uc8_t target) {
    return uz8_replace_uc8_ucv8(cstr, target, UCV8_EMPTY);
}

size_t uz8_erase_uz8(UINOUT uc8_t *cstr, const uc8_t *target) {
    return uz8_replace_uz8_ucv8(cstr, target, UCV8_EMPTY);
}

size_t uz8_erase_uz8n(UINOUT uc8_t *cstr, const uc8_t *target, size_t target_len) {
    return uz8_replace_uz8n_ucv8(cstr, target, target_len, UCV8_EMPTY);
}

size_t uz8_erase_ucv8(UINOUT uc8_t *cstr, ucv8_t target) {
    return uz8_replace_ucv8_ucv8(cstr, target, UCV8_EMPTY);
}

size_t uz8_erase_uv8(UINOUT uc8_t *cstr, uv8_t target) {
    return uz8_replace_uv8_ucv8(cstr, target, UCV8_EMPTY);
}

size_t uz8_erase_us8(UINOUT uc8_t *cstr, const us8_t *target) {
    return uz8_replace_us8_ucv8(cstr, target, UCV8_EMPTY);
}

size_t uz8n_erase_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t target) {
    return uz8n_replace_uc8_ucv8(cstr, cstr_len, target, UCV8_EMPTY);
}

size_t uz8n_erase_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
    return uz8n_replace_uz8_ucv8(cstr, cstr_len, target, UCV8_EMPTY);
}

size_t uz8n_erase_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
    return uz8n_replace_uz8n_ucv8(cstr, cstr_len, target, target_len, UCV8_EMPTY);
}

size_t uz8n_erase_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t target) {
    return uz8n_replace_ucv8_ucv8(cstr, cstr_len, target, UCV8_EMPTY);
}

size_t uz8n_erase_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t target) {
    return uz8n_replace_uv8_ucv8(cstr, cstr_len, target, UCV8_EMPTY);
}

size_t uz8n_erase_us8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *target) {
    return uz8n_replace_us8_ucv8(cstr, cstr_len, target, UCV8_EMPTY);
}

#define UZX_REPLACE_UCX_UCX(cstr, from, to, X) \
    assert(cstr);                              \
                                               \
    uc##X##_t *begin = cstr;                   \
                                               \
    for (; *cstr; ++cstr)                      \
        if (*cstr == from)                     \
            *cstr = to;                        \
                                               \
    return cstr - begin

#define UZXN_REPLACE_UCX_UCX(cstr, cstr_len, from, to, X)      \
    assert(cstr);                                              \
                                                               \
    for (uc##X##_t *end = cstr + cstr_len; cstr < end; ++cstr) \
        if (*cstr == from)                                     \
            *cstr = to;                                        \
                                                               \
    return cstr_len 
    
#define UZXN_REPLACE_UCX_UZXN(cstr, cstr_len, from, to, to_len, X) \
    assert(cstr && to);                                            \
                                                                   \
    for (size_t i = 0; i < cstr_len;) {                            \
        if (cstr[i] != from) {                                     \
            ++i;                                                   \
            continue;                                              \
        }                                                          \
                                                                   \
        uc##X##_t *cur = cstr + i;                                 \
                                                                   \
        uz##X##_move(cur + to_len, cur + 1, cstr_len - i - 1);     \
        uz##X##_from_uz##X##n(cur, to, to_len);                    \
                                                                   \
        cstr_len += to_len;                                        \
        i        += to_len;                                        \
    }                                                              \
                                                                   \
	return cstr_len
    
#define UZXN_REPLACE_UZXN_UCX(cstr, cstr_len, from, from_len, to, X)                           \
    assert(cstr && from);                                                                      \
                                                                                               \
    if (!from_len)                                                                             \
        return cstr_len;                                                                       \
                                                                                               \
    ptrdiff_t prev_pos = 0;                                                                    \
                                                                                               \
    while (prev_pos < cstr_len) {                                                              \
        ptrdiff_t pos = uz##X##n_find_uz##X##n_from(cstr, cstr_len, from, from_len, prev_pos); \
                                                                                               \
        if (pos < 0)                                                                           \
            break;                                                                             \
                                                                                               \
        uc##X##_t *cur = cstr + pos;                                                           \
                                                                                               \
        uz##X##_move(cur + 1, cur + from_len, cstr_len - pos - from_len);                      \
        *cur = to;                                                                             \
                                                                                               \
        cstr_len -= from_len - 1;                                                              \
        prev_pos  = pos      + 1;                                                              \
    }                                                                                          \
                                                                                               \
    return cstr_len

#define UZXN_REPLACE_UZXN_UZXN(cstr, cstr_len, from, from_len, to, to_len, X)                  \
    assert(cstr && from && to);                                                                \
                                                                                               \
    if (!from_len)                                                                             \
        return cstr_len;                                                                       \
                                                                                               \
    ptrdiff_t len_delta = to_len - from_len;                                                   \
    ptrdiff_t prev_pos  = 0;                                                                   \
                                                                                               \
    while (prev_pos < cstr_len) {                                                              \
        ptrdiff_t pos = uz##X##n_find_uz##X##n_from(cstr, cstr_len, from, from_len, prev_pos); \
                                                                                               \
        if (pos < 0)                                                                           \
            break;                                                                             \
                                                                                               \
        uc##X##_t *cur = cstr + pos;                                                           \
                                                                                               \
        uz##X##_move(cur + to_len, cur + from_len, cstr_len - pos - from_len);                 \
        uz##X##_from_uz##X##n(cur, to, to_len);                                                \
                                                                                               \
        prev_pos  = pos + to_len;                                                              \
        cstr_len += len_delta;                                                                 \
    }                                                                                          \
                                                                                               \
    return cstr_len

size_t uz32_replace_uc32_uc32(UINOUT uc32_t *cstr, uc32_t from, uc32_t to) {
    UZX_REPLACE_UCX_UCX(cstr, from, to, 32);
}

size_t uz32_replace_uc32_uz32(UINOUT uc32_t *cstr, uc32_t from, const uc32_t *to) {
	return uz32_replace_uc32_uz32n(cstr, from, to, uz32_len(to));
}

size_t uz32_replace_uc32_uz32n(UINOUT uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len) {
	return uz32n_replace_uc32_uz32n(cstr, uz32_len(cstr), from, to, to_len);
}

size_t uz32_replace_uc32_ucv32(UINOUT uc32_t *cstr, uc32_t from, ucv32_t to) {
	return uz32_replace_uc32_uz32n(cstr, from, UCV32_CEXPAND(to));
}

size_t uz32_replace_uc32_uv32(UINOUT uc32_t *cstr, uc32_t from, uv32_t to) {
	return uz32_replace_uc32_uz32n(cstr, from, UV32_CEXPAND(to));
}

size_t uz32_replace_uc32_us32(UINOUT uc32_t *cstr, uc32_t from, const us32_t *to) {
	return uz32_replace_uc32_uz32n(cstr, from, US32_CEXPAND(to));
}

size_t uz32_replace_uz32_uc32(UINOUT uc32_t *cstr, const uc32_t *from, uc32_t to) {
	return uz32_replace_uz32n_uc32(cstr, from, uz32_len(from), to);
}

size_t uz32_replace_uz32_uz32(UINOUT uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
	return uz32_replace_uz32n_uz32n(cstr, from, uz32_len(from), to, uz32_len(to));
}

size_t uz32_replace_uz32_uz32n(UINOUT uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len) {
	return uz32_replace_uz32n_uz32n(cstr, from, uz32_len(from), to, to_len);
}

size_t uz32_replace_uz32_ucv32(UINOUT uc32_t *cstr, const uc32_t *from, ucv32_t to) {
	return uz32_replace_uz32n_uz32n(cstr, from, uz32_len(from), UCV32_CEXPAND(to));
}

size_t uz32_replace_uz32_uv32(UINOUT uc32_t *cstr, const uc32_t *from, uv32_t to) {
	return uz32_replace_uz32n_uz32n(cstr, from, uz32_len(from), UV32_CEXPAND(to));
}

size_t uz32_replace_uz32_us32(UINOUT uc32_t *cstr, const uc32_t *from, const us32_t *to) {
	return uz32_replace_uz32n_uz32n(cstr, from, uz32_len(from), US32_CEXPAND(to));
}

size_t uz32_replace_uz32n_uc32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to) {
	return uz32n_replace_uz32n_uc32(cstr, uz32_len(cstr), from, from_len, to);
}

size_t uz32_replace_uz32n_uz32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
	return uz32_replace_uz32n_uz32n(cstr, from, from_len, to, uz32_len(to));
}

size_t uz32_replace_uz32n_uz32n(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
	return uz32n_replace_uz32n_uz32n(cstr, uz32_len(cstr), from, from_len, to, to_len);
}

size_t uz32_replace_uz32n_ucv32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, ucv32_t to) {
	return uz32_replace_uz32n_uz32n(cstr, from, from_len, UCV32_CEXPAND(to));
}

size_t uz32_replace_uz32n_uv32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, uv32_t to) {
	return uz32_replace_uz32n_uz32n(cstr, from, from_len, UV32_CEXPAND(to));
}

size_t uz32_replace_uz32n_us32(UINOUT uc32_t *cstr, const uc32_t *from, size_t from_len, const us32_t *to) {
	return uz32_replace_uz32n_uz32n(cstr, from, from_len, US32_CEXPAND(to));
}

size_t uz32_replace_ucv32_uc32(UINOUT uc32_t *cstr, ucv32_t from, uc32_t to) {
	return uz32_replace_uz32n_uc32(cstr, UCV32_CEXPAND(from), to);
}

size_t uz32_replace_ucv32_uz32(UINOUT uc32_t *cstr, ucv32_t from, const uc32_t *to) {
	return uz32_replace_uz32n_uz32(cstr, UCV32_CEXPAND(from), to);
}

size_t uz32_replace_ucv32_uz32n(UINOUT uc32_t *cstr, ucv32_t from, const uc32_t *to, size_t to_len) {
	return uz32_replace_uz32n_uz32n(cstr, UCV32_CEXPAND(from), to, to_len);
}

size_t uz32_replace_ucv32_ucv32(UINOUT uc32_t *cstr, ucv32_t from, ucv32_t to) {
	return uz32_replace_uz32n_ucv32(cstr, UCV32_CEXPAND(from), to);
}

size_t uz32_replace_ucv32_uv32(UINOUT uc32_t *cstr, ucv32_t from, uv32_t to) {
	return uz32_replace_uz32n_uv32(cstr, UCV32_CEXPAND(from), to);
}

size_t uz32_replace_ucv32_us32(UINOUT uc32_t *cstr, ucv32_t from, const us32_t *to) {
	return uz32_replace_uz32n_us32(cstr, UCV32_CEXPAND(from), to);
}

size_t uz32_replace_uv32_uc32(UINOUT uc32_t *cstr, uv32_t from, uc32_t to) {
	return uz32_replace_uz32n_uc32(cstr, UV32_CEXPAND(from), to);
}

size_t uz32_replace_uv32_uz32(UINOUT uc32_t *cstr, uv32_t from, const uc32_t *to) {
	return uz32_replace_uz32n_uz32(cstr, UV32_CEXPAND(from), to);
}

size_t uz32_replace_uv32_uz32n(UINOUT uc32_t *cstr, uv32_t from, const uc32_t *to, size_t to_len) {
	return uz32_replace_uz32n_uz32n(cstr, UV32_CEXPAND(from), to, to_len);
}

size_t uz32_replace_uv32_ucv32(UINOUT uc32_t *cstr, uv32_t from, ucv32_t to) {
	return uz32_replace_uz32n_ucv32(cstr, UV32_CEXPAND(from), to);
}

size_t uz32_replace_uv32_uv32(UINOUT uc32_t *cstr, uv32_t from, uv32_t to) {
	return uz32_replace_uz32n_uv32(cstr, UV32_CEXPAND(from), to);
}

size_t uz32_replace_uv32_us32(UINOUT uc32_t *cstr, uv32_t from, const us32_t *to) {
	return uz32_replace_uz32n_us32(cstr, UV32_CEXPAND(from), to);
}

size_t uz32_replace_us32_uc32(UINOUT uc32_t *cstr, const us32_t *from, uc32_t to) {
	return uz32_replace_uz32n_uc32(cstr, US32_CEXPAND(from), to);
}

size_t uz32_replace_us32_uz32(UINOUT uc32_t *cstr, const us32_t *from, const uc32_t *to) {
	return uz32_replace_uz32n_uz32(cstr, US32_CEXPAND(from), to);
}

size_t uz32_replace_us32_uz32n(UINOUT uc32_t *cstr, const us32_t *from, const uc32_t *to, size_t to_len) {
	return uz32_replace_uz32n_uz32n(cstr, US32_CEXPAND(from), to, to_len);
}

size_t uz32_replace_us32_ucv32(UINOUT uc32_t *cstr, const us32_t *from, ucv32_t to) {
	return uz32_replace_uz32n_ucv32(cstr, US32_CEXPAND(from), to);
}

size_t uz32_replace_us32_uv32(UINOUT uc32_t *cstr, const us32_t *from, uv32_t to) {
	return uz32_replace_uz32n_uv32(cstr, US32_CEXPAND(from), to);
}

size_t uz32_replace_us32_us32(UINOUT uc32_t *cstr, const us32_t *from, const us32_t *to) {
	return uz32_replace_uz32n_us32(cstr, US32_CEXPAND(from), to);
}

size_t uz32n_replace_uc32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to) {
    UZXN_REPLACE_UCX_UCX(cstr, cstr_len, from, to, 32);
}

size_t uz32n_replace_uc32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
	return uz32n_replace_uc32_uz32n(cstr, cstr_len, from, to, uz32_len(to));
}

size_t uz32n_replace_uc32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len) {
    UZXN_REPLACE_UCX_UZXN(cstr, cstr_len, from, to, to_len, 32);
}

size_t uz32n_replace_uc32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, ucv32_t to) {
	return uz32n_replace_uc32_uz32n(cstr, cstr_len, from, UCV32_CEXPAND(to));
}

size_t uz32n_replace_uc32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, uv32_t to) {
	return uz32n_replace_uc32_uz32n(cstr, cstr_len, from, UV32_CEXPAND(to));
}

size_t uz32n_replace_uc32_us32(UINOUT uc32_t *cstr, size_t cstr_len, uc32_t from, const us32_t *to) {
	return uz32n_replace_uc32_uz32n(cstr, cstr_len, from, US32_CEXPAND(to));
}

size_t uz32n_replace_uz32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to) {
	return uz32n_replace_uz32n_uc32(cstr, cstr_len, from, uz32_len(from), to);
}

size_t uz32n_replace_uz32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, uz32_len(from), to, uz32_len(to));
}

size_t uz32n_replace_uz32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, uz32_len(from), to, to_len);
}

size_t uz32n_replace_uz32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, ucv32_t to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, uz32_len(from), UCV32_CEXPAND(to));
}

size_t uz32n_replace_uz32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, uv32_t to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, uz32_len(from), UV32_CEXPAND(to));
}

size_t uz32n_replace_uz32_us32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, const us32_t *to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, uz32_len(from), US32_CEXPAND(to));
}

size_t uz32n_replace_uz32n_uc32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to) {
    UZXN_REPLACE_UZXN_UCX(cstr, cstr_len, from, from_len, to, 32);
}

size_t uz32n_replace_uz32n_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, from_len, to, uz32_len(to));
}

size_t uz32n_replace_uz32n_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    UZXN_REPLACE_UZXN_UZXN(cstr, cstr_len, from, from_len, to, to_len, 32);
}

size_t uz32n_replace_uz32n_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, ucv32_t to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, from_len, UCV32_CEXPAND(to));
}

size_t uz32n_replace_uz32n_uv32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uv32_t to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, from_len, UV32_CEXPAND(to));
}

size_t uz32n_replace_uz32n_us32(UINOUT uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const us32_t *to) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, from, from_len, US32_CEXPAND(to));
}

size_t uz32n_replace_ucv32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, uc32_t to) {
	return uz32n_replace_uz32n_uc32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replace_ucv32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, const uc32_t *to) {
	return uz32n_replace_uz32n_uz32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replace_ucv32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, const uc32_t *to, size_t to_len) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, UCV32_CEXPAND(from), to, to_len);
}

size_t uz32n_replace_ucv32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, ucv32_t to) {
	return uz32n_replace_uz32n_ucv32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replace_ucv32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, uv32_t to) {
	return uz32n_replace_uz32n_uv32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replace_ucv32_us32(UINOUT uc32_t *cstr, size_t cstr_len, ucv32_t from, const us32_t *to) {
	return uz32n_replace_uz32n_us32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replace_uv32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, uc32_t to) {
	return uz32n_replace_uz32n_uc32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replace_uv32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, const uc32_t *to) {
	return uz32n_replace_uz32n_uz32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replace_uv32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, const uc32_t *to, size_t to_len) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, UV32_CEXPAND(from), to, to_len);
}

size_t uz32n_replace_uv32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, ucv32_t to) {
	return uz32n_replace_uz32n_ucv32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replace_uv32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, uv32_t to) {
	return uz32n_replace_uz32n_uv32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replace_uv32_us32(UINOUT uc32_t *cstr, size_t cstr_len, uv32_t from, const us32_t *to) {
	return uz32n_replace_uz32n_us32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replace_us32_uc32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, uc32_t to) {
	return uz32n_replace_uz32n_uc32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replace_us32_uz32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, const uc32_t *to) {
	return uz32n_replace_uz32n_uz32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replace_us32_uz32n(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, const uc32_t *to, size_t to_len) {
	return uz32n_replace_uz32n_uz32n(cstr, cstr_len, US32_CEXPAND(from), to, to_len);
}

size_t uz32n_replace_us32_ucv32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, ucv32_t to) {
	return uz32n_replace_uz32n_ucv32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replace_us32_uv32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, uv32_t to) {
	return uz32n_replace_uz32n_uv32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replace_us32_us32(UINOUT uc32_t *cstr, size_t cstr_len, const us32_t *from, const us32_t *to) {
	return uz32n_replace_uz32n_us32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz16_replace_uc16_uc16(UINOUT uc16_t *cstr, uc16_t from, uc16_t to) {
    UZX_REPLACE_UCX_UCX(cstr, from, to, 16);
}

size_t uz16_replace_uc16_uz16(UINOUT uc16_t *cstr, uc16_t from, const uc16_t *to) {
	return uz16_replace_uc16_uz16n(cstr, from, to, uz16_len(to));
}

size_t uz16_replace_uc16_uz16n(UINOUT uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len) {
	return uz16n_replace_uc16_uz16n(cstr, uz16_len(cstr), from, to, to_len);
}

size_t uz16_replace_uc16_ucv16(UINOUT uc16_t *cstr, uc16_t from, ucv16_t to) {
	return uz16_replace_uc16_uz16n(cstr, from, UCV16_CEXPAND(to));
}

size_t uz16_replace_uc16_uv16(UINOUT uc16_t *cstr, uc16_t from, uv16_t to) {
	return uz16_replace_uc16_uz16n(cstr, from, UV16_CEXPAND(to));
}

size_t uz16_replace_uc16_us16(UINOUT uc16_t *cstr, uc16_t from, const us16_t *to) {
	return uz16_replace_uc16_uz16n(cstr, from, US16_CEXPAND(to));
}

size_t uz16_replace_uz16_uc16(UINOUT uc16_t *cstr, const uc16_t *from, uc16_t to) {
	return uz16_replace_uz16n_uc16(cstr, from, uz16_len(from), to);
}

size_t uz16_replace_uz16_uz16(UINOUT uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
	return uz16_replace_uz16n_uz16n(cstr, from, uz16_len(from), to, uz16_len(to));
}

size_t uz16_replace_uz16_uz16n(UINOUT uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len) {
	return uz16_replace_uz16n_uz16n(cstr, from, uz16_len(from), to, to_len);
}

size_t uz16_replace_uz16_ucv16(UINOUT uc16_t *cstr, const uc16_t *from, ucv16_t to) {
	return uz16_replace_uz16n_uz16n(cstr, from, uz16_len(from), UCV16_CEXPAND(to));
}

size_t uz16_replace_uz16_uv16(UINOUT uc16_t *cstr, const uc16_t *from, uv16_t to) {
	return uz16_replace_uz16n_uz16n(cstr, from, uz16_len(from), UV16_CEXPAND(to));
}

size_t uz16_replace_uz16_us16(UINOUT uc16_t *cstr, const uc16_t *from, const us16_t *to) {
	return uz16_replace_uz16n_uz16n(cstr, from, uz16_len(from), US16_CEXPAND(to));
}

size_t uz16_replace_uz16n_uc16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to) {
	return uz16n_replace_uz16n_uc16(cstr, uz16_len(cstr), from, from_len, to);
}

size_t uz16_replace_uz16n_uz16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
	return uz16_replace_uz16n_uz16n(cstr, from, from_len, to, uz16_len(to));
}

size_t uz16_replace_uz16n_uz16n(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
	return uz16n_replace_uz16n_uz16n(cstr, uz16_len(cstr), from, from_len, to, to_len);
}

size_t uz16_replace_uz16n_ucv16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, ucv16_t to) {
	return uz16_replace_uz16n_uz16n(cstr, from, from_len, UCV16_CEXPAND(to));
}

size_t uz16_replace_uz16n_uv16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, uv16_t to) {
	return uz16_replace_uz16n_uz16n(cstr, from, from_len, UV16_CEXPAND(to));
}

size_t uz16_replace_uz16n_us16(UINOUT uc16_t *cstr, const uc16_t *from, size_t from_len, const us16_t *to) {
	return uz16_replace_uz16n_uz16n(cstr, from, from_len, US16_CEXPAND(to));
}

size_t uz16_replace_ucv16_uc16(UINOUT uc16_t *cstr, ucv16_t from, uc16_t to) {
	return uz16_replace_uz16n_uc16(cstr, UCV16_CEXPAND(from), to);
}

size_t uz16_replace_ucv16_uz16(UINOUT uc16_t *cstr, ucv16_t from, const uc16_t *to) {
	return uz16_replace_uz16n_uz16(cstr, UCV16_CEXPAND(from), to);
}

size_t uz16_replace_ucv16_uz16n(UINOUT uc16_t *cstr, ucv16_t from, const uc16_t *to, size_t to_len) {
	return uz16_replace_uz16n_uz16n(cstr, UCV16_CEXPAND(from), to, to_len);
}

size_t uz16_replace_ucv16_ucv16(UINOUT uc16_t *cstr, ucv16_t from, ucv16_t to) {
	return uz16_replace_uz16n_ucv16(cstr, UCV16_CEXPAND(from), to);
}

size_t uz16_replace_ucv16_uv16(UINOUT uc16_t *cstr, ucv16_t from, uv16_t to) {
	return uz16_replace_uz16n_uv16(cstr, UCV16_CEXPAND(from), to);
}

size_t uz16_replace_ucv16_us16(UINOUT uc16_t *cstr, ucv16_t from, const us16_t *to) {
	return uz16_replace_uz16n_us16(cstr, UCV16_CEXPAND(from), to);
}

size_t uz16_replace_uv16_uc16(UINOUT uc16_t *cstr, uv16_t from, uc16_t to) {
	return uz16_replace_uz16n_uc16(cstr, UV16_CEXPAND(from), to);
}

size_t uz16_replace_uv16_uz16(UINOUT uc16_t *cstr, uv16_t from, const uc16_t *to) {
	return uz16_replace_uz16n_uz16(cstr, UV16_CEXPAND(from), to);
}

size_t uz16_replace_uv16_uz16n(UINOUT uc16_t *cstr, uv16_t from, const uc16_t *to, size_t to_len) {
	return uz16_replace_uz16n_uz16n(cstr, UV16_CEXPAND(from), to, to_len);
}

size_t uz16_replace_uv16_ucv16(UINOUT uc16_t *cstr, uv16_t from, ucv16_t to) {
	return uz16_replace_uz16n_ucv16(cstr, UV16_CEXPAND(from), to);
}

size_t uz16_replace_uv16_uv16(UINOUT uc16_t *cstr, uv16_t from, uv16_t to) {
	return uz16_replace_uz16n_uv16(cstr, UV16_CEXPAND(from), to);
}

size_t uz16_replace_uv16_us16(UINOUT uc16_t *cstr, uv16_t from, const us16_t *to) {
	return uz16_replace_uz16n_us16(cstr, UV16_CEXPAND(from), to);
}

size_t uz16_replace_us16_uc16(UINOUT uc16_t *cstr, const us16_t *from, uc16_t to) {
	return uz16_replace_uz16n_uc16(cstr, US16_CEXPAND(from), to);
}

size_t uz16_replace_us16_uz16(UINOUT uc16_t *cstr, const us16_t *from, const uc16_t *to) {
	return uz16_replace_uz16n_uz16(cstr, US16_CEXPAND(from), to);
}

size_t uz16_replace_us16_uz16n(UINOUT uc16_t *cstr, const us16_t *from, const uc16_t *to, size_t to_len) {
	return uz16_replace_uz16n_uz16n(cstr, US16_CEXPAND(from), to, to_len);
}

size_t uz16_replace_us16_ucv16(UINOUT uc16_t *cstr, const us16_t *from, ucv16_t to) {
	return uz16_replace_uz16n_ucv16(cstr, US16_CEXPAND(from), to);
}

size_t uz16_replace_us16_uv16(UINOUT uc16_t *cstr, const us16_t *from, uv16_t to) {
	return uz16_replace_uz16n_uv16(cstr, US16_CEXPAND(from), to);
}

size_t uz16_replace_us16_us16(UINOUT uc16_t *cstr, const us16_t *from, const us16_t *to) {
	return uz16_replace_uz16n_us16(cstr, US16_CEXPAND(from), to);
}

size_t uz16n_replace_uc16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to) {
    UZXN_REPLACE_UCX_UCX(cstr, cstr_len, from, to, 16);
}

size_t uz16n_replace_uc16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
	return uz16n_replace_uc16_uz16n(cstr, cstr_len, from, to, uz16_len(to));
}

size_t uz16n_replace_uc16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len) {
    UZXN_REPLACE_UCX_UZXN(cstr, cstr_len, from, to, to_len, 16);
}

size_t uz16n_replace_uc16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, ucv16_t to) {
	return uz16n_replace_uc16_uz16n(cstr, cstr_len, from, UCV16_CEXPAND(to));
}

size_t uz16n_replace_uc16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, uv16_t to) {
	return uz16n_replace_uc16_uz16n(cstr, cstr_len, from, UV16_CEXPAND(to));
}

size_t uz16n_replace_uc16_us16(UINOUT uc16_t *cstr, size_t cstr_len, uc16_t from, const us16_t *to) {
	return uz16n_replace_uc16_uz16n(cstr, cstr_len, from, US16_CEXPAND(to));
}

size_t uz16n_replace_uz16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to) {
	return uz16n_replace_uz16n_uc16(cstr, cstr_len, from, uz16_len(from), to);
}

size_t uz16n_replace_uz16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, uz16_len(from), to, uz16_len(to));
}

size_t uz16n_replace_uz16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, uz16_len(from), to, to_len);
}

size_t uz16n_replace_uz16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, ucv16_t to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, uz16_len(from), UCV16_CEXPAND(to));
}

size_t uz16n_replace_uz16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, uv16_t to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, uz16_len(from), UV16_CEXPAND(to));
}

size_t uz16n_replace_uz16_us16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, const us16_t *to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, uz16_len(from), US16_CEXPAND(to));
}

size_t uz16n_replace_uz16n_uc16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to) {
    UZXN_REPLACE_UZXN_UCX(cstr, cstr_len, from, from_len, to, 16);
}

size_t uz16n_replace_uz16n_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, from_len, to, uz16_len(to));
}

size_t uz16n_replace_uz16n_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    UZXN_REPLACE_UZXN_UZXN(cstr, cstr_len, from, from_len, to, to_len, 16);
}

size_t uz16n_replace_uz16n_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, ucv16_t to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, from_len, UCV16_CEXPAND(to));
}

size_t uz16n_replace_uz16n_uv16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uv16_t to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, from_len, UV16_CEXPAND(to));
}

size_t uz16n_replace_uz16n_us16(UINOUT uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const us16_t *to) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, from, from_len, US16_CEXPAND(to));
}

size_t uz16n_replace_ucv16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, uc16_t to) {
	return uz16n_replace_uz16n_uc16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replace_ucv16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, const uc16_t *to) {
	return uz16n_replace_uz16n_uz16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replace_ucv16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, const uc16_t *to, size_t to_len) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, UCV16_CEXPAND(from), to, to_len);
}

size_t uz16n_replace_ucv16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, ucv16_t to) {
	return uz16n_replace_uz16n_ucv16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replace_ucv16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, uv16_t to) {
	return uz16n_replace_uz16n_uv16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replace_ucv16_us16(UINOUT uc16_t *cstr, size_t cstr_len, ucv16_t from, const us16_t *to) {
	return uz16n_replace_uz16n_us16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replace_uv16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, uc16_t to) {
	return uz16n_replace_uz16n_uc16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replace_uv16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, const uc16_t *to) {
	return uz16n_replace_uz16n_uz16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replace_uv16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, const uc16_t *to, size_t to_len) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, UV16_CEXPAND(from), to, to_len);
}

size_t uz16n_replace_uv16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, ucv16_t to) {
	return uz16n_replace_uz16n_ucv16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replace_uv16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, uv16_t to) {
	return uz16n_replace_uz16n_uv16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replace_uv16_us16(UINOUT uc16_t *cstr, size_t cstr_len, uv16_t from, const us16_t *to) {
	return uz16n_replace_uz16n_us16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replace_us16_uc16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, uc16_t to) {
	return uz16n_replace_uz16n_uc16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replace_us16_uz16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, const uc16_t *to) {
	return uz16n_replace_uz16n_uz16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replace_us16_uz16n(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, const uc16_t *to, size_t to_len) {
	return uz16n_replace_uz16n_uz16n(cstr, cstr_len, US16_CEXPAND(from), to, to_len);
}

size_t uz16n_replace_us16_ucv16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, ucv16_t to) {
	return uz16n_replace_uz16n_ucv16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replace_us16_uv16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, uv16_t to) {
	return uz16n_replace_uz16n_uv16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replace_us16_us16(UINOUT uc16_t *cstr, size_t cstr_len, const us16_t *from, const us16_t *to) {
	return uz16n_replace_uz16n_us16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz8_replace_uc8_uc8(UINOUT uc8_t *cstr, uc8_t from, uc8_t to) {
    UZX_REPLACE_UCX_UCX(cstr, from, to, 8);
}

size_t uz8_replace_uc8_uz8(UINOUT uc8_t *cstr, uc8_t from, const uc8_t *to) {
	return uz8_replace_uc8_uz8n(cstr, from, to, uz8_len(to));
}

size_t uz8_replace_uc8_uz8n(UINOUT uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len) {
	return uz8n_replace_uc8_uz8n(cstr, uz8_len(cstr), from, to, to_len);
}

size_t uz8_replace_uc8_ucv8(UINOUT uc8_t *cstr, uc8_t from, ucv8_t to) {
	return uz8_replace_uc8_uz8n(cstr, from, UCV8_CEXPAND(to));
}

size_t uz8_replace_uc8_uv8(UINOUT uc8_t *cstr, uc8_t from, uv8_t to) {
	return uz8_replace_uc8_uz8n(cstr, from, UV8_CEXPAND(to));
}

size_t uz8_replace_uc8_us8(UINOUT uc8_t *cstr, uc8_t from, const us8_t *to) {
	return uz8_replace_uc8_uz8n(cstr, from, US8_CEXPAND(to));
}

size_t uz8_replace_uz8_uc8(UINOUT uc8_t *cstr, const uc8_t *from, uc8_t to) {
	return uz8_replace_uz8n_uc8(cstr, from, uz8_len(from), to);
}

size_t uz8_replace_uz8_uz8(UINOUT uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
	return uz8_replace_uz8n_uz8n(cstr, from, uz8_len(from), to, uz8_len(to));
}

size_t uz8_replace_uz8_uz8n(UINOUT uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len) {
	return uz8_replace_uz8n_uz8n(cstr, from, uz8_len(from), to, to_len);
}

size_t uz8_replace_uz8_ucv8(UINOUT uc8_t *cstr, const uc8_t *from, ucv8_t to) {
	return uz8_replace_uz8n_uz8n(cstr, from, uz8_len(from), UCV8_CEXPAND(to));
}

size_t uz8_replace_uz8_uv8(UINOUT uc8_t *cstr, const uc8_t *from, uv8_t to) {
	return uz8_replace_uz8n_uz8n(cstr, from, uz8_len(from), UV8_CEXPAND(to));
}

size_t uz8_replace_uz8_us8(UINOUT uc8_t *cstr, const uc8_t *from, const us8_t *to) {
	return uz8_replace_uz8n_uz8n(cstr, from, uz8_len(from), US8_CEXPAND(to));
}

size_t uz8_replace_uz8n_uc8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to) {
	return uz8n_replace_uz8n_uc8(cstr, uz8_len(cstr), from, from_len, to);
}

size_t uz8_replace_uz8n_uz8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
	return uz8_replace_uz8n_uz8n(cstr, from, from_len, to, uz8_len(to));
}

size_t uz8_replace_uz8n_uz8n(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
	return uz8n_replace_uz8n_uz8n(cstr, uz8_len(cstr), from, from_len, to, to_len);
}

size_t uz8_replace_uz8n_ucv8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, ucv8_t to) {
	return uz8_replace_uz8n_uz8n(cstr, from, from_len, UCV8_CEXPAND(to));
}

size_t uz8_replace_uz8n_uv8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, uv8_t to) {
	return uz8_replace_uz8n_uz8n(cstr, from, from_len, UV8_CEXPAND(to));
}

size_t uz8_replace_uz8n_us8(UINOUT uc8_t *cstr, const uc8_t *from, size_t from_len, const us8_t *to) {
	return uz8_replace_uz8n_uz8n(cstr, from, from_len, US8_CEXPAND(to));
}

size_t uz8_replace_ucv8_uc8(UINOUT uc8_t *cstr, ucv8_t from, uc8_t to) {
	return uz8_replace_uz8n_uc8(cstr, UCV8_CEXPAND(from), to);
}

size_t uz8_replace_ucv8_uz8(UINOUT uc8_t *cstr, ucv8_t from, const uc8_t *to) {
	return uz8_replace_uz8n_uz8(cstr, UCV8_CEXPAND(from), to);
}

size_t uz8_replace_ucv8_uz8n(UINOUT uc8_t *cstr, ucv8_t from, const uc8_t *to, size_t to_len) {
	return uz8_replace_uz8n_uz8n(cstr, UCV8_CEXPAND(from), to, to_len);
}

size_t uz8_replace_ucv8_ucv8(UINOUT uc8_t *cstr, ucv8_t from, ucv8_t to) {
	return uz8_replace_uz8n_ucv8(cstr, UCV8_CEXPAND(from), to);
}

size_t uz8_replace_ucv8_uv8(UINOUT uc8_t *cstr, ucv8_t from, uv8_t to) {
	return uz8_replace_uz8n_uv8(cstr, UCV8_CEXPAND(from), to);
}

size_t uz8_replace_ucv8_us8(UINOUT uc8_t *cstr, ucv8_t from, const us8_t *to) {
	return uz8_replace_uz8n_us8(cstr, UCV8_CEXPAND(from), to);
}

size_t uz8_replace_uv8_uc8(UINOUT uc8_t *cstr, uv8_t from, uc8_t to) {
	return uz8_replace_uz8n_uc8(cstr, UV8_CEXPAND(from), to);
}

size_t uz8_replace_uv8_uz8(UINOUT uc8_t *cstr, uv8_t from, const uc8_t *to) {
	return uz8_replace_uz8n_uz8(cstr, UV8_CEXPAND(from), to);
}

size_t uz8_replace_uv8_uz8n(UINOUT uc8_t *cstr, uv8_t from, const uc8_t *to, size_t to_len) {
	return uz8_replace_uz8n_uz8n(cstr, UV8_CEXPAND(from), to, to_len);
}

size_t uz8_replace_uv8_ucv8(UINOUT uc8_t *cstr, uv8_t from, ucv8_t to) {
	return uz8_replace_uz8n_ucv8(cstr, UV8_CEXPAND(from), to);
}

size_t uz8_replace_uv8_uv8(UINOUT uc8_t *cstr, uv8_t from, uv8_t to) {
	return uz8_replace_uz8n_uv8(cstr, UV8_CEXPAND(from), to);
}

size_t uz8_replace_uv8_us8(UINOUT uc8_t *cstr, uv8_t from, const us8_t *to) {
	return uz8_replace_uz8n_us8(cstr, UV8_CEXPAND(from), to);
}

size_t uz8_replace_us8_uc8(UINOUT uc8_t *cstr, const us8_t *from, uc8_t to) {
	return uz8_replace_uz8n_uc8(cstr, US8_CEXPAND(from), to);
}

size_t uz8_replace_us8_uz8(UINOUT uc8_t *cstr, const us8_t *from, const uc8_t *to) {
	return uz8_replace_uz8n_uz8(cstr, US8_CEXPAND(from), to);
}

size_t uz8_replace_us8_uz8n(UINOUT uc8_t *cstr, const us8_t *from, const uc8_t *to, size_t to_len) {
	return uz8_replace_uz8n_uz8n(cstr, US8_CEXPAND(from), to, to_len);
}

size_t uz8_replace_us8_ucv8(UINOUT uc8_t *cstr, const us8_t *from, ucv8_t to) {
	return uz8_replace_uz8n_ucv8(cstr, US8_CEXPAND(from), to);
}

size_t uz8_replace_us8_uv8(UINOUT uc8_t *cstr, const us8_t *from, uv8_t to) {
	return uz8_replace_uz8n_uv8(cstr, US8_CEXPAND(from), to);
}

size_t uz8_replace_us8_us8(UINOUT uc8_t *cstr, const us8_t *from, const us8_t *to) {
	return uz8_replace_uz8n_us8(cstr, US8_CEXPAND(from), to);
}

size_t uz8n_replace_uc8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to) {
    UZXN_REPLACE_UCX_UCX(cstr, cstr_len, from, to, 8);
}

size_t uz8n_replace_uc8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
	return uz8n_replace_uc8_uz8n(cstr, cstr_len, from, to, uz8_len(to));
}

size_t uz8n_replace_uc8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len) {
    UZXN_REPLACE_UCX_UZXN(cstr, cstr_len, from, to, to_len, 8);
}

size_t uz8n_replace_uc8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, ucv8_t to) {
	return uz8n_replace_uc8_uz8n(cstr, cstr_len, from, UCV8_CEXPAND(to));
}

size_t uz8n_replace_uc8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, uv8_t to) {
	return uz8n_replace_uc8_uz8n(cstr, cstr_len, from, UV8_CEXPAND(to));
}

size_t uz8n_replace_uc8_us8(UINOUT uc8_t *cstr, size_t cstr_len, uc8_t from, const us8_t *to) {
	return uz8n_replace_uc8_uz8n(cstr, cstr_len, from, US8_CEXPAND(to));
}

size_t uz8n_replace_uz8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to) {
	return uz8n_replace_uz8n_uc8(cstr, cstr_len, from, uz8_len(from), to);
}

size_t uz8n_replace_uz8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, uz8_len(from), to, uz8_len(to));
}

size_t uz8n_replace_uz8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, uz8_len(from), to, to_len);
}

size_t uz8n_replace_uz8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, ucv8_t to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, uz8_len(from), UCV8_CEXPAND(to));
}

size_t uz8n_replace_uz8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, uv8_t to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, uz8_len(from), UV8_CEXPAND(to));
}

size_t uz8n_replace_uz8_us8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, const us8_t *to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, uz8_len(from), US8_CEXPAND(to));
}

size_t uz8n_replace_uz8n_uc8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to) {
    UZXN_REPLACE_UZXN_UCX(cstr, cstr_len, from, from_len, to, 8);
}

size_t uz8n_replace_uz8n_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, from_len, to, uz8_len(to));
}

size_t uz8n_replace_uz8n_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    UZXN_REPLACE_UZXN_UZXN(cstr, cstr_len, from, from_len, to, to_len, 8);
}

size_t uz8n_replace_uz8n_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, ucv8_t to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, from_len, UCV8_CEXPAND(to));
}

size_t uz8n_replace_uz8n_uv8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uv8_t to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, from_len, UV8_CEXPAND(to));
}

size_t uz8n_replace_uz8n_us8(UINOUT uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const us8_t *to) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, from, from_len, US8_CEXPAND(to));
}

size_t uz8n_replace_ucv8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, uc8_t to) {
	return uz8n_replace_uz8n_uc8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replace_ucv8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, const uc8_t *to) {
	return uz8n_replace_uz8n_uz8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replace_ucv8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, const uc8_t *to, size_t to_len) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, UCV8_CEXPAND(from), to, to_len);
}

size_t uz8n_replace_ucv8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, ucv8_t to) {
	return uz8n_replace_uz8n_ucv8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replace_ucv8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, uv8_t to) {
	return uz8n_replace_uz8n_uv8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replace_ucv8_us8(UINOUT uc8_t *cstr, size_t cstr_len, ucv8_t from, const us8_t *to) {
	return uz8n_replace_uz8n_us8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replace_uv8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, uc8_t to) {
	return uz8n_replace_uz8n_uc8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replace_uv8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, const uc8_t *to) {
	return uz8n_replace_uz8n_uz8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replace_uv8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, const uc8_t *to, size_t to_len) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, UV8_CEXPAND(from), to, to_len);
}

size_t uz8n_replace_uv8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, ucv8_t to) {
	return uz8n_replace_uz8n_ucv8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replace_uv8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, uv8_t to) {
	return uz8n_replace_uz8n_uv8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replace_uv8_us8(UINOUT uc8_t *cstr, size_t cstr_len, uv8_t from, const us8_t *to) {
	return uz8n_replace_uz8n_us8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replace_us8_uc8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, uc8_t to) {
	return uz8n_replace_uz8n_uc8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replace_us8_uz8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, const uc8_t *to) {
	return uz8n_replace_uz8n_uz8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replace_us8_uz8n(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, const uc8_t *to, size_t to_len) {
	return uz8n_replace_uz8n_uz8n(cstr, cstr_len, US8_CEXPAND(from), to, to_len);
}

size_t uz8n_replace_us8_ucv8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, ucv8_t to) {
	return uz8n_replace_uz8n_ucv8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replace_us8_uv8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, uv8_t to) {
	return uz8n_replace_uz8n_uv8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replace_us8_us8(UINOUT uc8_t *cstr, size_t cstr_len, const us8_t *from, const us8_t *to) {
	return uz8n_replace_uz8n_us8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz32_replaced_len_uc32_uc32(const uc32_t *cstr, uc32_t from, uc32_t to) {
    return uz32n_replaced_len_uc32_uc32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uc32_uz32(const uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uc32_uz32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uc32_uz32n(const uc32_t *cstr, uc32_t from, size_t to_len) {
    return uz32n_replaced_len_uc32_uz32n(cstr, uz32_len(cstr), from, to_len);
}

size_t uz32_replaced_len_uc32_ucv32(const uc32_t *cstr, uc32_t from, ucv32_t to) {
    return uz32n_replaced_len_uc32_ucv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uc32_uv32(const uc32_t *cstr, uc32_t from, uv32_t to) {
    return uz32n_replaced_len_uc32_uv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uc32_us32(const uc32_t *cstr, uc32_t from, const us32_t *to) {
    return uz32n_replaced_len_uc32_us32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uz32_uc32(const uc32_t *cstr, const uc32_t *from, uc32_t to) {
    return uz32n_replaced_len_uz32_uc32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uz32_uz32(const uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_uz32_uz32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uz32_uz32n(const uc32_t *cstr, const uc32_t *from, size_t to_len) {
    return uz32n_replaced_len_uz32_uz32n(cstr, uz32_len(cstr), from, to_len);
}

size_t uz32_replaced_len_uz32_ucv32(const uc32_t *cstr, const uc32_t *from, ucv32_t to) {
    return uz32n_replaced_len_uz32_ucv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uz32_uv32(const uc32_t *cstr, const uc32_t *from, uv32_t to) {
    return uz32n_replaced_len_uz32_uv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uz32_us32(const uc32_t *cstr, const uc32_t *from, const us32_t *to) {
    return uz32n_replaced_len_uz32_us32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uz32n_uc32(const uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32n_replaced_len_uz32n_uc32(cstr, uz32_len(cstr), from, from_len, to);
}

size_t uz32_replaced_len_uz32n_uz32(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32n_replaced_len_uz32n_uz32(cstr, uz32_len(cstr), from, from_len, to);
}

size_t uz32_replaced_len_uz32n_uz32n(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32n_replaced_len_uz32n_uz32n(cstr, uz32_len(cstr), from, from_len, to_len);
}

size_t uz32_replaced_len_uz32n_ucv32(const uc32_t *cstr, const uc32_t *from, size_t from_len, ucv32_t to) {
    return uz32n_replaced_len_uz32n_ucv32(cstr, uz32_len(cstr), from, from_len, to);
}

size_t uz32_replaced_len_uz32n_uv32(const uc32_t *cstr, const uc32_t *from, size_t from_len, uv32_t to) {
    return uz32n_replaced_len_uz32n_uv32(cstr, uz32_len(cstr), from, from_len, to);
}

size_t uz32_replaced_len_uz32n_us32(const uc32_t *cstr, const uc32_t *from, size_t from_len, const us32_t *to) {
    return uz32n_replaced_len_uz32n_us32(cstr, uz32_len(cstr), from, from_len, to);
}

size_t uz32_replaced_len_ucv32_uc32(const uc32_t *cstr, ucv32_t from, uc32_t to) {
    return uz32n_replaced_len_ucv32_uc32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_ucv32_uz32(const uc32_t *cstr, ucv32_t from, const uc32_t *to) {
    return uz32n_replaced_len_ucv32_uz32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_ucv32_uz32n(const uc32_t *cstr, ucv32_t from, size_t to_len) {
    return uz32n_replaced_len_ucv32_uz32n(cstr, uz32_len(cstr), from, to_len);
}

size_t uz32_replaced_len_ucv32_ucv32(const uc32_t *cstr, ucv32_t from, ucv32_t to) {
    return uz32n_replaced_len_ucv32_ucv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_ucv32_uv32(const uc32_t *cstr, ucv32_t from, uv32_t to) {
    return uz32n_replaced_len_ucv32_uv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_ucv32_us32(const uc32_t *cstr, ucv32_t from, const us32_t *to) {
    return uz32n_replaced_len_ucv32_us32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uv32_uc32(const uc32_t *cstr, uv32_t from, uc32_t to) {
    return uz32n_replaced_len_uv32_uc32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uv32_uz32(const uc32_t *cstr, uv32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uv32_uz32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uv32_uz32n(const uc32_t *cstr, uv32_t from, size_t to_len) {
    return uz32n_replaced_len_uv32_uz32n(cstr, uz32_len(cstr), from, to_len);
}

size_t uz32_replaced_len_uv32_ucv32(const uc32_t *cstr, uv32_t from, ucv32_t to) {
    return uz32n_replaced_len_uv32_ucv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uv32_uv32(const uc32_t *cstr, uv32_t from, uv32_t to) {
    return uz32n_replaced_len_uv32_uv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_uv32_us32(const uc32_t *cstr, uv32_t from, const us32_t *to) {
    return uz32n_replaced_len_uv32_us32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_us32_uc32(const uc32_t *cstr, const us32_t *from, uc32_t to) {
    return uz32n_replaced_len_us32_uc32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_us32_uz32(const uc32_t *cstr, const us32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_us32_uz32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_us32_uz32n(const uc32_t *cstr, const us32_t *from, size_t to_len) {
    return uz32n_replaced_len_us32_uz32n(cstr, uz32_len(cstr), from, to_len);
}

size_t uz32_replaced_len_us32_ucv32(const uc32_t *cstr, const us32_t *from, ucv32_t to) {
    return uz32n_replaced_len_us32_ucv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_us32_uv32(const uc32_t *cstr, const us32_t *from, uv32_t to) {
    return uz32n_replaced_len_us32_uv32(cstr, uz32_len(cstr), from, to);
}

size_t uz32_replaced_len_us32_us32(const uc32_t *cstr, const us32_t *from, const us32_t *to) {
    return uz32n_replaced_len_us32_us32(cstr, uz32_len(cstr), from, to);
}

size_t uz32n_replaced_len_uc32_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to) {
    assert(cstr);
    return cstr_len;
}

size_t uz32n_replaced_len_uc32_uz32(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32n_replaced_len_uc32_uz32n(cstr, cstr_len, from, uz32_len(to));
}

size_t uz32n_replaced_len_uc32_uz32n(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len) {
    size_t count = uz32n_count_uc32(cstr, cstr_len, from);
    return cstr_len - count + count * to_len;
}

size_t uz32n_replaced_len_uc32_ucv32(const uc32_t *cstr, size_t cstr_len, uc32_t from, ucv32_t to) {
	return uz32n_replaced_len_uc32_uz32n(cstr, cstr_len, from, ucv32_len(to));
}

size_t uz32n_replaced_len_uc32_uv32(const uc32_t *cstr, size_t cstr_len, uc32_t from, uv32_t to) {
	return uz32n_replaced_len_uc32_uz32n(cstr, cstr_len, from, uv32_len(to));
}

size_t uz32n_replaced_len_uc32_us32(const uc32_t *cstr, size_t cstr_len, uc32_t from, const us32_t *to) {
	return uz32n_replaced_len_uc32_uz32n(cstr, cstr_len, from, us32_len(to));
}

size_t uz32n_replaced_len_uz32_uc32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to) {
    return uz32n_replaced_len_uz32n_uc32(cstr, cstr_len, from, uz32_len(from), to);
}

size_t uz32n_replaced_len_uz32_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32n_replaced_len_uz32n_uz32(cstr, cstr_len, from, uz32_len(from), to);
}

size_t uz32n_replaced_len_uz32_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len) {
    return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, from, uz32_len(from), to_len);
}

size_t uz32n_replaced_len_uz32_ucv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, ucv32_t to) {
    return uz32n_replaced_len_uz32n_ucv32(cstr, cstr_len, from, uz32_len(from), to);
}

size_t uz32n_replaced_len_uz32_uv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, uv32_t to) {
    return uz32n_replaced_len_uz32n_uv32(cstr, cstr_len, from, uz32_len(from), to);
}

size_t uz32n_replaced_len_uz32_us32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const us32_t *to) {
    return uz32n_replaced_len_uz32n_us32(cstr, cstr_len, from, uz32_len(from), to);
}

size_t uz32n_replaced_len_uz32n_uc32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to) {
    size_t count = uz32n_count_uz32n(cstr, cstr_len, from, from_len);
    return cstr_len - from_len * count + count;
}

size_t uz32n_replaced_len_uz32n_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, from, from_len, uz32_len(to));
}

size_t uz32n_replaced_len_uz32n_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len) {
    size_t count = uz32n_count_uz32n(cstr, cstr_len, from, from_len);
    return cstr_len - from_len * count + to_len * count;
}

size_t uz32n_replaced_len_uz32n_ucv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, ucv32_t to) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, from, from_len, ucv32_len(to));
}

size_t uz32n_replaced_len_uz32n_uv32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uv32_t to) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, from, from_len, uv32_len(to));
}

size_t uz32n_replaced_len_uz32n_us32(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const us32_t *to) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, from, from_len, us32_len(to));
}

size_t uz32n_replaced_len_ucv32_uc32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, uc32_t to) {
	return uz32n_replaced_len_uz32n_uc32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_ucv32_uz32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, const uc32_t *to) {
	return uz32n_replaced_len_uz32n_uz32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_ucv32_uz32n(const uc32_t *cstr, size_t cstr_len, ucv32_t from, size_t to_len) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, UCV32_CEXPAND(from), to_len);
}

size_t uz32n_replaced_len_ucv32_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, ucv32_t to) {
	return uz32n_replaced_len_uz32n_ucv32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_ucv32_uv32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, uv32_t to) {
	return uz32n_replaced_len_uz32n_uv32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_ucv32_us32(const uc32_t *cstr, size_t cstr_len, ucv32_t from, const us32_t *to) {
	return uz32n_replaced_len_uz32n_us32(cstr, cstr_len, UCV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_uv32_uc32(const uc32_t *cstr, size_t cstr_len, uv32_t from, uc32_t to) {
	return uz32n_replaced_len_uz32n_uc32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_uv32_uz32(const uc32_t *cstr, size_t cstr_len, uv32_t from, const uc32_t *to) {
	return uz32n_replaced_len_uz32n_uz32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_uv32_uz32n(const uc32_t *cstr, size_t cstr_len, uv32_t from, size_t to_len) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, UV32_CEXPAND(from), to_len);
}

size_t uz32n_replaced_len_uv32_ucv32(const uc32_t *cstr, size_t cstr_len, uv32_t from, ucv32_t to) {
	return uz32n_replaced_len_uz32n_ucv32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_uv32_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t from, uv32_t to) {
	return uz32n_replaced_len_uz32n_uv32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_uv32_us32(const uc32_t *cstr, size_t cstr_len, uv32_t from, const us32_t *to) {
	return uz32n_replaced_len_uz32n_us32(cstr, cstr_len, UV32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_us32_uc32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, uc32_t to) {
	return uz32n_replaced_len_uz32n_uc32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_us32_uz32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, const uc32_t *to) {
	return uz32n_replaced_len_uz32n_uz32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_us32_uz32n(const uc32_t *cstr, size_t cstr_len, const us32_t *from, size_t to_len) {
	return uz32n_replaced_len_uz32n_uz32n(cstr, cstr_len, US32_CEXPAND(from), to_len);
}

size_t uz32n_replaced_len_us32_ucv32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, ucv32_t to) {
	return uz32n_replaced_len_uz32n_ucv32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_us32_uv32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, uv32_t to) {
	return uz32n_replaced_len_uz32n_uv32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz32n_replaced_len_us32_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *from, const us32_t *to) {
	return uz32n_replaced_len_uz32n_us32(cstr, cstr_len, US32_CEXPAND(from), to);
}

size_t uz16_replaced_len_uc16_uc16(const uc16_t *cstr, uc16_t from, uc16_t to) {
    return uz16n_replaced_len_uc16_uc16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uc16_uz16(const uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uc16_uz16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uc16_uz16n(const uc16_t *cstr, uc16_t from, size_t to_len) {
    return uz16n_replaced_len_uc16_uz16n(cstr, uz16_len(cstr), from, to_len);
}

size_t uz16_replaced_len_uc16_ucv16(const uc16_t *cstr, uc16_t from, ucv16_t to) {
    return uz16n_replaced_len_uc16_ucv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uc16_uv16(const uc16_t *cstr, uc16_t from, uv16_t to) {
    return uz16n_replaced_len_uc16_uv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uc16_us16(const uc16_t *cstr, uc16_t from, const us16_t *to) {
    return uz16n_replaced_len_uc16_us16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uz16_uc16(const uc16_t *cstr, const uc16_t *from, uc16_t to) {
    return uz16n_replaced_len_uz16_uc16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uz16_uz16(const uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_uz16_uz16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uz16_uz16n(const uc16_t *cstr, const uc16_t *from, size_t to_len) {
    return uz16n_replaced_len_uz16_uz16n(cstr, uz16_len(cstr), from, to_len);
}

size_t uz16_replaced_len_uz16_ucv16(const uc16_t *cstr, const uc16_t *from, ucv16_t to) {
    return uz16n_replaced_len_uz16_ucv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uz16_uv16(const uc16_t *cstr, const uc16_t *from, uv16_t to) {
    return uz16n_replaced_len_uz16_uv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uz16_us16(const uc16_t *cstr, const uc16_t *from, const us16_t *to) {
    return uz16n_replaced_len_uz16_us16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uz16n_uc16(const uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16n_replaced_len_uz16n_uc16(cstr, uz16_len(cstr), from, from_len, to);
}

size_t uz16_replaced_len_uz16n_uz16(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16n_replaced_len_uz16n_uz16(cstr, uz16_len(cstr), from, from_len, to);
}

size_t uz16_replaced_len_uz16n_uz16n(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16n_replaced_len_uz16n_uz16n(cstr, uz16_len(cstr), from, from_len, to_len);
}

size_t uz16_replaced_len_uz16n_ucv16(const uc16_t *cstr, const uc16_t *from, size_t from_len, ucv16_t to) {
    return uz16n_replaced_len_uz16n_ucv16(cstr, uz16_len(cstr), from, from_len, to);
}

size_t uz16_replaced_len_uz16n_uv16(const uc16_t *cstr, const uc16_t *from, size_t from_len, uv16_t to) {
    return uz16n_replaced_len_uz16n_uv16(cstr, uz16_len(cstr), from, from_len, to);
}

size_t uz16_replaced_len_uz16n_us16(const uc16_t *cstr, const uc16_t *from, size_t from_len, const us16_t *to) {
    return uz16n_replaced_len_uz16n_us16(cstr, uz16_len(cstr), from, from_len, to);
}

size_t uz16_replaced_len_ucv16_uc16(const uc16_t *cstr, ucv16_t from, uc16_t to) {
    return uz16n_replaced_len_ucv16_uc16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_ucv16_uz16(const uc16_t *cstr, ucv16_t from, const uc16_t *to) {
    return uz16n_replaced_len_ucv16_uz16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_ucv16_uz16n(const uc16_t *cstr, ucv16_t from, size_t to_len) {
    return uz16n_replaced_len_ucv16_uz16n(cstr, uz16_len(cstr), from, to_len);
}

size_t uz16_replaced_len_ucv16_ucv16(const uc16_t *cstr, ucv16_t from, ucv16_t to) {
    return uz16n_replaced_len_ucv16_ucv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_ucv16_uv16(const uc16_t *cstr, ucv16_t from, uv16_t to) {
    return uz16n_replaced_len_ucv16_uv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_ucv16_us16(const uc16_t *cstr, ucv16_t from, const us16_t *to) {
    return uz16n_replaced_len_ucv16_us16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uv16_uc16(const uc16_t *cstr, uv16_t from, uc16_t to) {
    return uz16n_replaced_len_uv16_uc16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uv16_uz16(const uc16_t *cstr, uv16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uv16_uz16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uv16_uz16n(const uc16_t *cstr, uv16_t from, size_t to_len) {
    return uz16n_replaced_len_uv16_uz16n(cstr, uz16_len(cstr), from, to_len);
}

size_t uz16_replaced_len_uv16_ucv16(const uc16_t *cstr, uv16_t from, ucv16_t to) {
    return uz16n_replaced_len_uv16_ucv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uv16_uv16(const uc16_t *cstr, uv16_t from, uv16_t to) {
    return uz16n_replaced_len_uv16_uv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_uv16_us16(const uc16_t *cstr, uv16_t from, const us16_t *to) {
    return uz16n_replaced_len_uv16_us16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_us16_uc16(const uc16_t *cstr, const us16_t *from, uc16_t to) {
    return uz16n_replaced_len_us16_uc16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_us16_uz16(const uc16_t *cstr, const us16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_us16_uz16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_us16_uz16n(const uc16_t *cstr, const us16_t *from, size_t to_len) {
    return uz16n_replaced_len_us16_uz16n(cstr, uz16_len(cstr), from, to_len);
}

size_t uz16_replaced_len_us16_ucv16(const uc16_t *cstr, const us16_t *from, ucv16_t to) {
    return uz16n_replaced_len_us16_ucv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_us16_uv16(const uc16_t *cstr, const us16_t *from, uv16_t to) {
    return uz16n_replaced_len_us16_uv16(cstr, uz16_len(cstr), from, to);
}

size_t uz16_replaced_len_us16_us16(const uc16_t *cstr, const us16_t *from, const us16_t *to) {
    return uz16n_replaced_len_us16_us16(cstr, uz16_len(cstr), from, to);
}

size_t uz16n_replaced_len_uc16_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to) {
    assert(cstr);
    return cstr_len;
}

size_t uz16n_replaced_len_uc16_uz16(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16n_replaced_len_uc16_uz16n(cstr, cstr_len, from, uz16_len(to));
}

size_t uz16n_replaced_len_uc16_uz16n(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len) {
    size_t count = uz16n_count_uc16(cstr, cstr_len, from);
    return cstr_len - count + count * to_len;
}

size_t uz16n_replaced_len_uc16_ucv16(const uc16_t *cstr, size_t cstr_len, uc16_t from, ucv16_t to) {
	return uz16n_replaced_len_uc16_uz16n(cstr, cstr_len, from, ucv16_len(to));
}

size_t uz16n_replaced_len_uc16_uv16(const uc16_t *cstr, size_t cstr_len, uc16_t from, uv16_t to) {
	return uz16n_replaced_len_uc16_uz16n(cstr, cstr_len, from, uv16_len(to));
}

size_t uz16n_replaced_len_uc16_us16(const uc16_t *cstr, size_t cstr_len, uc16_t from, const us16_t *to) {
	return uz16n_replaced_len_uc16_uz16n(cstr, cstr_len, from, us16_len(to));
}

size_t uz16n_replaced_len_uz16_uc16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to) {
    return uz16n_replaced_len_uz16n_uc16(cstr, cstr_len, from, uz16_len(from), to);
}

size_t uz16n_replaced_len_uz16_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16n_replaced_len_uz16n_uz16(cstr, cstr_len, from, uz16_len(from), to);
}

size_t uz16n_replaced_len_uz16_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len) {
    return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, from, uz16_len(from), to_len);
}

size_t uz16n_replaced_len_uz16_ucv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, ucv16_t to) {
    return uz16n_replaced_len_uz16n_ucv16(cstr, cstr_len, from, uz16_len(from), to);
}

size_t uz16n_replaced_len_uz16_uv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, uv16_t to) {
    return uz16n_replaced_len_uz16n_uv16(cstr, cstr_len, from, uz16_len(from), to);
}

size_t uz16n_replaced_len_uz16_us16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const us16_t *to) {
    return uz16n_replaced_len_uz16n_us16(cstr, cstr_len, from, uz16_len(from), to);
}

size_t uz16n_replaced_len_uz16n_uc16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to) {
    size_t count = uz16n_count_uz16n(cstr, cstr_len, from, from_len);
    return cstr_len - from_len * count + count;
}

size_t uz16n_replaced_len_uz16n_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, from, from_len, uz16_len(to));
}

size_t uz16n_replaced_len_uz16n_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len) {
    size_t count = uz16n_count_uz16n(cstr, cstr_len, from, from_len);
    return cstr_len - from_len * count + to_len * count;
}

size_t uz16n_replaced_len_uz16n_ucv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, ucv16_t to) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, from, from_len, ucv16_len(to));
}

size_t uz16n_replaced_len_uz16n_uv16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uv16_t to) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, from, from_len, uv16_len(to));
}

size_t uz16n_replaced_len_uz16n_us16(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const us16_t *to) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, from, from_len, us16_len(to));
}

size_t uz16n_replaced_len_ucv16_uc16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, uc16_t to) {
	return uz16n_replaced_len_uz16n_uc16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_ucv16_uz16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, const uc16_t *to) {
	return uz16n_replaced_len_uz16n_uz16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_ucv16_uz16n(const uc16_t *cstr, size_t cstr_len, ucv16_t from, size_t to_len) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, UCV16_CEXPAND(from), to_len);
}

size_t uz16n_replaced_len_ucv16_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, ucv16_t to) {
	return uz16n_replaced_len_uz16n_ucv16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_ucv16_uv16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, uv16_t to) {
	return uz16n_replaced_len_uz16n_uv16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_ucv16_us16(const uc16_t *cstr, size_t cstr_len, ucv16_t from, const us16_t *to) {
	return uz16n_replaced_len_uz16n_us16(cstr, cstr_len, UCV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_uv16_uc16(const uc16_t *cstr, size_t cstr_len, uv16_t from, uc16_t to) {
	return uz16n_replaced_len_uz16n_uc16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_uv16_uz16(const uc16_t *cstr, size_t cstr_len, uv16_t from, const uc16_t *to) {
	return uz16n_replaced_len_uz16n_uz16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_uv16_uz16n(const uc16_t *cstr, size_t cstr_len, uv16_t from, size_t to_len) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, UV16_CEXPAND(from), to_len);
}

size_t uz16n_replaced_len_uv16_ucv16(const uc16_t *cstr, size_t cstr_len, uv16_t from, ucv16_t to) {
	return uz16n_replaced_len_uz16n_ucv16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_uv16_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t from, uv16_t to) {
	return uz16n_replaced_len_uz16n_uv16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_uv16_us16(const uc16_t *cstr, size_t cstr_len, uv16_t from, const us16_t *to) {
	return uz16n_replaced_len_uz16n_us16(cstr, cstr_len, UV16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_us16_uc16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, uc16_t to) {
	return uz16n_replaced_len_uz16n_uc16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_us16_uz16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, const uc16_t *to) {
	return uz16n_replaced_len_uz16n_uz16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_us16_uz16n(const uc16_t *cstr, size_t cstr_len, const us16_t *from, size_t to_len) {
	return uz16n_replaced_len_uz16n_uz16n(cstr, cstr_len, US16_CEXPAND(from), to_len);
}

size_t uz16n_replaced_len_us16_ucv16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, ucv16_t to) {
	return uz16n_replaced_len_uz16n_ucv16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_us16_uv16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, uv16_t to) {
	return uz16n_replaced_len_uz16n_uv16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz16n_replaced_len_us16_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *from, const us16_t *to) {
	return uz16n_replaced_len_uz16n_us16(cstr, cstr_len, US16_CEXPAND(from), to);
}

size_t uz8_replaced_len_uc8_uc8(const uc8_t *cstr, uc8_t from, uc8_t to) {
    return uz8n_replaced_len_uc8_uc8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uc8_uz8(const uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uc8_uz8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uc8_uz8n(const uc8_t *cstr, uc8_t from, size_t to_len) {
    return uz8n_replaced_len_uc8_uz8n(cstr, uz8_len(cstr), from, to_len);
}

size_t uz8_replaced_len_uc8_ucv8(const uc8_t *cstr, uc8_t from, ucv8_t to) {
    return uz8n_replaced_len_uc8_ucv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uc8_uv8(const uc8_t *cstr, uc8_t from, uv8_t to) {
    return uz8n_replaced_len_uc8_uv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uc8_us8(const uc8_t *cstr, uc8_t from, const us8_t *to) {
    return uz8n_replaced_len_uc8_us8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uz8_uc8(const uc8_t *cstr, const uc8_t *from, uc8_t to) {
    return uz8n_replaced_len_uz8_uc8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uz8_uz8(const uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_uz8_uz8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uz8_uz8n(const uc8_t *cstr, const uc8_t *from, size_t to_len) {
    return uz8n_replaced_len_uz8_uz8n(cstr, uz8_len(cstr), from, to_len);
}

size_t uz8_replaced_len_uz8_ucv8(const uc8_t *cstr, const uc8_t *from, ucv8_t to) {
    return uz8n_replaced_len_uz8_ucv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uz8_uv8(const uc8_t *cstr, const uc8_t *from, uv8_t to) {
    return uz8n_replaced_len_uz8_uv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uz8_us8(const uc8_t *cstr, const uc8_t *from, const us8_t *to) {
    return uz8n_replaced_len_uz8_us8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uz8n_uc8(const uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8n_replaced_len_uz8n_uc8(cstr, uz8_len(cstr), from, from_len, to);
}

size_t uz8_replaced_len_uz8n_uz8(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8n_replaced_len_uz8n_uz8(cstr, uz8_len(cstr), from, from_len, to);
}

size_t uz8_replaced_len_uz8n_uz8n(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8n_replaced_len_uz8n_uz8n(cstr, uz8_len(cstr), from, from_len, to_len);
}

size_t uz8_replaced_len_uz8n_ucv8(const uc8_t *cstr, const uc8_t *from, size_t from_len, ucv8_t to) {
    return uz8n_replaced_len_uz8n_ucv8(cstr, uz8_len(cstr), from, from_len, to);
}

size_t uz8_replaced_len_uz8n_uv8(const uc8_t *cstr, const uc8_t *from, size_t from_len, uv8_t to) {
    return uz8n_replaced_len_uz8n_uv8(cstr, uz8_len(cstr), from, from_len, to);
}

size_t uz8_replaced_len_uz8n_us8(const uc8_t *cstr, const uc8_t *from, size_t from_len, const us8_t *to) {
    return uz8n_replaced_len_uz8n_us8(cstr, uz8_len(cstr), from, from_len, to);
}

size_t uz8_replaced_len_ucv8_uc8(const uc8_t *cstr, ucv8_t from, uc8_t to) {
    return uz8n_replaced_len_ucv8_uc8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_ucv8_uz8(const uc8_t *cstr, ucv8_t from, const uc8_t *to) {
    return uz8n_replaced_len_ucv8_uz8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_ucv8_uz8n(const uc8_t *cstr, ucv8_t from, size_t to_len) {
    return uz8n_replaced_len_ucv8_uz8n(cstr, uz8_len(cstr), from, to_len);
}

size_t uz8_replaced_len_ucv8_ucv8(const uc8_t *cstr, ucv8_t from, ucv8_t to) {
    return uz8n_replaced_len_ucv8_ucv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_ucv8_uv8(const uc8_t *cstr, ucv8_t from, uv8_t to) {
    return uz8n_replaced_len_ucv8_uv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_ucv8_us8(const uc8_t *cstr, ucv8_t from, const us8_t *to) {
    return uz8n_replaced_len_ucv8_us8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uv8_uc8(const uc8_t *cstr, uv8_t from, uc8_t to) {
    return uz8n_replaced_len_uv8_uc8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uv8_uz8(const uc8_t *cstr, uv8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uv8_uz8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uv8_uz8n(const uc8_t *cstr, uv8_t from, size_t to_len) {
    return uz8n_replaced_len_uv8_uz8n(cstr, uz8_len(cstr), from, to_len);
}

size_t uz8_replaced_len_uv8_ucv8(const uc8_t *cstr, uv8_t from, ucv8_t to) {
    return uz8n_replaced_len_uv8_ucv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uv8_uv8(const uc8_t *cstr, uv8_t from, uv8_t to) {
    return uz8n_replaced_len_uv8_uv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_uv8_us8(const uc8_t *cstr, uv8_t from, const us8_t *to) {
    return uz8n_replaced_len_uv8_us8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_us8_uc8(const uc8_t *cstr, const us8_t *from, uc8_t to) {
    return uz8n_replaced_len_us8_uc8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_us8_uz8(const uc8_t *cstr, const us8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_us8_uz8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_us8_uz8n(const uc8_t *cstr, const us8_t *from, size_t to_len) {
    return uz8n_replaced_len_us8_uz8n(cstr, uz8_len(cstr), from, to_len);
}

size_t uz8_replaced_len_us8_ucv8(const uc8_t *cstr, const us8_t *from, ucv8_t to) {
    return uz8n_replaced_len_us8_ucv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_us8_uv8(const uc8_t *cstr, const us8_t *from, uv8_t to) {
    return uz8n_replaced_len_us8_uv8(cstr, uz8_len(cstr), from, to);
}

size_t uz8_replaced_len_us8_us8(const uc8_t *cstr, const us8_t *from, const us8_t *to) {
    return uz8n_replaced_len_us8_us8(cstr, uz8_len(cstr), from, to);
}

size_t uz8n_replaced_len_uc8_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to) {
    assert(cstr);
    return cstr_len;
}

size_t uz8n_replaced_len_uc8_uz8(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8n_replaced_len_uc8_uz8n(cstr, cstr_len, from, uz8_len(to));
}

size_t uz8n_replaced_len_uc8_uz8n(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len) {
    size_t count = uz8n_count_uc8(cstr, cstr_len, from);
    return cstr_len - count + count * to_len;
}

size_t uz8n_replaced_len_uc8_ucv8(const uc8_t *cstr, size_t cstr_len, uc8_t from, ucv8_t to) {
	return uz8n_replaced_len_uc8_uz8n(cstr, cstr_len, from, ucv8_len(to));
}

size_t uz8n_replaced_len_uc8_uv8(const uc8_t *cstr, size_t cstr_len, uc8_t from, uv8_t to) {
	return uz8n_replaced_len_uc8_uz8n(cstr, cstr_len, from, uv8_len(to));
}

size_t uz8n_replaced_len_uc8_us8(const uc8_t *cstr, size_t cstr_len, uc8_t from, const us8_t *to) {
	return uz8n_replaced_len_uc8_uz8n(cstr, cstr_len, from, us8_len(to));
}

size_t uz8n_replaced_len_uz8_uc8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to) {
    return uz8n_replaced_len_uz8n_uc8(cstr, cstr_len, from, uz8_len(from), to);
}

size_t uz8n_replaced_len_uz8_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8n_replaced_len_uz8n_uz8(cstr, cstr_len, from, uz8_len(from), to);
}

size_t uz8n_replaced_len_uz8_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len) {
    return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, from, uz8_len(from), to_len);
}

size_t uz8n_replaced_len_uz8_ucv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, ucv8_t to) {
    return uz8n_replaced_len_uz8n_ucv8(cstr, cstr_len, from, uz8_len(from), to);
}

size_t uz8n_replaced_len_uz8_uv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, uv8_t to) {
    return uz8n_replaced_len_uz8n_uv8(cstr, cstr_len, from, uz8_len(from), to);
}

size_t uz8n_replaced_len_uz8_us8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const us8_t *to) {
    return uz8n_replaced_len_uz8n_us8(cstr, cstr_len, from, uz8_len(from), to);
}

size_t uz8n_replaced_len_uz8n_uc8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to) {
    size_t count = uz8n_count_uz8n(cstr, cstr_len, from, from_len);
    return cstr_len - from_len * count + count;
}

size_t uz8n_replaced_len_uz8n_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, from, from_len, uz8_len(to));
}

size_t uz8n_replaced_len_uz8n_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len) {
    size_t count = uz8n_count_uz8n(cstr, cstr_len, from, from_len);
    return cstr_len - from_len * count + to_len * count;
}

size_t uz8n_replaced_len_uz8n_ucv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, ucv8_t to) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, from, from_len, ucv8_len(to));
}

size_t uz8n_replaced_len_uz8n_uv8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uv8_t to) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, from, from_len, uv8_len(to));
}

size_t uz8n_replaced_len_uz8n_us8(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const us8_t *to) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, from, from_len, us8_len(to));
}

size_t uz8n_replaced_len_ucv8_uc8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, uc8_t to) {
	return uz8n_replaced_len_uz8n_uc8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_ucv8_uz8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, const uc8_t *to) {
	return uz8n_replaced_len_uz8n_uz8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_ucv8_uz8n(const uc8_t *cstr, size_t cstr_len, ucv8_t from, size_t to_len) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, UCV8_CEXPAND(from), to_len);
}

size_t uz8n_replaced_len_ucv8_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, ucv8_t to) {
	return uz8n_replaced_len_uz8n_ucv8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_ucv8_uv8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, uv8_t to) {
	return uz8n_replaced_len_uz8n_uv8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_ucv8_us8(const uc8_t *cstr, size_t cstr_len, ucv8_t from, const us8_t *to) {
	return uz8n_replaced_len_uz8n_us8(cstr, cstr_len, UCV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_uv8_uc8(const uc8_t *cstr, size_t cstr_len, uv8_t from, uc8_t to) {
	return uz8n_replaced_len_uz8n_uc8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_uv8_uz8(const uc8_t *cstr, size_t cstr_len, uv8_t from, const uc8_t *to) {
	return uz8n_replaced_len_uz8n_uz8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_uv8_uz8n(const uc8_t *cstr, size_t cstr_len, uv8_t from, size_t to_len) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, UV8_CEXPAND(from), to_len);
}

size_t uz8n_replaced_len_uv8_ucv8(const uc8_t *cstr, size_t cstr_len, uv8_t from, ucv8_t to) {
	return uz8n_replaced_len_uz8n_ucv8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_uv8_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t from, uv8_t to) {
	return uz8n_replaced_len_uz8n_uv8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_uv8_us8(const uc8_t *cstr, size_t cstr_len, uv8_t from, const us8_t *to) {
	return uz8n_replaced_len_uz8n_us8(cstr, cstr_len, UV8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_us8_uc8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, uc8_t to) {
	return uz8n_replaced_len_uz8n_uc8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_us8_uz8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, const uc8_t *to) {
	return uz8n_replaced_len_uz8n_uz8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_us8_uz8n(const uc8_t *cstr, size_t cstr_len, const us8_t *from, size_t to_len) {
	return uz8n_replaced_len_uz8n_uz8n(cstr, cstr_len, US8_CEXPAND(from), to_len);
}

size_t uz8n_replaced_len_us8_ucv8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, ucv8_t to) {
	return uz8n_replaced_len_uz8n_ucv8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_us8_uv8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, uv8_t to) {
	return uz8n_replaced_len_uz8n_uv8(cstr, cstr_len, US8_CEXPAND(from), to);
}

size_t uz8n_replaced_len_us8_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *from, const us8_t *to) {
	return uz8n_replaced_len_uz8n_us8(cstr, cstr_len, US8_CEXPAND(from), to);
}

#define UZX_COUNT_UCX(cstr, target) \
    assert(cstr);                   \
                                    \
    size_t count = 0;               \
                                    \
    while (*cstr)                   \
        if (*cstr++ == target)      \
            ++count;                \
                                    \
    return count

#define UZXN_COUNT_UCX(cstr, cstr_len, target) \
    assert(cstr);                              \
                                               \
    size_t count = 0;                          \
                                               \
    while (cstr_len--)                         \
        if (*cstr++ == target)                 \
            ++count;                           \
                                               \
    return count
    
#define UZXN_COUNT_UZXN(cstr, cstr_len, target, target_len, X)                                     \
    assert(cstr && target);                                                                        \
                                                                                                   \
    ptrdiff_t prev_pos = 0;                                                                        \
    size_t    count    = 0;                                                                        \
                                                                                                   \
    while (prev_pos < cstr_len) {                                                                  \
        ptrdiff_t pos = uz##X##n_find_uz##X##n_from(cstr, cstr_len, target, target_len, prev_pos); \
                                                                                                   \
        if (pos < 0)                                                                               \
            break;                                                                                 \
                                                                                                   \
        prev_pos = pos + target_len;                                                               \
                                                                                                   \
        ++count;                                                                                   \
    }                                                                                              \
                                                                                                   \
    return count

size_t uz32_count_uc32(const uc32_t *cstr, uc32_t target) {
    UZX_COUNT_UCX(cstr, target);
}

size_t uz32_count_uz32(const uc32_t *cstr, const uc32_t *target) {
	return uz32n_count_uz32n(cstr, uz32_len(cstr), target, uz32_len(target));
}

size_t uz32_count_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len) {
	return uz32n_count_uz32n(cstr, uz32_len(cstr), target, target_len);
}

size_t uz32_count_ucv32(const uc32_t *cstr, ucv32_t target) {
	return uz32_count_uz32n(cstr, UCV32_CEXPAND(target));
}

size_t uz32_count_uv32(const uc32_t *cstr, uv32_t target) {
	return uz32_count_uz32n(cstr, UV32_CEXPAND(target));
}

size_t uz32_count_us32(const uc32_t *cstr, const us32_t *target) {
	return uz32_count_uz32n(cstr, US32_CEXPAND(target));
}

size_t uz32n_count_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target) {
    UZXN_COUNT_UCX(cstr, cstr_len, target);
}

size_t uz32n_count_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
	return uz32n_count_uz32n(cstr, cstr_len, target, uz32_len(target));
}

size_t uz32n_count_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
    UZXN_COUNT_UZXN(cstr, cstr_len, target, target_len, 32);
}

size_t uz32n_count_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target) {
	return uz32n_count_uz32n(cstr, cstr_len, UCV32_CEXPAND(target));
}

size_t uz32n_count_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target) {
	return uz32n_count_uz32n(cstr, cstr_len, UV32_CEXPAND(target));
}

size_t uz32n_count_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target) {
	return uz32n_count_uz32n(cstr, cstr_len, US32_CEXPAND(target));
}

size_t uz16_count_uc16(const uc16_t *cstr, uc16_t target) {
    UZX_COUNT_UCX(cstr, target);
}

size_t uz16_count_uz16(const uc16_t *cstr, const uc16_t *target) {
	return uz16n_count_uz16n(cstr, uz16_len(cstr), target, uz16_len(target));
}

size_t uz16_count_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len) {
	return uz16n_count_uz16n(cstr, uz16_len(cstr), target, target_len);
}

size_t uz16_count_ucv16(const uc16_t *cstr, ucv16_t target) {
	return uz16_count_uz16n(cstr, UCV16_CEXPAND(target));
}

size_t uz16_count_uv16(const uc16_t *cstr, uv16_t target) {
	return uz16_count_uz16n(cstr, UV16_CEXPAND(target));
}

size_t uz16_count_us16(const uc16_t *cstr, const us16_t *target) {
	return uz16_count_uz16n(cstr, US16_CEXPAND(target));
}

size_t uz16n_count_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target) {
    UZXN_COUNT_UCX(cstr, cstr_len, target);
}

size_t uz16n_count_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
	return uz16n_count_uz16n(cstr, cstr_len, target, uz16_len(target));
}

size_t uz16n_count_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
    UZXN_COUNT_UZXN(cstr, cstr_len, target, target_len, 16);
}

size_t uz16n_count_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target) {
	return uz16n_count_uz16n(cstr, cstr_len, UCV16_CEXPAND(target));
}

size_t uz16n_count_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target) {
	return uz16n_count_uz16n(cstr, cstr_len, UV16_CEXPAND(target));
}

size_t uz16n_count_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target) {
	return uz16n_count_uz16n(cstr, cstr_len, US16_CEXPAND(target));
}

size_t uz8_count_uc8(const uc8_t *cstr, uc8_t target) {
    UZX_COUNT_UCX(cstr, target);
}

size_t uz8_count_uz8(const uc8_t *cstr, const uc8_t *target) {
	return uz8n_count_uz8n(cstr, uz8_len(cstr), target, uz8_len(target));
}

size_t uz8_count_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len) {
	return uz8n_count_uz8n(cstr, uz8_len(cstr), target, target_len);
}

size_t uz8_count_ucv8(const uc8_t *cstr, ucv8_t target) {
	return uz8_count_uz8n(cstr, UCV8_CEXPAND(target));
}

size_t uz8_count_uv8(const uc8_t *cstr, uv8_t target) {
	return uz8_count_uz8n(cstr, UV8_CEXPAND(target));
}

size_t uz8_count_us8(const uc8_t *cstr, const us8_t *target) {
	return uz8_count_uz8n(cstr, US8_CEXPAND(target));
}

size_t uz8n_count_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target) {
    UZXN_COUNT_UCX(cstr, cstr_len, target);
}

size_t uz8n_count_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
	return uz8n_count_uz8n(cstr, cstr_len, target, uz8_len(target));
}

size_t uz8n_count_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
    UZXN_COUNT_UZXN(cstr, cstr_len, target, target_len, 8);
}

size_t uz8n_count_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target) {
	return uz8n_count_uz8n(cstr, cstr_len, UCV8_CEXPAND(target));
}

size_t uz8n_count_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target) {
	return uz8n_count_uz8n(cstr, cstr_len, UV8_CEXPAND(target));
}

size_t uz8n_count_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target) {
	return uz8n_count_uz8n(cstr, cstr_len, US8_CEXPAND(target));
}

bool uz32_bounds(const uc32_t *cstr, size_t index) {
	return index < uz32_len(cstr);
}

bool uz32_ebounds(const uc32_t *cstr, size_t index) {
	return index <= uz32_len(cstr);
}

bool uz32_bounds_range(const uc32_t *cstr, size_t begin, size_t len) {
	return ubounds_range(uz32_len(cstr), begin, len);
}

bool uz32_ebounds_range(const uc32_t *cstr, size_t begin, size_t len) {
	return uebounds_range(uz32_len(cstr), begin, len);
}

bool uz16_bounds(const uc16_t *cstr, size_t index) {
	return index < uz16_len(cstr);
}

bool uz16_ebounds(const uc16_t *cstr, size_t index) {
	return index <= uz16_len(cstr);
}

bool uz16_bounds_range(const uc16_t *cstr, size_t begin, size_t len) {
	return ubounds_range(uz16_len(cstr), begin, len);
}

bool uz16_ebounds_range(const uc16_t *cstr, size_t begin, size_t len) {
	return uebounds_range(uz16_len(cstr), begin, len);
}

bool uz8_bounds(const uc8_t *cstr, size_t index) {
	return index < uz8_len(cstr);
}

bool uz8_ebounds(const uc8_t *cstr, size_t index) {
	return index <= uz8_len(cstr);
}

bool uz8_bounds_range(const uc8_t *cstr, size_t begin, size_t len) {
	return ubounds_range(uz8_len(cstr), begin, len);
}

bool uz8_ebounds_range(const uc8_t *cstr, size_t begin, size_t len) {
	return uebounds_range(uz8_len(cstr), begin, len);
}

bool ubounds_range(size_t len, size_t range_begin, size_t range_len) {
    return range_begin             < len
        && range_begin + range_len < len;
}

bool uebounds_range(size_t len, size_t range_begin, size_t range_len) {
    return range_begin             <= len 
        && range_begin + range_len <= len;
}

#define UZX_STARTS_WITH_UCX(cstr, target) \
    assert(cstr);                         \
    return *cstr && *cstr == target

#define UZX_STARTS_WITH_UZX(cstr, target) \
    assert(cstr && target);               \
                                          \
    while (*cstr && *target)              \
        if (*cstr++ != *target++)         \
            return false;                 \
                                          \
	return !*target

#define UZX_STARTS_WITH_UZXN(cstr, target, target_len) \
    assert(cstr && target);                            \
                                                       \
    while (*cstr && target_len--)                      \
        if (*cstr++ != *target++)                      \
            return false;                              \
                                                       \
	return !target_len

#define UZXN_STARTS_WITH_UCX(cstr, cstr_len, target) \
    assert(cstr);                                    \
    return cstr_len && *cstr == target

#define UZXN_STARTS_WITH_UZX(cstr, cstr_len, target) \
    assert(cstr && target);                          \
                                                     \
    while (cstr_len-- && *target)                    \
        if (*cstr++ != *target++)                    \
            return false;                            \
                                                     \
	return !*target

#define UZXN_STARTS_WITH_UZXN(cstr, cstr_len, target, target_len) \
    assert(cstr && target);                                       \
                                                                  \
    if (cstr_len < target_len)                                    \
        return false;                                             \
                                                                  \
    while (cstr_len-- && target_len--)                            \
        if (*cstr++ != *target++)                                 \
            return false;                                         \
                                                                  \
	return !target_len

bool uz32_starts_with_uc32(const uc32_t *cstr, uc32_t target) {
    UZX_STARTS_WITH_UCX(cstr, target);
}

bool uz32_starts_with_uz32(const uc32_t *cstr, const uc32_t *target) {
    UZX_STARTS_WITH_UZX(cstr, target);
}

bool uz32_starts_with_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len) {
    UZX_STARTS_WITH_UZXN(cstr, target, target_len);
}

bool uz32_starts_with_ucv32(const uc32_t *cstr, ucv32_t target) {
	return uz32_starts_with_uz32n(cstr, UCV32_CEXPAND(target));
}

bool uz32_starts_with_uv32(const uc32_t *cstr, uv32_t target) {
	return uz32_starts_with_uz32n(cstr, UV32_CEXPAND(target));
}

bool uz32_starts_with_us32(const uc32_t *cstr, const us32_t *target) {
	return uz32_starts_with_uz32n(cstr, US32_CEXPAND(target));
}

bool uz32n_starts_with_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target) {
    UZXN_STARTS_WITH_UCX(cstr, cstr_len, target);
}

bool uz32n_starts_with_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
    UZXN_STARTS_WITH_UZX(cstr, cstr_len, target);
}

bool uz32n_starts_with_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
    UZXN_STARTS_WITH_UZXN(cstr, cstr_len, target, target_len);
}

bool uz32n_starts_with_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target) {
	return uz32n_starts_with_uz32n(cstr, cstr_len, UCV32_CEXPAND(target));
}

bool uz32n_starts_with_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target) {
	return uz32n_starts_with_uz32n(cstr, cstr_len, UV32_CEXPAND(target));
}

bool uz32n_starts_with_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target) {
	return uz32n_starts_with_uz32n(cstr, cstr_len, US32_CEXPAND(target));
}

bool uz16_starts_with_uc16(const uc16_t *cstr, uc16_t target) {
    UZX_STARTS_WITH_UCX(cstr, target);
}

bool uz16_starts_with_uz16(const uc16_t *cstr, const uc16_t *target) {
    UZX_STARTS_WITH_UZX(cstr, target);
}

bool uz16_starts_with_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len) {
    UZX_STARTS_WITH_UZXN(cstr, target, target_len);
}

bool uz16_starts_with_ucv16(const uc16_t *cstr, ucv16_t target) {
	return uz16_starts_with_uz16n(cstr, UCV16_CEXPAND(target));
}

bool uz16_starts_with_uv16(const uc16_t *cstr, uv16_t target) {
	return uz16_starts_with_uz16n(cstr, UV16_CEXPAND(target));
}

bool uz16_starts_with_us16(const uc16_t *cstr, const us16_t *target) {
	return uz16_starts_with_uz16n(cstr, US16_CEXPAND(target));
}

bool uz16n_starts_with_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target) {
    UZXN_STARTS_WITH_UCX(cstr, cstr_len, target);
}

bool uz16n_starts_with_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
    UZXN_STARTS_WITH_UZX(cstr, cstr_len, target);
}

bool uz16n_starts_with_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
    UZXN_STARTS_WITH_UZXN(cstr, cstr_len, target, target_len);
}

bool uz16n_starts_with_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target) {
	return uz16n_starts_with_uz16n(cstr, cstr_len, UCV16_CEXPAND(target));
}

bool uz16n_starts_with_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target) {
	return uz16n_starts_with_uz16n(cstr, cstr_len, UV16_CEXPAND(target));
}

bool uz16n_starts_with_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target) {
	return uz16n_starts_with_uz16n(cstr, cstr_len, US16_CEXPAND(target));
}

bool uz8_starts_with_uc8(const uc8_t *cstr, uc8_t target) {
    UZX_STARTS_WITH_UCX(cstr, target);
}

bool uz8_starts_with_uz8(const uc8_t *cstr, const uc8_t *target) {
    UZX_STARTS_WITH_UZX(cstr, target);
}

bool uz8_starts_with_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len) {
    UZX_STARTS_WITH_UZXN(cstr, target, target_len);
}

bool uz8_starts_with_ucv8(const uc8_t *cstr, ucv8_t target) {
	return uz8_starts_with_uz8n(cstr, UCV8_CEXPAND(target));
}

bool uz8_starts_with_uv8(const uc8_t *cstr, uv8_t target) {
	return uz8_starts_with_uz8n(cstr, UV8_CEXPAND(target));
}

bool uz8_starts_with_us8(const uc8_t *cstr, const us8_t *target) {
	return uz8_starts_with_uz8n(cstr, US8_CEXPAND(target));
}

bool uz8n_starts_with_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target) {
    UZXN_STARTS_WITH_UCX(cstr, cstr_len, target);
}

bool uz8n_starts_with_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
    UZXN_STARTS_WITH_UZX(cstr, cstr_len, target);
}

bool uz8n_starts_with_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
    UZXN_STARTS_WITH_UZXN(cstr, cstr_len, target, target_len);
}

bool uz8n_starts_with_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target) {
	return uz8n_starts_with_uz8n(cstr, cstr_len, UCV8_CEXPAND(target));
}

bool uz8n_starts_with_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target) {
	return uz8n_starts_with_uz8n(cstr, cstr_len, UV8_CEXPAND(target));
}

bool uz8n_starts_with_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target) {
	return uz8n_starts_with_uz8n(cstr, cstr_len, US8_CEXPAND(target));
}

#define UZXN_ENDS_WITH_UCX(cstr, cstr_len, target) \
    assert(cstr);                                  \
    return cstr_len                                \
        && cstr[cstr_len - 1] == target
    
#define UZXN_ENDS_WITH_UZXN(cstr, cstr_len, target, target_len) \
    assert(cstr && target);                                     \
                                                                \
    if (cstr_len < target_len)                                  \
        return false;                                           \
                                                                \
    ptrdiff_t i = cstr_len   - 1;                               \
    ptrdiff_t j = target_len - 1;                               \
                                                                \
    while(i >= 0 && j >= 0)                                     \
        if (cstr[i--] != target[j--])                           \
            return false;                                       \
                                                                \
    return j < 0

bool uz32_ends_with_uc32(const uc32_t *cstr, uc32_t target) {
    return uz32n_ends_with_uc32(cstr, uz32_len(cstr), target); 
}

bool uz32_ends_with_uz32(const uc32_t *cstr, const uc32_t *target) {
	return uz32n_ends_with_uz32n(cstr, uz32_len(cstr), target, uz32_len(target));
}

bool uz32_ends_with_uz32n(const uc32_t *cstr, const uc32_t *target, size_t target_len) {
	return uz32n_ends_with_uz32n(cstr, uz32_len(cstr), target, target_len);
}

bool uz32_ends_with_ucv32(const uc32_t *cstr, ucv32_t target) {
	return uz32_ends_with_uz32n(cstr, UCV32_CEXPAND(target));
}

bool uz32_ends_with_uv32(const uc32_t *cstr, uv32_t target) {
	return uz32_ends_with_uz32n(cstr, UV32_CEXPAND(target));
}

bool uz32_ends_with_us32(const uc32_t *cstr, const us32_t *target) {
	return uz32_ends_with_uz32n(cstr, US32_CEXPAND(target));
}

bool uz32n_ends_with_uc32(const uc32_t *cstr, size_t cstr_len, uc32_t target) {
    UZXN_ENDS_WITH_UCX(cstr, cstr_len, target);
}

bool uz32n_ends_with_uz32(const uc32_t *cstr, size_t cstr_len, const uc32_t *target) {
    return uz32n_ends_with_uz32n(cstr, cstr_len, target, uz32_len(target));
}

bool uz32n_ends_with_uz32n(const uc32_t *cstr, size_t cstr_len, const uc32_t *target, size_t target_len) {
    UZXN_ENDS_WITH_UZXN(cstr, cstr_len, target, target_len);
}

bool uz32n_ends_with_ucv32(const uc32_t *cstr, size_t cstr_len, ucv32_t target) {
	return uz32n_ends_with_uz32n(cstr, cstr_len, UCV32_CEXPAND(target));
}

bool uz32n_ends_with_uv32(const uc32_t *cstr, size_t cstr_len, uv32_t target) {
	return uz32n_ends_with_uz32n(cstr, cstr_len, UV32_CEXPAND(target));
}

bool uz32n_ends_with_us32(const uc32_t *cstr, size_t cstr_len, const us32_t *target) {
	return uz32n_ends_with_uz32n(cstr, cstr_len, US32_CEXPAND(target));
}

bool uz16_ends_with_uc16(const uc16_t *cstr, uc16_t target) {
    return uz16n_ends_with_uc16(cstr, uz16_len(cstr), target); 
}

bool uz16_ends_with_uz16(const uc16_t *cstr, const uc16_t *target) {
	return uz16n_ends_with_uz16n(cstr, uz16_len(cstr), target, uz16_len(target));
}

bool uz16_ends_with_uz16n(const uc16_t *cstr, const uc16_t *target, size_t target_len) {
	return uz16n_ends_with_uz16n(cstr, uz16_len(cstr), target, target_len);
}

bool uz16_ends_with_ucv16(const uc16_t *cstr, ucv16_t target) {
	return uz16_ends_with_uz16n(cstr, UCV16_CEXPAND(target));
}

bool uz16_ends_with_uv16(const uc16_t *cstr, uv16_t target) {
	return uz16_ends_with_uz16n(cstr, UV16_CEXPAND(target));
}

bool uz16_ends_with_us16(const uc16_t *cstr, const us16_t *target) {
	return uz16_ends_with_uz16n(cstr, US16_CEXPAND(target));
}

bool uz16n_ends_with_uc16(const uc16_t *cstr, size_t cstr_len, uc16_t target) {
    UZXN_ENDS_WITH_UCX(cstr, cstr_len, target);
}

bool uz16n_ends_with_uz16(const uc16_t *cstr, size_t cstr_len, const uc16_t *target) {
	return uz16n_ends_with_uz16n(cstr, cstr_len, target, uz16_len(target));
}

bool uz16n_ends_with_uz16n(const uc16_t *cstr, size_t cstr_len, const uc16_t *target, size_t target_len) {
    UZXN_ENDS_WITH_UZXN(cstr, cstr_len, target, target_len);
}

bool uz16n_ends_with_ucv16(const uc16_t *cstr, size_t cstr_len, ucv16_t target) {
	return uz16n_ends_with_uz16n(cstr, cstr_len, UCV16_CEXPAND(target));
}

bool uz16n_ends_with_uv16(const uc16_t *cstr, size_t cstr_len, uv16_t target) {
	return uz16n_ends_with_uz16n(cstr, cstr_len, UV16_CEXPAND(target));
}

bool uz16n_ends_with_us16(const uc16_t *cstr, size_t cstr_len, const us16_t *target) {
	return uz16n_ends_with_uz16n(cstr, cstr_len, US16_CEXPAND(target));
}

bool uz8_ends_with_uc8(const uc8_t *cstr, uc8_t target) {
    return uz8n_ends_with_uc8(cstr, uz8_len(cstr), target); 
}

bool uz8_ends_with_uz8(const uc8_t *cstr, const uc8_t *target) {
	return uz8n_ends_with_uz8n(cstr, uz8_len(cstr), target, uz8_len(target));
}

bool uz8_ends_with_uz8n(const uc8_t *cstr, const uc8_t *target, size_t target_len) {
	return uz8n_ends_with_uz8n(cstr, uz8_len(cstr), target, target_len);
}

bool uz8_ends_with_ucv8(const uc8_t *cstr, ucv8_t target) {
	return uz8_ends_with_uz8n(cstr, UCV8_CEXPAND(target));
}

bool uz8_ends_with_uv8(const uc8_t *cstr, uv8_t target) {
	return uz8_ends_with_uz8n(cstr, UV8_CEXPAND(target));
}

bool uz8_ends_with_us8(const uc8_t *cstr, const us8_t *target) {
	return uz8_ends_with_uz8n(cstr, US8_CEXPAND(target));
}

bool uz8n_ends_with_uc8(const uc8_t *cstr, size_t cstr_len, uc8_t target) {
    UZXN_ENDS_WITH_UCX(cstr, cstr_len, target);
}

bool uz8n_ends_with_uz8(const uc8_t *cstr, size_t cstr_len, const uc8_t *target) {
	return uz8n_ends_with_uz8n(cstr, cstr_len, target, uz8_len(target));
}

bool uz8n_ends_with_uz8n(const uc8_t *cstr, size_t cstr_len, const uc8_t *target, size_t target_len) {
    UZXN_ENDS_WITH_UZXN(cstr, cstr_len, target, target_len);
}

bool uz8n_ends_with_ucv8(const uc8_t *cstr, size_t cstr_len, ucv8_t target) {
	return uz8n_ends_with_uz8n(cstr, cstr_len, UCV8_CEXPAND(target));
}

bool uz8n_ends_with_uv8(const uc8_t *cstr, size_t cstr_len, uv8_t target) {
	return uz8n_ends_with_uz8n(cstr, cstr_len, UV8_CEXPAND(target));
}

bool uz8n_ends_with_us8(const uc8_t *cstr, size_t cstr_len, const us8_t *target) {
	return uz8n_ends_with_uz8n(cstr, cstr_len, US8_CEXPAND(target));
}