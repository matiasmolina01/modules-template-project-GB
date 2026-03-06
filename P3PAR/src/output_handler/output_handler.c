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


// const char *symbol_to_string(SymbolCategory s) {
//     switch (s) {
//         case CAT_NUMBER: return "NUM";
//         case CAT_PLUS:   return "+";
//         case CAT_EOF:    return "$";
//         case CAT_MULT:   return "*";
//         case CAT_OPEN_PARENTHESIS: return "(";
//         case CAT_CLOSE_PARENTHESIS: return ")";
//         case CAT_S: return "s";
//         case CAT_E: return "e";
//         case CAT_T: return "t";
//         case CAT_F: return "f";
//     }
// }

const char *symbol_to_string(Language *language, int symbol_id){ // te cambio la firma por Language* language
    for(int i = 0; i < language->num_symbols; i++){  // por lo tanto usamos language->num_symbols
        if(language->symbols[i]->id == symbol_id){
            return language->symbols[i]->name;
        }
    }
    return NULL;
}

void stack_instance_to_string(const Stack *stack, char* string, Language *language){
    int pos = 0;
    for(int i= 0; i< stack->top; i++){ // te cambio size por top
        pos += snprintf(string+pos, MAX_LEN-pos, "(%s, %d) ", symbol_to_string(language, stack->stack_list[i].symbol_id), stack->stack_list[i].state );
        if(pos >= MAX_LEN) break;
    }
}

FILE *o_open_output_file(const char *input_filename) {
    char output_filename[512];

    generate_timestamped_log_filename(input_filename, output_filename, sizeof(output_filename));

    FILE *fp = fopen(output_filename, "w");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    return fp;
}


char *input_process(int index, TokenList *token_list, char *input){
     if (token_list == NULL || input == NULL || index < 0) {
        return NULL;
    }
    TokenNode *current = token_list->head;
    int i = 0;
    int pos = 0;

     /* Concatenar los lexemas desde index hasta el final */
    while (current != NULL && pos < MAX_LEN - 1) {
        if(i == index){
            input[pos++] = '.';
            
        }
        for (size_t j = 0; j < current->token.length && pos < MAX_LEN - 1; j++) {
            input[pos++] = current->token.lexeme[j];
        }

        current = current->next;
        i++;
    }

    input[pos] = '\0';
    return input;

}

int o_output_handler(FILE* fp, int index, const Stack *stack, const char *operation, const char *input_filename, const int state, Language *language, TokenList *token_list) {
   

    char buffer[MAX_LEN];
    char input[MAX_LEN];
    
    stack_instance_to_string(stack, buffer, language);
    // Printing the operations
    // stack_string = o_stack_to_string(stack);

    // We need to go though tokenList from index to the end to get remaining input left

    input_process(index, token_list, input);

    char input_left[MAX_LEN] = "temporal"; // te pongo esto temporal para que lo veas
    fprintf(fp,  "STATE %d | OPERATIONS %s | STACK %s| INPUT %s", state, operation, buffer, input);

    // fclose(fp); ----------- esto deberia cerrarlo el main.

    return 0;

}