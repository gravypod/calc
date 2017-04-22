
#include "token.h"
#include "token.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define AST_NULL 0
#define AST_LEAF 1
#define AST_VALUE 2

struct ast {
	tok token;
	int left_type, right_type;
	void *left, *right;
};

struct ast *make_ast(tok *token, int left_type, void *left, int right_type, void *right)
{
	struct ast *a = malloc(sizeof(struct ast));

	a->token = *token;
	a->left_type = left_type;
	a->left = left;
	a->right_type = right_type;
	a->right = right;

	// memcpy(&a->token, token, sizeof(tok));

	return a;
}

int panic(char *msg)
{
	fprintf(stderr, msg);
	return 1;
}

struct ast *value()
{
	tok token;
	if (!tok_read(&token))
		exit(panic("ERR: Parser failed to find value\n"));
	return make_ast(&token, AST_VALUE, AST_VALUE, strdup(token.value), AST_NULL, 0);
}

tok_type type()
{
	tok token;
	if (!tok_read(&token))
		exit(panic("ERR: Parser failed to find value\n"));
	return token.type;
}

struct ast *parse()
{
	struct ast *a = NULL; // malloc(sizeof(struct ast));

	while (!feof(stdin))
	{

		struct ast *left = value();
		tok_type type = type();
		struct ast *right = value();

		tok token;

		if (!tok_read(&token))
			exit(panic("ERR: Parser failed to read tokens\n"));

		if (token.type == T_CL_PAR)
			return a;

		tok op_token, right_token;

		if (!tok_read(&token) || !tok_read(&right_token))
			exit(panic("ERR: Parser failed to read tokens\n"));

		

	}

	return a;
}

int main(int argc, char **argv)
{
	tok token;
	while (!feof(stdin))
	{
		if (!tok_read(&token))
			return panic("ERR: Parser failed to read tokens\n");
	}

	return 0;
}
