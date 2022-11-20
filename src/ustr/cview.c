#include "cview.h"

#include <assert.h>

#include "cstr.h"
#include "str.h"
#include "view.h"

ucv32_t ucv32_mk(void) {
    return (ucv32_t) {
        .chars = NULL,
        .len   = 0
    };
}

ucv32_t ucv32_from_us32(const us32_t *str) {
    assert(us32_valid(str));

    return (ucv32_t) {
        .chars = str->chars,
        .len   = str->len
    };
}

ucv32_t ucv32_from_us32_range(const us32_t *str, size_t from, size_t len) {
    assert(us32_valid(str)
        && from < str->len
        && str->len >= from + len);

    return (ucv32_t) {
        .chars = str->chars + from,
        .len   = len
    };
}

ucv32_t ucv32_from_uv32(uv32_t view) {
    assert(uv32_valid(view));

    return (ucv32_t) {
        .chars = view.chars,
        .len   = view.len
    };
}

ucv32_t ucv32_from_uv32_range(uv32_t view, size_t from, size_t len) {
    assert(uv32_bounds(view, from) && uv32_ebounds(view, from + len));

    return (ucv32_t) {
        .chars = view.chars + from,
        .len   = len
    };
}

ucv32_t ucv32_from_uz32(const uc32_t *cstr) {
    assert(cstr);

    return (ucv32_t) {
        .chars = cstr,
        .len   = uz32_len(cstr)
    };
}

ucv32_t ucv32_from_uz32_n(const uc32_t *cstr, size_t n) {
    assert(cstr);

    return (ucv32_t) {
        .chars = cstr,
        .len   = n
    };
}

size_t ucv32_trim_right(ucv32_t *view) {
    assert(view && ucv32_valid(*view));
    return view->len = uz32_n_trim_right(view->chars, view->len);
}

uc32_t ucv32_uc32(ucv32_t view, size_t index) {
    assert(ucv32_bounds(view, index));
    return view.chars[index];
}

int ucv32_cmp(ucv32_t lhs, ucv32_t rhs) {
    assert(ucv32_valid(lhs) && ucv32_valid(rhs));
    return uz32_n_cmp_n(lhs.chars, lhs.len, rhs.chars, rhs.len);
}

int ucv32_cmp_n(ucv32_t lhs, ucv32_t rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n) && ucv32_ebounds(rhs, n));
    return uz32_n_cmp_n(lhs.chars, n, rhs.chars, n);
}

int ucv32_cmp_uv32(ucv32_t lhs, uv32_t rhs) {
    assert(ucv32_valid(lhs) && uv32_valid(rhs));
    return uz32_n_cmp_n(lhs.chars, lhs.len, rhs.chars, rhs.len);
}

int ucv32_cmp_uv32_n(ucv32_t lhs, uv32_t rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n) && uv32_ebounds(rhs, n));
    return uz32_n_cmp_n(lhs.chars, n, rhs.chars, n);
}

int ucv32_cmp_us32(ucv32_t lhs, const us32_t *rhs) {
    assert(ucv32_valid(lhs) && us32_valid(rhs));
    return uz32_n_cmp_n(lhs.chars, lhs.len, rhs->chars, rhs->len);
}

int ucv32_cmp_us32_n(ucv32_t lhs, const us32_t *rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n) && us32_ebounds(rhs, n));
    return uz32_n_cmp_n(lhs.chars, n, rhs->chars, n);
}

int ucv32_cmp_uz32(ucv32_t lhs, const uc32_t *rhs) {
    assert(ucv32_valid(lhs));
    return uz32_n_cmp(lhs.chars, lhs.len, rhs);
}

int ucv32_cmp_uz32_n(ucv32_t lhs, const uc32_t *rhs, size_t n) {
    assert(ucv32_valid(lhs) && rhs);
    return uz32_n_cmp_n(lhs.chars, lhs.len, rhs, n);
}

ptrdiff_t ucv32_pos(ucv32_t view, ucv32_t another) {
    assert(ucv32_valid(view) && ucv32_valid(another));
    return uz32_n_pos_n(view.chars, view.len, another.chars, another.len);
}

ptrdiff_t ucv32_pos_from(ucv32_t view, ucv32_t another, size_t from) {
    assert(ucv32_bounds(view, from) && ucv32_valid(another));
    return uz32_n_pos_n(view.chars + from, view.len - from, another.chars, another.len);
}

ptrdiff_t ucv32_uc32_pos(ucv32_t view, uc32_t c) {
    assert(ucv32_valid(view));
    return uz32_n_uc32_pos(view.chars, view.len, c);
}

ptrdiff_t ucv32_uc32_pos_from(ucv32_t view, uc32_t c, size_t from) {
    assert(ucv32_bounds(view, from));
    return uz32_n_uc32_pos(view.chars + from, view.len - from, c);
}

ptrdiff_t ucv32_uz32_pos(ucv32_t view, const uc32_t *cstr) {
    assert(ucv32_valid(view) && cstr);
    return uz32_n_pos(view.chars, view.len, cstr);
}

ptrdiff_t ucv32_uz32_pos_from(ucv32_t view, const uc32_t *cstr, size_t from) {
    assert(ucv32_bounds(view, from) && cstr);
    return uz32_n_pos(view.chars + from, view.len - from, cstr);
}

ptrdiff_t ucv32_uz32_n_pos(ucv32_t view, const uc32_t *cstr, size_t n) {
    assert(ucv32_valid(view) && cstr);
    return uz32_n_pos_n(view.chars, view.len, cstr, n);
}

