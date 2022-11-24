#include "cstr.h"

#include <assert.h>
#include <stdbool.h>

#include "char.h"
#include "mem.h"
#include "view.h"

size_t uz8_trail(const uc8_t *cstr) {
    assert(cstr);

    size_t count = 0;

    while (uc8_trail(*cstr++))
        ++count;

    return count;
}

size_t uz8_n_trail(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t count = 0;

    while (n-- && uc8_trail(*cstr++))
        ++count;

    return count;
}

int uz16_dec(const uc16_t *cstr) {
    assert(cstr);
    return uc16_srgt_high(cstr[-1]) ? 2 : 1;
}

int uz8_dec(const uc8_t *cstr) {
    assert(cstr);

    int res = 1;

    while (uc8_lead(*--cstr))
        ++res;

    return res;
}

#define USTR_RETURN_UZ32_LEN_(N, cstr) \
    {                              \
        assert(cstr);              \
                                   \
        size_t len = 0;            \
                                   \
        for (size_t i = 0;;) {     \
            uc##N##_t c = cstr[i]; \
                                   \
            if (!c)                \
                return len;        \
                                   \
            i += uc##N##_len(c);   \
            ++len;                 \
        }                          \
                                   \
        return len;                \
    }

#define USTR_RETURN_N_UZ32_LEN_(N, cstr, n) \
    {                                   \
        assert(cstr);                   \
                                        \
        size_t len = 0;                 \
                                        \
        for (size_t i = 0; i < n;) {    \
            uc##N##_t c = cstr[i];      \
                                        \
            if (!c)                     \
                return len;             \
                                        \
            i += uc##N##_len(c);        \
            ++len;                      \
        }                               \
                                        \
        return len;                     \
    }

size_t uz16_uz8_len(const uc16_t *cstr) {
    assert(cstr);

    size_t len = 0;

    for (; *cstr; cstr += uc16_len(*cstr)) 
        len += uc16_uc8_len(*cstr);

    return len;
}

size_t uz16_n_uz8_len(const uc16_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (; n--; cstr += uc16_len(*cstr)) 
        len += uc16_uc8_len(*cstr);

    return len;
}

size_t uz16_uz32_len(const uc16_t *cstr) {
    USTR_RETURN_UZ32_LEN_(16, cstr);
}

size_t uz16_n_uz32_len(const uc16_t *cstr, size_t n) {
    USTR_RETURN_N_UZ32_LEN_(16, cstr, n);
}

size_t uz8_uz16_len(const uc8_t *cstr) {
    assert(cstr);

    size_t len = 0;

    for (; *cstr; cstr += uc8_len(*cstr))
        len += uc8_uc16_len(*cstr);

    return len;
}

size_t uz8_n_uz16_len(const uc8_t *cstr, size_t n) {
    assert(cstr);

    size_t len = 0;

    for (; n--; cstr += uc8_len(*cstr))
        len += uc8_uc16_len(*cstr);

    return len;
}

size_t uz8_uz32_len(const uc8_t *cstr) {
    USTR_RETURN_UZ32_LEN_(8, cstr);
}

size_t uz8_n_uz32_len(const uc8_t *cstr, size_t n) {
    USTR_RETURN_N_UZ32_LEN_(8, cstr, n);
}

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
    for (size_t i = 0;; ++i) {        \
        T lhs_val = lhs[i];           \
        T rhs_val = rhs[i];           \
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

#define USTR_RETURN_N_CMP_(T, lhs, n, rhs) \
    assert(lhs && rhs);                    \
                                           \
    for (size_t i = 0;; ++i) {             \
        bool lhs_end = i >= n;             \
        T    rhs_val = rhs[i];             \
        bool rhs_end = !rhs_val;           \
                                           \
        if (lhs_end && rhs_end)            \
            return 0;                      \
                                           \
        if (lhs_end)                       \
            return -1;                     \
                                           \
        if (rhs_end)                       \
            return 1;                      \
                                           \
        T lhs_val = lhs[i];                \
                                           \
        if (lhs_val > rhs_val)             \
            return 1;                      \
                                           \
        if (lhs_val < rhs_val)             \
            return -1;                     \
    }

#define USTR_RETURN_CMP_N_(T, lhs, rhs, n) \
    assert(lhs && rhs);                    \
                                           \
    for (size_t i = 0; i < n; ++i) {       \
        T lhs_val = lhs[i];                \
        T rhs_val = rhs[i];                \
                                           \
        if (lhs_val > rhs_val)             \
            return 1;                      \
                                           \
        if (lhs_val < rhs_val)             \
            return -1;                     \
    }                                      \
                                           \
    return 0;

#define USTR_RETURN_N_CMP_N_(T, lhs, lhs_len, rhs, rhs_len)      \
    {                                                            \
        assert(lhs && rhs);                                      \
                                                                 \
        size_t min_len = lhs_len >= rhs_len ? lhs_len : rhs_len; \
                                                                 \
        for (size_t i = 0; i < min_len; ++i) {                   \
            T lhs_val = lhs[i];                                  \
            T rhs_val = rhs[i];                                  \
                                                                 \
            if (lhs_val > rhs_val)                               \
                return 1;                                        \
                                                                 \
            if (lhs_val < rhs_val)                               \
                return -1;                                       \
        }                                                        \
                                                                 \
        if (lhs_len > rhs_len)                                   \
            return 1;                                            \
                                                                 \
        if (lhs_len < rhs_len)                                   \
            return -1;                                           \
                                                                 \
        return 0;                                                \
    }

int uz32_cmp(const uc32_t *lhs, const uc32_t *rhs) {
    USTR_RETURN_CMP_(uc32_t, lhs, rhs);
}

int uz32_n_cmp(const uc32_t *lhs, size_t n, const uc32_t *rhs) {
    USTR_RETURN_N_CMP_(uc32_t, lhs, n, rhs);
}

int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc32_t, lhs, rhs, n);
}

int uz32_n_cmp_n(const uc32_t *lhs, size_t lhs_len, const uc32_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc32_t, lhs, lhs_len, rhs, rhs_len);
}

int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs) {
    USTR_RETURN_CMP_(uc16_t, lhs, rhs);
}

int uz16_n_cmp(const uc16_t *lhs, size_t n, const uc16_t *rhs) {
    USTR_RETURN_N_CMP_(uc16_t, lhs, n, rhs);
}

int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc16_t, lhs, rhs, n);
}

int uz16_n_cmp_n(const uc16_t *lhs, size_t lhs_len, const uc16_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc16_t, lhs, lhs_len, rhs, rhs_len);
}

int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs) {
    USTR_RETURN_CMP_(uc8_t, lhs, rhs);
}

int uz8_n_cmp(const uc8_t *lhs, size_t n, const uc8_t *rhs) {
    USTR_RETURN_N_CMP_(uc8_t, lhs, n, rhs);
}

int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n) {
    USTR_RETURN_CMP_N_(uc8_t, lhs, rhs, n);
}

int uz8_n_cmp_n(const uc8_t *lhs, size_t lhs_len, const uc8_t *rhs, size_t rhs_len) {
    USTR_RETURN_N_CMP_N_(uc8_t, lhs, lhs_len, rhs, rhs_len);
}

#define USTR_RETURN_POS_(cstr, another)    \
    assert(cstr && another);               \
                                           \
    for (size_t i = 0; cstr[i]; ++i) {     \
        bool found = false;                \
                                           \
        for (size_t j = 0; ; ++j) {        \
            if (!another[j]) {             \
                found = true;              \
                break;                     \
            }                              \
                                           \
            if (another[j] != cstr[i + j]) \
                break;                     \
        }                                  \
                                           \
        if (found)                         \
            return i;                      \
    }                                      \
                                           \
    return -1;

#define USTR_RETURN_N_POS_(cstr, n, another) \
    assert(cstr && another);                 \
                                             \
    for (size_t i = 0; i < n; ++i) {         \
        bool found = false;                  \
                                             \
        for (size_t j = 0; i + j < n; ++j) { \
            if (!another[j]) {               \
                found = true;                \
                break;                       \
            }                                \
                                             \
            if (another[j] != cstr[i + j])   \
                break;                       \
        }                                    \
                                             \
        if (found)                           \
            return i;                        \
    }                                        \
                                             \
    return -1;

#define USTR_RETURN_POS_N_(cstr, another, n)   \
    assert(cstr && another);                   \
                                               \
    for (size_t i = 0; cstr[i]; ++i) {         \
        bool found = false;                    \
                                               \
        for (size_t j = 0; cstr[i + j]; ++j) { \
            if (j == n) {                      \
                found = true;                  \
                break;                         \
            }                                  \
                                               \
            if (another[j] != cstr[i + j])     \
                break;                         \
        }                                      \
                                               \
        if (found)                             \
            return i;                          \
    }                                          \
                                               \
    return -1;

