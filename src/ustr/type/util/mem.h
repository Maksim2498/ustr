#ifndef USTR_TYPE_UTIL_MEM_H
#define USTR_TYPE_UTIL_MEM_H

#include <stddef.h>

typedef void *(*ualloc_t)(size_t);
typedef void *(*urealloc_t)(void *, size_t);
typedef void (*ufree_t)(void *);

#endif