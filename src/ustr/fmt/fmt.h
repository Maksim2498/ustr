#ifndef USTR_FMT_FMT_H
#define USTR_FMT_FMT_H

#include <stdbool.h>
#include <stddef.h>

#include <ustr/type/fmt/fmt.h>
#include <ustr/type/char.h>
#include <ustr/type/cview.h>
#include <ustr/type/str.h>
#include <ustr/type/view.h>

struct ufmt ufmt_from_ucv32(ucv32_t view);
struct ufmt ufmt_from_us32(const us32_t *str);
struct ufmt ufmt_from_uv32(uv32_t view);

struct ufmt ufmt_from_uz32(const uc32_t *cstr);
struct ufmt ufmt_from_uz32_n(const uc32_t *cstr, size_t n);

struct ufmt ufmt_from_uz16(const uc16_t *cstr);
struct ufmt ufmt_from_uz16_n(const uc16_t *cstr, size_t n);

struct ufmt ufmt_from_uz8(const uc8_t *cstr);
struct ufmt ufmt_from_uz8_n(const uc8_t *cstr, size_t n);

bool ufmt_valid(const struct ufmt *fmt);

#endif