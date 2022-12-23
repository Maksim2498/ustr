#include "io.h"

#include <assert.h>
#include <locale.h>

#include "fmt/float.h"
#include "fmt/int.h"
#include "util/math.h"
#include "char.h"
#include "config.h"
#include "cstr.h"
#include "cview.h"
#include "str.h"
#include "view.h"

static _Thread_local char uio_buffer_[USTR_IO_BUFFER_SIZE];

typedef size_t (*uz8_from_int_t)(uc8_t *, uintmax_t, const struct uifmt *);

static size_t ufprint_int_fmt_(FILE *file, uintmax_t i, const struct uifmt *fmt, uz8_from_int_t func);

void uset_locale(void) {
    setlocale(LC_ALL, "en_US.UTF-8");
}

size_t uprintln_bool(bool b) {
	return uprint_bool(b) + uprintln();
}

size_t uprint_bool(bool b) {
	return ufprint_bool(stdout, b);
}

size_t uprintln_case_bool(bool b, ucase_t c) {
	return uprint_case_bool(b, c) + uprintln();
}

size_t uprint_case_bool(bool b, ucase_t c) {
	return ufprint_case_bool(stdout, b, c);
}

size_t uprintln_upper_bool(bool b) {
	return uprint_upper_bool(b) + uprintln();
}

size_t uprint_upper_bool(bool b) {
	return ufprint_upper_bool(stdout, b);
}

size_t uprintln_lower_bool(bool b) {
	return uprint_lower_bool(b) + uprintln();
}

size_t uprint_lower_bool(bool b) {
	return ufprint_lower_bool(stdout, b);
}

size_t ufprintln_bool(FILE *file, bool b) {
	return ufprint_bool(file, b) + ufprintln(file);
}

size_t ufprint_bool(FILE *file, bool b) {
	return ufprint_lower_bool(file, b);
}

size_t ufprintln_case_bool(FILE *file, bool b, ucase_t c) {
	return ufprint_case_bool(file, b, c) + ufprintln(file);
}

size_t ufprint_case_bool(FILE *file, bool b, ucase_t c) {
	return UCASE_UPPER == c ? ufprint_upper_bool(file, b) : ufprint_lower_bool(file, b);
}

size_t ufprintln_upper_bool(FILE *file, bool b) {
	return ufprint_upper_bool(file, b) + ufprintln(file);
}

size_t ufprint_upper_bool(FILE *file, bool b) {
	return ufprint_uz8(file, b ? uz8("TRUE") : uz8("FALSE"));
}

size_t ufprintln_lower_bool(FILE *file, bool b) {
	return ufprint_lower_bool(file, b) + ufprintln(file);
}

size_t ufprint_lower_bool(FILE *file, bool b) {
	return ufprint_uz8(file, b ? uz8("true") : uz8("false"));
}

size_t uprintln_float(double f) {
	return uprint_float(f) + uprintln();
}

size_t uprint_float(double f) {
	return ufprint_float(stdout, f);
}

size_t uprintln_float_fmt(double f, const struct uffmt *fmt) {
	return uprint_float_fmt(f, fmt) + uprintln();
}

size_t uprint_float_fmt(double f, const struct uffmt *fmt) {
	return ufprint_float_fmt(stdout, f, fmt);
}

size_t ufprintln_float(FILE *file, double f) {
	return ufprint_float(file, f) + ufprintln(file);
}

size_t ufprint_float(FILE *file, double f) {
	return ufprint_float_fmt(file, f, &UFFMT);
}

size_t ufprintln_float_fmt(FILE *file, double f, const struct uffmt *fmt) {
	return ufprint_float_fmt(file, f, fmt) + ufprintln(file);
}

