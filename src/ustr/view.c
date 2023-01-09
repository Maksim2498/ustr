#include "view.h"

#include <assert.h>

#include "cstr.h"
#include "cview.h"
#include "str.h"

uv32_t uv32_mk(void) {
    return (uv32_t) {
        .chars = NULL,
        .len   = 0
    };
}

uv32_t uv32_from_range(uv32_t view, size_t from, size_t len) {
    return uv32_from_uv32_range(view, from, len);
}

uv32_t uv32_from_uv32_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    
    return (uv32_t) {
        .chars = view.chars + from,
        .len   = len
    };
}

uv32_t uv32_from_us32(us32_t *str) {
    assert(us32_valid(str));

    return (uv32_t) {
        .chars = str->chars,
        .len   = str->len
    };
}

uv32_t uv32_from_us32_range(us32_t *str, size_t from, size_t len) {
    assert(us32_ebounds_range(str, from, len));

    return (uv32_t) {
        .chars = str->chars + from,
        .len   = len
    };
}

uv32_t uv32_from_uz32(uc32_t *cstr) {
    assert(cstr);

    return (uv32_t) {
        .chars = cstr,
        .len   = uz32_len(cstr)
    };
}

uv32_t uv32_from_uz32n(uc32_t *cstr, size_t n) {
    assert(cstr);

    return (uv32_t) {
        .chars = cstr,
        .len   = n
    };
}

size_t uv32_len_n_from(uv32_t view, unsigned n, size_t from) {
    switch (n) {
        case 1:
            return uv32_len_8_from(view, from);

        case 2:
            return uv32_len_16_from(view, from);

        case 4:
            return uv32_len_32_from(view, from);

        default:
            assert(false);
            break;
    }
}

size_t uv32_len_32_from(uv32_t view, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_len_32(uv32_cchars(view) + from, view.len - from);
}

size_t uv32_len_16_from(uv32_t view, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_len_16(uv32_cchars(view) + from, view.len - from);
}

size_t uv32_len_8_from(uv32_t view, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_len_8(uv32_cchars(view) + from, view.len - from);
}

size_t uv32_len_n_to(uv32_t view, unsigned n, size_t to) {
    switch (n) {
        case 1:
            return uv32_len_8_to(view, to);

        case 2:
            return uv32_len_16_to(view, to);

        case 4:
            return uv32_len_32_to(view, to);

        default:
            assert(false);
            break;
    }
}

size_t uv32_len_32_to(uv32_t view, size_t to) {
    assert(uv32_ebounds(view, to));
    return uz32n_len_32(uv32_cchars(view), to);
}

size_t uv32_len_16_to(uv32_t view, size_t to) {
    assert(uv32_ebounds(view, to));
    return uz32n_len_16(uv32_cchars(view), to);
}

size_t uv32_len_8_to(uv32_t view, size_t to) {
    assert(uv32_ebounds(view, to));
    return uz32n_len_8(uv32_cchars(view), to);
}

size_t uv32_len_n_range(uv32_t view, unsigned n, size_t from, size_t len) {
    switch (n) {
        case 1:
            return uv32_len_8_range(view, from, len);

        case 2:
            return uv32_len_16_range(view, from, len);

        case 4:
            return uv32_len_32_range(view, from, len);

        default:
            assert(false);
            break;
    }
}

size_t uv32_len_32_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    return uz32n_len_32(uv32_cchars(view) + from, len);
}

size_t uv32_len_16_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    return uz32n_len_16(uv32_cchars(view) + from, len);
}

size_t uv32_len_8_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    return uz32n_len_8(uv32_cchars(view) + from, len);
}

size_t uv32_len_n(uv32_t view, unsigned n) {
    return uz32n_len_n(UV32_CEXPAND(view), n);
}

size_t uv32_len_32(uv32_t view) {
    return uv32_len(view);
}

size_t uv32_len_16(uv32_t view) {
    return uz32n_len_16(UV32_CEXPAND(view));
}

size_t uv32_len_8(uv32_t view) {
    return uz32n_len_8(UV32_CEXPAND(view));
}

void uv32_reverse(uv32_t view) {
    uz32n_reverse(UV32_EXPAND(view));
}

size_t uv32_trim(uv32_t *view) {
    assert(uv32_valid_p(view));
    return view->len = uz32n_trim(UV32_EXPAND(*view));
}

size_t uv32_trim_left(uv32_t *view) {
    assert(uv32_valid_p(view));
    return view->len = uz32n_ltrim(UV32_EXPAND(*view));
}

size_t uv32_trim_right(uv32_t *view) {
    assert(uv32_valid_p(view));
    return view->len = uz32n_rtrim(UV32_CEXPAND(*view));
}

uc32_t uv32_at(uv32_t view, size_t index) {
    assert(uv32_bounds(view, index));
    return view.chars[index];
}

void uv32_set_at(uv32_t view, uc32_t c, size_t index) {
    assert(uv32_bounds(view, index));
    view.chars[index] = c;
}

int uv32_cmp(uv32_t lhs, uv32_t rhs) {
    return uv32_cmp_uv32(lhs, rhs);
}

