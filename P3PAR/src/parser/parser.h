#ifndef MODULE_PARSER_H
#define MODULE_PARSER_H

#include "../main.h"

typedef struct Parser {
    SRA* SRA;
    TokenList* token;
} Parser;

typedef enum {
    SYM_S = 0,
    SYM_LPAREN,
    SYM_RPAREN,
    SYM_PLUS,
    SYM_STAR,
    SYM_NUM,
    SYM_EOF,

    SYM_e,
    SYM_t,
    SYM_f

} SymbolID;

Parser* parser_create(SRA* sra, TokenList* tokens);
void parser_destroy(Parser* parser);
Symbol parser_token_to_symbol(Token token);
int parser_run(Parser* parser);

#endif