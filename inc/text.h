#ifndef bristle_text_h
#define bristle_text_h

#include <stddef.h>

typedef struct {
	size_t length;
	size_t capacity;
	unsigned char* chars;
} String;

typedef struct {
	size_t length;
	unsigned char* chars;
} Slice;

// String constructors
String NewString();

// String utility methods
int StringAppend(String* str, unsigned char c);

// String destructor
void FreeString(String* str);

#endif
