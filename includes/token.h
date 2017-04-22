#ifndef CALC_TOKEN_H
#define CALC_TOKEN_H

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#define T_ERR 0
#define T_SPC 1
#define T_NUM 2
#define T_MUL 3
#define T_DIV 4
#define T_ADD 5
#define T_SUB 6
#define T_POW 7
#define T_OP_PAR 8
#define T_CL_PAR 9

typedef int tok_type;

typedef struct {
	char *value;
	tok_type type;
} tok;

inline bool is_expression(const tok_type type)
{
	return type == T_OP_PAR;
}

inline bool is_value(const tok_type type)
{
	return type == T_NUM;
}

inline bool is_operation(const tok_type type)
{
	return type == T_MUL || type == T_DIV || type ==  T_ADD || type == T_SUB || type == T_POW;
}

inline tok_type get_char_type(const char c)
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
		case '(': return T_OP_PAR;
		case ')': return T_CL_PAR;
		default:  return T_ERR;
	}
}

inline tok_type get_tok_type(const char *c)
{

	if (!c)
		return T_ERR;

	const int length = strlen(c);
	if (length == 0)
		return T_ERR;
	if (length == 1)
		return get_char_type(c[0]);

	tok_type first = get_char_type(c[0]);

	// Allow negative numbers. The first character of
	// a number MAY be negative.
	if (first == T_SUB && get_char_type(c[1]) == T_NUM)
		return T_NUM;

	// Everything else should be the same as the first
	// char.
	return first;
}

inline bool tok_read(tok *token)
{
	char *line = NULL;
	size_t size;

	if (getline(&line, &size, stdin) == -1)
		return false;

	token->type = get_tok_type(line);
	token->value = strdup(line);

	return true;
}


#endif