int uv32_cmp_n(uv32_t lhs, uv32_t rhs, size_t n) {
    return uv32_cmp_uv32_n(lhs, rhs, n);
}

int uv32_cmp_uv32(uv32_t lhs, uv32_t rhs) {
    return uz32n_cmp_n(UV32_CEXPAND(lhs), UV32_CEXPAND(rhs));
}

int uv32_cmp_uv32_n(uv32_t lhs, uv32_t rhs, size_t n) {
    assert(uv32_ebounds(lhs, n) && uv32_ebounds(rhs, n));
    return uz32n_cmp_n(uv32_chars(lhs), n, uv32_chars(rhs), n);
}

int uv32_cmp_ucv32(uv32_t lhs, ucv32_t rhs) {
    return uz32n_cmp_n(UV32_CEXPAND(lhs), UCV32_CEXPAND(rhs));
}

int uv32_cmp_ucv32_n(uv32_t lhs, ucv32_t rhs, size_t n) {
    assert(uv32_ebounds(lhs, n) && ucv32_ebounds(rhs, n));
    return uz32n_cmp_n(uv32_chars(lhs), n, ucv32_cchars(rhs), n);
}

int uv32_cmp_us32(uv32_t lhs, const us32_t *rhs) {
    return uz32n_cmp_n(UV32_CEXPAND(lhs), US32_CEXPAND(rhs));
}

int uv32_cmp_us32_n(uv32_t lhs, const us32_t *rhs, size_t n) {
    assert(uv32_ebounds(lhs, n) && us32_ebounds(rhs, n));
    return uz32n_cmp_n(uv32_chars(lhs), n, us32_cchars(rhs), n);
}

int uv32_cmp_uz32(uv32_t lhs, const uc32_t *rhs) {
    return uz32n_cmp(UV32_CEXPAND(lhs), rhs);
}

int uv32_cmp_uz32_n(uv32_t lhs, const uc32_t *rhs, size_t n) {
    assert(uv32_ebounds(lhs, n));
    return uz32_cmp_n(lhs.chars, rhs, n);
}

int uv32_cmp_uz32n(uv32_t lhs, const uc32_t *rhs, size_t n) {
    return uz32n_cmp_n(UV32_CEXPAND(lhs), rhs, n);
}

int uv32_cmp_uz32n_n(uv32_t lhs, const uc32_t *rhs, size_t rhs_len, size_t n) {
    assert(uv32_ebounds(lhs, n) && rhs_len <= n);
    return uz32_cmp_n(lhs.chars, rhs, n);
}

ptrdiff_t uv32_pos(uv32_t view, uv32_t another) {
    return uv32_pos_uv32(view, another);
}

ptrdiff_t uv32_pos_from(uv32_t view, uv32_t another, size_t from) {
    return uv32_pos_uv32_from(view, another, from);
}

ptrdiff_t uv32_pos_uv32(uv32_t view, uv32_t another) {
    return uz32n_pos_uz32n(UV32_CEXPAND(view), UV32_CEXPAND(another));
}

ptrdiff_t uv32_pos_uv32_from(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(uv32_cchars(view) + from, view.len - from, UV32_CEXPAND(another));
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t uv32_pos_uc32(uv32_t view, uc32_t c) {
    return uz32n_pos_uc32(UV32_CEXPAND(view), c);
}

ptrdiff_t uv32_pos_uc32_from(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uc32(uv32_chars(view) + from, view.len - from, c);
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t uv32_pos_uz32(uv32_t view, const uc32_t *cstr) {
    return uz32n_pos_uz32(UV32_CEXPAND(view), cstr);
}

ptrdiff_t uv32_pos_uz32_from(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32(uv32_chars(view) + from, view.len - from, cstr);
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t uv32_pos_uz32n(uv32_t view, const uc32_t *cstr, size_t n) {
    return uz32n_pos_uz32n(UV32_CEXPAND(view), cstr, n);
}

ptrdiff_t uv32_pos_uz32n_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_pos_uz32n(uv32_chars(view) + from, view.len - from, cstr, n);
}

ptrdiff_t uv32_pos_ucv32(uv32_t view, ucv32_t another) {
    return uz32n_pos_uz32n(UV32_CEXPAND(view), UCV32_CEXPAND(another));
}

ptrdiff_t uv32_pos_ucv32_from(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(uv32_chars(view) + from, view.len - from, UCV32_CEXPAND(another));
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t uv32_pos_us32(uv32_t view, const us32_t *str) {
    return uz32n_pos_uz32n(UV32_CEXPAND(view), US32_CEXPAND(str));
}

ptrdiff_t uv32_pos_us32_from(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(uv32_chars(view) + from, view.len - from, US32_CEXPAND(str));
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t uv32_rpos(uv32_t view, uv32_t another) {
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), UV32_CEXPAND(another), view.len - 1);
}

ptrdiff_t uv32_rpos_from(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_rpos_uz32n(uv32_chars(view) + from, view.len - from, UV32_CEXPAND(another), from);
}

ptrdiff_t uv32_rpos_uc32(uv32_t view, uc32_t c) {
    return uz32n_rpos_uc32(UV32_CEXPAND(view), c, view.len - 1);
}

ptrdiff_t uv32_rpos_uc32_from(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_rpos_uc32(UV32_CEXPAND(view), c, from);
}

ptrdiff_t uv32_rpos_uz32(uv32_t view, const uc32_t *cstr) {
    return uz32n_rpos_uz32(UV32_CEXPAND(view), cstr, view.len - 1);
}

ptrdiff_t uv32_rpos_uz32_from(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_rpos_uz32(UV32_CEXPAND(view), cstr, from);
}

ptrdiff_t uv32_rpos_uz32n(uv32_t view, const uc32_t *cstr, size_t n) {
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), cstr, n, view.len - 1);
}

