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


/*
    Initilizes the GlobalContext datastructure.
    Returns GlobalContext pointer.
*/
GlobalContext* gc_init(char input_file_path) {
    GlobalContext *global_context = (GlobalContext*) malloc(sizeof(GlobalContext));
    if(global_context == NULL) exit(0); // TODO Put standarized error

    TokenList *token_list = tl_token_list_init();

    global_context->token_list = token_list;

    // TODO initiate atomatas

    Input* input = i_create();

    global_context->input = input;

    i_open_input(global_context->input, input_file_path);
    
    return global_context;
}

int gc_destroy(GlobalContext* global_context){
    i_close_input(global_context->input);
    free(global_context->token_list);
    free(global_context);
    return 0;
}