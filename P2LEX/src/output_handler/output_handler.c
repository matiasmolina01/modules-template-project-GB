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

static void build_output_filename(const char *input, char *out, size_t size) {
    snprintf(out, size, "%sscn", input);
}

int o_output_handler(const TokenList *list, const char *input_filename) {
        if (!list || !input_filename) return -1;

    char output_filename[512];
    build_output_filename(input_filename, output_filename, sizeof(output_filename));

    FILE *fp = fopen(output_filename, "w");
    if (!fp) return -1;

    #if OUTFORMAT == RELEASE
        tl_token_list_print_release(fp, list);
    #else
        tl_token_list_print_debug(fp, list);
    #endif

    fclose(fp);
    return 0;
}