ptrdiff_t uv32_rpos_uz32n_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), cstr, n, from);
}

ptrdiff_t uv32_rpos_ucv32(uv32_t view, ucv32_t another) {
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), UCV32_CEXPAND(another), view.len - 1);
}

ptrdiff_t uv32_rpos_ucv32_from(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), UCV32_CEXPAND(another), from);
}

ptrdiff_t uv32_rpos_us32(uv32_t view, const us32_t *str) {
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), US32_CEXPAND(str), view.len - 1);
}

ptrdiff_t uv32_rpos_us32_from(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UV32_CEXPAND(view), US32_CEXPAND(str), from);
}

void uv32_fill(uv32_t view, uc32_t c) {
    uv32_fill_uc32(view, c);
}

void uv32_fill_from(uv32_t view, uc32_t c, size_t from) {
    uv32_fill_uc32_from(view, c, from);
}

void uv32_fill_to(uv32_t view, uc32_t c, size_t to) {
    uv32_fill_uc32_to(view, c, to);
}

void uv32_fill_range(uv32_t view, uc32_t c, size_t from, size_t len) {
    uv32_fill_uc32_range(view, c, from, len);
}

void uv32_fill_uc32(uv32_t view, uc32_t c) {
    uz32n_fill_uc32(UV32_EXPAND(view), c);
}

void uv32_fill_uc32_from(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_ebounds(view, from));
    uz32n_fill_uc32(uv32_chars(view) + from, view.len - from, c);
}

void uv32_fill_uc32_to(uv32_t view, uc32_t c, size_t to) {
    assert(uv32_ebounds(view, to));
    uz32n_fill_uc32(uv32_chars(view), to, c);
}

void uv32_fill_uc32_range(uv32_t view, uc32_t c, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    uz32n_fill_uc32(uv32_chars(view) + from, len, c);
}

void uv32_fill_uz32(uv32_t view, const uc32_t *cstr) {
    uz32n_fill_uz32(UV32_EXPAND(view), cstr);
}

void uv32_fill_uz32_from(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_ebounds(view, from));
    uz32n_fill_uz32(uv32_chars(view) + from, view.len - from, cstr);
}

void uv32_fill_uz32_to(uv32_t view, const uc32_t *cstr, size_t to) {
    assert(uv32_ebounds(view, to));
    uz32n_fill_uz32(uv32_chars(view), to, cstr);
}

void uv32_fill_uz32_range(uv32_t view, const uc32_t *cstr, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    uz32n_fill_uz32(uv32_chars(view) + from, len, cstr);
}

void uv32_fill_uz32n(uv32_t view, const uc32_t *cstr, size_t n) {
    uz32n_fill_uz32n(UV32_EXPAND(view), cstr, n);
}

void uv32_fill_uz32n_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_ebounds(view, from));
    uz32n_fill_uz32n(uv32_chars(view) + from, view.len - from, cstr, n);
}

void uv32_fill_uz32n_to(uv32_t view, const uc32_t *cstr, size_t n, size_t to) {
    assert(uv32_ebounds(view, to));
    uz32n_fill_uz32n(uv32_chars(view), to, cstr, n);
}

void uv32_fill_uz32n_range(uv32_t view, const uc32_t *cstr, size_t n, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    uz32n_fill_uz32n(uv32_chars(view) + from, len, cstr, n);
}

void uv32_fill_uv32(uv32_t view, uv32_t another) {
    uz32n_fill_uz32n(UV32_EXPAND(view), UV32_CEXPAND(another));
}

void uv32_fill_uv32_from(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_ebounds(view, from));
    uz32n_fill_uz32n(uv32_chars(view) + from, view.len - from, UV32_CEXPAND(another));
}

void uv32_fill_uv32_to(uv32_t view, uv32_t another, size_t to) {
    assert(uv32_ebounds(view, to));
    uz32n_fill_uz32n(uv32_chars(view), to, UV32_CEXPAND(another));
}

void uv32_fill_uv32_range(uv32_t view, uv32_t another, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    uz32n_fill_uz32n(uv32_chars(view) + from, len, UV32_CEXPAND(another));
}

void uv32_fill_ucv32(uv32_t view, ucv32_t another) {
    uz32n_fill_uz32n(UV32_EXPAND(view), UCV32_CEXPAND(another));
}

void uv32_fill_ucv32_from(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_ebounds(view, from));
    uz32n_fill_uz32n(uv32_chars(view) + from, view.len - from, UCV32_CEXPAND(another));
}

