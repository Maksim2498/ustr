#ifndef USTR_IO_H
#define USTR_IO_H

#include <stddef.h>
#include <stdio.h>

#include "char_t.h"
#include "cview_t.h"
#include "str_t.h"
#include "view_t.h"

// Locale

void uset_locale(void);

// CView

size_t uprintln_ucv32(ucv32_t view);
size_t uprint_ucv32(ucv32_t view);

size_t ufprintln_ucv32(FILE *file, ucv32_t view);
size_t ufprint_ucv32(FILE *file, ucv32_t view);

// Str

size_t uprintln_us32(const us32_t *str);
size_t uprint_us32(const us32_t *str);

size_t ufprintln_us32(FILE *file, const us32_t *str);
size_t ufprint_us32(FILE *file, const us32_t *str);

// View

size_t uprintln_uv32(uv32_t view);
size_t uprint_uv32(uv32_t view);

size_t ufprintln_uv32(FILE *file, uv32_t view);
size_t ufprint_uv32(FILE *file, uv32_t view);

// CStr

size_t uprintln_uz32(const uc32_t *cstr);
size_t uprint_uz32(const uc32_t *cstr);
size_t uprintln_uz32_n(const uc32_t *cstr, size_t n);
size_t uprint_uz32_n(const uc32_t *cstr, size_t n);
size_t uprintln_uz16(const uc16_t *cstr);
size_t uprint_uz16(const uc16_t *cstr);
size_t uprintln_uz16_n(const uc16_t *cstr, size_t n);
size_t uprint_uz16_n(const uc16_t *cstr, size_t n);
size_t uprintln_uz8(const uc8_t *cstr);
size_t uprint_uz8(const uc8_t *cstr);
size_t uprintln_uz8_n(const uc8_t *cstr, size_t n);
size_t uprint_uz8_n(const uc8_t *cstr, size_t n);

size_t ufprintln_uz32(FILE *file, const uc32_t *cstr);
size_t ufprint_uz32(FILE *file, const uc32_t *cstr);
size_t ufprintln_uz32_n(FILE *file, const uc32_t *cstr, size_t n);
size_t ufprint_uz32_n(FILE *file, const uc32_t *cstr, size_t n);
size_t ufprintln_uz16(FILE *file, const uc16_t *cstr);
size_t ufprint_uz16(FILE *file, const uc16_t *cstr);
size_t ufprintln_uz16_n(FILE *file, const uc16_t *cstr, size_t n);
size_t ufprint_uz16_n(FILE *file, const uc16_t *cstr, size_t n);
size_t ufprintln_uz8(FILE *file, const uc8_t *cstr);
size_t ufprint_uz8(FILE *file, const uc8_t *cstr);
size_t ufprintln_uz8_n(FILE *file, const uc8_t *cstr, size_t n);
size_t ufprint_uz8_n(FILE *file, const uc8_t *cstr, size_t n);

// Char

size_t uprintln_uc32(uc32_t c);
size_t uprint_uc32(uc32_t c);
size_t uprintln_uc32_n(uc32_t c, size_t n);
size_t uprint_uc32_n(uc32_t c, size_t n);
size_t uprintln_uc16(uc16_t c);
size_t uprint_uc16(uc16_t c);
size_t uprintln_uc16_n(uc16_t c, size_t n);
size_t uprint_uc16_n(uc16_t c, size_t n);
size_t uprintln_uc8(uc8_t c);
size_t uprint_uc8(uc8_t c);
size_t uprintln_uc8_n(uc8_t c, size_t n);
size_t uprint_uc8_n(uc8_t c, size_t n);

size_t ufprintln_uc32(FILE *file, uc32_t c);
size_t ufprint_uc32(FILE *file, uc32_t c);
size_t ufprintln_uc32_n(FILE *file, uc32_t c, size_t n);
size_t ufprint_uc32_n(FILE *file, uc32_t c, size_t n);
size_t ufprintln_uc16(FILE *file, uc16_t c);
size_t ufprint_uc16(FILE *file, uc16_t c);
size_t ufprintln_uc16_n(FILE *file, uc16_t c, size_t n);
size_t ufprint_uc16_n(FILE *file, uc16_t c, size_t n);
size_t ufprintln_uc8(FILE *file, uc8_t c);
size_t ufprint_uc8(FILE *file, uc8_t c);
size_t ufprintln_uc8_n(FILE *file, uc8_t c, size_t n);
size_t ufprint_uc8_n(FILE *file, uc8_t c, size_t n);

size_t uprintln(void);
size_t ufprintln(FILE *file);

#endif