#ifndef USTR_CHAR_H
#define USTR_CHAR_H

#include <stdbool.h>
#include <stddef.h>

#include "type/fmt/case.h"
#include "type/fmt/radix.h"
#include "type/attr.h"
#include "type/char.h"
#include "type/encoding.h"
#include "util/export.h"

// Creation

// - Conversion

#define uc32_from_imm(from)                 \
    _Generic((from),                        \
        default:        uc32_from_uc32_imm, \
        const uc16_t *: uc32_from_uc16_imm, \
        uc16_t *:       uc32_from_uc16_imm, \
        const uc8_t *:  uc32_from_uc8_imm,  \
        uc8_t *:        uc32_from_uc8_imm   \
    )((from))

#define uc32_from_le_imm(from)                \
    _Generic((from),                          \
        default:        uc32_from_uc32le_imm, \
        const uc16_t *: uc32_from_uc16le_imm, \
        uc16_t *:       uc32_from_uc16le_imm, \
        const uc8_t *:  uc32_from_uc8_imm,    \
        uc8_t *:        uc32_from_uc8_imm     \
    )((from))

#define uc32_from_be_imm(from)                \
    _Generic((from),                          \
        default:        uc32_from_uc32be_imm, \
        const uc16_t *: uc32_from_uc16be_imm, \
        uc16_t *:       uc32_from_uc16be_imm, \
        const uc8_t *:  uc32_from_uc8_imm,    \
        uc8_t *:        uc32_from_uc8_imm     \
    )((from))

UEXPORT uc32_t uc32_from_bytes_imm(const void *from, uencoding_t encoding);
UEXPORT uc32_t uc32_from_uc32_imm(uc32_t from);
UEXPORT uc32_t uc32_from_uc16_imm(const uc16_t *from);
UEXPORT uc32_t uc32_from_uc8_imm(const uc8_t *from);
UEXPORT uc32_t uc32_from_uc32le_imm(uc32_t from);
UEXPORT uc32_t uc32_from_uc16le_imm(const uc16_t *from);
UEXPORT uc32_t uc32_from_uc32be_imm(uc32_t from);
UEXPORT uc32_t uc32_from_uc16be_imm(const uc16_t *from);

#define uc32le_from_imm(from)                 \
    _Generic((from),                          \
        default:        uc32le_from_uc32_imm, \
        const uc16_t *: uc32le_from_uc16_imm, \
        uc16_t *:       uc32le_from_uc16_imm, \
        const uc8_t *:  uc32le_from_uc8_imm,  \
        uc8_t *:        uc32le_from_uc8_imm   \
    )((from))

#define uc32le_from_le_imm(from)                \
    _Generic((from),                            \
        default:        uc32le_from_uc32le_imm, \
        const uc16_t *: uc32le_from_uc16le_imm, \
        uc16_t *:       uc32le_from_uc16le_imm, \
        const uc8_t *:  uc32le_from_uc8_imm,    \
        uc8_t *:        uc32le_from_uc8_imm     \
    )((from))

#define uc32le_from_be_imm(from)                \
    _Generic((from),                            \
        default:        uc32le_from_uc32be_imm, \
        const uc16_t *: uc32le_from_uc16be_imm, \
        uc16_t *:       uc32le_from_uc16be_imm, \
        const uc8_t *:  uc32le_from_uc8_imm,    \
        uc8_t *:        uc32le_from_uc8_imm     \
    )((from))

UEXPORT uc32_t uc32le_from_bytes_imm(const void *from, uencoding_t encoding);
UEXPORT uc32_t uc32le_from_uc32_imm(uc32_t from);
UEXPORT uc32_t uc32le_from_uc16_imm(const uc16_t *from);
UEXPORT uc32_t uc32le_from_uc8_imm(const uc8_t *from);
UEXPORT uc32_t uc32le_from_uc32le_imm(uc32_t from);
UEXPORT uc32_t uc32le_from_uc16le_imm(const uc16_t *from);
UEXPORT uc32_t uc32le_from_uc32be_imm(uc32_t from);
UEXPORT uc32_t uc32le_from_uc16be_imm(const uc16_t *from);

#define uc32be_from_imm(from)                 \
    _Generic((from),                          \
        default:        uc32be_from_uc32_imm, \
        const uc16_t *: uc32be_from_uc16_imm, \
        uc16_t *:       uc32be_from_uc16_imm, \
        const uc8_t *:  uc32be_from_uc8_imm,  \
        uc8_t *:        uc32be_from_uc8_imm   \
    )((from))

#define uc32be_from_le_imm(from)                \
    _Generic((from),                            \
        default:        uc32be_from_uc32le_imm, \
        const uc16_t *: uc32be_from_uc16le_imm, \
        uc16_t *:       uc32be_from_uc16le_imm, \
        const uc8_t *:  uc32be_from_uc8_imm,    \
        uc8_t *:        uc32be_from_uc8_imm     \
    )((from))

#define uc32be_from_be_imm(from)                \
    _Generic((from),                            \
        default:        uc32be_from_uc32be_imm, \
        const uc16_t *: uc32be_from_uc16be_imm, \
        uc16_t *:       uc32be_from_uc16be_imm, \
        const uc8_t *:  uc32be_from_uc8_imm,    \
        uc8_t *:        uc32be_from_uc8_imm     \
    )((from))

UEXPORT uc32_t uc32be_from_bytes_imm(const void *from, uencoding_t encoding);
UEXPORT uc32_t uc32be_from_uc32_imm(uc32_t from);
UEXPORT uc32_t uc32be_from_uc16_imm(const uc16_t *from);
UEXPORT uc32_t uc32be_from_uc8_imm(const uc8_t *from);
UEXPORT uc32_t uc32be_from_uc32le_imm(uc32_t from);
UEXPORT uc32_t uc32be_from_uc16le_imm(const uc16_t *from);
UEXPORT uc32_t uc32be_from_uc32be_imm(uc32_t from);
UEXPORT uc32_t uc32be_from_uc16be_imm(const uc16_t *from);

