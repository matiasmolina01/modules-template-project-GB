#ifndef MODULE_PARSER_H
#define MODULE_PARSER_H

#include "../main.h"

typedef struct Parser {
    SRA* SRA;
    TokenList* token;
} Parser;

Parser* parser_create(SRA* sra, TokenList* tokens);
void parser_destroy(Parser* parser);
int parser_run(Parser* parser);

#endif