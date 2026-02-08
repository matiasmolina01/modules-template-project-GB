#ifndef MODULE_OUTPUT_HANDLER_H
#define MODULE_OUTPUT_HANDLER_H

#include "../main.h"

#define RELEASE 0
#define DEBUG 1
// Usage: gcc -DOUTFORMAT=DEBUG or gcc -DOUTFORMAT=RELEASE

#ifndef OUTFORMAT
#define OUTFORMAT RELEASE
#endif

void o_output_handler(TokenList *list, const char *filename);

#endif