#define uc32_from(to, from)             \
    _Generic((from)                     \
        const uc32_t *: uc32_from_uc32, \
        uc32_t *:       uc32_from_uc32, \
        const uc16_t *: uc32_from_uc16, \
        uc16_t *:       uc32_from_uc16, \
        const uc8_t *:  uc32_from_uc8,  \
        uc8_t *:        uc32_from_uc8   \
    )((to), (from))

#define uc32_from_le(to, from)            \
    _Generic((from)                       \
        const uc32_t *: uc32_from_uc32le, \
        uc32_t *:       uc32_from_uc32le, \
        const uc16_t *: uc32_from_uc16le, \
        uc16_t *:       uc32_from_uc16le, \
        const uc8_t  *: uc32_from_uc8,    \
        uc8_t *:        uc32_from_uc8     \
    )((to), (from))

#define uc32_from_be(to, from)            \
    _Generic((from)                       \
        const uc32_t *: uc32_from_uc32be, \
        uc32_t *:       uc32_from_uc32be, \
        const uc16_t *: uc32_from_uc16be, \
        uc16_t *:       uc32_from_uc16be, \
        const uc8_t  *: uc32_from_uc8,    \
        uc8_t *:        uc32_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc32_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc32_from_uc32(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32_from_uc16(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT unsigned uc32_from_uc8(UNULLABLE UOUT uc32_t *to, const uc8_t *from);
UEXPORT unsigned uc32_from_uc32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32_from_uc16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT unsigned uc32_from_uc32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32_from_uc16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from);

#define uc32_from_n(to, from, from_len)  \
    _Generic((from)                      \
        const uc32_t *: uc32_from_uc32n, \
        uc32_t *:       uc32_from_uc32n, \
        const uc16_t *: uc32_from_uc16n, \
        uc16_t *:       uc32_from_uc16n, \
        const uc8_t *:  uc32_from_uc8n,  \
        uc8_t *:        uc32_from_uc8n   \
    )((to), (from), (from_len))

#define uc32_from_len(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc32_from_uc32len, \
        uc32_t *:       uc32_from_uc32len, \
        const uc16_t *: uc32_from_uc16len, \
        uc16_t *:       uc32_from_uc16len, \
        const uc8_t *:  uc32_from_uc8n,    \
        uc8_t *:        uc32_from_uc8n     \
    )((to), (from), (from_len))

#define uc32_from_ben(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc32_from_uc32ben, \
        uc32_t *:       uc32_from_uc32ben, \
        const uc16_t *: uc32_from_uc16ben, \
        uc16_t *:       uc32_from_uc16ben, \
        const uc8_t *:  uc32_from_uc8n,    \
        uc8_t *:        uc32_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc32_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc32_from_uc32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32_from_uc16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc32_from_uc8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc32_from_uc32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32_from_uc16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc32_from_uc32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32_from_uc16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);

#define uc32le_from(to, from)             \
    _Generic((from)                       \
        const uc32_t *: uc32le_from_uc32, \
        uc32_t *:       uc32le_from_uc32, \
        const uc16_t *: uc32le_from_uc16, \
        uc16_t *:       uc32le_from_uc16, \
        const uc8_t *:  uc32le_from_uc8,  \
        uc8_t *:        uc32le_from_uc8   \
    )((to), (from))

#define uc32le_from_le(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc32le_from_uc32le, \
        uc32_t *:       uc32le_from_uc32le, \
        const uc16_t *: uc32le_from_uc16le, \
        uc16_t *:       uc32le_from_uc16le, \
        const uc8_t *:  uc32le_from_uc8,    \
        uc8_t *:        uc32le_from_uc8     \
    )((to), (from))

#define uc32le_from_be(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc32le_from_uc32be, \
        uc32_t *:       uc32le_from_uc32be, \
        const uc16_t *: uc32le_from_uc16be, \
        uc16_t *:       uc32le_from_uc16be, \
        const uc8_t *:  uc32le_from_uc8,    \
        uc8_t *:        uc32le_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc32le_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc32le_from_uc32(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32le_from_uc16(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT unsigned uc32le_from_uc8(UNULLABLE UOUT uc32_t *to, const uc8_t *from);
UEXPORT unsigned uc32le_from_uc32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32le_from_uc16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT unsigned uc32le_from_uc32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32le_from_uc16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from);

#define uc32le_from_n(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc32le_from_uc32n, \
        uc32_t *:       uc32le_from_uc32n, \
        const uc16_t *: uc32le_from_uc16n, \
        uc16_t *:       uc32le_from_uc16n, \
        const uc8_t *:  uc32le_from_uc8n,  \
        uc8_t *:        uc32le_from_uc8n   \
    )((to), (from), (from_len))

#define uc32le_from_len(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc32le_from_uc32len, \
        uc32_t *:       uc32le_from_uc32len, \
        const uc16_t *: uc32le_from_uc16len, \
        uc16_t *:       uc32le_from_uc16len, \
        const uc8_t *:  uc32le_from_uc8n,    \
        uc8_t *:        uc32le_from_uc8n     \
    )((to), (from), (from_len))

#define uc32le_from_ben(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc32le_from_uc32ben, \
        uc32_t *:       uc32le_from_uc32ben, \
        const uc16_t *: uc32le_from_uc16ben, \
        uc16_t *:       uc32le_from_uc16ben, \
        const uc8_t *:  uc32le_from_uc8n,    \
        uc8_t *:        uc32le_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc32le_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc32le_from_uc32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32le_from_uc16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc32le_from_uc8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc32le_from_uc32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32le_from_uc16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc32le_from_uc32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32le_from_uc16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);

