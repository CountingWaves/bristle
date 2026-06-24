#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

// I'm borrowing pretty heavily from
// Crafting Interpreters right now, 
// in case you couldn't tell

void execute(char* source) {
	Lexer lex = NewLexer(source);
	int line = 0;

	for (;;) {
		Token tk = NextToken(&lex);

		if (tk.line == line) {
			printf("   |");
		} else {
			line = tk.line;
			printf("%4d", line);
		}
	
		printf(" %d: '%.*s'\n", tk.kind, tk.length, tk.chars);
		if (tk.kind == TOKEN_END) return;
	}
}

void repl() {

	char buffer[256];

	for (;;) {
		printf("> ");
		if (fgets(buffer, 256, stdin) == NULL) { 
			printf("\n");
			return;
		}
		execute(buffer);
	}

}

char* ReadFile(char* path) {
	FILE* file = fopen(path, "r");

	if (file == NULL) {
		fprintf(stderr, "Failed to open file '%s'", path);
		exit(1);
	}

	// get the size of the file
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	// allocate a heap buffer for the source code
	char* buffer = (char*) malloc(size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Not enough memory to read file '%s'!", path);
		exit(1);
	}

	// read file contents into the buffer
	size_t bytesRead = fread(buffer, 1, size, file);
	if (bytesRead < size) {
		fprintf(stderr, "Error while reading file '%s'!", path);
		exit(1);
	}

	buffer[bytesRead] = '\0';
	
	// release the file and return the buffer
	fclose(file);
	return buffer;
}


int main(int argc, char** argv) {

	if (argc == 1) {
		repl();
	} else if (argc == 2) {
		char* source = ReadFile(argv[1]);
		execute(source);
	} else {
		fprintf(stderr, "Usage: bristle [file_path]\n");
		return 1;
	}

	return 0;
}
