/*
 * -----------------------------------------------------------------------------
 * init.c 
 *
 * Usage:
 *     Called from the main file or test modules to manipulate the datastructures on the GlobalContext.
 *
 * Status:
 *     Initial development — logic to handle init is not yet implemented.
 *
 * Author: [Franco Olano]
 * -----------------------------------------------------------------------------
 */

#include "./global_context.h"


void  gc_init_automatas(Automata* automata_list[]){

    // TODO define automatas using macros delared in language.h
    //TODO automata_list[OPERATOR_AUTOMATA] = a_create_automata(...)
    //TODO automata_list[SPECIAL_CHAR_AUTOMATA] = a_create_automata(...)
    //TODO automata_list[NUMBERS_AUTOMATA] = a_create_automata(...)
    //TODO automata_list[KEYWORDS_AUTOMATA] = a_create_automata(...)
    //TODO automata_list[LITERALS_AUTOMATA] = a_create_automata(...)
    //TODO automata_list[IDENTIFIERS_AUTOMATA] = a_create_automata(...)

}

/*
    Initilizes the GlobalContext datastructure.
    Returns GlobalContext pointer.
*/
GlobalContext* gc_init(Arguments* arguments) {
    GlobalContext *global_context = (GlobalContext*) malloc(sizeof(GlobalContext));
    if(global_context == NULL) exit(0); // TODO Put standarized error

    global_context->arguments = arguments;

    TokenList *token_list = tl_token_list_init();

    global_context->token_list = token_list;

    Automata* automatas_list[NUM_AUTOMATAS] = {};
    //gc_init_automatas(automatas_list);

    Input* input = i_create();

    global_context->input = input;

    i_open_input(global_context->input, arguments->input_path);
    
    return global_context;
}

void gc_destroy(GlobalContext* global_context){
    //TODO fix
	i_close_input(global_context->input);
    free(global_context->token_list);
    args_free(global_context->arguments);
    free(global_context);
}