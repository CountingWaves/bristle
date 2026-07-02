#ifndef bristle_ast_unary_h
#define bristle_ast_unary_h

#include "ast/base.h"

typedef enum {
	UNARY_NEGATE,
} UnaryOp;

typedef struct {
	AstNode base;
	UnaryOp op;
	AstNode* expr;
} UnaryNode;

#endif
