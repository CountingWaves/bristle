#ifndef bristle_text_h
#define bristle_text_h

// Helper module for implementing length-based
// string slices, instead of null-terminated strings
// see docs/text.md for more detail

#include <stddef.h>

typedef struct {
	size_t length;
	size_t capacity;
	char* chars;
} String;

typedef struct {
	size_t length;
	char* chars;
} Slice;

// String constructors
String NewString(void);

// String utility methods
int StringAppend(String* str, char c);

// String destructor
void FreeString(String* str);


// slice constructors
Slice SliceChars(char* chars);

#endif
