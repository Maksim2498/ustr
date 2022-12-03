#include "type.h"

#include <assert.h>

ucv32_t utgroup_name(utgroup_t group) {
	assert(utgroup_valid(group));

	switch (group) {
		case UTGROUP_INT:
			return UTGROUP_INT_NAME;

		case UTGROUP_FLOAT:
			return UTGROUP_FLOAT_NAME;

		case UTGROUP_CHAR:
			return UTGROUP_CHAR_NAME;

		case UTGROUP_BOOL:
			return UTGROUP_BOOL_NAME;

		case UTGROUP_STR:
			return UTGROUP_STR_NAME;

		case UTGROUP_CUSTOM:
			return UTGROUP_CUSTOM_NAME;

		default:
			return UTGROUP_UNKNOWN_NAME;
	}
}

bool utgroup_valid(utgroup_t group) {
	return group < UTGROUP_COUNT;
}

ucv32_t utype_name(utype_t type) {
    assert(utype_valid(type));

    switch (type) {
		case UTYPE_FLOAT:
			return UTYPE_FLOAT_NAME;

		case UTYPE_DOUBLE:
			return UTYPE_DOUBLE_NAME;

		case UTYPE_LDOUBLE:
			return UTYPE_LDOUBLE_NAME;

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

		case UTYPE_CSTR:
			return UTYPE_CSTR_NAME;
 
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

		case UTYPE_CUSTOM:
			return UTYPE_CUSTOM_NAME;

        default:
			return UTYPE_UNKNOWN_NAME;
    }
}

utgroup_t utype_group(utype_t type) {
	assert(utype_valid(type));

	switch (type) {
		case UTYPE_FLOAT:
		case UTYPE_DOUBLE:
		case UTYPE_LDOUBLE:
			return UTGROUP_FLOAT;

		case UTYPE_SINT:
		case UTYPE_USINT:
		case UTYPE_INT:
		case UTYPE_UINT:
		case UTYPE_LINT:
		case UTYPE_ULINT:
		case UTYPE_LLINT:
		case UTYPE_ULLINT:
		case UTYPE_INT_8:
		case UTYPE_UINT_8:
		case UTYPE_INT_16:
		case UTYPE_UINT_16:
		case UTYPE_INT_32:
		case UTYPE_UINT_32:
		case UTYPE_INT_64:
		case UTYPE_UINT_64:
		case UTYPE_FAST_8:
		case UTYPE_UFAST_8:
		case UTYPE_FAST_16:
		case UTYPE_UFAST_16:
		case UTYPE_FAST_32:
		case UTYPE_UFAST_32:
		case UTYPE_FAST_64:
		case UTYPE_UFAST_64:
		case UTYPE_LEAST_8:
		case UTYPE_ULEAST_8:
		case UTYPE_LEAST_16:
		case UTYPE_ULEAST_16:
		case UTYPE_LEAST_32:
		case UTYPE_ULEAST_32:
		case UTYPE_LEAST_64:
		case UTYPE_ULEAST_64:
		case UTYPE_MAX:
		case UTYPE_UMAX:
		case UTYPE_PTR:
		case UTYPE_UPTR:
		case UTYPE_SIZE:
		case UTYPE_PTRDIFF:
		case UTYPE_SCHAR:
		case UTYPE_UCHAR:
			return UTGROUP_INT;

		case UTYPE_CHAR:
		case UTYPE_UC8:
		case UTYPE_UC16:
		case UTYPE_UC32:
			return UTGROUP_CHAR;

		case UTYPE_BOOL:
			return UTGROUP_BOOL;

		case UTYPE_CSTR:
		case UTYPE_UZ8:
		case UTYPE_UZ16:
		case UTYPE_UZ32:
		case UTYPE_US32:
		case UTYPE_UV32:
		case UTYPE_UCV32:
			return UTGROUP_STR;

		case UTYPE_CUSTOM:
			return UTGROUP_CUSTOM;

        default:
			return UTGROUP_UNKNOWN;
	}
}

bool utype_valid(utype_t type) {
    return type < UTYPE_COUNT;
}