#include <assert.h>
#include <stdio.h>

#include "lexer.h"
#include "text.h"

int main(void) {

	// Initialize source code and lexer
	Slice source = SliceChars("23() += ?! hello\n print let\t */;");
	Lexer* lex = NewLexer(source);

	// allocate an array for all the tokens, plus
	// two at the end to make sure the lexer keeps
	// producing EOF tokens
	const int NUM_EXPECTED = 14;
	Token tokens[NUM_EXPECTED + 2]; 

	// Get the tokens
	for (int i = 0; i < NUM_EXPECTED + 2; i++) {
		tokens[i] = NextToken(lex);
	}
	
	unsigned int lines[] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
	unsigned int kinds[] = { 
		TOKEN_INTEGER, TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
		TOKEN_PLUS, TOKEN_EQUAL, TOKEN_ERROR, TOKEN_ERROR,
		TOKEN_IDENTIFIER, TOKEN_PRINT, TOKEN_LET,
		TOKEN_STAR, TOKEN_SLASH, TOKEN_SEMICOLON,
		TOKEN_END, TOKEN_END, TOKEN_END
	};

	for (int i = 0; i < NUM_EXPECTED + 2; i++) {
		assert(tokens[i].line == lines[i]);
		assert(tokens[i].kind == kinds[i]);

		printf("  { line: %d, kind: %d, chars: '%.*s'}\n",
			tokens[i].line, tokens[i].kind, 
			(int) tokens[i].lexeme.length, 
			tokens[i].lexeme.chars
		);
	}

	return 0;
}
