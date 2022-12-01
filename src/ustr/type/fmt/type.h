#ifndef USTR_TYPE_FMT_TYPE_H
#define USTR_TYPE_FMT_TYPE_H

enum {
    UTYPE_MAX_LEN = 5
};

enum {
    UTYPE_SINT,      //   s[bodhH]?
    UTYPE_USINT,     //  us[bodhH]?
    UTYPE_INT,       //    [dobhH]
    UTYPE_UINT,      //   u[dobhH]?
    UTYPE_LINT,      //   l[dobhH]?
    UTYPE_ULINT,     //  ul[dobhH]?
    UTYPE_LLINT,     //  ll[dobhH]?
    UTYPE_ULLINT,    // ull[dobhH]?

    UTYPE_INT_8,     //  [dobhH]8
    UTYPE_UINT_8,    // u[dobhH]?8
    UTYPE_INT_16,    //  [dobhH]16
    UTYPE_UINT_16,   // u[dobhH]?16
    UTYPE_INT_32,    //  [dobhH]32
    UTYPE_UINT_32,   // u[dobhH]?32
    UTYPE_INT_64,    //  [dobhH]64
    UTYPE_UINT_64,   // u[dobhH]?64

    UTYPE_FAST_8,    //  F[dobhH]?8
    UTYPE_UFAST_8,   // uF[dobhH]?8
    UTYPE_FAST_16,   //  F[dobhH]?16
    UTYPE_UFAST_16,  // uF[dobhH]?16
    UTYPE_FAST_32,   //  F[dobhH]?32
    UTYPE_UFAST_32,  // uF[dobhH]?32
    UTYPE_FAST_64,   //  F[dobhH]?64
    UTYPE_UFAST_64,  // uF[dobhH]?64

    UTYPE_LEAST_8,   //  L[dobhH]?8
    UTYPE_ULEAST_8,  // uL[dobhH]?8
    UTYPE_LEAST_16,  //  L[dobhH]?16
    UTYPE_ULEAST_16, // uL[dobhH]?16
    UTYPE_LEAST_32,  //  L[dobhH]?32
    UTYPE_ULEAST_32, // uL[dobhH]?32
    UTYPE_LEAST_64,  //  L[dobhH]?64
    UTYPE_ULEAST_64, // uL[dobhH]?64

    UTYPE_MAX,       //  m[dobhH]?
    UTYPE_UMAX,      // um[dobhH]?
    
    UTYPE_PTR,       //  p[dobhH]?
    UTYPE_UPTR,      // up[dobhH]?

    UTYPE_SIZE,      // z[dobhH]?
    UTYPE_PTRDIFF,   // D[dobhH]?

    UTYPE_CHAR,      //  c
    UTYPE_SCHAR,     // sc[dobhH]?
    UTYPE_UCHAR,     // uc[dobhH]?

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

    UTYPE_UCASE,     // C
    UTYPE_UTYPE,     // t
    UTYPE_URADIX,    // r
    UTYPE_ENCODING,  // E
    UTYPE_ENDIAN,    // e

    UTYPE_CUSTOM,    // %
    UTYPE_UNKNOWN,

    UTYPE_COUNT
};

typedef unsigned char utype_t;

#endif