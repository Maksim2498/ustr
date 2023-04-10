#include "fmt.h"

#include <assert.h>

#include <ustr/char.h>
#include <ustr/config.h>
#include <ustr/cstr.h>
#include <ustr/cview.h>
#include <ustr/str.h>
#include <ustr/view.h>

#include "bool.h"
#include "case.h"
#include "char.h"
#include "float.h"
#include "int.h"
#include "plus.h"
#include "radix.h"
#include "str.h"
#include "type.h"

#define UFMT_INT_GROUP_OUTPUT_EXPAND_X(fmt, X)                  \
    assert(ufmt_int_group_output_valid(fmt));                   \
                                                                \
    struct ufmt##X##_int_output res = UFMT##X##_INT_OUTPUT_DEC; \
                                                                \
    res.digit_case        = fmt->digit_case;                    \
    res.plus              = fmt->plus;                          \
    res.radix             = fmt->radix;                         \
    res.radix_prefix_case = fmt->radix_prefix_case;             \
    res.show_radix_prefix = fmt->show_radix_prefix;             \
                                                                \
    return res

struct ufmt32_int_output ufmt_int_group_output_expand_32(const struct ufmt_int_group_output *fmt) {
    UFMT_INT_GROUP_OUTPUT_EXPAND_X(fmt, 32);
}

struct ufmt16_int_output ufmt_int_group_output_expand_16(const struct ufmt_int_group_output *fmt) {
    UFMT_INT_GROUP_OUTPUT_EXPAND_X(fmt, 16);
}

struct ufmt8_int_output ufmt_int_group_output_expand_8(const struct ufmt_int_group_output *fmt) {
    UFMT_INT_GROUP_OUTPUT_EXPAND_X(fmt, 8);
}

bool ufmt_int_group_output_valid(const struct ufmt_int_group_output *fmt) {
    if (!fmt)
        return false;

    if (!uradix_valid(fmt->radix))
        return false;

    if (fmt->show_radix_prefix && uradix_has_prefix(fmt->radix) && !ucase_valid(fmt->radix_prefix_case))
        return false;

    return uplus_valid(fmt->plus);
}

#define UFMT_FLOAT_GROUP_OUTPUT_EXPAND_X(fmt, X)                \
    assert(ufmt_float_group_output_valid(fmt));                 \
                                                                \
    struct ufmt##X##_float_output res = UFMT##X##_FLOAT_OUTPUT; \
                                                                \
    res.exp_case   = fmt->exp_case;                             \
    res.plus       = fmt->plus;                                 \
    res.scientific = fmt->scientific;                           \
                                                                \
    return res

struct ufmt32_float_output ufmt_float_group_output_expand_32(const struct ufmt_float_group_output *fmt) {
    UFMT_FLOAT_GROUP_OUTPUT_EXPAND_X(fmt, 32);
}

struct ufmt16_float_output ufmt_float_group_output_expand_16(const struct ufmt_float_group_output *fmt) {
    UFMT_FLOAT_GROUP_OUTPUT_EXPAND_X(fmt, 16);
}

struct ufmt8_float_output ufmt_float_group_output_expand_8(const struct ufmt_float_group_output *fmt) {
    UFMT_FLOAT_GROUP_OUTPUT_EXPAND_X(fmt, 8);
}

bool ufmt_float_group_output_valid(const struct ufmt_float_group_output *fmt) {
	return fmt
        && ucase_valid(fmt->exp_case)
        && uplus_valid(fmt->plus);
}

bool ufmt_bool_group_output_valid(const struct ufmt_bool_group_output *fmt) {
    return fmt && ucase_valid_output(fmt->char_case);
}

struct ufmt_output ufmt_output_from_uz32(const uc32_t *from) {
    return ufmt_output_from_uz32n(from, uz32_len(from));
}

static const struct ufmt_automata {
    struct ufmt_output             fmt;
    struct ufmt_int_group_output   ifmt;
    struct ufmt_float_group_output ffmt;
    struct ufmt_bool_group_output  bfmt;
    unsigned                       state;
} UFMT_AUTOMATA = {
    .fmt   = UFMT_OUTPUT_CTC,
    .ifmt  = UFMT_INT_GROUP_OUTPUT_CTC,
    .ffmt  = UFMT_FLOAT_GROUP_OUTPUT_CTC,
    .bfmt  = UFMT_BOOL_GROUP_OUTPUT_CTC,
    .state = 0
};

static size_t ufmt_automata_plus(struct ufmt_automata *a, uc8_t c) {
    switch (c) {
        case ' ':
            a->ifmt.plus = UPLUS_SPACE;
            a->ffmt.plus = UPLUS_SPACE;
            return 1;

        case '+':
            a->ifmt.plus = UPLUS_SIGN;
            a->ffmt.plus = UPLUS_SIGN;
            return 1;

        default:
            return 0;
    }
}

#define UFMT_AUTOMATA_PLUS_X(a, from, from_len, i) \
    if (i >= from_len)                             \
        return 0;                                  \
                                                   \
    return i + ufmt_automata_plus(a, from[i])

static size_t ufmt_automata_plus_32(struct ufmt_automata *a, const uc32_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PLUS_X(a, from, from_len, i);
}

static size_t ufmt_automata_plus_16(struct ufmt_automata *a, const uc16_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PLUS_X(a, from, from_len, i);
}

static size_t ufmt_automata_plus_8(struct ufmt_automata *a, const uc8_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PLUS_X(a, from, from_len, i);
}

static size_t ufmt_automata_prefix(struct ufmt_automata *a, uc8_t c) {
    switch (c) {
        case 'x':
            a->ifmt.show_radix_prefix = true;
            return 1;

        case 'X':
            a->ifmt.show_radix_prefix = true;
            a->ifmt.radix_prefix_case = UCASE_UPPER;
            return 1;
        
        default:
            return 0;
    }
}

