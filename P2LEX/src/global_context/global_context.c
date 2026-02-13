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
GlobalContext* i_init() {
    GlobalContext *global_context = (GlobalContext*) malloc(sizeof(GlobalContext));
    if(global_context == NULL) exit(0); // TODO Put standarized error

    TokenList *token_list = (TokenList*) malloc(sizeof(TokenList));
    if(global_context == NULL) exit(0); // TODO Put standarized error
    tl_token_list_init(token_list);


    return global_context;
}