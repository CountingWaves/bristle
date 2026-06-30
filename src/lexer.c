#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "memory.h"

struct Lexer {
	Slice source;

	// fields to track position in source
	char* start;
	char* current;
	unsigned int line;
};


Lexer* NewLexer(Slice source) {
	Lexer* lex = (Lexer*) xmalloc(sizeof(Lexer));

	*lex = (Lexer) {
		.source = source,
		.start = source.chars,
		.current = source.chars,
		.line = 1,
	};
	
	return lex;
}

static bool IsDigit(char c) {
	return '0' <= c && c <= '9';
}

static bool IsAlpha(char c) {
	return ('a' <= c && c <= 'z') ||
		('A' <= c && c <= 'Z') ||
		(c == '_');
}

static char Advance(Lexer* lexer) {
	if (lexer->current > lexer->source.chars + lexer->source.length) {
		return '\0';
	} else {
		return *lexer->current++;
	}
}

static char Peek(Lexer* lexer) {
	return *lexer->current;
}

static void SkipWhitespace(Lexer* lexer) {
	for (;;) {
		char c = Peek(lexer);
		switch (c) {
			case ' ':
			case '\t':
			case '\r':
				Advance(lexer);
				break;
			case '\n':
				lexer->line++;
				Advance(lexer);
				break;
			default:
				return;
		}
	}
}

static Token MakeToken(Lexer* lexer, TokenKind kind) {
	Token t = {
		.lexeme = (Slice) {
			.length = (size_t) (lexer->current - lexer->start),
			.chars = lexer->start
		},
		.kind = kind,
		.line = lexer->line
	};
	return t;
}

static Token ErrorToken(Lexer* lexer, char* msg) {
	Token t = {
		.lexeme = (Slice) {
			.length = strlen(msg),
			.chars = msg,
		},
		.kind = TOKEN_ERROR,
		.line = lexer->line,
	};
	return t;
}

static Token NumberToken(Lexer* lexer) {
	while (IsDigit(Peek(lexer))) Advance(lexer);
	return MakeToken(lexer, TOKEN_INTEGER);
}

static TokenKind CheckKeyword(Lexer* lexer, size_t start, size_t length,
		const char* rest, TokenKind keyword) 
{
	if ((size_t) (lexer->current - lexer->start) == start + length 
			&& memcmp(lexer->start + start, rest, length) == 0) 
	{
		return keyword;
	} else {
		return TOKEN_IDENTIFIER;
	}
}

static TokenKind IdentifyWord(Lexer* lexer) {
	char* word = lexer->start;

	switch (word[0]) {
		case 'l':
			return CheckKeyword(lexer, 1, 2, "et", TOKEN_LET);
		case 'p':
			return CheckKeyword(lexer, 1, 4, "rint", TOKEN_PRINT);
		default: 
			return TOKEN_IDENTIFIER;
	}
}

static Token WordToken(Lexer* lexer) {
	char c = Peek(lexer);
	while (IsDigit(c) || IsAlpha(c)) {
		Advance(lexer);
		c = Peek(lexer);
	}

	TokenKind kind = IdentifyWord(lexer);
	return MakeToken(lexer, kind);
}

Token NextToken(Lexer* lexer) {
	SkipWhitespace(lexer);
	lexer->start = lexer->current;
	
	char c = Advance(lexer);

	if (c == '\0') return MakeToken(lexer, TOKEN_END);
	else if (IsDigit(c)) return NumberToken(lexer);
	else if (IsAlpha(c)) return WordToken(lexer);

	switch (c) {
		case '(':
			return MakeToken(lexer, TOKEN_LEFT_PAREN);
		case ')':
			return MakeToken(lexer, TOKEN_RIGHT_PAREN);
		case ';':
			return MakeToken(lexer, TOKEN_SEMICOLON);
		case '+':
			return MakeToken(lexer, TOKEN_PLUS);
		case '-':
			return MakeToken(lexer, TOKEN_MINUS);
		case '*':
			return MakeToken(lexer, TOKEN_STAR);
		case '/':
			return MakeToken(lexer, TOKEN_SLASH);
		case '=':
			return MakeToken(lexer, TOKEN_EQUAL);
		default:
			return ErrorToken(lexer, "Unrecognized character!");
	}
}
