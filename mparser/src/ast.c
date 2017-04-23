
#include "ast.h"


struct ast *make_ast_leaf(tok *value)
{
	return make_ast(value, NULL, NULL);
}

struct ast *make_ast(tok *value, struct ast *left, struct ast *right)
{
	struct ast *node = malloc(sizeof(struct ast));
	node->value.value = value->value;
	node->value.type = value->type;
	node->left = left;
	node->right = right;
	return node;
}


struct ast *read_value()
{
	// printf("Reading Value\n");
	struct ast *value = NULL;
	tok next;
	tok_read(&next);

	// printf("%s\n", next.value);

	if (next.type == T_OP_PAR) {
		value = read_expression();
		tok_read(&next); // Throw away )
	}

	return value ? value : make_ast_leaf(&next);
}

struct ast *read_expression()
{
	// printf("Reading expr\n");
	struct ast *left, *right;
	tok op;

	left = read_value();

	if (!tok_read(&op))
		return left;

	right = read_value();

	return make_ast(&op, left, right);
}

struct ast *read_ast()
{
	// printf("Reading AST\n");
	struct ast *tree = read_expression();
	tok op;
	while (tok_read(&op))
	{
		if (op.type == T_MUL || op.type == T_DIV || op.type == T_POW)
		{
			struct ast *new_right = make_ast(&op, tree->right, read_value());
			tree->right = new_right;
		}
		else
		{
			tree = make_ast(&op, tree, read_expression());
		}
	}
	return tree;
}
