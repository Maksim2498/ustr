#include "mem.h"

#include <stdio.h>
#include <stdlib.h>

void unot_enought_memeory_(void) {
    fputs("Not enought memory", stderr);
    exit(EXIT_FAILURE);
}

void *usafe_alloc(size_t size) {
    void *block = malloc(size);

    if (!block)
        unot_enought_memeory_();

    return block;
}

void *usafe_realloc(void *block, size_t new_size) {
    void *new_block = realloc(block, new_size);

    if (!new_block)
        unot_enought_memeory_();

    return new_block;
}

void usafe_free(void *block) {
    free(block);
}

_Thread_local void *(*ualloc)(size_t)           = usafe_alloc;
_Thread_local void *(*urealloc)(void *, size_t) = usafe_realloc;
_Thread_local void (*ufree)(void *)             = usafe_free;