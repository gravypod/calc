#ifndef CALC_AST_H
#define CALC_AST_H

#include "token.h"

struct ast {
	tok value;
	struct ast *left, *right;
};


struct ast *make_ast(tok *value, struct ast *left, struct ast *right);
struct ast *make_ast_leaf(tok *value);

struct ast *read_value();
struct ast *read_expression();
struct ast *read_ast();

#endif