size_t ufprint_float_fmt(FILE *file, double f, const struct uffmt *fmt) {
	struct uffmt inner_fmt = *fmt;
	size_t       written   = 0;
	size_t 		 to_write  = uz8_from_float_fmt(NULL, f, fmt);

	while (to_write) {
		inner_fmt.max_len = inner_fmt.start_from + UMIN(USTR_IO_BUFFER_SIZE, to_write);

		size_t len = uz8_from_float_fmt((uc8_t *) uio_buffer_, f, &inner_fmt);

		inner_fmt.start_from += len;
		to_write             -= len;
		written              += ufprint_uz8_n(file, (uc8_t *) uio_buffer_, len);
	}

	return written;
}

size_t uprintln_int(intmax_t i) {
	return uprint_int(i) + uprintln();
}

size_t uprint_int(intmax_t i) {
	return ufprint_int(stdout, i);
}

size_t uprintln_int_fmt(intmax_t i, const struct uifmt *fmt) {
	return uprint_int_fmt(i, fmt) + uprintln();
}

size_t uprint_int_fmt(intmax_t i, const struct uifmt *fmt) {
	return ufprint_int_fmt(stdout, i, fmt);
}

size_t uprintln_uint(uintmax_t i) {
	return uprint_uint(i) + uprintln();
}

size_t uprint_uint(uintmax_t i) {
	return ufprint_uint(stdout, i);
}

size_t uprintln_uint_fmt(uintmax_t i, const struct uifmt *fmt) {
	return uprint_uint_fmt(i, fmt) + uprintln();
}

size_t uprint_uint_fmt(uintmax_t i, const struct uifmt *fmt) {
	return ufprint_uint_fmt(stdout, i, fmt);
}

size_t ufprintln_int(FILE *file, intmax_t i) {
	return ufprint_int(file, i) + ufprintln(file);
}

size_t ufprint_int(FILE *file, intmax_t i) {
	return ufprint_int_fmt(file, i, &UIFMT_DEC);
}

size_t ufprintln_int_fmt(FILE *file, intmax_t i, const struct uifmt *fmt) {
	return ufprint_int_fmt(file, i, fmt) + ufprintln(file);
}

size_t ufprint_int_fmt(FILE *file, intmax_t i, const struct uifmt *fmt) {
	return ufprint_int_fmt_(file, i, fmt, (uz8_from_int_t) uz8_from_int_fmt);
}

size_t ufprintln_uint(FILE *file, uintmax_t i) {
	return ufprint_uint(file, i) + ufprintln(file);
}

size_t ufprint_uint(FILE *file, uintmax_t i) {
	return ufprint_uint_fmt(file, i, &UIFMT_DEC);
}

size_t ufprintln_uint_fmt(FILE *file, uintmax_t i, const struct uifmt *fmt) {
	return ufprint_uint_fmt(file, i, fmt) + ufprintln(file);
}

size_t ufprint_uint_fmt(FILE *file, uintmax_t i, const struct uifmt *fmt) {
	return ufprint_int_fmt_(file, i, fmt, uz8_from_uint_fmt);
}

size_t ufprint_int_fmt_(FILE *file, uintmax_t i, const struct uifmt *fmt, size_t (*func)(uc8_t *, uintmax_t, const struct uifmt *)) {
	struct uifmt inner_fmt = *fmt;
	size_t       written   = 0;
	size_t 		 to_write  = func(NULL, i, fmt);

	while (to_write) {
		inner_fmt.max_len = inner_fmt.start_from + UMIN(USTR_IO_BUFFER_SIZE, to_write);

		size_t len = func((uc8_t *) uio_buffer_, i, &inner_fmt);

		inner_fmt.start_from += len;
		to_write             -= len;
		written              += ufprint_uz8_n(file, (uc8_t *) uio_buffer_, len);
	}

	return written;
}

size_t uprintln_ucv32(ucv32_t view) {
	return uprint_ucv32(view) + uprintln();
}

size_t uprint_ucv32(ucv32_t view) {
    return ufprint_ucv32(stdout, view);
}

