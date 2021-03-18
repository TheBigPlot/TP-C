#ifndef ALLOC_H
#define ALLOC_H

#define _GNU_SOURCE 
#include <dlfcn.h>


void free(void *ptr);
void *malloc(size_t size);
void* realloc(void* ptr, size_t size);

void r_free(void *ptr);
void *r_malloc(size_t size);

void g_free(void *ptr);
void *g_malloc(size_t size);

#endif
