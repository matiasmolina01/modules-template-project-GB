/*
 * -----------------------------------------------------------------------------
 * module_symbol_table.c 
 *
 * Usage:
 *     Called from the main application or test modules to process symbol table.
 *
 * Status:
 *     Initial development — logic to handle symbol table is not yet implemented.
 *
 * Author: [Martí Ponsa]
 * -----------------------------------------------------------------------------
 */

#include "./module_symbol_table.h"

static int st_initialized = 0;


/*
    Initializes the macro table.
*/

void st_init(void){
    st_initialized = 1;
    printf(" - Function: st_init Not implemented.");
}


/*
    Destroys the macro table.
*/

void st_destroy(void){
    st_initialized = 0;
    printf(" - Function: st_destroy Not implemented.");
}


/*
    Function used by Classifier module to define a new macro in the symbol table.

    If value is NULL, the macro is defined with NULL value.

    Returns 0 on success, other error numbers on different errors (defined as MACROS).
*/

int st_define(const char *name, const char *value){
    
    // Validate initialization and name
    if (!st_is_initialized()) return ST_ERR_NOT_INIT;
    if (name == NULL) return ST_ERR_NULL_NAME;
    if (!st_is_valid_name(name)) return ST_ERR_INVALID_NAME;

    printf(" - Function: st_define Not implemented.\n");
    return ST_OK;
}



/*  
    Function used by Symbol Resolver module to get the value of a macro.

    It will return a pointer to the macro value string if found, or NULL if the macro does not exist.
*/

const char *st_get(const char *name){
    if (!st_is_initialized()) return NULL;
    if (name == NULL) return NULL;

    printf(" - Function: st_get Not implemented.\n");
    return NULL;
}


/*
    Function used by Symbol Resolver and Recursivity Handler module to check if a macro exists in the table.

    It will return 1 if the macro exists, or 0 otherwise.
*/

int st_exists(const char *name){
    if (!st_is_initialized()) return 0;
    if (name == NULL) return 0;

    printf(" - Function: st_exists Not implemented.\n");
    return 0;
}


/*
    Function used to print all macros in the symbol table for debugging purposes.
*/

void st_print_all(void){
    if (!st_is_initialized()) {
        printf("Symbol table not initialized.\n");
        return;
    }
    printf(" - Function: st_print_all Not implemented.\n");
}


/*
    Function to check if the symbol table has been initialized.

    It will return 1 if initialized, or 0 otherwise.
*/

int st_is_initialized(void){
    return st_initialized;

}


/*
    Function to validate if a macro name is valid according to the naming rules.

    It will return 1 if valid, or 0 otherwise.
*/

int st_is_valid_name(const char *name){
    if (name == NULL || *name == '\0') return 0;
    /* Later: check first char is letter or _, others alnum or _ */
    return 1;

}


/*
    Symbol table main function.
    Handles the symbol table operations.

    Parameters:

    Returns: 
*/

int symbol_table(int n) {
    printf("Symbol Table module, still to be implemented\n");
    return ST_OK;
}
