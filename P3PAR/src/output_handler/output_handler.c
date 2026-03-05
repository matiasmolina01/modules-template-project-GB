/*
 * -----------------------------------------------------------------------------
 * output_handler.c 
 *
 * Usage:
 *     Called from the scanner module or test modules to handle output.
 *
 * Status:
 *     Initial development — logic to handle output is not yet implemented.
 *
 * Author: Marc Lounds
 * -----------------------------------------------------------------------------
 */

#include "./output_handler.h"

// char* stack_string(const Stack *stack){

// }


const char *symbol_to_string(TokenCategory s) {
    switch (s) {
        case CAT_NUMBER: return "NUM";
        case CAT_PLUS:   return "+";
        case CAT_EOF:    return "$";
        case CAT_MULT:   return "*";
        case CAT_OPEN_PARENTHESIS: return "(";
        case CAT_CLOSE_PARENTHESIS: return ")";
        case CAT_S: return "s";
        case CAT_E: return "e";
        case CAT_T: return "t";
        case CAT_F: return "f";
    }
}


void stack_instance_to_string( Stack *stack, char* string){
    for(int i= 0; i< stack->size; i++){
        pos += snprintf(string+pos, MAX_LEN-pos, "{%s, %d}", symbol_to_string(stack->stacklist[i].symbol_id), stack->stacklist[i].state );

        if(pos >= MAX_LEN) break;
        
        
        

    }
}

FILE *o_open_output_file(const char *input_filename) {
    char output_filename[512];

    build_output_filename(input_filename, output_filename, sizeof(output_filename));

    FILE *fp = fopen(output_filename, "w");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    return fp;
}


int o_output_handler(const Token *lookahead, const Stack *stack, cost char *operation, const char *input_filename, const int state) {
   

    char buffer[MAX_LEN];

    stack_instance_to_string(stack, buffer);
    //Printing the operations
    // stack_string = o_stack_to_string(stack);
    fprintf("STATE %d | OPERATIONS %s | STACK %s| INPUT %s", state, operation, buffer, input_left);

    fclose(fp);

    return 0;

}