#define UFMT_AUTOMATA_PREFIX_X(a, from, from_len, i) \
    if (i >= from_len)                               \
        return 0;                                    \
                                                     \
    return i + ufmt_automata_prefix(a, from[i])


static size_t ufmt_automata_prefix_32(struct ufmt_automata *a, const uc32_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PREFIX_X(a, from, from_len, i);
}

static size_t ufmt_automata_prefix_16(struct ufmt_automata *a, const uc16_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PREFIX_X(a, from, from_len, i);
}

static size_t ufmt_automata_prefix_8(struct ufmt_automata *a, const uc8_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PREFIX_X(a, from, from_len, i);
}

#define UFMT_AUTOMATA_PRECISION_X(a, from, from_len, i, X) \
    if (i >= from_len)                                     \
        return i;                                          \
                                                           \
    if ('*' == from[i]) {                                  \
        a->fmt.use_precision = true;                       \
        a->fmt.arg_precision = true;                       \
        return i + 1;                                      \
    }                                                      \
                                                           \
    if (!uc##X##_dec(from[i]))                             \
        return i;                                          \
                                                           \
    a->fmt.use_precision = true;                           \
                                                           \
    for (; i < from_len; ++i) {                            \
        int val = uc##X##_dec_val(from[i]);                \
                                                           \
        if (val < 0)                                       \
            break;                                         \
                                                           \
        a->fmt.precision *= 10;                            \
        a->fmt.precision += val;                           \
    }                                                      \
                                                           \
    return i

static size_t ufmt_automata_precision_32(struct ufmt_automata *a, const uc32_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PRECISION_X(a, from, from_len, i, 32);
}

static size_t ufmt_automata_precision_16(struct ufmt_automata *a, const uc16_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PRECISION_X(a, from, from_len, i, 16);
}

static size_t ufmt_automata_precision_8(struct ufmt_automata *a, const uc8_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_PRECISION_X(a, from, from_len, i, 8);
}

static bool ufmt_automata_fmt_step(struct ufmt_automata *a, uc8_t c) {
    switch (a->state) {
        case 0:
            switch (c) {
                case 's':
                    a->fmt.type = UTYPE_SINT;
                    a->fmt.len  = 1;
                    a->state    = 6;
                    return false;

                case 'l':
                    a->fmt.type = UTYPE_LINT;
                    a->fmt.len  = 1;
                    a->state    = 5;
                    return false;

                case 'i':
                    a->fmt.type = UTYPE_INT;
                    a->fmt.len  = 1;
                    a->state    = 9;
                    return false;

                case 'u':
                    a->fmt.type = UTYPE_UINT;
                    a->fmt.len  = 1;
                    a->state    = 7;
                    return false;

                case 'f':
                    a->fmt.type = UTYPE_FLOAT;
                    a->fmt.len  = 1;
                    a->state    = 4;
                    return false;

                case 'd':
                    a->fmt.type = UTYPE_DOUBLE;
                    a->fmt.len  = 1;
                    a->state    = 3;
                    return false;

                case 'c':
                    a->fmt.type = UTYPE_CHAR;
                    a->fmt.len  = 1;
                    a->state    = 53;
                    return false;

                case 'z':
                    a->fmt.type = UTYPE_CSTR;
                    a->fmt.len  = 1;
                    a->state    = 57;
                    return false;

                case 'B':
                    a->fmt.type       = UTYPE_BOOL;
                    a->fmt.len        = 1;
                    a->bfmt.char_case = UCASE_UPPER;
                    return true;

                case 'b':
                    a->fmt.type   = UTYPE_BOOL;
                    a->fmt.len    = 1;
                    a->ifmt.radix = 2;
                    a->state      = 3;
                    return false;

                case 'o':
                    a->ifmt.radix = 8;
                    a->state      = 3;
                    return false;

                case 'h':
                    a->ifmt.radix      = 16;
                    a->ifmt.digit_case = UCASE_LOWER;
                    a->state           = 3;
                    return false;

                case 'H':
                    a->ifmt.radix = 16;
                    a->state      = 3;
                    return false;

                case 'm':
                    a->fmt.type = UTYPE_MAX;
                    a->fmt.len  = 1;
                    return true;

                case 'p':
                    a->fmt.type = UTYPE_PTR;
                    a->fmt.len  = 1;
                    return true;

                case 'Z':
                    a->fmt.type = UTYPE_SIZE;
                    a->fmt.len  = 1;
                    return true;

                case 'D':
                    a->fmt.type = UTYPE_PTRDIFF;
                    a->fmt.len  = 1;
                    return true;

                case 'e':
                    a->fmt.type = UTYPE_FLOAT;
                    a->fmt.len  = 1;
                    a->state    = 1;
                    return false;

                case 'E':
                    a->fmt.type      = UTYPE_FLOAT;
                    a->fmt.len       = 1;
                    a->ffmt.exp_case = UCASE_UPPER;
                    a->state         = 1;
                    return false;

                case 'v':
                    a->state = 62;
                    return false;

                case '!':
                    a->fmt.type = UTYPE_CUSTOM;
                    a->fmt.len  = 1;
                    return true;

                default:
                    return true;
            }

        // [eE]
        // float

        case 1:
            switch (c) {
                case 'f':
                    a->fmt.len = 2;
                    return true;

                case 'd':
                    a->fmt.type = UTYPE_DOUBLE;
                    a->fmt.len  = 2;
                    return true;

                case 'l':
                    a->state = 2;
                    return false;

                default:
                    return true;
            }

        // [eE]l
        // float

        case 2:
            switch (c) {
                case 'd':
                    a->fmt.type = UTYPE_LDOUBLE;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]
        // bool if b, double if d

        case 3:
            switch (c) {
                case 'i':
                    a->fmt.type = UTYPE_INT;
                    a->fmt.len  = 2;
                    a->state    = 10;
                    return false;

                case 'l':
                    a->fmt.type = UTYPE_LINT;
                    a->fmt.len  = 2;
                    a->state    = 11;
                    return false;

                case 'u':
                    a->fmt.type = UTYPE_UINT;
                    a->fmt.len  = 2;
                    a->state    = 8;
                    return false;

                case 'f':
                    a->state = 29;
                    return false;

                case 'm':
                    a->fmt.type = UTYPE_MAX;
                    a->fmt.len  = 2;
                    return true;

                case 'p':
                    a->fmt.type = UTYPE_PTR;
                    a->fmt.len  = 2;
                    return true;

                case 'Z':
                    a->fmt.type = UTYPE_SIZE;
                    a->fmt.len  = 2;
                    return true;

                case 's':
                    a->fmt.type = UTYPE_SINT;
                    a->fmt.len  = 2;
                    a->state    = 56;
                    return false;

                case 'D':
                    a->fmt.type = UTYPE_PTRDIFF;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // f
        // float

        case 4:
            switch (c) {
                case '1':
                    a->state = 26;
                    return false;

                case '3':
                    a->state = 27;
                    return false;

                case '6':
                    a->state = 28;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_FAST8;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // l
        // lint

        case 5:
            switch (c) {
                case 'l':
                    a->fmt.type = UTYPE_LLINT;
                    a->fmt.len  = 2;
                    return true;

                case '1':
                    a->state = 41;
                    return false;

                case '3':
                    a->state = 42;
                    return false;

                case '6':
                    a->state = 43;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_LEAST8;
                    a->fmt.len  = 2;
                    return true;

                case 'd':
                    a->fmt.type = UTYPE_LDOUBLE;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // s
        // sint

        case 6:
            switch (c) {
                case '1':
                    a->state = 60;
                    return false;

                case '3':
                    a->state = 61;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_US8;
                    a->fmt.len  = 2;
                    return true;
                    
                case 'c':
                    a->fmt.type = UTYPE_SCHAR;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // u
        // uint

        case 7:
            switch (c) {
                case '8':
                    a->fmt.type = UTYPE_UINT8;
                    a->fmt.len  = 2;
                    return true;

                case '1':
                    a->state = 18;
                    return false;

                case '3':
                    a->state = 19;
                    return false;

                case '6':
                    a->state = 24;
                    return false;

                case 'c':
                    a->fmt.type = UTYPE_UCHAR;
                    a->fmt.len  = 2;
                    return false;

                case 'm':
                    a->fmt.type = UTYPE_UMAX;
                    a->fmt.len  = 2;
                    return true;

                case 'p':
                    a->fmt.type = UTYPE_UPTR;
                    a->fmt.len  = 2;
                    return true;

                case 'l':
                    a->fmt.type = UTYPE_ULINT;
                    a->fmt.len  = 2;
                    a->state    = 12;
                    return false;

                case 'f':
                    a->state = 37;
                    return false;

                case 's':
                    a->fmt.type = UTYPE_USINT;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // [bodhH]u
        // uint

        case 8:
            switch (c) {
                case '8':
                    a->fmt.type = UTYPE_UINT8;
                    a->fmt.len  = 3;
                    return false;

                case '1':
                    a->state = 20;
                    return false;

                case '3':
                    a->state = 21;
                    return false;

                case '6':
                    a->state = 25;
                    return false;

                case 'f':
                    a->state = 33;
                    return false;;

                case 'm':
                    a->fmt.type = UTYPE_UMAX;
                    a->fmt.len  = 3;
                    return true;

                case 'c':
                    a->fmt.type = UTYPE_UCHAR;
                    a->fmt.len  = 3;
                    return true;

                case 'p':
                    a->fmt.type = UTYPE_UPTR;
                    a->fmt.len  = 3;
                    return true;

                case 'l':
                    a->fmt.type = UTYPE_ULINT;
                    a->fmt.len  = 3;
                    a->state    = 13;
                    return false;
                    
                case 's':
                    a->fmt.type = UTYPE_USINT;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // i
        // int

        case 9:
            switch (c) {
                case '1':
                    a->state = 14;
                    return false;

                case '3':
                    a->state = 15;
                    return false;

                case '6':
                    a->state = 23;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_INT8;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // [bodhH]i
        // int

        case 10:
            switch (c) {
                case '1':
                    a->state = 16;
                    return false;

                case '3':
                    a->state = 17;
                    return false;

                case '6':
                    a->state = 22;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_INT8;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]l
        // lint

        case 11:
            switch (c) {
                case '1':
                    a->state = 44;
                    return false;

                case '3':
                    a->state = 45;
                    return false;

                case '6':
                    a->state = 46;
                    return false;
                    
                case '8':
                    a->fmt.type = UTYPE_LEAST8;
                    a->fmt.len  = 3;
                    return true;

                case 'l':
                    a->fmt.type = UTYPE_LLINT;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // ul
        // ulint

        case 12:
            switch (c) {
                case '1':
                    a->state = 47;
                    return false;

                case '3':
                    a->state = 48;
                    return false;

                case '6':
                    a->state = 49;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_ULEAST8;
                    a->fmt.len  = 3;
                    return true;

                case 'l':
                    a->fmt.type = UTYPE_ULLINT;
                    a->fmt.len  = 3;
                    
                default:
                    return true;
            }

        // [bodhH]ul
        // ulint

        case 13:
            switch (c) {
                case '1':
                    a->state = 50;
                    return false;

                case '3':
                    a->state = 51;
                    return false;

                case '6':
                    a->state = 52;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_ULEAST8;
                    a->fmt.len  = 4;
                    return true;

                case 'l':
                    a->fmt.type = UTYPE_ULLINT;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // i1
        // int

        case 14:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_INT16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // i3
        // int

        case 15:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_INT32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]i1
        // int

        case 16:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_INT16;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]i3
        // int

        case 17:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_INT32;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // u1
        // uint

        case 18:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UINT16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // u3
        // uint

        case 19:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UINT32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]u1
        // uint

        case 20:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UINT16;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]u3
        // uint

        case 21:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UINT32;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]i6
        // int

        case 22:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_INT64;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // i6
        // int

        case 23:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_INT64;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // u6
        // uint

        case 24:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_UINT64;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]u6
        // uint

        case 25:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_UINT64;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // f1
        // float

        case 26:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_FAST16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // f3
        // float

        case 27:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_FAST32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // f6
        // float

        case 28:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_FAST64;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]f
        // bool if b, double if d

        case 29:
            switch (c) {
                case '1':
                    a->state = 30;
                    return false;

                case '3':
                    a->state = 31;
                    return false;

                case '6':
                    a->state = 32;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_FAST8;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]f1
        // bool if b, double if d

        case 30:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_FAST16;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]f3
        // bool if b, double if d

        case 31:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_FAST32;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]f6
        // bool if b, double if d

        case 32:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_FAST64;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]uf
        // uint

        case 33:
            switch (c) {
                case '1':
                    a->state = 34;
                    return false;

                case '3':
                    a->state = 35;
                    return false;

                case '6':
                    a->state = 36;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_UFAST8;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]uf1
        // uint

        case 34:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UFAST16;
                    a->fmt.len  = 5;

                default:
                    return true;
            }

        // [bodhH]uf3
        // uint

        case 35:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UFAST32;
                    a->fmt.len  = 5;

                default:
                    return true;
            }

        // [bodhH]uf6
        // uint

        case 36:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_UFAST64;
                    a->fmt.len  = 5;

                default:
                    return true;
            }

        // uf
        // uint

        case 37:
            switch (c) {
                case '1':
                    a->state = 38;
                    return false;

                case '3':
                    a->state = 39;
                    return false;

                case '6':
                    a->state = 40;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_UFAST8;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // uf1
        // uint

        case 38:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UFAST16;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // uf3
        // uint

        case 39:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UFAST32;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // uf6
        // uint

        case 40:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_UFAST64;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // l1
        // long

        case 41:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_LEAST16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // l3
        // long

        case 42:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_LEAST32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // l6
        // long

        case 43:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_LEAST64;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]l1
        // lint

        case 44:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_LEAST16;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]l3
        // lint

        case 45:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_LEAST32;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // [bodhH]l6
        // lint

        case 46:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_LEAST64;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // ul1
        // ulint

        case 47:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_ULEAST16;
                    a->fmt.len  = 4;
                    
                default:
                    return true;
            }

        // ul3
        // ulint

        case 48:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_ULEAST32;
                    a->fmt.len  = 4;
                    
                default:
                    return true;
            }

        // ul6
        // ulint

        case 49:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_ULEAST64;
                    a->fmt.len  = 4;
                    
                default:
                    return true;
            }

        // [bodhH]ul1
        // ulint

        case 50:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_ULEAST16;
                    a->fmt.len  = 5;

                default:
                    return true;
            }

        // [bodhH]ul3
        // ulint

        case 51:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_ULEAST32;
                    a->fmt.len  = 5;

                default:
                    return true;
            }

        // [bodhH]ul6
        // ulint

        case 52:
            switch (c) {
                case '4':
                    a->fmt.type = UTYPE_ULEAST64;
                    a->fmt.len  = 5;

                default:
                    return true;
            }

        // c
        // char

        case 53:
            switch (c) {
                case 'v':
                    a->state = 65;
                    return false;

                case '1':
                    a->state = 54;
                    return false;

                case '3':
                    a->state = 55;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_UC8;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // c1
        // char

        case 54:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UC16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // c3
        // char

        case 55:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UC32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // [bodhH]s
        // sint

        case 56:
            switch (c) {
                case 'c':
                    a->fmt.type = UTYPE_SCHAR;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // z
        // cstr

        case 57:
            switch (c) {
                case '1':
                    a->state = 58;
                    return false;

                case '3':
                    a->state = 59;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_UZ8;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // z1
        // cstr

        case 58:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UZ16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // z3
        // cstr

        case 59:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UZ32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // s1
        // sint

        case 60:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_US16;
                    a->fmt.len  = 3;
                    
                default:
                    return true;
            }

        // s3
        // sint

        case 61:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_US32;
                    a->fmt.len  = 3;
                    
                default:
                    return true;
            }

        // v
        // <unknown>

        case 62:
            switch (c) {
                case '1':
                    a->state = 63;
                    return false;

                case '3':
                    a->state = 64;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_UV8;
                    a->fmt.len  = 2;

                default:
                    return true;
            }

        // v1
        // <unknown>

        case 63:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UV16;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // v3
        // <unknown>

        case 64:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UV32;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // cv
        // char

        case 65:
            switch (c) {
                case '1':
                    a->state = 66;
                    return false;

                case '3':
                    a->state = 67;
                    return false;

                case '8':
                    a->fmt.type = UTYPE_UCV8;
                    a->fmt.len  = 3;

                default:
                    return true;
            }

        // cv1
        // char

        case 66:
            switch (c) {
                case '6':
                    a->fmt.type = UTYPE_UCV16;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        // cv3
        // char

        case 67:
            switch (c) {
                case '2':
                    a->fmt.type = UTYPE_UCV32;
                    a->fmt.len  = 4;

                default:
                    return true;
            }

        default:
            assert(false);
            return true;
    }
}

