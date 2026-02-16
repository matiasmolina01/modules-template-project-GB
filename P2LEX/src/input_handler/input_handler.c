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

#ifdef COUNTCONFIG
    count_local_t __cnt_local_irc__;
    c_count_local_init(&__cnt_local_irc__);
    COUNTGEN(1, __cnt_local_irc__); /* read_char entry */
#endif

    if (input->input_file == NULL) {
		e_error_report(ERR_I_FILE_NOT_FOUND);
        return NULL;
    }

    input->column++;
    c = fgetc(input->input_file);

    if (c == EOF) {
        input->is_eof = IS_EOF;
#ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_irc__); /* EOF encountered */
#endif
        return NULL;   // indica EOF
    }

    if (c == '\n') {
        input->line_number++;
        input->column = 0;
    }

#ifdef COUNTCONFIG
    COUNTIO(1, __cnt_local_irc__); /* one char read */
#endif
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
#ifdef COUNTCONFIG
    count_local_t __cnt_local_ic__;
    c_count_local_init(&__cnt_local_ic__);
    COUNTGEN(1, __cnt_local_ic__); /* input create */
#endif
    return input;
}


int i_is_eof(Input *input) {
    return input->is_eof;
}

int i_open_input(Input *input, const char *path) {
	if(path == NULL || path[0] == '\0') { // invalid path
		e_error_report(ERR_I_FILE_NOT_FOUND);
        exit(1);
    } else {
		input->input_file = fopen(path, MODE_READ);
        if(input->input_file == NULL) { // error opening file
			e_error_report(ERR_I_INVALID_PATH);
            exit(1);
        }
#ifdef COUNTCONFIG
        count_local_t __cnt_local_open__;
        c_count_local_init(&__cnt_local_open__);
        COUNTIO(1, __cnt_local_open__); /* file opened */
        COUNTGEN(1, __cnt_local_open__);
#endif
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
#ifdef COUNTCONFIG
    count_local_t __cnt_local_close__;
    c_count_local_init(&__cnt_local_close__);
    COUNTIO(1, __cnt_local_close__); /* file close */
    COUNTGEN(1, __cnt_local_close__);
#endif
    return 1;
}