void uv32_fill_ucv32_to(uv32_t view, ucv32_t another, size_t to) {
    assert(uv32_ebounds(view, to));
    uz32n_fill_uz32n(uv32_chars(view), to, UCV32_CEXPAND(another));
}

void uv32_fill_ucv32_range(uv32_t view, ucv32_t another, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    uz32n_fill_uz32n(uv32_chars(view) + from, len, UCV32_CEXPAND(another));
}

void uv32_fill_us32(uv32_t view, const us32_t *str) {
    uz32n_fill_uz32n(UV32_EXPAND(view), US32_CEXPAND(str));
}

void uv32_fill_us32_from(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_ebounds(view, from));
    uz32n_fill_uz32n(uv32_chars(view) + from, view.len - from, US32_CEXPAND(str));
}

void uv32_fill_us32_to(uv32_t view, const us32_t *str, size_t to) {
    assert(uv32_ebounds(view, to));
    uz32n_fill_uz32n(uv32_chars(view), to, US32_CEXPAND(str));
}

void uv32_fill_us32_range(uv32_t view, const us32_t *str, size_t from, size_t len) {
    assert(uv32_ebounds_range(view, from, len));
    return uz32n_fill_uz32n(uv32_chars(view) + from, len, US32_CEXPAND(str));
}

void uv32_to_case(uv32_t view, ucase_t ca) {
    assert(uv32_valid(view));
    uz32n_to_case(UV32_EXPAND(view), ca);
}

void uv32_to_upper(uv32_t view) {
    uz32n_to_upper(UV32_EXPAND(view));
}

void uv32_to_lower(uv32_t view) {
    uz32n_to_lower(UV32_EXPAND(view));
}

uc32_t *uv32_begin(uv32_t view) {
    assert(uv32_valid(view));
    return view.chars;
}

const uc32_t *uv32_cbegin(uv32_t view) {
    assert(uv32_valid(view));
    return view.chars;
}

uc32_t *uv32_end(uv32_t view) {
    assert(uv32_valid(view));
    return view.chars + view.len;
}

const uc32_t *uv32_cend(uv32_t view) {
    assert(uv32_valid(view));
    return view.chars + view.len;
}

uc32_t *uv32_offset(uv32_t view, size_t index) {
    assert(uv32_ebounds(view, index));
    return view.chars + index;
}

const uc32_t *uv32_coffset(uv32_t view, size_t index) {
    assert(uv32_ebounds(view, index));
    return view.chars + index;
}

bool uv32_bounds(uv32_t view, size_t index) {
    assert(uv32_valid(view));
    return index < view.len;
}

bool uv32_ebounds(uv32_t view, size_t index) {
    assert(uv32_valid(view));
    return index <= view.len;
}

bool uv32_bounds_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_valid(view));
    return from < view.len && from + len < view.len;
}

bool uv32_ebounds_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_valid(view));
    return from <= view.len && from + len <= view.len;
}

size_t uv32_len(uv32_t view) {
    assert(uv32_valid(view));
    return view.len;
}

size_t uv32_add_len(uv32_t *view, ptrdiff_t delta) {
    assert(uv32_valid_p(view) && -(ptrdiff_t) view->len <= delta);
    return view->len += delta;
}

void uv32_set_len(uv32_t *view, size_t len) {
    assert(uv32_valid_p(view) && (!len || view->chars));
    view->len = len;
}

bool uv32_empty(uv32_t view) {
    assert(uv32_valid(view));
    return !view.len;
}

size_t uv32_new_csplit(uv32_t view, uv32_t another, ucv32_t **array) {
    return uv32_new_csplit_uv32(view, another, array);
}

size_t uv32_new_csplit_e(uv32_t view, uv32_t another, ucv32_t **array, bool *error) {
    return uv32_new_csplit_uv32_e(view, another, array, error);
}

size_t uv32_csplit(uv32_t view, uv32_t another, ucv32_t *array, size_t array_len) {
    return uv32_csplit_uv32(view, another, array, array_len);
}

size_t uv32_new_split(uv32_t view, uv32_t another, uv32_t **array) {
    return uv32_new_split_uv32(view, another, array);
}

size_t uv32_new_split_e(uv32_t view, uv32_t another, uv32_t **array, bool *error) {
    return uv32_new_split_uv32_e(view, another, array, error);
}

size_t uv32_split(uv32_t view, uv32_t another, uv32_t *array, size_t array_len) {
    return uv32_split_uv32(view, another, array, array_len);
}

size_t uv32_new_csplit_uc32(uv32_t view, uc32_t c, ucv32_t **array) {
    return uz32n_new_csplit_uc32(UV32_CEXPAND(view), c, array);
}

size_t uv32_new_csplit_uc32_e(uv32_t view, uc32_t c, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uc32_e(UV32_CEXPAND(view), c, array, error);
}

size_t uv32_csplit_uc32(uv32_t view, uc32_t c, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uc32(UV32_CEXPAND(view), c, array, array_len);
}

size_t uv32_new_split_uc32(uv32_t view, uc32_t c, uv32_t **array) {
    return uz32n_new_split_uc32(UV32_EXPAND(view), c, array);
}

