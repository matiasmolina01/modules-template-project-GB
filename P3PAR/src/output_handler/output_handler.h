#ifndef MODULE_OUTPUT_HANDLER_H
#define MODULE_OUTPUT_HANDLER_H

#include <stdio.h>
#include "../main.h"

void stack_instance_to_string(Stack *stack, char* string);
const char *symbol_to_string(TokenCategory s);
FILE *o_open_output_file(const char *input_filename);
int o_output_handler(const Token *lookahead, const Stack *stack, cost char *operation, const char *input_filename, const int state);

#endif