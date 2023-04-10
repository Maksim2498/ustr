#ifndef USTR_UTIL_MEM_H
#define USTR_UTIL_MEM_H

#include <stddef.h>

#include <ustr/type/util/mem.h>

#include "export.h"

// Safe memory managment

UEXPORT void *usafe_alloc(size_t size);
UEXPORT void *usafe_realloc(void *block, size_t new_size);
UEXPORT void usafe_free(void *block);

// Library memory managment functions

UEXPORT extern _Thread_local ualloc_t   ualloc;
UEXPORT extern _Thread_local urealloc_t urealloc;
UEXPORT extern _Thread_local ufree_t    ufree;

#endif