#include <stdbool.h>
#include <stdio.h>

//#include "ast.h"
#include "lexer.h"
#include "memory.h"
#include "parser.h"
#include "text.h"

typedef struct Parser {
	Lexer* lexer;
	Token previous;
	Token current;
} Parser;

Parser* NewParser(Slice source) {
	Lexer* lexer = NewLexer(source);
	Parser* parser = xmalloc(sizeof(Parser));
	
	parser->lexer = lexer;
	parser->current = NextToken(lexer);

	return parser;
}

bool Advance(Parser* parser) {
	parser->previous = parser->current;
	parser->current = NextToken(parser->lexer);

	return parser->current.kind == TOKEN_ERROR;
}

// error handling code
void DisplayError(Token* token, Slice msg) {
	fprintf(stderr, "Error on line %d", token->line);
	
	if (token->kind == TOKEN_END) {
		fprintf(stderr, ", at end of file: '%.*s'\n", 
				(int) msg.length, msg.chars);
		return;
	} else if (token->kind == TOKEN_ERROR) {
		Slice err = token->lexeme;
		fprintf(stderr, ": '%.*s'\n", (int) err.length, err.chars);
		return;
	}
	
	Slice lexeme = token->lexeme;
	fprintf(stderr, ", at '%.*s':", (int) lexeme.length, lexeme.chars);
	fprintf(stderr, " '%.*s'", (int) msg.length, msg.chars);
}

void Error(Parser* parser, Slice msg) {
	DisplayError(&parser->previous, msg);
}

void ErrorAtCurrent(Parser* parser, Slice msg) {
	DisplayError(&parser->current, msg);
}

void Panic(Parser* parser) {
	while (parser->current.kind != TOKEN_END) {
		Advance(parser);
	}
}
