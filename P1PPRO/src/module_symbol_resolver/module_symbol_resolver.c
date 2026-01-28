#include "./module_symbol_resolver.h"

//Implementation of the symbol resolver module

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


const char* sr_substitute(char *word, ReplaceFlags *flags, MacroTable *table){
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