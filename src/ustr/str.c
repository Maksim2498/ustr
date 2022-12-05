#include "str.h"

#include <assert.h>

#include "fmt/int.h"
#include "util/mem.h"
#include "config.h"
#include "cstr.h"
#include "cview.h"
#include "view.h"

us32_t us32_mk(void) {
	return (us32_t) {
		.chars = NULL,
		.len   = 0,
		.cap   = 0
	};
}

us32_t us32_from(us32_t *str) {
	return us32_from_e(str, NULL);
}

us32_t us32_from_e(us32_t *str, bool *error) {
	us32_t res = us32_mk();
	us32_append_e(&res, str, error);
	return res;
}

us32_t us32_from_us32_range(us32_t *str, size_t from, size_t len) {
	return us32_from_us32_range_e(str, from, len, NULL);
}

us32_t us32_from_us32_range_e(us32_t *str, size_t from, size_t len, bool *error) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, str->chars + from, len, error);
	return res;
}

us32_t us32_from_uv32(uv32_t view) {
	return us32_from_uv32_e(view, NULL);
}

us32_t us32_from_uv32_e(uv32_t view, bool *error) {
	us32_t res = us32_mk();
	us32_append_uv32_e(&res, view, error);
	return res;
}

us32_t us32_from_uv32_range(uv32_t view, size_t from, size_t len) {
	return us32_from_uv32_range_e(view, from, len, NULL);
}

us32_t us32_from_uv32_range_e(uv32_t view, size_t from, size_t len, bool *error) {
	assert(uv32_bounds(view, from) && uv32_ebounds(view, from + len));
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, view.chars + from, len, error);
	return res;
}

us32_t us32_from_ucv32(ucv32_t view) {
	return us32_from_ucv32_e(view, NULL);
}

us32_t us32_from_ucv32_e(ucv32_t view, bool *error) {
	us32_t res = us32_mk();
	us32_append_ucv32_e(&res, view, error);
	return res;
}

us32_t us32_from_ucv32_range(ucv32_t view, size_t from, size_t len) {
	return us32_from_ucv32_range_e(view, from, len, NULL);
}

us32_t us32_from_ucv32_range_e(ucv32_t view, size_t from, size_t len, bool *error) {
	assert(ucv32_bounds(view, from) && ucv32_ebounds(view, from + len));
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, view.chars + from, len, error);
	return res;
}

us32_t us32_from_uz32(uc32_t *cstr) {
	return us32_from_uz32_e(cstr, NULL);
}

us32_t us32_from_uz32_e(uc32_t *cstr, bool *error) {
	us32_t res = us32_mk();
	us32_append_uz32_e(&res, cstr, error);
	return res;
}

us32_t us32_from_uz32_n(uc32_t *cstr, size_t n) {
    return us32_from_uz32_n_e(cstr, n, NULL);
}

us32_t us32_from_uz32_n_e(uc32_t *cstr, size_t n, bool *error) {
	us32_t res = us32_mk();
	us32_append_uz32_n_e(&res, cstr, n, error);
	return res;
}

us32_t us32_from_uc32(uc32_t c) {
	return us32_from_uc32_e(c, NULL);
}

us32_t us32_from_uc32_e(uc32_t c, bool *error) {
	us32_t res = us32_mk();
	us32_append_uc32_e(&res, c, error);
	return res;
}

us32_t us32_from_uc32_n(uc32_t c, size_t n) {
	return us32_from_uc32_n_e(c, n, NULL);
}

us32_t us32_from_uc32_n_e(uc32_t c, size_t n, bool *error) {
	us32_t res = us32_mk();
	us32_append_uc32_n_e(&res, c, n, error);
	return res;
}

us32_t us32_from_int(intmax_t i) {
	return us32_from_int_e(i, NULL);
}

us32_t us32_from_int_e(intmax_t i, bool *error) {
	us32_t res = us32_mk();
	us32_append_int_e(&res, i, error);
	return res;
}

us32_t us32_from_int_fmt(intmax_t i, const struct uifmt *fmt) {
	return us32_from_int_fmt_e(i, fmt, NULL);
}

us32_t us32_from_int_fmt_e(intmax_t i, const struct uifmt *fmt, bool *error) {
	us32_t res = us32_mk();
	us32_append_int_fmt_e(&res, i, fmt, error);
	return res;
}

us32_t us32_from_uint(uintmax_t i) {
	return us32_from_uint_e(i, NULL);
}

us32_t us32_from_uint_e(uintmax_t i, bool *error) {
	us32_t res = us32_mk();
	us32_append_uint_e(&res, i, error);
	return res;
}

us32_t us32_from_uint_fmt(uintmax_t i, const struct uifmt *fmt) {
	return us32_from_uint_fmt_e(i, fmt, NULL);
}

us32_t us32_from_uint_fmt_e(uintmax_t i, const struct uifmt *fmt, bool *error) {
	us32_t res = us32_mk();
	us32_append_uint_fmt_e(&res, i, fmt, error);
	return res;
}

us32_t us32_from_bool(bool b) {
	return us32_from_bool_e(b, NULL);
}

us32_t us32_from_bool_e(bool b, bool *error) {
	us32_t res = us32_mk();
	us32_append_bool_e(&res, b, error);
	return res;
}

us32_t us32_from_case_bool(bool b, ucase_t c) {
	return us32_from_case_bool_e(b, c, NULL);
}

us32_t us32_from_case_bool_e(bool b, ucase_t c, bool *error) {
	us32_t res = us32_mk();
	us32_append_case_bool_e(&res, b, c, error);
	return res;
}

us32_t us32_from_upper_bool(bool b) {
	return us32_from_upper_bool_e(b, NULL);
}

us32_t us32_from_upper_bool_e(bool b, bool *error) {
	us32_t res = us32_mk();
	us32_append_upper_bool_e(&res, b, error);
	return res;
}

us32_t us32_from_lower_bool(bool b) {
	return us32_from_lower_bool_e(b, NULL);
}

us32_t us32_from_lower_bool_e( bool b, bool *error) {
	us32_t res = us32_mk();
	us32_append_lower_bool_e(&res, b, error);
	return res;
}

void us32_free(us32_t *str) {
	assert(us32_valid(str));

	ufree(str->chars);
	
	str->chars = NULL;
	str->len   = 0;
	str->cap   = 0;
}

size_t us32_uz16_len(const us32_t *str) {
	return uz32_n_uz16_len(US32_CEXPAND(str));
}

size_t us32_uz8_len(const us32_t *str) {
	return uz32_n_uz8_len(US32_CEXPAND(str));
}

size_t us32_append(us32_t *str, const us32_t *another) {
	return us32_append_e(str, another, NULL);
}

size_t us32_append_e(us32_t *str, const us32_t *another, bool *error) {
	return us32_append_uz32_n_e(str, US32_CEXPAND(another), error);
}

size_t us32_append_uv32(us32_t *str, uv32_t view) {
	return us32_append_uv32_e(str, view, NULL);
}

size_t us32_append_uv32_e(us32_t *str, uv32_t view, bool *error) {
	return us32_append_uz32_n_e(str, UV32_EXPAND(view), error);
}

size_t us32_append_ucv32(us32_t *str, ucv32_t view) {
	return us32_append_ucv32_e(str, view, NULL);
}

size_t us32_append_ucv32_e(us32_t *str, ucv32_t view, bool *error) {
	return us32_append_uz32_n_e(str, UCV32_CEXPAND(view), error);
}

