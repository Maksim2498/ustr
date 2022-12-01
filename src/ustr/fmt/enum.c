#include "enum.h"

#include <assert.h>

ucv32_t utype_name(utype_t type) {
    assert(utype_valid(type));

    switch (type) {
		case UTYPE_SINT:
			return UTYPE_SINT_NAME;
 
		case UTYPE_USINT:
			return UTYPE_USINT_NAME;
 
		case UTYPE_INT:
			return UTYPE_INT_NAME;
 
		case UTYPE_UINT:
			return UTYPE_UINT_NAME;
 
		case UTYPE_LINT:
			return UTYPE_LINT_NAME;
 
		case UTYPE_ULINT:
			return UTYPE_ULINT_NAME;
 
		case UTYPE_LLINT:
			return UTYPE_LLINT_NAME;
 
		case UTYPE_ULLINT:
			return UTYPE_ULLINT_NAME;
 
		case UTYPE_INT_8:
			return UTYPE_INT_8_NAME;
 
		case UTYPE_UINT_8:
			return UTYPE_UINT_8_NAME;
 
		case UTYPE_INT_16:
			return UTYPE_INT_16_NAME;
 
		case UTYPE_UINT_16:
			return UTYPE_UINT_16_NAME;
 
		case UTYPE_INT_32:
			return UTYPE_INT_32_NAME;
 
		case UTYPE_UINT_32:
			return UTYPE_UINT_32_NAME;
 
		case UTYPE_INT_64:
			return UTYPE_INT_64_NAME;
 
		case UTYPE_UINT_64:
			return UTYPE_UINT_64_NAME;
 
		case UTYPE_FAST_8:
			return UTYPE_FAST_8_NAME;
 
		case UTYPE_UFAST_8:
			return UTYPE_UFAST_8_NAME;
 
		case UTYPE_FAST_16:
			return UTYPE_FAST_16_NAME;
 
		case UTYPE_UFAST_16:
			return UTYPE_UFAST_16_NAME;
 
		case UTYPE_FAST_32:
			return UTYPE_FAST_32_NAME;
 
		case UTYPE_UFAST_32:
			return UTYPE_UFAST_32_NAME;
 
		case UTYPE_FAST_64:
			return UTYPE_FAST_64_NAME;
 
		case UTYPE_UFAST_64:
			return UTYPE_UFAST_64_NAME;
 
		case UTYPE_LEAST_8:
			return UTYPE_LEAST_8_NAME;
 
		case UTYPE_ULEAST_8:
			return UTYPE_ULEAST_8_NAME;
 
		case UTYPE_LEAST_16:
			return UTYPE_LEAST_16_NAME;
 
		case UTYPE_ULEAST_16:
			return UTYPE_ULEAST_16_NAME;
 
		case UTYPE_LEAST_32:
			return UTYPE_LEAST_32_NAME;
 
		case UTYPE_ULEAST_32:
			return UTYPE_ULEAST_32_NAME;
 
		case UTYPE_LEAST_64:
			return UTYPE_LEAST_64_NAME;
 
		case UTYPE_ULEAST_64:
			return UTYPE_ULEAST_64_NAME;
 
		case UTYPE_MAX:
			return UTYPE_MAX_NAME;
 
		case UTYPE_UMAX:
			return UTYPE_UMAX_NAME;
 
		case UTYPE_PTR:
			return UTYPE_PTR_NAME;
 
		case UTYPE_UPTR:
			return UTYPE_UPTR_NAME;
 
		case UTYPE_SIZE:
			return UTYPE_SIZE_NAME;

		case UTYPE_PTRDIFF:
			return UTYPE_PTRDIFF_NAME;
 
		case UTYPE_CHAR:
			return UTYPE_CHAR_NAME;
 
		case UTYPE_SCHAR:
			return UTYPE_SCHAR_NAME;
 
		case UTYPE_UCHAR:
			return UTYPE_UCHAR_NAME;
 
		case UTYPE_BOOL:
			return UTYPE_BOOL_NAME;
 
		case UTYPE_UC8:
			return UTYPE_UC8_NAME;

		case UTYPE_UC16:
			return UTYPE_UC16_NAME;
 
		case UTYPE_UC32:
			return UTYPE_UC32_NAME;
 
		case UTYPE_UZ8:
			return UTYPE_UZ8_NAME;
 
		case UTYPE_UZ16:
			return UTYPE_UZ16_NAME;
 
		case UTYPE_UZ32:
			return UTYPE_UZ32_NAME;

		case UTYPE_US32:
			return UTYPE_US32_NAME;

		case UTYPE_UV32:
			return UTYPE_UV32_NAME;

		case UTYPE_UCV32:
			return UTYPE_UCV32_NAME;

		case UTYPE_UCASE:
			return UTYPE_UCASE_NAME;
 
		case UTYPE_UTYPE:
			return UTYPE_UTYPE_NAME;
 
		case UTYPE_URADIX:
			return UTYPE_URADIX_NAME;
 
		case UTYPE_ENCODING:
			return UTYPE_ENCODING_NAME;
 
		case UTYPE_ENDIAN:
			return UTYPE_ENDIAN_NAME;
            
        default:
            assert(false);
            return ucv32_mk();
    }
}

bool utype_valid(utype_t type) {
    return type < UTYPE_COUNT;
}