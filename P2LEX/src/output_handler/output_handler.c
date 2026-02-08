/*
 * -----------------------------------------------------------------------------
 * output_handler.c 
 *
 * Usage:
 *     Called from the controller module or test modules to handle output.
 *
 * Status:
 *     Initial development — logic to handle output is not yet implemented.
 *
 * Author: Anna Vasileva
 * -----------------------------------------------------------------------------
 */

#include "./output_handler.h"

static void write_token(FILE *fp, Token *tok) {
#if OUTFORMAT == RELEASE
    fprintf(fp, "%s\n", tok->lexeme);
#else
    fprintf(fp,
        "LEXEME: %-15s | CATEGORY: %-10s | LINE: %d | COL: %d\n",
        tok->lexeme,
        token_category_to_string(tok->category),
        tok->line,
        tok->column
    );
#endif
}

void o_output_handler(TokenList *list, const char *filename) {
        if (!list || !filename) return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp) return -1;

    Token *node = token_list_head(list);
    while (node) {
        Token *tok = token_node_get(node);
        if (tok) {
            write_token(fp, tok);
        }
        node = token_node_next(node);
    }

    fclose(fp);
    return 0;
}