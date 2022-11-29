#include "io.h"

#include <assert.h>
#include <locale.h>

#include "char.h"
#include "cview.h"
#include "str.h"
#include "view.h"

void uset_locale(void) {
    setlocale(LC_ALL, "en_US.UTF-8");
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

size_t ufprintln_uz32(FILE *file, const uc32_t *cstr) {
	return ufprint_uz32(file, cstr) + ufprintln(file);
}

size_t ufprint_uz32(FILE *file, const uc32_t *cstr) {
	assert(cstr);

	size_t written = 0;

	for (; cstr[written]; ++written) {
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc32(c8, cstr[written]);

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
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc32(c8, cstr[written]);

		if (!fwrite(c8, c8_len, 1, file))
			break;
	}

	return written;
}

size_t ufprintln_uz16(FILE *file, const uc16_t *cstr) {
	return ufprint_uz16(file, cstr) + ufprintln(file);
}

size_t ufprint_uz16(FILE *file, const uc16_t *cstr) {
	assert(cstr);

	size_t written = 0;

	for (; cstr[written]; written += uc16_len(cstr[written])) {
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc16(c8, cstr + written);

		if (!fwrite(c8, c8_len, 1, file))
			break;
	}

	return written;
}

size_t ufprintln_uz16_n(FILE *file, const uc16_t *cstr, size_t n) {
	return ufprint_uz16_n(file, cstr, n) + ufprintln(file);
}

size_t ufprint_uz16_n(FILE *file, const uc16_t *cstr, size_t n) {
	assert(cstr);

	size_t written = 0;

	for (; written < n; written += uc16_len(cstr[written])) {
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc16(c8, cstr + written);

		if (!fwrite(c8, c8_len, 1, file))
			break;
	}

	return written;
}

size_t ufprintln_uz8(FILE *file, const uc8_t *cstr) {
	return ufprint_uz8(file, cstr) + ufprintln(file);
}

size_t ufprint_uz8(FILE *file, const uc8_t *cstr) {
	assert(cstr);

	size_t written = 0;

	while (*cstr && fputc(*cstr++, file) != EOF) 
		++written;

	return written;
}

size_t ufprintln_uz8_n(FILE *file, const uc8_t *cstr, size_t n) {
	return ufprint_uz8_n(file, cstr, n) + ufprintln(file);
}

size_t ufprint_uz8_n(FILE *file, const uc8_t *cstr, size_t n) {
	assert(cstr);
	return fwrite(cstr, 1, n, file);
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

size_t ufprintln_uc32(FILE *file, uc32_t c) {
	return ufprint_uc32(file, c) + ufprintln(file);
}

size_t ufprint_uc32(FILE *file, uc32_t c) {
	uc8_t  c8[4];
	size_t n = uc8_from_uc32(c8, c);

	return fwrite(c8, n, 1, file);
}

size_t ufprintln_uc32_n(FILE *file, uc32_t c, size_t n) {
	return ufprint_uc32_n(file, c, n) + ufprintln(file);
}

size_t ufprint_uc32_n(FILE *file, uc32_t c, size_t n) {
	size_t written = 0;

	while (n--) {
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc32(c8, c);

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

	uc8_t  c8[4];
	size_t n = uc8_from_uc16(c8, &c);

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
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc16(c8, &c);
		
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

		int len = uc8_len(c8[0]);

		for (int i = 1; i < len; ++i) {
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
	return ufread_uc32(file, &c32) && uc32_uc16_len(c32) == 1 ? uc16_from_uc32(c16, c32) : 0;
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

	int len = uc8_len(c);

	for (int i = 1; i < len; ++i) {
		int c = fgetc(file);

		if (EOF == c)
			return 0;

		inner_c8[i] = c;
	}

	for (int i = 0; i < len; ++i)
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