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

/* Allocates memory for a new GlobalContext and initializes its pointers to NULL. 
 * Returns a pointer to the newly created GlobalContext. */
GlobalContext* create_global_context(void) {
    GlobalContext* context = (GlobalContext*)malloc(sizeof(GlobalContext));
    if (context != NULL) {
        context->language = NULL;
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

    return context;
}

/* Frees the memory associated with the GlobalContext and its internal structures.
 * Returns nothing. */
void destroy_global_context(GlobalContext* context) {
    if (context != NULL) {
        if (context->language != NULL) {
            free_language(context->language); 
        }
        free(context);
    }
}