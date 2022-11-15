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

size_t uprint_ucv32(ucv32_t view) {
    return ufprint_ucv32(stdout, view);
}

size_t ufprint_ucv32(FILE *file, ucv32_t view) {
    assert(ucv32_valid(view));
    return ufprint_uz32_n(file, view.chars, view.len);
}

size_t uprint_us32(const us32_t *str) {
    return ufprint_us32(stdout, str);
}

size_t ufprint_us32(FILE *file, const us32_t *str) {
    assert(us32_valid(str));
    return ufprint_uz32_n(file, str->chars, str->len);
}

size_t uprint_uv32(uv32_t view) {
    return ufprint_uv32(stdout, view);
}

size_t ufprint_uv32(FILE *file, uv32_t view) {
    assert(uv32_valid(view));
    return ufprint_uz32_n(file, view.chars, view.len);
}

size_t uprint_uz32(const uc32_t *cstr) {
	return ufprint_uz32(stdout, cstr);
}

size_t uprint_uz32_n(const uc32_t *cstr, size_t n) {
	return ufprint_uz32_n(stdout, cstr, n);
}

size_t uprint_uz16(const uc16_t *cstr) {
	return ufprint_uz16(stdout, cstr);
}

size_t uprint_uz16_n(const uc16_t *cstr, size_t n) {
	return ufprint_uz16_n(stdout, cstr, n);
}

size_t uprint_uz8(const uc8_t *cstr) {
	return ufprint_uz8(stdout, cstr);
}

size_t uprint_uz8_n(const uc8_t *cstr, size_t n) {
	return ufprint_uz8_n(stdout, cstr, n);
}

size_t ufprint_uz32(FILE *file, const uc32_t *cstr) {
	assert(cstr);

	size_t written = 0;

	while (*cstr)
		written += ufprint_uc32(file, *cstr++);

	return written;
}

size_t ufprint_uz32_n(FILE *file, const uc32_t *cstr, size_t n) {
	assert(cstr);

	size_t written = 0;

	for (size_t i = 0; i < n; ++i)
		written += ufprint_uc32(file, cstr[i]);

	return written;
}

size_t ufprint_uz16(FILE *file, const uc16_t *cstr) {
	assert(cstr);

	size_t written = 0;

	for (size_t i = 0; cstr[i]; i += uc16_len(cstr[i])) {
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc16(c8, cstr + i);

		written += ufprint_uz8_n(file, c8, c8_len);
	}

	return written;
}

size_t ufprint_uz16_n(FILE *file, const uc16_t *cstr, size_t n) {
	assert(cstr);

	size_t written = 0;

	for (size_t i = 0; i < n; i += uc16_len(cstr[i])) {
		uc8_t  c8[4];
		size_t c8_len = uc8_from_uc16(c8, cstr + i);

		written += ufprint_uz8_n(file, c8, c8_len);
	}

	return written;
}

size_t ufprint_uz8(FILE *file, const uc8_t *cstr) {
	assert(cstr);

	size_t written = 0;

	while (*cstr)
		written += ufprint_uc8(file, *cstr++);

	return written;
}

size_t ufprint_uz8_n(FILE *file, const uc8_t *cstr, size_t n) {
	assert(cstr);

	size_t written = 0;

	for (size_t i = 0; i < n; ++i)
		written += ufprint_uc8(file, cstr[i]);

	return written;
}

size_t uprint_uc32(uc32_t c) {
	return ufprint_uc32(stdout, c);
}

size_t uprint_uc32_n(uc32_t c, size_t n) {
	return ufprint_uc32_n(stdout, c, n);
}

size_t uprint_uc16(uc16_t c) {
	return ufprint_uc16(stdout, c);
}

size_t uprint_uc16_n(uc16_t c, size_t n) {
	return ufprint_uc16_n(stdout, c, n);
}

size_t uprint_uc8(uc8_t c) {
	return ufprint_uc8(stdout, c);
}

size_t uprint_uc8_n(uc8_t c, size_t n) {
	return ufprint_uc8_n(stdout, c, n);
}

size_t ufprint_uc32(FILE *file, uc32_t c) {
	if (ferror(file))
		return 0;
	
	uc8_t  c8[4];
	size_t n 	   = uc8_from_uc32(c8, c);
	size_t written = 0;

	for (size_t i = 0; i < n; ++i)
		written += ufprint_uc8(file, c8[i]);

	return written;
}

size_t ufprint_uc32_n(FILE *file, uc32_t c, size_t n) {
	size_t written = 0;

	while (n--)
		written += ufprint_uc32(file, c);

	return written;
}

size_t ufprint_uc16(FILE *file, uc16_t c) {
	if (ferror(file) || uc16_srgt(c))
		return 0;

	uc8_t  c8[4];
	size_t n       = uc8_from_uc16(c8, &c);
	size_t written = 0;

	for (size_t i = 0; i < n; ++i)
		written += ufprint_uc8(file, c8[i]);

	return written;
}

size_t ufprint_uc16_n(FILE *file, uc16_t c, size_t n) {
	size_t written = 0;

	while (n--)
		written += ufprint_uc16(file, c);

	return written;
}

size_t ufprint_uc8(FILE *file, uc8_t c) {
	return ferror(file) || fputc(c, file) == EOF ? 0 : 1;
}

size_t ufprint_uc8_n(FILE *file, uc8_t c, size_t n) { 
	size_t written = 0;

	while (n--)
		written += ufprint_uc8(file, c);

	return written;
}