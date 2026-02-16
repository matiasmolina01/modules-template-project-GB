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

char i_read_char(Input *input) {
    int c;

    if (input->input_file == NULL) {
        fprintf(stderr, "i_read_char: input file not opened\n");
        // TODO standarize error
        return -1;
    }

    input->column++;
    c = fgetc(input->input_file);

    if (c == EOF) {
        input->is_eof = IS_EOF;
        return NULL;   // indica EOF
    }

    if (c == '\n') {
        input->line_number++;
        input->column = 0;
    }

    return c;  // return del carácter 
}

void i_init(Input *input) {
	input->input_file = NULL;
    input->line_number = 0;
    input->is_eof = 0;
}

Input* i_create(void) {
    Input *input = (Input*) malloc(sizeof(Input));
    if (input == NULL) return NULL;
    i_init(input);
    return input;
}


int i_is_eof(Input *input) {
    return input->is_eof;
}

int i_open_input(Input *input, const char *path) {
	if(path == NULL || path[0] == '\0') { // invalid path
        fprintf(stderr, "ioh_open_input: invalid path\n");
        // TODO standarize error
        exit(1);
    } else {
		input->input_file = fopen(path, MODE_READ);
        if(input->input_file == NULL) { // error opening file
            fprintf(stderr, "ioh_open_input: could not open input file '%s'\n", path);
            // TODO standarize error
            exit(1);
        }
		return 1;
    }
    return 1;
}


int i_close_input(Input *input) {
    if(input->input_file != NULL) { // close file if opened
        fclose(input->input_file); // close file
        input->input_file = NULL; // reset pointer
    }
    input->line_number = 0; // reset line number
    input->is_eof = 0; // reset EOF status
    return 1;
}
