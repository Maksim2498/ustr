#include "view.h"

#include <assert.h>

#include "cstr.h"
#include "cview.h"
#include "str.h"

uv32_t uv32_from_us32(us32_t *str) {
    assert(us32_valid(str));

    return (uv32_t) {
        .chars = str->chars,
        .len   = str->len
    };
}

uv32_t uv32_from_us32_range(us32_t *str, size_t from, size_t len) {
    assert(us32_valid(str)
        && from < str->len
        && str->len >= from + len);

    return (uv32_t) {
        .chars = str->chars + from,
        .len   = len
    };
}

uv32_t uv32_from_uv32_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_valid(view)
        && from < view.len
        && view.len >= from + len);

    return (uv32_t) {
        .chars = view.chars + from,
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

uv32_t uv32_from_uz32_n(uc32_t *cstr, size_t n) {
    assert(cstr);

    return (uv32_t) {
        .chars = cstr,
        .len   = n
    };
}

uc32_t uv32_uc32(uv32_t view, size_t index) {
    assert(uv32_bounds(view, index));
    return view.chars[index];
}

void uv32_set_uc32(uv32_t view, uc32_t c, size_t index) {
    assert(uv32_bounds(view, index));
    view.chars[index] = c;
}

int uv32_cmp(uv32_t lhs, uv32_t rhs) {
    assert(uv32_valid(lhs) && uv32_valid(rhs));
    return uz32_cmp_nn(lhs.chars, lhs.len, rhs.chars, rhs.len);
}

int uv32_cmp_n(uv32_t lhs, uv32_t rhs, size_t n) {
    assert(uv32_valid(lhs)
        && uv32_valid(rhs)
        && lhs.len >= n
        && rhs.len >= n);
        
    return uz32_cmp_n(lhs.chars, rhs.chars, n);
}

int uv32_cmp_ucv32(uv32_t lhs, ucv32_t rhs) {
    assert(uv32_valid(lhs) && ucv32_valid(rhs));
    return uz32_cmp_nn(lhs.chars, lhs.len, rhs.chars, rhs.len);
}

int uv32_cmp_ucv32_n(uv32_t lhs, ucv32_t rhs, size_t n) {
    assert(uv32_valid(lhs)
        && ucv32_valid(rhs)
        && lhs.len >= n
        && rhs.len >= n);

    return uz32_cmp_n(lhs.chars, rhs.chars, n);
}

int uv32_cmp_us32(uv32_t lhs, const us32_t *rhs) {
    assert(uv32_valid(lhs) && us32_valid(rhs));
    return uz32_cmp_nn(lhs.chars, lhs.len, rhs->chars, rhs->len);
}

int uv32_cmp_us32_n(uv32_t lhs, const us32_t *rhs, size_t n) {
    assert(uv32_valid(lhs)
        && us32_valid(rhs)
        && lhs.len >= n
        && rhs->len >= n);

    return uz32_cmp_n(lhs.chars, rhs->chars, n);
}

int uv32_cmp_uz32(uv32_t lhs, const uc32_t *rhs) {
    assert(uv32_valid(lhs) && rhs);
    return uz32_cmp_nn(lhs.chars, lhs.len, rhs, uz32_len(rhs));
}

int uv32_cmp_uz32_n(uv32_t lhs, const uc32_t *rhs, size_t n) {
    assert(uv32_valid(lhs)
        && rhs
        && lhs.len >= n);

    return uz32_cmp_n(lhs.chars, rhs, n);
}

ptrdiff_t uv32_pos(uv32_t view, uv32_t another) {
    assert(uv32_valid(view) && uv32_valid(another));
    return uz32_n_pos_n(view.chars, view.len, another.chars, another.len);
}

ptrdiff_t uv32_pos_from(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && uv32_valid(another));
    return uz32_n_pos_n(view.chars + from, view.len - from, another.chars, another.len);
}

ptrdiff_t uv32_uc32_pos(uv32_t view, uc32_t c) {
    assert(uv32_valid(view));
    return uz32_n_c32_pos(view.chars, view.len, c);
}

ptrdiff_t uv32_uc32_pos_from(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_bounds(view, from));
    return uz32_n_c32_pos(view.chars + from, view.len - from, c);
}

ptrdiff_t uv32_uz32_pos(uv32_t view, const uc32_t *cstr) {
    assert(uv32_valid(view) && cstr);
    return uz32_n_pos(view.chars, view.len, cstr);
}

ptrdiff_t uv32_uz32_pos_from(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    return uz32_n_pos(view.chars + from, view.len - from, cstr);
}

ptrdiff_t uv32_uz32_n_pos(uv32_t view, const uc32_t *cstr, size_t n) {
    assert(uv32_valid(view) && cstr);
    return uz32_n_pos_n(view.chars, view.len, cstr, n);
}

