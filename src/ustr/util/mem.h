#ifndef USTR_UTIL_MEM_H
#define USTR_UTIL_MEM_H

#include <stddef.h>

void *usafe_alloc(size_t size);
void *usafe_realloc(void *block, size_t new_size);
void usafe_free(void *block);

extern _Thread_local void *(*ualloc)(size_t);
extern _Thread_local void *(*urealloc)(void *, size_t);
extern _Thread_local void (*ufree)(void *);

#endif