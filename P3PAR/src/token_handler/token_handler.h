#ifndef TOKEN_HANDLER_H
#define TOKEN_HANDLER_H

#include "../main.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum TokenCategory{
    CAT_NUMBER,
    CAT_IDENTIFIER,
    CAT_KEYWORD,
    CAT_LITERAL,
    CAT_OPERATOR,
    CAT_SPECIALCHAR,
    CAT_NONRECOGNIZED
} TokenCategory;

typedef struct Token{
    char *lexeme;
    size_t length;
    size_t capacity;
    TokenCategory category;
    int line;
    int column;
} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode *next;
} TokenNode;

typedef struct TokenList{
    TokenNode *head;
    TokenNode *tail;
    int size;
} TokenList;

// Token functions
Token* t_token_create(int line, int column);
void t_token_append_char(Token *t, char c);
void t_token_update_category(Token *t, TokenCategory cat);
void t_token_destroy(Token *t);

// Token list functions
TokenList *tl_token_list_init();
void tl_token_list_add(TokenList *list, Token t);
void tl_token_update_and_append(TokenList *list, Token *t, TokenCategory cat);
int  tl_token_list_size(const TokenList *list);
void tl_token_list_destroy(TokenList *list);

// Useful functions for the output module
void t_token_print_release(FILE *out, const Token *t);
void t_token_print_debug(FILE *out, const Token *t);

void tl_token_list_print_release(FILE *out, const TokenList *list);
void tl_token_list_print_debug(FILE *out, const TokenList *list);


void t_token_handler(void);

#endif