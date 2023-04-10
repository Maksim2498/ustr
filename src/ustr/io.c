#include "io.h"

#include <assert.h>

#include "fmt/case.h"
#include "fmt/float.h"
#include "fmt/fmt.h"
#include "fmt/int.h"

#include "char.h"
#include "cstr.h"
#include "cview.h"
#include "str.h"
#include "view.h"

#define UPRINT_FMT_T(fmt, T)                         \
    va_list args;                                    \
    va_start(args, fmt);                             \
    size_t written = uprint_fmt_##T##_v(fmt, &args); \
    va_end(args);                                    \
    return written

#define UPRINT_FMT_UZXN(fmt, fmt_len, X)                         \
    va_list args;                                                \
    va_start(args, fmt_len);                                     \
    size_t written = uprint_fmt_uz##X##n_v(fmt, fmt_len, &args); \
    va_end(args);                                                \
    return written

static bool uwrite_uc32_to_file(uc32_t c, void *arg) {
    return !ufprint_uc32(arg, c);
}

static bool uwrite_uc16_to_file(uc16_t c, void *arg) {
    return !ufprint_uc16(arg, c);
}

static bool uwrite_uc8_to_file(uc8_t c, void *arg) {
    return !ufprint_uc8(arg, c);
}

size_t uprint_fmt_uz32(const uc32_t *fmt, ...) {
    UPRINT_FMT_T(fmt, uz32);
}

size_t uprint_fmt_uz32n(const uc32_t *fmt, size_t fmt_len, ...) {
    UPRINT_FMT_UZXN(fmt, fmt_len, 32);
}

size_t uprint_fmt_ucv32(ucv32_t fmt, ...) {
    UPRINT_FMT_T(fmt, ucv32);
}

size_t uprint_fmt_uv32(uv32_t fmt, ...) {
    UPRINT_FMT_T(fmt, uv32);
}

size_t uprint_fmt_us32(const us32_t *fmt, ...) {
    UPRINT_FMT_T(fmt, us32);
}

size_t uprint_fmt_uz32_v(const uc32_t *fmt, va_list *args) {
	return uprint_fmt_uz32n_v(fmt, uz32_len(fmt), args);
}

size_t uprint_fmt_uz32n_v(const uc32_t *fmt, size_t fmt_len, va_list *args) {
    return ufprint_fmt_uz32n_v(stdout, fmt, fmt_len, args);
}

size_t uprint_fmt_ucv32_v(ucv32_t fmt, va_list *args) {
    return uprint_fmt_uz32n_v(UCV32_CEXPAND(fmt), args);
}

size_t uprint_fmt_uv32_v(uv32_t fmt, va_list *args) {
    return uprint_fmt_uz32n_v(UV32_CEXPAND(fmt), args);
}

size_t uprint_fmt_us32_v(const us32_t *fmt, va_list *args) {
    return uprint_fmt_uz32n_v(US32_CEXPAND(fmt), args);
}

size_t uprint_fmt_uz16(const uc16_t *fmt, ...) {
    UPRINT_FMT_T(fmt, uz16);
}

size_t uprint_fmt_uz16n(const uc16_t *fmt, size_t fmt_len, ...) {
    UPRINT_FMT_UZXN(fmt, fmt_len, 16);
}

size_t uprint_fmt_ucv16(ucv16_t fmt, ...) {
    UPRINT_FMT_T(fmt, ucv16);
}

size_t uprint_fmt_uv16(uv16_t fmt, ...) {
    UPRINT_FMT_T(fmt, uv16);
}

size_t uprint_fmt_us16(const us16_t *fmt, ...) {
    UPRINT_FMT_T(fmt, us16);
}

size_t uprint_fmt_uz16_v(const uc16_t *fmt, va_list *args) {
	return uprint_fmt_uz16n_v(fmt, uz16_len(fmt), args);
}

size_t uprint_fmt_uz16n_v(const uc16_t *fmt, size_t fmt_len, va_list *args) {
    return ufprint_fmt_uz16n_v(stdout, fmt, fmt_len, args);
}

size_t uprint_fmt_ucv16_v(ucv16_t fmt, va_list *args) {
    return uprint_fmt_uz16n_v(UCV16_CEXPAND(fmt), args);
}

size_t uprint_fmt_uv16_v(uv16_t fmt, va_list *args) {
    return uprint_fmt_uz16n_v(UV16_CEXPAND(fmt), args);
}

size_t uprint_fmt_us16_v(const us16_t *fmt, va_list *args) {
    return uprint_fmt_uz16n_v(US16_CEXPAND(fmt), args);
}

size_t uprint_fmt_uz8(const uc8_t *fmt, ...) {
    UPRINT_FMT_T(fmt, uz8);
}

size_t uprint_fmt_uz8n(const uc8_t *fmt, size_t fmt_len, ...) {
    UPRINT_FMT_UZXN(fmt, fmt_len, 8);
}

size_t uprint_fmt_ucv8(ucv8_t fmt, ...) {
    UPRINT_FMT_T(fmt, ucv8);
}

size_t uprint_fmt_uv8(uv8_t fmt, ...) {
    UPRINT_FMT_T(fmt, uv8);
}

size_t uprint_fmt_us8(const us8_t *fmt, ...) {
    UPRINT_FMT_T(fmt, us8);
}

size_t uprint_fmt_uz8_v(const uc8_t *fmt, va_list *args) {
	return uprint_fmt_uz8n_v(fmt, uz8_len(fmt), args);
}

size_t uprint_fmt_uz8n_v(const uc8_t *fmt, size_t fmt_len, va_list *args) {
    return ufprint_fmt_uz8n_v(stdout, fmt, fmt_len, args);
}

size_t uprint_fmt_ucv8_v(ucv8_t fmt, va_list *args) {
    return uprint_fmt_uz8n_v(UCV8_CEXPAND(fmt), args);
}