size_t uv32_new_split_uc32_e(uv32_t view, uc32_t c, uv32_t **array, bool *error) {
    return uz32n_new_split_uc32_e(UV32_EXPAND(view), c, array, error);
}

size_t uv32_split_uc32(uv32_t view, uc32_t c, uv32_t *array, size_t array_len) {
    return uz32n_split_uc32(UV32_EXPAND(view), c, array, array_len);
}

size_t uv32_new_csplit_uz32(uv32_t view, const uc32_t *cstr, ucv32_t **array) {
    return uz32n_new_csplit_uz32(UV32_CEXPAND(view), cstr, array);
}

size_t uv32_new_csplit_uz32_e(uv32_t view, const uc32_t *cstr, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32_e(UV32_CEXPAND(view), cstr, array, error);
}

size_t uv32_csplit_uz32(uv32_t view, const uc32_t *cstr, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32(UV32_CEXPAND(view), cstr, array, array_len);
}

size_t uv32_new_split_uz32(uv32_t view, const uc32_t *cstr, uv32_t **array) {
    return uz32n_new_split_uz32(UV32_EXPAND(view), cstr, array);
}

size_t uv32_new_split_uz32_e(uv32_t view, const uc32_t *cstr, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32_e(UV32_EXPAND(view), cstr, array, error);
}

size_t uv32_split_uz32(uv32_t view, const uc32_t *cstr, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32(UV32_EXPAND(view), cstr, array, array_len);
}

size_t uv32_new_csplit_uz32n(uv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UV32_CEXPAND(view), cstr, n, array);
}

size_t uv32_new_csplit_uz32n_e(uv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UV32_CEXPAND(view), cstr, n, array, error);
}

size_t uv32_csplit_uz32n(uv32_t view, const uc32_t *cstr, size_t n, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UV32_CEXPAND(view), cstr, n, array, array_len);
}

size_t uv32_new_split_uz32n(uv32_t view, const uc32_t *cstr, size_t n, uv32_t **array) {
    return uz32n_new_split_uz32n(UV32_EXPAND(view), cstr, n, array);
}

size_t uv32_new_split_uz32n_e(uv32_t view, const uc32_t *cstr, size_t n, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(UV32_EXPAND(view), cstr, n, array, error);
}

size_t uv32_split_uz32n(uv32_t view, const uc32_t *cstr, size_t n, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(UV32_EXPAND(view), cstr, n, array, array_len);
}

size_t uv32_new_csplit_ucv32(uv32_t view, ucv32_t another, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UV32_CEXPAND(view), UCV32_CEXPAND(another), array);
}

size_t uv32_new_csplit_ucv32_e(uv32_t view, ucv32_t another, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UV32_CEXPAND(view), UCV32_CEXPAND(another), array, error);
}

size_t uv32_csplit_ucv32(uv32_t view, ucv32_t another, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UV32_CEXPAND(view), UCV32_CEXPAND(another), array, array_len);
}

size_t uv32_new_split_ucv32(uv32_t view, ucv32_t another, uv32_t **array) {
    return uz32n_new_split_uz32n(UV32_EXPAND(view), UCV32_CEXPAND(another), array);
}

size_t uv32_new_split_ucv32_e(uv32_t view, ucv32_t another, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(UV32_EXPAND(view), UCV32_CEXPAND(another), array, error);
}

size_t uv32_split_ucv32(uv32_t view, ucv32_t another, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(UV32_EXPAND(view), UCV32_CEXPAND(another), array, array_len);
}

size_t uv32_new_csplit_us32(uv32_t view, const us32_t *str, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UV32_CEXPAND(view), US32_CEXPAND(str), array);
}

size_t uv32_new_csplit_us32_e(uv32_t view, const us32_t *str, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UV32_CEXPAND(view), US32_CEXPAND(str), array, error);
}

size_t uv32_csplit_us32(uv32_t view, const us32_t *str, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UV32_CEXPAND(view), US32_CEXPAND(str), array, array_len);
}

size_t uv32_new_split_us32(uv32_t view, const us32_t *str, uv32_t **array) {
    return uz32n_new_split_uz32n(UV32_EXPAND(view), US32_CEXPAND(str), array);
}

size_t uv32_new_split_us32_e(uv32_t view, const us32_t *str, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(UV32_EXPAND(view), US32_CEXPAND(str), array, error);
}

size_t uv32_split_us32(uv32_t view, const us32_t *str, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(UV32_EXPAND(view), US32_CEXPAND(str), array, array_len);
}

size_t uv32_new_csplit_uv32(uv32_t view, uv32_t another, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UV32_CEXPAND(view), UV32_EXPAND(another), array);
}

size_t uv32_new_csplit_uv32_e(uv32_t view, uv32_t another, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UV32_CEXPAND(view), UV32_EXPAND(another), array, error);
}

size_t uv32_csplit_uv32(uv32_t view, uv32_t another, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UV32_CEXPAND(view), UV32_EXPAND(another), array, array_len);
}

size_t uv32_new_split_uv32(uv32_t view, uv32_t another, uv32_t **array) {
    return uz32n_new_split_uz32n(UV32_EXPAND(view), UV32_EXPAND(another), array);
}

