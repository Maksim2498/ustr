#include "fmt.h"

#include <assert.h>

#include <ustr/char.h>
#include <ustr/cstr.h>
#include <ustr/cview.h>
#include <ustr/str.h>
#include <ustr/view.h>

#include "case.h"
#include "radix.h"
#include "type.h"

static struct ufmt ufmt_from_uz_n_(const void *cstr, size_t n, size_t len);
static uc32_t uget_c_(const void *cstr, size_t n, size_t i);

struct ufmt ufmt_from_ucv32(ucv32_t view) {
    return ufmt_from_uz32_n(UCV32_CEXPAND(view));
}

struct ufmt ufmt_from_us32(const us32_t *str) {
    return ufmt_from_uz32_n(US32_CEXPAND(str));
}

struct ufmt ufmt_from_uv32(uv32_t view) {
    return ufmt_from_uz32_n(UV32_CEXPAND(view));
}

struct ufmt ufmt_from_uz32(const uc32_t *cstr) {
    return ufmt_from_uz32_n(cstr, uz32_len(cstr));
}

struct ufmt ufmt_from_uz32_n(const uc32_t *cstr, size_t n) {
    return ufmt_from_uz_n_(cstr, sizeof(uc32_t), n);
}

struct ufmt ufmt_from_uz16(const uc16_t *cstr) {
    return ufmt_from_uz16_n(cstr, uz16_len(cstr));
}

struct ufmt ufmt_from_uz16_n(const uc16_t *cstr, size_t n) {
    return ufmt_from_uz_n_(cstr, sizeof(uc16_t), n);
}

struct ufmt ufmt_from_uz8(const uc8_t *cstr) {
    return ufmt_from_uz8_n(cstr, uz8_len(cstr));
}

struct ufmt ufmt_from_uz8_n(const uc8_t *cstr, size_t n) {
    return ufmt_from_uz_n_(cstr, sizeof(uc8_t), n);
}

struct ufmt ufmt_from_z(const char *cstr) {
    return ufmt_from_uz8((const uc8_t *) cstr);
}

struct ufmt ufmt_from_z_n(const char *cstr, size_t n) {
    return ufmt_from_uz8_n((const uc8_t *) cstr, n);
}

struct ufmt ufmt_from_uz_n_(const void *cstr, size_t n, size_t len) {
	assert(cstr);

    // Init

    struct uigfmt ifmt = UIGFMT;
    struct ufgfmt ffmt = UFGFMT;
    struct ubgfmt bfmt = UBGFMT;
    struct ufmt   fmt  = UFMT;
 
    size_t prefix_len = 0;
    size_t i          = 0;
    uc32_t c;

    // Plus

    if (i >= len)
        goto exit;

    c = uget_c_(cstr, n, i);

    if ('+' == c) {
        ifmt.show_plus = true;
        ffmt.show_plus = true;
        
        ++prefix_len;
        ++i;
    }

    // Prefix

    if (i >= len)
        goto exit;

    c = uget_c_(cstr, n, i);

    switch (c) {
        case 'X':
            ifmt.radix_prefix_case = UCASE_UPPER;
            goto prefix;

        case 'x':
            ifmt.radix_prefix_case = UCASE_LOWER;

        prefix:
            ifmt.show_radix_prefix = true;

            ++prefix_len;
            ++i;
    }

    // Precision

    if (i >= len)
        goto exit;

    c = uget_c_(cstr, n, i);

    if ('*' == c) {
        fmt.arg_precision = true;
        fmt.use_precision = true;

        ++prefix_len;
        ++i;
    } else if (uc32_dec(c)) {
        do {
            fmt.precision *= 10;
            fmt.precision += uc32_dec_val(c);

            ++prefix_len;
            ++i;

            c = uget_c_(cstr, n, i); 
        } while (i < len && uc32_dec(c));

        fmt.use_precision = true;
    }
    
    // FSA
    
