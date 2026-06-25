#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "io.h"

#define NullSlice \
	((Slice) { .length = 0, .chars = NULL })

Slice ReadFile(char* path, IOError* err) {
	
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		*err = BAD_FILE_PATH;
		return NullSlice;
	}

	// get size of file
	fseek(file, 0, SEEK_END);
	long tell = (size_t) ftell(file);
	if (tell == -1) {
		*err = FILE_READ_ERROR;
		return NullSlice;
	}
	
	size_t size = (size_t) tell;
	rewind(file);

	// allocate buffer for file data
	unsigned char* buffer = (unsigned char*) malloc(size);
	if (buffer == NULL) {
		*err = FILE_OOM;
		return NullSlice;	
	}

	// read the file contents into a buffer
	size_t BytesRead = fread(buffer, 1, size, file);
	if (BytesRead < size) {
		*err = FILE_READ_ERROR;
		return NullSlice;
	}

	// clean up
	fclose(file);
	*err = IO_STATUS_OK;
	return (Slice) {
		.length = size,
		.chars = buffer
	};
}

String ReadLineStdin() {
	
	String buffer = NewString();
	
	int c = getchar();
	while (c != '\n' && c != EOF) {
		StringAppend(&buffer, (unsigned char) c);
		c = getchar();
	}	
	
	return buffer;
}
