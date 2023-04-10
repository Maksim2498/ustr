#include "char.h"

#include <assert.h>

#include <ustr/char.h>

#define UWRITE_UCX_X(c, n, write, write_arg) \
    assert(write);                           \
                                             \
    size_t written = 0;                      \
                                             \
    while (n--) {                            \
        if (write(c, write_arg))             \
            break;                           \
                                             \
        ++written;                           \
    }                                        \
                                             \
    return written

size_t uwrite_uc32_32(uc32_t c, size_t n, uwrite_uc32_t write, void *write_arg) {
    UWRITE_UCX_X(c, n, write, write_arg);
}

size_t uwrite_uc16_32(uc16_t c, size_t n, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uc32_32(c, n, write, write_arg);
}

size_t uwrite_uc8_32(uc8_t c, size_t n, uwrite_uc32_t write, void *write_arg) {
    return uwrite_uc32_32(c, n, write, write_arg);
}

size_t uwrite_uc32_16(uc32_t c, size_t n, uwrite_uc16_t write, void *write_arg) {
    assert(write);

    size_t   written = 0;
    uc16_t   c16[2];
    unsigned c16_len = uc16_from_uc32_imm(c16, c);

    if (c16_len == 1)
        while (n--) {
            if (write(c16[0], write_arg))
                break;

            ++written;
        }
    else
        while (n--) {
            if (write(c16[0], write_arg) || write(c16[1], write_arg))
                break;

            ++written;
        }

    return written;
}

size_t uwrite_uc16_16(uc16_t c, size_t n, uwrite_uc16_t write, void *write_arg) {
    UWRITE_UCX_X(c, n, write, write_arg);
}

size_t uwrite_uc8_16(uc8_t c, size_t n, uwrite_uc16_t write, void *write_arg) {
	return uwrite_uc16_16(c, n, write, write_arg);
}

size_t uwrite_uc32_8(uc32_t c, size_t n, uwrite_uc8_t write, void *write_arg) {
    assert(write);

    size_t   written = 0;
    uc8_t    c8[4];
    unsigned c8_len  = uc8_from_uc32_imm(c8, c);

    while (n--)
        for (unsigned i = 0; i < c8_len; ++i) {
            if (write(c8[i], write_arg))
                goto quit;

            ++written;
        }

quit:
    return written;
}

size_t uwrite_uc16_8(uc16_t c, size_t n, uwrite_uc8_t write, void *write_arg) {
    assert(write);

    size_t   written = 0;
    uc16_t   c16[2]  = { c, 0 };
    uc8_t    c8[4];
    unsigned c8_len  = uc8_from_uc16(c8, c16);

    while (n--)
        for (unsigned i = 0; i < c8_len; ++i) {
            if (write(c8[i], write_arg))
                goto quit;

            ++written;
        }

quit:
    return written;
}

size_t uwrite_uc8_8(uc8_t c, size_t n, uwrite_uc8_t write, void *write_arg) {
    UWRITE_UCX_X(c, n, write, write_arg);
}