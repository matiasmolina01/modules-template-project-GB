#ifndef MODULE_INPUT_HANDLER_H
#define MODULE_INPUT_HANDLER_H

#include "../main.h"
#include <stdio.h>

#define MODE_READ "r"
#define IS_EOF 1
#define NO_EOF 0

typedef struct Input {
    FILE *input_file;   
    int is_eof;
    int line_number;
    int column;
} Input;

char i_read_char(Input *input);
Input* i_create();
void i_init(Input *input);
int i_is_eof(Input *input);
int i_open_input(Input *input, const char *path);
int i_close_input(Input *input);

#endif