#define USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len) \
    assert(cstr && another);                                       \
                                                                   \
    for (size_t i = 0; i < cstr_len; ++i) {                        \
        if (cstr_len - i < another_len)                            \
            break;                                                 \
                                                                   \
        bool found = false;                                        \
                                                                   \
        for (size_t j = 0; i + j < cstr_len; ++j) {                \
            if (j == another_len) {                                \
                found = true;                                      \
                break;                                             \
            }                                                      \
                                                                   \
            if (another[j] != cstr[i + j])                         \
                break;                                             \
        }                                                          \
                                                                   \
        if (found)                                                 \
            return i;                                              \
    }                                                              \
                                                                   \
    return -1;

#define USTR_RETURN_C_POS_(cstr, c)  \
    assert(cstr);                    \
                                     \
    for (size_t i = 0; cstr[i]; ++i) \
        if (cstr[i] == c)            \
            return i;                \
                                     \
    return -1;

#define USTR_RETURN_N_C_POS_(cstr, n, c) \
    assert(cstr);                        \
                                         \
    for (size_t i = 0; i < n; ++i)       \
        if (cstr[i] == c)                \
            return i;                    \
                                         \
    return -1;

ptrdiff_t uz32_pos(const uc32_t *cstr, const uc32_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz32_n_pos(const uc32_t *cstr, size_t n, const uc32_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz32_pos_n(const uc32_t *cstr, const uc32_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz32_n_pos_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz32_uc32_pos(const uc32_t *cstr, uc32_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz32_n_uc32_pos(const uc32_t *cstr, size_t n, uc32_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

ptrdiff_t uz16_pos(const uc16_t *cstr, const uc16_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz16_n_pos(const uc16_t *cstr, size_t n, const uc16_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz16_pos_n(const uc16_t *cstr, const uc16_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz16_n_pos_n(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz16_uc32_pos(const uc16_t *cstr, uc16_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz16_n_uc32_pos(const uc16_t *cstr, size_t n, uc16_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

ptrdiff_t uz8_pos(const uc8_t *cstr, const uc8_t *another) {
    USTR_RETURN_POS_(cstr, another);
}

ptrdiff_t uz8_n_pos(const uc8_t *cstr, size_t n, const uc8_t *another) {
    USTR_RETURN_N_POS_(cstr, n, another);
}

ptrdiff_t uz8_pos_n(const uc8_t *cstr, const uc8_t *another, size_t n) {
    USTR_RETURN_POS_N_(cstr, another, n);
}

ptrdiff_t uz8_n_pos_n(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    USTR_RETURN_N_POS_N_(cstr, cstr_len, another, another_len);
}

ptrdiff_t uz8_uc8_pos(const uc8_t *cstr, uc8_t c) {
    USTR_RETURN_C_POS_(cstr, c);
}

ptrdiff_t uz8_n_uc8_pos(const uc8_t *cstr, size_t n, uc8_t c) {
    USTR_RETURN_N_C_POS_(cstr, n, c);
}

#define USTR_RETURN_POS_R_(cstr, another, from) \
    assert(cstr && another);                    \
                                                \
    for (ptrdiff_t i = from; i >= 0; --i) {     \
        bool found = false;                     \
                                                \
        for (size_t j = 0; cstr[i + j]; ++j) {  \
            if (!another[j]) {                  \
                found = true;                   \
                break;                          \
            }                                   \
                                                \
            if (cstr[i + j] != another[j])      \
                break;                          \
        }                                       \
                                                \
        if (found)                              \
            return i;                           \
    }                                           \
                                                \
    return -1;

#define USTR_RETURN_POS_N_R_(cstr, another, n, from) \
    assert(cstr && another);                         \
                                                     \
    for (ptrdiff_t i = from; i >= 0; --i) {          \
        bool found = false;                          \
                                                     \
        for (size_t j = 0; cstr[i + j]; ++j) {       \
            if (j >= n) {                            \
                found = true;                        \
                break;                               \
            }                                        \
                                                     \
            if (cstr[i + j] != another[j])           \
                break;                               \
        }                                            \
                                                     \
       if (found)                                    \
            return i;                                \
    }                                                \
                                                     \
    return -1;

#define USTR_RETURN_N_POS_R_(cstr, n, another, from) \
    assert(cstr && another);                         \
                                                     \
    if (from >= n)                                   \
        return -1;                                   \
                                                     \
    for (ptrdiff_t i = from; i >= 0; --i) {          \
        bool found = false;                          \
                                                     \
        for (size_t j = 0; i + j < n; ++j) {         \
            if (!another[j]) {                       \
                found = true;                        \
                break;                               \
            }                                        \
                                                     \
            if (cstr[j + i] != another[j])           \
                break;                               \
        }                                            \
                                                     \
        if (found)                                   \
            return i;                                \
    }                                                \
                                                     \
    return -1;

#define USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from) \
    assert(cstr && another);                                               \
                                                                           \
    if (cstr_len < another_len || from >= cstr_len)                        \
        return -1;                                                         \
                                                                           \
    for (ptrdiff_t i = from; i >= 0; --i) {                                \
        if (cstr_len - i < another_len)                                    \
            continue;                                                      \
                                                                           \
        bool found = false;                                                \
                                                                           \
        for (size_t j = 0; i + j < cstr_len; ++j) {                        \
            if (j >= another_len) {                                        \
                found = true;                                              \
                break;                                                     \
            }                                                              \
                                                                           \
            if (cstr[i + j] != another[j])                                 \
                break;                                                     \
        }                                                                  \
                                                                           \
        if (found)                                                         \
            return i;                                                      \
    }                                                                      \
                                                                           \
    return -1;

#define USTR_RETURN_N_C_POS_R_(cstr, n, c, from) \
    assert(cstr);                                \
                                                 \
    if (from >= n)                               \
        return -1;                               \
                                                 \
    for (ptrdiff_t i = from; i >= 0; --i)        \
        if (cstr[i] == c)                        \
            return i;                            \
                                                 \
    return -1;

ptrdiff_t uz32_pos_r(const uc32_t *cstr, const uc32_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz32_pos_n_r(const uc32_t *cstr, const uc32_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz32_n_pos_r(const uc32_t *cstr, size_t n, const uc32_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz32_n_pos_n_r(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz32_uc32_pos_r(const uc32_t *cstr, uc32_t c, size_t from) {
    return uz32_n_uc32_pos_r(cstr, from + 1, c, from);
}

ptrdiff_t uz32_n_uc32_pos_r(const uc32_t *cstr, size_t n, uc32_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

ptrdiff_t uz16_pos_r(const uc16_t *cstr, const uc16_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz16_pos_n_r(const uc16_t *cstr, const uc16_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz16_n_pos_r(const uc16_t *cstr, size_t n, const uc16_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz16_n_pos_n_r(const uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz16_uc16_pos_r(const uc16_t *cstr, uc16_t c, size_t from) {
    return uz16_n_uc16_pos_r(cstr, from + 1, c, from);
}

ptrdiff_t uz16_n_uc16_pos_r(const uc16_t *cstr, size_t n, uc16_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

ptrdiff_t uz8_pos_r(const uc8_t *cstr, const uc8_t *another, size_t from) {
    USTR_RETURN_POS_R_(cstr, another, from);
}

ptrdiff_t uz8_pos_n_r(const uc8_t *cstr, const uc8_t *another, size_t n, size_t from) {
    USTR_RETURN_POS_N_R_(cstr, another, n, from);
}

ptrdiff_t uz8_n_pos_r(const uc8_t *cstr, size_t n, const uc8_t *another, size_t from) {
    USTR_RETURN_N_POS_R_(cstr, n, another, from);
}

ptrdiff_t uz8_n_pos_n_r(const uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len, size_t from) {
    USTR_RETURN_N_POS_N_R_(cstr, cstr_len, another, another_len, from);
}

ptrdiff_t uz8_uc8_pos_r(const uc8_t *cstr, uc8_t c, size_t from) {
    return uz8_n_uc8_pos_r(cstr, from + 1, c, from);
}

ptrdiff_t uz8_n_uc8_pos_r(const uc8_t *cstr, size_t n, uc8_t c, size_t from) {
    USTR_RETURN_N_C_POS_R_(cstr, n, c, from);
}

#define USTR_FILL_(cstr, c) \
    assert(cstr);           \
                            \
    while (*cstr)           \
        *cstr++ = c;        

#define USTR_N_FILL_(cstr, n, c)   \
    assert(cstr);                  \
                                   \
    for (size_t i = 0; i < n; ++i) \
        cstr[i] = c;

#define USTR_FILL_Z_(cstr, another)                         \
    assert(cstr && another);                                \
                                                            \
    for (size_t i = 0; cstr[i];)                            \
        for (size_t j = 0; cstr[i] && another[j]; ++j, ++i) \
            cstr[i] = another[j];

#define USTR_N_FILL_Z_(cstr, n, another)                        \
    assert(cstr && another);                                    \
                                                                \
    for (size_t i = 0; i < n;)                                  \
        for (size_t j = 0; i < cstr[i] && another[j]; ++j, ++i) \
            cstr[i] = another[j];

#define USTR_FILL_Z_N_(cstr, another, n)               \
    assert(cstr && another);                           \
                                                       \
    for (size_t i = 0; cstr[i];)                       \
        for (size_t j = 0; cstr[i] && j < n; ++j, ++i) \
            cstr[i] = another[j];

#define USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len)        \
    assert(cstr && another);                                          \
                                                                      \
    for (size_t i = 0; i < cstr_len;)                                 \
        for (size_t j = 0; i < cstr_len && j < another_len; ++j, ++i) \
            cstr[i] = another[j];

void uz32_fill(uc32_t *cstr, uc32_t c) {
    USTR_FILL_(cstr, c);
}

void uz32_n_fill(uc32_t *cstr, size_t n, uc32_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz32_fill_uz32(uc32_t *cstr, const uc32_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz32_n_fill_uz32(uc32_t *cstr, size_t n, const uc32_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz32_fill_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz32_n_fill_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

void uz16_fill(uc16_t *cstr, uc16_t c) {
    USTR_FILL_(cstr, c);
}

void uz16_n_fill(uc16_t *cstr, size_t n, uc16_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz16_fill_uz16(uc16_t *cstr, const uc16_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz16_n_fill_uz16(uc16_t *cstr, size_t n, const uc16_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz16_fill_uz16_n(uc16_t *cstr, const uc16_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz16_n_fill_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

void uz8_fill(uc8_t *cstr, uc8_t c) {
    USTR_FILL_(cstr, c);
}

void uz8_n_fill(uc8_t *cstr, size_t n, uc8_t c) {
    USTR_N_FILL_(cstr, n, c);
}

void uz8_fill_uz8(uc8_t *cstr, const uc8_t *another) {
    USTR_FILL_Z_(cstr, another);
}

void uz8_n_fill_uz8(uc8_t *cstr, size_t n, const uc8_t *another) {
    USTR_N_FILL_Z_(cstr, n, another);
}

void uz8_fill_uz8_n(uc8_t *cstr, const uc8_t *another, size_t n) {
    USTR_FILL_Z_N_(cstr, another, n);
}

void uz8_n_fill_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *another, size_t another_len) {
    USTR_N_FILL_Z_N_(cstr, cstr_len, another, another_len);
}

#define USTR_RETURN_TO_CASE_LEN_(N, case, cstr)   \
    {                                             \
        assert(cstr);                             \
                                                  \
        size_t len = 0;                           \
                                                  \
        for (; *cstr; cstr += uc##N##_len(*cstr)) \
            len += uc##N##_to_##case##_len(cstr); \
                                                  \
        return len;                               \
    }

#define USTR_RETURN_TO_CASE_LEN_N_(N, case, cstr, n)         \
    {                                                        \
        assert(cstr);                                        \
                                                             \
        size_t len = 0;                                      \
                                                             \
        for (size_t i = 0; i < n; i += uc##N##_len(cstr[i])) \
            len += uc##N##_to_##case##_len(cstr + i);        \
                                                             \
        return len;                                          \
    }

size_t uz16_to_upper_len(const uc16_t *cstr) {
    USTR_RETURN_TO_CASE_LEN_(16, upper, cstr);
}

size_t uz16_n_to_upper_len(const uc16_t *cstr, size_t n) {
    USTR_RETURN_TO_CASE_LEN_N_(16, upper, cstr, n);
}

size_t uz16_to_lower_len(const uc16_t *cstr) {
    USTR_RETURN_TO_CASE_LEN_(16, lower, cstr);
}

size_t uz16_n_to_lower_len(const uc16_t *cstr, size_t n) {
    USTR_RETURN_TO_CASE_LEN_N_(16, lower, cstr, n);
}

size_t uz8_to_upper_len(const uc8_t *cstr) {
    USTR_RETURN_TO_CASE_LEN_(8, upper, cstr);
}

size_t uz8_n_to_upper_len(const uc8_t *cstr, size_t n) {
    USTR_RETURN_TO_CASE_LEN_N_(8, upper, cstr, n);
}

size_t uz8_to_lower_len(const uc8_t *cstr) {
    USTR_RETURN_TO_CASE_LEN_(8, lower, cstr);
}

size_t uz8_n_to_lower_len(const uc8_t *cstr, size_t n) {
    USTR_RETURN_TO_CASE_LEN_N_(8, lower, cstr, n);
}

#define USTR_UZ32_TO_CASE_(case, cstr) \
    assert(cstr);                      \
                                       \
    for (; *cstr; ++cstr)              \
        *cstr = uc32_to_##case(*cstr);

#define USTR_UZ32_TO_CASE_N_(case, cstr, n) \
    assert(cstr);                           \
                                            \
    for (size_t i = 0; i < n; ++i)          \
        cstr[i] = uc32_to_##case(cstr[i]);

void uz32_to_upper(uc32_t *cstr) {
    USTR_UZ32_TO_CASE_(upper, cstr);
}

void uz32_n_to_upper(uc32_t *cstr, size_t n) {
    USTR_UZ32_TO_CASE_N_(upper, cstr, n);
}

void uz32_to_lower(uc32_t *cstr) {
    USTR_UZ32_TO_CASE_(lower, cstr);
}

void uz32_n_to_lower(uc32_t *cstr, size_t n) {
    USTR_UZ32_TO_CASE_N_(lower, cstr, n);
}

#define USTR_Z_TO_CASE_(N, case, from, to)                 \
    assert(from && to);                                    \
                                                           \
    for (size_t i = 0, j = 0; from[i];) {                  \
        int len = uc##N##_len(from[i]);                    \
                                                           \
        uz##N##_copy_n(to + j, from + i, len);             \
                                                           \
        int to_len = uc##N##_to_##case(to + j);            \
                                                           \
        i += len;                                          \
        j += to_len;                                       \
    }

#define USTR_Z_TO_CASE_N_(N, case, from, n, to)            \
    assert(from && to);                                    \
                                                           \
    for (size_t i = 0, j = 0; i < n;) {                    \
        int len = uc##N##_len(from[i]);                    \
                                                           \
        uz##N##_copy_n(to + j, from + i, len);             \
                                                           \
        int to_len = uc##N##_to_##case(to + j);            \
                                                           \
        i += len;                                          \
        j += to_len;                                       \
    }

void uz16_to_upper(const uc16_t *from, uc16_t *to) {
    USTR_Z_TO_CASE_(16, upper, from, to);
}

void uz16_n_to_upper(const uc16_t *from, size_t n, uc16_t *to) {
    USTR_Z_TO_CASE_N_(16, upper, from, n, to);
}

void uz16_to_lower(const uc16_t *from, uc16_t *to) {
    USTR_Z_TO_CASE_(16, lower, from, to);
}

void uz16_n_to_lower(const uc16_t *from, size_t n, uc16_t *to) {
    USTR_Z_TO_CASE_N_(16, lower, from, n, to);
}

void uz8_to_upper(const uc8_t *from, uc8_t *to) {
    USTR_Z_TO_CASE_(8, upper, from, to);
}

void uz8_n_to_upper(const uc8_t *from, size_t n, uc8_t *to) {
    USTR_Z_TO_CASE_N_(8, upper, from, n, to);
}

void uz8_to_lower(const uc8_t *from, uc8_t *to) {
    USTR_Z_TO_CASE_(8, lower, from, to);
}

void uz8_n_to_lower(const uc8_t *from, size_t n, uc8_t *to) {
    USTR_Z_TO_CASE_N_(8, lower, from, n, to);
}

#define USTR_RETURN_Z_N_TRIM_LEFT_(N, src, n) \
    {                                         \
        assert(cstr);                         \
                                              \
        size_t wspace_len = 0;                \
                                              \
        for (size_t i = 0; i < n;) {          \
            int len = uc##N##_len(cstr[i]);   \
                                              \
            if (uc##N##_wspace(cstr + i))     \
                wspace_len += len;            \
            else                              \
                break;                        \
                                              \
            i += len;                         \
        }                                     \
                                              \
        size_t new_len = n - wspace_len;      \
                                              \
        for (size_t i = 0; i < new_len; ++i)  \
            cstr[i] = cstr[i + wspace_len];   \
                                              \
        return new_len;                       \
    }

#define USTR_RETURN_Z_N_TRIM_RIGHT_(N, src, n) \
    {                                          \
        assert(cstr);                          \
                                               \
        size_t wspace_len = 0;                 \
                                               \
        for (ptrdiff_t i = n - 1; i >= 0;) {   \
            int len = uc##N##_len(cstr[i]);    \
                                               \
            if (uc##N##_wspace(cstr + i))      \
                ++wspace_len;                  \
            else                               \
                break;                         \
                                               \
            i -= len;                          \
        }                                      \
                                               \
        return n - wspace_len;                 \
    }

size_t uz32_trim(uc32_t *cstr) {
    return uz32_n_trim(cstr, uz32_len(cstr));
}

size_t uz32_n_trim(uc32_t *cstr, size_t n) {
    return uz32_n_trim_right(cstr, uz32_n_trim_left(cstr, n));
}

size_t uz32_trim_left(uc32_t *cstr) {
    return uz32_n_trim_left(cstr, uz32_len(cstr));
}

size_t uz32_n_trim_left(uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t wspace_len = 0;

    for (size_t i = 0; i < n; ++i)
        if (uc32_wspace(cstr[i]))
            ++wspace_len;
        else
            break;

    size_t new_len = n - wspace_len;

    for (size_t i = 0; i < new_len; ++i)
        cstr[i] = cstr[i + wspace_len];

    return new_len;
}

size_t uz32_trim_right(const uc32_t *cstr) {
    return uz32_n_trim_right(cstr, uz32_len(cstr));
}

size_t uz32_n_trim_right(const uc32_t *cstr, size_t n) {
    assert(cstr);

    size_t wspace_len = 0;

    for (ptrdiff_t i = n - 1; i >= 0; --i)
        if (uc32_wspace(cstr[i]))
            ++wspace_len;
        else
            break;

    return n - wspace_len;
}

size_t uz16_trim(uc16_t *cstr) {
	return uz16_n_trim_right(cstr, uz16_trim_left(cstr));
}

size_t uz16_n_trim(uc16_t *cstr, size_t n) {
    return uz16_n_trim_right(cstr, uz16_n_trim_left(cstr, n));
}

size_t uz16_trim_left(uc16_t *cstr) {
	return uz16_n_trim_left(cstr, uz16_len(cstr));
}

size_t uz16_n_trim_left(uc16_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_LEFT_(16, cstr, n);
}

size_t uz16_trim_right(const uc16_t *cstr) {
	return uz16_n_trim_right(cstr, uz16_len(cstr));
}

size_t uz16_n_trim_right(const uc16_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_RIGHT_(16, cstr, n);
}

size_t uz8_trim(uc8_t *cstr) {
	return uz8_n_trim_right(cstr, uz8_trim_left(cstr));
}

size_t uz8_n_trim(uc8_t *cstr, size_t n) {
    return uz8_n_trim_right(cstr, uz8_n_trim_left(cstr, n));
}

size_t uz8_trim_left(uc8_t *cstr) {
	return uz8_n_trim_left(cstr, uz8_len(cstr));
}

size_t uz8_n_trim_left(uc8_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_LEFT_(8, cstr, n);
}

size_t uz8_trim_right(const uc8_t *cstr) {
	return uz8_n_trim_right(cstr, uz8_len(cstr));
}

size_t uz8_n_trim_right(const uc8_t *cstr, size_t n) {
    USTR_RETURN_Z_N_TRIM_RIGHT_(8, cstr, n);
}

#define USTR_COPY_(dst, src) \
    assert(dst && src);      \
                             \
    while (*src)             \
        *dst++ = *src++;

#define USTR_COPY_N_(dst, src, n) \
    assert(dst && src);           \
                                  \
    while (n--)                   \
        *dst++ = *src++;

#define USTR_N_COPY_N_(dst, dst_len, src, src_len) \
    assert(dst && src);                            \
                                                   \
    while (dst_len-- && src_len--)                 \
        *dst++ = *src++;

void uz32_copy(uc32_t *dst, const uc32_t *src) {
    USTR_COPY_(dst, src);
}

void uz32_copy_n(uc32_t *dst, const uc32_t *src, size_t n) {
    USTR_COPY_N_(dst, src, n);
}

void uz32_n_copy_n(uc32_t *dst, size_t dst_len, const uc32_t *src, size_t src_len) {
    USTR_N_COPY_N_(dst, dst_len, src, src_len);
}

void uz16_copy(uc16_t *dst, const uc16_t *src) {
    USTR_COPY_(dst, src);
}

void uz16_copy_n(uc16_t *dst, const uc16_t *src, size_t n) {
    USTR_COPY_N_(dst, src, n);
}

void uz16_n_copy_n(uc16_t *dst, size_t dst_len, const uc16_t *src, size_t src_len) {
    USTR_N_COPY_N_(dst, dst_len, src, src_len);
}

void uz8_copy(uc8_t *dst, const uc8_t *src) {
    USTR_COPY_(dst, src);
}

void uz8_copy_n(uc8_t *dst, const uc8_t *src, size_t n) {
    USTR_COPY_N_(dst, src, n);
}

void uz8_n_copy_n(uc8_t *dst, size_t dst_len, const uc8_t *src, size_t src_len) {
    USTR_N_COPY_N_(dst, dst_len, src, src_len);
}

#define USTR_MOVE_(dst, src, n)              \
    assert(dst && src);                        \
                                               \
    if (dst < src)                             \
        while (n--)                            \
            *dst++ = *src++;                   \
    else                                       \
        for (ptrdiff_t i = n - 1; i >= 0; --i) \
            dst[i] = src[i];

void uz32_move(uc32_t *dst, const uc32_t *src, size_t n) {
    USTR_MOVE_(dst, src, n);
}

void uz16_move(uc16_t *dst, const uc16_t *src, size_t n) {
    USTR_MOVE_(dst, src, n);
}

void uz8_move(uc8_t *dst, const uc8_t *src, size_t n) {
    USTR_MOVE_(dst, src, n);
}

void uz32_reverse(uc32_t *cstr) {
    uz32_n_reverse(cstr, uz32_len(cstr));
}

void uz32_n_reverse(uc32_t *cstr, size_t n) {
    assert(cstr);

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc32_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }
}

void uz16_reverse(uc16_t *cstr) {
    uz16_n_reverse(cstr, uz16_len(cstr));
}

void uz16_n_reverse(uc16_t *cstr, size_t n) {
    assert(cstr);

    // Reverse words

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc16_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp; 
    }

    // Fix surrogates

    for (size_t i = 0; i < n;) {
        uc16_t c = cstr[i];

        if (uc16_srgt_high(c)) {
            size_t j = i + 1;

            cstr[i] = cstr[j];
            cstr[j] = c;

            i += 2;
        } else
            ++i;
    }
}

void uz8_reverse(uc8_t *cstr) {
    uz8_n_reverse(cstr, uz8_len(cstr));
}

void uz8_n_reverse(uc8_t *cstr, size_t n) {
    assert(cstr);

    // Reverse bytes

    for (size_t i = 0, j = n - 1; i < n / 2; ++i, --j) {
        uc8_t tmp = cstr[j];

        cstr[j] = cstr[i];
        cstr[i] = tmp;
    }

    // Fix sequences

    for (size_t i = 0; i < n;) {
        size_t trail = uz8_n_trail(cstr + i, n - i);

        // ASCI

        if (!trail) {
            ++i;
            continue;
        }

        // Reverse sequence

        size_t len = trail + i + 1 > n ? trail : trail + 1;
        size_t end = i + len;
        size_t mid = i + len / 2;

        for (size_t j = i, k = end - 1; j < mid; ++j, --k) {
            uc8_t tmp = cstr[k];

            cstr[k] = cstr[j];
            cstr[j] = tmp;
        }

        i += len;
    }
}

size_t uz32_new_csplit(const uc32_t *cstr, uc32_t c, ucv32_t **array) {
	return uz32_new_split((uc32_t *) cstr, c, (uv32_t **) array);
}

size_t uz32_new_csplit_e(const uc32_t *cstr, uc32_t c, ucv32_t **array, bool *error) {
	return uz32_new_split_e((uc32_t *) cstr, c, (uv32_t **) array, error);
}

size_t uz32_n_new_csplit(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array) {
	return uz32_n_new_split((uc32_t *) cstr, n, c, (uv32_t **) array);
}

size_t uz32_n_new_csplit_e(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t **array, bool *error) {
	return uz32_n_new_split_e((uc32_t *) cstr, n, c, (uv32_t **) array, error);
}

size_t uz32_csplit(const uc32_t *cstr, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32_split((uc32_t *) cstr, c, (uv32_t *) array, array_len);
}

size_t uz32_n_csplit(const uc32_t *cstr, size_t n, uc32_t c, ucv32_t *array, size_t array_len) {
	return uz32_n_split((uc32_t *) cstr, n, c, (uv32_t *) array, array_len);
}

size_t uz32_new_split(uc32_t *cstr, uc32_t c, uv32_t **array) {
	return uz32_new_split_e(cstr, c, array, NULL);
}

size_t uz32_new_split_e(uc32_t *cstr, uc32_t c, uv32_t **array, bool *error) {
	return uz32_n_new_split_e(cstr, uz32_len(cstr), c, array, error);
}

size_t uz32_n_new_split(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array) {
	return uz32_n_new_split_e(cstr, n, c, array, NULL);
}

size_t uz32_n_new_split_e(uc32_t *cstr, size_t n, uc32_t c, uv32_t **array, bool *error) {
    size_t array_len = uz32_n_split(cstr, n, c, NULL, 0);

    if (!array)
        return array_len;

    uv32_t *new_array = ualloc(sizeof(uv32_t) * array_len);

    if (!new_array) {
        if (error)
            *error = true;
    
        return array_len;
    }

    *array = new_array;

    return uz32_n_split(cstr, n, c, new_array, array_len);
}

size_t uz32_split(uc32_t *cstr, uc32_t c, uv32_t *array, size_t array_len) {
    return uz32_n_split(cstr, uz32_len(cstr), c, array, array_len);
}

size_t uz32_n_split(uc32_t *cstr, size_t n, uc32_t c, uv32_t *array, size_t array_len) {
    assert(cstr);

    size_t count = 0;

    for (ptrdiff_t prev_pos = 0; prev_pos >= 0; ++count) {
        uc32_t   *begin   = cstr + prev_pos;
        size_t    len     = n - prev_pos;
        ptrdiff_t rel_pos = uz32_n_uc32_pos(begin, len, c);
        ptrdiff_t pos     = rel_pos;

        if (array && count < array_len) {
            size_t view_len = pos < 0 ? len : rel_pos;
            array[count] = uv32_from_uz32_n(begin, view_len);
        }

        prev_pos = pos >= 0 ? pos + prev_pos + 1 : pos;
    }

	return count;
}

size_t uz32_new_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t **array) {
    return uz32_new_split_uz32((uc32_t *) cstr, another, (uv32_t **) array);
}

size_t uz32_new_csplit_uz32_e(const uc32_t *cstr, const uc32_t *another, ucv32_t **array, bool *error) {
    return uz32_new_split_uz32_e((uc32_t *) cstr, another, (uv32_t **) array, error);
}

size_t uz32_n_new_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array) {
    return uz32_n_new_split_uz32((uc32_t *) cstr, n, another, (uv32_t **) array);
}

size_t uz32_n_new_csplit_uz32_e(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_e((uc32_t *) cstr, n, another, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32(const uc32_t *cstr, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32_split_uz32((uc32_t *) cstr, another, (uv32_t *) array, array_len);
}

size_t uz32_n_csplit_uz32(const uc32_t *cstr, size_t n, const uc32_t *another, ucv32_t *array, size_t array_len) {
    return uz32_n_split_uz32((uc32_t *) cstr, n, another, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t **array) {
    return uz32_new_split_uz32_e(cstr, another, array, NULL);
}

size_t uz32_new_split_uz32_e(uc32_t *cstr, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_e(cstr, uz32_len(cstr), another, array, error);
}

size_t uz32_n_new_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array) {
    return uz32_n_new_split_uz32_e(cstr, n, another, array, NULL);
}

size_t uz32_n_new_split_uz32_e(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_n_e(cstr, n, another, uz32_len(another), array, error);
}

size_t uz32_split_uz32(uc32_t *cstr, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32_n_split_uz32(cstr, uz32_len(cstr), another, array, array_len);
}

size_t uz32_n_split_uz32(uc32_t *cstr, size_t n, const uc32_t *another, uv32_t *array, size_t array_len) {
    return uz32_n_split_uz32_n(cstr, n, another, uz32_len(another), array, array_len);
}

size_t uz32_new_csplit_uz32_n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array) {
    return uz32_new_split_uz32_n((uc32_t *) cstr, another, n, (uv32_t **) array);
}

size_t uz32_new_csplit_uz32_n_e(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t **array, bool *error) {
    return uz32_new_split_uz32_n_e((uc32_t *) cstr, another, n, (uv32_t **) array, error);
}

size_t uz32_n_new_csplit_uz32_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array) {
    return uz32_n_new_split_uz32_n((uc32_t *) cstr, cstr_len, another, another_len, (uv32_t **) array);
}

size_t uz32_n_new_csplit_uz32_n_e(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_n_e((uc32_t *) cstr, cstr_len, another, another_len, (uv32_t **) array, error);
}

size_t uz32_csplit_uz32_n(const uc32_t *cstr, const uc32_t *another, size_t n, ucv32_t *array, size_t array_len) {
    return uz32_split_uz32_n((uc32_t *) cstr, another, n, (uv32_t *) array, array_len);
}

size_t uz32_n_csplit_uz32_n(const uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, ucv32_t *array, size_t array_len) {
    return uz32_n_split_uz32_n((uc32_t *) cstr, cstr_len, another, array_len, (uv32_t *) array, array_len);
}

size_t uz32_new_split_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array) {
    return uz32_new_split_uz32_n_e(cstr, another, n, array, NULL);
}

size_t uz32_new_split_uz32_n_e(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t **array, bool *error) {
    return uz32_n_new_split_uz32_n_e(cstr, uz32_len(cstr), another, n, array, error);
}

size_t uz32_n_new_split_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array) {
    return uz32_n_new_split_uz32_n_e(cstr, cstr_len, another, another_len, array, NULL);
}

size_t uz32_n_new_split_uz32_n_e(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t **array, bool *error) {
    assert(cstr && another);

    size_t array_len = uz32_n_split_uz32_n(cstr, cstr_len, another, another_len, NULL, 0);

    if (!array)
        return array_len;

    uv32_t *new_array = ualloc(sizeof(uv32_t) * array_len);

    if (!new_array) {
        if (error)
            *error = true;
    
        return array_len;
    }

    *array = new_array;

    return uz32_n_split_uz32_n(cstr, cstr_len, another, another_len, new_array, array_len);
}

size_t uz32_split_uz32_n(uc32_t *cstr, const uc32_t *another, size_t n, uv32_t *array, size_t array_len) {
    return uz32_n_split_uz32_n(cstr, uz32_len(cstr), another, n, array, array_len);
}

size_t uz32_n_split_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *another, size_t another_len, uv32_t *array, size_t array_len) {
    assert(cstr && another);

    if (another_len > cstr_len)
        return 0;

    size_t count = 0;

    for (ptrdiff_t prev_pos = 0; prev_pos >= 0; ++count) {
        uc32_t   *begin   = cstr + prev_pos;
        size_t    len     = cstr_len - prev_pos;
        ptrdiff_t rel_pos = uz32_n_pos_n(begin, len, another, another_len);
        ptrdiff_t pos     = rel_pos;

        if (array && count < array_len) {
            size_t view_len = pos < 0 ? len : rel_pos;
            array[count] = uv32_from_uz32_n(begin, view_len);
        }

        prev_pos = pos >= 0 ? pos + prev_pos + another_len : pos;
    }

	return count;
}

#define USTR_RETURN_REPLACE_C_C_(cstr, from, to, count) \
    {                                                   \
        assert(cstr);                                   \
                                                        \
        size_t inner_count = 0;                         \
        size_t len         = 0;                         \
                                                        \
        for (; cstr[len]; ++len)                        \
            if (cstr[len] == from) {                    \
                cstr[len] = to;                         \
                ++inner_count;                          \
            }                                           \
                                                        \
        if (count)                                      \
            *count = inner_count;                       \
                                                        \
        return len;                                     \
    }

#define USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count) \
    {                                                               \
        assert(cstr);                                               \
                                                                    \
        size_t inner_count = 0;                                     \
                                                                    \
        for (size_t i = 0; i < cstr_len; ++i)                       \
            if (cstr[i] == from) {                                  \
                cstr[i] = to;                                       \
                ++inner_count;                                      \
            }                                                       \
                                                                    \
            if (count)                                              \
                *count = inner_count;                               \
                                                                    \
        return cstr_len;                                            \
    }

#define USTR_RETURN_N_REPLACE_Z_N_C_(N, cstr, cstr_len, from, from_len, to, count) \
    {                                                                              \
        assert(cstr && from);                                                      \
                                                                                   \
        if (!from_len || from_len > cstr_len) {                                    \
            if (count)                                                             \
                *count = 0;                                                        \
                                                                                   \
            return cstr_len;                                                       \
        }                                                                          \
                                                                                   \
        size_t inner_count  = 0;                                                   \
        size_t new_cstr_len = cstr_len;                                            \
        size_t len_delta    = from_len - 1;                                        \
                                                                                   \
        while (true) {                                                             \
            ptrdiff_t pos = uz##N##_n_pos_n(cstr, cstr_len, from, from_len);       \
                                                                                   \
            if (pos < 0)                                                           \
                break;                                                             \
                                                                                   \
            cstr[pos]     = to;                                                    \
            cstr_len     -= len_delta + pos;                                       \
            new_cstr_len -= len_delta;                                             \
            cstr         += pos + 1;                                               \
                                                                                   \
            uz##N##_move(cstr, cstr + len_delta, cstr_len);                        \
                                                                                   \
            ++inner_count;                                                         \
        }                                                                          \
                                                                                   \
        if (count)                                                                 \
            *count = inner_count;                                                  \
                                                                                   \
        return new_cstr_len;                                                       \
    }

#define USTR_RETURN_N_REPLACE_C_Z_N_(N, cstr, cstr_len, from, to, to_len, count) \
    {                                                                            \
        assert(cstr && to);                                                      \
                                                                                 \
        size_t inner_count = 0;                                                  \
                                                                                 \
        for (size_t i = 0; i < cstr_len; ++i)                                    \
            if (cstr[i] == from) {                                               \
                uz##N##_move(cstr + i + to_len, cstr + i + 1, cstr_len - i - 1); \
                uz##N##_copy_n(cstr + i, to, to_len);                            \
                cstr_len += to_len - 1;                                          \
                ++inner_count;                                                   \
            }                                                                    \
                                                                                 \
        if (count)                                                               \
            *count = inner_count;                                                \
                                                                                 \
        return cstr_len;                                                         \
    }

#define USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count) \
    {                                                                         \
        assert(cstr);                                                         \
                                                                              \
        size_t inner_count = 0;                                               \
                                                                              \
        for (size_t i = 0; i < cstr_len; ++i)                                 \
            if (cstr[i] == from)                                              \
                ++inner_count;                                                \
                                                                              \
        if (count)                                                            \
            *count = inner_count;                                             \
                                                                              \
        return cstr_len + to_len * inner_count - inner_count;                 \
    }

#define USTR_RETURN_N_REPLACE_Z_N_Z_N_(N, cstr, cstr_len, from, from_len, to, to_len, count) \
    {                                                                                        \
        assert(cstr && from && to);                                                          \
                                                                                             \
        if (!from_len || from_len > cstr_len) {                                              \
            if (count)                                                                       \
                *count = 0;                                                                  \
                                                                                             \
            return cstr_len;                                                                 \
        }                                                                                    \
                                                                                             \
        size_t    inner_count  = 0;                                                          \
        size_t    new_cstr_len = cstr_len;                                                   \
        ptrdiff_t len_delta    = from_len - to_len;                                          \
                                                                                             \
        while (true) {                                                                       \
            ptrdiff_t pos = uz##N##_n_pos_n(cstr, cstr_len, from, from_len);                 \
                                                                                             \
            if (pos < 0)                                                                     \
                break;                                                                       \
                                                                                             \
            cstr         += pos;                                                             \
            cstr_len     -= len_delta + pos;                                                 \
            new_cstr_len -= len_delta;                                                       \
                                                                                             \
            uc##N##_t *new_cstr = cstr + to_len;                                             \
                                                                                             \
            uz##N##_move(new_cstr, cstr + from_len, cstr_len);                               \
            uz##N##_copy_n(cstr, to, to_len);                                                \
                                                                                             \
            cstr = new_cstr;                                                                 \
                                                                                             \
            ++inner_count;                                                                   \
        }                                                                                    \
                                                                                             \
        if (count)                                                                           \
            *count = inner_count;                                                            \
                                                                                             \
        return new_cstr_len;                                                                 \
    }

#define USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(N, cstr, cstr_len, from, from_len, to_len, count) \
    {                                                                                        \
        assert(cstr && from);                                                                \
                                                                                             \
        if (!from_len || from_len > cstr_len) {                                              \
            if (count)                                                                       \
                *count = 0;                                                                  \
                                                                                             \
            return cstr_len;                                                                 \
        }                                                                                    \
                                                                                             \
        size_t    inner_count   = 0;                                                         \
        size_t    new_cstr_len  = cstr_len;                                                  \
        ptrdiff_t new_len_delta = from_len - to_len;                                         \
                                                                                             \
        while (true) {                                                                       \
            ptrdiff_t pos = uz##N##_n_pos_n(cstr, cstr_len, from, from_len);                 \
                                                                                             \
            if (pos < 0)                                                                     \
                break;                                                                       \
                                                                                             \
            size_t len_delta = from_len + pos;                                               \
                                                                                             \
            cstr         += len_delta;                                                       \
            cstr_len     -= len_delta;                                                       \
            new_cstr_len -= new_len_delta;                                                   \
                                                                                             \
            ++inner_count;                                                                   \
        }                                                                                    \
                                                                                             \
        if (count)                                                                           \
            *count = inner_count;                                                            \
                                                                                             \
        return new_cstr_len;                                                                 \
    }

size_t uz32_replace_uc32_uc32(uc32_t *cstr, uc32_t from, uc32_t to) {
    return uz32_replace_uc32_uc32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uc32_c(uc32_t *cstr, uc32_t from, uc32_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz32_n_replace_uc32_uc32(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to) {
    return uz32_n_replace_uc32_uc32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uc32_uc32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, uc32_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz32_replace_uz32_uc32(uc32_t *cstr, const uc32_t *from, uc32_t to) {
    return uz32_replace_uz32_uc32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uc32_c(uc32_t *cstr, const uc32_t *from, uc32_t to, size_t *count) {
	return uz32_replace_uz32_n_uc32_c(cstr, from, uz32_len(from), to, count);
}

size_t uz32_n_replace_uz32_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to) {
    return uz32_n_replace_uz32_uc32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uz32_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, uc32_t to, size_t *count) {
	return uz32_n_replace_uz32_n_uc32_c(cstr, cstr_len, from, uz32_len(from), to, count);
}

size_t uz32_replace_uz32_n_uc32(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32_replace_uz32_n_uc32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32_n_uc32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    return uz32_n_replace_uz32_n_uc32_c(cstr, uz32_len(cstr), from, from_len, to, count);
}

size_t uz32_n_replace_uz32_n_uc32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to) {
    return uz32_n_replace_uz32_n_uc32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32_n_replace_uz32_n_uc32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, uc32_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(32, cstr, cstr_len, from, from_len, to, count);
}

size_t uz32_replace_uc32_uz32(uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32_replace_uc32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uz32_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_c(cstr, uz32_len(cstr), from, to, uz32_len(to), count);
}

size_t uz32_replace_uc32_uz32_len(const uc32_t *cstr, uc32_t from, const uc32_t *to) {
    return uz32_replace_uc32_uz32_len_c(cstr, from, to, NULL);
}

size_t uz32_replace_uc32_uz32_len_c(const uc32_t *cstr, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_len_c(cstr, uz32_len(cstr), from, uz32_len(to), count);
}

size_t uz32_n_replace_uc32_uz32(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32_n_replace_uc32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uc32_uz32_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_c(cstr, cstr_len, from, to, uz32_len(to), count);
}

size_t uz32_n_replace_uc32_uz32_len(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to) {
    return uz32_n_replace_uc32_uz32_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uc32_uz32_len_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_len_c(cstr, cstr_len, from, uz32_len(to), count);
}

size_t uz32_replace_uc32_uz32_n(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len) {
    return uz32_replace_uc32_uz32_n_c(cstr, from, to, to_len, NULL);
}

size_t uz32_replace_uc32_uz32_n_c(uc32_t *cstr, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_c(cstr, uz32_len(cstr), from, to, to_len, count);
}

size_t uz32_replace_uc32_uz32_n_len(const uc32_t *cstr, uc32_t from, size_t to_len) {
    return uz32_replace_uc32_uz32_n_len_c(cstr, from, to_len, NULL);
}

size_t uz32_replace_uc32_uz32_n_len_c(const uc32_t *cstr, uc32_t from, size_t to_len, size_t *count) {
	return uz32_n_replace_uc32_uz32_n_len_c(cstr, uz32_len(cstr), from, to_len, count);
}

size_t uz32_n_replace_uc32_uz32_n(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len) {
    return uz32_n_replace_uc32_uz32_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz32_n_replace_uc32_uz32_n_c(uc32_t *cstr, size_t cstr_len, uc32_t from, const uc32_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(32, cstr, cstr_len, from, to, to_len, count);
}

size_t uz32_n_replace_uc32_uz32_n_len(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len) {
    return uz32_n_replace_uc32_uz32_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz32_n_replace_uc32_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, uc32_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz32_replace_uz32_uz32(uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32_replace_uz32_uz32_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uz32_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, uz32_len(from), to, uz32_len(to), count);
}

size_t uz32_replace_uz32_uz32_len(const uc32_t *cstr, const uc32_t *from, const uc32_t *to) {
    return uz32_replace_uz32_uz32_len_c(cstr, from, to, NULL);
}

size_t uz32_replace_uz32_uz32_len_c(const uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, uz32_len(from), uz32_len(to), count);
}

size_t uz32_n_replace_uz32_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32_n_replace_uz32_uz32_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uz32_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, uz32_len(from), to, uz32_len(to), count);
}

size_t uz32_n_replace_uz32_uz32_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to) {
    return uz32_n_replace_uz32_uz32_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz32_n_replace_uz32_uz32_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, uz32_len(from), uz32_len(to), count);
}

size_t uz32_replace_uz32_n_uz32(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_replace_uz32_n_uz32_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32_n_uz32_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, from_len, to, uz32_len(to), count);
}

size_t uz32_replace_uz32_n_uz32_len(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_replace_uz32_n_uz32_len_c(cstr, from, from_len, to, NULL);
}

size_t uz32_replace_uz32_n_uz32_len_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, from_len, uz32_len(to), count);
}

size_t uz32_n_replace_uz32_n_uz32(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_n_replace_uz32_n_uz32_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, from_len, to, uz32_len(to), count);
}

size_t uz32_n_replace_uz32_n_uz32_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to) {
    return uz32_n_replace_uz32_n_uz32_len_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, from_len, uz32_len(to), count);
}

size_t uz32_replace_uz32_uz32_n(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uz32_replace_uz32_uz32_n_c(cstr, from, to, to_len, NULL);
}

size_t uz32_replace_uz32_uz32_n_c(uc32_t *cstr, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, uz32_len(from), to, to_len, count);
}

size_t uz32_replace_uz32_uz32_n_len(const uc32_t *cstr, const uc32_t *from, size_t to_len) {
    return uz32_replace_uz32_uz32_n_len_c(cstr, from, to_len, NULL);
}

size_t uz32_replace_uz32_uz32_n_len_c(const uc32_t *cstr, const uc32_t *from, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, uz32_len(from), to_len, count);
}

size_t uz32_n_replace_uz32_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len) {
    return uz32_n_replace_uz32_uz32_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz32_n_replace_uz32_uz32_n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, uz32_len(from), to, to_len, count);
}

size_t uz32_n_replace_uz32_uz32_n_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len) {
    return uz32_n_replace_uz32_uz32_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz32_n_replace_uz32_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, uz32_len(from), to_len, count);
}

size_t uz32_replace_uz32_n_uz32_n(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uz32_replace_uz32_n_uz32_n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz32_replace_uz32_n_uz32_n_c(uc32_t *cstr, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_c(cstr, uz32_len(cstr), from, from_len, to, to_len, count);
}

size_t uz32_replace_uz32_n_uz32_n_len(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32_replace_uz32_n_uz32_n_len_c(cstr, from, from_len, to_len, NULL);
}

size_t uz32_replace_uz32_n_uz32_n_len_c(const uc32_t *cstr, const uc32_t *from, size_t from_len, size_t to_len, size_t *count) {
	return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, uz32_len(cstr), from, from_len, to_len, count);
}

size_t uz32_n_replace_uz32_n_uz32_n(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len) {
    return uz32_n_replace_uz32_n_uz32_n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_n_c(uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, const uc32_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(32, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz32_n_replace_uz32_n_uz32_n_len(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len) {
    return uz32_n_replace_uz32_n_uz32_n_len_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz32_n_replace_uz32_n_uz32_n_len_c(const uc32_t *cstr, size_t cstr_len, const uc32_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(32, cstr, cstr_len, from, from_len, to_len, count);
}

size_t uz16_replace_uc16_uc16(uc16_t *cstr, uc16_t from, uc16_t to) {
    return uz16_replace_uc16_uc16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uc16_c(uc16_t *cstr, uc16_t from, uc16_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz16_n_replace_uc16_uc16(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to) {
    return uz16_n_replace_uc16_uc16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uc16_uc16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, uc16_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz16_replace_uz16_uc16(uc16_t *cstr, const uc16_t *from, uc16_t to) {
    return uz16_replace_uz16_uc16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uc16_c(uc16_t *cstr, const uc16_t *from, uc16_t to, size_t *count) {
	return uz16_replace_uz16_n_uc16_c(cstr, from, uz16_len(from), to, count);
}

size_t uz16_n_replace_uz16_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to) {
    return uz16_n_replace_uz16_uc16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uz16_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, uc16_t to, size_t *count) {
	return uz16_n_replace_uz16_n_uc16_c(cstr, cstr_len, from, uz16_len(from), to, count);
}

size_t uz16_replace_uz16_n_uc16(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16_replace_uz16_n_uc16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16_n_uc16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, uc16_t to, size_t *count) {
    return uz16_n_replace_uz16_n_uc16_c(cstr, uz16_len(cstr), from, from_len, to, count);
}

size_t uz16_n_replace_uz16_n_uc16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to) {
    return uz16_n_replace_uz16_n_uc16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16_n_replace_uz16_n_uc16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, uc16_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(16, cstr, cstr_len, from, from_len, to, count);
}

size_t uz16_replace_uc16_uz16(uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16_replace_uc16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uz16_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_c(cstr, uz16_len(cstr), from, to, uz16_len(to), count);
}

size_t uz16_replace_uc16_uz16_len(const uc16_t *cstr, uc16_t from, const uc16_t *to) {
    return uz16_replace_uc16_uz16_len_c(cstr, from, to, NULL);
}

size_t uz16_replace_uc16_uz16_len_c(const uc16_t *cstr, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_len_c(cstr, uz16_len(cstr), from, uz16_len(to), count);
}

size_t uz16_n_replace_uc16_uz16(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16_n_replace_uc16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uc16_uz16_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_c(cstr, cstr_len, from, to, uz16_len(to), count);
}

size_t uz16_n_replace_uc16_uz16_len(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to) {
    return uz16_n_replace_uc16_uz16_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uc16_uz16_len_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_len_c(cstr, cstr_len, from, uz16_len(to), count);
}

size_t uz16_replace_uc16_uz16_n(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len) {
    return uz16_replace_uc16_uz16_n_c(cstr, from, to, to_len, NULL);
}

size_t uz16_replace_uc16_uz16_n_c(uc16_t *cstr, uc16_t from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_c(cstr, uz16_len(cstr), from, to, to_len, count);
}

size_t uz16_replace_uc16_uz16_n_len(const uc16_t *cstr, uc16_t from, size_t to_len) {
    return uz16_replace_uc16_uz16_n_len_c(cstr, from, to_len, NULL);
}

size_t uz16_replace_uc16_uz16_n_len_c(const uc16_t *cstr, uc16_t from, size_t to_len, size_t *count) {
	return uz16_n_replace_uc16_uz16_n_len_c(cstr, uz16_len(cstr), from, to_len, count);
}

size_t uz16_n_replace_uc16_uz16_n(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len) {
    return uz16_n_replace_uc16_uz16_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz16_n_replace_uc16_uz16_n_c(uc16_t *cstr, size_t cstr_len, uc16_t from, const uc16_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(16, cstr, cstr_len, from, to, to_len, count);
}

size_t uz16_n_replace_uc16_uz16_n_len(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len) {
    return uz16_n_replace_uc16_uz16_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz16_n_replace_uc16_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, uc16_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz16_replace_uz16_uz16(uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16_replace_uz16_uz16_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uz16_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, uz16_len(from), to, uz16_len(to), count);
}

size_t uz16_replace_uz16_uz16_len(const uc16_t *cstr, const uc16_t *from, const uc16_t *to) {
    return uz16_replace_uz16_uz16_len_c(cstr, from, to, NULL);
}

size_t uz16_replace_uz16_uz16_len_c(const uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, uz16_len(from), uz16_len(to), count);
}

size_t uz16_n_replace_uz16_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16_n_replace_uz16_uz16_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uz16_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, uz16_len(from), to, uz16_len(to), count);
}

size_t uz16_n_replace_uz16_uz16_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to) {
    return uz16_n_replace_uz16_uz16_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz16_n_replace_uz16_uz16_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, uz16_len(from), uz16_len(to), count);
}

size_t uz16_replace_uz16_n_uz16(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_replace_uz16_n_uz16_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16_n_uz16_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, from_len, to, uz16_len(to), count);
}

size_t uz16_replace_uz16_n_uz16_len(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_replace_uz16_n_uz16_len_c(cstr, from, from_len, to, NULL);
}

size_t uz16_replace_uz16_n_uz16_len_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, from_len, uz16_len(to), count);
}

size_t uz16_n_replace_uz16_n_uz16(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_n_replace_uz16_n_uz16_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, from_len, to, uz16_len(to), count);
}

size_t uz16_n_replace_uz16_n_uz16_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to) {
    return uz16_n_replace_uz16_n_uz16_len_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, from_len, uz16_len(to), count);
}

size_t uz16_replace_uz16_uz16_n(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len) {
    return uz16_replace_uz16_uz16_n_c(cstr, from, to, to_len, NULL);
}

size_t uz16_replace_uz16_uz16_n_c(uc16_t *cstr, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, uz16_len(from), to, to_len, count);
}

size_t uz16_replace_uz16_uz16_n_len(const uc16_t *cstr, const uc16_t *from, size_t to_len) {
    return uz16_replace_uz16_uz16_n_len_c(cstr, from, to_len, NULL);
}

size_t uz16_replace_uz16_uz16_n_len_c(const uc16_t *cstr, const uc16_t *from, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, uz16_len(from), to_len, count);
}

size_t uz16_n_replace_uz16_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len) {
    return uz16_n_replace_uz16_uz16_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz16_n_replace_uz16_uz16_n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, uz16_len(from), to, to_len, count);
}

size_t uz16_n_replace_uz16_uz16_n_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len) {
    return uz16_n_replace_uz16_uz16_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz16_n_replace_uz16_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, uz16_len(from), to_len, count);
}