	for (size_t s = 0; i < len; ++i) {
        c = uget_c_(cstr, n, i);

		switch (s) {
			case 0:
                switch (c) {
                    case 'e':
                        fmt.type = UTYPE_FLOAT;
                        fmt.len  = 1;

                        ffmt.scientific = true;
                        ffmt.exp_case   = UCASE_LOWER; 

                        s = 1;

                        continue;

                    case 'E':
                        fmt.type = UTYPE_FLOAT;
                        fmt.len  = 1;

                        ffmt.scientific = true;
                        ffmt.exp_case   = UCASE_UPPER;

                        s = 3;

                        continue;

                    case 'f':
                        fmt.type = UTYPE_FLOAT;
                        fmt.len  = 1;

                        s = 5;

                        continue;

                    case 'd':
                        fmt.type = UTYPE_DOUBLE;
                        fmt.len  = 1;

                        s = 9;

                        continue;

                    case 'l':
                        fmt.type = UTYPE_LINT;
                        fmt.len  = 1;
                    
                        s = 35;
                        
                        continue;

                    case 'b':
                        fmt.type = UTYPE_BOOL;
                        fmt.len  = 1;

                        bfmt.char_case = UCASE_LOWER;

                        ifmt.radix = 2;

                        s = 9;

                        continue;

                    case 'o':
                        ifmt.radix = 8;

                        s = 9;

                        continue;

                    case 'h':
                        ifmt.radix = 16;

                        s = 9;

                        continue;

                    case 'H':
                        ifmt.digit_case = UCASE_UPPER;
                        ifmt.radix      = 16;

                        s = 9;

                        continue;

                    case 's':
                        fmt.type = UTYPE_SINT;
                        fmt.len  = 1;

                        s = 39;

                        continue;

                    case 'i':
                        fmt.type = UTYPE_INT;
                        fmt.len  = 1;

                        s = 44;

                        continue;

                    case 'u':
                        fmt.type = UTYPE_UINT;
                        fmt.len  = 1;

                        s = 48;

                        continue;

                    case 'm':
                        fmt.type = UTYPE_MAX;
                        fmt.len  = 1;

                        goto exit;

                    case 'p':
                        fmt.type = UTYPE_PTR;
                        fmt.len  = 1;

                        goto exit;

                    case 'Z':
                        fmt.type = UTYPE_SIZE;
                        fmt.len  = 1;

                        goto exit;

                    case 'D':
                        fmt.type = UTYPE_PTRDIFF;
                        fmt.len  = 1;

                        goto exit;

                    case 'z':
                        fmt.type = UTYPE_CSTR;
                        fmt.len  = 1;

                        s = 41;

                        continue;

                    case 'c':
                        fmt.type = UTYPE_CHAR;
                        fmt.len  = 1;

                        s = 60;

                        continue;

                    case 'B':
                        fmt.type = UTYPE_BOOL;
                        fmt.len  = 1;

                        bfmt.char_case = UCASE_UPPER;

                        goto exit;

                    case 'v':
                        s = 65;
                        continue;

                    case '!':
                        fmt.type = UTYPE_CUSTOM;
                        fmt.len  = 1;

                    default:
                        goto exit;
                }

            // e
            //
            // type:   float

            case 1:
                switch (c) {
                    case 'f':
                        fmt.len = 2;

                        goto exit;

                    case 'l':
                        s = 2;
                        continue;

                    case 'd':
                        fmt.type = UTYPE_DOUBLE;
                        fmt.len  = 2;

                    default:
                        goto exit;
                }

            // el
            //
            // type: float

            case 2:
                if ('d' == c) {
                    fmt.type = UTYPE_LDOUBLE;
                    fmt.len  = 3;
                }

                goto exit;

            // E
            //
            // type: float

            case 3:
                switch (c) {
                    case 'f':
                        fmt.len = 2;

                        goto exit;

                    case 'l':
                        s = 4;
                        continue;

                    case 'd':
                        fmt.type = UTYPE_DOUBLE;
                        fmt.len  = 2;

                    default:
                        goto exit;
                }

            // El
            //
            // type: float

            case 4:
                if ('d' == c) {
                    fmt.type = UTYPE_LDOUBLE;
                    fmt.len  = 3;
                }

                goto exit;

            // f
            //
            // type: float

            case 5:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_FAST_8;
                        fmt.len  = 2;

                        goto exit;

                    case '1':
                        s = 6;
                        continue;

                    case '3':
                        s = 7;
                        continue;

                    case '6':
                        s = 8;
                        continue;

                    default:
                        goto exit;
                }

            // f1
            //
            // type: float

            case 6:
                if ('6' == c) {
                    fmt.type = UTYPE_FAST_16;
                    fmt.len  = 3;
                }

                goto exit;

            // f3
            //
            // type: float

            case 7:
                if ('2' == c) {
                    fmt.type = UTYPE_FAST_32;
                    fmt.len  = 3;
                }

                goto exit;

            // f6
            //
            // type: float

            case 8:
                if ('4' == c) {
                    fmt.type = UTYPE_FAST_64;
                    fmt.len  = 3;
                }

                goto exit;

            // [bdohH]
            //
            // type: unknown
            //
            // if b:
            //     type: bool
            //
            // if d:
            //     type: double

            case 9:
                switch (c) {
                    case 's':
                        fmt.type = UTYPE_SINT;
                        fmt.len  = 2;

                        s = 10;

                        continue;

                    case 'u':
                        fmt.type = UTYPE_UINT;
                        fmt.len  = 2;

                        s = 11;

                        continue;

                    case 'i':
                        fmt.type = UTYPE_INT;
                        fmt.len  = 2;

                        s = 23;

                        continue;

                    case 'l':
                        fmt.type = UTYPE_LINT;
                        fmt.len  = 2;

                        s = 27;

                        continue;

                    case 'f':
                        s = 31;
                        continue;

                    case 'm':
                        fmt.type = UTYPE_MAX;
                        fmt.len  = 2;

                        goto exit;

                    case 'p':
                        fmt.type = UTYPE_PTR;
                        fmt.len  = 2;

                        goto exit;

                    case 'Z':
                        fmt.type = UTYPE_SIZE;
                        fmt.len  = 2;

                        goto exit;

                    case 'D':
                        fmt.type = UTYPE_PTRDIFF;
                        fmt.len  = 2;

                        goto exit;

                    default:
                        goto exit;
                }

            // [bdohH]s
            //
            // type: sint

            case 10:
                if ('c' == c) {
                    fmt.type = UTYPE_SCHAR;
                    fmt.len  = 3;
                }

                goto exit;

            // [bdohH]u
            //
            // type: uint

            case 11:
                switch (c) {
                    case 's':
                        fmt.type = UTYPE_USINT;
                        fmt.len  = 3;

                        goto exit;

                    case 'l':
                        fmt.type = UTYPE_ULINT;
                        fmt.len  = 3;

                        s = 12;

                        continue;

                    case '8':
                        fmt.type = UTYPE_UINT_8;
                        fmt.len  = 3;

                        goto exit;

                    case '1':
                        s = 16;
                        continue;

                    case '3':
                        s = 17;
                        continue;

                    case '6':
                        s = 18;
                        continue;

                    case 'f':
                        s = 19;
                        continue;

                    case 'm':
                        fmt.type = UTYPE_UMAX;
                        fmt.len  = 3;

                        goto exit;

                    case 'p':
                        fmt.type = UTYPE_UPTR;
                        fmt.len  = 3;

                        goto exit;

                    case 'c':
                        fmt.type = UTYPE_UCHAR;
                        fmt.len  = 3;

                        goto exit;

                    default:
                        goto exit;
                }

            // [bdohH]ul
            //
            // type: ulint

            case 12:
                switch (c) {
                    case 'l':
                        fmt.type = UTYPE_ULLINT;
                        fmt.len  = 4;

                        goto exit;

                    case '8':
                        fmt.type = UTYPE_ULEAST_8;
                        fmt.len  = 4;

                        goto exit;

                    case '1':
                        s = 13;
                        continue;

                    case '3':
                        s = 14;
                        continue;

                    case '6':
                        s = 15;
                        continue;

                    default:
                        goto exit;
                }

            // [bdohH]ul1
            //
            // type: ulint

            case 13:
                if ('6' == c) {
                    fmt.type = UTYPE_ULEAST_16;
                    fmt.len  = 5;
                }

                goto exit;

            // [bdohH]ul3
            //
            // type: ulint

            case 14:
                if ('2' == c) {
                    fmt.type = UTYPE_ULEAST_32;
                    fmt.len  = 5;
                }


                goto exit;

            // [bdohH]ul6
            //
            // type: ulint

            case 15:
                if ('4' == c) {
                    fmt.type = UTYPE_ULEAST_64;
                    fmt.len  = 5;
                }

                goto exit;

            // [bdohH]u1
            //
            // type: uint
            
            case 16:
                if ('6' == c) {
                    fmt.type = UTYPE_UINT_16;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]u3
            //
            // type: uint

            case 17:
                if ('2' == c) {
                    fmt.type = UTYPE_UINT_32;
                    fmt.len  = 4;
                }


                goto exit;

            // [bdohH]u6
            //
            // type: uint
            
            case 18:
                if ('4' == c) {
                    fmt.type = UTYPE_UINT_64;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]uf
            //
            // type: uint

            case 19:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_UFAST_8;
                        fmt.len  = 4;

                        goto exit;

                    case '1':
                        s = 20;
                        continue;

                    case '3':
                        s = 21;
                        continue;

                    case '6':
                        s = 22;
                        continue;

                    default:
                        goto exit;
                }

