#ifndef USTR_TYPE_CHAR_H
#define USTR_TYPE_CHAR_H

#include <stdint.h>

typedef uint32_t uc32_t;
typedef uint16_t uc16_t;
typedef uint8_t  uc8_t;

typedef int (*uc8_to_case_len_func_t)(const uc8_t *);

typedef int (*uc8_to_case_func_t)(uc8_t *);
typedef int (*uc16_to_case_func_t)(uc16_t *);
typedef uc32_t (*uc32_to_case_func_t)(uc32_t);

#endif