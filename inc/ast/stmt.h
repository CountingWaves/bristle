#ifndef bristle_ast_stmt_h
#define bristle_ast_stmt_h

#include "ast/base.h"

typedef struct {
	AstNode base;
	AstNode* lvalue;
	AstNode* rvalue;
} AssignNode;

typedef struct {
	AstNode base;
	AstNode* expr;
} PrintNode;

#endif
