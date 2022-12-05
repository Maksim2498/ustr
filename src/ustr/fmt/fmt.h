#ifndef USTR_FMT_FMT_H
#define USTR_FMT_FMT_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/fmt/case.h>
#include <ustr/type/fmt/fmt.h>
#include <ustr/type/char.h>
#include <ustr/type/cview.h>
#include <ustr/type/str.h>
#include <ustr/type/view.h>

static const struct ufmt UFMT = {
    .precision     = 0,
    .len           = 0,
    .arg_precision = false,
    .use_precision = false,
    .type          = UTYPE_UNKNOWN
};

static const struct uigfmt UIGFMT = {
    .digit_case        = UCASE_LOWER,
    .radix             = 10,
    .show_plus         = false,
    .show_radix_prefix = false,
    .radix_prefix_case = UCASE_LOWER
};

static const struct ufgfmt UFGFMT = {
    .scientific = false,
    .exp_case   = UCASE_LOWER,
    .show_plus  = false
};

static const struct ubgfmt UBGFMT = {
    .char_case = UCASE_LOWER
};

struct ufmt ufmt_from_ucv32(ucv32_t view);
struct ufmt ufmt_from_us32(const us32_t *str);
struct ufmt ufmt_from_uv32(uv32_t view);

struct ufmt ufmt_from_uz32(const uc32_t *cstr);
struct ufmt ufmt_from_uz32_n(const uc32_t *cstr, size_t n);

struct ufmt ufmt_from_uz16(const uc16_t *cstr);
struct ufmt ufmt_from_uz16_n(const uc16_t *cstr, size_t n);

struct ufmt ufmt_from_uz8(const uc8_t *cstr);
struct ufmt ufmt_from_uz8_n(const uc8_t *cstr, size_t n);

struct ufmt ufmt_from_z(const char *cstr);
struct ufmt ufmt_from_z_n(const char *cstr, size_t n);

bool ufmt_valid(const struct ufmt *fmt);

bool uigfmt_valid(const struct uigfmt *fmt);
bool ufgfmt_valid(const struct ufgfmt *fmt);
bool ubgfmt_valid(const struct ubgfmt *fmt);

#endif