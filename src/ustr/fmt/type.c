#include "type.h"

#include <assert.h>

#define UTGROUP_NAME_X(group, X)             \
    assert(utgroup_valid(group));            \
                                             \
    switch (group) {                         \
        case UTGROUP_INT:                    \
            return UTGROUP_INT_NAME_##X;     \
                                             \
        case UTGROUP_FLOAT:                  \
            return UTGROUP_FLOAT_NAME_##X;   \
                                             \
        case UTGROUP_CHAR:                   \
            return UTGROUP_CHAR_NAME_##X;    \
                                             \
        case UTGROUP_BOOL:                   \
            return UTGROUP_BOOL_NAME_##X;    \
                                             \
        case UTGROUP_STR:                    \
            return UTGROUP_STR_NAME_##X;     \
                                             \
        case UTGROUP_CUSTOM:                 \
            return UTGROUP_CUSTOM_NAME_##X;  \
                                             \
        default:                             \
            return UTGROUP_UNKNOWN_NAME_##X; \
    }

ucv32_t utgroup_name_32(utgroup_t group) {
    UTGROUP_NAME_X(group, 32);
}

ucv16_t utgroup_name_16(utgroup_t group) {
    UTGROUP_NAME_X(group, 16);
}

ucv8_t utgroup_name_8(utgroup_t group) {
    UTGROUP_NAME_X(group, 8);
}

bool utgroup_valid(utgroup_t group) {
    return group < UTGROUP_COUNT;
}

