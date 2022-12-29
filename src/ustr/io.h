#ifndef USTR_IO_H
#define USTR_IO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "type/fmt/case.h"
#include "type/fmt/float.h"
#include "type/fmt/int.h"
#include "type/char.h"
#include "type/cview.h"
#include "type/str.h"
#include "type/view.h"

// Locale

void uset_locale(void);

// Output

/*
// - Fmt

size_t uprintln_ucv32_fmt(ucv32_t fmt, ...);
size_t uprint_ucv32_fmt(ucv32_t fmt, ...);

size_t uprintln_uv32_fmt(uv32_t fmt, ...);
size_t uprint_uv32_fmt(uv32_t fmt, ...);

size_t uprintln_us32_fmt(const us32_t *fmt, ...);
size_t uprint_us32_fmt(const us32_t *fmt, ...);

size_t uprintln_uz32_fmt(const uc32_t *fmt, ...);
size_t uprint_uz32_fmt(const uc32_t *fmt, ...);

size_t uprintln_uz16_fmt(const uc16_t *fmt, ...);
size_t uprint_uz16_fmt(const uc16_t *fmt, ...);

size_t uprintln_uz8_fmt(const uc8_t *fmt, ...);
size_t uprint_uz8_fmt(const uc8_t *fmt, ...);

size_t uprintln_fmt(const char *fmt, ...);
size_t uprint_fmt(const char *fmt, ...);


size_t ufprintln_ucv32_fmt(FILE *file, ucv32_t fmt, ...);
size_t ufprint_ucv32_fmt(FILE *file, ucv32_t fmt, ...);

size_t ufprintln_uv32_fmt(FILE *file, uv32_t fmt, ...);
size_t ufprint_uv32_fmt(FILE *file, uv32_t fmt, ...);

size_t ufprintln_us32_fmt(FILE *file, const us32_t *fmt, ...);
size_t ufprint_us32_fmt(FILE *file, const us32_t *fmt, ...);

size_t ufprintln_uz32_fmt(FILE *file, const uc32_t *fmt, ...);
size_t ufprint_uz32_fmt(FILE *file, const uc32_t *fmt, ...);

size_t ufprintln_uz16_fmt(FILE *file, const uc16_t *fmt, ...);
size_t ufprint_uz16_fmt(FILE *file, const uc16_t *fmt, ...);

size_t ufprintln_uz8_fmt(FILE *file, const uc8_t *fmt, ...);
size_t ufprint_uz8_fmt(FILE *file, const uc8_t *fmt, ...);

size_t ufprintln_fmt(FILE *file, const char *fmt, ...);
size_t ufprint_fmt(FILE *file, const char *fmt, ...);
*/

// - Bool

size_t uprintln_bool(bool b);
size_t uprint_bool(bool b);
size_t uprintln_case_bool(bool b, ucase_t c);
size_t uprint_case_bool(bool b, ucase_t c);
size_t uprintln_upper_bool(bool b);
size_t uprint_upper_bool(bool b);
size_t uprintln_lower_bool(bool b);
size_t uprint_lower_bool(bool b);

size_t ufprintln_bool(FILE *file, bool b);
size_t ufprint_bool(FILE *file, bool b);
size_t ufprintln_case_bool(FILE *file, bool b, ucase_t c);
size_t ufprint_case_bool(FILE *file, bool b, ucase_t c);
size_t ufprintln_upper_bool(FILE *file, bool b);
size_t ufprint_upper_bool(FILE *file, bool b);
size_t ufprintln_lower_bool(FILE *file, bool b);
size_t ufprint_lower_bool(FILE *file, bool b);

// - Float

size_t uprintln_float(double f);
size_t uprint_float(double f);
size_t uprintln_float_fmt(double f, const struct uffmt *fmt);
size_t uprint_float_fmt(double f, const struct uffmt *fmt);

size_t ufprintln_float(FILE *file, double f);
size_t ufprint_float(FILE *file, double f);
size_t ufprintln_float_fmt(FILE *file, double f, const struct uffmt *fmt);
size_t ufprint_float_fmt(FILE *file, double f, const struct uffmt *fmt);

// - Int

size_t uprintln_int(intmax_t i);
size_t uprint_int(intmax_t i);
size_t uprintln_int_fmt(intmax_t i, const struct uifmt *fmt);
size_t uprint_int_fmt(intmax_t i, const struct uifmt *fmt);
size_t uprintln_uint(uintmax_t i);
size_t uprint_uint(uintmax_t i);
size_t uprintln_uint_fmt(uintmax_t i, const struct uifmt *fmt);
size_t uprint_uint_fmt(uintmax_t i, const struct uifmt *fmt);

size_t ufprintln_int(FILE *file, intmax_t i);
size_t ufprint_int(FILE *file, intmax_t i);
size_t ufprintln_int_fmt(FILE *file, intmax_t i, const struct uifmt *fmt);
size_t ufprint_int_fmt(FILE *file, intmax_t i, const struct uifmt *fmt);
size_t ufprintln_uint(FILE *file, uintmax_t i);
size_t ufprint_uint(FILE *file, uintmax_t i);
size_t ufprintln_uint_fmt(FILE *file, uintmax_t i, const struct uifmt *fmt);
size_t ufprint_uint_fmt(FILE *file, uintmax_t i, const struct uifmt *fmt);

