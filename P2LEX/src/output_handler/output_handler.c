/*
 * -----------------------------------------------------------------------------
 * output_handler.c 
 *
 * Usage:
 *     Called from the scanner module or test modules to handle output.
 *
 * Status:
 *     Initial development — logic to handle output is not yet implemented.
 *
 * Author: Anna Vasileva
 * -----------------------------------------------------------------------------
 */

#include "./output_handler.h"

// This function doesn't need to exist, because token module already 
// provides the necessary fucntions to print the token list in the appropiate way.
static void write_token(FILE *fp, Token *tok) {
    #if OUTFORMAT == RELEASE
        // Should call t_token_print_release
        fprintf(fp, "%s\n", tok->lexeme);
    #else
        // Should call t_token_print_debug
        fprintf(fp,
            "LEXEME: %-15s | CATEGORY: %-10s | LINE: %d | COL: %d\n",
            tok->lexeme,
            token_category_to_string(tok->category),
            tok->line,
            tok->column
        );
    #endif
}

// This function should call tl_token_list_print_release if in RELEASE mode, or tl_token_list_print_debug if in DEBUG mode, 
// to print the entire list of tokens to the specified file. 
void o_output_handler(TokenList *list, const char *filename) {
        if (!list || !filename) return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp) return -1;

    // Here 
    Token *node = token_list_head(list);
    while (node) {
        Token *tok = token_node_get(node);
        if (tok) {
            write_token(fp, tok);
        }
        node = token_node_next(node);
    }

    fclose(fp);
    // return 0; I comment this because output_handler is void
}