#define uc32be_from(to, from)             \
    _Generic((from)                       \
        const uc32_t *: uc32be_from_uc32, \
        uc32_t *:       uc32be_from_uc32, \
        const uc16_t *: uc32be_from_uc16, \
        uc16_t *:       uc32be_from_uc16, \
        const uc8_t *:  uc32be_from_uc8,  \
        uc8_t *:        uc32be_from_uc8   \
    )((to), (from))

#define uc32be_from_le(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc32be_from_uc32le, \
        uc32_t *:       uc32be_from_uc32le, \
        const uc16_t *: uc32be_from_uc16le, \
        uc16_t *:       uc32be_from_uc16le, \
        const uc8_t *:  uc32be_from_uc8,    \
        uc8_t *:        uc32be_from_uc8     \
    )((to), (from))

#define uc32be_from_be(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc32be_from_uc32be, \
        uc32_t *:       uc32be_from_uc32be, \
        const uc16_t *: uc32be_from_uc16be, \
        uc16_t *:       uc32be_from_uc16be, \
        const uc8_t *:  uc32be_from_uc8,    \
        uc8_t *:        uc32be_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc32be_from_bytes(UNULLABLE UOUT uc32_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc32be_from_uc32(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32be_from_uc16(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT unsigned uc32be_from_uc8(UNULLABLE UOUT uc32_t *to, const uc8_t *from);
UEXPORT unsigned uc32be_from_uc32le(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32be_from_uc16le(UNULLABLE UOUT uc32_t *to, const uc16_t *from);
UEXPORT unsigned uc32be_from_uc32be(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32be_from_uc16be(UNULLABLE UOUT uc32_t *to, const uc16_t *from);

#define uc32be_from_n(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc32be_from_uc32n, \
        uc32_t *:       uc32be_from_uc32n, \
        const uc16_t *: uc32be_from_uc16n, \
        uc16_t *:       uc32be_from_uc16n, \
        const uc8_t *:  uc32be_from_uc8n,  \
        uc8_t *:        uc32be_from_uc8n   \
    )((to), (from), (from_len))

#define uc32be_from_len(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc32be_from_uc32len, \
        uc32_t *:       uc32be_from_uc32len, \
        const uc16_t *: uc32be_from_uc16len, \
        uc16_t *:       uc32be_from_uc16len, \
        const uc8_t *:  uc32be_from_uc8n,    \
        uc8_t *:        uc32be_from_uc8n     \
    )((to), (from), (from_len))

#define uc32be_from_ben(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc32be_from_uc32ben, \
        uc32_t *:       uc32be_from_uc32ben, \
        const uc16_t *: uc32be_from_uc16ben, \
        uc16_t *:       uc32be_from_uc16ben, \
        const uc8_t *:  uc32be_from_uc8n,    \
        uc8_t *:        uc32be_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc32be_from_bytesn(UNULLABLE UOUT uc32_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc32be_from_uc32n(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32be_from_uc16n(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc32be_from_uc8n(UNULLABLE UOUT uc32_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc32be_from_uc32len(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32be_from_uc16len(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc32be_from_uc32ben(UNULLABLE UOUT uc32_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc32be_from_uc16ben(UNULLABLE UOUT uc32_t *to, const uc16_t *from, size_t from_len);


UEXPORT unsigned uc16_from_uc32_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);
UEXPORT unsigned uc16_from_uc32le_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);
UEXPORT unsigned uc16_from_uc32be_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);

UEXPORT unsigned uc16le_from_uc32_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);
UEXPORT unsigned uc16le_from_uc32le_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);
UEXPORT unsigned uc16le_from_uc32be_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);

UEXPORT unsigned uc16be_from_uc32_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);
UEXPORT unsigned uc16be_from_uc32le_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);
UEXPORT unsigned uc16be_from_uc32be_imm(UNULLABLE UOUT uc16_t *to, uc32_t from);

#define uc16_from(to, from)             \
    _Generic((from)                     \
        const uc32_t *: uc16_from_uc32, \
        uc32_t *:       uc16_from_uc32, \
        const uc16_t *: uc16_from_uc16, \
        uc16_t *:       uc16_from_uc16, \
        const uc8_t *:  uc16_from_uc8,  \
        uc8_t *:        uc16_from_uc8   \
    )((to), (from))

#define uc16_from_le(to, from)            \
    _Generic((from)                       \
        const uc32_t *: uc16_from_uc32le, \
        uc32_t *:       uc16_from_uc32le, \
        const uc16_t *: uc16_from_uc16le, \
        uc16_t *:       uc16_from_uc16le, \
        const uc8_t *:  uc16_from_uc8,    \
        uc8_t *:        uc16_from_uc8     \
    )((to), (from))

#define uc16_from_be(to, from)            \
    _Generic((from)                       \
        const uc32_t *: uc16_from_uc32be, \
        uc32_t *:       uc16_from_uc32be, \
        const uc16_t *: uc16_from_uc16be, \
        uc16_t *:       uc16_from_uc16be, \
        const uc8_t *:  uc16_from_uc8,    \
        uc8_t *:        uc16_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc16_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc16_from_uc32(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16_from_uc16(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16_from_uc8(UNULLABLE UOUT uc16_t *to, const uc8_t *from);
UEXPORT unsigned uc16_from_uc32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16_from_uc16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16_from_uc32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16_from_uc16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from);

#define uc16_from_n(to, from, from_len)  \
    _Generic((from)                      \
        const uc32_t *: uc16_from_uc32n, \
        uc32_t *:       uc16_from_uc32n, \
        const uc16_t *: uc16_from_uc16n, \
        uc16_t *:       uc16_from_uc16n, \
        const uc8_t *:  uc16_from_uc8n,  \
        uc8_t *:        uc16_from_uc8n   \
    )((to), (from), (from_len))

#define uc16_from_len(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc16_from_uc32len, \
        uc32_t *:       uc16_from_uc32len, \
        const uc16_t *: uc16_from_uc16len, \
        uc16_t *:       uc16_from_uc16len, \
        const uc8_t *:  uc16_from_uc8n,    \
        uc8_t *:        uc16_from_uc8n     \
    )((to), (from), (from_len))

#define uc16_from_ben(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc16_from_uc32ben, \
        uc32_t *:       uc16_from_uc32ben, \
        const uc16_t *: uc16_from_uc16ben, \
        uc16_t *:       uc16_from_uc16ben, \
        const uc8_t *:  uc16_from_uc8n,    \
        uc8_t *:        uc16_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc16_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc16_from_uc32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16_from_uc16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc16_from_uc8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc16_from_uc32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16_from_uc16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc16_from_uc32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16_from_uc16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);

#define uc16le_from(to, from)             \
    _Generic((from)                       \
        const uc32_t *: uc16le_from_uc32, \
        uc32_t *:       uc16le_from_uc32, \
        const uc16_t *: uc16le_from_uc16, \
        uc16_t *:       uc16le_from_uc16, \
        const uc8_t *:  uc16le_from_uc8,  \
        uc8_t *:        uc16le_from_uc8   \
    )((to), (from))

#define uc16le_from_le(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc16le_from_uc32le, \
        uc32_t *:       uc16le_from_uc32le, \
        const uc16_t *: uc16le_from_uc16le, \
        uc16_t *:       uc16le_from_uc16le, \
        const uc8_t *:  uc16le_from_uc8,    \
        uc8_t *:        uc16le_from_uc8     \
    )((to), (from))

#define uc16le_from_be(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc16le_from_uc32be, \
        uc32_t *:       uc16le_from_uc32be, \
        const uc16_t *: uc16le_from_uc16be, \
        uc16_t *:       uc16le_from_uc16be, \
        const uc8_t *:  uc16le_from_uc8,    \
        uc8_t *:        uc16le_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc16le_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc16le_from_uc32(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16le_from_uc16(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16le_from_uc8(UNULLABLE UOUT uc16_t *to, const uc8_t *from);
UEXPORT unsigned uc16le_from_uc32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16le_from_uc16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16le_from_uc32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16le_from_uc16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from);

#define uc16le_from_n(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc16le_from_uc32n, \
        uc32_t *:       uc16le_from_uc32n, \
        const uc16_t *: uc16le_from_uc16n, \
        uc16_t *:       uc16le_from_uc16n, \
        const uc8_t *:  uc16le_from_uc8n,  \
        uc8_t *:        uc16le_from_uc8n   \
    )((to), (from), (from_len))

#define uc16le_from_len(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc16le_from_uc32len, \
        uc32_t *:       uc16le_from_uc32len, \
        const uc16_t *: uc16le_from_uc16len, \
        uc16_t *:       uc16le_from_uc16len, \
        const uc8_t *:  uc16le_from_uc8n,    \
        uc8_t *:        uc16le_from_uc8n     \
    )((to), (from), (from_len))

