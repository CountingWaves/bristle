#ifndef bristle_parser_pub_h
#define bristle_parser_pub_h

#include "ast/base.h"
#include "text.h"

typedef struct Parser Parser;

Parser* NewParser(Slice source);

// TODO!
AstNode* ParseBlock(Parser* parser);

#endif