size_t uprint_fmt_uv8_v(uv8_t fmt, va_list *args) {
    return uprint_fmt_uz8n_v(UV8_CEXPAND(fmt), args);
}

size_t uprint_fmt_us8_v(const us8_t *fmt, va_list *args) {
    return uprint_fmt_uz8n_v(US8_CEXPAND(fmt), args);
}

#define UPRINTLN_FMT_T(fmt, T)                         \
    va_list args;                                      \
    va_start(args, fmt);                               \
    size_t written = uprintln_fmt_##T##_v(fmt, &args); \
    va_end(args);                                      \
    return written

#define UPRINTLN_FMT_UZXN(fmt, fmt_len, X)                         \
    va_list args;                                                  \
    va_start(args, fmt_len);                                       \
    size_t written = uprintln_fmt_uz##X##n_v(fmt, fmt_len, &args); \
    va_end(args);                                                  \
    return written

size_t uprintln_fmt_uz32(const uc32_t *fmt, ...) {
    UPRINTLN_FMT_T(fmt, uz32);
}

size_t uprintln_fmt_uz32n(const uc32_t *fmt, size_t fmt_len, ...) {
    UPRINTLN_FMT_UZXN(fmt, fmt_len, 32);
}

size_t uprintln_fmt_ucv32(ucv32_t fmt, ...) {
    UPRINTLN_FMT_T(fmt, ucv32);
}

size_t uprintln_fmt_uv32(uv32_t fmt, ...) {
    UPRINTLN_FMT_T(fmt, uv32);
}

size_t uprintln_fmt_us32(const us32_t *fmt, ...) {
    UPRINTLN_FMT_T(fmt, us32);
}

size_t uprintln_fmt_uz32_v(const uc32_t *fmt, va_list *args) {
	return uprintln_fmt_uz32n_v(fmt, uz32_len(fmt), args);
}

size_t uprintln_fmt_uz32n_v(const uc32_t *fmt, size_t fmt_len, va_list *args) {
	return ufprintln_fmt_uz32n_v(stdout, fmt, fmt_len, args);
}

size_t uprintln_fmt_ucv32_v(ucv32_t fmt, va_list *args) {
	return uprintln_fmt_uz32n_v(UCV32_CEXPAND(fmt), args);
}

size_t uprintln_fmt_uv32_v(uv32_t fmt, va_list *args) {
	return uprintln_fmt_uz32n_v(UV32_CEXPAND(fmt), args);
}

size_t uprintln_fmt_us32_v(const us32_t *fmt, va_list *args) {
	return uprintln_fmt_uz32n_v(US32_CEXPAND(fmt), args);
}

size_t uprintln_fmt_uz16(const uc16_t *fmt, ...) {
    UPRINTLN_FMT_T(fmt, uz16);
}

size_t uprintln_fmt_uz16n(const uc16_t *fmt, size_t fmt_len, ...) {
    UPRINTLN_FMT_UZXN(fmt, fmt_len, 16);
}

size_t uprintln_fmt_ucv16(ucv16_t fmt, ...) {
    UPRINTLN_FMT_T(fmt, ucv16);
}

size_t uprintln_fmt_uv16(uv16_t fmt, ...) {
    UPRINTLN_FMT_T(fmt, uv16);
}

size_t uprintln_fmt_us16(const us16_t *fmt, ...) {
    UPRINTLN_FMT_T(fmt, us16);
}

size_t uprintln_fmt_uz16_v(const uc16_t *fmt, va_list *args) {
	return uprintln_fmt_uz16n_v(fmt, uz16_len(fmt), args);
}

size_t uprintln_fmt_uz16n_v(const uc16_t *fmt, size_t fmt_len, va_list *args) {
	return ufprintln_fmt_uz16n_v(stdout, fmt, fmt_len, args);
}

size_t uprintln_fmt_ucv16_v(ucv16_t fmt, va_list *args) {
	return uprintln_fmt_uz16n_v(UCV16_CEXPAND(fmt), args);
}

size_t uprintln_fmt_uv16_v(uv16_t fmt, va_list *args) {
	return uprintln_fmt_uz16n_v(UV16_CEXPAND(fmt), args);
}

size_t uprintln_fmt_us16_v(const us16_t *fmt, va_list *args) {
	return uprintln_fmt_uz16n_v(US16_CEXPAND(fmt), args);
}

size_t uprintln_fmt_uz8(const uc8_t *fmt, ...) {
    UPRINTLN_FMT_T(fmt, uz8);
}

size_t uprintln_fmt_uz8n(const uc8_t *fmt, size_t fmt_len, ...) {
    UPRINTLN_FMT_UZXN(fmt, fmt_len, 8);
}

size_t uprintln_fmt_ucv8(ucv8_t fmt, ...) {
    UPRINTLN_FMT_T(fmt, ucv8);
}

size_t uprintln_fmt_uv8(uv8_t fmt, ...) {
    UPRINTLN_FMT_T(fmt, uv8);
}

size_t uprintln_fmt_us8(const us8_t *fmt, ...) {
    UPRINTLN_FMT_T(fmt, us8);
}

size_t uprintln_fmt_uz8_v(const uc8_t *fmt, va_list *args) {
	return uprintln_fmt_uz8n_v(fmt, uz8_len(fmt), args);
}

size_t uprintln_fmt_uz8n_v(const uc8_t *fmt, size_t fmt_len, va_list *args) {
	return ufprintln_fmt_uz8n_v(stdout, fmt, fmt_len, args);
}

size_t uprintln_fmt_ucv8_v(ucv8_t fmt, va_list *args) {
	return uprintln_fmt_uz8n_v(UCV8_CEXPAND(fmt), args);
}