size_t ufprintln_ucv32(FILE *file, ucv32_t view) {
	return ufprint_ucv32(file, view) + ufprintln(file);
}

size_t ufprint_ucv32(FILE *file, ucv32_t view) {
    assert(ucv32_valid(view));
    return ufprint_uz32_n(file, view.chars, view.len);
}

size_t uprintln_us32(const us32_t *str) {
	return uprint_us32(str) + uprintln();
}

size_t uprint_us32(const us32_t *str) {
    return ufprint_us32(stdout, str);
}

size_t ufprintln_us32(FILE *file, const us32_t *str) {
	return ufprint_us32(file, str) + ufprintln(file);
}

size_t ufprint_us32(FILE *file, const us32_t *str) {
    assert(us32_valid(str));
    return ufprint_uz32_n(file, str->chars, str->len);
}

size_t uprintln_uv32(uv32_t view) {
	return uprint_uv32(view) + uprintln();
}

size_t uprint_uv32(uv32_t view) {
    return ufprint_uv32(stdout, view);
}

size_t ufprintln_uv32(FILE *file, uv32_t view) {
	return ufprint_uv32(file, view) + ufprintln(file);
}

size_t ufprint_uv32(FILE *file, uv32_t view) {
    assert(uv32_valid(view));
    return ufprint_uz32_n(file, view.chars, view.len);
}

size_t uprintln_uz32(const uc32_t *cstr) {
	return uprint_uz32(cstr) + uprintln();
}

size_t uprint_uz32(const uc32_t *cstr) {
	return ufprint_uz32(stdout, cstr);
}

size_t uprintln_uz32_n(const uc32_t *cstr, size_t n) {
	return uprint_uz32_n(cstr, n) + uprintln();
}

size_t uprint_uz32_n(const uc32_t *cstr, size_t n) {
	return ufprint_uz32_n(stdout, cstr, n);
}

size_t uprintln_uz16(const uc16_t *cstr) {
	return uprint_uz16(cstr) + uprintln();
}

size_t uprint_uz16(const uc16_t *cstr) {
	return ufprint_uz16(stdout, cstr);
}

size_t uprintln_uz16_n(const uc16_t *cstr, size_t n) {
	return uprint_uz16_n(cstr, n) + uprintln();
}

size_t uprint_uz16_n(const uc16_t *cstr, size_t n) {
	return ufprint_uz16_n(stdout, cstr, n);
}

size_t uprintln_uz8(const uc8_t *cstr) {
	return uprint_uz8(cstr) + uprintln();
}

size_t uprint_uz8(const uc8_t *cstr) {
	return ufprint_uz8(stdout, cstr);
}

size_t uprintln_uz8_n(const uc8_t *cstr, size_t n) {
	return uprint_uz8_n(cstr, n) + uprintln();
}

size_t uprint_uz8_n(const uc8_t *cstr, size_t n) {
	return ufprint_uz8_n(stdout, cstr, n);
}

size_t uprintln_z(const char *cstr) {
	return uprintln_uz8((const uc8_t *) cstr);
}

size_t uprint_z(const char *cstr) {
	return uprint_uz8((const uc8_t *) cstr);
}

size_t uprintln_z_n(const char *cstr, size_t n) {
	return uprintln_uz8_n((const uc8_t *) cstr, n);
}

size_t uprint_z_n(const char *cstr, size_t n) {
	return uprint_uz8_n((const uc8_t *) cstr, n);
}

size_t ufprintln_uz32(FILE *file, const uc32_t *cstr) {
	return ufprint_uz32(file, cstr) + ufprintln(file);
}

size_t ufprint_uz32(FILE *file, const uc32_t *cstr) {
	assert(cstr);

	size_t written = 0;

	for (; cstr[written]; ++written) {
		uc8_t    c8[4];
		unsigned c8_len = uc8_from_uc32(c8, cstr[written]);

		if (!fwrite(c8, c8_len, 1, file))
			break;
	}

	return written;
}

