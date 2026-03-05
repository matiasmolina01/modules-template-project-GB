#ifndef MODULE_INPUT_HANDLER_H
#define MODULE_INPUT_HANDLER_H

#include "../main.h"
#include <stdio.h>



#define MODE_READ "r"
#define IS_EOF 1
#define NO_EOF 0
#define  MAX_LEN 100

typedef struct GlobalContext GlobalContext;

typedef struct Input {
    FILE *input_file;   
    int is_eof;
 
} Input;


void i_read_elements_from_file(Input *input, GlobalContext *global_context);

void i_init(Input *input);

Input* i_create(void);

int i_is_eof(Input *input) ;


int i_open_input(Input *input, const char *path);

int i_close_input(Input *input) ;

#endif