size_t us32_append_uc32(us32_t *str, uc32_t c) {
	return us32_append_uc32_e(str, c, NULL);
}

size_t us32_append_uc32_e(us32_t *str, uc32_t c, bool *error) {
	bool inner_error = false;

	us32_raise_if_needed_e(str, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		str->chars[str->len++] = c;
	
	return str->len;
}

size_t us32_append_uc32_n(us32_t *str, uc32_t c, size_t n) {
	return us32_append_uc32_n_e(str, c, n, NULL);
}

size_t us32_append_uc32_n_e(us32_t *str, uc32_t c, size_t n, bool *error) {
	bool inner_error = false;

	us32_raise_to_e(str, str->cap + n, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		while (n--)
			str->chars[str->len++] = c;

	return str->len;
}

size_t us32_append_uz32(us32_t *str, const uc32_t *cstr) {
	return us32_append_uz32_e(str, cstr, NULL);
}

size_t us32_append_uz32_e(us32_t *str, const uc32_t *cstr, bool *error) {
	return us32_append_uz32_n_e(str, cstr, uz32_len(cstr), error);
}

size_t us32_append_uz32_n(us32_t *str, const uc32_t *cstr, size_t n) {
	return us32_append_uz32_n_e(str, cstr, n, NULL);
}

size_t us32_append_uz32_n_e(us32_t *str, const uc32_t *cstr, size_t n, bool *error) {
	assert(cstr);

	bool inner_error = false;

	us32_raise_to_e(str, str->cap + n, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		while (n--)
			str->chars[str->len++] = *cstr++;

	return str->len;
}

size_t us32_append_int(us32_t *str, intmax_t i) {
	return us32_append_int_e(str, i, NULL);
}

size_t us32_append_int_e(us32_t *str, intmax_t i, bool *error) {
	return us32_append_int_fmt_e(str, i, &UIFMT_DEC, error);
}

size_t us32_append_int_fmt(us32_t *str, intmax_t i, const struct uifmt *fmt) {
	return us32_append_int_fmt_e(str, i, fmt, NULL);
}

size_t us32_append_int_fmt_e(us32_t *str, intmax_t i, const struct uifmt *fmt, bool *error) {
	assert(us32_valid(str));

	bool inner_error = false;
	size_t old_len   = str->len;

	us32_add_len_e(str, uz32_from_int_fmt(NULL, i, fmt), &inner_error);

	if (inner_error) {
		if (error)
			*error = true;

		return old_len;
	}

	uz32_from_int_fmt(str->chars + old_len, i, fmt);

	return str->len;
}

size_t us32_append_uint(us32_t *str, uintmax_t i) {
	return us32_append_uint_e(str, i, NULL);
}

size_t us32_append_uint_e(us32_t *str, uintmax_t i, bool *error) {
	return us32_append_uint_fmt_e(str, i, &UIFMT_DEC, error);
}

size_t us32_append_uint_fmt(us32_t *str, uintmax_t i, const struct uifmt *fmt) {
	return us32_append_uint_fmt_e(str, i, fmt, NULL);
}

size_t us32_append_uint_fmt_e(us32_t *str, uintmax_t i, const struct uifmt *fmt, bool *error) {
	assert(us32_valid(str));

	bool inner_error = false;
	size_t old_len   = str->len;

	us32_add_len_e(str, uz32_from_uint_fmt(NULL, i, fmt), &inner_error);

	if (inner_error) {
		if (error)
			*error = true;

		return old_len;
	}

	uz32_from_uint_fmt(str->chars + old_len, i, fmt);

	return str->len;
}

size_t us32_append_bool(us32_t *str, bool b) {
	return us32_append_bool_e(str, b, NULL);
}

size_t us32_append_bool_e(us32_t *str, bool b, bool *error) {
	return us32_append_lower_bool_e(str, b, error);
}

size_t us32_append_case_bool(us32_t *str, bool b, ucase_t c) {
	return us32_append_case_bool_e(str, b, c, NULL);
}

size_t us32_append_case_bool_e(us32_t *str, bool b, ucase_t c, bool *error) {
	return UCASE_UPPER == c ? us32_append_upper_bool_e(str, b, error) : us32_append_lower_bool_e(str, b, error);
}

size_t us32_append_upper_bool(us32_t *str, bool b) {
	return us32_append_upper_bool_e(str, b, NULL);
}

size_t us32_append_upper_bool_e(us32_t *str, bool b, bool *error) {
	return us32_append_uz32_e(str, b ? uz32("TRUE") : uz32("FALSE"), error);
}

size_t us32_append_lower_bool(us32_t *str, bool b) {
	return us32_append_lower_bool_e(str, b, NULL);
}

size_t us32_append_lower_bool_e(us32_t *str, bool b, bool *error) {
	return us32_append_uz32_e(str, b ? uz32("true") : uz32("false"), error);
}

void us32_reverse(us32_t *str) {
	uz32_n_reverse(US32_EXPAND(str));
}

size_t us32_trim(us32_t *str) {
	return str->len = uz32_n_trim(US32_EXPAND(str));
}

size_t us32_trim_left(us32_t *str) {
	return str->len = uz32_n_trim_left(US32_EXPAND(str));
}

size_t us32_trim_right(us32_t *str) {
	return str->len = uz32_n_trim_right(US32_EXPAND(str));
}

uc32_t us32_at(const us32_t *str, size_t index) {
	assert(us32_bounds(str, index));
	return str->chars[index];
}

void us32_set_at(us32_t *str, uc32_t c, size_t index) {
	assert(us32_bounds(str, index));
	str->chars[index] = c;
}

int us32_cmp(const us32_t *lhs, const us32_t *rhs) {
	return uz32_n_cmp_n(US32_CEXPAND(lhs), US32_CEXPAND(rhs));
}

int us32_cmp_n(const us32_t *lhs, const us32_t *rhs, size_t n) {
	assert(us32_ebounds(lhs, n) && us32_ebounds(rhs, n));
	return uz32_n_cmp_n(us32_cchars(lhs), n, us32_cchars(rhs), n);
}

int us32_cmp_uv32(const us32_t *lhs, uv32_t rhs) {
	return uz32_n_cmp_n(US32_CEXPAND(lhs), UV32_EXPAND(rhs));
}

int us32_cmp_uv32_n(const us32_t *lhs, uv32_t rhs, size_t n) {
	assert(us32_ebounds(lhs, n) && uv32_ebounds(rhs, n));
	return uz32_n_cmp_n(us32_cchars(lhs), n, uv32_chars(rhs), n);
}

int us32_cmp_ucv32(const us32_t *lhs, ucv32_t rhs) {
	return uz32_n_cmp_n(US32_CEXPAND(lhs), UCV32_CEXPAND(rhs));
}

int us32_cmp_ucv32_n(const us32_t *lhs, ucv32_t rhs, size_t n) {
	assert(us32_ebounds(lhs, n) && ucv32_ebounds(rhs, n));
	return uz32_n_cmp_n(us32_cchars(lhs), n, ucv32_cchars(rhs), n);
}

int us32_cmp_uz32(const us32_t *lhs, const uc32_t *rhs) {
	return uz32_n_cmp(US32_CEXPAND(lhs), rhs);
}

int us32_cmp_uz32_n(const us32_t *lhs, const uc32_t *rhs, size_t n) {
	return uz32_n_cmp_n(US32_CEXPAND(lhs), rhs, n);
}

ptrdiff_t us32_pos(const us32_t *str, const us32_t *another) {
	return uz32_n_pos_n(US32_CEXPAND(str), US32_CEXPAND(another));
}

ptrdiff_t us32_pos_from(const us32_t *str, const us32_t *another, size_t from) {
	assert(us32_bounds(str, from));
	ptrdiff_t pos = uz32_n_pos_n(us32_cchars(str) + from, str->len - from, US32_CEXPAND(another));
	return pos < 0 ? pos : pos + from;
}

ptrdiff_t us32_uc32_pos(const us32_t *str, uc32_t c) {
	return uz32_n_uc32_pos(US32_CEXPAND(str), c);
}

ptrdiff_t us32_uc32_pos_from(const us32_t *str, uc32_t c, size_t from) {
	assert(us32_bounds(str, from));
	ptrdiff_t pos = uz32_n_uc32_pos(us32_cchars(str) + from, str->len - from, c);
	return pos < 0 ? pos : pos + from;
}

ptrdiff_t us32_uz32_pos(const us32_t *str, const uc32_t *cstr) {
	return uz32_n_pos(US32_CEXPAND(str), cstr);
}

ptrdiff_t us32_uz32_pos_from(const us32_t *str, const uc32_t *cstr, size_t from) {
	assert(us32_bounds(str, from) && cstr);
	ptrdiff_t pos = uz32_n_pos(us32_cchars(str) + from, str->len - from, cstr);
	return pos < 0 ? pos : pos + from;
}

ptrdiff_t us32_uz32_n_pos(const us32_t *str, const uc32_t *cstr, size_t n) {
	return uz32_n_pos_n(US32_CEXPAND(str), cstr, n);
}

ptrdiff_t us32_uz32_n_pos_from(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	assert(us32_bounds(str, from));
	ptrdiff_t pos = uz32_n_pos_n(us32_cchars(str) + from, str->len - from, cstr, n);
	return pos < 0 ? pos : pos + from;
}

ptrdiff_t us32_uv32_pos(const us32_t *str, uv32_t view) {
	return uz32_n_pos_n(US32_CEXPAND(str), UV32_EXPAND(view));
}

ptrdiff_t us32_uv32_pos_from(const us32_t *str, uv32_t view, size_t from) {
	assert(us32_bounds(str, from));
	ptrdiff_t pos = uz32_n_pos_n(us32_cchars(str) + from, str->len - from, UV32_EXPAND(view));
	return pos < 0 ? pos : pos + from;
}

ptrdiff_t us32_ucv32_pos(const us32_t *str, ucv32_t view) {
	return uz32_n_pos_n(US32_CEXPAND(str), UCV32_CEXPAND(view));
}

ptrdiff_t us32_ucv32_pos_from(const us32_t *str, ucv32_t view, size_t from) {
	assert(us32_bounds(str, from));
	ptrdiff_t pos = uz32_n_pos_n(us32_cchars(str) + from, str->len - from, UCV32_CEXPAND(view));
	return pos < 0 ? pos : pos + from;
}

ptrdiff_t us32_pos_r(const us32_t *str, const us32_t *another) {
	return uz32_n_pos_n_r(US32_CEXPAND(str), US32_CEXPAND(another), str->len - 1);
}

ptrdiff_t us32_pos_from_r(const us32_t *str, const us32_t *another, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_pos_n_r(US32_CEXPAND(str), US32_CEXPAND(another), from);
}

ptrdiff_t us32_uc32_pos_r(const us32_t *str, uc32_t c) {
	return uz32_n_uc32_pos_r(US32_CEXPAND(str), c, str->len - 1);
}

ptrdiff_t us32_uc32_pos_from_r(const us32_t *str, uc32_t c, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_uc32_pos_r(US32_CEXPAND(str), c, from);
}

ptrdiff_t us32_uz32_pos_r(const us32_t *str, const uc32_t *cstr) {
	return uz32_n_pos_r(US32_CEXPAND(str), cstr, str->len - 1);
}

ptrdiff_t us32_uz32_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_pos_r(US32_CEXPAND(str), cstr, from);
}

ptrdiff_t us32_uz32_n_pos_r(const us32_t *str, const uc32_t *cstr, size_t n) {
	return uz32_n_pos_n_r(US32_CEXPAND(str), cstr, n, str->len - 1);
}

ptrdiff_t us32_uz32_n_pos_from_r(const us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_pos_n_r(US32_CEXPAND(str), cstr, n, from);
}

ptrdiff_t us32_uv32_pos_r(const us32_t *str, uv32_t view) {
	return uz32_n_pos_n_r(US32_CEXPAND(str), UV32_EXPAND(view), str->len - 1);
}

ptrdiff_t us32_uv32_pos_from_r(const us32_t *str, uv32_t view, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_pos_n_r(US32_CEXPAND(str), UV32_EXPAND(view), from);
}

ptrdiff_t us32_ucv32_pos_r(const us32_t *str, ucv32_t view) {
	return uz32_n_pos_n_r(US32_CEXPAND(str), UCV32_CEXPAND(view), str->len - 1);
}

ptrdiff_t us32_ucv32_pos_from_r(const us32_t *str, ucv32_t view, size_t from) {
	assert(us32_bounds(str, from));
	return uz32_n_pos_n_r(US32_CEXPAND(str), UCV32_CEXPAND(view), from);
}

void us32_fill(us32_t *str, uc32_t c) {
	uz32_n_fill(US32_EXPAND(str), c);
}

void us32_fill_from(us32_t *str, uc32_t c, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill(us32_chars(str) + from, str->len - from, c);
}

void us32_fill_to(us32_t *str, uc32_t c, size_t to) {
	assert(us32_ebounds(str, to));
	uz32_n_fill(us32_chars(str), to, c);
}

void us32_fill_range(us32_t *str, uc32_t c, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill(us32_chars(str) + from, len, c);
}

void us32_fill_uz32(us32_t *str, const uc32_t *cstr) {
	uz32_n_fill_uz32(US32_EXPAND(str), cstr);
}

void us32_fill_uz32_from(us32_t *str, const uc32_t *cstr, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill_uz32(us32_chars(str) + from, str->len - from, cstr);
}

void us32_fill_uz32_to(us32_t *str, const uc32_t *cstr, size_t to) {
	uz32_n_fill_uz32(us32_chars(str), to, cstr);
}

void us32_fill_uz32_range(us32_t *str, const uc32_t *cstr, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill_uz32(us32_chars(str) + from, len, cstr);
}

void us32_fill_uz32_n(us32_t *str, const uc32_t *cstr, size_t n) {
	uz32_n_fill_uz32_n(US32_EXPAND(str), cstr, n);
}

void us32_fill_uz32_n_from(us32_t *str, const uc32_t *cstr, size_t n, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill_uz32_n(us32_chars(str) + from, str->len - from, cstr, n);
}

void us32_fill_uz32_n_to(us32_t *str, const uc32_t *cstr, size_t n, size_t to) {
	assert(us32_ebounds(str, to));
	uz32_n_fill_uz32_n(us32_chars(str), to, cstr, n);
}

void us32_fill_uz32_n_range(us32_t *str, const uc32_t *cstr, size_t n, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill_uz32_n(us32_chars(str) + from, len, cstr, n);
}

void us32_fill_uv32(us32_t *str, uv32_t view) {
	uz32_n_fill_uz32_n(US32_EXPAND(str), UV32_EXPAND(view));
}

void us32_fill_uv32_from(us32_t *str, uv32_t view, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill_uz32_n(str->chars + from, str->len - from, UV32_EXPAND(view));
}

void us32_fill_uv32_to(us32_t *str, uv32_t view, size_t to) {
	assert(us32_ebounds(str, to));
	uz32_n_fill_uz32_n(str->chars, to, UV32_EXPAND(view));
}

void us32_fill_uv32_range(us32_t *str, uv32_t view, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill_uz32_n(us32_chars(str) + from, len, UV32_EXPAND(view));
}

void us32_fill_ucv32(us32_t *str, ucv32_t view) {
	uz32_n_fill_uz32_n(US32_EXPAND(str), UCV32_CEXPAND(view));
}

void us32_fill_ucv32_from(us32_t *str, ucv32_t view, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill_uz32_n(us32_chars(str) + from, str->len - from, UCV32_CEXPAND(view));
}

void us32_fill_ucv32_to(us32_t *str, ucv32_t view, size_t to) {
	assert(us32_ebounds(str, to));
	uz32_n_fill_uz32_n(us32_chars(str), to, UCV32_CEXPAND(view));
}

void us32_fill_ucv32_range(us32_t *str, ucv32_t view, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill_uz32_n(us32_chars(str) + from, len, UCV32_CEXPAND(view));
}

void us32_fill_us32(us32_t *str, const us32_t *another) {
	uz32_n_fill_uz32_n(US32_EXPAND(str), US32_CEXPAND(another));
}

void us32_fill_us32_from(us32_t *str, const us32_t *another, size_t from) {
	assert(us32_bounds(str, from));
	uz32_n_fill_uz32_n(us32_chars(str) + from, str->len - from, US32_CEXPAND(another));
}

void us32_fill_us32_to(us32_t *str, const us32_t *another, size_t to) {
	assert(us32_ebounds(str, to));
	uz32_n_fill_uz32_n(us32_chars(str), to, US32_CEXPAND(another));
}

void us32_fill_us32_range(us32_t *str, const us32_t *another, size_t from, size_t len) {
	assert(us32_bounds(str, from) && us32_ebounds(str, from + len));
	uz32_n_fill_uz32_n(us32_chars(str) + from, len, US32_CEXPAND(another));
}

void us32_to_case(us32_t *str, ucase_t ca) {
	assert(us32_valid(str));
	uz32_n_to_case(US32_EXPAND(str), ca);
}

void us32_to_upper(us32_t *str) {
	uz32_n_to_upper(US32_EXPAND(str));
}

void us32_to_lower(us32_t *str) {
	uz32_n_to_lower(US32_EXPAND(str));
}

uc32_t *us32_begin(us32_t *str) {
	assert(us32_valid(str));
	return str->chars;
}

const uc32_t *us32_cbegin(const us32_t *str) {
	assert(us32_valid(str));
	return str->chars;
}

uc32_t *us32_end(us32_t *str) {
	assert(us32_valid(str));
	return str->chars + str->len;
}

const uc32_t *us32_cend(const us32_t *str) {
	assert(us32_valid(str));
	return str->chars + str->len;
}

uc32_t *us32_offset(us32_t *str, size_t index) {
	assert(us32_ebounds(str, index));
	return str->chars + index;
}

const uc32_t *us32_coffset(const us32_t *str, size_t index) {
	assert(us32_ebounds(str, index));
	return str->chars + index;
}

bool us32_bounds(const us32_t *str, size_t index) {
	assert(us32_valid(str));
	return index < str->len;
}

bool us32_ebounds(const us32_t *str, size_t index) {
	assert(us32_valid(str));
	return index <= str->len;
}

size_t us32_len(const us32_t *str) {
	assert(us32_valid(str));
	return str->len;
}

size_t us32_add_len(us32_t *str, ptrdiff_t delta) {
	return us32_add_len_e(str, delta, NULL);
}

size_t us32_add_len_e(us32_t *str, ptrdiff_t delta, bool *error) {
	assert(us32_valid(str) && -(ptrdiff_t) str->len <= delta);
	return us32_set_len_e(str, (ptrdiff_t) str->len + delta, error);
}

size_t us32_set_len(us32_t *str, size_t len) {
	return us32_set_len_e(str, len, NULL);
}

size_t us32_set_len_e(us32_t *str, size_t len, bool *error) {
	assert(us32_valid(str));

	bool inner_error = false;

	if (len > str->cap) 
		us32_raise_to_e(str, len, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
	} else
		str->len = len;

	return str->len;
}

bool us32_empty(const us32_t *str) {
	assert(us32_valid(str));
	return !str->len;
}

void us32_clear(us32_t *str) {
	assert(us32_valid(str));
	str->len = 0;
}

size_t us32_cap(const us32_t *str) {
	assert(us32_valid(str));
	return str->cap;
}

size_t us32_set_cap(us32_t *str, size_t cap) {
	return us32_set_cap_e(str, cap, NULL);
}

size_t us32_set_cap_e(us32_t *str, size_t cap, bool *error) {
	assert(us32_valid(str));

	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * cap);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = cap;
	
		if (cap < str->len)
			str->len = cap;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_shrink_to_fit(us32_t *str) {
	return us32_shrink_to_fit_e(str, NULL);
}

size_t us32_shrink_to_fit_e(us32_t *str, bool *error) {
	assert(us32_valid(str));

	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * str->len);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = str->len;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_raise_if_needed(us32_t *str) {
	return us32_raise_if_needed_e(str, NULL);
}

size_t us32_raise_if_needed_e(us32_t *str, bool *error) {
	assert(us32_valid(str));

	if (str->cap == str->len)
		us32_raise_e(str, error);

	return str->cap;
}

size_t us32_raise(us32_t *str) {
	return us32_raise_e(str, NULL);
}

size_t us32_raise_e(us32_t *str, bool *error) {
	assert(us32_valid(str));
	
	size_t  new_cap   = str->cap ? USTR_RAISE_FACTOR * str->cap : USTR_INIT_CAP;
	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * new_cap);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = new_cap;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_raise_to(us32_t *str, size_t to) {
	return us32_raise_to_e(str, to, NULL);
}

size_t us32_raise_to_e(us32_t *str, size_t to, bool *error) {
	assert(us32_valid(str));

	if (!to)
		return str->cap;

	size_t new_cap = str->cap ? str->cap : USTR_INIT_CAP;

	while (new_cap < to)
		new_cap *= USTR_RAISE_FACTOR;

	if (new_cap == str->cap)
		return str->cap;

	uc32_t *new_chars = urealloc(str->chars, sizeof(uc32_t) * new_cap);

	if (new_chars) {
		str->chars = new_chars;
		str->cap   = new_cap;
	} else if (error)
		*error = true;

	return str->cap;
}

size_t us32_new_csplit(const us32_t *str, uc32_t c, ucv32_t **array) {
	return uz32_n_new_csplit(US32_CEXPAND(str), c, array);
}

size_t us32_new_csplit_e(const us32_t *str, uc32_t c, ucv32_t **array, bool *error) {
	return uz32_n_new_csplit_e(US32_CEXPAND(str), c, array, error);
}

size_t us32_csplit(const us32_t *str, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32_n_csplit(US32_CEXPAND(str), c, array, array_len);
}

size_t us32_new_split(us32_t *str, uc32_t c, uv32_t **array) {
	return uz32_n_new_split(US32_EXPAND(str), c, array);
}

size_t us32_new_split_e(us32_t *str, uc32_t c, uv32_t **array, bool *error) {
	return uz32_n_new_split_e(US32_EXPAND(str), c, array, error);
}

size_t us32_split(us32_t *str, uc32_t c, uv32_t *array, size_t array_len) {
	return uz32_n_split(US32_EXPAND(str), c, array, array_len);
}

size_t us32_new_csplit_uz32(const us32_t *str, const uc32_t *cstr, ucv32_t **array) {
	return uz32_n_new_csplit_uz32(US32_CEXPAND(str), cstr, array);
}

size_t us32_new_csplit_uz32_e(const us32_t *str, const uc32_t *cstr, ucv32_t **array, bool *error) {
	return uz32_n_new_csplit_uz32_e(US32_CEXPAND(str), cstr, array, error);
}

size_t us32_csplit_uz32(const us32_t *str, const uc32_t *cstr, ucv32_t *array, size_t array_len) {
	return uz32_n_csplit_uz32(US32_CEXPAND(str), cstr, array, array_len);
}

size_t us32_new_split_uz32(us32_t *str, const uc32_t *cstr, uv32_t **array) {
	return uz32_n_new_split_uz32(US32_EXPAND(str), cstr, array);
}

size_t us32_new_split_uz32_e(us32_t *str, const uc32_t *cstr, uv32_t **array, bool *error) {
	return uz32_n_new_split_uz32_e(US32_EXPAND(str), cstr, array, error);
}

size_t us32_split_uz32(us32_t *str, const uc32_t *cstr, uv32_t *array, size_t array_len) {
	return uz32_n_split_uz32(US32_EXPAND(str), cstr, array, array_len);
}

size_t us32_new_csplit_uz32_n(const us32_t *str, const uc32_t *cstr, size_t n, ucv32_t **array) {
	return uz32_n_new_csplit_uz32_n(US32_CEXPAND(str), cstr, n, array);
}

size_t us32_new_csplit_uz32_n_e(const us32_t *str, const uc32_t *cstr, size_t n, ucv32_t **array, bool *error) {
	return uz32_n_new_csplit_uz32_n_e(US32_CEXPAND(str), cstr, n, array, error);
}

size_t us32_csplit_uz32_n(const us32_t *str, const uc32_t *cstr, size_t n, ucv32_t *array, size_t array_len) {
	return uz32_n_csplit_uz32_n(US32_CEXPAND(str), cstr, n, array, array_len);
}

size_t us32_new_split_uz32_n(us32_t *str, const uc32_t *cstr, size_t n, uv32_t **array) {
	return uz32_n_new_split_uz32_n(US32_EXPAND(str), cstr, n, array);
}

size_t us32_new_split_uz32_n_e(us32_t *str, const uc32_t *cstr, size_t n, uv32_t **array, bool *error) {
	return uz32_n_new_split_uz32_n_e(US32_EXPAND(str), cstr, n, array, error);
}

size_t us32_split_uz32_n(us32_t *str, const uc32_t *cstr, size_t n, uv32_t *array, size_t array_len) {
	return uz32_n_split_uz32_n(US32_EXPAND(str), cstr, n, array, array_len);
}

size_t us32_new_csplit_us32(const us32_t *str, const us32_t *another, ucv32_t **array) {
	return uz32_n_new_csplit_uz32_n(US32_CEXPAND(str), US32_CEXPAND(another), array);
}

size_t us32_new_csplit_us32_e(const us32_t *str, const us32_t *another, ucv32_t **array, bool *error) {
	return uz32_n_new_csplit_uz32_n_e(US32_CEXPAND(str), US32_CEXPAND(another), array, error);
}

size_t us32_csplit_us32(const us32_t *str, const us32_t *another, ucv32_t *array, size_t array_len) {
	return uz32_n_csplit_uz32_n(US32_CEXPAND(str), US32_CEXPAND(another), array, array_len);
}

size_t us32_new_split_us32(us32_t *str, const us32_t *another, uv32_t **array) {
	return uz32_n_new_split_uz32_n(US32_EXPAND(str), US32_CEXPAND(another), array);
}

size_t us32_new_split_us32_e(us32_t *str, const us32_t *another, uv32_t **array, bool *error) {
	return uz32_n_new_split_uz32_n_e(US32_EXPAND(str), US32_CEXPAND(another), array, error);
}

size_t us32_split_us32(us32_t *str, const us32_t *another, uv32_t *array, size_t array_len) {
	return uz32_n_split_uz32_n(US32_EXPAND(str), US32_CEXPAND(another), array, array_len);
}

size_t us32_new_csplit_uv32(const us32_t *str, uv32_t view, ucv32_t **array) {
	return uz32_n_new_csplit_uz32_n(US32_CEXPAND(str), UV32_EXPAND(view), array);
}

size_t us32_new_csplit_uv32_e(const us32_t *str, uv32_t view, ucv32_t **array, bool *error) {
	return uz32_n_new_csplit_uz32_n_e(US32_CEXPAND(str), UV32_EXPAND(view), array, error);
}

size_t us32_csplit_uv32(const us32_t *str, uv32_t view, ucv32_t *array, size_t array_len) {
	return uz32_n_csplit_uz32_n(US32_CEXPAND(str), UV32_EXPAND(view), array, array_len);
}

size_t us32_new_split_uv32(us32_t *str, uv32_t view, uv32_t **array) {
	return uz32_n_new_split_uz32_n(US32_EXPAND(str), UV32_EXPAND(view), array);
}

size_t us32_new_split_uv32_e(us32_t *str, uv32_t view, uv32_t **array, bool *error) {
	return uz32_n_new_split_uz32_n_e(US32_EXPAND(str), UV32_EXPAND(view), array, error);
}

size_t us32_split_uv32(us32_t *str, uv32_t view, uv32_t *array, size_t array_len) {
	return uz32_n_split_uz32_n(US32_EXPAND(str), UV32_EXPAND(view), array, array_len);
}

size_t us32_new_csplit_ucv32(const us32_t *str, ucv32_t view, ucv32_t **array) {
	return uz32_n_new_csplit_uz32_n(US32_CEXPAND(str), UCV32_CEXPAND(view), array);
}

size_t us32_new_csplit_ucv32_e(const us32_t *str, ucv32_t view, ucv32_t **array, bool *error) {
	return uz32_n_new_csplit_uz32_n_e(US32_CEXPAND(str), UCV32_CEXPAND(view), array, error);
}

size_t us32_csplit_ucv32(const us32_t *str, ucv32_t view, ucv32_t *array, size_t array_len) {
	return uz32_n_csplit_uz32_n(US32_CEXPAND(str), UCV32_CEXPAND(view), array, array_len);
}

size_t us32_new_split_ucv32(us32_t *str, ucv32_t view, uv32_t **array) {
	return uz32_n_new_split_uz32_n(US32_EXPAND(str), UCV32_CEXPAND(view), array);
}

size_t us32_new_split_ucv32_e(us32_t *str, ucv32_t view, uv32_t **array, bool *error) {
	return uz32_n_new_split_uz32_n_e(US32_EXPAND(str), UCV32_CEXPAND(view), array, error);
}

size_t us32_split_ucv32(us32_t *str, ucv32_t view, uv32_t *array, size_t array_len) {
	return uz32_n_split_uz32_n(US32_EXPAND(str), UCV32_CEXPAND(view), array, array_len);
}

size_t us32_replace_uc32_uc32(us32_t *str, uc32_t from, uc32_t to) {
	return str->len = uz32_n_replace_uc32_uc32(US32_EXPAND(str), from, to);
}

size_t us32_replace_uc32_uc32_c(us32_t *str, uc32_t from, uc32_t to, size_t *count) {
	return str->len = uz32_n_replace_uc32_uc32_c(US32_EXPAND(str), from, to, count);
}

size_t us32_replace_uz32_uc32(us32_t *str, const uc32_t *from, uc32_t to) {
	return str->len = uz32_n_replace_uz32_uc32(US32_EXPAND(str), from, to);
}

size_t us32_replace_uz32_uc32_c(us32_t *str, const uc32_t *from, uc32_t to, size_t *count) {
	return str->len = uz32_n_replace_uz32_uc32_c(US32_EXPAND(str), from, to, count);
}

size_t us32_replace_uz32_n_uc32(us32_t *str, const uc32_t *from, size_t from_len, uc32_t to) {
	return str->len = uz32_n_replace_uz32_n_uc32(US32_EXPAND(str), from, from_len, to);
}

size_t us32_replace_uz32_n_uc32_c(us32_t *str, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
	return str->len = uz32_n_replace_uz32_n_uc32_c(US32_EXPAND(str), from, from_len, to, count);
}

size_t us32_replace_ucv32_uc32(us32_t *str, ucv32_t from, uc32_t to) {
	return str->len = uz32_n_replace_uz32_n_uc32(US32_EXPAND(str), UCV32_CEXPAND(from), to);
}

size_t us32_replace_ucv32_uc32_c(us32_t *str, ucv32_t from, uc32_t to, size_t *count) {
	return str->len = uz32_n_replace_uz32_n_uc32_c(US32_EXPAND(str), UCV32_CEXPAND(from), to, count);
}

size_t us32_replace_us32_uc32(us32_t *str, const us32_t *from, uc32_t to) {
	return str->len = uz32_n_replace_uz32_n_uc32(US32_EXPAND(str), US32_CEXPAND(from), to);
}

size_t us32_replace_us32_uc32_c(us32_t *str, const us32_t *from, uc32_t to, size_t *count) {
	return str->len = uz32_n_replace_uz32_n_uc32_c(US32_EXPAND(str), US32_CEXPAND(from), to, count);
}

size_t us32_replace_uv32_uc32(us32_t *str, uv32_t from, uc32_t to) {
	return str->len = uz32_n_replace_uz32_n_uc32(US32_EXPAND(str), UV32_EXPAND(from), to);
}

size_t us32_replace_uv32_uc32_c(us32_t *str, uv32_t from, uc32_t to, size_t *count) {
	return str->len = uz32_n_replace_uz32_n_uc32_c(US32_EXPAND(str), UV32_EXPAND(from), to, count);
}

size_t us32_replace_uc32_uz32(us32_t *str, uc32_t from, const uc32_t *to) {
	return us32_replace_uc32_uz32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uc32_uz32_e(us32_t *str, uc32_t from, const uc32_t *to, bool *error) {
	return us32_replace_uc32_uz32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uc32_uz32_c(us32_t *str, uc32_t from, const uc32_t *to, size_t *count) {
	return us32_replace_uc32_uz32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uc32_uz32_c_e(us32_t *str, uc32_t from, const uc32_t *to, size_t *count, bool *error) {
	return us32_replace_uc32_uz32_n_c_e(str, from, to, uz32_len(to), count, error);
}

size_t us32_replace_uc32_uz32_n(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len) {
	return us32_replace_uc32_uz32_n_c_e(str, from, to, to_len, NULL, NULL);
}

size_t us32_replace_uc32_uz32_n_e(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len, bool *error) {
	return us32_replace_uc32_uz32_n_c_e(str, from, to, to_len, NULL, error);
}

size_t us32_replace_uc32_uz32_n_c(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return us32_replace_uc32_uz32_n_c_e(str, from, to, to_len, count, NULL);
}

size_t us32_replace_uc32_uz32_n_c_e(us32_t *str, uc32_t from, const uc32_t *to, size_t to_len, size_t *count, bool *error) {
	size_t old_len     = us32_len(str);
	size_t new_len     = uz32_n_replace_uc32_uz32_n_len_c(US32_EXPAND(str), from, to_len, count);
	bool   inner_error = false;

	us32_set_len_e(str, new_len, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;

		return str->len;
	}

	return uz32_n_replace_uc32_uz32_n(us32_chars(str), old_len, from, to, to_len);
}

size_t us32_replace_uc32_ucv32(us32_t *str, uc32_t from, ucv32_t to) {
	return us32_replace_uc32_ucv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uc32_ucv32_e(us32_t *str, uc32_t from, ucv32_t to, bool *error) {
	return us32_replace_uc32_ucv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uc32_ucv32_c(us32_t *str, uc32_t from, ucv32_t to, size_t *count) {
	return us32_replace_uc32_ucv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uc32_ucv32_c_e(us32_t *str, uc32_t from, ucv32_t to, size_t *count, bool *error) {
	return us32_replace_uc32_uz32_n_c_e(str, from, UCV32_CEXPAND(to), count, error);
}

size_t us32_replace_uc32_us32(us32_t *str, uc32_t from, const us32_t *to) {
	return us32_replace_uc32_us32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uc32_us32_e(us32_t *str, uc32_t from, const us32_t *to, bool *error) {
	return us32_replace_uc32_us32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uc32_us32_c(us32_t *str, uc32_t from, const us32_t *to, size_t *count) {
	return us32_replace_uc32_us32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uc32_us32_c_e(us32_t *str, uc32_t from, const us32_t *to, size_t *count, bool *error) {
	return us32_replace_uc32_uz32_n_c_e(str, from, US32_CEXPAND(to), count, error);
}

size_t us32_replace_uc32_uv32(us32_t *str, uc32_t from, uv32_t to) {
	return us32_replace_uc32_uv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uc32_uv32_e(us32_t *str, uc32_t from, uv32_t to, bool *error) {
	return us32_replace_uc32_uv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uc32_uv32_c(us32_t *str, uc32_t from, uv32_t to, size_t *count) {
	return us32_replace_uc32_uv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uc32_uv32_c_e(us32_t *str, uc32_t from, uv32_t to, size_t *count, bool *error) {
	return us32_replace_uc32_uz32_n_c_e(str, from, UV32_EXPAND(to), count, error);
}

size_t us32_replace_uz32_uz32(us32_t *str, const uc32_t *from, const uc32_t *to) {
	return us32_replace_uz32_uz32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uz32_uz32_e(us32_t *str, const uc32_t *from, const uc32_t *to, bool *error) {
	return us32_replace_uz32_uz32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uz32_uz32_c(us32_t *str, const uc32_t *from, const uc32_t *to, size_t *count) {
	return us32_replace_uz32_uz32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uz32_uz32_c_e(us32_t *str, const uc32_t *from, const uc32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, uz32_len(from), to, uz32_len(to), count, error);
}

size_t us32_replace_uz32_n_uz32(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to) {
	return us32_replace_uz32_n_uz32_c_e(str, from, from_len, to, NULL, NULL);
}

size_t us32_replace_uz32_n_uz32_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, bool *error) {
	return us32_replace_uz32_n_uz32_c_e(str, from, from_len, to, NULL, error);
}

size_t us32_replace_uz32_n_uz32_c(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return us32_replace_uz32_n_uz32_c_e(str, from, from_len, to, count, NULL);
}

size_t us32_replace_uz32_n_uz32_c_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, to, uz32_len(to), count, error);
}

size_t us32_replace_ucv32_uz32(us32_t *str, ucv32_t from, const uc32_t *to) {
	return us32_replace_ucv32_uz32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_ucv32_uz32_e(us32_t *str, ucv32_t from, const uc32_t *to, bool *error) {
	return us32_replace_ucv32_uz32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_ucv32_uz32_c(us32_t *str, ucv32_t from, const uc32_t *to, size_t *count) {
	return us32_replace_ucv32_uz32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_ucv32_uz32_c_e(us32_t *str, ucv32_t from, const uc32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UCV32_CEXPAND(from), to, uz32_len(to), count, error);
}

size_t us32_replace_us32_uz32(us32_t *str, const us32_t *from, const uc32_t *to) {
	return us32_replace_us32_uz32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_us32_uz32_e(us32_t *str, const us32_t *from, const uc32_t *to, bool *error) {
	return us32_replace_us32_uz32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_us32_uz32_c(us32_t *str, const us32_t *from, const uc32_t *to, size_t *count) {
	return us32_replace_us32_uz32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_us32_uz32_c_e(us32_t *str, const us32_t *from, const uc32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, US32_CEXPAND(from), to, uz32_len(to), count, error);
}

size_t us32_replace_uv32_uz32(us32_t *str, uv32_t from, const uc32_t *to) {
	return us32_replace_uv32_uz32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uv32_uz32_e(us32_t *str, uv32_t from, const uc32_t *to, bool *error) {
	return us32_replace_uv32_uz32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uv32_uz32_c(us32_t *str, uv32_t from, const uc32_t *to, size_t *count) {
	return us32_replace_uv32_uz32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uv32_uz32_c_e(us32_t *str, uv32_t from, const uc32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UV32_EXPAND(from), to, uz32_len(to), count, error);
}

size_t us32_replace_uz32_uz32_n(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len) {
	return us32_replace_uz32_uz32_n_c_e(str, from, to, to_len, NULL, NULL);
}

size_t us32_replace_uz32_uz32_n_e(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len, bool *error) {
	return us32_replace_uz32_uz32_n_c_e(str, from, to, to_len, NULL, error);
}

size_t us32_replace_uz32_uz32_n_c(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return us32_replace_uz32_uz32_n_c_e(str, from, to, to_len, count, NULL);
}

size_t us32_replace_uz32_uz32_n_c_e(us32_t *str, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, uz32_len(from), to, to_len, count, error);
}

size_t us32_replace_uz32_n_uz32_n(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, to, to_len, NULL, NULL);
}

size_t us32_replace_uz32_n_uz32_n_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, to, to_len, NULL, error);
}

size_t us32_replace_uz32_n_uz32_n_c(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, to, to_len, count, NULL);
}

size_t us32_replace_uz32_n_uz32_n_c_e(us32_t *str, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count, bool *error) {
	size_t old_len     = us32_len(str);
	size_t new_len     = uz32_n_replace_uz32_n_uz32_n_len_c(US32_EXPAND(str), from, from_len, to_len, count);
	bool   inner_error = false;

	us32_set_len_e(str, new_len, &inner_error);

	if (inner_error) {
		if (error)
			*error = true;
		
		return str->len;
	}

	return uz32_n_replace_uz32_n_uz32_n(us32_chars(str), old_len, from, from_len, to, to_len);
}

size_t us32_replace_ucv32_uz32_n(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len) {
	return us32_replace_ucv32_uz32_n_c_e(str, from, to, to_len, NULL, NULL);
}

size_t us32_replace_ucv32_uz32_n_e(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len, bool *error) {
	return us32_replace_ucv32_uz32_n_c_e(str, from, to, to_len, NULL, error);
}

size_t us32_replace_ucv32_uz32_n_c(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return us32_replace_ucv32_uz32_n_c_e(str, from, to, to_len, count, NULL);
}

size_t us32_replace_ucv32_uz32_n_c_e(us32_t *str, ucv32_t from, const uc32_t *to, size_t to_len, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UCV32_CEXPAND(from), to, to_len, count, error);
}

size_t us32_replace_us32_uz32_n(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len) {
	return us32_replace_us32_uz32_n_c_e(str, from, to, to_len, NULL, NULL);
}

size_t us32_replace_us32_uz32_n_e(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len, bool *error) {
	return us32_replace_us32_uz32_n_c_e(str, from, to, to_len, NULL, error);
}

size_t us32_replace_us32_uz32_n_c(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return us32_replace_us32_uz32_n_c_e(str, from, to, to_len, count, NULL);
}

size_t us32_replace_us32_uz32_n_c_e(us32_t *str, const us32_t *from, const uc32_t *to, size_t to_len, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, US32_CEXPAND(from), to, to_len, count, error);
}

size_t us32_replace_uv32_uz32_n(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len) {
	return us32_replace_uv32_uz32_n_c_e(str, from, to, to_len, NULL, NULL);
}

size_t us32_replace_uv32_uz32_n_e(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len, bool *error) {
	return us32_replace_uv32_uz32_n_c_e(str, from, to, to_len, NULL, error);
}

size_t us32_replace_uv32_uz32_n_c(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return us32_replace_uv32_uz32_n_c_e(str, from, to, to_len, count, NULL);
}

size_t us32_replace_uv32_uz32_n_c_e(us32_t *str, uv32_t from, const uc32_t *to, size_t to_len, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UV32_EXPAND(from), to, to_len, count, error);
}

size_t us32_replace_uz32_ucv32(us32_t *str, const uc32_t *from, ucv32_t to) {
	return us32_replace_uz32_ucv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uz32_ucv32_e(us32_t *str, const uc32_t *from, ucv32_t to, bool *error) {
	return us32_replace_uz32_ucv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uz32_ucv32_c(us32_t *str, const uc32_t *from, ucv32_t to, size_t *count) {
	return us32_replace_uz32_ucv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uz32_ucv32_c_e(us32_t *str, const uc32_t *from, ucv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, uz32_len(from), UCV32_CEXPAND(to), count, error);
}

size_t us32_replace_uz32_n_ucv32(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to) {
	return us32_replace_uz32_n_ucv32_c_e(str, from, from_len, to, NULL, NULL);
}

size_t us32_replace_uz32_n_ucv32_e(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to, bool *error) {
	return us32_replace_uz32_n_ucv32_c_e(str, from, from_len, to, NULL, error);
}

size_t us32_replace_uz32_n_ucv32_c(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to, size_t *count) {
	return us32_replace_uz32_n_ucv32_c_e(str, from, from_len, to, count, NULL);
}

size_t us32_replace_uz32_n_ucv32_c_e(us32_t *str, const uc32_t *from, size_t from_len, ucv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, UCV32_CEXPAND(to), count, error);
}

size_t us32_replace_ucv32_ucv32(us32_t *str, ucv32_t from, ucv32_t to) {
	return us32_replace_ucv32_ucv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_ucv32_ucv32_e(us32_t *str, ucv32_t from, ucv32_t to, bool *error) {
	return us32_replace_ucv32_ucv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_ucv32_ucv32_c(us32_t *str, ucv32_t from, ucv32_t to, size_t *count) {
	return us32_replace_ucv32_ucv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_ucv32_ucv32_c_e(us32_t *str, ucv32_t from, ucv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UCV32_CEXPAND(from), UCV32_CEXPAND(to), count, error);
}

size_t us32_replace_us32_ucv32(us32_t *str, const us32_t *from, ucv32_t to) {
	return us32_replace_us32_ucv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_us32_ucv32_e(us32_t *str, const us32_t *from, ucv32_t to, bool *error) {
	return us32_replace_us32_ucv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_us32_ucv32_c(us32_t *str, const us32_t *from, ucv32_t to, size_t *count) {
	return us32_replace_us32_ucv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_us32_ucv32_c_e(us32_t *str, const us32_t *from, ucv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, US32_CEXPAND(from), UCV32_CEXPAND(to), count, error);
}

size_t us32_replace_uv32_ucv32(us32_t *str, uv32_t from, ucv32_t to) {
	return us32_replace_uv32_ucv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uv32_ucv32_e(us32_t *str, uv32_t from, ucv32_t to, bool *error) {
	return us32_replace_uv32_ucv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uv32_ucv32_c(us32_t *str, uv32_t from, ucv32_t to, size_t *count) {
	return us32_replace_uv32_ucv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uv32_ucv32_c_e(us32_t *str, uv32_t from, ucv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UV32_EXPAND(from), UCV32_CEXPAND(to), count, error);
}

size_t us32_replace_uz32_us32(us32_t *str, const uc32_t *from, const us32_t *to) {
	return us32_replace_uz32_us32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uz32_us32_e(us32_t *str, const uc32_t *from, const us32_t *to, bool *error) {
	return us32_replace_uz32_us32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uz32_us32_c(us32_t *str, const uc32_t *from, const us32_t *to, size_t *count) {
	return us32_replace_uz32_us32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uz32_us32_c_e(us32_t *str, const uc32_t *from, const us32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, uz32_len(from), US32_CEXPAND(to), count, error);
}

size_t us32_replace_uz32_n_us32(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to) {
	return us32_replace_uz32_n_us32_c_e(str, from, from_len, to, NULL, NULL);
}

size_t us32_replace_uz32_n_us32_e(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to, bool *error) {
	return us32_replace_uz32_n_us32_c_e(str, from, from_len, to, NULL, error);
}

size_t us32_replace_uz32_n_us32_c(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to, size_t *count) {
	return us32_replace_uz32_n_us32_c_e(str, from, from_len, to, count, NULL);
}

size_t us32_replace_uz32_n_us32_c_e(us32_t *str, const uc32_t *from, size_t from_len, const us32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, US32_CEXPAND(to), count, error);
}

size_t us32_replace_ucv32_us32(us32_t *str, ucv32_t from, const us32_t *to) {
	return us32_replace_ucv32_us32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_ucv32_us32_e(us32_t *str, ucv32_t from, const us32_t *to, bool *error) {
	return us32_replace_ucv32_us32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_ucv32_us32_c(us32_t *str, ucv32_t from, const us32_t *to, size_t *count) {
	return us32_replace_ucv32_us32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_ucv32_us32_c_e(us32_t *str, ucv32_t from, const us32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UCV32_CEXPAND(from), US32_CEXPAND(to), count, error);
}

size_t us32_replace_us32_us32(us32_t *str, const us32_t *from, const us32_t *to) {
	return us32_replace_us32_us32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_us32_us32_e(us32_t *str, const us32_t *from, const us32_t *to, bool *error) {
	return us32_replace_us32_us32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_us32_us32_c(us32_t *str, const us32_t *from, const us32_t *to, size_t *count) {
	return us32_replace_us32_us32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_us32_us32_c_e(us32_t *str, const us32_t *from, const us32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, US32_CEXPAND(from), US32_CEXPAND(to), count, error);
}

size_t us32_replace_uv32_us32(us32_t *str, uv32_t from, const us32_t *to) {
	return us32_replace_uv32_us32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uv32_us32_e(us32_t *str, uv32_t from, const us32_t *to, bool *error) {
	return us32_replace_uv32_us32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uv32_us32_c(us32_t *str, uv32_t from, const us32_t *to, size_t *count) {
	return us32_replace_uv32_us32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uv32_us32_c_e(us32_t *str, uv32_t from, const us32_t *to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UV32_EXPAND(from), US32_CEXPAND(to), count, error);
}

size_t us32_replace_uz32_uv32(us32_t *str, const uc32_t *from, uv32_t to) {
	return us32_replace_uz32_uv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uz32_uv32_e(us32_t *str, const uc32_t *from, uv32_t to, bool *error) {
	return us32_replace_uz32_uv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uz32_uv32_c(us32_t *str, const uc32_t *from, uv32_t to, size_t *count) {
	return us32_replace_uz32_uv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uz32_uv32_c_e(us32_t *str, const uc32_t *from, uv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, uz32_len(from), UV32_EXPAND(to), count, error);
}

size_t us32_replace_uz32_n_uv32(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to) {
	return us32_replace_uz32_n_uv32_c_e(str, from, from_len, to, NULL, NULL);
}

size_t us32_replace_uz32_n_uv32_e(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to, bool *error) {
	return us32_replace_uz32_n_uv32_c_e(str, from, from_len, to, NULL, error);
}

size_t us32_replace_uz32_n_uv32_c(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to, size_t *count) {
	return us32_replace_uz32_n_uv32_c_e(str, from, from_len, to, count, NULL);
}

size_t us32_replace_uz32_n_uv32_c_e(us32_t *str, const uc32_t *from, size_t from_len, uv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, from, from_len, UV32_EXPAND(to), count, error);
}

size_t us32_replace_ucv32_uv32(us32_t *str, ucv32_t from, uv32_t to) {
	return us32_replace_ucv32_uv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_ucv32_uv32_e(us32_t *str, ucv32_t from, uv32_t to, bool *error) {
	return us32_replace_ucv32_uv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_ucv32_uv32_c(us32_t *str, ucv32_t from, uv32_t to, size_t *count) {
	return us32_replace_ucv32_uv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_ucv32_uv32_c_e(us32_t *str, ucv32_t from, uv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UCV32_CEXPAND(from), UV32_EXPAND(to), count, error);
}

size_t us32_replace_us32_uv32(us32_t *str, const us32_t *from, uv32_t to) {
	return us32_replace_us32_uv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_us32_uv32_e(us32_t *str, const us32_t *from, uv32_t to, bool *error) {
	return us32_replace_us32_uv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_us32_uv32_c(us32_t *str, const us32_t *from, uv32_t to, size_t *count) {
	return us32_replace_us32_uv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_us32_uv32_c_e(us32_t *str, const us32_t *from, uv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, US32_CEXPAND(from), UV32_EXPAND(to), count, error);
}

size_t us32_replace_uv32_uv32(us32_t *str, uv32_t from, uv32_t to) {
	return us32_replace_uv32_uv32_c_e(str, from, to, NULL, NULL);
}

size_t us32_replace_uv32_uv32_e(us32_t *str, uv32_t from, uv32_t to, bool *error) {
	return us32_replace_uv32_uv32_c_e(str, from, to, NULL, error);
}

size_t us32_replace_uv32_uv32_c(us32_t *str, uv32_t from, uv32_t to, size_t *count) {
	return us32_replace_uv32_uv32_c_e(str, from, to, count, NULL);
}

size_t us32_replace_uv32_uv32_c_e(us32_t *str, uv32_t from, uv32_t to, size_t *count, bool *error) {
	return us32_replace_uz32_n_uz32_n_c_e(str, UV32_EXPAND(from), UV32_EXPAND(to), count, error);
}

const uc32_t *us32_cchars(const us32_t *str) {
	assert(us32_valid(str));
	return str->chars ? str->chars : U"";
}

uc32_t *us32_chars(us32_t *str) {
	assert(us32_valid(str));
	static uc32_t chars[] = U"";
	return str->chars ? str->chars : chars;
}

bool us32_valid(const us32_t *str) {
	return str
		&& (bool) str->chars == (bool) str->cap
		&& str->len <= str->cap;
}