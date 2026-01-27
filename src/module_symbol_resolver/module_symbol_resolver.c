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
   
    flags->inString = 0;
}




void sr_flag_activate(char input_char, ReplaceFlags* flags) {
    if(input_char == '"'){
        switch(flags->inString){
            case 1:
            flags->inString = 0;
            break;
            
            case 0:
            flags->inString = 1;
            break;
        }
    }
    return;
}


char* sr_substitute(char *word, ReplaceFlags *flags, MacroTable *table){
    if(flags->inString ==1){
        return word;
    }
    else{
        const char *value = st_get(table, word);
        if(value==NULL){
            return word;
        }
        else{
        
            return value;

        }
    }
}