#include "mem.h"

#include <stdlib.h>

_Thread_local void *(*ualloc)(size_t)           = malloc;
_Thread_local void *(*urealloc)(void *, size_t) = realloc;
_Thread_local void (*ufree)(void *)             = free;