#define uc16le_from_ben(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc16le_from_uc32ben, \
        uc32_t *:       uc16le_from_uc32ben, \
        const uc16_t *: uc16le_from_uc16ben, \
        uc16_t *:       uc16le_from_uc16ben, \
        const uc8_t *:  uc16le_from_uc8n,    \
        uc8_t *:        uc16le_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc16le_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc16le_from_uc32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16le_from_uc16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc16le_from_uc8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc16le_from_uc32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16le_from_uc16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc16le_from_uc32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16le_from_uc16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);

#define uc16be_from(to, from)             \
    _Generic((from)                       \
        const uc32_t *: uc16be_from_uc32, \
        uc32_t *:       uc16be_from_uc32, \
        const uc16_t *: uc16be_from_uc16, \
        uc16_t *:       uc16be_from_uc16, \
        const uc8_t *:  uc16be_from_uc8,  \
        uc8_t *:        uc16be_from_uc8   \
    )((to), (from))

#define uc16be_from_le(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc16be_from_uc32le, \
        uc32_t *:       uc16be_from_uc32le, \
        const uc16_t *: uc16be_from_uc16le, \
        uc16_t *:       uc16be_from_uc16le, \
        const uc8_t *:  uc16be_from_uc8,    \
        uc8_t *:        uc16be_from_uc8     \
    )((to), (from))

