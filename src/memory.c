#include <stdlib.h>

#include "memory.h"

// Guarantees that the resulting pointer
// is a valid allocation
void* xmalloc(size_t n_bytes) {
	void* ptr = malloc(n_bytes);
	if (ptr == NULL) abort();
	return ptr;
}

void* xcalloc(size_t n_bytes) {
	void* ptr = calloc(n_bytes, sizeof(char));
	if (ptr == NULL) abort();
	return ptr;
}

void* xrealloc(void* ptr, size_t n_bytes) {
	void* new_ptr = realloc(ptr, n_bytes);
	if (new_ptr == NULL) abort();
	return new_ptr;
}

void dealloc(void* ptr) {
	free(ptr);
}