#define UFMT_AUTOMATA_FMT_X(a, from, from_len, i) \
    for (; i < from_len; ++i)                     \
        if (ufmt_automata_fmt_step(a, from[i]))   \
            break

static void ufmt_automata_fmt_32(struct ufmt_automata *a, const uc32_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_FMT_X(a, from, from_len, i); 
}

static void ufmt_automata_fmt_16(struct ufmt_automata *a, const uc16_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_FMT_X(a, from, from_len, i); 
}

static void ufmt_automata_fmt_8(struct ufmt_automata *a, const uc8_t *from, size_t from_len, size_t i) {
    UFMT_AUTOMATA_FMT_X(a, from, from_len, i); 
}

static void ufmt_automata_collapse(struct ufmt_automata *a) {
    switch (utype_group(a->fmt.type)) {
        case UTGROUP_INT:
            a->fmt.i = a->ifmt;
            break;

        case UTGROUP_FLOAT:
            a->fmt.f = a->ffmt;
            break;

        case UTGROUP_BOOL:
            a->fmt.b = a->bfmt;
    }
}

static void ufmt_automata_count_prefix(struct ufmt_automata *a, size_t prefix_len) {
    if (UTYPE_UNKNOWN != a->fmt.type)
        a->fmt.len += prefix_len;
}

