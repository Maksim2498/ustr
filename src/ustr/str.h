#ifndef USTR_STR_H
#define USTR_STR_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "type/fmt/case.h"
#include "type/fmt/float.h"
#include "type/fmt/int.h"
#include "type/attr.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/encoding.h"
#include "type/str.h"
#include "type/view.h"
#include "util/export.h"

// Expand

#define US32_CEXPAND(str) us32_cchars(str), (str)->len
#define  US32_EXPAND(str)  us32_chars(str), (str)->len

#define US16_CEXPAND(str) us16_cchars(str), (str)->len
#define  US16_EXPAND(str)  us16_chars(str), (str)->len

#define  US8_CEXPAND(str)  us8_cchars(str), (str)->len
#define   US8_EXPAND(str)   us8_chars(str), (str)->len

// Creation

// - Literal

#define us32(literal)                           \
    us32_from_uz32n(                            \
        U##litreal,                             \
        sizeof(U##literal) / sizeof(uc32_t) - 1 \
    )

#define us32_e(literal, error)                   \
    us32_from_uz32n_e(                           \
        U##litreal,                              \
        sizeof(U##literal) / sizeof(uc32_t) - 1, \
        (error)                                  \
    )


#define us16(literal)                           \
    us16_from_uz16n(                            \
        u##litreal,                             \
        sizeof(u##literal) / sizeof(uc16_t) - 1 \
    )

#define us16_e(literal, error)                   \
    us16_from_uz16n_e(                           \
        u##litreal,                              \
        sizeof(u##literal) / sizeof(uc16_t) - 1, \
        (error)                                  \
    )


#define us8(literal)                            \
    us8_from_uz8n(                              \
        (const uc8_t *) u8##litreal,            \
        sizeof(u8##literal) / sizeof(uc8_t) - 1 \
    )

#define us8_e(literal, error)                    \
    us8_from_uz8n_e(                             \
        (const uc8_t *) u8##litreal,             \
        sizeof(u8##literal) / sizeof(uc8_t) - 1, \
        (error)                                  \
    )

// - Conversion

UEXPORT us32_t us32_from_uc32(uc32_t from);
UEXPORT us32_t us32_from_uc32_e(uc32_t from, bool *error);
UEXPORT us32_t us32_from_uc32n(uc32_t from, size_t n);
UEXPORT us32_t us32_from_uc32n_e(uc32_t from, size_t n, bool *error);
UEXPORT us32_t us32_from_uz32(const uc32_t *from);
UEXPORT us32_t us32_from_uz32_e(const uc32_t *from, bool *error);
UEXPORT us32_t us32_from_uz32_range(const uc32_t *from, size_t begin, size_t len);
UEXPORT us32_t us32_from_uz32_range_e(const uc32_t *from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_uz32n(const uc32_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz32n_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us32_t us32_from_uz32n_range(const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us32_t us32_from_uz32n_range_e(const uc32_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_ucv32(ucv32_t from);
UEXPORT us32_t us32_from_ucv32_e(ucv32_t from, bool *error);
UEXPORT us32_t us32_from_ucv32_range(ucv32_t from, size_t begin, size_t len);
UEXPORT us32_t us32_from_ucv32_range_e(ucv32_t from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_uv32(uv32_t from);
UEXPORT us32_t us32_from_uv32_e(uv32_t from, bool *error);
UEXPORT us32_t us32_from_uv32_range(uv32_t from, size_t begin, size_t len);
UEXPORT us32_t us32_from_uv32_range_e(uv32_t from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_us32(const us32_t *from);
UEXPORT us32_t us32_from_us32_e(const us32_t *from, bool *error);
UEXPORT us32_t us32_from_us32_range(const us32_t *from, size_t begin, size_t len);
UEXPORT us32_t us32_from_us32_range_e(const us32_t *from, size_t begin, size_t len, bool *error);

UEXPORT us32_t us32_from_uc16(uc16_t from);
UEXPORT us32_t us32_from_uc16_e(uc16_t from, bool *error);
UEXPORT us32_t us32_from_uc16n(uc16_t from, size_t n);
UEXPORT us32_t us32_from_uc16n_e(uc16_t from, size_t n, bool *error);
UEXPORT us32_t us32_from_uz16(const uc16_t *from);
UEXPORT us32_t us32_from_uz16_e(const uc16_t *from, bool *error);
UEXPORT us32_t us32_from_uz16_range(const uc16_t *from, size_t begin, size_t len);
UEXPORT us32_t us32_from_uz16_range_e(const uc16_t *from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_uz16n(const uc16_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz16n_e(const uc16_t *from, size_t from_len, bool *error);
UEXPORT us32_t us32_from_uz16n_range(const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us32_t us32_from_uz16n_range_e(const uc16_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_ucv16(ucv16_t from);
UEXPORT us32_t us32_from_ucv16_e(ucv16_t from, bool *error);
UEXPORT us32_t us32_from_ucv16_range(ucv16_t from, size_t begin, size_t len);
UEXPORT us32_t us32_from_ucv16_range_e(ucv16_t from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_uv16(uv16_t from);
UEXPORT us32_t us32_from_uv16_e(uv16_t from, bool *error);
UEXPORT us32_t us32_from_uv16_range(uv16_t from, size_t begin, size_t len);
UEXPORT us32_t us32_from_uv16_range_e(uv16_t from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_us16(const us16_t *from);
UEXPORT us32_t us32_from_us16_e(const us16_t *from, bool *error);
UEXPORT us32_t us32_from_us16_range(const us16_t *from, size_t begin, size_t len);
UEXPORT us32_t us32_from_us16_range_e(const us16_t *from, size_t begin, size_t len, bool *error);

UEXPORT us32_t us32_from_uc8(uc8_t from);
UEXPORT us32_t us32_from_uc8_e(uc8_t from, bool *error);
UEXPORT us32_t us32_from_uc8n(uc8_t from, size_t n);
UEXPORT us32_t us32_from_uc8n_e(uc8_t from, size_t n, bool *error);
UEXPORT us32_t us32_from_uz8(const uc8_t *from);
UEXPORT us32_t us32_from_uz8_e(const uc8_t *from, bool *error);
UEXPORT us32_t us32_from_uz8_range(const uc8_t *from, size_t begin, size_t len);
UEXPORT us32_t us32_from_uz8_range_e(const uc8_t *from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_uz8n(const uc8_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz8n_e(const uc8_t *from, size_t from_len, bool *error);
UEXPORT us32_t us32_from_uz8n_range(const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us32_t us32_from_uz8n_range_e(const uc8_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_ucv8(ucv8_t from);
UEXPORT us32_t us32_from_ucv8_e(ucv8_t from, bool *error);
UEXPORT us32_t us32_from_ucv8_range(ucv8_t from, size_t begin, size_t len);
UEXPORT us32_t us32_from_ucv8_range_e(ucv8_t from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_uv8(uv8_t from);
UEXPORT us32_t us32_from_uv8_e(uv8_t from, bool *error);
UEXPORT us32_t us32_from_uv8_range(uv8_t from, size_t begin, size_t len);
UEXPORT us32_t us32_from_uv8_range_e(uv8_t from, size_t begin, size_t len, bool *error);
UEXPORT us32_t us32_from_us8(const us8_t *from);
UEXPORT us32_t us32_from_us8_e(const us8_t *from, bool *error);
UEXPORT us32_t us32_from_us8_range(const us8_t *from, size_t begin, size_t len);
UEXPORT us32_t us32_from_us8_range_e(const us8_t *from, size_t begin, size_t len, bool *error);

UEXPORT us32_t us32_from_bytes(const void *from, uencoding_t encoding);
UEXPORT us32_t us32_from_bytes_e(const void *from, uencoding_t encoding, bool *error);
UEXPORT us32_t us32_from_bytesn(const void *from, size_t from_size, uencoding_t encoding);
UEXPORT us32_t us32_from_bytesn_e(const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT us32_t us32_from_uz32le(const uc32_t *from);
UEXPORT us32_t us32_from_uz32le_e(const uc32_t *from, bool *error);
UEXPORT us32_t us32_from_uz32len(const uc32_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz32len_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us32_t us32_from_uz16le(const uc16_t *from);
UEXPORT us32_t us32_from_uz16le_e(const uc16_t *from, bool *error);
UEXPORT us32_t us32_from_uz16len(const uc16_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz16len_e(const uc16_t *from, size_t from_len, bool *error);
UEXPORT us32_t us32_from_uz32be(const uc32_t *from);
UEXPORT us32_t us32_from_uz32be_e(const uc32_t *from, bool *error);
UEXPORT us32_t us32_from_uz32ben(const uc32_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz32ben_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us32_t us32_from_uz16be(const uc16_t *from);
UEXPORT us32_t us32_from_uz16be_e(const uc16_t *from, bool *error);
UEXPORT us32_t us32_from_uz16ben(const uc16_t *from, size_t from_len);
UEXPORT us32_t us32_from_uz16ben_e(const uc16_t *from, size_t from_len, bool *error);


UEXPORT us16_t us16_from_uc32(uc32_t from);
UEXPORT us16_t us16_from_uc32_e(uc32_t from, bool *error);
UEXPORT us16_t us16_from_uc32n(uc32_t from, size_t n);
UEXPORT us16_t us16_from_uc32n_e(uc32_t from, size_t n, bool *error);
UEXPORT us16_t us16_from_uz32(const uc32_t *from);
UEXPORT us16_t us16_from_uz32_e(const uc32_t *from, bool *error);
UEXPORT us16_t us16_from_uz32_range(const uc32_t *from, size_t begin, size_t len);
UEXPORT us16_t us16_from_uz32_range_e(const uc32_t *from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_uz32n(const uc32_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz32n_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us16_t us16_from_uz32n_range(const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us16_t us16_from_uz32n_range_e(const uc32_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_ucv32(ucv32_t from);
UEXPORT us16_t us16_from_ucv32_e(ucv32_t from, bool *error);
UEXPORT us16_t us16_from_ucv32_range(ucv32_t from, size_t begin, size_t len);
UEXPORT us16_t us16_from_ucv32_range_e(ucv32_t from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_uv32(uv32_t from);
UEXPORT us16_t us16_from_uv32_e(uv32_t from, bool *error);
UEXPORT us16_t us16_from_uv32_range(uv32_t from, size_t begin, size_t len);
UEXPORT us16_t us16_from_uv32_range_e(uv32_t from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_us32(const us32_t *from);
UEXPORT us16_t us16_from_us32_e(const us32_t *from, bool *error);
UEXPORT us16_t us16_from_us32_range(const us32_t *from, size_t begin, size_t len);
UEXPORT us16_t us16_from_us32_range_e(const us32_t *from, size_t begin, size_t len, bool *error);

UEXPORT us16_t us16_from_uc16(uc16_t from);
UEXPORT us16_t us16_from_uc16_e(uc16_t from, bool *error);
UEXPORT us16_t us16_from_uc16n(uc16_t from, size_t n);
UEXPORT us16_t us16_from_uc16n_e(uc16_t from, size_t n, bool *error);
UEXPORT us16_t us16_from_uz16(const uc16_t *from);
UEXPORT us16_t us16_from_uz16_e(const uc16_t *from, bool *error);
UEXPORT us16_t us16_from_uz16_range(const uc16_t *from, size_t begin, size_t len);
UEXPORT us16_t us16_from_uz16_range_e(const uc16_t *from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_uz16n(const uc16_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz16n_e(const uc16_t *from, size_t from_len, bool *error);
UEXPORT us16_t us16_from_uz16n_range(const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us16_t us16_from_uz16n_range_e(const uc16_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_ucv16(ucv16_t from);
UEXPORT us16_t us16_from_ucv16_e(ucv16_t from, bool *error);
UEXPORT us16_t us16_from_ucv16_range(ucv16_t from, size_t begin, size_t len);
UEXPORT us16_t us16_from_ucv16_range_e(ucv16_t from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_uv16(uv16_t from);
UEXPORT us16_t us16_from_uv16_e(uv16_t from, bool *error);
UEXPORT us16_t us16_from_uv16_range(uv16_t from, size_t begin, size_t len);
UEXPORT us16_t us16_from_uv16_range_e(uv16_t from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_us16(const us16_t *from);
UEXPORT us16_t us16_from_us16_e(const us16_t *from, bool *error);
UEXPORT us16_t us16_from_us16_range(const us16_t *from, size_t begin, size_t len);
UEXPORT us16_t us16_from_us16_range_e(const us16_t *from, size_t begin, size_t len, bool *error);

UEXPORT us16_t us16_from_uc8(uc8_t from);
UEXPORT us16_t us16_from_uc8_e(uc8_t from, bool *error);
UEXPORT us16_t us16_from_uc8n(uc8_t from, size_t n);
UEXPORT us16_t us16_from_uc8n_e(uc8_t from, size_t n, bool *error);
UEXPORT us16_t us16_from_uz8(const uc8_t *from);
UEXPORT us16_t us16_from_uz8_e(const uc8_t *from, bool *error);
UEXPORT us16_t us16_from_uz8_range(const uc8_t *from, size_t begin, size_t len);
UEXPORT us16_t us16_from_uz8_range_e(const uc8_t *from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_uz8n(const uc8_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz8n_e(const uc8_t *from, size_t from_len, bool *error);
UEXPORT us16_t us16_from_uz8n_range(const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us16_t us16_from_uz8n_range_e(const uc8_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_ucv8(ucv8_t from);
UEXPORT us16_t us16_from_ucv8_e(ucv8_t from, bool *error);
UEXPORT us16_t us16_from_ucv8_range(ucv8_t from, size_t begin, size_t len);
UEXPORT us16_t us16_from_ucv8_range_e(ucv8_t from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_uv8(uv8_t from);
UEXPORT us16_t us16_from_uv8_e(uv8_t from, bool *error);
UEXPORT us16_t us16_from_uv8_range(uv8_t from, size_t begin, size_t len);
UEXPORT us16_t us16_from_uv8_range_e(uv8_t from, size_t begin, size_t len, bool *error);
UEXPORT us16_t us16_from_us8(const us8_t *from);
UEXPORT us16_t us16_from_us8_e(const us8_t *from, bool *error);
UEXPORT us16_t us16_from_us8_range(const us8_t *from, size_t begin, size_t len);
UEXPORT us16_t us16_from_us8_range_e(const us8_t *from, size_t begin, size_t len, bool *error);

UEXPORT us16_t us16_from_bytes(const void *from, uencoding_t encoding);
UEXPORT us16_t us16_from_bytes_e(const void *from, uencoding_t encoding, bool *error);
UEXPORT us16_t us16_from_bytesn(const void *from, size_t from_size, uencoding_t encoding);
UEXPORT us16_t us16_from_bytesn_e(const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT us16_t us16_from_uz32le(const uc32_t *from);
UEXPORT us16_t us16_from_uz32le_e(const uc32_t *from, bool *error);
UEXPORT us16_t us16_from_uz32len(const uc32_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz32len_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us16_t us16_from_uz16le(const uc16_t *from);
UEXPORT us16_t us16_from_uz16le_e(const uc16_t *from, bool *error);
UEXPORT us16_t us16_from_uz16len(const uc16_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz16len_e(const uc16_t *from, size_t from_len, bool *error);
UEXPORT us16_t us16_from_uz32be(const uc32_t *from);
UEXPORT us16_t us16_from_uz32be_e(const uc32_t *from, bool *error);
UEXPORT us16_t us16_from_uz32ben(const uc32_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz32ben_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us16_t us16_from_uz16be(const uc16_t *from);
UEXPORT us16_t us16_from_uz16be_e(const uc16_t *from, bool *error);
UEXPORT us16_t us16_from_uz16ben(const uc16_t *from, size_t from_len);
UEXPORT us16_t us16_from_uz16ben_e(const uc16_t *from, size_t from_len, bool *error);


UEXPORT us8_t us8_from_uc32(uc32_t from);
UEXPORT us8_t us8_from_uc32_e(uc32_t from, bool *error);
UEXPORT us8_t us8_from_uc32n(uc32_t from, size_t n);
UEXPORT us8_t us8_from_uc32n_e(uc32_t from, size_t n, bool *error);
UEXPORT us8_t us8_from_uz32(const uc32_t *from);
UEXPORT us8_t us8_from_uz32_e(const uc32_t *from, bool *error);
UEXPORT us8_t us8_from_uz32_range(const uc32_t *from, size_t begin, size_t len);
UEXPORT us8_t us8_from_uz32_range_e(const uc32_t *from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_uz32n(const uc32_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz32n_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us8_t us8_from_uz32n_range(const uc32_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us8_t us8_from_uz32n_range_e(const uc32_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_ucv32(ucv32_t from);
UEXPORT us8_t us8_from_ucv32_e(ucv32_t from, bool *error);
UEXPORT us8_t us8_from_ucv32_range(ucv32_t from, size_t begin, size_t len);
UEXPORT us8_t us8_from_ucv32_range_e(ucv32_t from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_uv32(uv32_t from);
UEXPORT us8_t us8_from_uv32_e(uv32_t from, bool *error);
UEXPORT us8_t us8_from_uv32_range(uv32_t from, size_t begin, size_t len);
UEXPORT us8_t us8_from_uv32_range_e(uv32_t from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_us32(const us32_t *from);
UEXPORT us8_t us8_from_us32_e(const us32_t *from, bool *error);
UEXPORT us8_t us8_from_us32_range(const us32_t *from, size_t begin, size_t len);
UEXPORT us8_t us8_from_us32_range_e(const us32_t *from, size_t begin, size_t len, bool *error);

UEXPORT us8_t us8_from_uc16(uc16_t from);
UEXPORT us8_t us8_from_uc16_e(uc16_t from, bool *error);
UEXPORT us8_t us8_from_uc16n(uc16_t from, size_t n);
UEXPORT us8_t us8_from_uc16n_e(uc16_t from, size_t n, bool *error);
UEXPORT us8_t us8_from_uz16(const uc16_t *from);
UEXPORT us8_t us8_from_uz16_e(const uc16_t *from, bool *error);
UEXPORT us8_t us8_from_uz16_range(const uc16_t *from, size_t begin, size_t len);
UEXPORT us8_t us8_from_uz16_range_e(const uc16_t *from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_uz16n(const uc16_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz16n_e(const uc16_t *from, size_t from_len, bool *error);
UEXPORT us8_t us8_from_uz16n_range(const uc16_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us8_t us8_from_uz16n_range_e(const uc16_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_ucv16(ucv16_t from);
UEXPORT us8_t us8_from_ucv16_e(ucv16_t from, bool *error);
UEXPORT us8_t us8_from_ucv16_range(ucv16_t from, size_t begin, size_t len);
UEXPORT us8_t us8_from_ucv16_range_e(ucv16_t from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_uv16(uv16_t from);
UEXPORT us8_t us8_from_uv16_e(uv16_t from, bool *error);
UEXPORT us8_t us8_from_uv16_range(uv16_t from, size_t begin, size_t len);
UEXPORT us8_t us8_from_uv16_range_e(uv16_t from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_us16(const us16_t *from);
UEXPORT us8_t us8_from_us16_e(const us16_t *from, bool *error);
UEXPORT us8_t us8_from_us16_range(const us16_t *from, size_t begin, size_t len);
UEXPORT us8_t us8_from_us16_range_e(const us16_t *from, size_t begin, size_t len, bool *error);

UEXPORT us8_t us8_from_uc8(uc8_t from);
UEXPORT us8_t us8_from_uc8_e(uc8_t from, bool *error);
UEXPORT us8_t us8_from_uc8n(uc8_t from, size_t n);
UEXPORT us8_t us8_from_uc8n_e(uc8_t from, size_t n, bool *error);
UEXPORT us8_t us8_from_uz8(const uc8_t *from);
UEXPORT us8_t us8_from_uz8_e(const uc8_t *from, bool *error);
UEXPORT us8_t us8_from_uz8_range(const uc8_t *from, size_t begin, size_t len);
UEXPORT us8_t us8_from_uz8_range_e(const uc8_t *from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_uz8n(const uc8_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz8n_e(const uc8_t *from, size_t from_len, bool *error);
UEXPORT us8_t us8_from_uz8n_range(const uc8_t *from, size_t from_len, size_t begin, size_t len);
UEXPORT us8_t us8_from_uz8n_range_e(const uc8_t *from, size_t from_len, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_ucv8(ucv8_t from);
UEXPORT us8_t us8_from_ucv8_e(ucv8_t from, bool *error);
UEXPORT us8_t us8_from_ucv8_range(ucv8_t from, size_t begin, size_t len);
UEXPORT us8_t us8_from_ucv8_range_e(ucv8_t from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_uv8(uv8_t from);
UEXPORT us8_t us8_from_uv8_e(uv8_t from, bool *error);
UEXPORT us8_t us8_from_uv8_range(uv8_t from, size_t begin, size_t len);
UEXPORT us8_t us8_from_uv8_range_e(uv8_t from, size_t begin, size_t len, bool *error);
UEXPORT us8_t us8_from_us8(const us8_t *from);
UEXPORT us8_t us8_from_us8_e(const us8_t *from, bool *error);
UEXPORT us8_t us8_from_us8_range(const us8_t *from, size_t begin, size_t len);
UEXPORT us8_t us8_from_us8_range_e(const us8_t *from, size_t begin, size_t len, bool *error);

UEXPORT us8_t us8_from_bytes(const void *from, uencoding_t encoding);
UEXPORT us8_t us8_from_bytes_e(const void *from, uencoding_t encoding, bool *error);
UEXPORT us8_t us8_from_bytesn(const void *from, size_t from_size, uencoding_t encoding);
UEXPORT us8_t us8_from_bytesn_e(const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT us8_t us8_from_uz32le(const uc32_t *from);
UEXPORT us8_t us8_from_uz32le_e(const uc32_t *from, bool *error);
UEXPORT us8_t us8_from_uz32len(const uc32_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz32len_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us8_t us8_from_uz16le(const uc16_t *from);
UEXPORT us8_t us8_from_uz16le_e(const uc16_t *from, bool *error);
UEXPORT us8_t us8_from_uz16len(const uc16_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz16len_e(const uc16_t *from, size_t from_len, bool *error);
UEXPORT us8_t us8_from_uz32be(const uc32_t *from);
UEXPORT us8_t us8_from_uz32be_e(const uc32_t *from, bool *error);
UEXPORT us8_t us8_from_uz32ben(const uc32_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz32ben_e(const uc32_t *from, size_t from_len, bool *error);
UEXPORT us8_t us8_from_uz16be(const uc16_t *from);
UEXPORT us8_t us8_from_uz16be_e(const uc16_t *from, bool *error);
UEXPORT us8_t us8_from_uz16ben(const uc16_t *from, size_t from_len);
UEXPORT us8_t us8_from_uz16ben_e(const uc16_t *from, size_t from_len, bool *error);

// - From format

UEXPORT us32_t us32_from_fmt_uz32(const uc32_t *from, ...);
UEXPORT us32_t us32_from_fmt_uz32_e(const uc32_t *from, bool *error, ...);
UEXPORT us32_t us32_from_fmt_uz32_v(const uc32_t *from, va_list *args);
UEXPORT us32_t us32_from_fmt_uz32_v_e(const uc32_t *from, va_list *args, bool *error);
UEXPORT us32_t us32_from_fmt_uz32n(const uc32_t *from, size_t from_len, ...);
UEXPORT us32_t us32_from_fmt_uz32n_e(const uc32_t *from, size_t from_len, bool *error, ...);
UEXPORT us32_t us32_from_fmt_uz32n_v(const uc32_t *from, size_t from_len, va_list *args);
UEXPORT us32_t us32_from_fmt_uz32n_v_e(const uc32_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT us32_t us32_from_fmt_ucv32(ucv32_t from, ...);
UEXPORT us32_t us32_from_fmt_ucv32_e(ucv32_t from, bool *error, ...);
UEXPORT us32_t us32_from_fmt_ucv32_v(ucv32_t from, va_list *args);
UEXPORT us32_t us32_from_fmt_ucv32_v_e(ucv32_t from, va_list *args, bool *error);
UEXPORT us32_t us32_from_fmt_uv32(uv32_t from, ...);
UEXPORT us32_t us32_from_fmt_uv32_e(uv32_t from, bool *error, ...);
UEXPORT us32_t us32_from_fmt_uv32_v(uv32_t from, va_list *args);
UEXPORT us32_t us32_from_fmt_uv32_v_e(uv32_t from, va_list *args, bool *error);
UEXPORT us32_t us32_from_fmt_us32(const us32_t *from, ...);
UEXPORT us32_t us32_from_fmt_us32_e(const us32_t *from, bool *error, ...);
UEXPORT us32_t us32_from_fmt_us32_v(const us32_t *from, va_list *args);
UEXPORT us32_t us32_from_fmt_us32_v_e(const us32_t *from, va_list *args, bool *error);

UEXPORT us16_t us16_from_fmt_uz16(const uc16_t *from, ...);
UEXPORT us16_t us16_from_fmt_uz16_e(const uc16_t *from, bool *error, ...);
UEXPORT us16_t us16_from_fmt_uz16_v(const uc16_t *from, va_list *args);
UEXPORT us16_t us16_from_fmt_uz16_v_e(const uc16_t *from, va_list *args, bool *error);
UEXPORT us16_t us16_from_fmt_uz16n(const uc16_t *from, size_t from_len, ...);
UEXPORT us16_t us16_from_fmt_uz16n_e(const uc16_t *from, size_t from_len, bool *error, ...);
UEXPORT us16_t us16_from_fmt_uz16n_v(const uc16_t *from, size_t from_len, va_list *args);
UEXPORT us16_t us16_from_fmt_uz16n_v_e(const uc16_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT us16_t us16_from_fmt_ucv16(ucv16_t from, ...);
UEXPORT us16_t us16_from_fmt_ucv16_e(ucv16_t from, bool *error, ...);
UEXPORT us16_t us16_from_fmt_ucv16_v(ucv16_t from, va_list *args);
UEXPORT us16_t us16_from_fmt_ucv16_v_e(ucv16_t from, va_list *args, bool *error);
UEXPORT us16_t us16_from_fmt_uv16(uv16_t from, ...);
UEXPORT us16_t us16_from_fmt_uv16_e(uv16_t from, bool *error, ...);
UEXPORT us16_t us16_from_fmt_uv16_v(uv16_t from, va_list *args);
UEXPORT us16_t us16_from_fmt_uv16_v_e(uv16_t from, va_list *args, bool *error);
UEXPORT us16_t us16_from_fmt_us16(const us16_t *from, ...);
UEXPORT us16_t us16_from_fmt_us16_e(const us16_t *from, bool *error, ...);
UEXPORT us16_t us16_from_fmt_us16_v(const us16_t *from, va_list *args);
UEXPORT us16_t us16_from_fmt_us16_v_e(const us16_t *from, va_list *args, bool *error);

UEXPORT us8_t us8_from_fmt_uz8(const uc8_t *from, ...);
UEXPORT us8_t us8_from_fmt_uz8_e(const uc8_t *from, bool *error, ...);
UEXPORT us8_t us8_from_fmt_uz8_v(const uc8_t *from, va_list *args);
UEXPORT us8_t us8_from_fmt_uz8_v_e(const uc8_t *from, va_list *args, bool *error);
UEXPORT us8_t us8_from_fmt_uz8n(const uc8_t *from, size_t from_len, ...);
UEXPORT us8_t us8_from_fmt_uz8n_e(const uc8_t *from, size_t from_len, bool *error, ...);
UEXPORT us8_t us8_from_fmt_uz8n_v(const uc8_t *from, size_t from_len, va_list *args);
UEXPORT us8_t us8_from_fmt_uz8n_v_e(const uc8_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT us8_t us8_from_fmt_ucv8(ucv8_t from, ...);
UEXPORT us8_t us8_from_fmt_ucv8_e(ucv8_t from, bool *error, ...);
UEXPORT us8_t us8_from_fmt_ucv8_v(ucv8_t from, va_list *args);
UEXPORT us8_t us8_from_fmt_ucv8_v_e(ucv8_t from, va_list *args, bool *error);
UEXPORT us8_t us8_from_fmt_uv8(uv8_t from, ...);
UEXPORT us8_t us8_from_fmt_uv8_e(uv8_t from, bool *error, ...);
UEXPORT us8_t us8_from_fmt_uv8_v(uv8_t from, va_list *args);
UEXPORT us8_t us8_from_fmt_uv8_v_e(uv8_t from, va_list *args, bool *error);
UEXPORT us8_t us8_from_fmt_us8(const us8_t *from, ...);
UEXPORT us8_t us8_from_fmt_us8_e(const us8_t *from, bool *error, ...);
UEXPORT us8_t us8_from_fmt_us8_v(const us8_t *from, va_list *args);
UEXPORT us8_t us8_from_fmt_us8_v_e(const us8_t *from, va_list *args, bool *error);

// - From float

UEXPORT us32_t us32_from_float(double from);
UEXPORT us32_t us32_from_float_e(double from, bool *error);
UEXPORT us32_t us32_from_float_fmt(double from, const struct ufmt32_float_output *fmt);
UEXPORT us32_t us32_from_float_fmt_e(double from, const struct ufmt32_float_output *fmt, bool *error);

UEXPORT us16_t us16_from_float(double from);
UEXPORT us16_t us16_from_float_e(double from, bool *error);
UEXPORT us16_t us16_from_float_fmt(double from, const struct ufmt16_float_output *fmt);
UEXPORT us16_t us16_from_float_fmt_e(double from, const struct ufmt16_float_output *fmt, bool *error);

UEXPORT us8_t us8_from_float(double from);
UEXPORT us8_t us8_from_float_e(double from, bool *error);
UEXPORT us8_t us8_from_float_fmt(double from, const struct ufmt8_float_output *fmt);
UEXPORT us8_t us8_from_float_fmt_e(double from, const struct ufmt8_float_output *fmt, bool *error);

// - From int

UEXPORT us32_t us32_from_int(intmax_t from);
UEXPORT us32_t us32_from_int_e(intmax_t from, bool *error);
UEXPORT us32_t us32_from_int_fmt(intmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT us32_t us32_from_int_fmt_e(intmax_t from, const struct ufmt32_int_output *fmt, bool *error);
UEXPORT us32_t us32_from_uint(uintmax_t from);
UEXPORT us32_t us32_from_uint_e(uintmax_t from, bool *error);
UEXPORT us32_t us32_from_uint_fmt(uintmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT us32_t us32_from_uint_fmt_e(uintmax_t from, const struct ufmt32_int_output *fmt, bool *error);

UEXPORT us16_t us16_from_int(intmax_t from);
UEXPORT us16_t us16_from_int_e(intmax_t from, bool *error);
UEXPORT us16_t us16_from_int_fmt(intmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT us16_t us16_from_int_fmt_e(intmax_t from, const struct ufmt16_int_output *fmt, bool *error);
UEXPORT us16_t us16_from_uint(uintmax_t from);
UEXPORT us16_t us16_from_uint_e(uintmax_t from, bool *error);
UEXPORT us16_t us16_from_uint_fmt(uintmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT us16_t us16_from_uint_fmt_e(uintmax_t from, const struct ufmt16_int_output *fmt, bool *error);

UEXPORT us8_t us8_from_int(intmax_t from);
UEXPORT us8_t us8_from_int_e(intmax_t from, bool *error);
UEXPORT us8_t us8_from_int_fmt(intmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT us8_t us8_from_int_fmt_e(intmax_t from, const struct ufmt8_int_output *fmt, bool *error);
UEXPORT us8_t us8_from_uint(uintmax_t from);
UEXPORT us8_t us8_from_uint_e(uintmax_t from, bool *error);
UEXPORT us8_t us8_from_uint_fmt(uintmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT us8_t us8_from_uint_fmt_e(uintmax_t from, const struct ufmt8_int_output *fmt, bool *error);

// - From bool

UEXPORT us32_t us32_from_bool(bool from);
UEXPORT us32_t us32_from_bool_e(bool from, bool *error);
UEXPORT us32_t us32_from_case_bool(ucase_t ca, bool from);
UEXPORT us32_t us32_from_case_bool_e(ucase_t ca, bool from, bool *error);
UEXPORT us32_t us32_from_lower_bool(bool from);
UEXPORT us32_t us32_from_lower_bool_e(bool from, bool *error);
UEXPORT us32_t us32_from_upper_bool(bool from);
UEXPORT us32_t us32_from_upper_bool_e(bool from, bool *error);

UEXPORT us16_t us16_from_bool(bool from);
UEXPORT us16_t us16_from_bool_e(bool from, bool *error);
UEXPORT us16_t us16_from_case_bool(ucase_t ca, bool from);
UEXPORT us16_t us16_from_case_bool_e(ucase_t ca, bool from, bool *error);
UEXPORT us16_t us16_from_lower_bool(bool from);
UEXPORT us16_t us16_from_lower_bool_e(bool from, bool *error);
UEXPORT us16_t us16_from_upper_bool(bool from);
UEXPORT us16_t us16_from_upper_bool_e(bool from, bool *error);

UEXPORT us8_t us8_from_bool(bool from);
UEXPORT us8_t us8_from_bool_e(bool from, bool *error);
UEXPORT us8_t us8_from_case_bool(ucase_t ca, bool from);
UEXPORT us8_t us8_from_case_bool_e(ucase_t ca, bool from, bool *error);
UEXPORT us8_t us8_from_lower_bool(bool from);
UEXPORT us8_t us8_from_lower_bool_e(bool from, bool *error);
UEXPORT us8_t us8_from_upper_bool(bool from);
UEXPORT us8_t us8_from_upper_bool_e(bool from, bool *error);

// Free

UEXPORT void us32_free(us32_t *str);
UEXPORT void us16_free(us16_t *str);
UEXPORT void us8_free(us8_t *str);

// To bytes

UEXPORT size_t us32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const us32_t *from);
UEXPORT size_t us16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const us16_t *from);
UEXPORT size_t us8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const us8_t *from);

// Length

UEXPORT size_t us32_len(const us32_t *str);
UEXPORT size_t us32_len_n(const us32_t *str, unsigned n);
UEXPORT size_t us32_len_32(const us32_t *str);
UEXPORT size_t us32_len_16(const us32_t *str);
UEXPORT size_t us32_len_8(const us32_t *str);

UEXPORT size_t us16_len(const us16_t *str);
UEXPORT size_t us16_len_n(const us16_t *str, unsigned n);
UEXPORT size_t us16_len_32(const us16_t *str);
UEXPORT size_t us16_len_16(const us16_t *str);
UEXPORT size_t us16_len_8(const us16_t *str);

UEXPORT size_t us8_len(const us8_t *str);
UEXPORT size_t us8_len_n(const us8_t *str, unsigned n);
UEXPORT size_t us8_len_32(const us8_t *str);
UEXPORT size_t us8_len_16(const us8_t *str);
UEXPORT size_t us8_len_8(const us8_t *str);


UEXPORT void us32_clear(us32_t *str);
UEXPORT void us16_clear(us16_t *str);
UEXPORT void us8_clear(us8_t *str);

// Compare

UEXPORT int us32_cmp_uc32(const us32_t *lhs, uc32_t rhs);
UEXPORT int us32_cmp_uz32(const us32_t *lhs, const uc32_t *rhs);
UEXPORT int us32_cmp_uz32n(const us32_t *lhs, const uc32_t *rhs, size_t rhs_len);
UEXPORT int us32_cmp_ucv32(const us32_t *lhs, ucv32_t rhs);
UEXPORT int us32_cmp_uv32(const us32_t *lhs, uv32_t rhs);
UEXPORT int us32_cmp_us32(const us32_t *lhs, const us32_t *rhs);

UEXPORT int us16_cmp_uc16(const us16_t *lhs, uc16_t rhs);
UEXPORT int us16_cmp_uz16(const us16_t *lhs, const uc16_t *rhs);
UEXPORT int us16_cmp_uz16n(const us16_t *lhs, const uc16_t *rhs, size_t rhs_len);
UEXPORT int us16_cmp_ucv16(const us16_t *lhs, ucv16_t rhs);
UEXPORT int us16_cmp_uv16(const us16_t *lhs, uv16_t rhs);
UEXPORT int us16_cmp_us16(const us16_t *lhs, const us16_t *rhs);

UEXPORT int us8_cmp_uc8(const us8_t *lhs, uc8_t rhs);
UEXPORT int us8_cmp_uz8(const us8_t *lhs, const uc8_t *rhs);
UEXPORT int us8_cmp_uz8n(const us8_t *lhs, const uc8_t *rhs, size_t rhs_len);
UEXPORT int us8_cmp_ucv8(const us8_t *lhs, ucv8_t rhs);
UEXPORT int us8_cmp_uv8(const us8_t *lhs, uv8_t rhs);
UEXPORT int us8_cmp_us8(const us8_t *lhs, const us8_t *rhs);

// Fill

UEXPORT void us32_fill_uc32(us32_t *str, uc32_t with);
UEXPORT void us32_fill_uz32(us32_t *str, const uc32_t *with);
UEXPORT void us32_fill_uz32n(us32_t *str, const uc32_t *with, size_t with_len);
UEXPORT void us32_fill_ucv32(us32_t *str, ucv32_t with);
UEXPORT void us32_fill_uv32(us32_t *str, uv32_t with);
UEXPORT void us32_fill_us32(us32_t *str, const us32_t *with);

UEXPORT void us16_fill_uc16(us16_t *str, uc16_t with);
UEXPORT void us16_fill_uz16(us16_t *str, const uc16_t *with);
UEXPORT void us16_fill_uz16n(us16_t *str, const uc16_t *with, size_t with_len);
UEXPORT void us16_fill_ucv16(us16_t *str, ucv16_t with);
UEXPORT void us16_fill_uv16(us16_t *str, uv16_t with);
UEXPORT void us16_fill_us16(us16_t *str, const us16_t *with);

UEXPORT void us8_fill_uc8(us8_t *str, uc8_t with);
UEXPORT void us8_fill_uz8(us8_t *str, const uc8_t *with);
UEXPORT void us8_fill_uz8n(us8_t *str, const uc8_t *with, size_t with_len);
UEXPORT void us8_fill_ucv8(us8_t *str, ucv8_t with);
UEXPORT void us8_fill_uv8(us8_t *str, uv8_t with);
UEXPORT void us8_fill_us8(us8_t *str, const us8_t *with);

// White space

UEXPORT size_t us32_wspace_len(const us32_t *str);
UEXPORT size_t us16_wspace_len(const us16_t *str);
UEXPORT size_t us8_wspace_len(const us8_t *str);

// Trim

UEXPORT size_t us32_trim(us32_t *str);
UEXPORT size_t us32_ltrim(us32_t *str);
UEXPORT size_t us32_rtrim(us32_t *str);

UEXPORT size_t us16_trim(us16_t *str);
UEXPORT size_t us16_ltrim(us16_t *str);
UEXPORT size_t us16_rtrim(us16_t *str);

UEXPORT size_t us8_trim(us8_t *str);
UEXPORT size_t us8_ltrim(us8_t *str);
UEXPORT size_t us8_rtrim(us8_t *str);

// Case change

UEXPORT void us32_to_case(us32_t *str, ucase_t ca);
UEXPORT void us32_to_lower(us32_t *str);
UEXPORT void us32_to_upper(us32_t *str);

UEXPORT void us16_to_case(us16_t *str, ucase_t ca);
UEXPORT void us16_to_lower(us16_t *str);
UEXPORT void us16_to_upper(us16_t *str);

UEXPORT size_t us8_to_case(us8_t *str, ucase_t ca);
UEXPORT size_t us8_to_case_e(us8_t *str, ucase_t ca, bool *error);
UEXPORT size_t us8_to_lower(us8_t *str);
UEXPORT size_t us8_to_lower_e(us8_t *str, bool *error);
UEXPORT size_t us8_to_upper(us8_t *str);
UEXPORT size_t us8_to_upper_e(us8_t *str, bool *error);

// Case change length

UEXPORT size_t us8_case_len(const us8_t *from, ucase_t ca);
UEXPORT size_t us8_lower_len(const us8_t *from);
UEXPORT size_t us8_upper_len(const us8_t *from);

// Reverse

UEXPORT void us32_reverse(us32_t *str);
UEXPORT void us16_reverse(us16_t *str);
UEXPORT void us8_reverse(us8_t *str);

// Split

UEXPORT size_t us32_new_csplit_uc32(const us32_t *str, uc32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t us32_new_csplit_uc32_e(const us32_t *str, uc32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t us32_csplit_uc32(const us32_t *str, uc32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t us32_new_csplit_uz32(const us32_t *str, const uc32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t us32_new_csplit_uz32_e(const us32_t *str, const uc32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t us32_csplit_uz32(const us32_t *str, const uc32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t us32_new_csplit_uz32n(const us32_t *str, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array);
UEXPORT size_t us32_new_csplit_uz32n_e(const us32_t *str, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t us32_csplit_uz32n(const us32_t *str, const uc32_t *sep, size_t sep_len, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t us32_new_csplit_ucv32(const us32_t *str, ucv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t us32_new_csplit_ucv32_e(const us32_t *str, ucv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t us32_csplit_ucv32(const us32_t *str, ucv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t us32_new_csplit_uv32(const us32_t *str, uv32_t sep, UNULLABLE ucv32_t **array);
UEXPORT size_t us32_new_csplit_uv32_e(const us32_t *str, uv32_t sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t us32_csplit_uv32(const us32_t *str, uv32_t sep, UNULLABLE ucv32_t *array, size_t array_len);

UEXPORT size_t us32_new_csplit_us32(const us32_t *str, const us32_t *sep, UNULLABLE ucv32_t **array);
UEXPORT size_t us32_new_csplit_us32_e(const us32_t *str, const us32_t *sep, UNULLABLE ucv32_t **array, bool *error);
UEXPORT size_t us32_csplit_us32(const us32_t *str, const us32_t *sep, UNULLABLE ucv32_t *array, size_t array_len);


UEXPORT size_t us32_new_split_uc32(us32_t *str, uc32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t us32_new_split_uc32_e(us32_t *str, uc32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t us32_split_uc32(us32_t *str, uc32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t us32_new_split_uz32(us32_t *str, const uc32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t us32_new_split_uz32_e(us32_t *str, const uc32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t us32_split_uz32(us32_t *str, const uc32_t *sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t us32_new_split_uz32n(us32_t *str, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array);
UEXPORT size_t us32_new_split_uz32n_e(us32_t *str, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t us32_split_uz32n(us32_t *str, const uc32_t *sep, size_t sep_len, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t us32_new_split_ucv32(us32_t *str, ucv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t us32_new_split_ucv32_e(us32_t *str, ucv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t us32_split_ucv32(us32_t *str, ucv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t us32_new_split_uv32(us32_t *str, uv32_t sep, UNULLABLE uv32_t **array);
UEXPORT size_t us32_new_split_uv32_e(us32_t *str, uv32_t sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t us32_split_uv32(us32_t *str, uv32_t sep, UNULLABLE uv32_t *array, size_t array_len);

UEXPORT size_t us32_new_split_us32(us32_t *str, const us32_t *sep, UNULLABLE uv32_t **array);
UEXPORT size_t us32_new_split_us32_e(us32_t *str, const us32_t *sep, UNULLABLE uv32_t **array, bool *error);
UEXPORT size_t us32_split_us32(us32_t *str, const us32_t *sep, UNULLABLE uv32_t *array, size_t array_len);



UEXPORT size_t us16_new_csplit_uc16(const us16_t *str, uc16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t us16_new_csplit_uc16_e(const us16_t *str, uc16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t us16_csplit_uc16(const us16_t *str, uc16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t us16_new_csplit_uz16(const us16_t *str, const uc16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t us16_new_csplit_uz16_e(const us16_t *str, const uc16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t us16_csplit_uz16(const us16_t *str, const uc16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t us16_new_csplit_uz16n(const us16_t *str, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array);
UEXPORT size_t us16_new_csplit_uz16n_e(const us16_t *str, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t us16_csplit_uz16n(const us16_t *str, const uc16_t *sep, size_t sep_len, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t us16_new_csplit_ucv16(const us16_t *str, ucv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t us16_new_csplit_ucv16_e(const us16_t *str, ucv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t us16_csplit_ucv16(const us16_t *str, ucv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t us16_new_csplit_uv16(const us16_t *str, uv16_t sep, UNULLABLE ucv16_t **array);
UEXPORT size_t us16_new_csplit_uv16_e(const us16_t *str, uv16_t sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t us16_csplit_uv16(const us16_t *str, uv16_t sep, UNULLABLE ucv16_t *array, size_t array_len);

UEXPORT size_t us16_new_csplit_us16(const us16_t *str, const us16_t *sep, UNULLABLE ucv16_t **array);
UEXPORT size_t us16_new_csplit_us16_e(const us16_t *str, const us16_t *sep, UNULLABLE ucv16_t **array, bool *error);
UEXPORT size_t us16_csplit_us16(const us16_t *str, const us16_t *sep, UNULLABLE ucv16_t *array, size_t array_len);


UEXPORT size_t us16_new_split_uc16(us16_t *str, uc16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t us16_new_split_uc16_e(us16_t *str, uc16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t us16_split_uc16(us16_t *str, uc16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t us16_new_split_uz16(us16_t *str, const uc16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t us16_new_split_uz16_e(us16_t *str, const uc16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t us16_split_uz16(us16_t *str, const uc16_t *sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t us16_new_split_uz16n(us16_t *str, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array);
UEXPORT size_t us16_new_split_uz16n_e(us16_t *str, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t us16_split_uz16n(us16_t *str, const uc16_t *sep, size_t sep_len, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t us16_new_split_ucv16(us16_t *str, ucv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t us16_new_split_ucv16_e(us16_t *str, ucv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t us16_split_ucv16(us16_t *str, ucv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t us16_new_split_uv16(us16_t *str, uv16_t sep, UNULLABLE uv16_t **array);
UEXPORT size_t us16_new_split_uv16_e(us16_t *str, uv16_t sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t us16_split_uv16(us16_t *str, uv16_t sep, UNULLABLE uv16_t *array, size_t array_len);

UEXPORT size_t us16_new_split_us16(us16_t *str, const us16_t *sep, UNULLABLE uv16_t **array);
UEXPORT size_t us16_new_split_us16_e(us16_t *str, const us16_t *sep, UNULLABLE uv16_t **array, bool *error);
UEXPORT size_t us16_split_us16(us16_t *str, const us16_t *sep, UNULLABLE uv16_t *array, size_t array_len);



UEXPORT size_t us8_new_csplit_uc8(const us8_t *str, uc8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t us8_new_csplit_uc8_e(const us8_t *str, uc8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t us8_csplit_uc8(const us8_t *str, uc8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t us8_new_csplit_uz8(const us8_t *str, const uc8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t us8_new_csplit_uz8_e(const us8_t *str, const uc8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t us8_csplit_uz8(const us8_t *str, const uc8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t us8_new_csplit_uz8n(const us8_t *str, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array);
UEXPORT size_t us8_new_csplit_uz8n_e(const us8_t *str, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t us8_csplit_uz8n(const us8_t *str, const uc8_t *sep, size_t sep_len, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t us8_new_csplit_ucv8(const us8_t *str, ucv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t us8_new_csplit_ucv8_e(const us8_t *str, ucv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t us8_csplit_ucv8(const us8_t *str, ucv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t us8_new_csplit_uv8(const us8_t *str, uv8_t sep, UNULLABLE ucv8_t **array);
UEXPORT size_t us8_new_csplit_uv8_e(const us8_t *str, uv8_t sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t us8_csplit_uv8(const us8_t *str, uv8_t sep, UNULLABLE ucv8_t *array, size_t array_len);

UEXPORT size_t us8_new_csplit_us8(const us8_t *str, const us8_t *sep, UNULLABLE ucv8_t **array);
UEXPORT size_t us8_new_csplit_us8_e(const us8_t *str, const us8_t *sep, UNULLABLE ucv8_t **array, bool *error);
UEXPORT size_t us8_csplit_us8(const us8_t *str, const us8_t *sep, UNULLABLE ucv8_t *array, size_t array_len);


UEXPORT size_t us8_new_split_uc8(us8_t *str, uc8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t us8_new_split_uc8_e(us8_t *str, uc8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t us8_split_uc8(us8_t *str, uc8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t us8_new_split_uz8(us8_t *str, const uc8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t us8_new_split_uz8_e(us8_t *str, const uc8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t us8_split_uz8(us8_t *str, const uc8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t us8_new_split_uz8n(us8_t *str, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array);
UEXPORT size_t us8_new_split_uz8n_e(us8_t *str, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t us8_split_uz8n(us8_t *str, const uc8_t *sep, size_t sep_len, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t us8_new_split_ucv8(us8_t *str, ucv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t us8_new_split_ucv8_e(us8_t *str, ucv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t us8_split_ucv8(us8_t *str, ucv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t us8_new_split_uv8(us8_t *str, uv8_t sep, UNULLABLE uv8_t **array);
UEXPORT size_t us8_new_split_uv8_e(us8_t *str, uv8_t sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t us8_split_uv8(us8_t *str, uv8_t sep, UNULLABLE uv8_t *array, size_t array_len);

UEXPORT size_t us8_new_split_us8(us8_t *str, const us8_t *sep, UNULLABLE uv8_t **array);
UEXPORT size_t us8_new_split_us8_e(us8_t *str, const us8_t *sep, UNULLABLE uv8_t **array, bool *error);
UEXPORT size_t us8_split_us8(us8_t *str, const us8_t *sep, UNULLABLE uv8_t *array, size_t array_len);

// Contains

UEXPORT bool us32_contains_uc32(const us32_t *str, uc32_t target);
UEXPORT bool us32_contains_uz32(const us32_t *str, const uc32_t *target);
UEXPORT bool us32_contains_uz32n(const us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT bool us32_contains_ucv32(const us32_t *str, ucv32_t target);
UEXPORT bool us32_contains_uv32(const us32_t *str, uv32_t target);
UEXPORT bool us32_contains_us32(const us32_t *str, const us32_t *target);

UEXPORT bool us16_contains_uc16(const us16_t *str, uc16_t target);
UEXPORT bool us16_contains_uz16(const us16_t *str, const uc16_t *target);
UEXPORT bool us16_contains_uz16n(const us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT bool us16_contains_ucv16(const us16_t *str, ucv16_t target);
UEXPORT bool us16_contains_uv16(const us16_t *str, uv16_t target);
UEXPORT bool us16_contains_us16(const us16_t *str, const us16_t *target);

UEXPORT bool us8_contains_uc8(const us8_t *str, uc8_t target);
UEXPORT bool us8_contains_uz8(const us8_t *str, const uc8_t *target);
UEXPORT bool us8_contains_uz8n(const us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT bool us8_contains_ucv8(const us8_t *str, ucv8_t target);
UEXPORT bool us8_contains_uv8(const us8_t *str, uv8_t target);
UEXPORT bool us8_contains_us8(const us8_t *str, const us8_t *target);

// Search

// - Forward

UEXPORT ptrdiff_t us32_find_uc32(const us32_t *str, uc32_t target);
UEXPORT ptrdiff_t us32_find_uc32_from(const us32_t *str, uc32_t target, size_t from);
UEXPORT ptrdiff_t us32_find_uz32(const us32_t *str, const uc32_t *target);
UEXPORT ptrdiff_t us32_find_uz32_from(const us32_t *str, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t us32_find_uz32n(const us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t us32_find_uz32n_from(const us32_t *str, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t us32_find_ucv32(const us32_t *str, ucv32_t target);
UEXPORT ptrdiff_t us32_find_ucv32_from(const us32_t *str, ucv32_t target, size_t from);
UEXPORT ptrdiff_t us32_find_uv32(const us32_t *str, uv32_t target);
UEXPORT ptrdiff_t us32_find_uv32_from(const us32_t *str, uv32_t target, size_t from);
UEXPORT ptrdiff_t us32_find_us32(const us32_t *str, const us32_t *target);
UEXPORT ptrdiff_t us32_find_us32_from(const us32_t *str, const us32_t *target, size_t from);

UEXPORT ptrdiff_t us16_find_uc16(const us16_t *str, uc16_t target);
UEXPORT ptrdiff_t us16_find_uc16_from(const us16_t *str, uc16_t target, size_t from);
UEXPORT ptrdiff_t us16_find_uz16(const us16_t *str, const uc16_t *target);
UEXPORT ptrdiff_t us16_find_uz16_from(const us16_t *str, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t us16_find_uz16n(const us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t us16_find_uz16n_from(const us16_t *str, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t us16_find_ucv16(const us16_t *str, ucv16_t target);
UEXPORT ptrdiff_t us16_find_ucv16_from(const us16_t *str, ucv16_t target, size_t from);
UEXPORT ptrdiff_t us16_find_uv16(const us16_t *str, uv16_t target);
UEXPORT ptrdiff_t us16_find_uv16_from(const us16_t *str, uv16_t target, size_t from);
UEXPORT ptrdiff_t us16_find_us16(const us16_t *str, const us16_t *target);
UEXPORT ptrdiff_t us16_find_us16_from(const us16_t *str, const us16_t *target, size_t from);

UEXPORT ptrdiff_t us8_find_uc8(const us8_t *str, uc8_t target);
UEXPORT ptrdiff_t us8_find_uc8_from(const us8_t *str, uc8_t target, size_t from);
UEXPORT ptrdiff_t us8_find_uz8(const us8_t *str, const uc8_t *target);
UEXPORT ptrdiff_t us8_find_uz8_from(const us8_t *str, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t us8_find_uz8n(const us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t us8_find_uz8n_from(const us8_t *str, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t us8_find_ucv8(const us8_t *str, ucv8_t target);
UEXPORT ptrdiff_t us8_find_ucv8_from(const us8_t *str, ucv8_t target, size_t from);
UEXPORT ptrdiff_t us8_find_uv8(const us8_t *str, uv8_t target);
UEXPORT ptrdiff_t us8_find_uv8_from(const us8_t *str, uv8_t target, size_t from);
UEXPORT ptrdiff_t us8_find_us8(const us8_t *str, const us8_t *target);
UEXPORT ptrdiff_t us8_find_us8_from(const us8_t *str, const us8_t *target, size_t from);

// - Backward

UEXPORT ptrdiff_t us32_rfind_uc32(const us32_t *str, uc32_t target);
UEXPORT ptrdiff_t us32_rfind_uc32_from(const us32_t *str, uc32_t target, size_t from);
UEXPORT ptrdiff_t us32_rfind_uz32(const us32_t *str, const uc32_t *target);
UEXPORT ptrdiff_t us32_rfind_uz32_from(const us32_t *str, const uc32_t *target, size_t from);
UEXPORT ptrdiff_t us32_rfind_uz32n(const us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT ptrdiff_t us32_rfind_uz32n_from(const us32_t *str, const uc32_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t us32_rfind_ucv32(const us32_t *str, ucv32_t target);
UEXPORT ptrdiff_t us32_rfind_ucv32_from(const us32_t *str, ucv32_t target, size_t from);
UEXPORT ptrdiff_t us32_rfind_uv32(const us32_t *str, uv32_t target);
UEXPORT ptrdiff_t us32_rfind_uv32_from(const us32_t *str, uv32_t target, size_t from);
UEXPORT ptrdiff_t us32_rfind_us32(const us32_t *str, const us32_t *target);
UEXPORT ptrdiff_t us32_rfind_us32_from(const us32_t *str, const us32_t *target, size_t from);

UEXPORT ptrdiff_t us16_rfind_uc16(const us16_t *str, uc16_t target);
UEXPORT ptrdiff_t us16_rfind_uc16_from(const us16_t *str, uc16_t target, size_t from);
UEXPORT ptrdiff_t us16_rfind_uz16(const us16_t *str, const uc16_t *target);
UEXPORT ptrdiff_t us16_rfind_uz16_from(const us16_t *str, const uc16_t *target, size_t from);
UEXPORT ptrdiff_t us16_rfind_uz16n(const us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT ptrdiff_t us16_rfind_uz16n_from(const us16_t *str, const uc16_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t us16_rfind_ucv16(const us16_t *str, ucv16_t target);
UEXPORT ptrdiff_t us16_rfind_ucv16_from(const us16_t *str, ucv16_t target, size_t from);
UEXPORT ptrdiff_t us16_rfind_uv16(const us16_t *str, uv16_t target);
UEXPORT ptrdiff_t us16_rfind_uv16_from(const us16_t *str, uv16_t target, size_t from);
UEXPORT ptrdiff_t us16_rfind_us16(const us16_t *str, const us16_t *target);
UEXPORT ptrdiff_t us16_rfind_us16_from(const us16_t *str, const us16_t *target, size_t from);

UEXPORT ptrdiff_t us8_rfind_uc8(const us8_t *str, uc8_t target);
UEXPORT ptrdiff_t us8_rfind_uc8_from(const us8_t *str, uc8_t target, size_t from);
UEXPORT ptrdiff_t us8_rfind_uz8(const us8_t *str, const uc8_t *target);
UEXPORT ptrdiff_t us8_rfind_uz8_from(const us8_t *str, const uc8_t *target, size_t from);
UEXPORT ptrdiff_t us8_rfind_uz8n(const us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT ptrdiff_t us8_rfind_uz8n_from(const us8_t *str, const uc8_t *target, size_t target_len, size_t from);
UEXPORT ptrdiff_t us8_rfind_ucv8(const us8_t *str, ucv8_t target);
UEXPORT ptrdiff_t us8_rfind_ucv8_from(const us8_t *str, ucv8_t target, size_t from);
UEXPORT ptrdiff_t us8_rfind_uv8(const us8_t *str, uv8_t target);
UEXPORT ptrdiff_t us8_rfind_uv8_from(const us8_t *str, uv8_t target, size_t from);
UEXPORT ptrdiff_t us8_rfind_us8(const us8_t *str, const us8_t *target);
UEXPORT ptrdiff_t us8_rfind_us8_from(const us8_t *str, const us8_t *target, size_t from);

// Erase

UEXPORT size_t us32_erase_uc32(us32_t *str, uc32_t target);
UEXPORT size_t us32_erase_uz32(us32_t *str, const uc32_t *target);
UEXPORT size_t us32_erase_uz32n(us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT size_t us32_erase_ucv32(us32_t *str, ucv32_t target);
UEXPORT size_t us32_erase_uv32(us32_t *str, uv32_t target);
UEXPORT size_t us32_erase_us32(us32_t *str, const us32_t *target);

UEXPORT size_t us16_erase_uc16(us16_t *str, uc16_t target);
UEXPORT size_t us16_erase_uz16(us16_t *str, const uc16_t *target);
UEXPORT size_t us16_erase_uz16n(us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT size_t us16_erase_ucv16(us16_t *str, ucv16_t target);
UEXPORT size_t us16_erase_uv16(us16_t *str, uv16_t target);
UEXPORT size_t us16_erase_us16(us16_t *str, const us16_t *target);

UEXPORT size_t us8_erase_uc8(us8_t *str, uc8_t target);
UEXPORT size_t us8_erase_uz8(us8_t *str, const uc8_t *target);
UEXPORT size_t us8_erase_uz8n(us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT size_t us8_erase_ucv8(us8_t *str, ucv8_t target);
UEXPORT size_t us8_erase_uv8(us8_t *str, uv8_t target);
UEXPORT size_t us8_erase_us8(us8_t *str, const us8_t *target);

// Replace

UEXPORT size_t us32_replace_uc32_uc32(us32_t *str, uc32_t from, uc32_t to);
UEXPORT size_t us32_replace_uc32_uz32(us32_t *str, uc32_t from, const uc32_t *to);
UEXPORT size_t us32_replace_uc32_uz32n(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t us32_replace_uc32_ucv32(us32_t *str, uc32_t from, ucv32_t to);
UEXPORT size_t us32_replace_uc32_uv32(us32_t *str, uc32_t from, uv32_t to);
UEXPORT size_t us32_replace_uc32_us32(us32_t *str, uc32_t from, const us32_t *to);

UEXPORT size_t us32_replace_uz32_uc32(us32_t *str, const uc32_t *from, uc32_t to);
UEXPORT size_t us32_replace_uz32_uz32(us32_t *str, const uc32_t *from, const uc32_t *to);
UEXPORT size_t us32_replace_uz32_uz32n(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len);
UEXPORT size_t us32_replace_uz32_ucv32(us32_t *str, const uc32_t *from, ucv32_t to);
UEXPORT size_t us32_replace_uz32_uv32(us32_t *str, const uc32_t *from, uv32_t to);
UEXPORT size_t us32_replace_uz32_us32(us32_t *str, const uc32_t *from, const us32_t *to);

UEXPORT size_t us32_replace_uz32n_uc32(us32_t *str, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t us32_replace_uz32n_uz32(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t us32_replace_uz32n_uz32n(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len);
UEXPORT size_t us32_replace_uz32n_ucv32(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t us32_replace_uz32n_uv32(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t us32_replace_uz32n_us32(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t us32_replace_ucv32_uc32(us32_t *str, ucv32_t from, uc32_t to);
UEXPORT size_t us32_replace_ucv32_uz32(us32_t *str, ucv32_t from, const uc32_t *to);
UEXPORT size_t us32_replace_ucv32_uz32n(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t us32_replace_ucv32_ucv32(us32_t *str, ucv32_t from, ucv32_t to);
UEXPORT size_t us32_replace_ucv32_uv32(us32_t *str, ucv32_t from, uv32_t to);
UEXPORT size_t us32_replace_ucv32_us32(us32_t *str, ucv32_t from, const us32_t *to);

UEXPORT size_t us32_replace_uv32_uc32(us32_t *str, uv32_t from, uc32_t to);
UEXPORT size_t us32_replace_uv32_uz32(us32_t *str, uv32_t from, const uc32_t *to);
UEXPORT size_t us32_replace_uv32_uz32n(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len);
UEXPORT size_t us32_replace_uv32_ucv32(us32_t *str, uv32_t from, ucv32_t to);
UEXPORT size_t us32_replace_uv32_uv32(us32_t *str, uv32_t from, uv32_t to);
UEXPORT size_t us32_replace_uv32_us32(us32_t *str, uv32_t from, const us32_t *to);

UEXPORT size_t us32_replace_us32_uc32(us32_t *str, const us32_t *from, uc32_t to);
UEXPORT size_t us32_replace_us32_uz32(us32_t *str, const us32_t *from, const uc32_t *to);
UEXPORT size_t us32_replace_us32_uz32n(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len);
UEXPORT size_t us32_replace_us32_ucv32(us32_t *str, const us32_t *from, ucv32_t to);
UEXPORT size_t us32_replace_us32_uv32(us32_t *str, const us32_t *from, uv32_t to);
UEXPORT size_t us32_replace_us32_us32(us32_t *str, const us32_t *from, const us32_t *to);


UEXPORT size_t us16_replace_uc16_uc16(us16_t *str, uc16_t from, uc16_t to);
UEXPORT size_t us16_replace_uc16_uz16(us16_t *str, uc16_t from, const uc16_t *to);
UEXPORT size_t us16_replace_uc16_uz16n(us16_t *str, uc16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t us16_replace_uc16_ucv16(us16_t *str, uc16_t from, ucv16_t to);
UEXPORT size_t us16_replace_uc16_uv16(us16_t *str, uc16_t from, uv16_t to);
UEXPORT size_t us16_replace_uc16_us16(us16_t *str, uc16_t from, const us16_t *to);

UEXPORT size_t us16_replace_uz16_uc16(us16_t *str, const uc16_t *from, uc16_t to);
UEXPORT size_t us16_replace_uz16_uz16(us16_t *str, const uc16_t *from, const uc16_t *to);
UEXPORT size_t us16_replace_uz16_uz16n(us16_t *str, const uc16_t *from, const uc16_t *to, size_t to_len);
UEXPORT size_t us16_replace_uz16_ucv16(us16_t *str, const uc16_t *from, ucv16_t to);
UEXPORT size_t us16_replace_uz16_uv16(us16_t *str, const uc16_t *from, uv16_t to);
UEXPORT size_t us16_replace_uz16_us16(us16_t *str, const uc16_t *from, const us16_t *to);

UEXPORT size_t us16_replace_uz16n_uc16(us16_t *str, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t us16_replace_uz16n_uz16(us16_t *str, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t us16_replace_uz16n_uz16n(us16_t *str, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len);
UEXPORT size_t us16_replace_uz16n_ucv16(us16_t *str, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t us16_replace_uz16n_uv16(us16_t *str, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t us16_replace_uz16n_us16(us16_t *str, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t us16_replace_ucv16_uc16(us16_t *str, ucv16_t from, uc16_t to);
UEXPORT size_t us16_replace_ucv16_uz16(us16_t *str, ucv16_t from, const uc16_t *to);
UEXPORT size_t us16_replace_ucv16_uz16n(us16_t *str, ucv16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t us16_replace_ucv16_ucv16(us16_t *str, ucv16_t from, ucv16_t to);
UEXPORT size_t us16_replace_ucv16_uv16(us16_t *str, ucv16_t from, uv16_t to);
UEXPORT size_t us16_replace_ucv16_us16(us16_t *str, ucv16_t from, const us16_t *to);

UEXPORT size_t us16_replace_uv16_uc16(us16_t *str, uv16_t from, uc16_t to);
UEXPORT size_t us16_replace_uv16_uz16(us16_t *str, uv16_t from, const uc16_t *to);
UEXPORT size_t us16_replace_uv16_uz16n(us16_t *str, uv16_t from, const uc16_t *to, size_t to_len);
UEXPORT size_t us16_replace_uv16_ucv16(us16_t *str, uv16_t from, ucv16_t to);
UEXPORT size_t us16_replace_uv16_uv16(us16_t *str, uv16_t from, uv16_t to);
UEXPORT size_t us16_replace_uv16_us16(us16_t *str, uv16_t from, const us16_t *to);

UEXPORT size_t us16_replace_us16_uc16(us16_t *str, const us16_t *from, uc16_t to);
UEXPORT size_t us16_replace_us16_uz16(us16_t *str, const us16_t *from, const uc16_t *to);
UEXPORT size_t us16_replace_us16_uz16n(us16_t *str, const us16_t *from, const uc16_t *to, size_t to_len);
UEXPORT size_t us16_replace_us16_ucv16(us16_t *str, const us16_t *from, ucv16_t to);
UEXPORT size_t us16_replace_us16_uv16(us16_t *str, const us16_t *from, uv16_t to);
UEXPORT size_t us16_replace_us16_us16(us16_t *str, const us16_t *from, const us16_t *to);


UEXPORT size_t us8_replace_uc8_uc8(us8_t *str, uc8_t from, uc8_t to);
UEXPORT size_t us8_replace_uc8_uz8(us8_t *str, uc8_t from, const uc8_t *to);
UEXPORT size_t us8_replace_uc8_uz8n(us8_t *str, uc8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t us8_replace_uc8_ucv8(us8_t *str, uc8_t from, ucv8_t to);
UEXPORT size_t us8_replace_uc8_uv8(us8_t *str, uc8_t from, uv8_t to);
UEXPORT size_t us8_replace_uc8_us8(us8_t *str, uc8_t from, const us8_t *to);

UEXPORT size_t us8_replace_uz8_uc8(us8_t *str, const uc8_t *from, uc8_t to);
UEXPORT size_t us8_replace_uz8_uz8(us8_t *str, const uc8_t *from, const uc8_t *to);
UEXPORT size_t us8_replace_uz8_uz8n(us8_t *str, const uc8_t *from, const uc8_t *to, size_t to_len);
UEXPORT size_t us8_replace_uz8_ucv8(us8_t *str, const uc8_t *from, ucv8_t to);
UEXPORT size_t us8_replace_uz8_uv8(us8_t *str, const uc8_t *from, uv8_t to);
UEXPORT size_t us8_replace_uz8_us8(us8_t *str, const uc8_t *from, const us8_t *to);

UEXPORT size_t us8_replace_uz8n_uc8(us8_t *str, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t us8_replace_uz8n_uz8(us8_t *str, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t us8_replace_uz8n_uz8n(us8_t *str, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len);
UEXPORT size_t us8_replace_uz8n_ucv8(us8_t *str, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t us8_replace_uz8n_uv8(us8_t *str, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t us8_replace_uz8n_us8(us8_t *str, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t us8_replace_ucv8_uc8(us8_t *str, ucv8_t from, uc8_t to);
UEXPORT size_t us8_replace_ucv8_uz8(us8_t *str, ucv8_t from, const uc8_t *to);
UEXPORT size_t us8_replace_ucv8_uz8n(us8_t *str, ucv8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t us8_replace_ucv8_ucv8(us8_t *str, ucv8_t from, ucv8_t to);
UEXPORT size_t us8_replace_ucv8_uv8(us8_t *str, ucv8_t from, uv8_t to);
UEXPORT size_t us8_replace_ucv8_us8(us8_t *str, ucv8_t from, const us8_t *to);

UEXPORT size_t us8_replace_uv8_uc8(us8_t *str, uv8_t from, uc8_t to);
UEXPORT size_t us8_replace_uv8_uz8(us8_t *str, uv8_t from, const uc8_t *to);
UEXPORT size_t us8_replace_uv8_uz8n(us8_t *str, uv8_t from, const uc8_t *to, size_t to_len);
UEXPORT size_t us8_replace_uv8_ucv8(us8_t *str, uv8_t from, ucv8_t to);
UEXPORT size_t us8_replace_uv8_uv8(us8_t *str, uv8_t from, uv8_t to);
UEXPORT size_t us8_replace_uv8_us8(us8_t *str, uv8_t from, const us8_t *to);

UEXPORT size_t us8_replace_us8_uc8(us8_t *str, const us8_t *from, uc8_t to);
UEXPORT size_t us8_replace_us8_uz8(us8_t *str, const us8_t *from, const uc8_t *to);
UEXPORT size_t us8_replace_us8_uz8n(us8_t *str, const us8_t *from, const uc8_t *to, size_t to_len);
UEXPORT size_t us8_replace_us8_ucv8(us8_t *str, const us8_t *from, ucv8_t to);
UEXPORT size_t us8_replace_us8_uv8(us8_t *str, const us8_t *from, uv8_t to);
UEXPORT size_t us8_replace_us8_us8(us8_t *str, const us8_t *from, const us8_t *to);

// Replaced length

UEXPORT size_t us32_replaced_len_uc32_uc32(const us32_t *str, uc32_t from, uc32_t to);
UEXPORT size_t us32_replaced_len_uc32_uz32(const us32_t *str, uc32_t from, const uc32_t *to);
UEXPORT size_t us32_replaced_len_uc32_uz32n(const us32_t *str, uc32_t from, size_t to_len);
UEXPORT size_t us32_replaced_len_uc32_ucv32(const us32_t *str, uc32_t from, ucv32_t to);
UEXPORT size_t us32_replaced_len_uc32_uv32(const us32_t *str, uc32_t from, uv32_t to);
UEXPORT size_t us32_replaced_len_uc32_us32(const us32_t *str, uc32_t from, const us32_t *to);

UEXPORT size_t us32_replaced_len_uz32_uc32(const us32_t *str, const uc32_t *from, uc32_t to);
UEXPORT size_t us32_replaced_len_uz32_uz32(const us32_t *str, const uc32_t *from, const uc32_t *to);
UEXPORT size_t us32_replaced_len_uz32_uz32n(const us32_t *str, const uc32_t *from, size_t to_len);
UEXPORT size_t us32_replaced_len_uz32_ucv32(const us32_t *str, const uc32_t *from, ucv32_t to);
UEXPORT size_t us32_replaced_len_uz32_uv32(const us32_t *str, const uc32_t *from, uv32_t to);
UEXPORT size_t us32_replaced_len_uz32_us32(const us32_t *str, const uc32_t *from, const us32_t *to);

UEXPORT size_t us32_replaced_len_uz32n_uc32(const us32_t *str, const uc32_t *from, size_t from_len, uc32_t to);
UEXPORT size_t us32_replaced_len_uz32n_uz32(const us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to);
UEXPORT size_t us32_replaced_len_uz32n_uz32n(const us32_t *str, const uc32_t *from, size_t from_len, size_t to_len);
UEXPORT size_t us32_replaced_len_uz32n_ucv32(const us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to);
UEXPORT size_t us32_replaced_len_uz32n_uv32(const us32_t *str, const uc32_t *from, size_t from_len, uv32_t to);
UEXPORT size_t us32_replaced_len_uz32n_us32(const us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to);

UEXPORT size_t us32_replaced_len_ucv32_uc32(const us32_t *str, ucv32_t from, uc32_t to);
UEXPORT size_t us32_replaced_len_ucv32_uz32(const us32_t *str, ucv32_t from, const uc32_t *to);
UEXPORT size_t us32_replaced_len_ucv32_uz32n(const us32_t *str, ucv32_t from, size_t to_len);
UEXPORT size_t us32_replaced_len_ucv32_ucv32(const us32_t *str, ucv32_t from, ucv32_t to);
UEXPORT size_t us32_replaced_len_ucv32_uv32(const us32_t *str, ucv32_t from, uv32_t to);
UEXPORT size_t us32_replaced_len_ucv32_us32(const us32_t *str, ucv32_t from, const us32_t *to);

UEXPORT size_t us32_replaced_len_uv32_uc32(const us32_t *str, uv32_t from, uc32_t to);
UEXPORT size_t us32_replaced_len_uv32_uz32(const us32_t *str, uv32_t from, const uc32_t *to);
UEXPORT size_t us32_replaced_len_uv32_uz32n(const us32_t *str, uv32_t from, size_t to_len);
UEXPORT size_t us32_replaced_len_uv32_ucv32(const us32_t *str, uv32_t from, ucv32_t to);
UEXPORT size_t us32_replaced_len_uv32_uv32(const us32_t *str, uv32_t from, uv32_t to);
UEXPORT size_t us32_replaced_len_uv32_us32(const us32_t *str, uv32_t from, const us32_t *to);

UEXPORT size_t us32_replaced_len_us32_uc32(const us32_t *str, const us32_t *from, uc32_t to);
UEXPORT size_t us32_replaced_len_us32_uz32(const us32_t *str, const us32_t *from, const uc32_t *to);
UEXPORT size_t us32_replaced_len_us32_uz32n(const us32_t *str, const us32_t *from, size_t to_len);
UEXPORT size_t us32_replaced_len_us32_ucv32(const us32_t *str, const us32_t *from, ucv32_t to);
UEXPORT size_t us32_replaced_len_us32_uv32(const us32_t *str, const us32_t *from, uv32_t to);
UEXPORT size_t us32_replaced_len_us32_us32(const us32_t *str, const us32_t *from, const us32_t *to);


UEXPORT size_t us16_replaced_len_uc16_uc16(const us16_t *str, uc16_t from, uc16_t to);
UEXPORT size_t us16_replaced_len_uc16_uz16(const us16_t *str, uc16_t from, const uc16_t *to);
UEXPORT size_t us16_replaced_len_uc16_uz16n(const us16_t *str, uc16_t from, size_t to_len);
UEXPORT size_t us16_replaced_len_uc16_ucv16(const us16_t *str, uc16_t from, ucv16_t to);
UEXPORT size_t us16_replaced_len_uc16_uv16(const us16_t *str, uc16_t from, uv16_t to);
UEXPORT size_t us16_replaced_len_uc16_us16(const us16_t *str, uc16_t from, const us16_t *to);

UEXPORT size_t us16_replaced_len_uz16_uc16(const us16_t *str, const uc16_t *from, uc16_t to);
UEXPORT size_t us16_replaced_len_uz16_uz16(const us16_t *str, const uc16_t *from, const uc16_t *to);
UEXPORT size_t us16_replaced_len_uz16_uz16n(const us16_t *str, const uc16_t *from, size_t to_len);
UEXPORT size_t us16_replaced_len_uz16_ucv16(const us16_t *str, const uc16_t *from, ucv16_t to);
UEXPORT size_t us16_replaced_len_uz16_uv16(const us16_t *str, const uc16_t *from, uv16_t to);
UEXPORT size_t us16_replaced_len_uz16_us16(const us16_t *str, const uc16_t *from, const us16_t *to);

UEXPORT size_t us16_replaced_len_uz16n_uc16(const us16_t *str, const uc16_t *from, size_t from_len, uc16_t to);
UEXPORT size_t us16_replaced_len_uz16n_uz16(const us16_t *str, const uc16_t *from, size_t from_len, const uc16_t *to);
UEXPORT size_t us16_replaced_len_uz16n_uz16n(const us16_t *str, const uc16_t *from, size_t from_len, size_t to_len);
UEXPORT size_t us16_replaced_len_uz16n_ucv16(const us16_t *str, const uc16_t *from, size_t from_len, ucv16_t to);
UEXPORT size_t us16_replaced_len_uz16n_uv16(const us16_t *str, const uc16_t *from, size_t from_len, uv16_t to);
UEXPORT size_t us16_replaced_len_uz16n_us16(const us16_t *str, const uc16_t *from, size_t from_len, const us16_t *to);

UEXPORT size_t us16_replaced_len_ucv16_uc16(const us16_t *str, ucv16_t from, uc16_t to);
UEXPORT size_t us16_replaced_len_ucv16_uz16(const us16_t *str, ucv16_t from, const uc16_t *to);
UEXPORT size_t us16_replaced_len_ucv16_uz16n(const us16_t *str, ucv16_t from, size_t to_len);
UEXPORT size_t us16_replaced_len_ucv16_ucv16(const us16_t *str, ucv16_t from, ucv16_t to);
UEXPORT size_t us16_replaced_len_ucv16_uv16(const us16_t *str, ucv16_t from, uv16_t to);
UEXPORT size_t us16_replaced_len_ucv16_us16(const us16_t *str, ucv16_t from, const us16_t *to);

UEXPORT size_t us16_replaced_len_uv16_uc16(const us16_t *str, uv16_t from, uc16_t to);
UEXPORT size_t us16_replaced_len_uv16_uz16(const us16_t *str, uv16_t from, const uc16_t *to);
UEXPORT size_t us16_replaced_len_uv16_uz16n(const us16_t *str, uv16_t from, size_t to_len);
UEXPORT size_t us16_replaced_len_uv16_ucv16(const us16_t *str, uv16_t from, ucv16_t to);
UEXPORT size_t us16_replaced_len_uv16_uv16(const us16_t *str, uv16_t from, uv16_t to);
UEXPORT size_t us16_replaced_len_uv16_us16(const us16_t *str, uv16_t from, const us16_t *to);

UEXPORT size_t us16_replaced_len_us16_uc16(const us16_t *str, const us16_t *from, uc16_t to);
UEXPORT size_t us16_replaced_len_us16_uz16(const us16_t *str, const us16_t *from, const uc16_t *to);
UEXPORT size_t us16_replaced_len_us16_uz16n(const us16_t *str, const us16_t *from, size_t to_len);
UEXPORT size_t us16_replaced_len_us16_ucv16(const us16_t *str, const us16_t *from, ucv16_t to);
UEXPORT size_t us16_replaced_len_us16_uv16(const us16_t *str, const us16_t *from, uv16_t to);
UEXPORT size_t us16_replaced_len_us16_us16(const us16_t *str, const us16_t *from, const us16_t *to);


UEXPORT size_t us8_replaced_len_uc8_uc8(const us8_t *str, uc8_t from, uc8_t to);
UEXPORT size_t us8_replaced_len_uc8_uz8(const us8_t *str, uc8_t from, const uc8_t *to);
UEXPORT size_t us8_replaced_len_uc8_uz8n(const us8_t *str, uc8_t from, size_t to_len);
UEXPORT size_t us8_replaced_len_uc8_ucv8(const us8_t *str, uc8_t from, ucv8_t to);
UEXPORT size_t us8_replaced_len_uc8_uv8(const us8_t *str, uc8_t from, uv8_t to);
UEXPORT size_t us8_replaced_len_uc8_us8(const us8_t *str, uc8_t from, const us8_t *to);

UEXPORT size_t us8_replaced_len_uz8_uc8(const us8_t *str, const uc8_t *from, uc8_t to);
UEXPORT size_t us8_replaced_len_uz8_uz8(const us8_t *str, const uc8_t *from, const uc8_t *to);
UEXPORT size_t us8_replaced_len_uz8_uz8n(const us8_t *str, const uc8_t *from, size_t to_len);
UEXPORT size_t us8_replaced_len_uz8_ucv8(const us8_t *str, const uc8_t *from, ucv8_t to);
UEXPORT size_t us8_replaced_len_uz8_uv8(const us8_t *str, const uc8_t *from, uv8_t to);
UEXPORT size_t us8_replaced_len_uz8_us8(const us8_t *str, const uc8_t *from, const us8_t *to);

UEXPORT size_t us8_replaced_len_uz8n_uc8(const us8_t *str, const uc8_t *from, size_t from_len, uc8_t to);
UEXPORT size_t us8_replaced_len_uz8n_uz8(const us8_t *str, const uc8_t *from, size_t from_len, const uc8_t *to);
UEXPORT size_t us8_replaced_len_uz8n_uz8n(const us8_t *str, const uc8_t *from, size_t from_len, size_t to_len);
UEXPORT size_t us8_replaced_len_uz8n_ucv8(const us8_t *str, const uc8_t *from, size_t from_len, ucv8_t to);
UEXPORT size_t us8_replaced_len_uz8n_uv8(const us8_t *str, const uc8_t *from, size_t from_len, uv8_t to);
UEXPORT size_t us8_replaced_len_uz8n_us8(const us8_t *str, const uc8_t *from, size_t from_len, const us8_t *to);

UEXPORT size_t us8_replaced_len_ucv8_uc8(const us8_t *str, ucv8_t from, uc8_t to);
UEXPORT size_t us8_replaced_len_ucv8_uz8(const us8_t *str, ucv8_t from, const uc8_t *to);
UEXPORT size_t us8_replaced_len_ucv8_uz8n(const us8_t *str, ucv8_t from, size_t to_len);
UEXPORT size_t us8_replaced_len_ucv8_ucv8(const us8_t *str, ucv8_t from, ucv8_t to);
UEXPORT size_t us8_replaced_len_ucv8_uv8(const us8_t *str, ucv8_t from, uv8_t to);
UEXPORT size_t us8_replaced_len_ucv8_us8(const us8_t *str, ucv8_t from, const us8_t *to);

UEXPORT size_t us8_replaced_len_uv8_uc8(const us8_t *str, uv8_t from, uc8_t to);
UEXPORT size_t us8_replaced_len_uv8_uz8(const us8_t *str, uv8_t from, const uc8_t *to);
UEXPORT size_t us8_replaced_len_uv8_uz8n(const us8_t *str, uv8_t from, size_t to_len);
UEXPORT size_t us8_replaced_len_uv8_ucv8(const us8_t *str, uv8_t from, ucv8_t to);
UEXPORT size_t us8_replaced_len_uv8_uv8(const us8_t *str, uv8_t from, uv8_t to);
UEXPORT size_t us8_replaced_len_uv8_us8(const us8_t *str, uv8_t from, const us8_t *to);

UEXPORT size_t us8_replaced_len_us8_uc8(const us8_t *str, const us8_t *from, uc8_t to);
UEXPORT size_t us8_replaced_len_us8_uz8(const us8_t *str, const us8_t *from, const uc8_t *to);
UEXPORT size_t us8_replaced_len_us8_uz8n(const us8_t *str, const us8_t *from, size_t to_len);
UEXPORT size_t us8_replaced_len_us8_ucv8(const us8_t *str, const us8_t *from, ucv8_t to);
UEXPORT size_t us8_replaced_len_us8_uv8(const us8_t *str, const us8_t *from, uv8_t to);
UEXPORT size_t us8_replaced_len_us8_us8(const us8_t *str, const us8_t *from, const us8_t *to);

// Count

UEXPORT size_t us32_count_uc32(const us32_t *str, uc32_t target);
UEXPORT size_t us32_count_uz32(const us32_t *str, const uc32_t *target);
UEXPORT size_t us32_count_uz32n(const us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT size_t us32_count_ucv32(const us32_t *str, ucv32_t target);
UEXPORT size_t us32_count_uv32(const us32_t *str, uv32_t target);
UEXPORT size_t us32_count_us32(const us32_t *str, const us32_t *target);

UEXPORT size_t us16_count_uc16(const us16_t *str, uc16_t target);
UEXPORT size_t us16_count_uz16(const us16_t *str, const uc16_t *target);
UEXPORT size_t us16_count_uz16n(const us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT size_t us16_count_ucv16(const us16_t *str, ucv16_t target);
UEXPORT size_t us16_count_uv16(const us16_t *str, uv16_t target);
UEXPORT size_t us16_count_us16(const us16_t *str, const us16_t *target);

UEXPORT size_t us8_count_uc8(const us8_t *str, uc8_t target);
UEXPORT size_t us8_count_uz8(const us8_t *str, const uc8_t *target);
UEXPORT size_t us8_count_uz8n(const us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT size_t us8_count_ucv8(const us8_t *str, ucv8_t target);
UEXPORT size_t us8_count_uv8(const us8_t *str, uv8_t target);
UEXPORT size_t us8_count_us8(const us8_t *str, const us8_t *target);

// Bounds

UEXPORT bool us32_bounds(const us32_t *str, size_t index);
UEXPORT bool us32_ebounds(const us32_t *str, size_t index);
UEXPORT bool us32_bounds_range(const us32_t *str, size_t begin, size_t len);
UEXPORT bool us32_ebounds_range(const us32_t *str, size_t begin, size_t len);

UEXPORT bool us16_bounds(const us16_t *str, size_t index);
UEXPORT bool us16_ebounds(const us16_t *str, size_t index);
UEXPORT bool us16_bounds_range(const us16_t *str, size_t begin, size_t len);
UEXPORT bool us16_ebounds_range(const us16_t *str, size_t begin, size_t len);

UEXPORT bool us8_bounds(const us8_t *str, size_t index);
UEXPORT bool us8_ebounds(const us8_t *str, size_t index);
UEXPORT bool us8_bounds_range(const us8_t *str, size_t begin, size_t len);
UEXPORT bool us8_ebounds_range(const us8_t *str, size_t begin, size_t len);

// Starts with

UEXPORT bool us32_starts_with_uc32(const us32_t *str, uc32_t target);
UEXPORT bool us32_starts_with_uz32(const us32_t *str, const uc32_t *target);
UEXPORT bool us32_starts_with_uz32n(const us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT bool us32_starts_with_ucv32(const us32_t *str, ucv32_t target);
UEXPORT bool us32_starts_with_uv32(const us32_t *str, uv32_t target);
UEXPORT bool us32_starts_with_us32(const us32_t *str, const us32_t *target);

UEXPORT bool us16_starts_with_uc16(const us16_t *str, uc16_t target);
UEXPORT bool us16_starts_with_uz16(const us16_t *str, const uc16_t *target);
UEXPORT bool us16_starts_with_uz16n(const us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT bool us16_starts_with_ucv16(const us16_t *str, ucv16_t target);
UEXPORT bool us16_starts_with_uv16(const us16_t *str, uv16_t target);
UEXPORT bool us16_starts_with_us16(const us16_t *str, const us16_t *target);

UEXPORT bool us8_starts_with_uc8(const us8_t *str, uc8_t target);
UEXPORT bool us8_starts_with_uz8(const us8_t *str, const uc8_t *target);
UEXPORT bool us8_starts_with_uz8n(const us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT bool us8_starts_with_ucv8(const us8_t *str, ucv8_t target);
UEXPORT bool us8_starts_with_uv8(const us8_t *str, uv8_t target);
UEXPORT bool us8_starts_with_us8(const us8_t *str, const us8_t *target);

// Ends with

UEXPORT bool us32_ends_with_uc32(const us32_t *str, uc32_t target);
UEXPORT bool us32_ends_with_uz32(const us32_t *str, const uc32_t *target);
UEXPORT bool us32_ends_with_uz32n(const us32_t *str, const uc32_t *target, size_t target_len);
UEXPORT bool us32_ends_with_ucv32(const us32_t *str, ucv32_t target);
UEXPORT bool us32_ends_with_uv32(const us32_t *str, uv32_t target);
UEXPORT bool us32_ends_with_us32(const us32_t *str, const us32_t *target);

UEXPORT bool us16_ends_with_uc16(const us16_t *str, uc16_t target);
UEXPORT bool us16_ends_with_uz16(const us16_t *str, const uc16_t *target);
UEXPORT bool us16_ends_with_uz16n(const us16_t *str, const uc16_t *target, size_t target_len);
UEXPORT bool us16_ends_with_ucv16(const us16_t *str, ucv16_t target);
UEXPORT bool us16_ends_with_uv16(const us16_t *str, uv16_t target);
UEXPORT bool us16_ends_with_us16(const us16_t *str, const us16_t *target);

UEXPORT bool us8_ends_with_uc8(const us8_t *str, uc8_t target);
UEXPORT bool us8_ends_with_uz8(const us8_t *str, const uc8_t *target);
UEXPORT bool us8_ends_with_uz8n(const us8_t *str, const uc8_t *target, size_t target_len);
UEXPORT bool us8_ends_with_ucv8(const us8_t *str, ucv8_t target);
UEXPORT bool us8_ends_with_uv8(const us8_t *str, uv8_t target);
UEXPORT bool us8_ends_with_us8(const us8_t *str, const us8_t *target);

// Append

UEXPORT size_t us32_append_uc32(us32_t *str, uc32_t from);
UEXPORT size_t us32_append_uc32_e(us32_t *str, uc32_t from, bool *error);
UEXPORT size_t us32_append_uc32n(us32_t *str, uc32_t from, size_t n);
UEXPORT size_t us32_append_uc32n_e(us32_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us32_append_uz32(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_append_uz32_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_append_uz32n(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_append_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_append_ucv32(us32_t *str, ucv32_t from);
UEXPORT size_t us32_append_ucv32_e(us32_t *str, ucv32_t from, bool *error);
UEXPORT size_t us32_append_uv32(us32_t *str, uv32_t from);
UEXPORT size_t us32_append_uv32_e(us32_t *str, uv32_t from, bool *error);
UEXPORT size_t us32_append_us32(us32_t *str, const us32_t *from);
UEXPORT size_t us32_append_us32_e(us32_t *str, const us32_t *from, bool *error);

UEXPORT size_t us32_append_uc16(us32_t *str, uc16_t from);
UEXPORT size_t us32_append_uc16_e(us32_t *str, uc16_t from, bool *error);
UEXPORT size_t us32_append_uc16n(us32_t *str, uc16_t from, size_t n);
UEXPORT size_t us32_append_uc16n_e(us32_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us32_append_uz16(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_append_uz16_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_append_uz16n(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_append_uz16n_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_append_ucv16(us32_t *str, ucv16_t from);
UEXPORT size_t us32_append_ucv16_e(us32_t *str, ucv16_t from, bool *error);
UEXPORT size_t us32_append_uv16(us32_t *str, uv16_t from);
UEXPORT size_t us32_append_uv16_e(us32_t *str, uv16_t from, bool *error);
UEXPORT size_t us32_append_us16(us32_t *str, const us16_t *from);
UEXPORT size_t us32_append_us16_e(us32_t *str, const us16_t *from, bool *error);

UEXPORT size_t us32_append_uc8(us32_t *str, uc8_t from);
UEXPORT size_t us32_append_uc8_e(us32_t *str, uc8_t from, bool *error);
UEXPORT size_t us32_append_uc8n(us32_t *str, uc8_t from, size_t n);
UEXPORT size_t us32_append_uc8n_e(us32_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us32_append_uz8(us32_t *str, const uc8_t *from);
UEXPORT size_t us32_append_uz8_e(us32_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us32_append_uz8n(us32_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us32_append_uz8n_e(us32_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_append_ucv8(us32_t *str, ucv8_t from);
UEXPORT size_t us32_append_ucv8_e(us32_t *str, ucv8_t from, bool *error);
UEXPORT size_t us32_append_uv8(us32_t *str, uv8_t from);
UEXPORT size_t us32_append_uv8_e(us32_t *str, uv8_t from, bool *error);
UEXPORT size_t us32_append_us8(us32_t *str, const us8_t *from);
UEXPORT size_t us32_append_us8_e(us32_t *str, const us8_t *from, bool *error);

UEXPORT size_t us32_append_bytes(us32_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us32_append_bytes_e(us32_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us32_append_bytesn(us32_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us32_append_bytesn_e(us32_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us32_append_uz32le(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_append_uz32le_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_append_uz32len(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_append_uz32len_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_append_uz16le(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_append_uz16le_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_append_uz16len(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_append_uz16len_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_append_uz32be(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_append_uz32be_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_append_uz32ben(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_append_uz32ben_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_append_uz16be(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_append_uz16be_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_append_uz16ben(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_append_uz16ben_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us32_append_fmt_uz32(us32_t *str, const uc32_t *from, ...);
UEXPORT size_t us32_append_fmt_uz32_e(us32_t *str, const uc32_t *from, bool *error, ...);
UEXPORT size_t us32_append_fmt_uz32_v(us32_t *str, const uc32_t *from, va_list *args);
UEXPORT size_t us32_append_fmt_uz32_v_e(us32_t *str, const uc32_t *from, va_list *args, bool *error);
UEXPORT size_t us32_append_fmt_uz32n(us32_t *str, const uc32_t *from, size_t from_len, ...);
UEXPORT size_t us32_append_fmt_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us32_append_fmt_uz32n_v(us32_t *str, const uc32_t *from, size_t from_len, va_list *args);
UEXPORT size_t us32_append_fmt_uz32n_v_e(us32_t *str, const uc32_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us32_append_fmt_ucv32(us32_t *str, ucv32_t from, ...);
UEXPORT size_t us32_append_fmt_ucv32_e(us32_t *str, ucv32_t from, bool *error, ...);
UEXPORT size_t us32_append_fmt_ucv32_v(us32_t *str, ucv32_t from, va_list *args);
UEXPORT size_t us32_append_fmt_ucv32_v_e(us32_t *str, ucv32_t from, va_list *args, bool *error);
UEXPORT size_t us32_append_fmt_uv32(us32_t *str, uv32_t from, ...);
UEXPORT size_t us32_append_fmt_uv32_e(us32_t *str, uv32_t from, bool *error, ...);
UEXPORT size_t us32_append_fmt_uv32_v(us32_t *str, uv32_t from, va_list *args);
UEXPORT size_t us32_append_fmt_uv32_v_e(us32_t *str, uv32_t from, va_list *args, bool *error);
UEXPORT size_t us32_append_fmt_us32(us32_t *str, const us32_t *from, ...);
UEXPORT size_t us32_append_fmt_us32_e(us32_t *str, const us32_t *from, bool *error, ...);
UEXPORT size_t us32_append_fmt_us32_v(us32_t *str, const us32_t *from, va_list *args);
UEXPORT size_t us32_append_fmt_us32_v_e(us32_t *str, const us32_t *from, va_list *args, bool *error);

UEXPORT size_t us32_append_float(us32_t *str, double from);
UEXPORT size_t us32_append_float_e(us32_t *str, double from, bool *error);
UEXPORT size_t us32_append_float_fmt(us32_t *str, double from, const struct ufmt32_float_output *fmt);
UEXPORT size_t us32_append_float_fmt_e(us32_t *str, double from, const struct ufmt32_float_output *fmt, bool *error);

UEXPORT size_t us32_append_int(us32_t *str, intmax_t from);
UEXPORT size_t us32_append_int_e(us32_t *str, intmax_t from, bool *error);
UEXPORT size_t us32_append_int_fmt(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t us32_append_int_fmt_e(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt, bool *error);
UEXPORT size_t us32_append_uint(us32_t *str, uintmax_t from);
UEXPORT size_t us32_append_uint_e(us32_t *str, uintmax_t from, bool *error);
UEXPORT size_t us32_append_uint_fmt(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t us32_append_uint_fmt_e(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt, bool *error);

UEXPORT size_t us32_append_bool(us32_t *str, bool from);
UEXPORT size_t us32_append_bool_e(us32_t *str, bool from, bool *error);
UEXPORT size_t us32_append_case_bool(us32_t *str, ucase_t ca, bool from);
UEXPORT size_t us32_append_case_bool_e(us32_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us32_append_lower_bool(us32_t *str, bool from);
UEXPORT size_t us32_append_lower_bool_e(us32_t *str, bool from, bool *error);
UEXPORT size_t us32_append_upper_bool(us32_t *str, bool from);
UEXPORT size_t us32_append_upper_bool_e(us32_t *str, bool from, bool *error);


UEXPORT size_t us16_append_uc32(us16_t *str, uc32_t from);
UEXPORT size_t us16_append_uc32_e(us16_t *str, uc32_t from, bool *error);
UEXPORT size_t us16_append_uc32n(us16_t *str, uc32_t from, size_t n);
UEXPORT size_t us16_append_uc32n_e(us16_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us16_append_uz32(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_append_uz32_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_append_uz32n(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_append_uz32n_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_append_ucv32(us16_t *str, ucv32_t from);
UEXPORT size_t us16_append_ucv32_e(us16_t *str, ucv32_t from, bool *error);
UEXPORT size_t us16_append_uv32(us16_t *str, uv32_t from);
UEXPORT size_t us16_append_uv32_e(us16_t *str, uv32_t from, bool *error);
UEXPORT size_t us16_append_us32(us16_t *str, const us32_t *from);
UEXPORT size_t us16_append_us32_e(us16_t *str, const us32_t *from, bool *error);

UEXPORT size_t us16_append_uc16(us16_t *str, uc16_t from);
UEXPORT size_t us16_append_uc16_e(us16_t *str, uc16_t from, bool *error);
UEXPORT size_t us16_append_uc16n(us16_t *str, uc16_t from, size_t n);
UEXPORT size_t us16_append_uc16n_e(us16_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us16_append_uz16(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_append_uz16_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_append_uz16n(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_append_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_append_ucv16(us16_t *str, ucv16_t from);
UEXPORT size_t us16_append_ucv16_e(us16_t *str, ucv16_t from, bool *error);
UEXPORT size_t us16_append_uv16(us16_t *str, uv16_t from);
UEXPORT size_t us16_append_uv16_e(us16_t *str, uv16_t from, bool *error);
UEXPORT size_t us16_append_us16(us16_t *str, const us16_t *from);
UEXPORT size_t us16_append_us16_e(us16_t *str, const us16_t *from, bool *error);

UEXPORT size_t us16_append_uc8(us16_t *str, uc8_t from);
UEXPORT size_t us16_append_uc8_e(us16_t *str, uc8_t from, bool *error);
UEXPORT size_t us16_append_uc8n(us16_t *str, uc8_t from, size_t n);
UEXPORT size_t us16_append_uc8n_e(us16_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us16_append_uz8(us16_t *str, const uc8_t *from);
UEXPORT size_t us16_append_uz8_e(us16_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us16_append_uz8n(us16_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us16_append_uz8n_e(us16_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_append_ucv8(us16_t *str, ucv8_t from);
UEXPORT size_t us16_append_ucv8_e(us16_t *str, ucv8_t from, bool *error);
UEXPORT size_t us16_append_uv8(us16_t *str, uv8_t from);
UEXPORT size_t us16_append_uv8_e(us16_t *str, uv8_t from, bool *error);
UEXPORT size_t us16_append_us8(us16_t *str, const us8_t *from);
UEXPORT size_t us16_append_us8_e(us16_t *str, const us8_t *from, bool *error);

UEXPORT size_t us16_append_bytes(us16_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us16_append_bytes_e(us16_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us16_append_bytesn(us16_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us16_append_bytesn_e(us16_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us16_append_uz32le(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_append_uz32le_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_append_uz32len(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_append_uz32len_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_append_uz16le(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_append_uz16le_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_append_uz16len(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_append_uz16len_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_append_uz32be(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_append_uz32be_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_append_uz32ben(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_append_uz32ben_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_append_uz16be(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_append_uz16be_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_append_uz16ben(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_append_uz16ben_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us16_append_fmt_uz16(us16_t *str, const uc16_t *from, ...);
UEXPORT size_t us16_append_fmt_uz16_e(us16_t *str, const uc16_t *from, bool *error, ...);
UEXPORT size_t us16_append_fmt_uz16_v(us16_t *str, const uc16_t *from, va_list *args);
UEXPORT size_t us16_append_fmt_uz16_v_e(us16_t *str, const uc16_t *from, va_list *args, bool *error);
UEXPORT size_t us16_append_fmt_uz16n(us16_t *str, const uc16_t *from, size_t from_len, ...);
UEXPORT size_t us16_append_fmt_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us16_append_fmt_uz16n_v(us16_t *str, const uc16_t *from, size_t from_len, va_list *args);
UEXPORT size_t us16_append_fmt_uz16n_v_e(us16_t *str, const uc16_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us16_append_fmt_ucv16(us16_t *str, ucv16_t from, ...);
UEXPORT size_t us16_append_fmt_ucv16_e(us16_t *str, ucv16_t from, bool *error, ...);
UEXPORT size_t us16_append_fmt_ucv16_v(us16_t *str, ucv16_t from, va_list *args);
UEXPORT size_t us16_append_fmt_ucv16_v_e(us16_t *str, ucv16_t from, va_list *args, bool *error);
UEXPORT size_t us16_append_fmt_uv16(us16_t *str, uv16_t from, ...);
UEXPORT size_t us16_append_fmt_uv16_e(us16_t *str, uv16_t from, bool *error, ...);
UEXPORT size_t us16_append_fmt_uv16_v(us16_t *str, uv16_t from, va_list *args);
UEXPORT size_t us16_append_fmt_uv16_v_e(us16_t *str, uv16_t from, va_list *args, bool *error);
UEXPORT size_t us16_append_fmt_us16(us16_t *str, const us16_t *from, ...);
UEXPORT size_t us16_append_fmt_us16_e(us16_t *str, const us16_t *from, bool *error, ...);
UEXPORT size_t us16_append_fmt_us16_v(us16_t *str, const us16_t *from, va_list *args);
UEXPORT size_t us16_append_fmt_us16_v_e(us16_t *str, const us16_t *from, va_list *args, bool *error);

UEXPORT size_t us16_append_float(us16_t *str, double from);
UEXPORT size_t us16_append_float_e(us16_t *str, double from, bool *error);
UEXPORT size_t us16_append_float_fmt(us16_t *str, double from, const struct ufmt16_float_output *fmt);
UEXPORT size_t us16_append_float_fmt_e(us16_t *str, double from, const struct ufmt16_float_output *fmt, bool *error);

UEXPORT size_t us16_append_int(us16_t *str, intmax_t from);
UEXPORT size_t us16_append_int_e(us16_t *str, intmax_t from, bool *error);
UEXPORT size_t us16_append_int_fmt(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t us16_append_int_fmt_e(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt, bool *error);
UEXPORT size_t us16_append_uint(us16_t *str, uintmax_t from);
UEXPORT size_t us16_append_uint_e(us16_t *str, uintmax_t from, bool *error);
UEXPORT size_t us16_append_uint_fmt(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t us16_append_uint_fmt_e(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt, bool *error);

UEXPORT size_t us16_append_bool(us16_t *str, bool from);
UEXPORT size_t us16_append_bool_e(us16_t *str, bool from, bool *error);
UEXPORT size_t us16_append_case_bool(us16_t *str, ucase_t ca, bool from);
UEXPORT size_t us16_append_case_bool_e(us16_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us16_append_lower_bool(us16_t *str, bool from);
UEXPORT size_t us16_append_lower_bool_e(us16_t *str, bool from, bool *error);
UEXPORT size_t us16_append_upper_bool(us16_t *str, bool from);
UEXPORT size_t us16_append_upper_bool_e(us16_t *str, bool from, bool *error);


UEXPORT size_t us8_append_uc32(us8_t *str, uc32_t from);
UEXPORT size_t us8_append_uc32_e(us8_t *str, uc32_t from, bool *error);
UEXPORT size_t us8_append_uc32n(us8_t *str, uc32_t from, size_t n);
UEXPORT size_t us8_append_uc32n_e(us8_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us8_append_uz32(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_append_uz32_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_append_uz32n(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_append_uz32n_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_append_ucv32(us8_t *str, ucv32_t from);
UEXPORT size_t us8_append_ucv32_e(us8_t *str, ucv32_t from, bool *error);
UEXPORT size_t us8_append_uv32(us8_t *str, uv32_t from);
UEXPORT size_t us8_append_uv32_e(us8_t *str, uv32_t from, bool *error);
UEXPORT size_t us8_append_us32(us8_t *str, const us32_t *from);
UEXPORT size_t us8_append_us32_e(us8_t *str, const us32_t *from, bool *error);
UEXPORT size_t us8_append_us32_range(us8_t *str, const us32_t *from, size_t begin, size_t len);
UEXPORT size_t us8_append_us32_range_e(us8_t *str, const us32_t *from, size_t begin, size_t len, bool *error);

UEXPORT size_t us8_append_uc16(us8_t *str, uc16_t from);
UEXPORT size_t us8_append_uc16_e(us8_t *str, uc16_t from, bool *error);
UEXPORT size_t us8_append_uc16n(us8_t *str, uc16_t from, size_t n);
UEXPORT size_t us8_append_uc16n_e(us8_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us8_append_uz16(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_append_uz16_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_append_uz16n(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_append_uz16n_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_append_ucv16(us8_t *str, ucv16_t from);
UEXPORT size_t us8_append_ucv16_e(us8_t *str, ucv16_t from, bool *error);
UEXPORT size_t us8_append_uv16(us8_t *str, uv16_t from);
UEXPORT size_t us8_append_uv16_e(us8_t *str, uv16_t from, bool *error);
UEXPORT size_t us8_append_us16(us8_t *str, const us16_t *from);
UEXPORT size_t us8_append_us16_e(us8_t *str, const us16_t *from, bool *error);

UEXPORT size_t us8_append_uc8(us8_t *str, uc8_t from);
UEXPORT size_t us8_append_uc8_e(us8_t *str, uc8_t from, bool *error);
UEXPORT size_t us8_append_uc8n(us8_t *str, uc8_t from, size_t n);
UEXPORT size_t us8_append_uc8n_e(us8_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us8_append_uz8(us8_t *str, const uc8_t *from);
UEXPORT size_t us8_append_uz8_e(us8_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us8_append_uz8n(us8_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us8_append_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_append_ucv8(us8_t *str, ucv8_t from);
UEXPORT size_t us8_append_ucv8_e(us8_t *str, ucv8_t from, bool *error);
UEXPORT size_t us8_append_uv8(us8_t *str, uv8_t from);
UEXPORT size_t us8_append_uv8_e(us8_t *str, uv8_t from, bool *error);
UEXPORT size_t us8_append_us8(us8_t *str, const us8_t *from);
UEXPORT size_t us8_append_us8_e(us8_t *str, const us8_t *from, bool *error);

UEXPORT size_t us8_append_bytes(us8_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us8_append_bytes_e(us8_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us8_append_bytesn(us8_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us8_append_bytesn_e(us8_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us8_append_uz32le(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_append_uz32le_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_append_uz32len(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_append_uz32len_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_append_uz16le(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_append_uz16le_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_append_uz16len(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_append_uz16len_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_append_uz32be(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_append_uz32be_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_append_uz32ben(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_append_uz32ben_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_append_uz16be(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_append_uz16be_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_append_uz16ben(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_append_uz16ben_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us8_append_fmt_uz8(us8_t *str, const uc8_t *from, ...);
UEXPORT size_t us8_append_fmt_uz8_e(us8_t *str, const uc8_t *from, bool *error, ...);
UEXPORT size_t us8_append_fmt_uz8_v(us8_t *str, const uc8_t *from, va_list *args);
UEXPORT size_t us8_append_fmt_uz8_v_e(us8_t *str, const uc8_t *from, va_list *args, bool *error);
UEXPORT size_t us8_append_fmt_uz8n(us8_t *str, const uc8_t *from, size_t from_len, ...);
UEXPORT size_t us8_append_fmt_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us8_append_fmt_uz8n_v(us8_t *str, const uc8_t *from, size_t from_len, va_list *args);
UEXPORT size_t us8_append_fmt_uz8n_v_e(us8_t *str, const uc8_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us8_append_fmt_ucv8(us8_t *str, ucv8_t from, ...);
UEXPORT size_t us8_append_fmt_ucv8_e(us8_t *str, ucv8_t from, bool *error, ...);
UEXPORT size_t us8_append_fmt_ucv8_v(us8_t *str, ucv8_t from, va_list *args);
UEXPORT size_t us8_append_fmt_ucv8_v_e(us8_t *str, ucv8_t from, va_list *args, bool *error);
UEXPORT size_t us8_append_fmt_uv8(us8_t *str, uv8_t from, ...);
UEXPORT size_t us8_append_fmt_uv8_e(us8_t *str, uv8_t from, bool *error, ...);
UEXPORT size_t us8_append_fmt_uv8_v(us8_t *str, uv8_t from, va_list *args);
UEXPORT size_t us8_append_fmt_uv8_v_e(us8_t *str, uv8_t from, va_list *args, bool *error);
UEXPORT size_t us8_append_fmt_us8(us8_t *str, const us8_t *from, ...);
UEXPORT size_t us8_append_fmt_us8_e(us8_t *str, const us8_t *from, bool *error, ...);
UEXPORT size_t us8_append_fmt_us8_v(us8_t *str, const us8_t *from, va_list *args);
UEXPORT size_t us8_append_fmt_us8_v_e(us8_t *str, const us8_t *from, va_list *args, bool *error);

UEXPORT size_t us8_append_float(us8_t *str, double from);
UEXPORT size_t us8_append_float_e(us8_t *str, double from, bool *error);
UEXPORT size_t us8_append_float_fmt(us8_t *str, double from, const struct ufmt8_float_output *fmt);
UEXPORT size_t us8_append_float_fmt_e(us8_t *str, double from, const struct ufmt8_float_output *fmt, bool *error);

UEXPORT size_t us8_append_int(us8_t *str, intmax_t from);
UEXPORT size_t us8_append_int_e(us8_t *str, intmax_t from, bool *error);
UEXPORT size_t us8_append_int_fmt(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t us8_append_int_fmt_e(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt, bool *error);
UEXPORT size_t us8_append_uint(us8_t *str, uintmax_t from);
UEXPORT size_t us8_append_uint_e(us8_t *str, uintmax_t from, bool *error);
UEXPORT size_t us8_append_uint_fmt(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t us8_append_uint_fmt_e(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt, bool *error);

UEXPORT size_t us8_append_bool(us8_t *str, bool from);
UEXPORT size_t us8_append_bool_e(us8_t *str, bool from, bool *error);
UEXPORT size_t us8_append_case_bool(us8_t *str, ucase_t ca, bool from);
UEXPORT size_t us8_append_case_bool_e(us8_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us8_append_lower_bool(us8_t *str, bool from);
UEXPORT size_t us8_append_lower_bool_e(us8_t *str, bool from, bool *error);
UEXPORT size_t us8_append_upper_bool(us8_t *str, bool from);
UEXPORT size_t us8_append_upper_bool_e(us8_t *str, bool from, bool *error);

// Insert

UEXPORT size_t us32_insert_uc32(us32_t *str, uc32_t from, size_t at);
UEXPORT size_t us32_insert_uc32_e(us32_t *str, uc32_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uc32n(us32_t *str, uc32_t from, size_t n, size_t at);
UEXPORT size_t us32_insert_uc32n_e(us32_t *str, uc32_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us32_insert_uz32(us32_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us32_insert_uz32_e(us32_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz32n(us32_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us32_insert_ucv32(us32_t *str, ucv32_t from, size_t at);
UEXPORT size_t us32_insert_ucv32_e(us32_t *str, ucv32_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uv32(us32_t *str, uv32_t from, size_t at);
UEXPORT size_t us32_insert_uv32_e(us32_t *str, uv32_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_us32(us32_t *str, const us32_t *from, size_t at);
UEXPORT size_t us32_insert_us32_e(us32_t *str, const us32_t *from, size_t at, bool *error);

UEXPORT size_t us32_insert_uc16(us32_t *str, uc16_t from, size_t at);
UEXPORT size_t us32_insert_uc16_e(us32_t *str, uc16_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uc16n(us32_t *str, uc16_t from, size_t n, size_t at);
UEXPORT size_t us32_insert_uc16n_e(us32_t *str, uc16_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us32_insert_uz16(us32_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us32_insert_uz16_e(us32_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz16n(us32_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz16n_e(us32_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us32_insert_ucv16(us32_t *str, ucv16_t from, size_t at);
UEXPORT size_t us32_insert_ucv16_e(us32_t *str, ucv16_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uv16(us32_t *str, uv16_t from, size_t at);
UEXPORT size_t us32_insert_uv16_e(us32_t *str, uv16_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_us16(us32_t *str, const us16_t *from, size_t at);
UEXPORT size_t us32_insert_us16_e(us32_t *str, const us16_t *from, size_t at, bool *error);

UEXPORT size_t us32_insert_uc8(us32_t *str, uc8_t from, size_t at);
UEXPORT size_t us32_insert_uc8_e(us32_t *str, uc8_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uc8n(us32_t *str, uc8_t from, size_t n, size_t at);
UEXPORT size_t us32_insert_uc8n_e(us32_t *str, uc8_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us32_insert_uz8(us32_t *str, const uc8_t *from, size_t at);
UEXPORT size_t us32_insert_uz8_e(us32_t *str, const uc8_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz8n(us32_t *str, const uc8_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz8n_e(us32_t *str, const uc8_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us32_insert_ucv8(us32_t *str, ucv8_t from, size_t at);
UEXPORT size_t us32_insert_ucv8_e(us32_t *str, ucv8_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uv8(us32_t *str, uv8_t from, size_t at);
UEXPORT size_t us32_insert_uv8_e(us32_t *str, uv8_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_us8(us32_t *str, const us8_t *from, size_t at);
UEXPORT size_t us32_insert_us8_e(us32_t *str, const us8_t *from, size_t at, bool *error);

UEXPORT size_t us32_insert_bytes(us32_t *str, const void *from, uencoding_t encoding, size_t at);
UEXPORT size_t us32_insert_bytes_e(us32_t *str, const void *from, uencoding_t encoding, size_t at, bool *error);
UEXPORT size_t us32_insert_bytesn(us32_t *str, const void *from, size_t from_size, uencoding_t encoding, size_t at);
UEXPORT size_t us32_insert_bytesn_e(us32_t *str, const void *from, size_t from_size, uencoding_t encoding, size_t at, bool *error);
UEXPORT size_t us32_insert_uz32le(us32_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us32_insert_uz32le_e(us32_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz32len(us32_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz32len_e(us32_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us32_insert_uz16le(us32_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us32_insert_uz16le_e(us32_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz16len(us32_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz16len_e(us32_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us32_insert_uz32be(us32_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us32_insert_uz32be_e(us32_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz32ben(us32_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz32ben_e(us32_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us32_insert_uz16be(us32_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us32_insert_uz16be_e(us32_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us32_insert_uz16ben(us32_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us32_insert_uz16ben_e(us32_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);

UEXPORT size_t us32_insert_fmt_uz32(us32_t *str, const uc32_t *from, size_t at, ...);
UEXPORT size_t us32_insert_fmt_uz32_e(us32_t *str, const uc32_t *from, size_t at, bool *error, ...);
UEXPORT size_t us32_insert_fmt_uz32_v(us32_t *str, const uc32_t *from, va_list *args, size_t at);
UEXPORT size_t us32_insert_fmt_uz32_v_e(us32_t *str, const uc32_t *from, va_list *args, size_t at, bool *error);
UEXPORT size_t us32_insert_fmt_uz32n(us32_t *str, const uc32_t *from, size_t from_len, size_t at, ...);
UEXPORT size_t us32_insert_fmt_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error, ...);
UEXPORT size_t us32_insert_fmt_uz32n_v(us32_t *str, const uc32_t *from, size_t from_len, va_list *args, size_t at);
UEXPORT size_t us32_insert_fmt_uz32n_v_e(us32_t *str, const uc32_t *from, size_t from_len, va_list *args, size_t at, bool *error);
UEXPORT size_t us32_insert_fmt_ucv32(us32_t *str, ucv32_t from, size_t at, ...);
UEXPORT size_t us32_insert_fmt_ucv32_e(us32_t *str, ucv32_t from, size_t at, bool *error, ...);
UEXPORT size_t us32_insert_fmt_ucv32_v(us32_t *str, ucv32_t from, va_list *args, size_t at);
UEXPORT size_t us32_insert_fmt_ucv32_v_e(us32_t *str, ucv32_t from, va_list *args, size_t at, bool *error);
UEXPORT size_t us32_insert_fmt_uv32(us32_t *str, uv32_t from, size_t at, ...);
UEXPORT size_t us32_insert_fmt_uv32_e(us32_t *str, uv32_t from, size_t at, bool *error, ...);
UEXPORT size_t us32_insert_fmt_uv32_v(us32_t *str, uv32_t from, va_list *args, size_t at);
UEXPORT size_t us32_insert_fmt_uv32_v_e(us32_t *str, uv32_t from, va_list *args, size_t at, bool *error);
UEXPORT size_t us32_insert_fmt_us32(us32_t *str, const us32_t *from, size_t at, ...);
UEXPORT size_t us32_insert_fmt_us32_e(us32_t *str, const us32_t *from, size_t at, bool *error, ...);
UEXPORT size_t us32_insert_fmt_us32_v(us32_t *str, const us32_t *from, va_list *args, size_t at);
UEXPORT size_t us32_insert_fmt_us32_v_e(us32_t *str, const us32_t *from, va_list *args, size_t at, bool *error);

UEXPORT size_t us32_insert_float(us32_t *str, double from, size_t at);
UEXPORT size_t us32_insert_float_e(us32_t *str, double from, size_t at, bool *error);
UEXPORT size_t us32_insert_float_fmt(us32_t *str, double from, const struct ufmt32_float_output *fmt, size_t at);
UEXPORT size_t us32_insert_float_fmt_e(us32_t *str, double from, const struct ufmt32_float_output *fmt, size_t at, bool *error);

UEXPORT size_t us32_insert_int(us32_t *str, intmax_t from, size_t at);
UEXPORT size_t us32_insert_int_e(us32_t *str, intmax_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_int_fmt(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt, size_t at);
UEXPORT size_t us32_insert_int_fmt_e(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt, size_t at, bool *error);
UEXPORT size_t us32_insert_uint(us32_t *str, uintmax_t from, size_t at);
UEXPORT size_t us32_insert_uint_e(us32_t *str, uintmax_t from, size_t at, bool *error);
UEXPORT size_t us32_insert_uint_fmt(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt, size_t at);
UEXPORT size_t us32_insert_uint_fmt_e(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt, size_t at, bool *error);

UEXPORT size_t us32_insert_bool(us32_t *str, bool from, size_t at);
UEXPORT size_t us32_insert_bool_e(us32_t *str, bool from, size_t at, bool *error);
UEXPORT size_t us32_insert_case_bool(us32_t *str, ucase_t ca, bool from, size_t at);
UEXPORT size_t us32_insert_case_bool_e(us32_t *str, ucase_t ca, bool from, size_t at, bool *error);
UEXPORT size_t us32_insert_lower_bool(us32_t *str, bool from, size_t at);
UEXPORT size_t us32_insert_lower_bool_e(us32_t *str, bool from, size_t at, bool *error);
UEXPORT size_t us32_insert_upper_bool(us32_t *str, bool from, size_t at);
UEXPORT size_t us32_insert_upper_bool_e(us32_t *str, bool from, size_t at, bool *error);


UEXPORT size_t us16_insert_uc32(us16_t *str, uc32_t from, size_t at);
UEXPORT size_t us16_insert_uc32_e(us16_t *str, uc32_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uc32n(us16_t *str, uc32_t from, size_t n, size_t at);
UEXPORT size_t us16_insert_uc32n_e(us16_t *str, uc32_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us16_insert_uz32(us16_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us16_insert_uz32_e(us16_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz32n(us16_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz32n_e(us16_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us16_insert_ucv32(us16_t *str, ucv32_t from, size_t at);
UEXPORT size_t us16_insert_ucv32_e(us16_t *str, ucv32_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uv32(us16_t *str, uv32_t from, size_t at);
UEXPORT size_t us16_insert_uv32_e(us16_t *str, uv32_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_us32(us16_t *str, const us32_t *from, size_t at);
UEXPORT size_t us16_insert_us32_e(us16_t *str, const us32_t *from, size_t at, bool *error);

UEXPORT size_t us16_insert_uc16(us16_t *str, uc16_t from, size_t at);
UEXPORT size_t us16_insert_uc16_e(us16_t *str, uc16_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uc16n(us16_t *str, uc16_t from, size_t n, size_t at);
UEXPORT size_t us16_insert_uc16n_e(us16_t *str, uc16_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us16_insert_uz16(us16_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us16_insert_uz16_e(us16_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz16n(us16_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us16_insert_ucv16(us16_t *str, ucv16_t from, size_t at);
UEXPORT size_t us16_insert_ucv16_e(us16_t *str, ucv16_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uv16(us16_t *str, uv16_t from, size_t at);
UEXPORT size_t us16_insert_uv16_e(us16_t *str, uv16_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_us16(us16_t *str, const us16_t *from, size_t at);
UEXPORT size_t us16_insert_us16_e(us16_t *str, const us16_t *from, size_t at, bool *error);

UEXPORT size_t us16_insert_uc8(us16_t *str, uc8_t from, size_t at);
UEXPORT size_t us16_insert_uc8_e(us16_t *str, uc8_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uc8n(us16_t *str, uc8_t from, size_t n, size_t at);
UEXPORT size_t us16_insert_uc8n_e(us16_t *str, uc8_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us16_insert_uz8(us16_t *str, const uc8_t *from, size_t at);
UEXPORT size_t us16_insert_uz8_e(us16_t *str, const uc8_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz8n(us16_t *str, const uc8_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz8n_e(us16_t *str, const uc8_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us16_insert_ucv8(us16_t *str, ucv8_t from, size_t at);
UEXPORT size_t us16_insert_ucv8_e(us16_t *str, ucv8_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uv8(us16_t *str, uv8_t from, size_t at);
UEXPORT size_t us16_insert_uv8_e(us16_t *str, uv8_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_us8(us16_t *str, const us8_t *from, size_t at);
UEXPORT size_t us16_insert_us8_e(us16_t *str, const us8_t *from, size_t at, bool *error);

UEXPORT size_t us16_insert_bytes(us16_t *str, const void *from, uencoding_t encoding, size_t at);
UEXPORT size_t us16_insert_bytes_e(us16_t *str, const void *from, uencoding_t encoding, size_t at, bool *error);
UEXPORT size_t us16_insert_bytesn(us16_t *str, const void *from, size_t from_size, uencoding_t encoding, size_t at);
UEXPORT size_t us16_insert_bytesn_e(us16_t *str, const void *from, size_t from_size, uencoding_t encoding, size_t at, bool *error);
UEXPORT size_t us16_insert_uz32le(us16_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us16_insert_uz32le_e(us16_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz32len(us16_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz32len_e(us16_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us16_insert_uz16le(us16_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us16_insert_uz16le_e(us16_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz16len(us16_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz16len_e(us16_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us16_insert_uz32be(us16_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us16_insert_uz32be_e(us16_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz32ben(us16_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz32ben_e(us16_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us16_insert_uz16be(us16_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us16_insert_uz16be_e(us16_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us16_insert_uz16ben(us16_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us16_insert_uz16ben_e(us16_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);

UEXPORT size_t us16_insert_fmt_uz16(us16_t *str, const uc16_t *from, size_t at, ...);
UEXPORT size_t us16_insert_fmt_uz16_e(us16_t *str, const uc16_t *from, size_t at, bool *error, ...);
UEXPORT size_t us16_insert_fmt_uz16_v(us16_t *str, const uc16_t *from, va_list *args, size_t at);
UEXPORT size_t us16_insert_fmt_uz16_v_e(us16_t *str, const uc16_t *from, va_list *args, size_t at, bool *error);
UEXPORT size_t us16_insert_fmt_uz16n(us16_t *str, const uc16_t *from, size_t from_len, size_t at, ...);
UEXPORT size_t us16_insert_fmt_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error, ...);
UEXPORT size_t us16_insert_fmt_uz16n_v(us16_t *str, const uc16_t *from, size_t from_len, va_list *args, size_t at);
UEXPORT size_t us16_insert_fmt_uz16n_v_e(us16_t *str, const uc16_t *from, size_t from_len, va_list *args, size_t at, bool *error);
UEXPORT size_t us16_insert_fmt_ucv16(us16_t *str, ucv16_t from, size_t at, ...);
UEXPORT size_t us16_insert_fmt_ucv16_e(us16_t *str, ucv16_t from, size_t at, bool *error, ...);
UEXPORT size_t us16_insert_fmt_ucv16_v(us16_t *str, ucv16_t from, va_list *args, size_t at);
UEXPORT size_t us16_insert_fmt_ucv16_v_e(us16_t *str, ucv16_t from, va_list *args, size_t at, bool *error);
UEXPORT size_t us16_insert_fmt_uv16(us16_t *str, uv16_t from, size_t at, ...);
UEXPORT size_t us16_insert_fmt_uv16_e(us16_t *str, uv16_t from, size_t at, bool *error, ...);
UEXPORT size_t us16_insert_fmt_uv16_v(us16_t *str, uv16_t from, va_list *args, size_t at);
UEXPORT size_t us16_insert_fmt_uv16_v_e(us16_t *str, uv16_t from, va_list *args, size_t at, bool *error);
UEXPORT size_t us16_insert_fmt_us16(us16_t *str, const us16_t *from, size_t at, ...);
UEXPORT size_t us16_insert_fmt_us16_e(us16_t *str, const us16_t *from, size_t at, bool *error, ...);
UEXPORT size_t us16_insert_fmt_us16_v(us16_t *str, const us16_t *from, va_list *args, size_t at);
UEXPORT size_t us16_insert_fmt_us16_v_e(us16_t *str, const us16_t *from, va_list *args, size_t at, bool *error);

UEXPORT size_t us16_insert_float(us16_t *str, double from, size_t at);
UEXPORT size_t us16_insert_float_e(us16_t *str, double from, size_t at, bool *error);
UEXPORT size_t us16_insert_float_fmt(us16_t *str, double from, const struct ufmt16_float_output *fmt, size_t at);
UEXPORT size_t us16_insert_float_fmt_e(us16_t *str, double from, const struct ufmt16_float_output *fmt, size_t at, bool *error);

UEXPORT size_t us16_insert_int(us16_t *str, intmax_t from, size_t at);
UEXPORT size_t us16_insert_int_e(us16_t *str, intmax_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_int_fmt(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt, size_t at);
UEXPORT size_t us16_insert_int_fmt_e(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt, size_t at, bool *error);
UEXPORT size_t us16_insert_uint(us16_t *str, uintmax_t from, size_t at);
UEXPORT size_t us16_insert_uint_e(us16_t *str, uintmax_t from, size_t at, bool *error);
UEXPORT size_t us16_insert_uint_fmt(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt, size_t at);
UEXPORT size_t us16_insert_uint_fmt_e(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt, size_t at, bool *error);

UEXPORT size_t us16_insert_bool(us16_t *str, bool from, size_t at);
UEXPORT size_t us16_insert_bool_e(us16_t *str, bool from, size_t at, bool *error);
UEXPORT size_t us16_insert_case_bool(us16_t *str, ucase_t ca, bool from, size_t at);
UEXPORT size_t us16_insert_case_bool_e(us16_t *str, ucase_t ca, bool from, size_t at, bool *error);
UEXPORT size_t us16_insert_lower_bool(us16_t *str, bool from, size_t at);
UEXPORT size_t us16_insert_lower_bool_e(us16_t *str, bool from, size_t at, bool *error);
UEXPORT size_t us16_insert_upper_bool(us16_t *str, bool from, size_t at);
UEXPORT size_t us16_insert_upper_bool_e(us16_t *str, bool from, size_t at, bool *error);


UEXPORT size_t us8_insert_uc32(us8_t *str, uc32_t from, size_t at);
UEXPORT size_t us8_insert_uc32_e(us8_t *str, uc32_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uc32n(us8_t *str, uc32_t from, size_t n, size_t at);
UEXPORT size_t us8_insert_uc32n_e(us8_t *str, uc32_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us8_insert_uz32(us8_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us8_insert_uz32_e(us8_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz32n(us8_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz32n_e(us8_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us8_insert_ucv32(us8_t *str, ucv32_t from, size_t at);
UEXPORT size_t us8_insert_ucv32_e(us8_t *str, ucv32_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uv32(us8_t *str, uv32_t from, size_t at);
UEXPORT size_t us8_insert_uv32_e(us8_t *str, uv32_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_us32(us8_t *str, const us32_t *from, size_t at);
UEXPORT size_t us8_insert_us32_e(us8_t *str, const us32_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_us32_range(us8_t *str, const us32_t *from, size_t begin, size_t len, size_t at);
UEXPORT size_t us8_insert_us32_range_e(us8_t *str, const us32_t *from, size_t begin, size_t len, size_t at, bool *error);

UEXPORT size_t us8_insert_uc16(us8_t *str, uc16_t from, size_t at);
UEXPORT size_t us8_insert_uc16_e(us8_t *str, uc16_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uc16n(us8_t *str, uc16_t from, size_t n, size_t at);
UEXPORT size_t us8_insert_uc16n_e(us8_t *str, uc16_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us8_insert_uz16(us8_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us8_insert_uz16_e(us8_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz16n(us8_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz16n_e(us8_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us8_insert_ucv16(us8_t *str, ucv16_t from, size_t at);
UEXPORT size_t us8_insert_ucv16_e(us8_t *str, ucv16_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uv16(us8_t *str, uv16_t from, size_t at);
UEXPORT size_t us8_insert_uv16_e(us8_t *str, uv16_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_us16(us8_t *str, const us16_t *from, size_t at);
UEXPORT size_t us8_insert_us16_e(us8_t *str, const us16_t *from, size_t at, bool *error);

UEXPORT size_t us8_insert_uc8(us8_t *str, uc8_t from, size_t at);
UEXPORT size_t us8_insert_uc8_e(us8_t *str, uc8_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uc8n(us8_t *str, uc8_t from, size_t n, size_t at);
UEXPORT size_t us8_insert_uc8n_e(us8_t *str, uc8_t from, size_t n, size_t at, bool *error);
UEXPORT size_t us8_insert_uz8(us8_t *str, const uc8_t *from, size_t at);
UEXPORT size_t us8_insert_uz8_e(us8_t *str, const uc8_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz8n(us8_t *str, const uc8_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us8_insert_ucv8(us8_t *str, ucv8_t from, size_t at);
UEXPORT size_t us8_insert_ucv8_e(us8_t *str, ucv8_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uv8(us8_t *str, uv8_t from, size_t at);
UEXPORT size_t us8_insert_uv8_e(us8_t *str, uv8_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_us8(us8_t *str, const us8_t *from, size_t at);
UEXPORT size_t us8_insert_us8_e(us8_t *str, const us8_t *from, size_t at, bool *error);

UEXPORT size_t us8_insert_bytes(us8_t *str, const void *from, uencoding_t encoding, size_t at);
UEXPORT size_t us8_insert_bytes_e(us8_t *str, const void *from, uencoding_t encoding, size_t at, bool *error);
UEXPORT size_t us8_insert_bytesn(us8_t *str, const void *from, size_t from_size, uencoding_t encoding, size_t at);
UEXPORT size_t us8_insert_bytesn_e(us8_t *str, const void *from, size_t from_size, uencoding_t encoding, size_t at, bool *error);
UEXPORT size_t us8_insert_uz32le(us8_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us8_insert_uz32le_e(us8_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz32len(us8_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz32len_e(us8_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us8_insert_uz16le(us8_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us8_insert_uz16le_e(us8_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz16len(us8_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz16len_e(us8_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us8_insert_uz32be(us8_t *str, const uc32_t *from, size_t at);
UEXPORT size_t us8_insert_uz32be_e(us8_t *str, const uc32_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz32ben(us8_t *str, const uc32_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz32ben_e(us8_t *str, const uc32_t *from, size_t from_len, size_t at, bool *error);
UEXPORT size_t us8_insert_uz16be(us8_t *str, const uc16_t *from, size_t at);
UEXPORT size_t us8_insert_uz16be_e(us8_t *str, const uc16_t *from, size_t at, bool *error);
UEXPORT size_t us8_insert_uz16ben(us8_t *str, const uc16_t *from, size_t from_len, size_t at);
UEXPORT size_t us8_insert_uz16ben_e(us8_t *str, const uc16_t *from, size_t from_len, size_t at, bool *error);

UEXPORT size_t us8_insert_fmt_uz8(us8_t *str, const uc8_t *from, size_t at, ...);
UEXPORT size_t us8_insert_fmt_uz8_e(us8_t *str, const uc8_t *from, size_t at, bool *error, ...);
UEXPORT size_t us8_insert_fmt_uz8_v(us8_t *str, const uc8_t *from, va_list *args, size_t at);
UEXPORT size_t us8_insert_fmt_uz8_v_e(us8_t *str, const uc8_t *from, va_list *args, size_t at, bool *error);
UEXPORT size_t us8_insert_fmt_uz8n(us8_t *str, const uc8_t *from, size_t from_len, size_t at, ...);
UEXPORT size_t us8_insert_fmt_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, size_t at, bool *error, ...);
UEXPORT size_t us8_insert_fmt_uz8n_v(us8_t *str, const uc8_t *from, size_t from_len, va_list *args, size_t at);
UEXPORT size_t us8_insert_fmt_uz8n_v_e(us8_t *str, const uc8_t *from, size_t from_len, va_list *args, size_t at, bool *error);
UEXPORT size_t us8_insert_fmt_ucv8(us8_t *str, ucv8_t from, size_t at, ...);
UEXPORT size_t us8_insert_fmt_ucv8_e(us8_t *str, ucv8_t from, size_t at, bool *error, ...);
UEXPORT size_t us8_insert_fmt_ucv8_v(us8_t *str, ucv8_t from, va_list *args, size_t at);
UEXPORT size_t us8_insert_fmt_ucv8_v_e(us8_t *str, ucv8_t from, va_list *args, size_t at, bool *error);
UEXPORT size_t us8_insert_fmt_uv8(us8_t *str, uv8_t from, size_t at, ...);
UEXPORT size_t us8_insert_fmt_uv8_e(us8_t *str, uv8_t from, size_t at, bool *error, ...);
UEXPORT size_t us8_insert_fmt_uv8_v(us8_t *str, uv8_t from, va_list *args, size_t at);
UEXPORT size_t us8_insert_fmt_uv8_v_e(us8_t *str, uv8_t from, va_list *args, size_t at, bool *error);
UEXPORT size_t us8_insert_fmt_us8(us8_t *str, const us8_t *from, size_t at, ...);
UEXPORT size_t us8_insert_fmt_us8_e(us8_t *str, const us8_t *from, size_t at, bool *error, ...);
UEXPORT size_t us8_insert_fmt_us8_v(us8_t *str, const us8_t *from, va_list *args, size_t at);
UEXPORT size_t us8_insert_fmt_us8_v_e(us8_t *str, const us8_t *from, va_list *args, size_t at, bool *error);

UEXPORT size_t us8_insert_float(us8_t *str, double from, size_t at);
UEXPORT size_t us8_insert_float_e(us8_t *str, double from, size_t at, bool *error);
UEXPORT size_t us8_insert_float_fmt(us8_t *str, double from, const struct ufmt8_float_output *fmt, size_t at);
UEXPORT size_t us8_insert_float_fmt_e(us8_t *str, double from, const struct ufmt8_float_output *fmt, size_t at, bool *error);

UEXPORT size_t us8_insert_int(us8_t *str, intmax_t from, size_t at);
UEXPORT size_t us8_insert_int_e(us8_t *str, intmax_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_int_fmt(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt, size_t at);
UEXPORT size_t us8_insert_int_fmt_e(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt, size_t at, bool *error);
UEXPORT size_t us8_insert_uint(us8_t *str, uintmax_t from, size_t at);
UEXPORT size_t us8_insert_uint_e(us8_t *str, uintmax_t from, size_t at, bool *error);
UEXPORT size_t us8_insert_uint_fmt(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt, size_t at);
UEXPORT size_t us8_insert_uint_fmt_e(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt, size_t at, bool *error);

UEXPORT size_t us8_insert_bool(us8_t *str, bool from, size_t at);
UEXPORT size_t us8_insert_bool_e(us8_t *str, bool from, size_t at, bool *error);
UEXPORT size_t us8_insert_case_bool(us8_t *str, ucase_t ca, bool from, size_t at);
UEXPORT size_t us8_insert_case_bool_e(us8_t *str, ucase_t ca, bool from, size_t at, bool *error);
UEXPORT size_t us8_insert_lower_bool(us8_t *str, bool from, size_t at);
UEXPORT size_t us8_insert_lower_bool_e(us8_t *str, bool from, size_t at, bool *error);
UEXPORT size_t us8_insert_upper_bool(us8_t *str, bool from, size_t at);
UEXPORT size_t us8_insert_upper_bool_e(us8_t *str, bool from, size_t at, bool *error);

// Prepend

UEXPORT size_t us32_prepend_uc32(us32_t *str, uc32_t from);
UEXPORT size_t us32_prepend_uc32_e(us32_t *str, uc32_t from, bool *error);
UEXPORT size_t us32_prepend_uc32n(us32_t *str, uc32_t from, size_t n);
UEXPORT size_t us32_prepend_uc32n_e(us32_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us32_prepend_uz32(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_prepend_uz32_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_prepend_uz32n(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_prepend_ucv32(us32_t *str, ucv32_t from);
UEXPORT size_t us32_prepend_ucv32_e(us32_t *str, ucv32_t from, bool *error);
UEXPORT size_t us32_prepend_uv32(us32_t *str, uv32_t from);
UEXPORT size_t us32_prepend_uv32_e(us32_t *str, uv32_t from, bool *error);
UEXPORT size_t us32_prepend_us32(us32_t *str, const us32_t *from);
UEXPORT size_t us32_prepend_us32_e(us32_t *str, const us32_t *from, bool *error);

UEXPORT size_t us32_prepend_uc16(us32_t *str, uc16_t from);
UEXPORT size_t us32_prepend_uc16_e(us32_t *str, uc16_t from, bool *error);
UEXPORT size_t us32_prepend_uc16n(us32_t *str, uc16_t from, size_t n);
UEXPORT size_t us32_prepend_uc16n_e(us32_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us32_prepend_uz16(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_prepend_uz16_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_prepend_uz16n(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz16n_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_prepend_ucv16(us32_t *str, ucv16_t from);
UEXPORT size_t us32_prepend_ucv16_e(us32_t *str, ucv16_t from, bool *error);
UEXPORT size_t us32_prepend_uv16(us32_t *str, uv16_t from);
UEXPORT size_t us32_prepend_uv16_e(us32_t *str, uv16_t from, bool *error);
UEXPORT size_t us32_prepend_us16(us32_t *str, const us16_t *from);
UEXPORT size_t us32_prepend_us16_e(us32_t *str, const us16_t *from, bool *error);

UEXPORT size_t us32_prepend_uc8(us32_t *str, uc8_t from);
UEXPORT size_t us32_prepend_uc8_e(us32_t *str, uc8_t from, bool *error);
UEXPORT size_t us32_prepend_uc8n(us32_t *str, uc8_t from, size_t n);
UEXPORT size_t us32_prepend_uc8n_e(us32_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us32_prepend_uz8(us32_t *str, const uc8_t *from);
UEXPORT size_t us32_prepend_uz8_e(us32_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us32_prepend_uz8n(us32_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz8n_e(us32_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_prepend_ucv8(us32_t *str, ucv8_t from);
UEXPORT size_t us32_prepend_ucv8_e(us32_t *str, ucv8_t from, bool *error);
UEXPORT size_t us32_prepend_uv8(us32_t *str, uv8_t from);
UEXPORT size_t us32_prepend_uv8_e(us32_t *str, uv8_t from, bool *error);
UEXPORT size_t us32_prepend_us8(us32_t *str, const us8_t *from);
UEXPORT size_t us32_prepend_us8_e(us32_t *str, const us8_t *from, bool *error);

UEXPORT size_t us32_prepend_bytes(us32_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us32_prepend_bytes_e(us32_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us32_prepend_bytesn(us32_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us32_prepend_bytesn_e(us32_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us32_prepend_uz32le(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_prepend_uz32le_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_prepend_uz32len(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz32len_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_prepend_uz16le(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_prepend_uz16le_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_prepend_uz16len(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz16len_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_prepend_uz32be(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_prepend_uz32be_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_prepend_uz32ben(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz32ben_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_prepend_uz16be(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_prepend_uz16be_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_prepend_uz16ben(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_prepend_uz16ben_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us32_prepend_fmt_uz32(us32_t *str, const uc32_t *from, ...);
UEXPORT size_t us32_prepend_fmt_uz32_e(us32_t *str, const uc32_t *from, bool *error, ...);
UEXPORT size_t us32_prepend_fmt_uz32_v(us32_t *str, const uc32_t *from, va_list *args);
UEXPORT size_t us32_prepend_fmt_uz32_v_e(us32_t *str, const uc32_t *from, va_list *args, bool *error);
UEXPORT size_t us32_prepend_fmt_uz32n(us32_t *str, const uc32_t *from, size_t from_len, ...);
UEXPORT size_t us32_prepend_fmt_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us32_prepend_fmt_uz32n_v(us32_t *str, const uc32_t *from, size_t from_len, va_list *args);
UEXPORT size_t us32_prepend_fmt_uz32n_v_e(us32_t *str, const uc32_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us32_prepend_fmt_ucv32(us32_t *str, ucv32_t from, ...);
UEXPORT size_t us32_prepend_fmt_ucv32_e(us32_t *str, ucv32_t from, bool *error, ...);
UEXPORT size_t us32_prepend_fmt_ucv32_v(us32_t *str, ucv32_t from, va_list *args);
UEXPORT size_t us32_prepend_fmt_ucv32_v_e(us32_t *str, ucv32_t from, va_list *args, bool *error);
UEXPORT size_t us32_prepend_fmt_uv32(us32_t *str, uv32_t from, ...);
UEXPORT size_t us32_prepend_fmt_uv32_e(us32_t *str, uv32_t from, bool *error, ...);
UEXPORT size_t us32_prepend_fmt_uv32_v(us32_t *str, uv32_t from, va_list *args);
UEXPORT size_t us32_prepend_fmt_uv32_v_e(us32_t *str, uv32_t from, va_list *args, bool *error);
UEXPORT size_t us32_prepend_fmt_us32(us32_t *str, const us32_t *from, ...);
UEXPORT size_t us32_prepend_fmt_us32_e(us32_t *str, const us32_t *from, bool *error, ...);
UEXPORT size_t us32_prepend_fmt_us32_v(us32_t *str, const us32_t *from, va_list *args);
UEXPORT size_t us32_prepend_fmt_us32_v_e(us32_t *str, const us32_t *from, va_list *args, bool *error);

UEXPORT size_t us32_prepend_float(us32_t *str, double from);
UEXPORT size_t us32_prepend_float_e(us32_t *str, double from, bool *error);
UEXPORT size_t us32_prepend_float_fmt(us32_t *str, double from, const struct ufmt32_float_output *fmt);
UEXPORT size_t us32_prepend_float_fmt_e(us32_t *str, double from, const struct ufmt32_float_output *fmt, bool *error);

UEXPORT size_t us32_prepend_int(us32_t *str, intmax_t from);
UEXPORT size_t us32_prepend_int_e(us32_t *str, intmax_t from, bool *error);
UEXPORT size_t us32_prepend_int_fmt(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t us32_prepend_int_fmt_e(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt, bool *error);
UEXPORT size_t us32_prepend_uint(us32_t *str, uintmax_t from);
UEXPORT size_t us32_prepend_uint_e(us32_t *str, uintmax_t from, bool *error);
UEXPORT size_t us32_prepend_uint_fmt(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t us32_prepend_uint_fmt_e(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt, bool *error);

UEXPORT size_t us32_prepend_bool(us32_t *str, bool from);
UEXPORT size_t us32_prepend_bool_e(us32_t *str, bool from, bool *error);
UEXPORT size_t us32_prepend_case_bool(us32_t *str, ucase_t ca, bool from);
UEXPORT size_t us32_prepend_case_bool_e(us32_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us32_prepend_lower_bool(us32_t *str, bool from);
UEXPORT size_t us32_prepend_lower_bool_e(us32_t *str, bool from, bool *error);
UEXPORT size_t us32_prepend_upper_bool(us32_t *str, bool from);
UEXPORT size_t us32_prepend_upper_bool_e(us32_t *str, bool from, bool *error);


UEXPORT size_t us16_prepend_uc32(us16_t *str, uc32_t from);
UEXPORT size_t us16_prepend_uc32_e(us16_t *str, uc32_t from, bool *error);
UEXPORT size_t us16_prepend_uc32n(us16_t *str, uc32_t from, size_t n);
UEXPORT size_t us16_prepend_uc32n_e(us16_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us16_prepend_uz32(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_prepend_uz32_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_prepend_uz32n(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz32n_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_prepend_ucv32(us16_t *str, ucv32_t from);
UEXPORT size_t us16_prepend_ucv32_e(us16_t *str, ucv32_t from, bool *error);
UEXPORT size_t us16_prepend_uv32(us16_t *str, uv32_t from);
UEXPORT size_t us16_prepend_uv32_e(us16_t *str, uv32_t from, bool *error);
UEXPORT size_t us16_prepend_us32(us16_t *str, const us32_t *from);
UEXPORT size_t us16_prepend_us32_e(us16_t *str, const us32_t *from, bool *error);

UEXPORT size_t us16_prepend_uc16(us16_t *str, uc16_t from);
UEXPORT size_t us16_prepend_uc16_e(us16_t *str, uc16_t from, bool *error);
UEXPORT size_t us16_prepend_uc16n(us16_t *str, uc16_t from, size_t n);
UEXPORT size_t us16_prepend_uc16n_e(us16_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us16_prepend_uz16(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_prepend_uz16_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_prepend_uz16n(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_prepend_ucv16(us16_t *str, ucv16_t from);
UEXPORT size_t us16_prepend_ucv16_e(us16_t *str, ucv16_t from, bool *error);
UEXPORT size_t us16_prepend_uv16(us16_t *str, uv16_t from);
UEXPORT size_t us16_prepend_uv16_e(us16_t *str, uv16_t from, bool *error);
UEXPORT size_t us16_prepend_us16(us16_t *str, const us16_t *from);
UEXPORT size_t us16_prepend_us16_e(us16_t *str, const us16_t *from, bool *error);

UEXPORT size_t us16_prepend_uc8(us16_t *str, uc8_t from);
UEXPORT size_t us16_prepend_uc8_e(us16_t *str, uc8_t from, bool *error);
UEXPORT size_t us16_prepend_uc8n(us16_t *str, uc8_t from, size_t n);
UEXPORT size_t us16_prepend_uc8n_e(us16_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us16_prepend_uz8(us16_t *str, const uc8_t *from);
UEXPORT size_t us16_prepend_uz8_e(us16_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us16_prepend_uz8n(us16_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz8n_e(us16_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_prepend_ucv8(us16_t *str, ucv8_t from);
UEXPORT size_t us16_prepend_ucv8_e(us16_t *str, ucv8_t from, bool *error);
UEXPORT size_t us16_prepend_uv8(us16_t *str, uv8_t from);
UEXPORT size_t us16_prepend_uv8_e(us16_t *str, uv8_t from, bool *error);
UEXPORT size_t us16_prepend_us8(us16_t *str, const us8_t *from);
UEXPORT size_t us16_prepend_us8_e(us16_t *str, const us8_t *from, bool *error);

UEXPORT size_t us16_prepend_bytes(us16_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us16_prepend_bytes_e(us16_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us16_prepend_bytesn(us16_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us16_prepend_bytesn_e(us16_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us16_prepend_uz32le(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_prepend_uz32le_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_prepend_uz32len(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz32len_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_prepend_uz16le(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_prepend_uz16le_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_prepend_uz16len(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz16len_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_prepend_uz32be(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_prepend_uz32be_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_prepend_uz32ben(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz32ben_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_prepend_uz16be(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_prepend_uz16be_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_prepend_uz16ben(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_prepend_uz16ben_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us16_prepend_fmt_uz16(us16_t *str, const uc16_t *from, ...);
UEXPORT size_t us16_prepend_fmt_uz16_e(us16_t *str, const uc16_t *from, bool *error, ...);
UEXPORT size_t us16_prepend_fmt_uz16_v(us16_t *str, const uc16_t *from, va_list *args);
UEXPORT size_t us16_prepend_fmt_uz16_v_e(us16_t *str, const uc16_t *from, va_list *args, bool *error);
UEXPORT size_t us16_prepend_fmt_uz16n(us16_t *str, const uc16_t *from, size_t from_len, ...);
UEXPORT size_t us16_prepend_fmt_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us16_prepend_fmt_uz16n_v(us16_t *str, const uc16_t *from, size_t from_len, va_list *args);
UEXPORT size_t us16_prepend_fmt_uz16n_v_e(us16_t *str, const uc16_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us16_prepend_fmt_ucv16(us16_t *str, ucv16_t from, ...);
UEXPORT size_t us16_prepend_fmt_ucv16_e(us16_t *str, ucv16_t from, bool *error, ...);
UEXPORT size_t us16_prepend_fmt_ucv16_v(us16_t *str, ucv16_t from, va_list *args);
UEXPORT size_t us16_prepend_fmt_ucv16_v_e(us16_t *str, ucv16_t from, va_list *args, bool *error);
UEXPORT size_t us16_prepend_fmt_uv16(us16_t *str, uv16_t from, ...);
UEXPORT size_t us16_prepend_fmt_uv16_e(us16_t *str, uv16_t from, bool *error, ...);
UEXPORT size_t us16_prepend_fmt_uv16_v(us16_t *str, uv16_t from, va_list *args);
UEXPORT size_t us16_prepend_fmt_uv16_v_e(us16_t *str, uv16_t from, va_list *args, bool *error);
UEXPORT size_t us16_prepend_fmt_us16(us16_t *str, const us16_t *from, ...);
UEXPORT size_t us16_prepend_fmt_us16_e(us16_t *str, const us16_t *from, bool *error, ...);
UEXPORT size_t us16_prepend_fmt_us16_v(us16_t *str, const us16_t *from, va_list *args);
UEXPORT size_t us16_prepend_fmt_us16_v_e(us16_t *str, const us16_t *from, va_list *args, bool *error);

UEXPORT size_t us16_prepend_float(us16_t *str, double from);
UEXPORT size_t us16_prepend_float_e(us16_t *str, double from, bool *error);
UEXPORT size_t us16_prepend_float_fmt(us16_t *str, double from, const struct ufmt16_float_output *fmt);
UEXPORT size_t us16_prepend_float_fmt_e(us16_t *str, double from, const struct ufmt16_float_output *fmt, bool *error);

UEXPORT size_t us16_prepend_int(us16_t *str, intmax_t from);
UEXPORT size_t us16_prepend_int_e(us16_t *str, intmax_t from, bool *error);
UEXPORT size_t us16_prepend_int_fmt(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t us16_prepend_int_fmt_e(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt, bool *error);
UEXPORT size_t us16_prepend_uint(us16_t *str, uintmax_t from);
UEXPORT size_t us16_prepend_uint_e(us16_t *str, uintmax_t from, bool *error);
UEXPORT size_t us16_prepend_uint_fmt(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t us16_prepend_uint_fmt_e(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt, bool *error);

UEXPORT size_t us16_prepend_bool(us16_t *str, bool from);
UEXPORT size_t us16_prepend_bool_e(us16_t *str, bool from, bool *error);
UEXPORT size_t us16_prepend_case_bool(us16_t *str, ucase_t ca, bool from);
UEXPORT size_t us16_prepend_case_bool_e(us16_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us16_prepend_lower_bool(us16_t *str, bool from);
UEXPORT size_t us16_prepend_lower_bool_e(us16_t *str, bool from, bool *error);
UEXPORT size_t us16_prepend_upper_bool(us16_t *str, bool from);
UEXPORT size_t us16_prepend_upper_bool_e(us16_t *str, bool from, bool *error);


UEXPORT size_t us8_prepend_uc32(us8_t *str, uc32_t from);
UEXPORT size_t us8_prepend_uc32_e(us8_t *str, uc32_t from, bool *error);
UEXPORT size_t us8_prepend_uc32n(us8_t *str, uc32_t from, size_t n);
UEXPORT size_t us8_prepend_uc32n_e(us8_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us8_prepend_uz32(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_prepend_uz32_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_prepend_uz32n(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz32n_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_prepend_ucv32(us8_t *str, ucv32_t from);
UEXPORT size_t us8_prepend_ucv32_e(us8_t *str, ucv32_t from, bool *error);
UEXPORT size_t us8_prepend_uv32(us8_t *str, uv32_t from);
UEXPORT size_t us8_prepend_uv32_e(us8_t *str, uv32_t from, bool *error);
UEXPORT size_t us8_prepend_us32(us8_t *str, const us32_t *from);
UEXPORT size_t us8_prepend_us32_e(us8_t *str, const us32_t *from, bool *error);
UEXPORT size_t us8_prepend_us32_range(us8_t *str, const us32_t *from, size_t begin, size_t len);
UEXPORT size_t us8_prepend_us32_range_e(us8_t *str, const us32_t *from, size_t begin, size_t len, bool *error);

UEXPORT size_t us8_prepend_uc16(us8_t *str, uc16_t from);
UEXPORT size_t us8_prepend_uc16_e(us8_t *str, uc16_t from, bool *error);
UEXPORT size_t us8_prepend_uc16n(us8_t *str, uc16_t from, size_t n);
UEXPORT size_t us8_prepend_uc16n_e(us8_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us8_prepend_uz16(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_prepend_uz16_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_prepend_uz16n(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz16n_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_prepend_ucv16(us8_t *str, ucv16_t from);
UEXPORT size_t us8_prepend_ucv16_e(us8_t *str, ucv16_t from, bool *error);
UEXPORT size_t us8_prepend_uv16(us8_t *str, uv16_t from);
UEXPORT size_t us8_prepend_uv16_e(us8_t *str, uv16_t from, bool *error);
UEXPORT size_t us8_prepend_us16(us8_t *str, const us16_t *from);
UEXPORT size_t us8_prepend_us16_e(us8_t *str, const us16_t *from, bool *error);

UEXPORT size_t us8_prepend_uc8(us8_t *str, uc8_t from);
UEXPORT size_t us8_prepend_uc8_e(us8_t *str, uc8_t from, bool *error);
UEXPORT size_t us8_prepend_uc8n(us8_t *str, uc8_t from, size_t n);
UEXPORT size_t us8_prepend_uc8n_e(us8_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us8_prepend_uz8(us8_t *str, const uc8_t *from);
UEXPORT size_t us8_prepend_uz8_e(us8_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us8_prepend_uz8n(us8_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_prepend_ucv8(us8_t *str, ucv8_t from);
UEXPORT size_t us8_prepend_ucv8_e(us8_t *str, ucv8_t from, bool *error);
UEXPORT size_t us8_prepend_uv8(us8_t *str, uv8_t from);
UEXPORT size_t us8_prepend_uv8_e(us8_t *str, uv8_t from, bool *error);
UEXPORT size_t us8_prepend_us8(us8_t *str, const us8_t *from);
UEXPORT size_t us8_prepend_us8_e(us8_t *str, const us8_t *from, bool *error);

UEXPORT size_t us8_prepend_bytes(us8_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us8_prepend_bytes_e(us8_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us8_prepend_bytesn(us8_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us8_prepend_bytesn_e(us8_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us8_prepend_uz32le(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_prepend_uz32le_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_prepend_uz32len(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz32len_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_prepend_uz16le(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_prepend_uz16le_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_prepend_uz16len(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz16len_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_prepend_uz32be(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_prepend_uz32be_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_prepend_uz32ben(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz32ben_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_prepend_uz16be(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_prepend_uz16be_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_prepend_uz16ben(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_prepend_uz16ben_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us8_prepend_fmt_uz8(us8_t *str, const uc8_t *from, ...);
UEXPORT size_t us8_prepend_fmt_uz8_e(us8_t *str, const uc8_t *from, bool *error, ...);
UEXPORT size_t us8_prepend_fmt_uz8_v(us8_t *str, const uc8_t *from, va_list *args);
UEXPORT size_t us8_prepend_fmt_uz8_v_e(us8_t *str, const uc8_t *from, va_list *args, bool *error);
UEXPORT size_t us8_prepend_fmt_uz8n(us8_t *str, const uc8_t *from, size_t from_len, ...);
UEXPORT size_t us8_prepend_fmt_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us8_prepend_fmt_uz8n_v(us8_t *str, const uc8_t *from, size_t from_len, va_list *args);
UEXPORT size_t us8_prepend_fmt_uz8n_v_e(us8_t *str, const uc8_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us8_prepend_fmt_ucv8(us8_t *str, ucv8_t from, ...);
UEXPORT size_t us8_prepend_fmt_ucv8_e(us8_t *str, ucv8_t from, bool *error, ...);
UEXPORT size_t us8_prepend_fmt_ucv8_v(us8_t *str, ucv8_t from, va_list *args);
UEXPORT size_t us8_prepend_fmt_ucv8_v_e(us8_t *str, ucv8_t from, va_list *args, bool *error);
UEXPORT size_t us8_prepend_fmt_uv8(us8_t *str, uv8_t from, ...);
UEXPORT size_t us8_prepend_fmt_uv8_e(us8_t *str, uv8_t from, bool *error, ...);
UEXPORT size_t us8_prepend_fmt_uv8_v(us8_t *str, uv8_t from, va_list *args);
UEXPORT size_t us8_prepend_fmt_uv8_v_e(us8_t *str, uv8_t from, va_list *args, bool *error);
UEXPORT size_t us8_prepend_fmt_us8(us8_t *str, const us8_t *from, ...);
UEXPORT size_t us8_prepend_fmt_us8_e(us8_t *str, const us8_t *from, bool *error, ...);
UEXPORT size_t us8_prepend_fmt_us8_v(us8_t *str, const us8_t *from, va_list *args);
UEXPORT size_t us8_prepend_fmt_us8_v_e(us8_t *str, const us8_t *from, va_list *args, bool *error);

UEXPORT size_t us8_prepend_float(us8_t *str, double from);
UEXPORT size_t us8_prepend_float_e(us8_t *str, double from, bool *error);
UEXPORT size_t us8_prepend_float_fmt(us8_t *str, double from, const struct ufmt8_float_output *fmt);
UEXPORT size_t us8_prepend_float_fmt_e(us8_t *str, double from, const struct ufmt8_float_output *fmt, bool *error);

UEXPORT size_t us8_prepend_int(us8_t *str, intmax_t from);
UEXPORT size_t us8_prepend_int_e(us8_t *str, intmax_t from, bool *error);
UEXPORT size_t us8_prepend_int_fmt(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t us8_prepend_int_fmt_e(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt, bool *error);
UEXPORT size_t us8_prepend_uint(us8_t *str, uintmax_t from);
UEXPORT size_t us8_prepend_uint_e(us8_t *str, uintmax_t from, bool *error);
UEXPORT size_t us8_prepend_uint_fmt(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t us8_prepend_uint_fmt_e(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt, bool *error);

UEXPORT size_t us8_prepend_bool(us8_t *str, bool from);
UEXPORT size_t us8_prepend_bool_e(us8_t *str, bool from, bool *error);
UEXPORT size_t us8_prepend_case_bool(us8_t *str, ucase_t ca, bool from);
UEXPORT size_t us8_prepend_case_bool_e(us8_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us8_prepend_lower_bool(us8_t *str, bool from);
UEXPORT size_t us8_prepend_lower_bool_e(us8_t *str, bool from, bool *error);
UEXPORT size_t us8_prepend_upper_bool(us8_t *str, bool from);
UEXPORT size_t us8_prepend_upper_bool_e(us8_t *str, bool from, bool *error);

// Capacity

UEXPORT size_t us32_cap(const us32_t *str);
UEXPORT size_t us32_set_cap(us32_t *str, size_t cap);
UEXPORT size_t us32_set_cap_e(us32_t *str, size_t cap, bool *error);
UEXPORT size_t us32_raise_cap(us32_t *str);
UEXPORT size_t us32_raise_cap_e(us32_t *str, bool *error);
UEXPORT size_t us32_raise_cap_to(us32_t *str, size_t to);
UEXPORT size_t us32_raise_cap_to_e(us32_t *str, size_t to, bool *error);
UEXPORT size_t us32_shrink_to_fit(us32_t *str);
UEXPORT size_t us32_shrink_to_fit_e(us32_t *str, bool *error);

UEXPORT size_t us16_cap(const us16_t *str);
UEXPORT size_t us16_set_cap(us16_t *str, size_t cap);
UEXPORT size_t us16_set_cap_e(us16_t *str, size_t cap, bool *error);
UEXPORT size_t us16_raise_cap(us16_t *str);
UEXPORT size_t us16_raise_cap_e(us16_t *str, bool *error);
UEXPORT size_t us16_raise_cap_to(us16_t *str, size_t to);
UEXPORT size_t us16_raise_cap_to_e(us16_t *str, size_t to, bool *error);
UEXPORT size_t us16_shrink_to_fit(us16_t *str);
UEXPORT size_t us16_shrink_to_fit_e(us16_t *str, bool *error);

UEXPORT size_t us8_cap(const us8_t *str);
UEXPORT size_t us8_set_cap(us8_t *str, size_t cap);
UEXPORT size_t us8_set_cap_e(us8_t *str, size_t cap, bool *error);
UEXPORT size_t us8_raise_cap(us8_t *str);
UEXPORT size_t us8_raise_cap_e(us8_t *str, bool *error);
UEXPORT size_t us8_raise_cap_to(us8_t *str, size_t to);
UEXPORT size_t us8_raise_cap_to_e(us8_t *str, size_t to, bool *error);
UEXPORT size_t us8_shrink_to_fit(us8_t *str);
UEXPORT size_t us8_shrink_to_fit_e(us8_t *str, bool *error);

// Assign

UEXPORT size_t us32_assign_uc32(us32_t *str, uc32_t from);
UEXPORT size_t us32_assign_uc32_e(us32_t *str, uc32_t from, bool *error);
UEXPORT size_t us32_assign_uc32n(us32_t *str, uc32_t from, size_t n);
UEXPORT size_t us32_assign_uc32n_e(us32_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us32_assign_uz32(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_assign_uz32_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_assign_uz32n(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_assign_ucv32(us32_t *str, ucv32_t from);
UEXPORT size_t us32_assign_ucv32_e(us32_t *str, ucv32_t from, bool *error);
UEXPORT size_t us32_assign_uv32(us32_t *str, uv32_t from);
UEXPORT size_t us32_assign_uv32_e(us32_t *str, uv32_t from, bool *error);
UEXPORT size_t us32_assign_us32(us32_t *str, const us32_t *from);
UEXPORT size_t us32_assign_us32_e(us32_t *str, const us32_t *from, bool *error);

UEXPORT size_t us32_assign_uc16(us32_t *str, uc16_t from);
UEXPORT size_t us32_assign_uc16_e(us32_t *str, uc16_t from, bool *error);
UEXPORT size_t us32_assign_uc16n(us32_t *str, uc16_t from, size_t n);
UEXPORT size_t us32_assign_uc16n_e(us32_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us32_assign_uz16(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_assign_uz16_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_assign_uz16n(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz16n_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_assign_ucv16(us32_t *str, ucv16_t from);
UEXPORT size_t us32_assign_ucv16_e(us32_t *str, ucv16_t from, bool *error);
UEXPORT size_t us32_assign_uv16(us32_t *str, uv16_t from);
UEXPORT size_t us32_assign_uv16_e(us32_t *str, uv16_t from, bool *error);
UEXPORT size_t us32_assign_us16(us32_t *str, const us16_t *from);
UEXPORT size_t us32_assign_us16_e(us32_t *str, const us16_t *from, bool *error);

UEXPORT size_t us32_assign_uc8(us32_t *str, uc8_t from);
UEXPORT size_t us32_assign_uc8_e(us32_t *str, uc8_t from, bool *error);
UEXPORT size_t us32_assign_uc8n(us32_t *str, uc8_t from, size_t n);
UEXPORT size_t us32_assign_uc8n_e(us32_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us32_assign_uz8(us32_t *str, const uc8_t *from);
UEXPORT size_t us32_assign_uz8_e(us32_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us32_assign_uz8n(us32_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz8n_e(us32_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_assign_ucv8(us32_t *str, ucv8_t from);
UEXPORT size_t us32_assign_ucv8_e(us32_t *str, ucv8_t from, bool *error);
UEXPORT size_t us32_assign_uv8(us32_t *str, uv8_t from);
UEXPORT size_t us32_assign_uv8_e(us32_t *str, uv8_t from, bool *error);
UEXPORT size_t us32_assign_us8(us32_t *str, const us8_t *from);
UEXPORT size_t us32_assign_us8_e(us32_t *str, const us8_t *from, bool *error);

UEXPORT size_t us32_assign_bytes(us32_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us32_assign_bytes_e(us32_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us32_assign_bytesn(us32_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us32_assign_bytesn_e(us32_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us32_assign_uz32le(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_assign_uz32le_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_assign_uz32len(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz32len_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_assign_uz16le(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_assign_uz16le_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_assign_uz16len(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz16len_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_assign_uz32be(us32_t *str, const uc32_t *from);
UEXPORT size_t us32_assign_uz32be_e(us32_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us32_assign_uz32ben(us32_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz32ben_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us32_assign_uz16be(us32_t *str, const uc16_t *from);
UEXPORT size_t us32_assign_uz16be_e(us32_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us32_assign_uz16ben(us32_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us32_assign_uz16ben_e(us32_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us32_assign_fmt_uz32(us32_t *str, const uc32_t *from, ...);
UEXPORT size_t us32_assign_fmt_uz32_e(us32_t *str, const uc32_t *from, bool *error, ...);
UEXPORT size_t us32_assign_fmt_uz32_v(us32_t *str, const uc32_t *from, va_list *args);
UEXPORT size_t us32_assign_fmt_uz32_v_e(us32_t *str, const uc32_t *from, va_list *args, bool *error);
UEXPORT size_t us32_assign_fmt_uz32n(us32_t *str, const uc32_t *from, size_t from_len, ...);
UEXPORT size_t us32_assign_fmt_uz32n_e(us32_t *str, const uc32_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us32_assign_fmt_uz32n_v(us32_t *str, const uc32_t *from, size_t from_len, va_list *args);
UEXPORT size_t us32_assign_fmt_uz32n_v_e(us32_t *str, const uc32_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us32_assign_fmt_ucv32(us32_t *str, ucv32_t from, ...);
UEXPORT size_t us32_assign_fmt_ucv32_e(us32_t *str, ucv32_t from, bool *error, ...);
UEXPORT size_t us32_assign_fmt_ucv32_v(us32_t *str, ucv32_t from, va_list *args);
UEXPORT size_t us32_assign_fmt_ucv32_v_e(us32_t *str, ucv32_t from, va_list *args, bool *error);
UEXPORT size_t us32_assign_fmt_uv32(us32_t *str, uv32_t from, ...);
UEXPORT size_t us32_assign_fmt_uv32_e(us32_t *str, uv32_t from, bool *error, ...);
UEXPORT size_t us32_assign_fmt_uv32_v(us32_t *str, uv32_t from, va_list *args);
UEXPORT size_t us32_assign_fmt_uv32_v_e(us32_t *str, uv32_t from, va_list *args, bool *error);
UEXPORT size_t us32_assign_fmt_us32(us32_t *str, const us32_t *from, ...);
UEXPORT size_t us32_assign_fmt_us32_e(us32_t *str, const us32_t *from, bool *error, ...);
UEXPORT size_t us32_assign_fmt_us32_v(us32_t *str, const us32_t *from, va_list *args);
UEXPORT size_t us32_assign_fmt_us32_v_e(us32_t *str, const us32_t *from, va_list *args, bool *error);

UEXPORT size_t us32_assign_float(us32_t *str, double from);
UEXPORT size_t us32_assign_float_e(us32_t *str, double from, bool *error);
UEXPORT size_t us32_assign_float_fmt(us32_t *str, double from, const struct ufmt32_float_output *fmt);
UEXPORT size_t us32_assign_float_fmt_e(us32_t *str, double from, const struct ufmt32_float_output *fmt, bool *error);

UEXPORT size_t us32_assign_int(us32_t *str, intmax_t from);
UEXPORT size_t us32_assign_int_e(us32_t *str, intmax_t from, bool *error);
UEXPORT size_t us32_assign_int_fmt(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t us32_assign_int_fmt_e(us32_t *str, intmax_t from, const struct ufmt32_int_output *fmt, bool *error);
UEXPORT size_t us32_assign_uint(us32_t *str, uintmax_t from);
UEXPORT size_t us32_assign_uint_e(us32_t *str, uintmax_t from, bool *error);
UEXPORT size_t us32_assign_uint_fmt(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt);
UEXPORT size_t us32_assign_uint_fmt_e(us32_t *str, uintmax_t from, const struct ufmt32_int_output *fmt, bool *error);

UEXPORT size_t us32_assign_bool(us32_t *str, bool from);
UEXPORT size_t us32_assign_bool_e(us32_t *str, bool from, bool *error);
UEXPORT size_t us32_assign_case_bool(us32_t *str, ucase_t ca, bool from);
UEXPORT size_t us32_assign_case_bool_e(us32_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us32_assign_lower_bool(us32_t *str, bool from);
UEXPORT size_t us32_assign_lower_bool_e(us32_t *str, bool from, bool *error);
UEXPORT size_t us32_assign_upper_bool(us32_t *str, bool from);
UEXPORT size_t us32_assign_upper_bool_e(us32_t *str, bool from, bool *error);


UEXPORT size_t us16_assign_uc32(us16_t *str, uc32_t from);
UEXPORT size_t us16_assign_uc32_e(us16_t *str, uc32_t from, bool *error);
UEXPORT size_t us16_assign_uc32n(us16_t *str, uc32_t from, size_t n);
UEXPORT size_t us16_assign_uc32n_e(us16_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us16_assign_uz32(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_assign_uz32_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_assign_uz32n(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz32n_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_assign_ucv32(us16_t *str, ucv32_t from);
UEXPORT size_t us16_assign_ucv32_e(us16_t *str, ucv32_t from, bool *error);
UEXPORT size_t us16_assign_uv32(us16_t *str, uv32_t from);
UEXPORT size_t us16_assign_uv32_e(us16_t *str, uv32_t from, bool *error);
UEXPORT size_t us16_assign_us32(us16_t *str, const us32_t *from);
UEXPORT size_t us16_assign_us32_e(us16_t *str, const us32_t *from, bool *error);

UEXPORT size_t us16_assign_uc16(us16_t *str, uc16_t from);
UEXPORT size_t us16_assign_uc16_e(us16_t *str, uc16_t from, bool *error);
UEXPORT size_t us16_assign_uc16n(us16_t *str, uc16_t from, size_t n);
UEXPORT size_t us16_assign_uc16n_e(us16_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us16_assign_uz16(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_assign_uz16_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_assign_uz16n(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_assign_ucv16(us16_t *str, ucv16_t from);
UEXPORT size_t us16_assign_ucv16_e(us16_t *str, ucv16_t from, bool *error);
UEXPORT size_t us16_assign_uv16(us16_t *str, uv16_t from);
UEXPORT size_t us16_assign_uv16_e(us16_t *str, uv16_t from, bool *error);
UEXPORT size_t us16_assign_us16(us16_t *str, const us16_t *from);
UEXPORT size_t us16_assign_us16_e(us16_t *str, const us16_t *from, bool *error);

UEXPORT size_t us16_assign_uc8(us16_t *str, uc8_t from);
UEXPORT size_t us16_assign_uc8_e(us16_t *str, uc8_t from, bool *error);
UEXPORT size_t us16_assign_uc8n(us16_t *str, uc8_t from, size_t n);
UEXPORT size_t us16_assign_uc8n_e(us16_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us16_assign_uz8(us16_t *str, const uc8_t *from);
UEXPORT size_t us16_assign_uz8_e(us16_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us16_assign_uz8n(us16_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz8n_e(us16_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_assign_ucv8(us16_t *str, ucv8_t from);
UEXPORT size_t us16_assign_ucv8_e(us16_t *str, ucv8_t from, bool *error);
UEXPORT size_t us16_assign_uv8(us16_t *str, uv8_t from);
UEXPORT size_t us16_assign_uv8_e(us16_t *str, uv8_t from, bool *error);
UEXPORT size_t us16_assign_us8(us16_t *str, const us8_t *from);
UEXPORT size_t us16_assign_us8_e(us16_t *str, const us8_t *from, bool *error);

UEXPORT size_t us16_assign_bytes(us16_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us16_assign_bytes_e(us16_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us16_assign_bytesn(us16_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us16_assign_bytesn_e(us16_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us16_assign_uz32le(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_assign_uz32le_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_assign_uz32len(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz32len_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_assign_uz16le(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_assign_uz16le_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_assign_uz16len(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz16len_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_assign_uz32be(us16_t *str, const uc32_t *from);
UEXPORT size_t us16_assign_uz32be_e(us16_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us16_assign_uz32ben(us16_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz32ben_e(us16_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us16_assign_uz16be(us16_t *str, const uc16_t *from);
UEXPORT size_t us16_assign_uz16be_e(us16_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us16_assign_uz16ben(us16_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us16_assign_uz16ben_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us16_assign_fmt_uz16(us16_t *str, const uc16_t *from, ...);
UEXPORT size_t us16_assign_fmt_uz16_e(us16_t *str, const uc16_t *from, bool *error, ...);
UEXPORT size_t us16_assign_fmt_uz16_v(us16_t *str, const uc16_t *from, va_list *args);
UEXPORT size_t us16_assign_fmt_uz16_v_e(us16_t *str, const uc16_t *from, va_list *args, bool *error);
UEXPORT size_t us16_assign_fmt_uz16n(us16_t *str, const uc16_t *from, size_t from_len, ...);
UEXPORT size_t us16_assign_fmt_uz16n_e(us16_t *str, const uc16_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us16_assign_fmt_uz16n_v(us16_t *str, const uc16_t *from, size_t from_len, va_list *args);
UEXPORT size_t us16_assign_fmt_uz16n_v_e(us16_t *str, const uc16_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us16_assign_fmt_ucv16(us16_t *str, ucv16_t from, ...);
UEXPORT size_t us16_assign_fmt_ucv16_e(us16_t *str, ucv16_t from, bool *error, ...);
UEXPORT size_t us16_assign_fmt_ucv16_v(us16_t *str, ucv16_t from, va_list *args);
UEXPORT size_t us16_assign_fmt_ucv16_v_e(us16_t *str, ucv16_t from, va_list *args, bool *error);
UEXPORT size_t us16_assign_fmt_uv16(us16_t *str, uv16_t from, ...);
UEXPORT size_t us16_assign_fmt_uv16_e(us16_t *str, uv16_t from, bool *error, ...);
UEXPORT size_t us16_assign_fmt_uv16_v(us16_t *str, uv16_t from, va_list *args);
UEXPORT size_t us16_assign_fmt_uv16_v_e(us16_t *str, uv16_t from, va_list *args, bool *error);
UEXPORT size_t us16_assign_fmt_us16(us16_t *str, const us16_t *from, ...);
UEXPORT size_t us16_assign_fmt_us16_e(us16_t *str, const us16_t *from, bool *error, ...);
UEXPORT size_t us16_assign_fmt_us16_v(us16_t *str, const us16_t *from, va_list *args);
UEXPORT size_t us16_assign_fmt_us16_v_e(us16_t *str, const us16_t *from, va_list *args, bool *error);

UEXPORT size_t us16_assign_float(us16_t *str, double from);
UEXPORT size_t us16_assign_float_e(us16_t *str, double from, bool *error);
UEXPORT size_t us16_assign_float_fmt(us16_t *str, double from, const struct ufmt16_float_output *fmt);
UEXPORT size_t us16_assign_float_fmt_e(us16_t *str, double from, const struct ufmt16_float_output *fmt, bool *error);

UEXPORT size_t us16_assign_int(us16_t *str, intmax_t from);
UEXPORT size_t us16_assign_int_e(us16_t *str, intmax_t from, bool *error);
UEXPORT size_t us16_assign_int_fmt(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t us16_assign_int_fmt_e(us16_t *str, intmax_t from, const struct ufmt16_int_output *fmt, bool *error);
UEXPORT size_t us16_assign_uint(us16_t *str, uintmax_t from);
UEXPORT size_t us16_assign_uint_e(us16_t *str, uintmax_t from, bool *error);
UEXPORT size_t us16_assign_uint_fmt(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt);
UEXPORT size_t us16_assign_uint_fmt_e(us16_t *str, uintmax_t from, const struct ufmt16_int_output *fmt, bool *error);

UEXPORT size_t us16_assign_bool(us16_t *str, bool from);
UEXPORT size_t us16_assign_bool_e(us16_t *str, bool from, bool *error);
UEXPORT size_t us16_assign_case_bool(us16_t *str, ucase_t ca, bool from);
UEXPORT size_t us16_assign_case_bool_e(us16_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us16_assign_lower_bool(us16_t *str, bool from);
UEXPORT size_t us16_assign_lower_bool_e(us16_t *str, bool from, bool *error);
UEXPORT size_t us16_assign_upper_bool(us16_t *str, bool from);
UEXPORT size_t us16_assign_upper_bool_e(us16_t *str, bool from, bool *error);


UEXPORT size_t us8_assign_uc32(us8_t *str, uc32_t from);
UEXPORT size_t us8_assign_uc32_e(us8_t *str, uc32_t from, bool *error);
UEXPORT size_t us8_assign_uc32n(us8_t *str, uc32_t from, size_t n);
UEXPORT size_t us8_assign_uc32n_e(us8_t *str, uc32_t from, size_t n, bool *error);
UEXPORT size_t us8_assign_uz32(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_assign_uz32_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_assign_uz32n(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz32n_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_assign_ucv32(us8_t *str, ucv32_t from);
UEXPORT size_t us8_assign_ucv32_e(us8_t *str, ucv32_t from, bool *error);
UEXPORT size_t us8_assign_uv32(us8_t *str, uv32_t from);
UEXPORT size_t us8_assign_uv32_e(us8_t *str, uv32_t from, bool *error);
UEXPORT size_t us8_assign_us32(us8_t *str, const us32_t *from);
UEXPORT size_t us8_assign_us32_e(us8_t *str, const us32_t *from, bool *error);
UEXPORT size_t us8_assign_us32_range(us8_t *str, const us32_t *from, size_t begin, size_t len);
UEXPORT size_t us8_assign_us32_range_e(us8_t *str, const us32_t *from, size_t begin, size_t len, bool *error);

UEXPORT size_t us8_assign_uc16(us8_t *str, uc16_t from);
UEXPORT size_t us8_assign_uc16_e(us8_t *str, uc16_t from, bool *error);
UEXPORT size_t us8_assign_uc16n(us8_t *str, uc16_t from, size_t n);
UEXPORT size_t us8_assign_uc16n_e(us8_t *str, uc16_t from, size_t n, bool *error);
UEXPORT size_t us8_assign_uz16(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_assign_uz16_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_assign_uz16n(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz16n_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_assign_ucv16(us8_t *str, ucv16_t from);
UEXPORT size_t us8_assign_ucv16_e(us8_t *str, ucv16_t from, bool *error);
UEXPORT size_t us8_assign_uv16(us8_t *str, uv16_t from);
UEXPORT size_t us8_assign_uv16_e(us8_t *str, uv16_t from, bool *error);
UEXPORT size_t us8_assign_us16(us8_t *str, const us16_t *from);
UEXPORT size_t us8_assign_us16_e(us8_t *str, const us16_t *from, bool *error);

UEXPORT size_t us8_assign_uc8(us8_t *str, uc8_t from);
UEXPORT size_t us8_assign_uc8_e(us8_t *str, uc8_t from, bool *error);
UEXPORT size_t us8_assign_uc8n(us8_t *str, uc8_t from, size_t n);
UEXPORT size_t us8_assign_uc8n_e(us8_t *str, uc8_t from, size_t n, bool *error);
UEXPORT size_t us8_assign_uz8(us8_t *str, const uc8_t *from);
UEXPORT size_t us8_assign_uz8_e(us8_t *str, const uc8_t *from, bool *error);
UEXPORT size_t us8_assign_uz8n(us8_t *str, const uc8_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_assign_ucv8(us8_t *str, ucv8_t from);
UEXPORT size_t us8_assign_ucv8_e(us8_t *str, ucv8_t from, bool *error);
UEXPORT size_t us8_assign_uv8(us8_t *str, uv8_t from);
UEXPORT size_t us8_assign_uv8_e(us8_t *str, uv8_t from, bool *error);
UEXPORT size_t us8_assign_us8(us8_t *str, const us8_t *from);
UEXPORT size_t us8_assign_us8_e(us8_t *str, const us8_t *from, bool *error);

UEXPORT size_t us8_assign_bytes(us8_t *str, const void *from, uencoding_t encoding);
UEXPORT size_t us8_assign_bytes_e(us8_t *str, const void *from, uencoding_t encoding, bool *error);
UEXPORT size_t us8_assign_bytesn(us8_t *str, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT size_t us8_assign_bytesn_e(us8_t *str, const void *from, size_t from_size, uencoding_t encoding, bool *error);
UEXPORT size_t us8_assign_uz32le(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_assign_uz32le_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_assign_uz32len(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz32len_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_assign_uz16le(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_assign_uz16le_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_assign_uz16len(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz16len_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_assign_uz32be(us8_t *str, const uc32_t *from);
UEXPORT size_t us8_assign_uz32be_e(us8_t *str, const uc32_t *from, bool *error);
UEXPORT size_t us8_assign_uz32ben(us8_t *str, const uc32_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz32ben_e(us8_t *str, const uc32_t *from, size_t from_len, bool *error);
UEXPORT size_t us8_assign_uz16be(us8_t *str, const uc16_t *from);
UEXPORT size_t us8_assign_uz16be_e(us8_t *str, const uc16_t *from, bool *error);
UEXPORT size_t us8_assign_uz16ben(us8_t *str, const uc16_t *from, size_t from_len);
UEXPORT size_t us8_assign_uz16ben_e(us8_t *str, const uc16_t *from, size_t from_len, bool *error);

UEXPORT size_t us8_assign_fmt_uz8(us8_t *str, const uc8_t *from, ...);
UEXPORT size_t us8_assign_fmt_uz8_e(us8_t *str, const uc8_t *from, bool *error, ...);
UEXPORT size_t us8_assign_fmt_uz8_v(us8_t *str, const uc8_t *from, va_list *args);
UEXPORT size_t us8_assign_fmt_uz8_v_e(us8_t *str, const uc8_t *from, va_list *args, bool *error);
UEXPORT size_t us8_assign_fmt_uz8n(us8_t *str, const uc8_t *from, size_t from_len, ...);
UEXPORT size_t us8_assign_fmt_uz8n_e(us8_t *str, const uc8_t *from, size_t from_len, bool *error, ...);
UEXPORT size_t us8_assign_fmt_uz8n_v(us8_t *str, const uc8_t *from, size_t from_len, va_list *args);
UEXPORT size_t us8_assign_fmt_uz8n_v_e(us8_t *str, const uc8_t *from, size_t from_len, va_list *args, bool *error);
UEXPORT size_t us8_assign_fmt_ucv8(us8_t *str, ucv8_t from, ...);
UEXPORT size_t us8_assign_fmt_ucv8_e(us8_t *str, ucv8_t from, bool *error, ...);
UEXPORT size_t us8_assign_fmt_ucv8_v(us8_t *str, ucv8_t from, va_list *args);
UEXPORT size_t us8_assign_fmt_ucv8_v_e(us8_t *str, ucv8_t from, va_list *args, bool *error);
UEXPORT size_t us8_assign_fmt_uv8(us8_t *str, uv8_t from, ...);
UEXPORT size_t us8_assign_fmt_uv8_e(us8_t *str, uv8_t from, bool *error, ...);
UEXPORT size_t us8_assign_fmt_uv8_v(us8_t *str, uv8_t from, va_list *args);
UEXPORT size_t us8_assign_fmt_uv8_v_e(us8_t *str, uv8_t from, va_list *args, bool *error);
UEXPORT size_t us8_assign_fmt_us8(us8_t *str, const us8_t *from, ...);
UEXPORT size_t us8_assign_fmt_us8_e(us8_t *str, const us8_t *from, bool *error, ...);
UEXPORT size_t us8_assign_fmt_us8_v(us8_t *str, const us8_t *from, va_list *args);
UEXPORT size_t us8_assign_fmt_us8_v_e(us8_t *str, const us8_t *from, va_list *args, bool *error);

UEXPORT size_t us8_assign_float(us8_t *str, double from);
UEXPORT size_t us8_assign_float_e(us8_t *str, double from, bool *error);
UEXPORT size_t us8_assign_float_fmt(us8_t *str, double from, const struct ufmt8_float_output *fmt);
UEXPORT size_t us8_assign_float_fmt_e(us8_t *str, double from, const struct ufmt8_float_output *fmt, bool *error);

UEXPORT size_t us8_assign_int(us8_t *str, intmax_t from);
UEXPORT size_t us8_assign_int_e(us8_t *str, intmax_t from, bool *error);
UEXPORT size_t us8_assign_int_fmt(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t us8_assign_int_fmt_e(us8_t *str, intmax_t from, const struct ufmt8_int_output *fmt, bool *error);
UEXPORT size_t us8_assign_uint(us8_t *str, uintmax_t from);
UEXPORT size_t us8_assign_uint_e(us8_t *str, uintmax_t from, bool *error);
UEXPORT size_t us8_assign_uint_fmt(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt);
UEXPORT size_t us8_assign_uint_fmt_e(us8_t *str, uintmax_t from, const struct ufmt8_int_output *fmt, bool *error);

UEXPORT size_t us8_assign_bool(us8_t *str, bool from);
UEXPORT size_t us8_assign_bool_e(us8_t *str, bool from, bool *error);
UEXPORT size_t us8_assign_case_bool(us8_t *str, ucase_t ca, bool from);
UEXPORT size_t us8_assign_case_bool_e(us8_t *str, ucase_t ca, bool from, bool *error);
UEXPORT size_t us8_assign_lower_bool(us8_t *str, bool from);
UEXPORT size_t us8_assign_lower_bool_e(us8_t *str, bool from, bool *error);
UEXPORT size_t us8_assign_upper_bool(us8_t *str, bool from);
UEXPORT size_t us8_assign_upper_bool_e(us8_t *str, bool from, bool *error);

// Iteration

// - Begin

UEXPORT const uc32_t *us32_cbegin(const us32_t *str);
UEXPORT const uc16_t *us16_cbegin(const us16_t *str);
UEXPORT const uc8_t *us8_cbegin(const us8_t *str);

UEXPORT uc32_t *us32_begin(us32_t *str);
UEXPORT uc16_t *us16_begin(us16_t *str);
UEXPORT uc8_t *us8_begin(us8_t *str);

// - Offset

UEXPORT const uc32_t *us32_coffset(const us32_t *str, size_t offset);
UEXPORT const uc16_t *us16_coffset(const us16_t *str, size_t offset);
UEXPORT const uc8_t *us8_coffset(const us8_t *str, size_t offset);

UEXPORT uc32_t *us32_offset(us32_t *str, size_t offset);
UEXPORT uc16_t *us16_offset(us16_t *str, size_t offset);
UEXPORT uc8_t *us8_offset(us8_t *str, size_t offset);

// - End

UEXPORT const uc32_t *us32_cend(const us32_t *str);
UEXPORT const uc16_t *us16_cend(const us16_t *str);
UEXPORT const uc8_t *us8_cend(const us8_t *str);

UEXPORT uc32_t *us32_end(us32_t *str);
UEXPORT uc16_t *us16_end(us16_t *str);
UEXPORT uc8_t *us8_end(us8_t *str);

// Empty

UEXPORT bool us32_empty(const us32_t *str);
UEXPORT bool us16_empty(const us16_t *str);
UEXPORT bool us8_empty(const us8_t *str);

// At

UEXPORT uc32_t us32_at(const us32_t *str, size_t at);
UEXPORT uc16_t us16_at(const us16_t *str, size_t at);
UEXPORT uc8_t us8_at(const us8_t *str, size_t at);

// Chars

UEXPORT const uc32_t *us32_cchars(const us32_t *str);
UEXPORT uc32_t *us32_chars(us32_t *str);

UEXPORT const uc16_t *us16_cchars(const us16_t *str);
UEXPORT uc16_t *us16_chars(us16_t *str);

UEXPORT const uc8_t *us8_cchars(const us8_t *str);
UEXPORT uc8_t *us8_chars(us8_t *str);

// Valid

UEXPORT bool us32_valid(const us32_t *str);
UEXPORT bool us16_valid(const us16_t *str);
UEXPORT bool us8_valid(const us8_t *str);

#endif