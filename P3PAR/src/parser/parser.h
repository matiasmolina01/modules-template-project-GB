#ifndef MODULE_PARSER_H
#define MODULE_PARSER_H

#include "../main.h"

#define PARSE_ERROR -1

#define ACT_REDUCE_NAME "REDUCE"
#define ACT_SHIFT_NAME "SHIFT"
#define ACT_ACCEPT_NAME "REDUCE"
#define ACT_ERROR_NAME "REDUCE"

typedef struct Language Language;
typedef struct SRA SRA;
typedef struct TokenList TokenList;
typedef struct Token Token;
typedef struct TokenNode TokenNode;


typedef struct Parser {
    SRA* SRA;
    TokenList* token;
} Parser;


Parser* parser_create(SRA* sra, TokenList* tokens);
void parser_destroy(Parser* parser);
int parser_run(Parser* parser, Language *language, FILE *output_file);

#endif