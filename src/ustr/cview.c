#include "cview.h"

#include <assert.h>

#include "fmt/case.h"
#include "cstr.h"
#include "str.h"
#include "view.h"

ucv32_t ucv32_mk(void) {
    return (ucv32_t) {
        .chars = NULL,
        .len   = 0
    };
}

ucv32_t ucv32_from_range(ucv32_t view, size_t from, size_t len) {
    return ucv32_from_ucv32_range(view, from, len);
}

ucv32_t ucv32_from_ucv32_range(ucv32_t view, size_t from, size_t len) {
    assert(ucv32_ebounds_range(view, from, len));
    
    return (ucv32_t) {
        .chars = view.chars + from,
        .len   = len
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
    assert(us32_ebounds_range(str, from, len));

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
    assert(uv32_ebounds_range(view, from, len));

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

ucv32_t ucv32_from_uz32n(const uc32_t *cstr, size_t n) {
    assert(cstr);

    return (ucv32_t) {
        .chars = cstr,
        .len   = n
    };
}

ucv32_t ucv32_from_bool(bool b) {
    return ucv32_from_lower_bool(b);
}

ucv32_t ucv32_from_case_bool(bool b, ucase_t c) {
    return ucase_upper(c) ? ucv32_from_upper_bool(b) : ucv32_from_lower_bool(b);
}

ucv32_t ucv32_from_upper_bool(bool b) {
    return b ? ucv32("TRUE") : ucv32("FALSE");
}

ucv32_t ucv32_from_lower_bool(bool b) {
    return b ? ucv32("true") : ucv32("false");
}

size_t ucv32_len_n_from(ucv32_t view, unsigned n, size_t from) {
    switch (n) {
        case 1:
            return ucv32_len_8_from(view, from);

        case 2:
            return ucv32_len_16_from(view, from);

        case 4:
            return ucv32_len_32_from(view, from);

        default:
            assert(false);
            return 0;
    }
}

size_t ucv32_len_32_from(ucv32_t view, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_len_32(ucv32_cchars(view) + from, view.len - from);
}

size_t ucv32_len_16_from(ucv32_t view, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_len_16(ucv32_cchars(view) + from, view.len - from);
}

size_t ucv32_len_8_from(ucv32_t view, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_len_8(ucv32_cchars(view) + from, view.len - from);
}

size_t ucv32_len_n_to(ucv32_t view, unsigned n, size_t to) {
    switch (n) {
        case 1:
            return ucv32_len_8_to(view, to);

        case 2:
            return ucv32_len_16_to(view, to);

        case 4:
            return ucv32_len_32_to(view, to);

        default:
            assert(false);
            return 0;
    }
}

size_t ucv32_len_32_to(ucv32_t view, size_t to) {
    assert(ucv32_ebounds(view, to));
    return uz32n_len_32(ucv32_cchars(view), to);
}

size_t ucv32_len_16_to(ucv32_t view, size_t to) {
    assert(ucv32_ebounds(view, to));
    return uz32n_len_16(ucv32_cchars(view), to);
}

size_t ucv32_len_8_to(ucv32_t view, size_t to) {
    assert(ucv32_ebounds(view, to));
    return uz32n_len_8(ucv32_cchars(view), to);
}

size_t ucv32_len_n_range(ucv32_t view, unsigned n, size_t from, size_t len) {
    switch (n) {
        case 1:
            return ucv32_len_8_range(view, from, len);

        case 2:
            return ucv32_len_16_range(view, from, len);

        case 4:
            return ucv32_len_32_range(view, from, len);

        default:
            assert(false);
            return 0;
    }
}

size_t ucv32_len_32_range(ucv32_t view, size_t from, size_t len) {
    assert(ucv32_ebounds_range(view,from, len));
    return uz32n_len_32(ucv32_cchars(view) + from, len);
}

size_t ucv32_len_16_range(ucv32_t view, size_t from, size_t len) {
    assert(ucv32_ebounds_range(view,from, len));
    return uz32n_len_16(ucv32_cchars(view) + from, len);
}

size_t ucv32_len_8_range(ucv32_t view, size_t from, size_t len) {
    assert(ucv32_ebounds_range(view, from, len));
    return uz32n_len_8(ucv32_cchars(view) + from, len);
}

size_t ucv32_len_n(ucv32_t view, unsigned n) {
    return uz32n_len_n(UCV32_CEXPAND(view), n);
}

size_t ucv32_len_32(ucv32_t view) {
    return ucv32_len(view);
}

size_t ucv32_len_16(ucv32_t view) {
    return uz32n_len_16(UCV32_CEXPAND(view));
}

size_t ucv32_len_8(ucv32_t view) {
    return uz32n_len_8(UCV32_CEXPAND(view));
}

size_t ucv32_rtrim(ucv32_t *view) {
    assert(view);
    return view->len = uz32n_rtrim(UCV32_CEXPAND(*view));
}

uc32_t ucv32_at(ucv32_t view, size_t index) {
    assert(ucv32_bounds(view, index));
    return view.chars[index];
}

int ucv32_cmp(ucv32_t lhs, ucv32_t rhs) {
    return ucv32_cmp_ucv32(lhs, rhs);
}

int ucv32_cmp_n(ucv32_t lhs, ucv32_t rhs, size_t n) {
    return ucv32_cmp_ucv32_n(lhs, rhs, n);
}

int ucv32_cmp_ucv32(ucv32_t lhs, ucv32_t rhs) {
    return uz32n_cmp_n(UCV32_CEXPAND(lhs), UCV32_CEXPAND(rhs));
}

int ucv32_cmp_ucv32_n(ucv32_t lhs, ucv32_t rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n) && ucv32_ebounds(rhs, n));
    return uz32n_cmp_n(ucv32_cchars(lhs), n, ucv32_cchars(rhs), n);
}