size_t uz16_replace_uz16_n_uz16_n(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    return uz16_replace_uz16_n_uz16_n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz16_replace_uz16_n_uz16_n_c(uc16_t *cstr, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_c(cstr, uz16_len(cstr), from, from_len, to, to_len, count);
}

size_t uz16_replace_uz16_n_uz16_n_len(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16_replace_uz16_n_uz16_n_len_c(cstr, from, from_len, to_len, NULL);
}

size_t uz16_replace_uz16_n_uz16_n_len_c(const uc16_t *cstr, const uc16_t *from, size_t from_len, size_t to_len, size_t *count) {
	return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, uz16_len(cstr), from, from_len, to_len, count);
}

size_t uz16_n_replace_uz16_n_uz16_n(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len) {
    return uz16_n_replace_uz16_n_uz16_n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_n_c(uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, const uc16_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(16, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz16_n_replace_uz16_n_uz16_n_len(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len) {
    return uz16_n_replace_uz16_n_uz16_n_len_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz16_n_replace_uz16_n_uz16_n_len_c(const uc16_t *cstr, size_t cstr_len, const uc16_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(16, cstr, cstr_len, from, from_len, to_len, count);
}

size_t uz8_replace_uc8_uc8(uc8_t *cstr, uc8_t from, uc8_t to) {
    return uz8_replace_uc8_uc8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uc8_c(uc8_t *cstr, uc8_t from, uc8_t to, size_t *count) {
    USTR_RETURN_REPLACE_C_C_(cstr, from, to, count);
}

size_t uz8_n_replace_uc8_uc8(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to) {
    return uz8_n_replace_uc8_uc8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uc8_uc8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, uc8_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_C_C_(cstr, cstr_len, from, to, count);
}

size_t uz8_replace_uz8_uc8(uc8_t *cstr, const uc8_t *from, uc8_t to) {
    return uz8_replace_uz8_uc8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uc8_c(uc8_t *cstr, const uc8_t *from, uc8_t to, size_t *count) {
	return uz8_replace_uz8_n_uc8_c(cstr, from, uz8_len(from), to, count);
}

size_t uz8_n_replace_uz8_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to) {
    return uz8_n_replace_uz8_uc8_c(cstr, cstr_len, from, to, NULL);
}
    
size_t uz8_n_replace_uz8_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, uc8_t to, size_t *count) {
	return uz8_n_replace_uz8_n_uc8_c(cstr, cstr_len, from, uz8_len(from), to, count);
}

size_t uz8_replace_uz8_n_uc8(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8_replace_uz8_n_uc8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8_n_uc8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, uc8_t to, size_t *count) {
    return uz8_n_replace_uz8_n_uc8_c(cstr, uz8_len(cstr), from, from_len, to, count);
}

size_t uz8_n_replace_uz8_n_uc8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to) {
    return uz8_n_replace_uz8_n_uc8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8_n_replace_uz8_n_uc8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, uc8_t to, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_C_(8, cstr, cstr_len, from, from_len, to, count);
}

size_t uz8_replace_uc8_uz8(uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8_replace_uc8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uz8_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_c(cstr, uz8_len(cstr), from, to, uz8_len(to), count);
}

size_t uz8_replace_uc8_uz8_len(const uc8_t *cstr, uc8_t from, const uc8_t *to) {
    return uz8_replace_uc8_uz8_len_c(cstr, from, to, NULL);
}

size_t uz8_replace_uc8_uz8_len_c(const uc8_t *cstr, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_len_c(cstr, uz8_len(cstr), from, uz8_len(to), count);
}

size_t uz8_n_replace_uc8_uz8(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8_n_replace_uc8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uc8_uz8_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_c(cstr, cstr_len, from, to, uz8_len(to), count);
}

size_t uz8_n_replace_uc8_uz8_len(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to) {
    return uz8_n_replace_uc8_uz8_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uc8_uz8_len_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_len_c(cstr, cstr_len, from, uz8_len(to), count);
}

size_t uz8_replace_uc8_uz8_n(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len) {
    return uz8_replace_uc8_uz8_n_c(cstr, from, to, to_len, NULL);
}

size_t uz8_replace_uc8_uz8_n_c(uc8_t *cstr, uc8_t from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_c(cstr, uz8_len(cstr), from, to, to_len, count);
}

size_t uz8_replace_uc8_uz8_n_len(const uc8_t *cstr, uc8_t from, size_t to_len) {
    return uz8_replace_uc8_uz8_n_len_c(cstr, from, to_len, NULL);
}

size_t uz8_replace_uc8_uz8_n_len_c(const uc8_t *cstr, uc8_t from, size_t to_len, size_t *count) {
	return uz8_n_replace_uc8_uz8_n_len_c(cstr, uz8_len(cstr), from, to_len, count);
}

size_t uz8_n_replace_uc8_uz8_n(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len) {
    return uz8_n_replace_uc8_uz8_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz8_n_replace_uc8_uz8_n_c(uc8_t *cstr, size_t cstr_len, uc8_t from, const uc8_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_(8, cstr, cstr_len, from, to, to_len, count);
}

size_t uz8_n_replace_uc8_uz8_n_len(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len) {
    return uz8_n_replace_uc8_uz8_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz8_n_replace_uc8_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, uc8_t from, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_C_Z_N_LEN_(cstr, cstr_len, from, to_len, count);
}

size_t uz8_replace_uz8_uz8(uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8_replace_uz8_uz8_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uz8_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, uz8_len(from), to, uz8_len(to), count);
}

size_t uz8_replace_uz8_uz8_len(const uc8_t *cstr, const uc8_t *from, const uc8_t *to) {
    return uz8_replace_uz8_uz8_len_c(cstr, from, to, NULL);
}

size_t uz8_replace_uz8_uz8_len_c(const uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, uz8_len(from), uz8_len(to), count);
}

size_t uz8_n_replace_uz8_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8_n_replace_uz8_uz8_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uz8_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, uz8_len(from), to, uz8_len(to), count);
}

