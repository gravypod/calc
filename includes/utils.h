#ifndef CALC_UTILS_H
#define CALC_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define panic(message, ...) { fprintf(stderr, message, ##__VA_ARGS__); exit(1); }
#define panics(message) panic("%s\n", message)

#endif
