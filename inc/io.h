#ifndef bristle_io_h
#define bristle_io_h

#include "text.h"

typedef enum {
	IO_STATUS_OK,
	BAD_FILE_PATH,
	FILE_OOM,
	FILE_READ_ERROR,
} IOError;

Slice ReadFile(char* path, IOError* err);
String ReadLineStdin();

#endif
