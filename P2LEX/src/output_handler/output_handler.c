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

void o_output_handler(TokenList *list, const char *filename) {
        if (!list || !filename) return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp) return -1;

    Token *node = token_list_head(list);
    while (node) {
        Token *tok = token_node_get(node);
        if (tok) {
                #if OUTFORMAT == RELEASE
                    t_token_print_release(fp, tok);
                #else
                    t_token_print_debug(fp, tok);
                #endif
                    }
        node = token_node_next(node);
    }

    fclose(fp);
}