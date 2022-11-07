#ifndef USTR_CSTR_H
#define USTR_CSTR_H

#include <stddef.h>

#include "char_t.h"

// Len

size_t uz32_len(const uc32_t *cstr);
size_t uz16_len(const uc16_t *cstr);
size_t uz8_len(const uc8_t *cstr);

#endif