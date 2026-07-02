# io.h documentation

The `io.h` header provides I/O functions built on the functionality
provided in `stdio.h`.

## Enum IOError

This enum represents a set of error codes that fallible I/O functions
can throw. It is generally used as an out-parameter.

## ReadFile

Reads the contents of a file into a string slice.

### Parameters
- path: (char*), path of the file to be read
- err: (IOError*) \[Out], used to indicate the success/failure of
    the function call.

### Return Value
- Returns a `Slice` (see docs for text.h)[./text.md] containing the entire
   contents of the file.

### Errors
- In the event of an error, ReadFile() returns a null slice (length 0, points
    to NULL), and an error is writen to err.
- The possible error codes are:
    - BAD_FILE_PATH, which indicates that the file that could not be opened.
    - FILE_READ_ERROR, which indicates an unspecified error occurred while 
    reading the contents of the file into memory.
    
### Usage

```{c}
#include <stdio.h>

#include "io.h"
#include "text.h"

int main(void) { 
    IOError err;
    Slice code = ReadFile("my_program.c", &err);

    switch (err) {
        case IO_STATUS_OK:
            break; // :)
        case BAD_FILE_PATH:
            printf("couldn't open the file\n");
            return 1;
        case FILE_READ_ERROR:
            printf("error while reading the file\n");
            return 1;
        default:
            break; // unreachable
    }

    // do what you want with the file text 
}

```

## ReadLineStdin

Reads a line of input from stdin.

### Return Value