size_t ufprintln_uz32_n(FILE *file, const uc32_t *cstr, size_t n) {
	return ufprint_uz32_n(file, cstr, n) + ufprintln(file);
}

size_t ufprint_uz32_n(FILE *file, const uc32_t *cstr, size_t n) {
	assert(cstr);

	size_t written = 0;

	for (; written < n; ++written) {
		uc8_t    c8[4];
		unsigned c8_len = uc8_from_uc32(c8, cstr[written]);

		if (!fwrite(c8, c8_len, 1, file))
			break;
	}

	return written;
}

size_t ufprintln_uz16(FILE *file, const uc16_t *cstr) {
	return ufprint_uz16(file, cstr) + ufprintln(file);
}

size_t ufprint_uz16(FILE *file, const uc16_t *cstr) {
	return ufprint_uz16_n(file, cstr, uz16_len(cstr));
}

size_t ufprintln_uz16_n(FILE *file, const uc16_t *cstr, size_t n) {
	return ufprint_uz16_n(file, cstr, n) + ufprintln(file);
}

size_t ufprint_uz16_n(FILE *file, const uc16_t *cstr, size_t n) {
	assert(cstr);

	size_t written = 0;

	for (; written < n; written += uc16_32_len(cstr[written])) {
		uc8_t    c8[4];
		unsigned c8_len = uc8_from_uc16(c8, cstr + written);

		if (!fwrite(c8, c8_len, 1, file))
			break;
	}

	return written;
}

size_t ufprintln_uz8(FILE *file, const uc8_t *cstr) {
	return ufprint_uz8(file, cstr) + ufprintln(file);
}

size_t ufprint_uz8(FILE *file, const uc8_t *cstr) {
	return ufprint_uz8_n(file, cstr, uz8_len(cstr));
}

size_t ufprintln_uz8_n(FILE *file, const uc8_t *cstr, size_t n) {
	return ufprint_uz8_n(file, cstr, n) + ufprintln(file);
}

size_t ufprint_uz8_n(FILE *file, const uc8_t *cstr, size_t n) {
	assert(cstr);
	return fwrite(cstr, 1, n, file);
}

size_t ufprintln_z(FILE *file, const char *cstr) {
	return ufprintln_uz8(file, (const uc8_t *) cstr);
}

size_t ufprint_z(FILE *file, const char *cstr) {
	return ufprint_uz8(file, (const uc8_t *) cstr);
}

size_t ufprintln_z_n(FILE *file, const char *cstr, size_t n) {
	return ufprintln_uz8_n(file, (const uc8_t *) cstr, n);
}

size_t ufprint_z_n(FILE *file, const char *cstr, size_t n) {
	return ufprint_uz8_n(file, (const uc8_t *) cstr, n);
}

size_t uprintln_uc32(uc32_t c) {
	return uprint_uc32(c) + uprintln();
}

size_t uprint_uc32(uc32_t c) {
	return ufprint_uc32(stdout, c);
}

size_t uprintln_uc32_n(uc32_t c, size_t n) {
	return uprint_uc32_n(c, n) + uprintln();
}

size_t uprint_uc32_n(uc32_t c, size_t n) {
	return ufprint_uc32_n(stdout, c, n);
}

size_t uprintln_uc16(uc16_t c) {
	return uprint_uc16(c) + uprintln();
}

size_t uprint_uc16(uc16_t c) {
	return ufprint_uc16(stdout, c);
}

size_t uprintln_uc16_n(uc16_t c, size_t n) {
	return uprint_uc16_n(c, n) + uprintln();
}

size_t uprint_uc16_n(uc16_t c, size_t n) {
	return ufprint_uc16_n(stdout, c, n);
}

size_t uprintln_uc8(uc8_t c) {
	return uprint_uc8(c) + uprintln();
}