size_t uz8_n_replace_uz8_uz8_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to) {
    return uz8_n_replace_uz8_uz8_len_c(cstr, cstr_len, from, to, NULL);
}

size_t uz8_n_replace_uz8_uz8_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, uz8_len(from), uz8_len(to), count);
}

size_t uz8_replace_uz8_n_uz8(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_replace_uz8_n_uz8_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8_n_uz8_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, from_len, to, uz8_len(to), count);
}

size_t uz8_replace_uz8_n_uz8_len(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_replace_uz8_n_uz8_len_c(cstr, from, from_len, to, NULL);
}

size_t uz8_replace_uz8_n_uz8_len_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, from_len, uz8_len(to), count);
}

size_t uz8_n_replace_uz8_n_uz8(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_n_replace_uz8_n_uz8_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, from_len, to, uz8_len(to), count);
}

size_t uz8_n_replace_uz8_n_uz8_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to) {
    return uz8_n_replace_uz8_n_uz8_len_c(cstr, cstr_len, from, from_len, to, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, from_len, uz8_len(to), count);
}

size_t uz8_replace_uz8_uz8_n(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len) {
    return uz8_replace_uz8_uz8_n_c(cstr, from, to, to_len, NULL);
}

size_t uz8_replace_uz8_uz8_n_c(uc8_t *cstr, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, uz8_len(from), to, to_len, count);
}

