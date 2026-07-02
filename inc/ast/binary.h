#ifndef bristle_ast_binary_h
#define bristle_ast_binary_h

#include "ast/base.h"

typedef enum {
	BINARY_ADD,
	BINARY_SUB,
	BINARY_MULT,
	BINARY_DIV
} BinaryOp;

typedef struct {
	AstNode base;
	BinaryOp op;
	AstNode* lhs;
	AstNode* rhs;
} BinaryNode;

#endif