ptrdiff_t uv32_uz32_n_pos_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    return uz32_n_pos_n(view.chars + from, view.len - from, cstr, n);
}

ptrdiff_t uv32_ucv32_pos(uv32_t view, ucv32_t another) {
    assert(uv32_valid(view) && ucv32_valid(another));
    return uz32_n_pos_n(view.chars, view.len, another.chars, another.len);
}

ptrdiff_t uv32_ucv32_pos_from(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && ucv32_valid(another));
    return uz32_n_pos_n(view.chars + from, view.len - from, another.chars, another.len);
}

ptrdiff_t uv32_us32_pos(uv32_t view, const us32_t *str) {
    assert(uv32_valid(view) && us32_valid(str));
    return uz32_n_pos_n(view.chars, view.len, str->chars, str->len);
}

ptrdiff_t uv32_us32_pos_from(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_bounds(view, from) && us32_valid(str));
    return uz32_n_pos_n(view.chars + from, view.len - from, str->chars, str->len);
}

ptrdiff_t uv32_pos_r(uv32_t view, uv32_t another) {
    assert(uv32_valid(view) && uv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, view.len - 1);
}

ptrdiff_t uv32_pos_from_r(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && uv32_valid(another));
    return uz32_n_pos_n_r(view.chars + from, view.len - from, another.chars, another.len, from);
}

ptrdiff_t uv32_uc32_pos_r(uv32_t view, uc32_t c) {
    assert(uv32_valid(view));
    return uz32_n_c32_pos_r(view.chars, view.len, c, view.len - 1);
}

ptrdiff_t uv32_uc32_pos_from_r(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_bounds(view, from));
    return uz32_n_c32_pos_r(view.chars, view.len, c, from);
}

ptrdiff_t uv32_uz32_pos_r(uv32_t view, const uc32_t *cstr) {
    assert(uv32_valid(view) && cstr);
    return uz32_n_pos_r(view.chars, view.len, cstr, view.len - 1);
}

ptrdiff_t uv32_uz32_pos_from_r(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    return uz32_n_pos_r(view.chars, view.len, cstr, from);
}

ptrdiff_t uv32_uz32_n_pos_r(uv32_t view, const uc32_t *cstr, size_t n) {
    assert(uv32_valid(view) && cstr);
    return uz32_n_pos_n_r(view.chars, view.len, cstr, n, view.len - 1);
}

ptrdiff_t uv32_uz32_n_pos_from_r(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    return uz32_n_pos_n_r(view.chars, view.len, cstr, n, from);
}

ptrdiff_t uv32_ucv32_pos_r(uv32_t view, ucv32_t another) {
    assert(uv32_valid(view) && ucv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, view.len - 1);
}

ptrdiff_t uv32_ucv32_pos_from_r(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && ucv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, from);
}

ptrdiff_t uv32_us32_pos_r(uv32_t view, const us32_t *str) {
    assert(uv32_valid(view) && us32_valid(str));
    return uz32_n_pos_n_r(view.chars, view.len, str->chars, str->len, view.len - 1);
}

ptrdiff_t uv32_us32_pos_from_r(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_bounds(view, from) && us32_valid(str));
    return uz32_n_pos_n_r(view.chars, view.len, str->chars, str->len, from);
}

void uv32_fill(uv32_t view, uc32_t c) {
    assert(uv32_valid(view));
    uz32_n_fill(view.chars, view.len, c);
}

void uv32_fill_from(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_bounds(view, from));
    uz32_n_fill(view.chars + from, view.len - from, c);
}

void uv32_fill_from_r(uv32_t view, uc32_t c, size_t from) {
    assert(uv32_bounds(view, from));
    uz32_n_fill(view.chars, from + 1, c);
}

void uv32_fill_range(uv32_t view, uc32_t c, size_t from, size_t len) {
    assert(uv32_bounds(view, from) && view.len >= from + len);
    uz32_n_fill(view.chars + from, len, c);
}

void uv32_fill_uz32(uv32_t view, const uc32_t *cstr) {
    assert(uv32_valid(view) && cstr);
    uz32_n_fill_uz32(view.chars, view.len, cstr);
}

void uv32_fill_uz32_from(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    uz32_n_fill_uz32(view.chars + from, view.len - from, cstr);
}

void uv32_fill_uz32_from_r(uv32_t view, const uc32_t *cstr, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    uz32_n_fill_uz32(view.chars, from + 1, cstr);
}

void uv32_fill_uz32_range(uv32_t view, const uc32_t *cstr, size_t from, size_t len) {
    assert(uv32_bounds(view, from)
        && cstr
        && view.len >= from + len);
        
    uz32_n_fill_uz32(view.chars + from, len, cstr);
}

