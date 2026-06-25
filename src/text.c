#include <stdlib.h>
#include <string.h>

#include "text.h"

String NewString() {
	unsigned char* buffer = (unsigned char*) malloc(8);
	if (buffer == NULL) {
		return (String) {
			.length = 0,
			.capacity = 0,
			.chars = NULL,
		};
	} else {
		return (String) {
			.length = 0,
			.capacity = 8,
			.chars = buffer,
		};
	}
}

int StringAppend(String* str, unsigned char c) {
	if (str->length + 1 > str->capacity) {
		unsigned char* new_buf = (unsigned char*) 
			realloc(str->chars, str->capacity * 2);

		if (new_buf == NULL) return -1;
		str->chars = new_buf;
	}

	str->chars[str->length++] = c;
	return 0;
}

void FreeString(String* str) {
	free(str->chars);
	str->length = 0;
	str->capacity = 0;
	str->chars = NULL;
}
