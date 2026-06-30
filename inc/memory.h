#ifndef bristle_memory_h
#define bristle_memory_h

#include <stddef.h>

// checked versions of the allocator functions
void* xmalloc(size_t n_bytes);
void* xcalloc(size_t n_bytes);
void* xrealloc(void* ptr, size_t n_bytes);
void dealloc(void* ptr);

#endif