size_t uprintln_fmt_uv8_v(uv8_t fmt, va_list *args) {
	return uprintln_fmt_uz8n_v(UV8_CEXPAND(fmt), args);
}

size_t uprintln_fmt_us8_v(const us8_t *fmt, va_list *args) {
	return uprintln_fmt_uz8n_v(US8_CEXPAND(fmt), args);
}

#define UFPRINT_FMT_T(file, fmt, T)                         \
    va_list args;                                           \
    va_start(args, fmt);                                    \
    size_t written = ufprint_fmt_##T##_v(file, fmt, &args); \
    va_end(args);                                           \
    return written

#define UFPRINT_FMT_UZXN(file, fmt, fmt_len, X)                         \
    va_list args;                                                       \
    va_start(args, fmt_len);                                            \
    size_t written = ufprint_fmt_uz##X##n_v(file, fmt, fmt_len, &args); \
    va_end(args);                                                       \
    return written

size_t ufprint_fmt_uz32(FILE *file, const uc32_t *fmt, ...) {
    UFPRINT_FMT_T(file, fmt, uz32);
}

size_t ufprint_fmt_uz32n(FILE *file, const uc32_t *fmt, size_t fmt_len, ...) {
    UFPRINT_FMT_UZXN(file, fmt, fmt_len, 32);
}

size_t ufprint_fmt_ucv32(FILE *file, ucv32_t fmt, ...) {
    UFPRINT_FMT_T(file, fmt, ucv32);
}

size_t ufprint_fmt_uv32(FILE *file, uv32_t fmt, ...) {
    UFPRINT_FMT_T(file, fmt, uv32);
}

size_t ufprint_fmt_us32(FILE *file, const us32_t *fmt, ...) {
    UFPRINT_FMT_T(file, fmt, us32);
}

size_t ufprint_fmt_uz32_v(FILE *file, const uc32_t *fmt, va_list *args) {
	return ufprint_fmt_uz32n_v(file, fmt, uz32_len(fmt), args);
}

size_t ufprint_fmt_uz32n_v(FILE *file, const uc32_t *fmt, size_t fmt_len, va_list *args) {
	return uwrite_fmt_uz32n_32_v(fmt, fmt_len, uwrite_uc32_to_file, file, args);
}

size_t ufprint_fmt_ucv32_v(FILE *file, ucv32_t fmt, va_list *args) {
	return ufprint_fmt_uz32n_v(file, UCV32_CEXPAND(fmt), args);
}

size_t ufprint_fmt_uv32_v(FILE *file, uv32_t fmt, va_list *args) {
	return ufprint_fmt_uz32n_v(file, UV32_CEXPAND(fmt), args);
}

size_t ufprint_fmt_us32_v(FILE *file, const us32_t *fmt, va_list *args) {
	return ufprint_fmt_uz32n_v(file, US32_CEXPAND(fmt), args);
}

size_t ufprint_fmt_uz16(FILE *file, const uc16_t *fmt, ...) {
    UFPRINT_FMT_T(file, fmt, uz16);
}

size_t ufprint_fmt_uz16n(FILE *file, const uc16_t *fmt, size_t fmt_len, ...) {
    UFPRINT_FMT_UZXN(file, fmt, fmt_len, 16);
}

size_t ufprint_fmt_ucv16(FILE *file, ucv16_t fmt, ...) {
    UFPRINT_FMT_T(file, fmt, ucv16);
}

size_t ufprint_fmt_uv16(FILE *file, uv16_t fmt, ...) {
    UFPRINT_FMT_T(file, fmt, uv16);
}

size_t ufprint_fmt_us16(FILE *file, const us16_t *fmt, ...) {
    UFPRINT_FMT_T(file, fmt, us16);
}

size_t ufprint_fmt_uz16_v(FILE *file, const uc16_t *fmt, va_list *args) {
	return ufprint_fmt_uz16n_v(file, fmt, uz16_len(fmt), args);
}

size_t ufprint_fmt_uz16n_v(FILE *file, const uc16_t *fmt, size_t fmt_len, va_list *args) {
	return uwrite_fmt_uz16n_16_v(fmt, fmt_len, uwrite_uc16_to_file, file, args);
}

size_t ufprint_fmt_ucv16_v(FILE *file, ucv16_t fmt, va_list *args) {
	return ufprint_fmt_uz16n_v(file, UCV16_CEXPAND(fmt), args);
}

size_t ufprint_fmt_uv16_v(FILE *file, uv16_t fmt, va_list *args) {
	return ufprint_fmt_uz16n_v(file, UV16_CEXPAND(fmt), args);
}

size_t ufprint_fmt_us16_v(FILE *file, const us16_t *fmt, va_list *args) {
	return ufprint_fmt_uz16n_v(file, US16_CEXPAND(fmt), args);
}

size_t ufprint_fmt_uz8(FILE *file, const uc8_t *fmt, ...) {
    UFPRINT_FMT_T(file, fmt, uz8);
}

size_t ufprint_fmt_uz8n(FILE *file, const uc8_t *fmt, size_t fmt_len, ...) {
    UFPRINT_FMT_UZXN(file, fmt, fmt_len, 8);
}

size_t ufprint_fmt_ucv8(FILE *file, ucv8_t fmt, ...) {
    UFPRINT_FMT_T(file, fmt, ucv8);
}

size_t ufprint_fmt_uv8(FILE *file, uv8_t fmt, ...) {
    UFPRINT_FMT_T(file, fmt, uv8);
}

size_t ufprint_fmt_us8(FILE *file, const us8_t *fmt, ...) {
    UFPRINT_FMT_T(file, fmt, us8);
}

size_t ufprint_fmt_uz8_v(FILE *file, const uc8_t *fmt, va_list *args) {
	return ufprint_fmt_uz8n_v(file, fmt, uz8_len(fmt), args);
}