size_t uv32_new_split_uv32_e(uv32_t view, uv32_t another, uv32_t **array, bool *error) {
    return uz32n_new_split_uz32n_e(UV32_EXPAND(view), UV32_EXPAND(another), array, error);
}

size_t uv32_split_uv32(uv32_t view, uv32_t another, uv32_t *array, size_t array_len) {
    return uz32n_split_uz32n(UV32_EXPAND(view), UV32_EXPAND(another), array, array_len);
}

size_t uv32_replace_uc32_uc32(uv32_t *view, uc32_t from, uc32_t to) {
    return uv32_replace_uc32_uc32_c(view, from, to, NULL);
}

size_t uv32_replace_uc32_uc32_c(uv32_t *view, uc32_t from, uc32_t to, size_t *count) {
    assert(view);
	return view->len = uz32n_replace_uc32_uc32_c(UV32_EXPAND(*view), from, to, count);
}

size_t uv32_replace_uz32_uc32(uv32_t *view, const uc32_t *from, uc32_t to) {
    return uv32_replace_uz32_uc32_c(view, from, to, NULL);
}

size_t uv32_replace_uz32_uc32_c(uv32_t *view, const uc32_t *from, uc32_t to, size_t *count) {
    assert(view);
	return view->len = uz32n_replace_uz32_uc32_c(UV32_EXPAND(*view), from, to, count);
}

size_t uv32_replace_uz32n_uc32(uv32_t *view, const uc32_t *from, size_t from_len, uc32_t to) {
    return uv32_replace_uz32n_uc32_c(view, from, from_len, to, NULL);
}

size_t uv32_replace_uz32n_uc32_c(uv32_t *view, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    assert(view);
	return view->len = uz32n_replace_uz32n_uc32_c(UV32_EXPAND(*view), from, from_len, to, count);
}

size_t uv32_replace_ucv32_uc32(uv32_t *view, ucv32_t from, uc32_t to) {
    return uv32_replace_ucv32_uc32_c(view, from, to, NULL);
}

size_t uv32_replace_ucv32_uc32_c(uv32_t *view, ucv32_t from, uc32_t to, size_t *count) {
    assert(view);
	return view->len = uz32n_replace_uz32n_uc32_c(UV32_EXPAND(*view), UCV32_CEXPAND(from), to, count);
}

size_t uv32_replace_us32_uc32(uv32_t *view, const us32_t *from, uc32_t to) {
    return uv32_replace_us32_uc32_c(view, from, to, NULL);
}

size_t uv32_replace_us32_uc32_c(uv32_t *view, const us32_t *from, uc32_t to, size_t *count) {
    assert(view);
	return view->len = uz32n_replace_uz32n_uc32_c(UV32_EXPAND(*view), US32_CEXPAND(from), to, count);
}

size_t uv32_replace_uv32_uc32(uv32_t *view, uv32_t from, uc32_t to) {
    return uv32_replace_uv32_uc32_c(view, from, to, NULL);
}

size_t uv32_replace_uv32_uc32_c(uv32_t *view, uv32_t from, uc32_t to, size_t *count) {
    assert(view);
	return view->len = uz32n_replace_uz32n_uc32_c(UV32_EXPAND(*view), UV32_CEXPAND(from), to, count);
}

size_t uv32_replace_uc32_uz32(uv32_t *view, uc32_t from, const uc32_t *to) {
    return uv32_replace_uc32_uz32_c(view, from, to, NULL);
}

size_t uv32_replace_uc32_uz32_c(uv32_t *view, uc32_t from, const uc32_t *to, size_t *count) {
	return uv32_replace_uc32_uz32n_c(view, from, to, uz32_len(to), count);
}

size_t uv32_replace_uc32_uz32n(uv32_t *view, uc32_t from, const uc32_t *to, size_t to_len) {
    return uv32_replace_uc32_uz32n_c(view, from, to, to_len, NULL);
}

size_t uv32_replace_uc32_uz32n_c(uv32_t *view, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
    assert(view);
    size_t new_len = uz32n_replace_uc32_uz32n_c(UV32_EXPAND(*view), from, to, to_len, count);
    assert(view->len >= new_len);
	return view->len = new_len;
}

size_t uv32_replace_uc32_ucv32(uv32_t *view, uc32_t from, ucv32_t to) {
    return uv32_replace_uc32_ucv32_c(view, from, to, NULL);
}

size_t uv32_replace_uc32_ucv32_c(uv32_t *view, uc32_t from, ucv32_t to, size_t *count) {
	return uv32_replace_uc32_uz32n_c(view, from, UCV32_CEXPAND(to), count);
}

size_t uv32_replace_uc32_us32(uv32_t *view, uc32_t from, const us32_t *to) {
    return uv32_replace_uc32_us32_c(view, from, to, NULL);
}

size_t uv32_replace_uc32_us32_c(uv32_t *view, uc32_t from, const us32_t *to, size_t *count) {
	return uv32_replace_uc32_uz32n_c(view, from, US32_CEXPAND(to), count);
}

