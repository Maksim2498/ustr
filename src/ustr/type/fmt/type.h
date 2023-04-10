#ifndef USTR_TYPE_FMT_TYPE_H
#define USTR_TYPE_FMT_TYPE_H

#include <ustr/util/name.h>

// Type group

// - Name

UEXPORT_NAME(UTGROUP_INT,     "INT");
UEXPORT_NAME(UTGROUP_FLOAT,   "FLAOT");
UEXPORT_NAME(UTGROUP_CHAR,    "CHAR");
UEXPORT_NAME(UTGROUP_BOOL,    "BOOL");
UEXPORT_NAME(UTGROUP_STR,     "STR");
UEXPORT_NAME(UTGROUP_CUSTOM,  "CUSTOM");
UEXPORT_NAME(UTGROUP_UNKNOWN, "UNKNOWN");

// - Type

enum {
    UTGROUP_INT,
    UTGROUP_FLOAT,
    UTGROUP_CHAR,
    UTGROUP_BOOL,
    UTGROUP_STR,
    UTGROUP_CUSTOM,
    UTGROUP_UNKNOWN,
    UTGROUP_COUNT
};

typedef unsigned char utgroup_t;

// Type

// - Name

UEXPORT_NAME(UTYPE_FLOAT,    "float");
UEXPORT_NAME(UTYPE_DOUBLE,   "double");
UEXPORT_NAME(UTYPE_LDOUBLE,  "long double");

UEXPORT_NAME(UTYPE_SINT,     "short");
UEXPORT_NAME(UTYPE_USINT,    "unsigned short");
UEXPORT_NAME(UTYPE_INT,      "int");
UEXPORT_NAME(UTYPE_UINT,     "unsigned");
UEXPORT_NAME(UTYPE_LINT,     "long");
UEXPORT_NAME(UTYPE_ULINT,    "unsigned long");
UEXPORT_NAME(UTYPE_LLINT,    "long long");
UEXPORT_NAME(UTYPE_ULLINT,   "unsigned long long");

UEXPORT_NAME(UTYPE_INT8,     "int8_t");
UEXPORT_NAME(UTYPE_UINT8,    "uint8_t");
UEXPORT_NAME(UTYPE_INT16,    "int16_t");
UEXPORT_NAME(UTYPE_UINT16,   "uint16_t");
UEXPORT_NAME(UTYPE_INT32,    "int32_t");
UEXPORT_NAME(UTYPE_UINT32,   "uint32_t");
UEXPORT_NAME(UTYPE_INT64,    "int64_t");
UEXPORT_NAME(UTYPE_UINT64,   "uint64_t");

UEXPORT_NAME(UTYPE_FAST8,    "int_fast8_t");
UEXPORT_NAME(UTYPE_UFAST8,   "uint_fast8_t");
UEXPORT_NAME(UTYPE_FAST16,   "int_fast16_t");
UEXPORT_NAME(UTYPE_UFAST16,  "uint_fast16_t");
UEXPORT_NAME(UTYPE_FAST32,   "int_fast32_t");
UEXPORT_NAME(UTYPE_UFAST32,  "uint_fast32_t");
UEXPORT_NAME(UTYPE_FAST64,   "int_fast64_t");
UEXPORT_NAME(UTYPE_UFAST64,  "uint_fast64_t");

UEXPORT_NAME(UTYPE_LEAST8,   "int_least8_t");
UEXPORT_NAME(UTYPE_ULEAST8,  "uint_least8_t");
UEXPORT_NAME(UTYPE_LEAST16,  "int_least16_t");
UEXPORT_NAME(UTYPE_ULEAST16, "uint_least16_t");
UEXPORT_NAME(UTYPE_LEAST32,  "int_least32_t");
UEXPORT_NAME(UTYPE_ULEAST32, "uint_least32_t");
UEXPORT_NAME(UTYPE_LEAST64,  "int_least64_t");
UEXPORT_NAME(UTYPE_ULEAST64, "uint_least64_t");

UEXPORT_NAME(UTYPE_MAX,      "intmax_t");
UEXPORT_NAME(UTYPE_UMAX,     "uintmax_t");

UEXPORT_NAME(UTYPE_PTR,      "intptr_t");
UEXPORT_NAME(UTYPE_UPTR,     "uintptr_t");

UEXPORT_NAME(UTYPE_SIZE,     "size_t");
UEXPORT_NAME(UTYPE_PTRDIFF,  "ptrdiff_t");

UEXPORT_NAME(UTYPE_CHAR,     "char");
UEXPORT_NAME(UTYPE_SCHAR,    "signed char");
UEXPORT_NAME(UTYPE_UCHAR,    "unsigned char");

UEXPORT_NAME(UTYPE_CSTR,     "char *");

UEXPORT_NAME(UTYPE_BOOL,     "bool");

