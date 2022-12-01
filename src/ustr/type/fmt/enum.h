#ifndef USTR_TYPE_FMT_ENUM_H
#define USTR_TYPE_FMT_ENUM_H

enum {
    UTYPE_SINT,
    UTYPE_USINT,
    UTYPE_INT,
    UTYPE_UINT,
    UTYPE_LINT,
    UTYPE_ULINT,
    UTYPE_LLINT,
    UTYPE_ULLINT,

    UTYPE_INT_8,
    UTYPE_UINT_8,
    UTYPE_INT_16,
    UTYPE_UINT_16,
    UTYPE_INT_32,
    UTYPE_UINT_32,
    UTYPE_INT_64,
    UTYPE_UINT_64,

    UTYPE_FAST_8,
    UTYPE_UFAST_8,
    UTYPE_FAST_16,
    UTYPE_UFAST_16,
    UTYPE_FAST_32,
    UTYPE_UFAST_32,
    UTYPE_FAST_64,
    UTYPE_UFAST_64,

    UTYPE_LEAST_8,
    UTYPE_ULEAST_8,
    UTYPE_LEAST_16,
    UTYPE_ULEAST_16,
    UTYPE_LEAST_32,
    UTYPE_ULEAST_32,
    UTYPE_LEAST_64,
    UTYPE_ULEAST_64,

    UTYPE_MAX,
    UTYPE_UMAX,
    
    UTYPE_PTR,
    UTYPE_UPTR,

    UTYPE_SIZE,
    UTYPE_PTRDIFF,

    UTYPE_CHAR,
    UTYPE_SCHAR,
    UTYPE_UCHAR,

    UTYPE_BOOL,

    UTYPE_UC8,
    UTYPE_UC16,
    UTYPE_UC32,

    UTYPE_UZ8,
    UTYPE_UZ16,
    UTYPE_UZ32,

    UTYPE_US32,
    UTYPE_UV32,
    UTYPE_UCV32,

    UTYPE_UCASE,
    UTYPE_UTYPE,
    UTYPE_URADIX,
    UTYPE_ENCODING,
    UTYPE_ENDIAN,

    UTYPE_COUNT
};

typedef unsigned char utype_t;

#endif