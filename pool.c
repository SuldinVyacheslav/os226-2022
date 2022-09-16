#include <stddef.h>

#include "pool.h"

void pool_init(struct pool *p, void *mem, unsigned long nmemb, unsigned long membsz) {
    p->mem = mem;
    p->membsz = membsz;
    p->freestart = (char*)mem;
    p->freeend = (char*)mem + nmemb * membsz;
    p->free = NULL;
}

void *pool_alloc(struct pool *p) {
    struct pool_free_block *fb = p->free;
    if (fb) {
        p->free = fb->next;
        return fb;
    }

    if (p->freestart < p->freeend) {
        void *r = p->freestart;
        p->freestart += p->membsz;
        return r;
    }

    return NULL;
}

void pool_free(struct pool *p, void *ptr) {
    if (ptr)
    {
        void *tmp_next = p->free;
        p->free = ptr;
        p->free->next = tmp_next;
    }
    else return;

}