#include "token.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int panic(char *msg)
{
	fprintf(stderr, msg);
	return 1;
}

int main(int argc, char **argv)
{

	unsigned int parens = 0;

	size_t size;

	tok_type last = T_ERR, next;
	for (char *token = NULL; getline(&token, &size, stdin) != -1; last = next)
	{

		next = get_tok_type(token);

		if (next == T_OP_PAR)
			parens++;
		if (next == T_CL_PAR)
			parens--;

		if (is_value(last) && !(is_operation(next) || next == T_CL_PAR))
			return panic("ERR: Values may only be followed by operations or close parens.\n");

		if (last == T_OP_PAR && !(is_value(next) || next == T_OP_PAR))
			return panic("ERR: Parens must be followed by a value or more parens.\n");

		if (last == T_CL_PAR && !(is_operation(next) || next == T_CL_PAR))
			return panic("ERR: Closing parens must be followed by operations or closing parens.\n");

		if (is_operation(last) && !(is_value(next) || next == T_OP_PAR))
			return panic("ERR: Operations must be folloed by parens or values.\n");

		// Pass token along
		// printf("%s\n", token);
	}

	if (last != T_NUM && last != T_CL_PAR)
		return panic("ERR: Expressions must end with either a value or a close paren. They can't end with OPs.\n");

	// Number of open and closed parens does not match.
	if (parens != 0)
		return panic("ERR: Mismatched parens.\n");

	return 0;
}