size_t uprint_uc8(uc8_t c) {
	return ufprint_uc8(stdout, c);
}

size_t uprintln_uc8_n(uc8_t c, size_t n) {
	return uprint_uc8_n(c, n) + uprintln();
}

size_t uprint_uc8_n(uc8_t c, size_t n) {
	return ufprint_uc8_n(stdout, c, n);
}

size_t uprintln_c(char c) {
	return uprintln_uc8(c);
}

size_t uprint_c(char c) {
	return uprint_uc8(c);
}

size_t uprintln_c_n(char c, size_t n) {
	return uprintln_uc8_n(c, n);
}

size_t uprint_c_n(char c, size_t n) {
	return uprint_uc8_n(c, n);
}

size_t ufprintln_uc32(FILE *file, uc32_t c) {
	return ufprint_uc32(file, c) + ufprintln(file);
}

size_t ufprint_uc32(FILE *file, uc32_t c) {
	uc8_t    c8[4];
	unsigned n = uc8_from_uc32(c8, c);

	return fwrite(c8, n, 1, file);
}

size_t ufprintln_uc32_n(FILE *file, uc32_t c, size_t n) {
	return ufprint_uc32_n(file, c, n) + ufprintln(file);
}

size_t ufprint_uc32_n(FILE *file, uc32_t c, size_t n) {
	size_t written = 0;

	while (n--) {
		uc8_t    c8[4];
		unsigned c8_len = uc8_from_uc32(c8, c);

		if (!fwrite(c8, c8_len, 1, file))
			break;

		++written;
	}

	return written;
}

size_t ufprintln_uc16(FILE *file, uc16_t c) {
	return ufprint_uc16(file, c) + ufprintln(file);
}

size_t ufprint_uc16(FILE *file, uc16_t c) {
	if (uc16_srgt(c))
		return 0;

	uc8_t    c8[4];
	unsigned n = uc8_from_uc16(c8, &c);

	return fwrite(c8, n, 1, file);
}

size_t ufprintln_uc16_n(FILE *file, uc16_t c, size_t n) {
	return ufprint_uc16_n(file, c, n) + ufprintln(file);
}

size_t ufprint_uc16_n(FILE *file, uc16_t c, size_t n) {
	if (uc16_srgt(c))
		return 0;

	size_t written = 0;

	while (n--) {
		uc8_t    c8[4];
		unsigned c8_len = uc8_from_uc16(c8, &c);
		
		if (!fwrite(c8, c8_len, 1, file))
			break;

		++written;
	}

	return written;
}

size_t ufprintln_uc8(FILE *file, uc8_t c) {
	return ufprint_uc8(file, c) + ufprintln(file);
}

size_t ufprint_uc8(FILE *file, uc8_t c) {
	return fputc(c, file) == EOF ? 0 : 1;
}

size_t ufprintln_uc8_n(FILE *file, uc8_t c, size_t n) { 
	return ufprint_uc8_n(file, c, n) + ufprintln(file);
}

size_t ufprint_uc8_n(FILE *file, uc8_t c, size_t n) { 
	size_t written = 0;

	while (n-- && fputc(c, file) != EOF)
		++written; 

	return written;
}

size_t ufprintln_c(FILE *file, char c) {
	return ufprintln_uc8(file, c);
}

size_t ufprint_c(FILE *file, char c) {
	return ufprint_uc8(file, c);
}

size_t ufprintln_c_n(FILE *file, char c, size_t n) {
	return ufprintln_uc8_n(file, c, n);
}

size_t ufprint_c_n(FILE *file, char c, size_t n) {
	return ufprint_uc8_n(file, c, n);
}

size_t uprintln(void) {
	return ufprintln(stdout);
}

size_t ufprintln(FILE *file) {
	return ufprint_uc8(file, '\n');
}

size_t ureadln_us32(us32_t *s) {
	return ureadln_us32_e(s, NULL);
}

