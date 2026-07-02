#ifndef bristle_ast_base_h
#define bristle_ast_base_h

typedef enum {
	NODE_ASSIGN,
	NODE_PRINT,
	NODE_BINARY,
	NODE_UNARY,
	NODE_INTEGER,
	NODE_IDENT,
} NodeType;

typedef struct {
	NodeType type;
} AstNode;

#endif