#define UTYPE_NAME_X(type, X)                \
    assert(utype_valid(type));               \
                                             \
    switch (type) {                          \
        case UTYPE_FLOAT:                    \
            return UTYPE_FLOAT_NAME_##X;     \
                                             \
        case UTYPE_DOUBLE:                   \
            return UTYPE_DOUBLE_NAME_##X;    \
                                             \
        case UTYPE_LDOUBLE:                  \
            return UTYPE_LDOUBLE_NAME_##X;   \
                                             \
        case UTYPE_SINT:                     \
            return UTYPE_SINT_NAME_##X;      \
                                             \
        case UTYPE_USINT:                    \
            return UTYPE_USINT_NAME_##X;     \
                                             \
        case UTYPE_INT:                      \
            return UTYPE_INT_NAME_##X;       \
                                             \
        case UTYPE_UINT:                     \
            return UTYPE_UINT_NAME_##X;      \
                                             \
        case UTYPE_LINT:                     \
            return UTYPE_LINT_NAME_##X;      \
                                             \
        case UTYPE_ULINT:                    \
            return UTYPE_ULINT_NAME_##X;     \
                                             \
        case UTYPE_LLINT:                    \
            return UTYPE_LLINT_NAME_##X;     \
                                             \
        case UTYPE_ULLINT:                   \
            return UTYPE_ULLINT_NAME_##X;    \
                                             \
        case UTYPE_INT8:                     \
            return UTYPE_INT8_NAME_##X;      \
                                             \
        case UTYPE_UINT8:                    \
            return UTYPE_UINT8_NAME_##X;     \
                                             \
        case UTYPE_INT16:                    \
            return UTYPE_INT16_NAME_##X;     \
                                             \
        case UTYPE_UINT16:                   \
            return UTYPE_UINT16_NAME_##X;    \
                                             \
        case UTYPE_INT32:                    \
            return UTYPE_INT32_NAME_##X;     \
                                             \
        case UTYPE_UINT32:                   \
            return UTYPE_UINT32_NAME_##X;    \
                                             \
        case UTYPE_INT64:                    \
            return UTYPE_INT64_NAME_##X;     \
                                             \
        case UTYPE_UINT64:                   \
            return UTYPE_UINT64_NAME_##X;    \
                                             \
        case UTYPE_FAST8:                    \
            return UTYPE_FAST8_NAME_##X;     \
                                             \
        case UTYPE_UFAST8:                   \
            return UTYPE_UFAST8_NAME_##X;    \
                                             \
        case UTYPE_FAST16:                   \
            return UTYPE_FAST16_NAME_##X;    \
                                             \
        case UTYPE_UFAST16:                  \
            return UTYPE_UFAST16_NAME_##X;   \
                                             \
        case UTYPE_FAST32:                   \
            return UTYPE_FAST32_NAME_##X;    \
                                             \
        case UTYPE_UFAST32:                  \
            return UTYPE_UFAST32_NAME_##X;   \
                                             \
        case UTYPE_FAST64:                   \
            return UTYPE_FAST64_NAME_##X;    \
                                             \
        case UTYPE_UFAST64:                  \
            return UTYPE_UFAST64_NAME_##X;   \
                                             \
        case UTYPE_LEAST8:                   \
            return UTYPE_LEAST8_NAME_##X;    \
                                             \
        case UTYPE_ULEAST8:                  \
            return UTYPE_ULEAST8_NAME_##X;   \
                                             \
        case UTYPE_LEAST16:                  \
            return UTYPE_LEAST16_NAME_##X;   \
                                             \
        case UTYPE_ULEAST16:                 \
            return UTYPE_ULEAST16_NAME_##X;  \
                                             \
        case UTYPE_LEAST32:                  \
            return UTYPE_LEAST32_NAME_##X;   \
                                             \
        case UTYPE_ULEAST32:                 \
            return UTYPE_ULEAST32_NAME_##X;  \
                                             \
        case UTYPE_LEAST64:                  \
            return UTYPE_LEAST64_NAME_##X;   \
                                             \
        case UTYPE_ULEAST64:                 \
            return UTYPE_ULEAST64_NAME_##X;  \
                                             \
        case UTYPE_MAX:                      \
            return UTYPE_MAX_NAME_##X;       \
                                             \
        case UTYPE_UMAX:                     \
            return UTYPE_UMAX_NAME_##X;      \
                                             \
        case UTYPE_PTR:                      \
            return UTYPE_PTR_NAME_##X;       \
                                             \
        case UTYPE_UPTR:                     \
            return UTYPE_UPTR_NAME_##X;      \
                                             \
        case UTYPE_SIZE:                     \
            return UTYPE_SIZE_NAME_##X;      \
                                             \
        case UTYPE_PTRDIFF:                  \
            return UTYPE_PTRDIFF_NAME_##X;   \
                                             \
        case UTYPE_CHAR:                     \
            return UTYPE_CHAR_NAME_##X;      \
                                             \
        case UTYPE_SCHAR:                    \
            return UTYPE_SCHAR_NAME_##X;     \
                                             \
        case UTYPE_UCHAR:                    \
            return UTYPE_UCHAR_NAME_##X;     \
                                             \
        case UTYPE_CSTR:                     \
            return UTYPE_CSTR_NAME_##X;      \
                                             \
        case UTYPE_BOOL:                     \
            return UTYPE_BOOL_NAME_##X;      \
                                             \
        case UTYPE_UC32:                     \
            return UTYPE_UC32_NAME_##X;      \
                                             \
        case UTYPE_UC16:                     \
            return UTYPE_UC16_NAME_##X;      \
                                             \
        case UTYPE_UC8:                      \
            return UTYPE_UC8_NAME_##X;       \
                                             \
        case UTYPE_UZ8:                      \
            return UTYPE_UZ8_NAME_##X;       \
                                             \
        case UTYPE_UZ16:                     \
            return UTYPE_UZ16_NAME_##X;      \
                                             \
        case UTYPE_UZ32:                     \
            return UTYPE_UZ32_NAME_##X;      \
                                             \
        case UTYPE_US32:                     \
            return UTYPE_US32_NAME_##X;      \
                                             \
        case UTYPE_US16:                     \
            return UTYPE_US16_NAME_##X;      \
                                             \
        case UTYPE_US8:                      \
            return UTYPE_US8_NAME_##X;       \
                                             \
        case UTYPE_UV32:                     \
            return UTYPE_UV32_NAME_##X;      \
                                             \
        case UTYPE_UV16:                     \
            return UTYPE_UV16_NAME_##X;      \
                                             \
        case UTYPE_UV8:                      \
            return UTYPE_UV8_NAME_##X;       \
                                             \
        case UTYPE_UCV32:                    \
            return UTYPE_UCV32_NAME_##X;     \
                                             \
        case UTYPE_UCV16:                    \
            return UTYPE_UCV16_NAME_##X;     \
                                             \
        case UTYPE_UCV8:                     \
            return UTYPE_UCV8_NAME_##X;      \
                                             \
        case UTYPE_CUSTOM:                   \
            return UTYPE_CUSTOM_NAME_##X;    \
                                             \
        default:                             \
            return UTYPE_UNKNOWN_NAME_##X;   \
    }

ucv32_t utype_name_32(utype_t type) {
    UTYPE_NAME_X(type, 32);
}

ucv16_t utype_name_16(utype_t type) {
    UTYPE_NAME_X(type, 16);
}

ucv8_t utype_name_8(utype_t type) {
    UTYPE_NAME_X(type, 8);
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
        case UTYPE_INT8:
        case UTYPE_UINT8:
        case UTYPE_INT16:
        case UTYPE_UINT16:
        case UTYPE_INT32:
        case UTYPE_UINT32:
        case UTYPE_INT64:
        case UTYPE_UINT64:
        case UTYPE_FAST8:
        case UTYPE_UFAST8:
        case UTYPE_FAST16:
        case UTYPE_UFAST16:
        case UTYPE_FAST32:
        case UTYPE_UFAST32:
        case UTYPE_FAST64:
        case UTYPE_UFAST64:
        case UTYPE_LEAST8:
        case UTYPE_ULEAST8:
        case UTYPE_LEAST16:
        case UTYPE_ULEAST16:
        case UTYPE_LEAST32:
        case UTYPE_ULEAST32:
        case UTYPE_LEAST64:
        case UTYPE_ULEAST64:
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