#ifndef MODULE_SYMBOL_RESOLVER_H
#define MODULE_SYMBOL_RESOLVER_H

#include "../main.h"

typedef struct{
    int inPrint;
    int inString;
}replaceFlags;

typedef struct MacroTable MacroTable;

void sr_init_replaceFlags(replaceFlags *flags);
char* sr_substitute(char *word, replaceFlags *flags, MacroTable *table);

#endif