int ucv32_cmp_uv32(ucv32_t lhs, uv32_t rhs) {
    return uz32n_cmp_n(UCV32_CEXPAND(lhs), UV32_EXPAND(rhs));
}

int ucv32_cmp_uv32_n(ucv32_t lhs, uv32_t rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n) && uv32_ebounds(rhs, n));
    return uz32n_cmp_n(ucv32_cchars(lhs), n, uv32_chars(rhs), n);
}

int ucv32_cmp_us32(ucv32_t lhs, const us32_t *rhs) {
    return uz32n_cmp_n(UCV32_CEXPAND(lhs), US32_CEXPAND(rhs));
}

int ucv32_cmp_us32_n(ucv32_t lhs, const us32_t *rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n) && us32_ebounds(rhs, n));
    return uz32n_cmp_n(ucv32_cchars(lhs), n, us32_cchars(rhs), n);
}

int ucv32_cmp_uz32(ucv32_t lhs, const uc32_t *rhs) {
    return uz32n_cmp(UCV32_CEXPAND(lhs), rhs);
}

int ucv32_cmp_uz32_n(ucv32_t lhs, const uc32_t *rhs, size_t n) {
    assert(ucv32_ebounds(lhs, n));
    return uz32n_cmp_n(lhs.chars, n, rhs, n);
}

int ucv32_cmp_uz32n(ucv32_t lhs, const uc32_t *rhs, size_t n) {
    return uz32n_cmp_n(UCV32_CEXPAND(lhs), rhs, n);
}

int ucv32_cmp_uz32n_n(ucv32_t lhs, const uc32_t *rhs, size_t rhs_len, size_t n) {
    assert(ucv32_ebounds(lhs, n) && rhs_len <= n);
    return uz32_cmp_n(lhs.chars, rhs, n);
}

ptrdiff_t ucv32_pos(ucv32_t view, ucv32_t another) {
    return ucv32_pos_ucv32(view, another);
}

ptrdiff_t ucv32_pos_from(ucv32_t view, ucv32_t another, size_t from) {
    return ucv32_pos_ucv32_from(view, another, from);
}

ptrdiff_t ucv32_pos_ucv32(ucv32_t view, ucv32_t another) {
    return uz32n_pos_uz32n(UCV32_CEXPAND(view), UCV32_CEXPAND(another));
}