size_t uv32_replace_uc32_uv32(uv32_t *view, uc32_t from, uv32_t to) {
    return uv32_replace_uc32_uv32_c(view, from, to, NULL);
}

size_t uv32_replace_uc32_uv32_c(uv32_t *view, uc32_t from, uv32_t to, size_t *count) {
	return uv32_replace_uc32_uz32n_c(view, from, UV32_CEXPAND(to), count);
}

size_t uv32_replace_uz32_uz32(uv32_t *view, const uc32_t *from, const uc32_t *to) {
    return uv32_replace_uz32_uz32_c(view, from, to, NULL);
}

size_t uv32_replace_uz32_uz32_c(uv32_t *view, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, uz32_len(from), to, uz32_len(to), count);
}

size_t uv32_replace_uz32n_uz32(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uv32_replace_uz32n_uz32_c(view, from, from_len, to, NULL);
}

size_t uv32_replace_uz32n_uz32_c(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, from_len, to, uz32_len(to), count);
}

size_t uv32_replace_ucv32_uz32(uv32_t *view, ucv32_t from, const uc32_t *to) {
    return uv32_replace_ucv32_uz32_c(view, from, to, NULL);
}

size_t uv32_replace_ucv32_uz32_c(uv32_t *view, ucv32_t from, const uc32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UCV32_CEXPAND(from), to, uz32_len(to), count);
}

size_t uv32_replace_us32_uz32(uv32_t *view, const us32_t *from, const uc32_t *to) {
    return uv32_replace_us32_uz32_c(view, from, to, NULL);
}

size_t uv32_replace_us32_uz32_c(uv32_t *view, const us32_t *from, const uc32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, US32_CEXPAND(from), to, uz32_len(to), count);
}

size_t uv32_replace_uv32_uz32(uv32_t *view, uv32_t from, const uc32_t *to) {
    return uv32_replace_uv32_uz32_c(view, from, to, NULL);
}

size_t uv32_replace_uv32_uz32_c(uv32_t *view, uv32_t from, const uc32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UV32_CEXPAND(from), to, uz32_len(to), count);
}

size_t uv32_replace_uz32_uz32n(uv32_t *view, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uv32_replace_uz32_uz32n_c(view, from, to, to_len, NULL);
}

size_t uv32_replace_uz32_uz32n_c(uv32_t *view, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, uz32_len(from), to, to_len, count);
}

size_t uv32_replace_uz32n_uz32n(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uv32_replace_uz32n_uz32n_c(view, from, from_len, to, to_len, NULL);
}

size_t uv32_replace_uz32n_uz32n_c(uv32_t *view, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
    assert(view);
    size_t new_len = uz32n_replace_uz32n_uz32n_c(UV32_EXPAND(*view), from, from_len, to, to_len, count);
    assert(view->len >= new_len);
	return view->len = new_len;
}

size_t uv32_replace_ucv32_uz32n(uv32_t *view, ucv32_t from, const uc32_t *to, size_t to_len) {
	return uv32_replace_ucv32_uz32n_c(view, from, to, to_len, NULL);
}

size_t uv32_replace_ucv32_uz32n_c(uv32_t *view, ucv32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UCV32_CEXPAND(from), to, to_len, count);
}

size_t uv32_replace_us32_uz32n(uv32_t *view, const us32_t *from, const uc32_t *to, size_t to_len) {
	return uv32_replace_us32_uz32n_c(view, from, to, to_len, NULL);
}

size_t uv32_replace_us32_uz32n_c(uv32_t *view, const us32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, US32_CEXPAND(from), to, to_len, count);
}

size_t uv32_replace_uv32_uz32n(uv32_t *view, uv32_t from, const uc32_t *to, size_t to_len) {
	return uv32_replace_uv32_uz32n_c(view, from, to, to_len, NULL);
}

size_t uv32_replace_uv32_uz32n_c(uv32_t *view, uv32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UV32_CEXPAND(from), to, to_len, count);
}

size_t uv32_replace_uz32_ucv32(uv32_t *view, const uc32_t *from, ucv32_t to) {
	return uv32_replace_uz32_ucv32_c(view, from, to, NULL);
}

size_t uv32_replace_uz32_ucv32_c(uv32_t *view, const uc32_t *from, ucv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, uz32_len(from), UCV32_CEXPAND(to), count);
}

size_t uv32_replace_uz32n_ucv32(uv32_t *view, const uc32_t *from, size_t from_len, ucv32_t to) {
	return uv32_replace_uz32n_ucv32_c(view, from, from_len, to, NULL);
}

size_t uv32_replace_uz32n_ucv32_c(uv32_t *view, const uc32_t *from, size_t from_len, ucv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, from_len, UCV32_CEXPAND(to), count);
}

size_t uv32_replace_ucv32_ucv32(uv32_t *view, ucv32_t from, ucv32_t to) {
	return uv32_replace_ucv32_ucv32_c(view, from, to, NULL);
}

size_t uv32_replace_ucv32_ucv32_c(uv32_t *view, ucv32_t from, ucv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UCV32_CEXPAND(from), UCV32_CEXPAND(to), count);
}