UEXPORT_NAME(UTYPE_UC32,     "uc32_t");
UEXPORT_NAME(UTYPE_UC16,     "uc16_t");
UEXPORT_NAME(UTYPE_UC8,      "uc8_t");

UEXPORT_NAME(UTYPE_UZ32,     "uc32_t *");
UEXPORT_NAME(UTYPE_UZ16,     "uc16_t *");
UEXPORT_NAME(UTYPE_UZ8,      "uc8_t *");

UEXPORT_NAME(UTYPE_US32,     "us32_t");
UEXPORT_NAME(UTYPE_US16,     "us16_t");
UEXPORT_NAME(UTYPE_US8,      "us8_t");

UEXPORT_NAME(UTYPE_UV32,     "uv32_t");
UEXPORT_NAME(UTYPE_UV16,     "uv16_t");
UEXPORT_NAME(UTYPE_UV8,      "uv8_t");

UEXPORT_NAME(UTYPE_UCV32,    "ucv32_t");
UEXPORT_NAME(UTYPE_UCV16,    "ucv16_t");
UEXPORT_NAME(UTYPE_UCV8,     "ucv8_t");

UEXPORT_NAME(UTYPE_CUSTOM,   "<custom>");

UEXPORT_NAME(UTYPE_UNKNOWN,   "<unknown>");

// - Type

enum {
    UTYPE_FLOAT,     // [eE]?f | [eE]
    UTYPE_DOUBLE,    // [eE]?d,
    UTYPE_LDOUBLE,   // [eE]ld

    UTYPE_SINT,      // [bodhH]?s
    UTYPE_USINT,     // [bodhH]?us
    UTYPE_INT,       // [dobhH]?i
    UTYPE_UINT,      // [dobhH]?u
    UTYPE_LINT,      // [dobhH]?l
    UTYPE_ULINT,     // [dobhH]?ul
    UTYPE_LLINT,     // [dobhH]?ll
    UTYPE_ULLINT,    // [dobhH]?ull

    UTYPE_INT8,     // [dobhH]?i8
    UTYPE_UINT8,    // [dobhH]?u8
    UTYPE_INT16,    // [dobhH]?i16
    UTYPE_UINT16,   // [dobhH]?u16
    UTYPE_INT32,    // [dobhH]?i32
    UTYPE_UINT32,   // [dobhH]?u32
    UTYPE_INT64,    // [dobhH]?i64
    UTYPE_UINT64,   // [dobhH]?u64

    UTYPE_FAST8,    // [dobhH]?f8
    UTYPE_UFAST8,   // [dobhH]?uf8
    UTYPE_FAST16,   // [dobhH]?f16
    UTYPE_UFAST16,  // [dobhH]?uf16
    UTYPE_FAST32,   // [dobhH]?f32
    UTYPE_UFAST32,  // [dobhH]?uf32
    UTYPE_FAST64,   // [dobhH]?f64
    UTYPE_UFAST64,  // [dobhH]?uf64

    UTYPE_LEAST8,   // [dobhH]?l8
    UTYPE_ULEAST8,  // [dobhH]?ul8
    UTYPE_LEAST16,  // [dobhH]?l16
    UTYPE_ULEAST16, // [dobhH]?ul16
    UTYPE_LEAST32,  // [dobhH]?l32
    UTYPE_ULEAST32, // [dobhH]?ul32
    UTYPE_LEAST64,  // [dobhH]?l64
    UTYPE_ULEAST64, // [dobhH]?ul64

    UTYPE_MAX,       // [dobhH]?m
    UTYPE_UMAX,      // [dobhH]?um
    
    UTYPE_PTR,       // [dobhH]?p
    UTYPE_UPTR,      // [dobhH]?up

    UTYPE_SIZE,      // [dobhH]?Z
    UTYPE_PTRDIFF,   // [dobhH]?D

    UTYPE_CHAR,      // c
    UTYPE_SCHAR,     // [dobhH]?sc
    UTYPE_UCHAR,     // [dobhH]?uc

    UTYPE_CSTR,      // z

    UTYPE_BOOL,      // [bB]

    UTYPE_UC32,      // c32
    UTYPE_UC16,      // c16
    UTYPE_UC8,       // c8

    UTYPE_UZ32,      // z32
    UTYPE_UZ16,      // z16
    UTYPE_UZ8,       // z8

    UTYPE_US32,      // s32
    UTYPE_US16,      // s16
    UTYPE_US8,       // s8

    UTYPE_UV32,      // v32
    UTYPE_UV16,      // v16
    UTYPE_UV8,       // v8

    UTYPE_UCV32,     // cv32
    UTYPE_UCV16,     // cv16
    UTYPE_UCV8,      // cv8

    UTYPE_CUSTOM,    // !

    UTYPE_UNKNOWN,

    UTYPE_COUNT
};

typedef unsigned char utype_t;

#endif