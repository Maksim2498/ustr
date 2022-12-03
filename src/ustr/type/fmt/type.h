#ifndef USTR_TYPE_FMT_TYPE_H
#define USTR_TYPE_FMT_TYPE_H

enum {
    UTYPE_MAX_LEN = 5
};

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

    UTYPE_INT_8,     // [dobhH]?i8
    UTYPE_UINT_8,    // [dobhH]?u8
    UTYPE_INT_16,    // [dobhH]?i16
    UTYPE_UINT_16,   // [dobhH]?u16
    UTYPE_INT_32,    // [dobhH]?i32
    UTYPE_UINT_32,   // [dobhH]?u32
    UTYPE_INT_64,    // [dobhH]?i64
    UTYPE_UINT_64,   // [dobhH]?u64

    UTYPE_FAST_8,    // [dobhH]?f8
    UTYPE_UFAST_8,   // [dobhH]?uf8
    UTYPE_FAST_16,   // [dobhH]?f16
    UTYPE_UFAST_16,  // [dobhH]?uf16
    UTYPE_FAST_32,   // [dobhH]?f32
    UTYPE_UFAST_32,  // [dobhH]?uf32
    UTYPE_FAST_64,   // [dobhH]?f64
    UTYPE_UFAST_64,  // [dobhH]?uf64

    UTYPE_LEAST_8,   // [dobhH]?l8
    UTYPE_ULEAST_8,  // [dobhH]?ul8
    UTYPE_LEAST_16,  // [dobhH]?l16
    UTYPE_ULEAST_16, // [dobhH]?ul16
    UTYPE_LEAST_32,  // [dobhH]?l32
    UTYPE_ULEAST_32, // [dobhH]?ul32
    UTYPE_LEAST_64,  // [dobhH]?l64
    UTYPE_ULEAST_64, // [dobhH]?ul64

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

    UTYPE_UC8,       // c8
    UTYPE_UC16,      // c16
    UTYPE_UC32,      // c32

    UTYPE_UZ8,       // z8
    UTYPE_UZ16,      // z16
    UTYPE_UZ32,      // z32

    UTYPE_US32,      // s32
    UTYPE_UV32,      // v32
    UTYPE_UCV32,     // cv32

    UTYPE_CUSTOM,    // !
    UTYPE_UNKNOWN,

    UTYPE_COUNT
};

typedef unsigned char utype_t;

#endif