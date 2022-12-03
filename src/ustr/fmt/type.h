#ifndef USTR_FMT_TYPE_H
#define USTR_FMT_TYPE_H

#include <stdbool.h>

#include <ustr/type/fmt/type.h>
#include <ustr/cview.h>

static const ucv32_t UTGROUP_INT_NAME     = ucv32("int");
static const ucv32_t UTGROUP_FLOAT_NAME   = ucv32("float");
static const ucv32_t UTGROUP_CHAR_NAME    = ucv32("char");
static const ucv32_t UTGROUP_BOOL_NAME    = ucv32("bool");
static const ucv32_t UTGROUP_STR_NAME     = ucv32("str");
static const ucv32_t UTGROUP_CUSTOM_NAME  = ucv32("custom");
static const ucv32_t UTGROUP_UNKNOWN_NAME = ucv32("unknown");

ucv32_t utgroup_name(utgroup_t group);
bool utgroup_valid(utgroup_t group);

static const ucv32_t UTYPE_FLOAT_NAME     = ucv32("float");
static const ucv32_t UTYPE_DOUBLE_NAME    = ucv32("double");
static const ucv32_t UTYPE_LDOUBLE_NAME   = ucv32("long double");

static const ucv32_t UTYPE_SINT_NAME      = ucv32("short");
static const ucv32_t UTYPE_USINT_NAME     = ucv32("unsigned short");
static const ucv32_t UTYPE_INT_NAME       = ucv32("int");
static const ucv32_t UTYPE_UINT_NAME      = ucv32("unsigned");
static const ucv32_t UTYPE_LINT_NAME      = ucv32("long");
static const ucv32_t UTYPE_ULINT_NAME     = ucv32("unsigned long");
static const ucv32_t UTYPE_LLINT_NAME     = ucv32("long long");
static const ucv32_t UTYPE_ULLINT_NAME    = ucv32("unsigned long long");

static const ucv32_t UTYPE_INT_8_NAME     = ucv32("int8_t");
static const ucv32_t UTYPE_UINT_8_NAME    = ucv32("uint8_t");
static const ucv32_t UTYPE_INT_16_NAME    = ucv32("int16_t");
static const ucv32_t UTYPE_UINT_16_NAME   = ucv32("uint16_t");
static const ucv32_t UTYPE_INT_32_NAME    = ucv32("int32_t");
static const ucv32_t UTYPE_UINT_32_NAME   = ucv32("uint32_t");
static const ucv32_t UTYPE_INT_64_NAME    = ucv32("int64_t");
static const ucv32_t UTYPE_UINT_64_NAME   = ucv32("uint64_t");

static const ucv32_t UTYPE_FAST_8_NAME    = ucv32("int_fast8_t");
static const ucv32_t UTYPE_UFAST_8_NAME   = ucv32("uint_fast8_t");
static const ucv32_t UTYPE_FAST_16_NAME   = ucv32("int_fast16_t");
static const ucv32_t UTYPE_UFAST_16_NAME  = ucv32("uint_fast16_t");
static const ucv32_t UTYPE_FAST_32_NAME   = ucv32("int_fast32_t");
static const ucv32_t UTYPE_UFAST_32_NAME  = ucv32("uint_fast32_t");
static const ucv32_t UTYPE_FAST_64_NAME   = ucv32("int_fast64_t");
static const ucv32_t UTYPE_UFAST_64_NAME  = ucv32("uint_fast64_t");

static const ucv32_t UTYPE_LEAST_8_NAME   = ucv32("int_least8_t");
static const ucv32_t UTYPE_ULEAST_8_NAME  = ucv32("uint_least8_t");
static const ucv32_t UTYPE_LEAST_16_NAME  = ucv32("int_least16_t");
static const ucv32_t UTYPE_ULEAST_16_NAME = ucv32("uint_least16_t");
static const ucv32_t UTYPE_LEAST_32_NAME  = ucv32("int_least32_t");
static const ucv32_t UTYPE_ULEAST_32_NAME = ucv32("uint_least32_t");
static const ucv32_t UTYPE_LEAST_64_NAME  = ucv32("int_least64_t");
static const ucv32_t UTYPE_ULEAST_64_NAME = ucv32("uint_least64_t");

static const ucv32_t UTYPE_MAX_NAME       = ucv32("intmax_t");
static const ucv32_t UTYPE_UMAX_NAME      = ucv32("uintmax_t");

static const ucv32_t UTYPE_PTR_NAME       = ucv32("intptr_t");
static const ucv32_t UTYPE_UPTR_NAME      = ucv32("uintptr_t");

static const ucv32_t UTYPE_SIZE_NAME      = ucv32("size_t");
static const ucv32_t UTYPE_PTRDIFF_NAME   = ucv32("ptrdiff_t");

static const ucv32_t UTYPE_CHAR_NAME      = ucv32("char");
static const ucv32_t UTYPE_SCHAR_NAME     = ucv32("signed char");
static const ucv32_t UTYPE_UCHAR_NAME     = ucv32("unsigned char");

static const ucv32_t UTYPE_CSTR_NAME     = ucv32("char *");

static const ucv32_t UTYPE_BOOL_NAME      = ucv32("bool");

static const ucv32_t UTYPE_UC8_NAME       = ucv32("uc8_t");
static const ucv32_t UTYPE_UC16_NAME      = ucv32("uc16_t");
static const ucv32_t UTYPE_UC32_NAME      = ucv32("uc32_t");

static const ucv32_t UTYPE_UZ8_NAME       = ucv32("uc8_t *");
static const ucv32_t UTYPE_UZ16_NAME      = ucv32("uc16_t *");
static const ucv32_t UTYPE_UZ32_NAME      = ucv32("uc32_t *");

static const ucv32_t UTYPE_US32_NAME      = ucv32("us32_t");
static const ucv32_t UTYPE_UV32_NAME      = ucv32("uv32_t");
static const ucv32_t UTYPE_UCV32_NAME     = ucv32("ucv32_t");

static const ucv32_t UTYPE_CUSTOM_NAME    = ucv32("<custom>");
static const ucv32_t UTYPE_UNKNOWN_NAME   = ucv32("<unknown>");

ucv32_t utype_name(utype_t type);
utgroup_t utype_group(utype_t type);
bool utype_valid(utype_t type);

#endif