ptrdiff_t ucv32_pos_ucv32_from(ucv32_t view, ucv32_t another, size_t from) {
    assert(ucv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(ucv32_cchars(view) + from, view.len - from, UCV32_CEXPAND(another));
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t ucv32_pos_uc32(ucv32_t view, uc32_t c) {
    return uz32n_pos_uc32(UCV32_CEXPAND(view), c);
}

ptrdiff_t ucv32_pos_uc32_from(ucv32_t view, uc32_t c, size_t from) {
    assert(ucv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uc32(ucv32_cchars(view) + from, view.len - from, c);
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t ucv32_pos_uz32(ucv32_t view, const uc32_t *cstr) {
    return uz32n_pos_uz32(UCV32_CEXPAND(view), cstr);
}

ptrdiff_t ucv32_pos_uz32_from(ucv32_t view, const uc32_t *cstr, size_t from) {
    assert(ucv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32(ucv32_cchars(view) + from, view.len - from, cstr);
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t ucv32_pos_uz32n(ucv32_t view, const uc32_t *cstr, size_t n) {
    return uz32n_pos_uz32n(UCV32_CEXPAND(view), cstr, n);
}

ptrdiff_t ucv32_pos_uz32n_from(ucv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(ucv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(ucv32_cchars(view) + from, view.len - from, cstr, n);
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t ucv32_pos_uv32(ucv32_t view, uv32_t another) {
    return uz32n_pos_uz32n(UCV32_CEXPAND(view), UV32_EXPAND(another));
}

ptrdiff_t ucv32_pos_uv32_from(ucv32_t view, uv32_t another, size_t from) {
    assert(ucv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(ucv32_cchars(view) + from, view.len - from, UV32_EXPAND(another));
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t ucv32_pos_us32(ucv32_t view, const us32_t *str) {
    return uz32n_pos_uz32n(UCV32_CEXPAND(view), US32_CEXPAND(str));
}

ptrdiff_t ucv32_pos_us32_from(ucv32_t view, const us32_t *str, size_t from) {
    assert(ucv32_ebounds(view, from));
    ptrdiff_t pos = uz32n_pos_uz32n(ucv32_cchars(view) + from, view.len - from, US32_CEXPAND(str));
    return pos < 0 ? pos : pos + from;
}

ptrdiff_t ucv32_rpos(ucv32_t view, ucv32_t another) {
    return ucv32_rpos_ucv32(view, another);
}

ptrdiff_t ucv32_rpos_from(ucv32_t view, ucv32_t another, size_t from) {
    return ucv32_rpos_ucv32_from(view, another, from);
}

ptrdiff_t ucv32_rpos_ucv32(ucv32_t view, ucv32_t another) {
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), UCV32_CEXPAND(another), view.len - 1);
}

ptrdiff_t ucv32_rpos_ucv32_from(ucv32_t view, ucv32_t another, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), UCV32_CEXPAND(another), from);
}

ptrdiff_t ucv32_rpos_uc32(ucv32_t view, uc32_t c) {
    return uz32n_rpos_uc32(UCV32_CEXPAND(view), c, view.len - 1);
}

ptrdiff_t ucv32_rpos_uc32_from(ucv32_t view, uc32_t c, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_rpos_uc32(UCV32_CEXPAND(view), c, from);
}

ptrdiff_t ucv32_rpos_uz32(ucv32_t view, const uc32_t *cstr) {
    return uz32n_rpos_uz32(UCV32_CEXPAND(view), cstr, view.len - 1);
}

ptrdiff_t ucv32_rpos_uz32_from(ucv32_t view, const uc32_t *cstr, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_rpos_uz32(UCV32_CEXPAND(view), cstr, from);
}

ptrdiff_t ucv32_rpos_uz32n(ucv32_t view, const uc32_t *cstr, size_t n) {
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), cstr, n, view.len - 1);
}

ptrdiff_t ucv32_rpos_uz32n_from(ucv32_t view, const uc32_t *cstr, size_t n, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), cstr, n, from);
}

ptrdiff_t ucv32_rpos_uv32(ucv32_t view, uv32_t another) {
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), UV32_EXPAND(another), view.len - 1);
}

ptrdiff_t ucv32_rpos_uv32_from(ucv32_t view, uv32_t another, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), UV32_EXPAND(another), from);
}

ptrdiff_t ucv32_rpos_us32(ucv32_t view, const us32_t *str) {
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), US32_CEXPAND(str), view.len - 1);
}

ptrdiff_t ucv32_rpos_us32_from(ucv32_t view, const us32_t *str, size_t from) {
    assert(ucv32_ebounds(view, from));
    return uz32n_rpos_uz32n(UCV32_CEXPAND(view), US32_CEXPAND(str), from);
}

const uc32_t *ucv32_cbegin(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.chars;
}

const uc32_t *ucv32_cend(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.chars + view.len;
}

