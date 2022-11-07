#ifndef USTR_CSTR_H
#define USTR_CSTR_H

#include <stddef.h>

#include "char_t.h"

// Len

size_t uz32_len(const uc32_t *cstr);
size_t uz16_len(const uc16_t *cstr);
size_t uz8_len(const uc8_t *cstr);

// Cmp

int uz32_cmp(const uc32_t *lhs, const uc32_t *rhs);
int uz32_cmp_n(const uc32_t *lhs, const uc32_t *rhs, size_t n);
int uz16_cmp(const uc16_t *lhs, const uc16_t *rhs);
int uz16_cmp_n(const uc16_t *lhs, const uc16_t *rhs, size_t n);
int uz8_cmp(const uc8_t *lhs, const uc8_t *rhs);
int uz8_cmp_n(const uc8_t *lhs, const uc8_t *rhs, size_t n);

#endif