// - CView

size_t uprintln_ucv32(ucv32_t view);
size_t uprint_ucv32(ucv32_t view);

size_t ufprintln_ucv32(FILE *file, ucv32_t view);
size_t ufprint_ucv32(FILE *file, ucv32_t view);

// - Str

size_t uprintln_us32(const us32_t *str);
size_t uprint_us32(const us32_t *str);

size_t ufprintln_us32(FILE *file, const us32_t *str);
size_t ufprint_us32(FILE *file, const us32_t *str);

// - View

size_t uprintln_uv32(uv32_t view);
size_t uprint_uv32(uv32_t view);

size_t ufprintln_uv32(FILE *file, uv32_t view);
size_t ufprint_uv32(FILE *file, uv32_t view);

// - CStr

size_t uprintln_uz32(const uc32_t *cstr);
size_t uprint_uz32(const uc32_t *cstr);
size_t uprintln_uz32n(const uc32_t *cstr, size_t n);
size_t uprint_uz32n(const uc32_t *cstr, size_t n);

size_t uprintln_uz16(const uc16_t *cstr);
size_t uprint_uz16(const uc16_t *cstr);
size_t uprintln_uz16n(const uc16_t *cstr, size_t n);
size_t uprint_uz16n(const uc16_t *cstr, size_t n);

size_t uprintln_uz8(const uc8_t *cstr);
size_t uprint_uz8(const uc8_t *cstr);
size_t uprintln_uz8n(const uc8_t *cstr, size_t n);
size_t uprint_uz8n(const uc8_t *cstr, size_t n);

size_t uprintln_z(const char *cstr);
size_t uprint_z(const char *cstr);
size_t uprintln_zn(const char *cstr, size_t n);
size_t uprint_zn(const char *cstr, size_t n);


size_t ufprintln_uz32(FILE *file, const uc32_t *cstr);
size_t ufprint_uz32(FILE *file, const uc32_t *cstr);
size_t ufprintln_uz32n(FILE *file, const uc32_t *cstr, size_t n);
size_t ufprint_uz32n(FILE *file, const uc32_t *cstr, size_t n);

size_t ufprintln_uz16(FILE *file, const uc16_t *cstr);
size_t ufprint_uz16(FILE *file, const uc16_t *cstr);
size_t ufprintln_uz16n(FILE *file, const uc16_t *cstr, size_t n);
size_t ufprint_uz16n(FILE *file, const uc16_t *cstr, size_t n);

size_t ufprintln_uz8(FILE *file, const uc8_t *cstr);
size_t ufprint_uz8(FILE *file, const uc8_t *cstr);
size_t ufprintln_uz8n(FILE *file, const uc8_t *cstr, size_t n);
size_t ufprint_uz8n(FILE *file, const uc8_t *cstr, size_t n);

size_t ufprintln_z(FILE *file, const char *cstr);
size_t ufprint_z(FILE *file, const char *cstr);
size_t ufprintln_zn(FILE *file, const char *cstr, size_t n);
size_t ufprint_zn(FILE *file, const char *cstr, size_t n);

// - Char

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

size_t uprintln_c(char c);
size_t uprint_c(char c);
size_t uprintln_c_n(char c, size_t n);
size_t uprint_c_n(char c, size_t n);



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

size_t ufprintln_c(FILE *file, char c);
size_t ufprint_c(FILE *file, char c);
size_t ufprintln_c_n(FILE *file, char c, size_t n);
size_t ufprint_c_n(FILE *file, char c, size_t n);

// Line

size_t uprintln(void);
size_t ufprintln(FILE *file);

// Input

// - Str

size_t ureadln_us32(us32_t *s);
size_t ureadln_us32_e(us32_t *s, bool *error);
size_t ureadln_us32_sep(us32_t *s, uc32_t sep);
size_t ureadln_us32_sep_e(us32_t *s, uc32_t sep, bool *error);

size_t ufreadln_us32(FILE *file, us32_t *s);
size_t ufreadln_us32_e(FILE *file, us32_t *s, bool *error);
size_t ufreadln_us32_sep(FILE *file, us32_t *s, uc32_t sep);
size_t ufreadln_us32_sep_e(FILE *file, us32_t *s, uc32_t sep, bool *error);

// - Char

size_t uread_uc32(uc32_t *c);

size_t uread_uc16(uc16_t *c);
size_t uread_uc16_f(uc16_t *c);

size_t uread_uc8_f(uc8_t *c);
size_t uread_uc8(uc8_t *c);


size_t ufread_uc32(FILE *file, uc32_t *c);

size_t ufread_uc16_f(FILE *file, uc16_t *c);
size_t ufread_uc16(FILE *file, uc16_t *c);

size_t ufread_uc8_f(FILE *file, uc8_t *c);
size_t ufread_uc8(FILE *file, uc8_t *c);

#endif