            // [bdohH]uf1
            //
            // type: uint

            case 20:
                if ('6' == c) {
                    fmt.type = UTYPE_UFAST_16;
                    fmt.len  = 5;
                }

                goto exit;

            // [bdohH]uf3
            //
            // type: uint

            case 21:
                if ('2' == c) {
                    fmt.type = UTYPE_UFAST_32;
                    fmt.len  = 5;
                }

                goto exit;

            // [bdohH]uf6
            //
            // type: uint

            case 22:
                if ('4' == c) {
                    fmt.type = UTYPE_UFAST_64;
                    fmt.len  = 5;
                }

                goto exit;

            // [bdohH]i
            //
            // type: int

            case 23:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_INT_8;
                        fmt.len  = 3;

                        goto exit;

                    case '1':
                        s = 24;
                        continue;

                    case '3':
                        s = 25;
                        continue;

                    case '6':
                        s = 26;
                        continue;

                    default:
                        goto exit;
                }

            // [bdohH]i1
            //
            // type: int

            case 24:
                if ('6' == c) {
                    fmt.type = UTYPE_INT_16;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]i3
            //
            // type: int

            case 25:
                if ('2' == c) {
                    fmt.type = UTYPE_INT_32;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]i6
            //
            // type: int

            case 26:
                if ('4' == c) {
                    fmt.type = UTYPE_INT_64;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]i6
            //
            // tgroup: int 
            // type:   int

            // [bdohH]l
            // 
            // type: lint

            case 27:
                switch (c) {
                    case 'l':
                        fmt.type = UTYPE_LLINT;
                        fmt.len  = 3;

                        goto exit;

                    case '8':
                        fmt.type = UTYPE_LEAST_8;
                        fmt.len  = 3;

                        goto exit;

                    case '1':
                        s = 28;
                        continue;

                    case '3':
                        s = 29;
                        continue;

                    case '6':
                        s = 30;
                        continue;

                    default:
                        goto exit;
                }

            // [bdohH]l1
            // 
            // type: lint

            case 28:
                if ('6' == c) {
                    fmt.type = UTYPE_LEAST_16;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]l3
            // 
            // type: lint

            case 29:
                if ('2' == c) {
                    fmt.type = UTYPE_LEAST_32;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]l6
            // 
            // type: lint

            case 30:
                if ('4' == c) {
                    fmt.type = UTYPE_LEAST_64;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]f
            // 
            // type: unknown
            //
            // if b:
            //     type: bool
            //
            // if d:
            //     type: double

            case 31:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_FAST_8;
                        fmt.len  = 3;

                        goto exit;

                    case '1':
                        s = 32;
                        continue;

                    case '3':
                        s = 33;
                        continue;

                    case '6':
                        s = 34;
                        continue;

                    default:
                        goto exit;
                }

            // [bdohH]f1
            // 
            // type: unknown
            //
            // if b:
            //     type: bool
            //
            // if d:
            //     type: double

            case 32:
                if ('6' == c) {
                    fmt.type = UTYPE_FAST_16;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]f3
            // 
            // type: unknown
            //
            // if b:
            //     type: bool
            //
            // if d:
            //     type: double

            case 33:
                if ('2' == c) {
                    fmt.type = UTYPE_FAST_32;
                    fmt.len  = 4;
                }

                goto exit;

            // [bdohH]f6
            // 
            // type: unknown
            //
            // if b:
            //     type: bool
            //
            // if d:
            //     type: double

            case 34:
                if ('4' == c) {
                    fmt.type = UTYPE_FAST_64;
                    fmt.len  = 4;
                }

                goto exit;

            // l
            //
            // type: lint

            case 35:
                switch (c) {
                    case 'l':
                        fmt.type = UTYPE_LLINT;
                        fmt.len  = 2;

                        goto exit;

                    case 'd':
                        fmt.type = UTYPE_LDOUBLE;
                        fmt.len  = 2;

                        goto exit;

                    case '8':
                        fmt.type = UTYPE_LEAST_8;
                        fmt.len  = 2;

                        goto exit;

                    case '1':
                        s = 36;
                        continue;

                    case '3':
                        s = 37;
                        continue;

                    case '6':
                        s = 38;
                        continue;

                    default:
                        goto exit;
                }

            // l1
            //
            // type: lint

            case 36:
                if ('6' == c) {
                    fmt.type = UTYPE_LEAST_16;
                    fmt.len  = 3;
                }

                goto exit;

            // l3
            //
            // type: lint

            case 37:
                if ('2' == c) {
                    fmt.type = UTYPE_LEAST_32;
                    fmt.len  = 3;
                }

                goto exit;

            // l6
            //
            // type: lint

            case 38:
                if ('4' == c) {
                    fmt.type = UTYPE_LEAST_64;
                    fmt.len  = 3;
                }

                goto exit;

            // s
            //
            // type: sint

            case 39:
                switch (c) {
                    case 'c':
                        fmt.type = UTYPE_SCHAR;
                        fmt.len  = 2;

                        goto exit;

                    case '3':
                        s = 40;
                        continue;

                    default:
                        goto exit;
                }

            // s3
            //
            // type: sint

            case 40:
                if ('2' == c) {
                    fmt.type = UTYPE_US32;
                    fmt.len  = 3;
                }

                goto exit;

            // z
            //
            // type: cstr

            case 41:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_UZ8;
                        fmt.len  = 2;

                        goto exit;

                    case '1':
                        s = 42;
                        continue;

                    case '3':
                        s = 43;
                        continue;

                    default:
                        goto exit;
                }

            // z1
            //
            // type: cstr

            case 42:
                if ('6' == c) {
                    fmt.type = UTYPE_UZ16;
                    fmt.len  = 3;
                }

                goto exit;

            // z3
            //
            // type: cstr

            case 43:
                if ('2' == c) {
                    fmt.type = UTYPE_UZ32;
                    fmt.len  = 3;
                }

                goto exit;

            // i
            //
            // type: int

            case 44:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_INT_8;
                        fmt.len  = 2;

                        goto exit;

                    case '1':
                        s = 45;
                        continue;

                    case '3':
                        s = 46;
                        continue;

                    case '6':
                        s = 47;
                        continue;

                    default:
                        goto exit;
                }

            // i1
            //
            // type: int

            case 45:
                if ('6' == c) {
                    fmt.type = UTYPE_INT_16;
                    fmt.len  = 3;
                }

                goto exit;

            // i3
            //
            // type: int

            case 46:
                if ('2' == c) {
                    fmt.type = UTYPE_INT_32;
                    fmt.len  = 3;
                }

                goto exit;

            // i6
            //
            // type: int

            case 47:
                if ('4' == c) {
                    fmt.type = UTYPE_INT_64;
                    fmt.len  = 3;
                }

                goto exit;

            // u
            //
            // type: uint

            case 48:
                switch (c) {
                    case 's':
                        fmt.type = UTYPE_USINT;
                        fmt.len  = 2;

                        goto exit;

                    case 'l':
                        fmt.type = UTYPE_ULINT;
                        fmt.len  = 2;

                        s = 49;

                        continue;

                    case '8':
                        fmt.type = UTYPE_UINT_8;
                        fmt.len  = 2;

                        goto exit;

                    case '1':
                        s = 53;
                        continue;

                    case '3':
                        s = 54;
                        continue;

                    case '6':
                        s = 55;
                        continue;

                    case 'f':
                        s = 56;
                        continue;

                    case 'm':
                        fmt.type = UTYPE_UMAX;
                        fmt.len  = 2;

                        goto exit;

                    case 'p':
                        fmt.type = UTYPE_UPTR;
                        fmt.len  = 2;

                        goto exit;

                    case 'c':
                        fmt.type = UTYPE_UCHAR;
                        fmt.len  = 2;

                    default:
                        goto exit;
                }

            // ul
            //
            // type: ulint

            case 49:
                switch (c) {
                    case 'l':
                        fmt.type = UTYPE_ULLINT;
                        fmt.len  = 3;

                        goto exit;

                    case '8':
                        fmt.type = UTYPE_ULEAST_8;
                        fmt.len  = 3;

                        goto exit;

                    case '1':
                        s = 50;
                        continue;

                    case '3':
                        s = 51;
                        continue;

                    case '6':
                        s = 52;
                        continue;

                    default:
                        goto exit;
                }

            // ul1
            //
            // type: ulint

            case 50:
                if ('6' == c) {
                    fmt.type = UTYPE_ULEAST_16;
                    fmt.len  = 4;
                }

                goto exit;

            // ul3
            //
            // type: ulint

            case 51:
                if ('2' == c) {
                    fmt.type = UTYPE_ULEAST_32;
                    fmt.len  = 4;
                }

                goto exit;

            // ul6
            //
            // type: ulint

            case 52:
                if ('4' == c) {
                    fmt.type = UTYPE_ULEAST_64;
                    fmt.len  = 4;
                }

                goto exit;

            // u
            //
            // type: uint

            // u1
            //
            // type: ulint

            case 53:
                if ('6' == c) {
                    fmt.type = UTYPE_UINT_16;
                    fmt.len  = 3;
                }

                goto exit;

            // u1
            //
            // type: ulint

            case 54:
                if ('2' == c) {
                    fmt.type = UTYPE_UINT_32;
                    fmt.len  = 3;
                }

                goto exit;

            // u1
            //
            // type: ulint

            case 55:
                if ('4' == c) {
                    fmt.type = UTYPE_UINT_64;
                    fmt.len  = 3;
                }

                goto exit;


            // uf
            //
            // type: ulint

            case 56:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_UFAST_8;
                        fmt.len  = 3;

                        goto exit;

                    case '1':
                        s = 57;
                        continue;

                    case '3':
                        s = 58;
                        continue;

                    case '6':
                        s = 59;
                        continue;

                    default:
                        goto exit;
                }

            // uf1
            //
            // type: ulint

            case 57:
                if ('6' == c) {
                    fmt.type = UTYPE_UFAST_16;
                    fmt.len  = 4;
                }

                goto exit;

            // uf3
            //
            // type: ulint

            case 58:
                if ('2' == c) {
                    fmt.type = UTYPE_UFAST_32;
                    fmt.len  = 4;
                }


                goto exit;

            // uf6
            //
            // type: ulint

            case 59:
                if ('4' == c) {
                    fmt.type = UTYPE_UFAST_64;
                    fmt.len  = 4;
                }

                goto exit;

            // c
            //
            // type: char

            case 60:
                switch (c) {
                    case '8':
                        fmt.type = UTYPE_UC8;
                        fmt.len  = 2;

                        goto exit;

                    case '1':
                        s = 61;
                        continue;

                    case '3':
                        s = 62;
                        continue;

                    case 'v':
                        s = 63;
                        continue;

                    default:
                        goto exit;
                }

            // c1
            //
            // type: char

            case 61:
                if ('6' == c) {
                    fmt.type = UTYPE_UC16;
                    fmt.len  = 3;
                }

                goto exit;

            // c3
            //
            // type: char

            case 62:
                if ('2' == c) {
                    fmt.type = UTYPE_UC32;
                    fmt.len  = 3;
                }

                goto exit;

            // cv
            //
            // type: char

            case 63:
                if ('3' == c) {
                    s = 64;
                    continue;
                }

                goto exit;

            // cv
            //
            // type: char

            case 64:
                if ('2' == c) {
                    fmt.type = UTYPE_UCV32;
                    fmt.len  = 4;
                }

                goto exit;

            // v
            //
            // type: unknown

            case 65:
                if ('3' == c) {
                    s = 66;
                    continue;
                }

                goto exit;

            // v3
            //
            // type: unknown

            case 66:
                if ('2' == c) {
                    fmt.type = UTYPE_UV32;
                    fmt.len  = 3;
                }

            goto exit;

			default:
				assert(false);
		}
	}

    // Return