size_t ufprint_fmt_uz8n_v(FILE *file, const uc8_t *fmt, size_t fmt_len, va_list *args) {
	return uwrite_fmt_uz8n_8_v(fmt, fmt_len, uwrite_uc8_to_file, file, args);
}

size_t ufprint_fmt_ucv8_v(FILE *file, ucv8_t fmt, va_list *args) {
	return ufprint_fmt_uz8n_v(file, UCV8_CEXPAND(fmt), args);
}

size_t ufprint_fmt_uv8_v(FILE *file, uv8_t fmt, va_list *args) {
	return ufprint_fmt_uz8n_v(file, UV8_CEXPAND(fmt), args);
}

size_t ufprint_fmt_us8_v(FILE *file, const us8_t *fmt, va_list *args) {
	return ufprint_fmt_uz8n_v(file, US8_CEXPAND(fmt), args);
}

#define UFPRINTLN_FMT_T(file, fmt, T)                         \
    va_list args;                                             \
    va_start(args, fmt);                                      \
    size_t written = ufprintln_fmt_##T##_v(file, fmt, &args); \
    va_end(args);                                             \
    return written

#define UFPRINTLN_FMT_UZXN(file, fmt, fmt_len, X)                         \
    va_list args;                                                         \
    va_start(args, fmt_len);                                              \
    size_t written = ufprintln_fmt_uz##X##n_v(file, fmt, fmt_len, &args); \
    va_end(args);                                                         \
    return written

size_t ufprintln_fmt_uz32(FILE *file, const uc32_t *fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, uz32);
}

size_t ufprintln_fmt_uz32n(FILE *file, const uc32_t *fmt, size_t fmt_len, ...) {
    UFPRINTLN_FMT_UZXN(file, fmt, fmt_len, 32);
}

size_t ufprintln_fmt_ucv32(FILE *file, ucv32_t fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, ucv32);
}

size_t ufprintln_fmt_uv32(FILE *file, uv32_t fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, uv32);
}

size_t ufprintln_fmt_us32(FILE *file, const us32_t *fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, us32);
}

size_t ufprintln_fmt_uz32_v(FILE *file, const uc32_t *fmt, va_list *args) {
    return ufprintln_fmt_uz32n_v(file, fmt, uz32_len(fmt), args);
}

size_t ufprintln_fmt_uz32n_v(FILE *file, const uc32_t *fmt, size_t fmt_len, va_list *args) {
	return ufprint_fmt_uz32n_v(file, fmt, fmt_len, args) + ufprint_new_line(file);
}

