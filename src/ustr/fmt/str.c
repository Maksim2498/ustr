#include "str.h"

#include <assert.h>

#include <ustr/char.h>
#include <ustr/cstr.h>
#include <ustr/cview.h>
#include <ustr/str.h>
#include <ustr/view.h>

#define UWRITE_UZX_X(val, write, write_arg, X) \
    assert(val && write);                      \
                                               \
    const uc##X##_t *val_begin = val;          \
                                               \
    for (; *val; ++val)                        \
        if (write(*val, write_arg))            \
            break;                             \
                                               \
    return val - val_begin

#define UWRITE_UZXN_X(val, val_len, write, write_arg, X) \
    assert(val && write);                                \
                                                         \
    const uc##X##_t *val_begin = val;                    \
                                                         \
    for (; val_len--; ++val)                             \
        if (write(*val, write_arg))                      \
            break;                                       \
                                                         \
    return val - val_begin
    
#define UWRITE_UZXN_32(val, val_len, write, write_arg, X)                             \
    assert(val && write);                                                             \
                                                                                      \
    size_t i = 0;                                                                     \
    uc32_t c32;                                                                       \
                                                                                      \
    for (; i < val_len; i += uc##X##_len(val[i]))                                     \
        if (!uc32_from_uc##X##n(&c32, val + i, val_len - i) || write(c32, write_arg)) \
            break;                                                                    \
                                                                                      \
    return i

size_t uwrite_uz32_32(const uc32_t *val, uwrite_uc32_t write, void *write_arg) {
    UWRITE_UZX_X(val, write, write_arg, 32);
}

size_t uwrite_uz32n_32(const uc32_t *val, size_t val_len, uwrite_uc32_t write, void *write_arg) {
    UWRITE_UZXN_X(val, val_len, write, write_arg, 32);
}

size_t uwrite_ucv32_32(ucv32_t val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz32n_32(UCV32_CEXPAND(val), write, write_arg);
}

size_t uwrite_us32_32(const us32_t *val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz32n_32(US32_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv32_32(uv32_t val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz32n_32(UV32_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz16_32(const uc16_t *val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz16n_32(val, uz16_len(val), write, write_arg);
}

size_t uwrite_uz16n_32(const uc16_t *val, size_t val_len, uwrite_uc32_t write, void *write_arg) {
    UWRITE_UZXN_32(val, val_len, write, write_arg, 16);
}

size_t uwrite_ucv16_32(ucv16_t val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz16n_32(UCV16_CEXPAND(val), write, write_arg);
}

size_t uwrite_us16_32(const us16_t *val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz16n_32(US16_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv16_32(uv16_t val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz16n_32(UV16_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz8_32(const uc8_t *val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz8n_32(val, uz8_len(val), write, write_arg);
}

size_t uwrite_uz8n_32(const uc8_t *val, size_t val_len, uwrite_uc32_t write, void *write_arg) {
    UWRITE_UZXN_32(val, val_len, write, write_arg, 8);
}

size_t uwrite_ucv8_32(ucv8_t val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz8n_32(UCV8_CEXPAND(val), write, write_arg);
}

size_t uwrite_us8_32(const us8_t *val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz8n_32(US8_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv8_32(uv8_t val, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uz8n_32(UV8_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz32_16(const uc32_t *val, uwrite_uc16_t write, void *write_arg) {
    assert(val && write);

    const uc32_t *val_begin = val;

    for (; *val; ++val) {
        uc16_t   c16[2];
        unsigned c16_len = uc16_from_uc32_imm(c16, *val);

        if (write(c16[0], write_arg))
            break;

        if (c16_len == 2 && write(c16[1], write_arg))
            break;
    }

    return val - val_begin;
}

size_t uwrite_uz32n_16(const uc32_t *val, size_t val_len, uwrite_uc16_t write, void *write_arg) {
    assert(val && write);

    const uc32_t *val_begin = val;

    for (; val_len--; ++val) {
        uc16_t   c16[2];
        unsigned c16_len = uc16_from_uc32_imm(c16, *val);

        if (write(c16[0], write_arg))
            break;

        if (c16_len == 2 && write(c16[1], write_arg))
            break;
    }

    return val - val_begin;
}

size_t uwrite_ucv32_16(ucv32_t val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz32n_16(UCV32_CEXPAND(val), write, write_arg);
}

size_t uwrite_us32_16(const us32_t *val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz32n_16(US32_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv32_16(uv32_t val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz32n_16(UV32_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz16_16(const uc16_t *val, uwrite_uc16_t write, void *write_arg) {
    UWRITE_UZX_X(val, write, write_arg, 16);
}

size_t uwrite_uz16n_16(const uc16_t *val, size_t val_len, uwrite_uc16_t write, void *write_arg) {
    UWRITE_UZXN_X(val, val_len, write, write_arg, 16);
}

size_t uwrite_ucv16_16(ucv16_t val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz16n_16(UCV16_CEXPAND(val), write, write_arg);
}

size_t uwrite_us16_16(const us16_t *val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz16n_16(US16_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv16_16(uv16_t val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz16n_16(UV16_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz8_16(const uc8_t *val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz8n_16(val, uz8_len(val), write, write_arg);
}

size_t uwrite_uz8n_16(const uc8_t *val, size_t val_len, uwrite_uc16_t write, void *write_arg) {
    assert(val && write);

    size_t   written = 0;
    uc16_t   c16[2];
    unsigned c16_len;

    for (size_t i = 0; i < val_len; written = i, i += uc8_len(val[i])) {
        c16_len = uc16_from_uc8n(c16, val + i, val_len - i);

        for (unsigned j = 0; j < c16_len; ++j)
            if (write(c16[j], write_arg))
                goto quit;
    }

quit:
    return written;
}

size_t uwrite_ucv8_16(ucv8_t val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz8n_16(UCV8_CEXPAND(val), write, write_arg);
}

size_t uwrite_us8_16(const us8_t *val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz8n_16(US8_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv8_16(uv8_t val, uwrite_uc16_t write, void *write_arg) {
    return uwrite_uz8n_16(UV8_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz32_8(const uc32_t *val, uwrite_uc8_t write, void *write_arg) {
    assert(val && write);

    const uc32_t *val_begin = val;

    for (; *val; ++val) {
        uc8_t    c8[4];
        unsigned c8_len = uc8_from_uc32_imm(c8, *val);

        for (unsigned i = 0; i < c8_len; ++i)
            if (write(c8[i], write_arg))
                goto quit;
    }

quit:
    return val - val_begin;
}

size_t uwrite_uz32n_8(const uc32_t *val, size_t val_len, uwrite_uc8_t write, void *write_arg) {
    assert(val && write);

    const uc32_t *val_begin = val;

    for (; val_len--; ++val) {
        uc8_t    c8[4];
        unsigned c8_len = uc8_from_uc32_imm(c8, *val);

        for (unsigned i = 0; i < c8_len; ++i)
            if (write(c8[i], write_arg))
                goto quit;
    }

quit:
    return val - val_begin;
}

size_t uwrite_ucv32_8(ucv32_t val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz32n_8(UCV32_CEXPAND(val), write, write_arg);
}

size_t uwrite_us32_8(const us32_t *val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz32n_8(US32_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv32_8(uv32_t val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz32n_8(UV32_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz16_8(const uc16_t *val, uwrite_uc8_t write, void *write_arg) {
	return uwrite_uz16n_8(val, uz16_len(val), write, write_arg);
}

size_t uwrite_uz16n_8(const uc16_t *val, size_t val_len, uwrite_uc8_t write, void *write_arg) {
    assert(val && write);

    size_t   written = 0;
    uc8_t    c8[4];
    unsigned c8_len;

    for (size_t i = 0; i < val_len; written = i, i += uc16_len(val[i])) {
        c8_len = uc8_from_uc16n(c8, val + i, val_len - i);

        for (unsigned j = 0; j < c8_len; ++j)
            if (write(c8[j], write_arg))
                goto quit;
    }
    
quit:
    return written;
}

size_t uwrite_ucv16_8(ucv16_t val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz16n_8(UCV16_CEXPAND(val), write, write_arg);
}

size_t uwrite_us16_8(const us16_t *val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz16n_8(US16_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv16_8(uv16_t val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz16n_8(UV16_CEXPAND(val), write, write_arg);
}

size_t uwrite_uz8_8(const uc8_t *val, uwrite_uc8_t write, void *write_arg) {
    UWRITE_UZX_X(val, write, write_arg, 8);
}

size_t uwrite_uz8n_8(const uc8_t *val, size_t val_len, uwrite_uc8_t write, void *write_arg) {
    UWRITE_UZXN_X(val, val_len, write, write_arg, 8);
}

size_t uwrite_ucv8_8(ucv8_t val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz8n_8(UCV8_CEXPAND(val), write, write_arg);
}

size_t uwrite_us8_8(const us8_t *val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz8n_8(US8_CEXPAND(val), write, write_arg);
}

size_t uwrite_uv8_8(uv8_t val, uwrite_uc8_t write, void *write_arg) {
    return uwrite_uz8n_8(UV8_CEXPAND(val), write, write_arg);
}