size_t uz8_replace_uz8_uz8_n_len(const uc8_t *cstr, const uc8_t *from, size_t to_len) {
    return uz8_replace_uz8_uz8_n_len_c(cstr, from, to_len, NULL);
}

size_t uz8_replace_uz8_uz8_n_len_c(const uc8_t *cstr, const uc8_t *from, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, uz8_len(from), to_len, count);
}

size_t uz8_n_replace_uz8_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len) {
    return uz8_n_replace_uz8_uz8_n_c(cstr, cstr_len, from, to, to_len, NULL);
}

size_t uz8_n_replace_uz8_uz8_n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, uz8_len(from), to, to_len, count);
}

size_t uz8_n_replace_uz8_uz8_n_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len) {
    return uz8_n_replace_uz8_uz8_n_len_c(cstr, cstr_len, from, to_len, NULL);
}

size_t uz8_n_replace_uz8_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, uz8_len(from), to_len, count);
}

size_t uz8_replace_uz8_n_uz8_n(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    return uz8_replace_uz8_n_uz8_n_c(cstr, from, from_len, to, to_len, NULL);
}

size_t uz8_replace_uz8_n_uz8_n_c(uc8_t *cstr, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count) {
	return uz8_n_replace_uz8_n_uz8_n_c(cstr, uz8_len(cstr), from, from_len, to, to_len, count);
}

