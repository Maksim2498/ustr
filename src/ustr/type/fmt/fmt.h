#ifndef USTR_TYPE_FMT_FMT_H
#define USTR_TYPE_FMT_FMT_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#include <ustr/type/util/write.h>
#include <ustr/util/export.h>

#include "case.h"
#include "plus.h"
#include "radix.h"
#include "type.h"

// Output

// - Group format

// -- Int

// --- Struct

struct ufmt_int_group_output {
    uplus_t  plus;
    uradix_t radix;
    ucase_t  digit_case;
    ucase_t  radix_prefix_case;
    bool     show_radix_prefix;
};

// --- Predefined

#define UFMT_INT_GROUP_OUTPUT_CTC ((struct ufmt_int_group_output) { \
    .plus              = UPLUS_NONE,                                \
    .radix             = 10,                                        \
    .digit_case        = UCASE_UPPER,                               \
    .radix_prefix_case = UCASE_LOWER,                               \
    .show_radix_prefix = false                                      \
})

UEXPORT static const struct ufmt_int_group_output UFMT_INT_GROUP_OUTPUT = UFMT_INT_GROUP_OUTPUT_CTC;

// -- Float

// --- Struct

struct ufmt_float_group_output {
    ucase_t exp_case;
    bool    scientific;
    uplus_t plus;
};

// --- Predefined

#define UFMT_FLOAT_GROUP_OUTPUT_CTC ((struct ufmt_float_group_output) { \
    .exp_case   = UCASE_LOWER,                                          \
    .scientific = false,                                                \
    .plus       = UPLUS_NONE                                            \
})

UEXPORT static const struct ufmt_float_group_output UFMT_FLOAT_GROUP_OUTPUT = UFMT_FLOAT_GROUP_OUTPUT_CTC;

// -- Bool

// --- Struct

struct ufmt_bool_group_output {
    ucase_t char_case;
};

// --- Predefined

#define UFMT_BOOL_GROUP_OUTPUT_CTC ((struct ufmt_bool_group_output) { \
    .char_case = UCASE_LOWER                                          \
})

UEXPORT static const struct ufmt_bool_group_output UFMT_BOOl_GROUP_OUTPUT = UFMT_BOOL_GROUP_OUTPUT_CTC;

// - Format

// -- Struct

struct ufmt_output {
    size_t   precision;
    unsigned len;
    bool     arg_precision;
    bool     use_precision;
    utype_t  type;

    union {
        struct ufmt_int_group_output   i;
        struct ufmt_float_group_output f;
        struct ufmt_bool_group_output  b;
    };
};

// -- Predefined

#define UFMT_OUTPUT_CTC ((struct ufmt_output) { \
    .precision     = 0,                         \
    .len           = 0,                         \
    .arg_precision = false,                     \
    .use_precision = false,                     \
    .type          = UTYPE_UNKNOWN              \
})

UEXPORT static const struct ufmt_output UFMT_OUTPUT = UFMT_OUTPUT_CTC;

// - Custom

typedef size_t (*uwrite_custom_32_t)(uwrite_uc32_t, void *, const struct ufmt_output *, va_list *);
typedef size_t (*uwrite_custom_16_t)(uwrite_uc16_t, void *, const struct ufmt_output *, va_list *);
typedef size_t (*uwrite_custom_8_t)(uwrite_uc8_t, void *, const struct ufmt_output *, va_list *);

#endif