#define uc16be_from_be(to, from)            \
    _Generic((from)                         \
        const uc32_t *: uc16be_from_uc32be, \
        uc32_t *:       uc16be_from_uc32be, \
        const uc16_t *: uc16be_from_uc16be, \
        uc16_t *:       uc16be_from_uc16be, \
        const uc8_t *:  uc16be_from_uc8,    \
        uc8_t *:        uc16be_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc16be_from_bytes(UNULLABLE UOUT uc16_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc16be_from_uc32(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16be_from_uc16(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16be_from_uc8(UNULLABLE UOUT uc16_t *to, const uc8_t *from);
UEXPORT unsigned uc16be_from_uc32le(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16be_from_uc16le(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16be_from_uc32be(UNULLABLE UOUT uc16_t *to, const uc32_t *from);
UEXPORT unsigned uc16be_from_uc16be(UNULLABLE UOUT uc16_t *to, const uc16_t *from);

#define uc16be_from_n(to, from, from_len)  \
    _Generic((from)                        \
        const uc32_t *: uc16be_from_uc32n, \
        uc32_t *:       uc16be_from_uc32n, \
        const uc16_t *: uc16be_from_uc16n, \
        uc16_t *:       uc16be_from_uc16n, \
        const uc8_t *:  uc16be_from_uc8n,  \
        uc8_t *:        uc16be_from_uc8n   \
    )((to), (from), (from_len))

#define uc16be_from_len(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc16be_from_uc32len, \
        uc32_t *:       uc16be_from_uc32len, \
        const uc16_t *: uc16be_from_uc16len, \
        uc16_t *:       uc16be_from_uc16len, \
        const uc8_t *:  uc16be_from_uc8n,    \
        uc8_t *:        uc16be_from_uc8n     \
    )((to), (from), (from_len))

#define uc16be_from_ben(to, from, from_len)  \
    _Generic((from)                          \
        const uc32_t *: uc16be_from_uc32ben, \
        uc32_t *:       uc16be_from_uc32ben, \
        const uc16_t *: uc16be_from_uc16ben, \
        uc16_t *:       uc16be_from_uc16ben, \
        const uc8_t *:  uc16be_from_uc8n,    \
        uc8_t *:        uc16be_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc16be_from_bytesn(UNULLABLE UOUT uc16_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc16be_from_uc32n(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16be_from_uc16n(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc16be_from_uc8n(UNULLABLE UOUT uc16_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc16be_from_uc32len(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16be_from_uc16len(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc16be_from_uc32ben(UNULLABLE UOUT uc16_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc16be_from_uc16ben(UNULLABLE UOUT uc16_t *to, const uc16_t *from, size_t from_len);


UEXPORT unsigned uc8_from_uc32_imm(UNULLABLE uc8_t *to, uc32_t from);
UEXPORT unsigned uc8_from_uc32le_imm(UNULLABLE uc8_t *to, uc32_t from);
UEXPORT unsigned uc8_from_uc32be_imm(UNULLABLE uc8_t *to, uc32_t from);

#define uc8_from(to, from)             \
    _Generic((from)                    \
        const uc32_t *: uc8_from_uc32, \
        uc32_t *:       uc8_from_uc32, \
        const uc16_t *: uc8_from_uc16, \
        uc16_t *:       uc8_from_uc16, \
        const uc8_t *:  uc8_from_uc8,  \
        uc8_t *:        uc8_from_uc8   \
    )((to), (from))

#define uc8_from_le(to, from)            \
    _Generic((from)                      \
        const uc32_t *: uc8_from_uc32le, \
        uc32_t *:       uc8_from_uc32le, \
        const uc16_t *: uc8_from_uc16le, \
        uc16_t *:       uc8_from_uc16le, \
        const uc8_t *:  uc8_from_uc8,    \
        uc8_t *:        uc8_from_uc8     \
    )((to), (from))

#define uc8_from_be(to, from)            \
    _Generic((from)                      \
        const uc32_t *: uc8_from_uc32be, \
        uc32_t *:       uc8_from_uc32be, \
        const uc16_t *: uc8_from_uc16be, \
        uc16_t *:       uc8_from_uc16be, \
        const uc8_t *:  uc8_from_uc8,    \
        uc8_t *:        uc8_from_uc8     \
    )((to), (from))

UEXPORT unsigned uc8_from_bytes(UNULLABLE UOUT uc8_t *to, const void *from, uencoding_t encoding);
UEXPORT unsigned uc8_from_uc32(UNULLABLE UOUT uc8_t *to, const uc32_t *from);
UEXPORT unsigned uc8_from_uc16(UNULLABLE UOUT uc8_t *to, const uc16_t *from);
UEXPORT unsigned uc8_from_uc8(UNULLABLE UOUT uc8_t *to, const uc8_t *from);
UEXPORT unsigned uc8_from_uc32le(UNULLABLE UOUT uc8_t *to, const uc32_t *from);
UEXPORT unsigned uc8_from_uc16le(UNULLABLE UOUT uc8_t *to, const uc16_t *from);
UEXPORT unsigned uc8_from_uc32be(UNULLABLE UOUT uc8_t *to, const uc32_t *from);
UEXPORT unsigned uc8_from_uc16be(UNULLABLE UOUT uc8_t *to, const uc16_t *from);

#define uc8_from_n(to, from, from_len)  \
    _Generic((from)                     \
        const uc32_t *: uc8_from_uc32n, \
        uc32_t *:       uc8_from_uc32n, \
        const uc16_t *: uc8_from_uc16n, \
        uc16_t *:       uc8_from_uc16n, \
        const uc8_t *:  uc8_from_uc8n,  \
        uc8_t *:        uc8_from_uc8n   \
    )((to), (from), (from_len))

#define uc8_from_len(to, from, from_len)  \
    _Generic((from)                       \
        const uc32_t *: uc8_from_uc32len, \
        uc32_t *:       uc8_from_uc32len, \
        const uc16_t *: uc8_from_uc16len, \
        uc16_t *:       uc8_from_uc16len, \
        const uc8_t *:  uc8_from_uc8n,    \
        uc8_t *:        uc8_from_uc8n     \
    )((to), (from), (from_len))

#define uc8_from_ben(to, from, from_len)  \
    _Generic((from)                       \
        const uc32_t *: uc8_from_uc32ben, \
        uc32_t *:       uc8_from_uc32ben, \
        const uc16_t *: uc8_from_uc16ben, \
        uc16_t *:       uc8_from_uc16ben, \
        const uc8_t *:  uc8_from_uc8n,    \
        uc8_t *:        uc8_from_uc8n     \
    )((to), (from), (from_len))

UEXPORT unsigned uc8_from_bytesn(UNULLABLE UOUT uc8_t *to, const void *from, size_t from_size, uencoding_t encoding);
UEXPORT unsigned uc8_from_uc32n(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc8_from_uc16n(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc8_from_uc8n(UNULLABLE UOUT uc8_t *to, const uc8_t *from, size_t from_len);
UEXPORT unsigned uc8_from_uc32len(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc8_from_uc16len(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len);
UEXPORT unsigned uc8_from_uc32ben(UNULLABLE UOUT uc8_t *to, const uc32_t *from, size_t from_len);
UEXPORT unsigned uc8_from_uc16ben(UNULLABLE UOUT uc8_t *to, const uc16_t *from, size_t from_len);

// - Digit from val

UEXPORT uc32_t uc32_bin_from_val(unsigned val);
UEXPORT uc32_t uc32_oct_from_val(unsigned val);
UEXPORT uc32_t uc32_dec_from_val(unsigned val);
UEXPORT uc32_t uc32_hex_from_val(unsigned val);
UEXPORT uc32_t uc32_case_hex_from_val(ucase_t ca, unsigned val);
UEXPORT uc32_t uc32_lower_hex_from_val(unsigned val);
UEXPORT uc32_t uc32_upper_hex_from_val(unsigned val);
UEXPORT uc32_t uc32_radix_from_val(uradix_t radix, unsigned val);
UEXPORT uc32_t uc32_case_radix_from_val(ucase_t ca, uradix_t radix, unsigned val);
UEXPORT uc32_t uc32_lower_radix_from_val(uradix_t radix, unsigned val);
UEXPORT uc32_t uc32_upper_radix_from_val(uradix_t radix, unsigned val);

UEXPORT uc16_t uc16_bin_from_val(unsigned val);
UEXPORT uc16_t uc16_oct_from_val(unsigned val);
UEXPORT uc16_t uc16_dec_from_val(unsigned val);
UEXPORT uc16_t uc16_hex_from_val(unsigned val);
UEXPORT uc16_t uc16_case_hex_from_val(ucase_t ca, unsigned val);
UEXPORT uc16_t uc16_lower_hex_from_val(unsigned val);
UEXPORT uc16_t uc16_upper_hex_from_val(unsigned val);
UEXPORT uc16_t uc16_radix_from_val(uradix_t radix, unsigned val);
UEXPORT uc16_t uc16_case_radix_from_val(ucase_t ca, uradix_t radix, unsigned val);
UEXPORT uc16_t uc16_lower_radix_from_val(uradix_t radix, unsigned val);
UEXPORT uc16_t uc16_upper_radix_from_val(uradix_t radix, unsigned val);

UEXPORT uc8_t uc8_bin_from_val(unsigned val);
UEXPORT uc8_t uc8_oct_from_val(unsigned val);
UEXPORT uc8_t uc8_dec_from_val(unsigned val);
UEXPORT uc8_t uc8_hex_from_val(unsigned val);
UEXPORT uc8_t uc8_case_hex_from_val(ucase_t ca, unsigned val);
UEXPORT uc8_t uc8_lower_hex_from_val(unsigned val);
UEXPORT uc8_t uc8_upper_hex_from_val(unsigned val);
UEXPORT uc8_t uc8_radix_from_val(uradix_t radix, unsigned val);
UEXPORT uc8_t uc8_case_radix_from_val(ucase_t ca, uradix_t radix, unsigned val);
UEXPORT uc8_t uc8_lower_radix_from_val(uradix_t radix, unsigned val);
UEXPORT uc8_t uc8_upper_radix_from_val(uradix_t radix, unsigned val);

// Encode

UEXPORT unsigned uc32_to_bytes_imm(UNULLABLE UOUT void *to, uencoding_t encoding, uc32_t from);
UEXPORT unsigned uc32le_to_bytes_imm(UNULLABLE UOUT void *to, uencoding_t encoding, uc32_t from);
UEXPORT unsigned uc32be_to_bytes_imm(UNULLABLE UOUT void *to, uencoding_t encoding, uc32_t from);

UEXPORT unsigned uc32_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from);
UEXPORT unsigned uc32le_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from);
UEXPORT unsigned uc32be_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc32_t *from);


UEXPORT unsigned uc16_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from);
UEXPORT unsigned uc16le_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from);
UEXPORT unsigned uc16be_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc16_t *from);


UEXPORT unsigned uc8_to_bytes(UNULLABLE UOUT void *to, uencoding_t encoding, const uc8_t *from);

// Digit val

UEXPORT int uc32_bin_val(uc32_t c);
UEXPORT int uc32_oct_val(uc32_t c);
UEXPORT int uc32_dec_val(uc32_t c);
UEXPORT int uc32_hex_val(uc32_t c);
UEXPORT int uc32_case_hex_val(uc32_t c, ucase_t ca);
UEXPORT int uc32_lower_hex_val(uc32_t c);
UEXPORT int uc32_upper_hex_val(uc32_t c);
UEXPORT int uc32_radix_val(uc32_t c, uradix_t radix);
UEXPORT int uc32_case_radix_val(uc32_t c, ucase_t ca, uradix_t radix);
UEXPORT int uc32_lower_radix_val(uc32_t c, uradix_t radix);
UEXPORT int uc32_upper_radix_val(uc32_t c, uradix_t radix);

UEXPORT int uc16_bin_val(uc16_t c);
UEXPORT int uc16_oct_val(uc16_t c);
UEXPORT int uc16_dec_val(uc16_t c);
UEXPORT int uc16_hex_val(uc16_t c);
UEXPORT int uc16_case_hex_val(uc16_t c, ucase_t ca);
UEXPORT int uc16_lower_hex_val(uc16_t c);
UEXPORT int uc16_upper_hex_val(uc16_t c);
UEXPORT int uc16_radix_val(uc16_t c, uradix_t radix);
UEXPORT int uc16_case_radix_val(uc16_t c, ucase_t ca, uradix_t radix);
UEXPORT int uc16_lower_radix_val(uc16_t c, uradix_t radix);
UEXPORT int uc16_upper_radix_val(uc16_t c, uradix_t radix);

UEXPORT int uc8_bin_val(uc8_t c);
UEXPORT int uc8_oct_val(uc8_t c);
UEXPORT int uc8_dec_val(uc8_t c);
UEXPORT int uc8_hex_val(uc8_t c);
UEXPORT int uc8_case_hex_val(uc8_t c, ucase_t ca);
UEXPORT int uc8_lower_hex_val(uc8_t c);
UEXPORT int uc8_upper_hex_val(uc8_t c);
UEXPORT int uc8_radix_val(uc8_t c, uradix_t radix);
UEXPORT int uc8_case_radix_val(uc8_t c, ucase_t ca, uradix_t radix);
UEXPORT int uc8_lower_radix_val(uc8_t c, uradix_t radix);
UEXPORT int uc8_upper_radix_val(uc8_t c, uradix_t radix);

// Digit categories

UEXPORT bool uc32_bin(uc32_t c);
UEXPORT bool uc32_oct(uc32_t c);
UEXPORT bool uc32_dec(uc32_t c);
UEXPORT bool uc32_hex(uc32_t c);
UEXPORT bool uc32_case_hex(uc32_t c, ucase_t ca);
UEXPORT bool uc32_lower_hex(uc32_t c);
UEXPORT bool uc32_upper_hex(uc32_t c);
UEXPORT bool uc32_radix(uc32_t c, uradix_t radix);
UEXPORT bool uc32_case_radix(uc32_t c, ucase_t ca, uradix_t radix);
UEXPORT bool uc32_lower_radix(uc32_t c, uradix_t radix);
UEXPORT bool uc32_upper_radix(uc32_t c, uradix_t radix);

UEXPORT bool uc16_bin(uc16_t c);
UEXPORT bool uc16_oct(uc16_t c);
UEXPORT bool uc16_dec(uc16_t c);
UEXPORT bool uc16_hex(uc16_t c);
UEXPORT bool uc16_case_hex(uc16_t c, ucase_t ca);
UEXPORT bool uc16_lower_hex(uc16_t c);
UEXPORT bool uc16_upper_hex(uc16_t c);
UEXPORT bool uc16_radix(uc16_t c, uradix_t radix);
UEXPORT bool uc16_case_radix(uc16_t c, ucase_t ca, uradix_t radix);
UEXPORT bool uc16_lower_radix(uc16_t c, uradix_t radix);
UEXPORT bool uc16_upper_radix(uc16_t c, uradix_t radix);

UEXPORT bool uc8_bin(uc8_t c);
UEXPORT bool uc8_oct(uc8_t c);
UEXPORT bool uc8_dec(uc8_t c);
UEXPORT bool uc8_hex(uc8_t c);
UEXPORT bool uc8_case_hex(uc8_t c, ucase_t ca);
UEXPORT bool uc8_lower_hex(uc8_t c);
UEXPORT bool uc8_upper_hex(uc8_t c);
UEXPORT bool uc8_radix(uc8_t c, uradix_t radix);
UEXPORT bool uc8_case_radix(uc8_t c, ucase_t ca, uradix_t radix);
UEXPORT bool uc8_lower_radix(uc8_t c, uradix_t radix);
UEXPORT bool uc8_upper_radix(uc8_t c, uradix_t radix);

// Case change

UEXPORT uc32_t uc32_to_case_imm(uc32_t c, ucase_t ca);
UEXPORT uc32_t uc32_to_lower_imm(uc32_t c);
UEXPORT uc32_t uc32_to_upper_imm(uc32_t c);

UEXPORT unsigned uc32_to_case(UNULLABLE UOUT uc32_t *to, const uc32_t *from, ucase_t ca);
UEXPORT unsigned uc32_to_lower(UNULLABLE UOUT uc32_t *to, const uc32_t *from);
UEXPORT unsigned uc32_to_upper(UNULLABLE UOUT uc32_t *to, const uc32_t *from);

UEXPORT unsigned uc16_to_case(UNULLABLE UOUT uc16_t *to, const uc16_t *from, ucase_t ca);
UEXPORT unsigned uc16_to_lower(UNULLABLE UOUT uc16_t *to, const uc16_t *from);
UEXPORT unsigned uc16_to_upper(UNULLABLE UOUT uc16_t *to, const uc16_t *from);

UEXPORT unsigned uc8_to_case(UNULLABLE UOUT uc8_t *to, const uc8_t *from, ucase_t ca);
UEXPORT unsigned uc8_to_lower(UNULLABLE UOUT uc8_t *to, const uc8_t *from);
UEXPORT unsigned uc8_to_upper(UNULLABLE UOUT uc8_t *to, const uc8_t *from);

// Case change length

UEXPORT unsigned uc8_case_len(const uc8_t *c, ucase_t ca);
UEXPORT unsigned uc8_lower_len(const uc8_t *c);
UEXPORT unsigned uc8_upper_len(const uc8_t *c);

// Letter categories

UEXPORT bool uc32_letter_imm(uc32_t c);
UEXPORT bool uc32_case_imm(uc32_t c, ucase_t ca);
UEXPORT bool uc32_lower_imm(uc32_t c);
UEXPORT bool uc32_upper_imm(uc32_t c);
UEXPORT bool uc32_title_imm(uc32_t c);
UEXPORT bool uc32_mod_imm(uc32_t c);
UEXPORT bool uc32_oletter_imm(uc32_t c);

UEXPORT bool uc32_letter(const uc32_t *c);
UEXPORT bool uc32_case(const uc32_t *c, ucase_t ca);
UEXPORT bool uc32_lower(const uc32_t *c);
UEXPORT bool uc32_upper(const uc32_t *c);
UEXPORT bool uc32_title(const uc32_t *c);
UEXPORT bool uc32_mod(const uc32_t *c);
UEXPORT bool uc32_oletter(const uc32_t *c);

UEXPORT bool uc16_letter(const uc16_t *c);
UEXPORT bool uc16_case(const uc16_t *c, ucase_t ca);
UEXPORT bool uc16_lower(const uc16_t *c);
UEXPORT bool uc16_upper(const uc16_t *c);
UEXPORT bool uc16_title(const uc16_t *c);
UEXPORT bool uc16_mod(const uc16_t *c);
UEXPORT bool uc16_oletter(const uc16_t *c);

UEXPORT bool uc8_letter(const uc8_t *c);
UEXPORT bool uc8_case(const uc8_t *c, ucase_t ca);
UEXPORT bool uc8_lower(const uc8_t *c);
UEXPORT bool uc8_upper(const uc8_t *c);
UEXPORT bool uc8_title(const uc8_t *c);
UEXPORT bool uc8_mod(const uc8_t *c);
UEXPORT bool uc8_oletter(const uc8_t *c);

// Other categories

UEXPORT bool uc32_number_imm(uc32_t c);
UEXPORT bool uc32_cntrl_imm(uc32_t c);
UEXPORT bool uc32_space_imm(uc32_t c);
UEXPORT bool uc32_wspace_imm(uc32_t c);
UEXPORT bool uc32_punct_imm(uc32_t c);
UEXPORT bool uc32_priv_imm(uc32_t c);

UEXPORT bool uc32_number(const uc32_t *c);
UEXPORT bool uc32_cntrl(const uc32_t *c);
UEXPORT bool uc32_space(const uc32_t *c);
UEXPORT bool uc32_wspace(const uc32_t *c);
UEXPORT bool uc32_punct(const uc32_t *c);
UEXPORT bool uc32_priv(const uc32_t *c);

UEXPORT bool uc16_number(const uc16_t *c);
UEXPORT bool uc16_cntrl(const uc16_t *c);
UEXPORT bool uc16_space(const uc16_t *c);
UEXPORT bool uc16_wspace(const uc16_t *c);
UEXPORT bool uc16_punct(const uc16_t *c);
UEXPORT bool uc16_priv(const uc16_t *c);
UEXPORT bool uc16_srgt(uc16_t c);
UEXPORT bool uc16_lsrgt(uc16_t c);
UEXPORT bool uc16_hsrgt(uc16_t c);

UEXPORT bool uc8_number(const uc8_t *c);
UEXPORT bool uc8_cntrl(const uc8_t *c);
UEXPORT bool uc8_space(const uc8_t *c);
UEXPORT bool uc8_wspace(const uc8_t *c);
UEXPORT bool uc8_punct(const uc8_t *c);
UEXPORT bool uc8_priv(const uc8_t *c);
UEXPORT unsigned uc8_lead(uc8_t c);
UEXPORT bool uc8_trail(uc8_t c);

// Length

UEXPORT unsigned uc32_len(uc32_t c);
UEXPORT unsigned uc32_len_n(uc32_t c, unsigned n);
UEXPORT unsigned uc32_len_32(uc32_t c);
UEXPORT unsigned uc32_len_16(uc32_t c);
UEXPORT unsigned uc32_len_8(uc32_t c);

UEXPORT unsigned uc32le_len(uc32_t c);
UEXPORT unsigned uc32le_len_n(uc32_t c, unsigned n);
UEXPORT unsigned uc32le_len_32(uc32_t c);
UEXPORT unsigned uc32le_len_16(uc32_t c);
UEXPORT unsigned uc32le_len_8(uc32_t c);

UEXPORT unsigned uc32be_len(uc32_t c);
UEXPORT unsigned uc32be_len_n(uc32_t c, unsigned n);
UEXPORT unsigned uc32be_len_32(uc32_t c);
UEXPORT unsigned uc32be_len_16(uc32_t c);
UEXPORT unsigned uc32be_len_8(uc32_t c);


UEXPORT unsigned uc16_len(uc16_t c);
UEXPORT unsigned uc16_len_n(uc16_t c, unsigned n);
UEXPORT unsigned uc16_len_32(uc16_t c);
UEXPORT unsigned uc16_len_16(uc16_t c);
UEXPORT unsigned uc16_len_8(uc16_t c);

UEXPORT unsigned uc16le_len(uc16_t c);
UEXPORT unsigned uc16le_len_n(uc16_t c, unsigned n);
UEXPORT unsigned uc16le_len_32(uc16_t c);
UEXPORT unsigned uc16le_len_16(uc16_t c);
UEXPORT unsigned uc16le_len_8(uc16_t c);

UEXPORT unsigned uc16be_len(uc16_t c);
UEXPORT unsigned uc16be_len_n(uc16_t c, unsigned n);
UEXPORT unsigned uc16be_len_32(uc16_t c);
UEXPORT unsigned uc16be_len_16(uc16_t c);
UEXPORT unsigned uc16be_len_8(uc16_t c);


UEXPORT unsigned uc8_len(uc8_t c);
UEXPORT unsigned uc8_len_n(uc8_t c, unsigned n);
UEXPORT unsigned uc8_len_32(uc8_t c);
UEXPORT unsigned uc8_len_16(uc8_t c);
UEXPORT unsigned uc8_len_8(uc8_t c);

// Valid

UEXPORT bool uc32_valid_imm(uc32_t c);

UEXPORT unsigned uc32_valid(const uc32_t *c);
UEXPORT unsigned uc16_valid(const uc16_t *c);
UEXPORT unsigned uc8_valid(const uc8_t *c);

#endif