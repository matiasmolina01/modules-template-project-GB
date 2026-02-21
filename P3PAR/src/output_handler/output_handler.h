#ifndef MODULE_OUTPUT_HANDLER_H
#define MODULE_OUTPUT_HANDLER_H

#include <stdio.h>
#include "../main.h"

#define RELEASE 0
#define DEBUG 1

#ifndef OUTFORMAT
#define OUTFORMAT RELEASE
#endif

typedef struct TokenList TokenList;

int o_output_handler(const TokenList *list, const char *input_filename);

#endif