void uv32_fill_uz32_n(uv32_t view, const uc32_t *cstr, size_t n) {
    assert(uv32_valid(view) && cstr);
    uz32_n_fill_uz32_n(view.chars, view.len, cstr, n);
}

void uv32_fill_uz32_n_from(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    uz32_n_fill_uz32_n(view.chars + from, view.len - from, cstr, n);
}

void uv32_fill_uz32_n_from_r(uv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(uv32_bounds(view, from) && cstr);
    uz32_n_fill_uz32_n(view.chars, from + 1, cstr, n);
}

void uv32_fill_uz32_n_range(uv32_t view, const uc32_t *cstr, size_t n, size_t from, size_t len) {
    assert(uv32_bounds(view, from)
        && cstr
        && view.len >= from + len);
    
    uz32_n_fill_uz32_n(view.chars + from, len, cstr, n);
}

void uv32_fill_uv32(uv32_t view, uv32_t another) {
    assert(uv32_valid(view) && uv32_valid(another));
    uz32_n_fill_uz32_n(view.chars, view.len, another.chars, another.len);
}

void uv32_fill_uv32_from(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && uv32_valid(another));
    uz32_n_fill_uz32_n(view.chars + from, view.len - from, another.chars, another.len);
}

void uv32_fill_uv32_from_r(uv32_t view, uv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && uv32_valid(another));
    uz32_n_fill_uz32_n(view.chars, from + 1, another.chars, another.len);
}

void uv32_fill_uv32_range(uv32_t view, uv32_t another, size_t from, size_t len) {
    assert(uv32_bounds(view, from)
        && uv32_valid(another)
        && view.len >= from + len);

    uz32_n_fill_uz32_n(view.chars + from, len, another.chars, another.len);
}

void uv32_fill_ucv32(uv32_t view, ucv32_t another) {
    assert(uv32_valid(view) && ucv32_valid(another));
    uz32_n_fill_uz32_n(view.chars, view.len, another.chars, another.len);
}

void uv32_fill_ucv32_from(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && ucv32_valid(another));
    uz32_n_fill_uz32_n(view.chars + from, view.len - from, another.chars, another.len);
}

void uv32_fill_ucv32_from_r(uv32_t view, ucv32_t another, size_t from) {
    assert(uv32_bounds(view, from) && ucv32_valid(another));
    uz32_n_fill_uz32_n(view.chars, from + 1, another.chars, another.len);
}

void uv32_fill_ucv32_range(uv32_t view, ucv32_t another, size_t from, size_t len) {
    assert(uv32_bounds(view, from)
        && ucv32_valid(another)
        && view.len >= from + len);
    
    uz32_n_fill_uz32_n(view.chars + from, len, another.chars, another.len);
}

void uv32_fill_us32(uv32_t view, const us32_t *str) {
    assert(uv32_valid(view) && us32_valid(str));
    uz32_n_fill_uz32_n(view.chars, view.len, str->chars, str->len);
}

void uv32_fill_us32_from(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_bounds(view, from) && us32_valid(str));
    uz32_n_fill_uz32_n(view.chars + from, view.len - from, str->chars, str->len);
}

void uv32_fill_us32_from_r(uv32_t view, const us32_t *str, size_t from) {
    assert(uv32_bounds(view, from) && us32_valid(str));
    uz32_n_fill_uz32_n(view.chars, from + 1, str->chars, str->len);
}

void uv32_fill_us32_range(uv32_t view, const us32_t *str, size_t from, size_t len) {
    assert(uv32_bounds(view, from)
        && us32_valid(str)
        && view.len >= from + len);

    return uz32_n_fill_uz32_n(view.chars + from, len, str->chars, str->len);
}

void uv32_to_upper(uv32_t view) {
    assert(uv32_valid(view));
    uz32_to_upper_n(view.chars, view.len);
}

void uv32_to_lower(uv32_t view) {
    assert(uv32_valid(view));
    uz32_to_lower_n(view.chars, view.len);
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

uc32_t *uv32_at(uv32_t view, size_t index) {
    assert(uv32_valid(view) && index <= view.len);
    return view.chars + index;
}

const uc32_t *uv32_cat(uv32_t view, size_t index) {
    assert(uv32_valid(view) && index <= view.len);
    return view.chars + index;
}

bool uv32_bounds(uv32_t view, size_t index) {
    assert(uv32_valid(view));
    return index < view.len;
}

size_t uv32_len(uv32_t view) {
    assert(uv32_valid(view));
    return view.len;
}

bool uv32_empty(uv32_t view) {
    assert(uv32_valid(view));
    return !view.len;
}

bool uv32_valid(uv32_t view) {
    return (bool) view.chars == (bool) view.len;
}