// Format string structure: <Precision> <Plus> <Prefix> <Format>
//              Decryption: <Integer>   <None> <None>   <See ustr/type/fmt/type/.h>
//                          '*'         ' '    'x'
//                                      '+'    'X'

#define UFMT_OUTPUT_FROM_UZXN(from, from_len, X)                   \
    assert(from);                                                  \
                                                                   \
    /* Initialize */                                               \
                                                                   \
    struct ufmt_automata automata   = UFMT_AUTOMATA;               \
    size_t               prefix_len = 0;                           \
    size_t               i          = 0;                           \
                                                                   \
    /* Parse prefix */                                             \
                                                                   \
    i = ufmt_automata_precision_##X(&automata, from, from_len, i); \
    i = ufmt_automata_plus_##X(&automata, from, from_len, i);      \
    i = ufmt_automata_prefix_##X(&automata, from, from_len, i);    \
                                                                   \
    prefix_len = i;                                                \
                                                                   \
    /* Parse format */                                             \
                                                                   \
    ufmt_automata_fmt_##X(&automata, from, from_len, i);           \
                                                                   \
    /* Prepare return value */                                     \
                                                                   \
    ufmt_automata_collapse(&automata);                             \
    ufmt_automata_count_prefix(&automata, prefix_len);             \
                                                                   \
    return automata.fmt

