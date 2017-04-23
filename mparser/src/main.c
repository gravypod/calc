
#include "token.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <math.h>

float value(struct ast *tree)
{
	// printf("%s\n", tree->value.value);
	switch (tree->value.type)
	{
		case T_MUL: return value(tree->left) * value(tree->right);
		case T_DIV: return value(tree->left) / value(tree->right);
		case T_ADD: return value(tree->left) + value(tree->right);
		case T_SUB: return value(tree->left) - value(tree->right);
		case T_POW: return powf(value(tree->left), value(tree->right));
		case T_NUM: return strtof(tree->value.value, NULL);
		default:           panic("Unknown token case for value %d\n", tree->value.type);
	}
}

int main(int argc, char **argv)
{
	printf("Parser: ");

	struct ast *tree = read_ast();

	if (tree == NULL)
		panics("Failed to read any expression from STDIN\n");

	printf("%f\n", value(tree));

	return 0;
}