size_t ufprintln_fmt_ucv32_v(FILE *file, ucv32_t fmt, va_list *args) {
	return ufprintln_fmt_uz32n_v(file, UCV32_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_uv32_v(FILE *file, uv32_t fmt, va_list *args) {
	return ufprintln_fmt_uz32n_v(file, UV32_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_us32_v(FILE *file, const us32_t *fmt, va_list *args) {
	return ufprintln_fmt_uz32n_v(file, US32_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_uz16(FILE *file, const uc16_t *fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, uz16);
}

size_t ufprintln_fmt_uz16n(FILE *file, const uc16_t *fmt, size_t fmt_len, ...) {
    UFPRINTLN_FMT_UZXN(file, fmt, fmt_len, 16);
}

size_t ufprintln_fmt_ucv16(FILE *file, ucv16_t fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, ucv16);
}

size_t ufprintln_fmt_uv16(FILE *file, uv16_t fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, uv16);
}

size_t ufprintln_fmt_us16(FILE *file, const us16_t *fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, us16);
}

size_t ufprintln_fmt_uz16_v(FILE *file, const uc16_t *fmt, va_list *args) {
    return ufprintln_fmt_uz16n_v(file, fmt, uz16_len(fmt), args);
}

size_t ufprintln_fmt_uz16n_v(FILE *file, const uc16_t *fmt, size_t fmt_len, va_list *args) {
	return ufprint_fmt_uz16n_v(file, fmt, fmt_len, args) + ufprint_new_line(file);
}

size_t ufprintln_fmt_ucv16_v(FILE *file, ucv16_t fmt, va_list *args) {
	return ufprintln_fmt_uz16n_v(file, UCV16_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_uv16_v(FILE *file, uv16_t fmt, va_list *args) {
	return ufprintln_fmt_uz16n_v(file, UV16_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_us16_v(FILE *file, const us16_t *fmt, va_list *args) {
	return ufprintln_fmt_uz16n_v(file, US16_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_uz8(FILE *file, const uc8_t *fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, uz8);
}

size_t ufprintln_fmt_uz8n(FILE *file, const uc8_t *fmt, size_t fmt_len, ...) {
    UFPRINTLN_FMT_UZXN(file, fmt, fmt_len, 8);
}

size_t ufprintln_fmt_ucv8(FILE *file, ucv8_t fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, ucv8);
}

size_t ufprintln_fmt_uv8(FILE *file, uv8_t fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, uv8);
}

size_t ufprintln_fmt_us8(FILE *file, const us8_t *fmt, ...) {
    UFPRINTLN_FMT_T(file, fmt, us8);
}

size_t ufprintln_fmt_uz8_v(FILE *file, const uc8_t *fmt, va_list *args) {
    return ufprintln_fmt_uz8n_v(file, fmt, uz8_len(fmt), args);
}

size_t ufprintln_fmt_uz8n_v(FILE *file, const uc8_t *fmt, size_t fmt_len, va_list *args) {
	return ufprint_fmt_uz8n_v(file, fmt, fmt_len, args) + ufprint_new_line(file);
}

size_t ufprintln_fmt_ucv8_v(FILE *file, ucv8_t fmt, va_list *args) {
	return ufprintln_fmt_uz8n_v(file, UCV8_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_uv8_v(FILE *file, uv8_t fmt, va_list *args) {
	return ufprintln_fmt_uz8n_v(file, UV8_CEXPAND(fmt), args);
}

size_t ufprintln_fmt_us8_v(FILE *file, const us8_t *fmt, va_list *args) {
	return ufprintln_fmt_uz8n_v(file, US8_CEXPAND(fmt), args);
}

size_t uprint_int(intmax_t val) {
	return ufprint_int(stdout, val);
}

size_t uprint_int_fmt32(intmax_t val, const struct ufmt32_int_output *fmt) {
	return ufprint_int_fmt32(stdout, val, fmt);
}

size_t uprint_int_fmt16(intmax_t val, const struct ufmt16_int_output *fmt) {
	return ufprint_int_fmt16(stdout, val, fmt);
}

size_t uprint_int_fmt8(intmax_t val, const struct ufmt8_int_output *fmt) {
	return ufprint_int_fmt8(stdout, val, fmt);
}

size_t uprint_uint(uintmax_t val) {
	return ufprint_uint(stdout, val);
}

size_t uprint_uint_fmt32(uintmax_t val, const struct ufmt32_int_output *fmt) {
	return ufprint_uint_fmt32(stdout, val, fmt);
}

size_t uprint_uint_fmt16(uintmax_t val, const struct ufmt16_int_output *fmt) {
	return ufprint_uint_fmt16(stdout, val, fmt);
}

size_t uprint_uint_fmt8(uintmax_t val, const struct ufmt8_int_output *fmt) {
	return ufprint_uint_fmt8(stdout, val, fmt);
}

size_t uprintln_int(intmax_t val) {
	return ufprintln_int(stdout, val);
}

size_t uprintln_int_fmt32(intmax_t val, const struct ufmt32_int_output *fmt) {
	return ufprintln_int_fmt32(stdout, val, fmt);
}

size_t uprintln_int_fmt16(intmax_t val, const struct ufmt16_int_output *fmt) {
	return ufprintln_int_fmt16(stdout, val, fmt);
}

size_t uprintln_int_fmt8(intmax_t val, const struct ufmt8_int_output *fmt) {
	return ufprintln_int_fmt8(stdout, val, fmt);
}

size_t uprintln_uint(uintmax_t val) {
	return ufprintln_uint(stdout, val);
}

size_t uprintln_uint_fmt32(uintmax_t val, const struct ufmt32_int_output *fmt) {
	return ufprintln_uint_fmt32(stdout, val, fmt);
}

size_t uprintln_uint_fmt16(uintmax_t val, const struct ufmt16_int_output *fmt) {
	return ufprintln_uint_fmt16(stdout, val, fmt);
}

size_t uprintln_uint_fmt8(uintmax_t val, const struct ufmt8_int_output *fmt) {
	return ufprintln_uint_fmt8(stdout, val, fmt);
}

size_t ufprint_int(FILE *file, intmax_t val) {
	return ufprint_int_fmt8(file, val, &UFMT8_INT_OUTPUT_DEC);
}

size_t ufprint_int_fmt32(FILE *file, intmax_t val, const struct ufmt32_int_output *fmt) {
	return uwrite_int_32(val, fmt, uwrite_uc32_to_file, file);
}

size_t ufprint_int_fmt16(FILE *file, intmax_t val, const struct ufmt16_int_output *fmt) {
	return uwrite_int_16(val, fmt, uwrite_uc16_to_file, file);
}

size_t ufprint_int_fmt8(FILE *file, intmax_t val, const struct ufmt8_int_output *fmt) {
	return uwrite_int_8(val, fmt, uwrite_uc8_to_file, file);
}

size_t ufprint_uint(FILE *file, uintmax_t val) {
	return ufprint_uint_fmt8(file, val, &UFMT8_INT_OUTPUT_DEC);
}

size_t ufprint_uint_fmt32(FILE *file, uintmax_t val, const struct ufmt32_int_output *fmt) {
	return uwrite_uint_32(val, fmt, uwrite_uc32_to_file, file);
}

size_t ufprint_uint_fmt16(FILE *file, uintmax_t val, const struct ufmt16_int_output *fmt) {
	return uwrite_uint_16(val, fmt, uwrite_uc16_to_file, file);
}

size_t ufprint_uint_fmt8(FILE *file, uintmax_t val, const struct ufmt8_int_output *fmt) {
	return uwrite_uint_8(val, fmt, uwrite_uc8_to_file, file);
}

size_t ufprintln_int(FILE *file, intmax_t val) {
	return ufprint_int(file, val) + ufprint_new_line(file);
}

size_t ufprintln_int_fmt32(FILE *file, intmax_t val, const struct ufmt32_int_output *fmt) {
	return ufprint_int_fmt32(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_int_fmt16(FILE *file, intmax_t val, const struct ufmt16_int_output *fmt) {
	return ufprint_int_fmt16(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_int_fmt8(FILE *file, intmax_t val, const struct ufmt8_int_output *fmt) {
	return ufprint_int_fmt8(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_uint(FILE *file, uintmax_t val) {
	return ufprint_uint(file, val) + ufprint_new_line(file);
}

size_t ufprintln_uint_fmt32(FILE *file, uintmax_t val, const struct ufmt32_int_output *fmt) {
	return ufprint_uint_fmt32(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_uint_fmt16(FILE *file, uintmax_t val, const struct ufmt16_int_output *fmt) {
	return ufprint_uint_fmt16(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_uint_fmt8(FILE *file, uintmax_t val, const struct ufmt8_int_output *fmt) {
	return ufprint_uint_fmt8(file, val, fmt) + ufprint_new_line(file);
}

size_t uprint_float(double val) {
	return ufprint_float(stdout, val);
}

size_t uprint_float_fmt32(double val, const struct ufmt32_float_output *fmt) {
	return ufprint_float_fmt32(stdout, val, fmt);
}

size_t uprint_float_fmt16(double val, const struct ufmt16_float_output *fmt) {
	return ufprint_float_fmt16(stdout, val, fmt);
}

size_t uprint_float_fmt8(double val, const struct ufmt8_float_output *fmt) {
	return ufprint_float_fmt8(stdout, val, fmt);
}

size_t uprintln_float(double val) {
	return ufprintln_float(stdout, val);
}

size_t uprintln_float_fmt32(double val, const struct ufmt32_float_output *fmt) {
	return ufprintln_float_fmt32(stdout, val, fmt);
}

size_t uprintln_float_fmt16(double val, const struct ufmt16_float_output *fmt) {
	return ufprintln_float_fmt16(stdout, val, fmt);
}

size_t uprintln_float_fmt8(double val, const struct ufmt8_float_output *fmt) {
	return ufprintln_float_fmt8(stdout, val, fmt);
}

size_t ufprint_float(FILE *file, double val) {
	return ufprint_float_fmt8(file, val, &UFMT8_FLOAT_OUTPUT);
}

size_t ufprint_float_fmt32(FILE *file, double val, const struct ufmt32_float_output *fmt) {
	return uwrite_float_32(val, fmt, uwrite_uc32_to_file, file);
}

size_t ufprint_float_fmt16(FILE *file, double val, const struct ufmt16_float_output *fmt) {
	return uwrite_float_16(val, fmt, uwrite_uc16_to_file, file);
}

size_t ufprint_float_fmt8(FILE *file, double val, const struct ufmt8_float_output *fmt) {
	return uwrite_float_8(val, fmt, uwrite_uc8_to_file, file);
}

size_t ufprintln_float(FILE *file, double val) {
	return ufprint_float(file, val) + ufprint_new_line(file);
}

size_t ufprintln_float_fmt32(FILE *file, double val, const struct ufmt32_float_output *fmt) {
	return ufprint_float_fmt32(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_float_fmt16(FILE *file, double val, const struct ufmt16_float_output *fmt) {
	return ufprint_float_fmt16(file, val, fmt) + ufprint_new_line(file);
}

size_t ufprintln_float_fmt8(FILE *file, double val, const struct ufmt8_float_output *fmt) {
	return ufprint_float_fmt8(file, val, fmt) + ufprint_new_line(file);
}

size_t uprint_bool(bool val) {
	return ufprint_bool(stdout, val);
}

size_t uprint_case_bool(ucase_t ca, bool val) {
	return ufprint_case_bool(stdout, ca, val);
}

size_t uprint_lower_bool(bool val) {
	return ufprint_lower_bool(stdout, val);
}

size_t uprint_upper_bool(bool val) {
	return ufprint_upper_bool(stdout, val);
}

size_t uprintln_bool(bool val) {
	return ufprintln_bool(stdout, val);
}

size_t uprintln_case_bool(ucase_t ca, bool val) {
	return ufprintln_case_bool(stdout, ca, val);
}

size_t uprintln_lower_bool(bool val) {
	return ufprintln_lower_bool(stdout, val);
}

size_t uprintln_upper_bool(bool val) {
	return ufprintln_upper_bool(stdout, val);
}

size_t ufprint_bool(FILE *file, bool val) {
    return ufprint_lower_bool(file, val);
}

size_t ufprint_case_bool(FILE *file, ucase_t ca, bool val) {
    assert(ucase_valid_output(ca));

    switch (ca) {
        case UCASE_UPPER:
            return ufprint_upper_bool(file, val);

        case UCASE_LOWER:
            return ufprint_lower_bool(file, val);

        default:
            assert(0);
            return false;
    }
}

size_t ufprint_lower_bool(FILE *file, bool val) {
	return ufprint_ucv8(file, val ? ucv8("true") : ucv8("false"));
}

size_t ufprint_upper_bool(FILE *file, bool val) {
	return ufprint_ucv8(file, val ? ucv8("TRUE") : ucv8("FALSE"));
}

size_t ufprintln_bool(FILE *file, bool val) {
	return ufprint_bool(file, val) + ufprint_new_line(file);
}

size_t ufprintln_case_bool(FILE *file, ucase_t ca, bool val) {
	return ufprint_case_bool(file, ca, val) + ufprint_new_line(file);
}

size_t ufprintln_lower_bool(FILE *file, bool val) {
	return ufprint_lower_bool(file, val) + ufprint_new_line(file);
}

size_t ufprintln_upper_bool(FILE *file, bool val) {
	return ufprint_upper_bool(file, val) + ufprint_new_line(file);
}

size_t uprint_uc32(uc32_t c) {
    return ufprint_uc32(stdout, c);
}

size_t uprint_uc16(uc16_t c) {
    return ufprint_uc16(stdout, c);
}

size_t uprint_uc8(uc8_t c) {
    return ufprint_uc8(stdout, c);
}

size_t uprint_uc32n(uc32_t c, size_t n) {
    return ufprint_uc32n(stdout, c, n);
}

size_t uprint_uc16n(uc16_t c, size_t n) {
    return ufprint_uc16n(stdout, c, n);
}

size_t uprint_uc8n(uc8_t c, size_t n) {
    return ufprint_uc8n(stdout, c, n);
}

size_t uprintln_uc32(uc32_t c) {
    return ufprintln_uc32(stdout, c);
}

size_t uprintln_uc16(uc16_t c) {
    return ufprintln_uc16(stdout, c);
}

size_t uprintln_uc8(uc8_t c) {
    return ufprintln_uc8(stdout, c);
}

size_t uprintln_uc32n(uc32_t c, size_t n) {
    return ufprintln_uc32n(stdout, c, n);
}

size_t uprintln_uc16n(uc16_t c, size_t n) {
    return ufprintln_uc16n(stdout, c, n);
}

size_t uprintln_uc8n(uc8_t c, size_t n) {
    return ufprintln_uc8n(stdout, c, n);
}

size_t ufprint_uc32(FILE *file, uc32_t c) {
    uc8_t    c8[4];
    unsigned c8_len = uc8_from_uc32_imm(c8, c);

    return fwrite(c8, sizeof(uc8_t), c8_len, file);
}

size_t ufprint_uc16(FILE *file, uc16_t c) {
    uc16_t   c16[2] = { c, 0 };
    uc8_t    c8[4];
    unsigned c8_len = uc8_from_uc16(c8, c16);

    return fwrite(c8, sizeof(uc8_t), c8_len, file);
}

size_t ufprint_uc8(FILE *file, uc8_t c) {
    return fwrite(&c, sizeof(uc8_t), 1, file);
}

size_t ufprint_uc32n(FILE *file, uc32_t c, size_t n) {
    uc8_t    c8[4];
    unsigned c8_len  = uc8_from_uc32_imm(c8, c);
    size_t   written = 0;

    while (n--)
        written += fwrite(c8, sizeof(uc8_t), c8_len, file);

    return written;
}

size_t ufprint_uc16n(FILE *file, uc16_t c, size_t n) {
    uc16_t   c16[2]  = { c, 0 };
    uc8_t    c8[4];
    unsigned c8_len  = uc8_from_uc16(c8, c16);
    size_t   written = 0;

    while (n--)
        written += fwrite(c8, sizeof(uc8_t), c8_len, file);

    return written;
}

size_t ufprint_uc8n(FILE *file, uc8_t c, size_t n) {
    size_t written = 0;

    while (n--)
        written += fwrite(&c, sizeof(uc8_t), 1, file);

    return written;
}

size_t ufprintln_uc32(FILE *file, uc32_t c) {
	return ufprint_uc32(file, c) + ufprint_new_line(file);
}

size_t ufprintln_uc16(FILE *file, uc16_t c) {
	return ufprint_uc16(file, c) + ufprint_new_line(file);
}

size_t ufprintln_uc8(FILE *file, uc8_t c) {
	return ufprint_uc8(file, c) + ufprint_new_line(file);
}

size_t ufprintln_uc32n(FILE *file, uc32_t c, size_t n) {
	return ufprint_uc32n(file, c, n) + ufprint_new_line(file);
}

size_t ufprintln_uc16n(FILE *file, uc16_t c, size_t n) {
	return ufprint_uc16n(file, c, n) + ufprint_new_line(file);
}

size_t ufprintln_uc8n(FILE *file, uc8_t c, size_t n) {
	return ufprint_uc8n(file, c, n) + ufprint_new_line(file);
}

size_t uprint_uz32(const uc32_t *cstr) {
	return ufprint_uz32(stdout, cstr);
}

size_t uprint_uz16(const uc16_t *cstr) {
	return ufprint_uz16(stdout, cstr);
}

size_t uprint_uz8(const uc8_t *cstr) {
	return ufprint_uz8(stdout, cstr);
}

size_t uprint_uz32n(const uc32_t *cstr, size_t cstr_len) {
    return ufprint_uz32n(stdout, cstr, cstr_len);
}

size_t uprint_uz16n(const uc16_t *cstr, size_t cstr_len) {
    return ufprint_uz16n(stdout, cstr, cstr_len);
}

size_t uprint_uz8n(const uc8_t *cstr, size_t cstr_len) {
    return ufprint_uz8n(stdout, cstr, cstr_len);
}

size_t uprintln_uz32(const uc32_t *cstr) {
    return ufprintln_uz32(stdout, cstr);
}

size_t uprintln_uz16(const uc16_t *cstr) {
    return ufprintln_uz16(stdout, cstr);
}

size_t uprintln_uz8(const uc8_t *cstr) {
    return ufprintln_uz8(stdout, cstr);
}

size_t uprintln_uz32n(const uc32_t *cstr, size_t cstr_len) {
    return ufprintln_uz32n(stdout, cstr, cstr_len);
}

size_t uprintln_uz16n(const uc16_t *cstr, size_t cstr_len) {
    return ufprintln_uz16n(stdout, cstr, cstr_len);
}

size_t uprintln_uz8n(const uc8_t *cstr, size_t cstr_len) {
    return ufprintln_uz8n(stdout, cstr, cstr_len);
}

size_t ufprint_uz32(FILE *file, const uc32_t *cstr) {
    size_t written = 0;

    while (*cstr)
        written += ufprint_uc32(file, *cstr++);

    return written;
}

size_t ufprint_uz16(FILE *file, const uc16_t *cstr) {
	return ufprint_uz16n(file, cstr, uz16_len(cstr));
}

size_t ufprint_uz8(FILE *file, const uc8_t *cstr) {
	return ufprint_uz8n(file, cstr, uz8_len(cstr));
}

size_t ufprint_uz32n(FILE *file, const uc32_t *cstr, size_t cstr_len) {
    size_t written = 0;

    while (cstr_len--)
        written += ufprint_uc32(file, *cstr++);

    return written;
}

size_t ufprint_uz16n(FILE *file, const uc16_t *cstr, size_t cstr_len) {
    size_t written = 0;

    for (size_t i = 0; i < cstr_len; i += uc16_len(cstr[i])) {
        uc8_t    c8[4];
        unsigned c8_len = uc8_from_uc16n(c8, cstr + i, cstr_len - i);

        written += fwrite(c8, sizeof(uc8_t), c8_len, file);
    }

    return written;
}

size_t ufprint_uz8n(FILE *file, const uc8_t *cstr, size_t cstr_len) {
	return fwrite(cstr, sizeof(uc8_t), cstr_len, file);
}

size_t ufprintln_uz32(FILE *file, const uc32_t *cstr) {
	return ufprint_uz32(file, cstr) + ufprint_new_line(file);
}

size_t ufprintln_uz16(FILE *file, const uc16_t *cstr) {
	return ufprint_uz16(file, cstr) + ufprint_new_line(file);
}

size_t ufprintln_uz8(FILE *file, const uc8_t *cstr) {
	return ufprint_uz8(file, cstr) + ufprint_new_line(file);
}

size_t ufprintln_uz32n(FILE *file, const uc32_t *cstr, size_t cstr_len) {
	return ufprint_uz32n(file, cstr, cstr_len) + ufprint_new_line(file);
}

size_t ufprintln_uz16n(FILE *file, const uc16_t *cstr, size_t cstr_len) {
	return ufprint_uz16n(file, cstr, cstr_len) + ufprint_new_line(file);
}

size_t ufprintln_uz8n(FILE *file, const uc8_t *cstr, size_t cstr_len) {
	return ufprint_uz8n(file, cstr, cstr_len) + ufprint_new_line(file);
}

size_t uprint_ucv32(ucv32_t view) {
    return ufprint_ucv32(stdout, view);
}

size_t uprint_ucv16(ucv16_t view) {
    return ufprint_ucv16(stdout, view);
}

size_t uprint_ucv8(ucv8_t view) {
    return ufprint_ucv8(stdout, view);
}

size_t uprintln_ucv32(ucv32_t view) {
    return ufprintln_ucv32(stdout, view);
}

size_t uprintln_ucv16(ucv16_t view) {
    return ufprintln_ucv16(stdout, view);
}

size_t uprintln_ucv8(ucv8_t view) {
    return ufprintln_ucv8(stdout, view);
}

size_t ufprint_ucv32(FILE *file, ucv32_t view) {
	return ufprint_uz32n(file, UCV32_CEXPAND(view));
}

size_t ufprint_ucv16(FILE *file, ucv16_t view) {
	return ufprint_uz16n(file, UCV16_CEXPAND(view));
}

size_t ufprint_ucv8(FILE *file, ucv8_t view) {
	return ufprint_uz8n(file, UCV8_CEXPAND(view));
}

size_t ufprintln_ucv32(FILE *file, ucv32_t view) {
	return ufprint_ucv32(file, view) + ufprint_new_line(file);
}

size_t ufprintln_ucv16(FILE *file, ucv16_t view) {
	return ufprint_ucv16(file, view) + ufprint_new_line(file);
}

size_t ufprintln_ucv8(FILE *file, ucv8_t view) {
	return ufprint_ucv8(file, view) + ufprint_new_line(file);
}

size_t uprint_us32(const us32_t *str) {
	return ufprint_us32(stdout, str);
}

size_t uprint_us16(const us16_t *str) {
	return ufprint_us16(stdout, str);
}

size_t uprint_us8(const us8_t *str) {
	return ufprint_us8(stdout, str);
}

size_t uprintln_us32(const us32_t *str) {
	return ufprintln_us32(stdout, str);
}

size_t uprintln_us16(const us16_t *str) {
	return ufprintln_us16(stdout, str);
}

size_t uprintln_us8(const us8_t *str) {
	return ufprintln_us8(stdout, str);
}

size_t ufprint_us32(FILE *file, const us32_t *str) {
	return ufprint_uz32n(file, US32_CEXPAND(str));
}

size_t ufprint_us16(FILE *file, const us16_t *str) {
	return ufprint_uz16n(file, US16_CEXPAND(str));
}

size_t ufprint_us8(FILE *file, const us8_t *str) {
	return ufprint_uz8n(file, US8_CEXPAND(str));
}

size_t ufprintln_us32(FILE *file, const us32_t *str) {
	return ufprint_us32(file, str) + ufprint_new_line(file);
}

size_t ufprintln_us16(FILE *file, const us16_t *str) {
	return ufprint_us16(file, str) + ufprint_new_line(file);
}

size_t ufprintln_us8(FILE *file, const us8_t *str) {
	return ufprint_us8(file, str) + ufprint_new_line(file);
}

size_t uprint_uv32(uv32_t view) {
	return ufprint_uv32(stdout, view);
}

size_t uprint_uv16(uv16_t view) {
	return ufprint_uv16(stdout, view);
}

size_t uprint_uv8(uv8_t view) {
	return ufprint_uv8(stdout, view);
}

size_t uprintln_uv32(uv32_t view) {
	return ufprintln_uv32(stdout, view);
}

size_t uprintln_uv16(uv16_t view) {
	return ufprintln_uv16(stdout, view);
}

size_t uprintln_uv8(uv8_t view) {
	return ufprintln_uv8(stdout, view);
}

size_t ufprint_uv32(FILE *file, uv32_t view) {
	return ufprint_uz32n(file, UV32_CEXPAND(view));
}

size_t ufprint_uv16(FILE *file, uv16_t view) {
	return ufprint_uz16n(file, UV16_CEXPAND(view));
}

size_t ufprint_uv8(FILE *file, uv8_t view) {
	return ufprint_uz8n(file, UV8_CEXPAND(view));
}

size_t ufprintln_uv32(FILE *file, uv32_t view) {
	return ufprint_uv32(file, view) + ufprint_new_line(file);
}

size_t ufprintln_uv16(FILE *file, uv16_t view) {
	return ufprint_uv16(file, view) + ufprint_new_line(file);
}

size_t ufprintln_uv8(FILE *file, uv8_t view) {
	return ufprint_uv8(file, view) + ufprint_new_line(file);
}

size_t uprint_new_line(void) {
    return ufprint_new_line(stdout);
}

size_t ufprint_new_line(FILE *file) {
	return ufprint_uc8(file, '\n');
}