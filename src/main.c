#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "lexer.h"
#include "text.h"

void interpret(Slice source) {
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
	
		printf(" %d: '%.*s'\n", tk.kind, tk.lexeme.length, tk.lexeme.chars);
		if (tk.kind == TOKEN_END) return;
	}
}

void repl() {

	String source;

	for (;;) {
		printf("> ");
		source = ReadLineStdin();

		if (source.length == 0) {
			printf("\n");
			return;
		}

		interpret((Slice) { 
			.length = source.length, 
			.chars = source.chars 
		});

		FreeString(&source);
	}

}

void RunFile(char* path) {
	IOError err;
	Slice source = ReadFile(path, &err);

	switch (err) {
		case IO_STATUS_OK:
			interpret(source);
			return;
		case BAD_FILE_PATH:
			fprintf(stderr, "Could not find file '%s'", path);
			break;
		case FILE_OOM:
			fprintf(stderr, "Insufficient memory to read file '%s'", path);
			break;
		case FILE_READ_ERROR:
			fprintf(stderr, "Error while reading file '%s'", path);
			break;
	}
	exit(1);
}

int main(int argc, char** argv) {

	if (argc == 1) {
		repl();
	} else if (argc == 2) {
		RunFile(argv[1]);
	} else {
		fprintf(stderr, "Usage: bristle [file_path]\n");
		return 1;
	}

	return 0;
}