struct ufmt_output ufmt_output_from_uz32n(const uc32_t *from, size_t from_len) {
    UFMT_OUTPUT_FROM_UZXN(from, from_len, 32);
}

struct ufmt_output ufmt_output_from_ucv32(ucv32_t from) {
    return ufmt_output_from_uz32n(UCV32_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_us32(const us32_t *from) {
    return ufmt_output_from_uz32n(US32_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_uv32(uv32_t from) {
    return ufmt_output_from_uz32n(UV32_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_uz16(const uc16_t *from) {
    return ufmt_output_from_uz16n(from, uz16_len(from));
}

struct ufmt_output ufmt_output_from_uz16n(const uc16_t *from, size_t from_len) {
    UFMT_OUTPUT_FROM_UZXN(from, from_len, 16);
}

struct ufmt_output ufmt_output_from_ucv16(ucv16_t from) {
    return ufmt_output_from_uz16n(UCV16_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_us16(const us16_t *from) {
    return ufmt_output_from_uz16n(US16_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_uv16(uv16_t from) {
    return ufmt_output_from_uz16n(UV16_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_uz8(const uc8_t *from) {
    return ufmt_output_from_uz8n(from, uz8_len(from));
}

struct ufmt_output ufmt_output_from_uz8n(const uc8_t *from, size_t from_len) {
    UFMT_OUTPUT_FROM_UZXN(from, from_len, 8);
}

struct ufmt_output ufmt_output_from_ucv8(ucv8_t from) {
    return ufmt_output_from_uz8n(UCV8_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_us8(const us8_t *from) {
    return ufmt_output_from_uz8n(US8_CEXPAND(from));
}

struct ufmt_output ufmt_output_from_uv8(uv8_t from) {
    return ufmt_output_from_uz8n(UV8_CEXPAND(from));
}

#define UWRITE_FMT_T_X(fmt, write, write_arg, T, X)                      \
    va_list args;                                                        \
    va_start(args, write_arg);                                           \
    size_t len = uwrite_fmt_##T##_##X##_v(fmt, write, write_arg, &args); \
    va_end(args);                                                        \
    return len

#define UWRITE_FMT_UZXN_X(fmt, fmt_len, write, write_arg, X)                         \
    va_list args;                                                                    \
    va_start(args, write_arg);                                                       \
    size_t len = uwrite_fmt_uz##X##n_##X##_v(fmt, fmt_len, write, write_arg, &args); \
    va_end(args);                                                                    \
    return len

#define UWRITE_FMT_UZXN_X_V(fmt, fmt_len, write, write_arg, args, X)                                                    \
    assert(fmt && write && args);                                                                                       \
                                                                                                                        \
    size_t written = 0;                                                                                                 \
                                                                                                                        \
    for (size_t i = 0; i < fmt_len;) {                                                                                  \
        uc##X##_t c = fmt[i++];                                                                                         \
                                                                                                                        \
        /* Regular char */                                                                                              \
                                                                                                                        \
        if ('%' != c) {                                                                                                 \
            if (write(c, write_arg))                                                                                    \
                goto quit;                                                                                              \
                                                                                                                        \
            ++written;                                                                                                  \
                                                                                                                        \
            continue;                                                                                                   \
        }                                                                                                               \
                                                                                                                        \
        /* Parse format */                                                                                              \
                                                                                                                        \
        struct ufmt_output parsed_fmt = ufmt_output_from_uz##X##n(fmt + i, fmt_len - i);                                \
                                                                                                                        \
        /* Eval precision */                                                                                            \
                                                                                                                        \
        size_t precision;                                                                                               \
                                                                                                                        \
        if (parsed_fmt.use_precision)                                                                                   \
            precision = parsed_fmt.arg_precision ? va_arg(*args, unsigned)                                              \
                                                 : parsed_fmt.precision;                                                \
                                                                                                                        \
        /* Expand formats */                                                                                            \
                                                                                                                        \
        struct ufmt##X##_int_output   int_fmt;                                                                          \
        struct ufmt##X##_float_output float_fmt;                                                                        \
                                                                                                                        \
        switch (utype_group(parsed_fmt.type)) {                                                                         \
            case UTGROUP_INT:                                                                                           \
                int_fmt = ufmt_int_group_output_expand_##X(&parsed_fmt.i);                                              \
                break;                                                                                                  \
                                                                                                                        \
            case UTGROUP_FLOAT:                                                                                         \
                float_fmt = ufmt_float_group_output_expand_##X(&parsed_fmt.f);                                          \
        }                                                                                                               \
                                                                                                                        \
        /* Write type */                                                                                                \
                                                                                                                        \
        switch (parsed_fmt.type) {                                                                                      \
            case UTYPE_FLOAT: {                                                                                         \
                float val = va_arg(*args, double);                                                                      \
                written += uwrite_float_##X(val, &float_fmt, write, write_arg);                                         \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_DOUBLE: {                                                                                        \
                double val = va_arg(*args, double);                                                                     \
                written += uwrite_float_##X(val, &float_fmt, write, write_arg);                                         \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LDOUBLE: {                                                                                       \
                long double val = va_arg(*args, long double);                                                           \
                written += uwrite_float_##X(val, &float_fmt, write, write_arg);                                         \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_SINT: {                                                                                          \
                short val = va_arg(*args, int);                                                                         \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_USINT: {                                                                                         \
                unsigned short val = va_arg(*args, unsigned);                                                           \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_INT: {                                                                                           \
                int val = va_arg(*args, int);                                                                           \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UINT: {                                                                                          \
                unsigned val = va_arg(*args, unsigned);                                                                 \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LINT: {                                                                                          \
                long val = va_arg(*args, long);                                                                         \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_ULINT: {                                                                                         \
                unsigned long val = va_arg(*args, unsigned long);                                                       \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LLINT: {                                                                                         \
                long long val = va_arg(*args, long long);                                                               \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_ULLINT: {                                                                                        \
                unsigned long long val = va_arg(*args, unsigned long long);                                             \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_INT8: {                                                                                          \
                int8_t val = va_arg(*args, uarg_int8_t);                                                                \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UINT8: {                                                                                         \
                uint8_t val = va_arg(*args, uarg_uint8_t);                                                              \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_INT16: {                                                                                         \
                int16_t val = va_arg(*args, uarg_int16_t);                                                              \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UINT16: {                                                                                        \
                uint16_t val = va_arg(*args, uarg_uint16_t);                                                            \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_INT32: {                                                                                         \
                int32_t val = va_arg(*args, uarg_int32_t);                                                              \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UINT32: {                                                                                        \
                uint32_t val = va_arg(*args, uarg_uint32_t);                                                            \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_INT64: {                                                                                         \
                int64_t val = va_arg(*args, uarg_int64_t);                                                              \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UINT64: {                                                                                        \
                uint64_t val = va_arg(*args, uarg_uint64_t);                                                            \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_FAST8: {                                                                                         \
                int_fast8_t val = va_arg(*args, uarg_int_fast8_t);                                                      \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UFAST8: {                                                                                        \
                uint_fast8_t val = va_arg(*args, uarg_uint_fast8_t);                                                    \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_FAST16: {                                                                                        \
                int_fast16_t val = va_arg(*args, uarg_int_fast16_t);                                                    \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UFAST16: {                                                                                       \
                uint_fast16_t val = va_arg(*args, uarg_uint_fast16_t);                                                  \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_FAST32: {                                                                                        \
                int_fast32_t val = va_arg(*args, uarg_int_fast32_t);                                                    \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UFAST32: {                                                                                       \
                uint_fast32_t val = va_arg(*args, uarg_uint_fast32_t);                                                  \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_FAST64: {                                                                                        \
                int_fast64_t val = va_arg(*args, uarg_int_fast64_t);                                                    \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UFAST64: {                                                                                       \
                uint_fast64_t val = va_arg(*args, uarg_uint_fast64_t);                                                  \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LEAST8: {                                                                                        \
                int_least8_t val = va_arg(*args, uarg_int_least8_t);                                                    \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_ULEAST8: {                                                                                       \
                uint_least8_t val = va_arg(*args, uarg_uint_least8_t);                                                  \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LEAST16: {                                                                                       \
                int_least16_t val = va_arg(*args, uarg_int_least16_t);                                                  \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_ULEAST16: {                                                                                      \
                uint_least16_t val = va_arg(*args, uarg_uint_least16_t);                                                \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LEAST32: {                                                                                       \
                int_least32_t val = va_arg(*args, uarg_int_least32_t);                                                  \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_ULEAST32: {                                                                                      \
                uint_least32_t val = va_arg(*args, uarg_uint_least32_t);                                                \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_LEAST64: {                                                                                       \
                int_least64_t val = va_arg(*args, uarg_int_least64_t);                                                  \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_ULEAST64: {                                                                                      \
                uint_least64_t val = va_arg(*args, uarg_uint_least64_t);                                                \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_MAX: {                                                                                           \
                intmax_t val = va_arg(*args, intmax_t);                                                                 \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UMAX: {                                                                                          \
                uintmax_t val = va_arg(*args, uintmax_t);                                                               \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_PTR: {                                                                                           \
                intptr_t val = va_arg(*args, intptr_t);                                                                 \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UPTR: {                                                                                          \
                uintptr_t val = va_arg(*args, uintptr_t);                                                               \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_SIZE: {                                                                                          \
                size_t val = va_arg(*args, size_t);                                                                     \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_PTRDIFF: {                                                                                       \
                ptrdiff_t val = va_arg(*args, ptrdiff_t);                                                               \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_CHAR: {                                                                                          \
                char   val   = va_arg(*args, int);                                                                      \
                size_t count = parsed_fmt.use_precision ? precision : 1;                                                \
                written += uwrite_uc8_##X(val, count, write, write_arg);                                                \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_SCHAR: {                                                                                         \
                signed char val = va_arg(*args, int);                                                                   \
                written += uwrite_int_##X(val, &int_fmt, write, write_arg);                                             \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UCHAR: {                                                                                         \
                unsigned char val = va_arg(*args, unsigned);                                                            \
                written += uwrite_uint_##X(val, &int_fmt, write, write_arg);                                            \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_CSTR: {                                                                                          \
                const char *val = va_arg(*args, const char *);                                                          \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz8n_##X((const uc8_t *) val, precision, write, write_arg) \
                                                    : uwrite_uz8_##X((const uc8_t *) val, write, write_arg);            \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_BOOL: {                                                                                          \
                bool val = va_arg(*args, int);                                                                          \
                written += uwrite_bool_##X(val, parsed_fmt.b.char_case, write, write_arg);                              \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UC32: {                                                                                          \
                uc32_t val   = va_arg(*args, uarg_uc32_t);                                                              \
                size_t count = parsed_fmt.use_precision ? precision : 1;                                                \
                written += uwrite_uc32_##X(val, count, write, write_arg);                                               \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UC16: {                                                                                          \
                uc16_t val   = va_arg(*args, uarg_uc16_t);                                                              \
                size_t count = parsed_fmt.use_precision ? precision : 1;                                                \
                written += uwrite_uc16_##X(val, count, write, write_arg);                                               \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UC8: {                                                                                           \
                uc8_t val    = va_arg(*args, uarg_uc8_t);                                                               \
                size_t count = parsed_fmt.use_precision ? precision : 1;                                                \
                written += uwrite_uc8_##X(val, count, write, write_arg);                                                \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UZ32: {                                                                                          \
                const uc32_t *val = va_arg(*args, const uc32_t *);                                                      \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz32n_##X(val, precision, write, write_arg)                \
                                                    : uwrite_uz32_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UZ16: {                                                                                          \
                const uc16_t *val = va_arg(*args, const uc16_t *);                                                      \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz16n_##X(val, precision, write, write_arg)                \
                                                    : uwrite_uz16_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UZ8: {                                                                                           \
                const uc8_t *val = va_arg(*args, const uc8_t *);                                                        \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz8n_##X(val, precision, write, write_arg)                 \
                                                    : uwrite_uz8_##X(val, write, write_arg);                            \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_US32: {                                                                                          \
                const us32_t *val = va_arg(*args, const us32_t *);                                                      \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz32n_##X(us32_cchars(val), precision, write, write_arg)   \
                                                    : uwrite_us32_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_US16: {                                                                                          \
                const us16_t *val = va_arg(*args, const us16_t *);                                                      \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz16n_##X(us16_cchars(val), precision, write, write_arg)   \
                                                    : uwrite_us16_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_US8: {                                                                                           \
                const us8_t *val = va_arg(*args, const us8_t *);                                                        \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz8n_##X(us8_cchars(val), precision, write, write_arg)     \
                                                    : uwrite_us8_##X(val, write, write_arg);                            \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UV32: {                                                                                          \
                uv32_t val = va_arg(*args, uv32_t);                                                                     \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz32n_##X(uv32_cchars(val), precision, write, write_arg)   \
                                                    : uwrite_uv32_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UV16: {                                                                                          \
                uv16_t val = va_arg(*args, uv16_t);                                                                     \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz16n_##X(uv16_cchars(val), precision, write, write_arg)   \
                                                    : uwrite_uv16_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UV8: {                                                                                           \
                uv8_t val = va_arg(*args, uv8_t);                                                                       \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz8n_##X(uv8_cchars(val), precision, write, write_arg)     \
                                                    : uwrite_uv8_##X(val, write, write_arg);                            \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UCV32: {                                                                                         \
                ucv32_t val = va_arg(*args, ucv32_t);                                                                   \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz32n_##X(ucv32_cchars(val), precision, write, write_arg)  \
                                                    : uwrite_ucv32_##X(val, write, write_arg);                          \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UCV16: {                                                                                         \
                ucv16_t val = va_arg(*args, ucv16_t);                                                                   \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz16n_##X(ucv16_cchars(val), precision, write, write_arg)  \
                                                    : uwrite_ucv16_##X(val, write, write_arg);                          \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_UCV8: {                                                                                          \
                ucv8_t val = va_arg(*args, ucv8_t);                                                                     \
                                                                                                                        \
                written += parsed_fmt.use_precision ? uwrite_uz8n_##X(ucv8_cchars(val), precision, write, write_arg)    \
                                                    : uwrite_ucv8_##X(val, write, write_arg);                           \
                                                                                                                        \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            case UTYPE_CUSTOM: {                                                                                        \
                uwrite_custom_##X##_t val = va_arg(*args, uwrite_custom_##X##_t);                                       \
                written += val(write, write_arg, &parsed_fmt, args);                                                    \
                break;                                                                                                  \
            }                                                                                                           \
                                                                                                                        \
            default:                                                                                                    \
                assert(false);                                                                                          \
                                                                                                                        \
            case UTYPE_UNKNOWN:                                                                                         \
                if (write('%', write_arg))                                                                              \
                    goto quit;                                                                                          \
                                                                                                                        \
                ++written;                                                                                              \
        }                                                                                                               \
                                                                                                                        \
        i += parsed_fmt.len;                                                                                            \
    }                                                                                                                   \
                                                                                                                        \
quit:                                                                                                                   \
    return written

size_t uwrite_fmt_uz32_32(const uc32_t *fmt, uwrite_uc32_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, uz32, 32);
}

size_t uwrite_fmt_uz32_32_v(const uc32_t *fmt, uwrite_uc32_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz32n_32_v(fmt, uz32_len(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uz32n_32(const uc32_t *fmt, size_t fmt_len, uwrite_uc32_t write, void *write_arg, ...) {
    UWRITE_FMT_UZXN_X(fmt, fmt_len, write, write_arg, 32);
}

size_t uwrite_fmt_uz32n_32_v(const uc32_t *fmt, size_t fmt_len, uwrite_uc32_t write, void *write_arg, va_list *args) {
    UWRITE_FMT_UZXN_X_V(fmt, fmt_len, write, write_arg, args, 32);
}
 
size_t uwrite_fmt_ucv32_32(ucv32_t fmt, uwrite_uc32_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, ucv32, 32);
}

size_t uwrite_fmt_ucv32_32_v(ucv32_t fmt, uwrite_uc32_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz32n_32_v(UCV32_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_us32_32(const us32_t *fmt, uwrite_uc32_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, us32, 32);
}

size_t uwrite_fmt_us32_32_v(const us32_t *fmt, uwrite_uc32_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz32n_32_v(US32_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uv32_32(uv32_t fmt, uwrite_uc32_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, uv32, 32);
}

size_t uwrite_fmt_uv32_32_v(uv32_t fmt, uwrite_uc32_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz32n_32_v(UV32_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uz16_16(const uc16_t *fmt, uwrite_uc16_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, uz16, 16);
}

size_t uwrite_fmt_uz16_16_v(const uc16_t *fmt, uwrite_uc16_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz16n_16_v(fmt, uz16_len(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uz16n_16(const uc16_t *fmt, size_t fmt_len, uwrite_uc16_t write, void *write_arg, ...) {
    UWRITE_FMT_UZXN_X(fmt, fmt_len, write, write_arg, 16);
}

size_t uwrite_fmt_uz16n_16_v(const uc16_t *fmt, size_t fmt_len, uwrite_uc16_t write, void *write_arg, va_list *args) {
    UWRITE_FMT_UZXN_X_V(fmt, fmt_len, write, write_arg, args, 16);
}
 
size_t uwrite_fmt_ucv16_16(ucv16_t fmt, uwrite_uc16_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, ucv16, 16);
}

size_t uwrite_fmt_ucv16_16_v(ucv16_t fmt, uwrite_uc16_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz16n_16_v(UCV16_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_us16_16(const us16_t *fmt, uwrite_uc16_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, us16, 16);
}

size_t uwrite_fmt_us16_16_v(const us16_t *fmt, uwrite_uc16_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz16n_16_v(US16_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uv16_16(uv16_t fmt, uwrite_uc16_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, uv16, 16);
}

size_t uwrite_fmt_uv16_16_v(uv16_t fmt, uwrite_uc16_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz16n_16_v(UV16_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uz8_8(const uc8_t *fmt, uwrite_uc8_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, uz8, 8);
}

size_t uwrite_fmt_uz8_8_v(const uc8_t *fmt, uwrite_uc8_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz8n_8_v(fmt, uz8_len(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uz8n_8(const uc8_t *fmt, size_t fmt_len, uwrite_uc8_t write, void *write_arg, ...) {
    UWRITE_FMT_UZXN_X(fmt, fmt_len, write, write_arg, 8);
}

size_t uwrite_fmt_uz8n_8_v(const uc8_t *fmt, size_t fmt_len, uwrite_uc8_t write, void *write_arg, va_list *args) {
    UWRITE_FMT_UZXN_X_V(fmt, fmt_len, write, write_arg, args, 8);
}
 
size_t uwrite_fmt_ucv8_8(ucv8_t fmt, uwrite_uc8_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, ucv8, 8);
}

size_t uwrite_fmt_ucv8_8_v(ucv8_t fmt, uwrite_uc8_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz8n_8_v(UCV8_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_us8_8(const us8_t *fmt, uwrite_uc8_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, us8, 8);
}

size_t uwrite_fmt_us8_8_v(const us8_t *fmt, uwrite_uc8_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz8n_8_v(US8_CEXPAND(fmt), write, write_arg, args);
}
 
size_t uwrite_fmt_uv8_8(uv8_t fmt, uwrite_uc8_t write, void *write_arg, ...) {
    UWRITE_FMT_T_X(fmt, write, write_arg, uv8, 8);
}

size_t uwrite_fmt_uv8_8_v(uv8_t fmt, uwrite_uc8_t write, void *write_arg, va_list *args) {
	return uwrite_fmt_uz8n_8_v(UV8_CEXPAND(fmt), write, write_arg, args);
}
 
bool ufmt_output_valid(const struct ufmt_output *fmt) {
    if (!fmt)
        return false;

    if (!utype_valid(fmt->type))
        return false;

    switch (utype_group(fmt->type)) {
        case UTGROUP_INT:
            return ufmt_int_group_output_valid(&fmt->i);

        case UTGROUP_FLOAT:
            return ufmt_float_group_output_valid(&fmt->f);

        case UTGROUP_BOOL:
            return ufmt_bool_group_output_valid(&fmt->b);

        default:
            return true;
    }
}