#ifndef bristle_lexer_h
#define bristle_lexer_h

#include <stddef.h>

typedef enum {
	// one or two character tokens
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_SEMICOLON,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,
	
	// literals
	TOKEN_INTEGER,
	TOKEN_IDENTIFIER,

	// keywords
	TOKEN_LET,
	TOKEN_PRINT,

	// special
	TOKEN_ERROR,
	TOKEN_END
} TokenKind;

typedef struct {
	// characters of token with source
	size_t length;
	const char* chars;

	// other token data
	TokenKind kind;
	unsigned int line;	
} Token;

typedef struct {
	const char* source;
	const char* start;
	const char* current;
	unsigned int line;
} Lexer;


Lexer NewLexer(const char* source);
Token NextToken(Lexer* lexer);

#endif