size_t uv32_replace_us32_ucv32(uv32_t *view, const us32_t *from, ucv32_t to) {
	return uv32_replace_us32_ucv32_c(view, from, to, NULL);
}

size_t uv32_replace_us32_ucv32_c(uv32_t *view, const us32_t *from, ucv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, US32_CEXPAND(from), UCV32_CEXPAND(to), count);
}

size_t uv32_replace_uv32_ucv32(uv32_t *view, uv32_t from, ucv32_t to) {
	return uv32_replace_uv32_ucv32_c(view, from, to, NULL);
}

size_t uv32_replace_uv32_ucv32_c(uv32_t *view, uv32_t from, ucv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UV32_CEXPAND(from), UCV32_CEXPAND(to), count);
}

size_t uv32_replace_uz32_us32(uv32_t *view, const uc32_t *from, const us32_t *to) {
	return uv32_replace_uz32_us32_c(view, from, to, NULL);
}

size_t uv32_replace_uz32_us32_c(uv32_t *view, const uc32_t *from, const us32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, uz32_len(from), US32_CEXPAND(to), count);
}

size_t uv32_replace_uz32n_us32(uv32_t *view, const uc32_t *from, size_t from_len, const us32_t *to) {
	return uv32_replace_uz32n_us32_c(view, from, from_len, to, NULL);
}

size_t uv32_replace_uz32n_us32_c(uv32_t *view, const uc32_t *from, size_t from_len, const us32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, from_len, US32_CEXPAND(to), count);
}

size_t uv32_replace_ucv32_us32(uv32_t *view, ucv32_t from, const us32_t *to) {
	return uv32_replace_ucv32_us32_c(view, from, to, NULL);
}

size_t uv32_replace_ucv32_us32_c(uv32_t *view, ucv32_t from, const us32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UCV32_CEXPAND(from), US32_CEXPAND(to), count);
}

size_t uv32_replace_us32_us32(uv32_t *view, const us32_t *from, const us32_t *to) {
	return uv32_replace_us32_us32_c(view, from, to, NULL);
}

size_t uv32_replace_us32_us32_c(uv32_t *view, const us32_t *from, const us32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, US32_CEXPAND(from), US32_CEXPAND(to), count);
}

size_t uv32_replace_uv32_us32(uv32_t *view, uv32_t from, const us32_t *to) {
	return uv32_replace_uv32_us32_c(view, from, to, NULL);
}

size_t uv32_replace_uv32_us32_c(uv32_t *view, uv32_t from, const us32_t *to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UV32_CEXPAND(from), US32_CEXPAND(to), count);
}

size_t uv32_replace_uz32_uv32(uv32_t *view, const uc32_t *from, uv32_t to) {
	return uv32_replace_uz32_uv32_c(view, from, to, NULL);
}

size_t uv32_replace_uz32_uv32_c(uv32_t *view, const uc32_t *from, uv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, uz32_len(from), UV32_EXPAND(to), count);
}

size_t uv32_replace_uz32n_uv32(uv32_t *view, const uc32_t *from, size_t from_len, uv32_t to) {
	return uv32_replace_uz32n_uv32_c(view, from, from_len, to, NULL);
}

size_t uv32_replace_uz32n_uv32_c(uv32_t *view, const uc32_t *from, size_t from_len, uv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, from, from_len, UV32_EXPAND(to), count);
}

size_t uv32_replace_ucv32_uv32(uv32_t *view, ucv32_t from, uv32_t to) {
	return uv32_replace_ucv32_uv32_c(view, from, to, NULL);
}

size_t uv32_replace_ucv32_uv32_c(uv32_t *view, ucv32_t from, uv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UCV32_CEXPAND(from), UV32_EXPAND(to), count);
}

size_t uv32_replace_us32_uv32(uv32_t *view, const us32_t *from, uv32_t to) {
	return uv32_replace_us32_uv32_c(view, from, to, NULL);
}

size_t uv32_replace_us32_uv32_c(uv32_t *view, const us32_t *from, uv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, US32_CEXPAND(from), UV32_EXPAND(to), count);
}

size_t uv32_replace_uv32_uv32(uv32_t *view, uv32_t from, uv32_t to) {
	return uv32_replace_uv32_uv32_c(view, from, to, NULL);
}

size_t uv32_replace_uv32_uv32_c(uv32_t *view, uv32_t from, uv32_t to, size_t *count) {
	return uv32_replace_uz32n_uz32n_c(view, UV32_CEXPAND(from), UV32_EXPAND(to), count);
}

const uc32_t *uv32_cchars(uv32_t view) {
    assert(uv32_valid(view));
    return view.chars ? view.chars : U"";
}

uc32_t *uv32_chars(uv32_t view) {
    assert(uv32_valid(view));
    static uc32_t chars[] = U"";
    return view.chars ? view.chars : chars;
}

void uv32_set_chars(uv32_t *view, uc32_t *chars) {
    assert(uv32_valid_p(view) && chars);

    view->chars = chars;

    if (!chars)
        view->len = 0;
}

bool uv32_valid_p(const uv32_t *view) {
    return view && uv32_valid(*view);
}

bool uv32_valid(uv32_t view) {
    return  view.chars
        || !view.chars && !view.len;
}