ptrdiff_t ucv32_uz32_n_pos_from(ucv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(ucv32_bounds(view, from) && cstr);
    return uz32_n_pos_n(view.chars + from, view.len - from, cstr, n);
}

ptrdiff_t ucv32_uv32_pos(ucv32_t view, uv32_t another) {
    assert(ucv32_valid(view) && uv32_valid(another));
    return uz32_n_pos_n(view.chars, view.len, another.chars, another.len);
}

ptrdiff_t ucv32_uv32_pos_from(ucv32_t view, uv32_t another, size_t from) {
    assert(ucv32_bounds(view, from) && uv32_valid(another));
    return uz32_n_pos_n(view.chars + from, view.len - from, another.chars, another.len);
}

ptrdiff_t ucv32_us32_pos(ucv32_t view, const us32_t *str) {
    assert(ucv32_valid(view) && us32_valid(str));
    return uz32_n_pos_n(view.chars, view.len, str->chars, str->len);
}

ptrdiff_t ucv32_us32_pos_from(ucv32_t view, const us32_t *str, size_t from) {
    assert(ucv32_bounds(view, from) && us32_valid(str));
    return uz32_n_pos_n(view.chars + from, view.len - from, str->chars, str->len);
}

ptrdiff_t ucv32_pos_r(ucv32_t view, ucv32_t another) {
    assert(ucv32_valid(view) && ucv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, view.len - 1);
}

ptrdiff_t ucv32_pos_from_r(ucv32_t view, ucv32_t another, size_t from) {
    assert(ucv32_bounds(view, from) && ucv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, from);
}

ptrdiff_t ucv32_uc32_pos_r(ucv32_t view, uc32_t c) {
    assert(ucv32_valid(view));
    return uz32_n_uc32_pos_r(view.chars, view.len, c, view.len - 1);
}

ptrdiff_t ucv32_uc32_pos_from_r(ucv32_t view, uc32_t c, size_t from) {
    assert(ucv32_bounds(view, from));
    return uz32_n_uc32_pos_r(view.chars, view.len, c, from);
}

ptrdiff_t ucv32_uz32_pos_r(ucv32_t view, const uc32_t *cstr) {
    assert(ucv32_valid(view) && cstr);
    return uz32_n_pos_r(view.chars, view.len, cstr, view.len - 1);
}

ptrdiff_t ucv32_uz32_pos_from_r(ucv32_t view, const uc32_t *cstr, size_t from) {
    assert(ucv32_bounds(view, from) && cstr);
    return uz32_n_pos_r(view.chars, view.len, cstr, from);
}

ptrdiff_t ucv32_uz32_n_pos_r(ucv32_t view, const uc32_t *cstr, size_t n) {
    assert(ucv32_valid(view) && cstr);
    return uz32_n_pos_n_r(view.chars, view.len, cstr, n, view.len - 1);
}

ptrdiff_t ucv32_uz32_n_pos_from_r(ucv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(ucv32_bounds(view, from) && cstr);
    return uz32_n_pos_n_r(view.chars, view.len, cstr, n, from);
}

ptrdiff_t ucv32_uv32_pos_r(ucv32_t view, uv32_t another) {
    assert(ucv32_valid(view) && uv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, view.len - 1);
}

ptrdiff_t ucv32_uv32_pos_from_r(ucv32_t view, uv32_t another, size_t from) {
    assert(ucv32_bounds(view, from) && uv32_valid(another));
    return uz32_n_pos_n_r(view.chars, view.len, another.chars, another.len, from);
}

ptrdiff_t ucv32_us32_pos_r(ucv32_t view, const us32_t *str) {
    assert(ucv32_valid(view) && us32_valid(str));
    return uz32_n_pos_n_r(view.chars, view.len, str->chars, str->len, view.len - 1);
}

ptrdiff_t ucv32_us32_pos_from_r(ucv32_t view, const us32_t *str, size_t from) {
    assert(ucv32_bounds(view, from) && us32_valid(str));
    return uz32_n_pos_n_r(view.chars, view.len, str->chars, str->len, from);
}

const uc32_t *ucv32_cbegin(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.chars;
}

const uc32_t *ucv32_cend(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.chars + view.len;
}

const uc32_t *ucv32_cat(ucv32_t view, size_t index) {
    assert(ucv32_ebounds(view, index));
    return view.chars + index;
}

bool ucv32_bounds(ucv32_t view, size_t index) {
    assert(ucv32_valid(view));
    return index < view.len;
}

bool ucv32_ebounds(ucv32_t view, size_t index) {
    assert(ucv32_valid(view));
    return index <= view.len;
}

size_t ucv32_len(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.len;
}

bool ucv32_empty(ucv32_t view) {
    assert(ucv32_valid(view));
    return !view.len;
}

size_t ucv32_new_csplit(ucv32_t view, uc32_t c, ucv32_t **array) {
    assert(ucv32_valid(view));
    return uz32_n_new_csplit(view.chars, view.len, c, array);
}

size_t ucv32_new_csplit_e(ucv32_t view, uc32_t c, ucv32_t **array, bool *error) {
    assert(ucv32_valid(view));
    return uz32_n_new_csplit_e(view.chars, view.len, c, array, error);
}

size_t ucv32_csplit(ucv32_t view, uc32_t c, ucv32_t *array, size_t array_len) {
    assert(ucv32_valid(view));
    return uz32_n_csplit(view.chars, view.len, c, array, array_len);
}

bool ucv32_valid(ucv32_t view) {
    return  view.chars
        || !view.chars && !view.len;
}