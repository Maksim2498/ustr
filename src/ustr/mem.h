#ifndef USTR_MEM_H
#define USTR_MEM_H

#include <stddef.h>

extern _Thread_local void *(*ualloc)(size_t);
extern _Thread_local void *(*urealloc)(void *, size_t);
extern _Thread_local void (*ufree)(void *);

#endif