#include <stdio.h>
#include "lexer.h"

int main(int argc, char** argv) {
	
	const char* source = "()+/23;h\nprint let hello 2 \n ();";
	Lexer lex = NewLexer(source);

	for (;;) {
		Token tk = NextToken(&lex);
		if (tk.kind == TOKEN_END) break;
		printf("%.*s\n", (int) tk.length, tk.chars);
	}
	
	return 0;
}
