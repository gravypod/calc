#include "token.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

tok_type get_char_type(const char c)
{
	if (isdigit(c))
		return T_NUM;

	if (isspace(c))
		return T_SPC;

	switch (c) {
		case '+': return T_ADD;
		case '-': return T_SUB;
		case '*': return T_MUL;
		case '/': return T_DIV;
		case '^': return T_POW;
		default: return T_ERR;
	}
}

bool can_join_toks(const char left, const char right)
{
	tok_type left_type = get_char_type(left), right_type = get_char_type(right);

	if (left_type == T_SUB && right_type == T_NUM)
		return true;
	if (left_type == T_NUM && right_type == T_NUM)
		return true;

	return false;
}

int main(int argc, char **argv)
{
	for (char last = getchar(), next = getchar(); next != EOF; last = next, next = getchar())
	{
		// Do we print out this character.
		if (isspace(last))
			continue;

		// It's not a space so we want to keep it.
		putchar(last);

		// Is this character and the last one related?
		// If not, put a new line in.
		if (!can_join_toks(last, next))
			putchar('\n');
	}

	return 0;
}
