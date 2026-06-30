#include <string.h>

#include "memory.h"
#include "text.h"

String NewString(void) {
	String s = {
		.length = 0,
		.capacity = 0,
		.chars = NULL
	};

	char* buffer = (char*) xmalloc(8);
	if (buffer == NULL) return s;

	s.capacity = 8;
	s.chars = buffer;
	return s;
}

int GrowString(String* str, size_t add_cap) {
	char* new_buf = xrealloc(str->chars, str->capacity + add_cap);
	
	if (new_buf == NULL) return -1;
	else {	
		str->chars = new_buf;
		return 0;
	}
}

int StringAppend(String* str, char c) {
	if (str->length + 1 > str->capacity) {
		int result = GrowString(str, str->capacity);
		if (result == -1) return -1;
	}

	str->chars[str->length++] = c;
	return 0;
}

void FreeString(String* str) {
	dealloc(str->chars);
	str->length = 0;
	str->capacity = 0;
	str->chars = NULL;
}

Slice SliceChars(char* chars) {
	return (Slice) {
		.length = strlen(chars),
		.chars = chars,
	};
}
