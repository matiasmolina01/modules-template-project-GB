/*
 * -----------------------------------------------------------------------------
 * global_context.c 
 *
 * Usage:
 * Implement the global context that holds the main data structures for the parser,
 * coordinating the initialization of the Language definitions.
 *
 * Status:
 * Initial development — contains only the Language data structure for now.
 *
 * Author: [Franco Olano Melo]
 * -----------------------------------------------------------------------------
 */

#include "./global_context.h"
#define CAPACITY_STACK_H 100 // CAMBIAR SI HACE FALTAAAA

/* Allocates memory for a new GlobalContext and initializes its pointers to NULL. 
 * Returns a pointer to the newly created GlobalContext. */
GlobalContext* create_global_context(void) {
    GlobalContext* context = (GlobalContext*)malloc(sizeof(GlobalContext));
    if (context != NULL) {
        context->language = NULL;
        context->sra = NULL;
        context->tokenlist = NULL;
    }
    return context;
}

/* Initializes the GlobalContext by creating it and loading the language from the provided file path.
 * Returns a pointer to the fully populated GlobalContext. */
GlobalContext* init_global_context(const char* language_file_path) {
    if (language_file_path == NULL) {
        return NULL;
    }

    GlobalContext* context = create_global_context();
    if (context == NULL) {
        return NULL;
    }

    context->language = get_language(language_file_path);
    if (context->language == NULL) {
        destroy_global_context(context);
        return NULL;
    }    
    context->sra = (SRA*)malloc(sizeof(SRA));
    context->sra->automata = NULL;
    context->sra->stack = NULL;

    context->sra->automata = a_create_automata(context->language->num_symbols, context->language->num_states, context->language->action_table, context->language->symbols);
    context->sra->stack = create_stack(CAPACITY_STACK_H);
    stack_push(context->sra->stack, INITIAL_SYMBOL_ID, INITIAL_STATE);
    
    context->tokenlist = tl_token_list_init();

    return context;
}

/* Frees the memory associated with the GlobalContext and its internal structures.
 * Returns nothing. */
void destroy_global_context(GlobalContext* context) {
    if(context == NULL) return;
    if(context->tokenlist != NULL) {
        tl_token_list_destroy(context->tokenlist);
    }
    if(context->sra != NULL){
        if(context->sra->automata != NULL){
            a_destroy_automata(context->sra->automata);
        }
        if(context->sra->stack != NULL){
            destroy_stack(context->sra->stack);
        }
        free(context->sra);
    }
    
    if (context->language != NULL) {
        free_language(context->language); 
    }
    free(context);
}