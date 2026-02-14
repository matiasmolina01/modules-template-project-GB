/*
 * -----------------------------------------------------------------------------
 * input_handler.c 
 *
 * Usage:
 *     Called from the scanner module or test modules to handle input.
 *
 * Status:
 *     Initial development — logic to handle input is not yet implemented.
 *
 * Author: Marc Lounds
 * -----------------------------------------------------------------------------
 */

#include "./input_handler.h"

//Para leer carácter por carácter

char ioh_read_char(ioh_state_t *g_ioh) {
    int c;

    if (g_ioh->input_file == NULL) {
        fprintf(stderr, "ioh_read_char: input file not opened\n");
        return -1;
    }

    c = fgetc(g_ioh->input_file);

    if (c == EOF) {
        g_ioh->is_eof = true;
        return 0;   // indica EOF
    }

    if (c == '\n') {
        g_ioh->line_number++;
    }

    return c;  // return del carácter 
}