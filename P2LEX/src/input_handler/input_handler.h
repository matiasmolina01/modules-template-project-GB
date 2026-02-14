#ifndef MODULE_INPUT_HANDLER_H
#define MODULE_INPUT_HANDLER_H

#include "../main.h"
#include <stdio.h>
#include <stdbool.h>


typedef struct {
    FILE *input_file;   // fichero de entrada
    bool  is_eof;       // flag de fin de fichero
    int   line_number;  // número de línea actual
} ioh_state_t;

char ioh_read_char(ioh_state_t *g_ioh);

#endif