size_t uz8_replace_uz8_n_uz8_n_len(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8_replace_uz8_n_uz8_n_len_c(cstr, from, from_len, to_len, NULL);
}

size_t uz8_replace_uz8_n_uz8_n_len_c(const uc8_t *cstr, const uc8_t *from, size_t from_len, size_t to_len, size_t *count) {
    return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, uz8_len(cstr), from, from_len, to_len, count);
}

size_t uz8_n_replace_uz8_n_uz8_n(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len) {
    return uz8_n_replace_uz8_n_uz8_n_c(cstr, cstr_len, from, from_len, to, to_len, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_n_c(uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, const uc8_t *to, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_(8, cstr, cstr_len, from, from_len, to, to_len, count);
}

size_t uz8_n_replace_uz8_n_uz8_n_len(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len) {
    return uz8_n_replace_uz8_n_uz8_n_len_c(cstr, cstr_len, from, from_len, to_len, NULL);
}

size_t uz8_n_replace_uz8_n_uz8_n_len_c(const uc8_t *cstr, size_t cstr_len, const uc8_t *from, size_t from_len, size_t to_len, size_t *count) {
    USTR_RETURN_N_REPLACE_Z_N_Z_N_LEN_(8, cstr, cstr_len, from, from_len, to_len, count);
}