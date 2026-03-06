#ifndef MODULE_OUTPUT_HANDLER_H
#define MODULE_OUTPUT_HANDLER_H

#include <stdio.h>
#include "../main.h"

#define MAX_LEN 100


// typedef enum SymbolCategory{
//     CAT_NUMBER,
//     CAT_PLUS,
//     CAT_EOF,
//     CAT_MULT,
//     CAT_OPEN_PARENTHESIS,
//     CAT_CLOSE_PARENTHESIS,
//     CAT_S,
//     CAT_E,
//     CAT_T,
//     CAT_F


// }SymbolCategory;

typedef struct Token Token;
typedef struct Stack Stack;
typedef struct Language Language;
typedef struct TokenList TokenList;


void stack_instance_to_string(Stack *stack, char* string, Language *language);
FILE *o_open_output_file(char *input_filename);
int o_output_handler(FILE* fp, int index, Stack *stack, char *operation, int state, Language *language, TokenList *token_list);

#endif