exit:
    switch (utype_group(fmt.type)) {
        case UTGROUP_INT:
            fmt.i = ifmt;
            break;

        case UTGROUP_FLOAT:
            fmt.f = ffmt;
            break;

        case UTGROUP_BOOL:
            fmt.b = bfmt;
    }

    if (fmt.type != UTYPE_UNKNOWN)
        fmt.len += prefix_len;

    return fmt;
}

uc32_t uget_c_(const void *cstr, size_t n, size_t i) {
    switch (n) {
        case 1:
            return ((uc8_t *) cstr)[i];

        case 2:
            return ((uc16_t *) cstr)[i];

        case 4:
            return ((uc32_t *) cstr)[i];

        default:
            assert(false);
            return 0;
    }
}

bool ufmt_valid(const struct ufmt *fmt) {
    if (!fmt
     || !utype_valid(fmt->type)
     || !fmt->len && fmt->type != UTYPE_UNKNOWN
     || fmt->arg_precision && !fmt->use_precision)
        return false;

    switch (utype_group(fmt->type)) {
        case UTGROUP_INT:
            return uigfmt_valid(&fmt->i);

        case UTGROUP_FLOAT:
            return ufgfmt_valid(&fmt->f);

        case UTGROUP_BOOL:
            return ubgfmt_valid(&fmt->b);

        default:
            return true;
    }
}

bool uigfmt_valid(const struct uigfmt *fmt) {
    return fmt
        && ucase_valid(fmt->digit_case)
        && uradix_valid(fmt->radix)
        && (!fmt->show_radix_prefix || ucase_valid(fmt->radix_prefix_case));
}

bool ufgfmt_valid(const struct ufgfmt *fmt) {
    return fmt
        && ucase_valid(fmt->exp_case);
}

bool ubgfmt_valid(const struct ubgfmt *fmt) {
    return fmt
        && ucase_valid(fmt->char_case);
}