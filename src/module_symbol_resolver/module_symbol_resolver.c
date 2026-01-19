/*
 * -----------------------------------------------------------------------------
 * module_symbol_resolver.c 
 *
 * Usage:
 *     Called from the main application or test modules to process symbol resolver.
 *
 * Status:
 *     Initial development — logic to handle symbol resolver is not yet implemented.
 *
 * Author: [Marc Lounds]
 * -----------------------------------------------------------------------------
 */

#include "./module_symbol_resolver.h"



void sr_init_ReplaceFlags(ReplaceFlags *flags){
    //We initialize as false because as default the word in file won't be inside a print or a string.
    flags->inPrint = 0;
    flags->inString = 0;
}

char* sr_substitute(char *word, ReplaceFlags *flags, MacroTable *table){
    if(flags->inPrint ==1 || flags->inString ==1){
        return word;
    }
    else{
        const char *value = st_get(table, word);
        if(value==NULL){
            return word;
        }
        else{
        
            return word;

        }
    }
}