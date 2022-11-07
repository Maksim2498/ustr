#include "cstr.h"

#include <assert.h>

#define USTR_RETURN_LEN_(cstr) \
    {                          \
        assert(cstr);          \
                               \
        size_t len = 0;        \
                               \
        while (cstr[len])      \
            ++len;             \
                               \
        return len;            \
    }

size_t uz32_len(const uc32_t *cstr) {
    USTR_RETURN_LEN_(cstr);
}

size_t uz16_len(const uc16_t *cstr) {
    USTR_RETURN_LEN_(cstr);
}

size_t uz8_len(const uc8_t *cstr) {
    USTR_RETURN_LEN_(cstr);
}

#define USTR_RETURN_CMP_(T, lhs, rhs) \
    assert(lhs && rhs);               \
                                      \
    while (1) {                       \
        T lhs_val = *lhs;             \
        T rhs_val = *rhs;             \
                                      \
        if (!lhs_val && !rhs_val)     \
            return 0;                 \
                                      \
        if (lhs_val < rhs_val)        \
            return -1;                \
                                      \
        if (lhs_val > rhs_val)        \
            return 1;                 \
    }                                 \

#define USTR_RETURN_CMP_N_(T, lhs, rhs) \
    assert(lhs && rhs);                 \
                                        \
    for (size_t i = 0; i < n; ++i) {    \
        T lhs_val = *lhs;               \
        T rhs_val = *rhs;               \
                                        \
        if (lhs_val > rhs_val)          \
            return 1;                   \
                                        \
        if (lhs_val < rhs_val)          \
            return -1;                  \
    }                                   \
                                        \
    return 0;

int uz32_cmp(const uc32_t *lhs, const uc32_t *rhs) {
    USTR_RETURN_CMP_(uc32_t, lhs, rhs);
}

int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc32_t, lhs, rhs);
}

int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs) {
    USTR_RETURN_CMP_(uc16_t, lhs, rhs);
}

int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc16_t, lhs, rhs);
}

int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs) {
    USTR_RETURN_CMP_(uc8_t, lhs, rhs);
}

int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc8_t, lhs, rhs);
}