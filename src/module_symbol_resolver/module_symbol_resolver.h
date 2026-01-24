#ifndef MODULE_SYMBOL_RESOLVER_H
#define MODULE_SYMBOL_RESOLVER_H

#include "../main.h"

typedef struct ReplaceFlags{
    int inString;
} ReplaceFlags;

typedef struct MacroTable MacroTable;

void sr_init_ReplaceFlags(ReplaceFlags *flags);
char* sr_substitute(char *word, ReplaceFlags *flags, MacroTable *table);
void flag_activate(char * input_line, ReplaceFlags* flags);

#endif