#ifndef bristle_lexer_h
#define bristle_lexer_h

#include "text.h"

typedef enum {
	// one or two character tokens
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_SEMICOLON,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,
	TOKEN_EQUAL,
	
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
	Slice lexeme;

	// other token data
	TokenKind kind;
	unsigned int line;	
} Token;

typedef struct {
	Slice source;

	// fields to track position in source
	const unsigned char* start;
	const unsigned char* current;
	unsigned int line;
} Lexer;


Lexer NewLexer(Slice source);
Token NextToken(Lexer* lexer);

#endif