const uc32_t *ucv32_coffset(ucv32_t view, size_t index) {
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

bool ucv32_bounds_range(ucv32_t view, size_t from, size_t len) {
    assert(ucv32_valid(view));
    return from < view.len && from + len < view.len;
}

bool ucv32_ebounds_range(ucv32_t view, size_t from, size_t len) {
    assert(ucv32_valid(view));
    return from <= view.len && from + len <= view.len;
}

size_t ucv32_len(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.len;
}

size_t ucv32_add_len(ucv32_t *view, ptrdiff_t delta) {
    assert(ucv32_valid_p(view) && -(ptrdiff_t) view->len <= delta);
    return view->len += delta;
}

void ucv32_set_len(ucv32_t *view, size_t len) {
    assert(ucv32_valid_p(view) && (!len || view->chars));
    view->len = len;
}

bool ucv32_empty(ucv32_t view) {
    assert(ucv32_valid(view));
    return !view.len;
}

size_t ucv32_new_csplit(ucv32_t view, ucv32_t another, ucv32_t **array) {
    return ucv32_new_csplit_ucv32(view, another, array);
}

size_t ucv32_new_csplit_e(ucv32_t view, ucv32_t another, ucv32_t **array, bool *error) {
    return ucv32_new_csplit_ucv32_e(view, another, array, error);
}

size_t ucv32_csplit(ucv32_t view, ucv32_t another, ucv32_t *array, size_t array_len) {
    return ucv32_csplit_ucv32(view, another, array, array_len);
}

size_t ucv32_new_csplit_uc32(ucv32_t view, uc32_t c, ucv32_t **array) {
    return uz32n_new_csplit_uc32(UCV32_CEXPAND(view), c, array);
}

size_t ucv32_new_csplit_uc32_e(ucv32_t view, uc32_t c, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uc32_e(UCV32_CEXPAND(view), c, array, error);
}

size_t ucv32_csplit_uc32(ucv32_t view, uc32_t c, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uc32(UCV32_CEXPAND(view), c, array, array_len);
}

size_t ucv32_new_csplit_uz32(ucv32_t view, const uc32_t *cstr, ucv32_t **array) {
    return uz32n_new_csplit_uz32(UCV32_CEXPAND(view), cstr, array);
}

size_t ucv32_new_csplit_uz32_e(ucv32_t view, const uc32_t *cstr, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32_e(UCV32_CEXPAND(view), cstr, array, error);
}

size_t ucv32_csplit_uz32(ucv32_t view, const uc32_t *cstr, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32(UCV32_CEXPAND(view), cstr, array, array_len);
}

size_t ucv32_new_csplit_uz32n(ucv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UCV32_CEXPAND(view), cstr, n, array);
}

size_t ucv32_new_csplit_uz32n_e(ucv32_t view, const uc32_t *cstr, size_t n, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UCV32_CEXPAND(view), cstr, n, array, error);
}

size_t ucv32_csplit_uz32_n(ucv32_t view, const uc32_t *cstr, size_t n, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UCV32_CEXPAND(view), cstr, n, array, array_len);
}

size_t ucv32_new_csplit_ucv32(ucv32_t view, ucv32_t another, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UCV32_CEXPAND(view), UCV32_CEXPAND(another), array);
}

size_t ucv32_new_csplit_ucv32_e(ucv32_t view, ucv32_t another, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UCV32_CEXPAND(view), UCV32_CEXPAND(another), array, error);
}

size_t ucv32_csplit_ucv32(ucv32_t view, ucv32_t another, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UCV32_CEXPAND(view), UCV32_CEXPAND(another), array, array_len);
}

size_t ucv32_new_csplit_us32(ucv32_t view, const us32_t *str, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UCV32_CEXPAND(view), US32_CEXPAND(str), array);
}

size_t ucv32_new_csplit_us32_e(ucv32_t view, const us32_t *str, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UCV32_CEXPAND(view), US32_CEXPAND(str), array, error);
}

size_t ucv32_csplit_us32(ucv32_t view, const us32_t *str, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UCV32_CEXPAND(view), US32_CEXPAND(str), array, array_len);
}

size_t ucv32_new_csplit_uv32(ucv32_t view, uv32_t another, ucv32_t **array) {
    return uz32n_new_csplit_uz32n(UCV32_CEXPAND(view), UV32_EXPAND(another), array);
}

size_t ucv32_new_csplit_uv32_e(ucv32_t view, uv32_t another, ucv32_t **array, bool *error) {
    return uz32n_new_csplit_uz32n_e(UCV32_CEXPAND(view), UV32_EXPAND(another), array, error);
}

size_t ucv32_csplit_uv32(ucv32_t view, uv32_t another, ucv32_t *array, size_t array_len) {
    return uz32n_csplit_uz32n(UCV32_CEXPAND(view), UV32_EXPAND(another), array, array_len);
}

const uc32_t *ucv32_cchars(ucv32_t view) {
    assert(ucv32_valid(view));
    return view.chars ? view.chars : U"";
}

void ucv32_set_chars(ucv32_t *view, const uc32_t *chars) {
    assert(ucv32_valid_p(view));

    view->chars = chars;

    if (!chars)
        view->len = 0;
}

bool ucv32_valid_p(const ucv32_t *view) {
    return view && ucv32_valid(*view);
}

bool ucv32_valid(ucv32_t view) {
    return  view.chars
        || !view.chars && !view.len;
}