size_t ureadln_us32_e(us32_t *s, bool *error) {
	return ufreadln_us32_e(stdin, s, error);
}

size_t ureadln_us32_sep(us32_t *s, uc32_t sep) {
	return ureadln_us32_sep_e(s, sep, NULL);
}

size_t ureadln_us32_sep_e(us32_t *s, uc32_t sep, bool *error) {
	return ufreadln_us32_sep_e(stdin, s, sep, error);
}

size_t ufreadln_us32(FILE *file, us32_t *s) {
	return ufreadln_us32_e(file, s, NULL);
}

size_t ufreadln_us32_e(FILE *file, us32_t *s, bool *error) {
	return ufreadln_us32_sep_e(file, s, '\n', error);
}

size_t ufreadln_us32_sep(FILE *file, us32_t *s, uc32_t sep) {
	return ufreadln_us32_sep_e(file, s, sep, NULL);
}

size_t ufreadln_us32_sep_e(FILE *file, us32_t *s, uc32_t sep, bool *error) {
	assert(us32_valid(s));

	if (ferror(file))
		return 0;

	us32_clear(s);

	bool inner_error = false;

	while (true) {
		uc8_t c8[4];
		int   c = fgetc(file);

		if (EOF == c)
			break;

		c8[0] = c;

		unsigned len = uc8_len(c8[0]);

		for (unsigned i = 1; i < len; ++i) {
			c = fgetc(file);

			if (EOF == c)
				goto exit;

			c8[i] = c;
		}

		uc32_t c32;

		uc32_from_uc8(&c32, c8);

		if (c32 == sep)
			break;

		us32_append_uc32_e(s, c32, &inner_error);

		if (inner_error) {
			if (error)
				*error = true;

			break;
		}
	}

exit:
	return us32_len(s);
}

size_t uread_uc32(uc32_t *c) {
	return ufread_uc32(stdin, c);
}

size_t uread_uc16_f(uc16_t *c) {
	return ufread_uc16_f(stdin, c);
}

size_t uread_uc16(uc16_t *c) {
	return ufread_uc16(stdin, c);
}

size_t uread_uc8_f(uc8_t *c) {
	return ufread_uc8_f(stdin, c);
}

size_t uread_uc8(uc8_t *c) {
	return ufread_uc8(stdin, c);
}

size_t ufread_uc32(FILE *file, uc32_t *c32) {
	assert(c32);

	uc8_t c8[4];

	if (!ufread_uc8_f(file, c8))
		return 0;

	uc32_from_uc8(c32, c8);

	return 1;
}

size_t ufread_uc16(FILE *file, uc16_t *c16) {
	assert(c16);
	uc32_t c32;
	return ufread_uc32(file, &c32) && uc32_16_len(c32) == 1 ? uc16_from_uc32(c16, c32) : 0;
}

size_t ufread_uc16_f(FILE *file, uc16_t *c16) {
	assert(c16);
	uc32_t c32;
	return ufread_uc32(file, &c32) ? uc16_from_uc32(c16, c32) : 0;
}

size_t ufread_uc8_f(FILE *file, uc8_t *c8) {
	assert(c8);

	if (ferror(file))
		return 0;

	int c = fgetc(file);

	if (EOF == c)
		return 0;

	uc8_t inner_c8[4] = { c };

	unsigned len = uc8_len(c);

	for (unsigned i = 1; i < len; ++i) {
		int c = fgetc(file);

		if (EOF == c)
			return 0;

		inner_c8[i] = c;
	}

	for (unsigned i = 0; i < len; ++i)
		c8[i] = inner_c8[i];

	return len;
}

size_t ufread_uc8(FILE *file, uc8_t *c8) {
	assert(c8);

	if (ferror(file))
		return 0;

	int c = fgetc(file);

	if (EOF == c)
		return 0;

	*c8 = c;

	return 1;
}