#ifndef bristle_ast_simple_h
#define bristle_ast_simple_h

#include "ast/base.h"
#include "text.h"

typedef struct {
	AstNode base;
	int value;
} IntegerNode;

typedef struct {
	AstNode base;
	Slice ident;
} IdentNode;

#endif
