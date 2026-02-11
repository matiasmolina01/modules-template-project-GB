#ifndef MODULE_OUTPUT_HANDLER_H
#define MODULE_OUTPUT_HANDLER_H

#include "../main.h"

#define RELEASE 0
#define DEBUG 1
// Usage: gcc -DOUTFORMAT=DEBUG or gcc -DOUTFORMAT=RELEASE

#ifndef OUTFORMAT
#define OUTFORMAT RELEASE
#endif

/* TEMPORAL: minimal definitions so output_handler can access tok->fields */
typedef enum {
    TOK_UNKNOWN = 0
} TokenCategory;

typedef struct Token {
    char lexeme[126];
    TokenCategory category;
    int line;
    int column;
    struct Token *next;   /* if your list uses next pointers (optional) */
} Token;

typedef struct TokenList {
    Token *head;
} TokenList;


void o_output_handler(TokenList *list, const char *filename);



#endif