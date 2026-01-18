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

#define ST_TABLE_SIZE 1024

typedef struct{
    char *name;
    char *value;
    int in_use; // 0 = free, 1 = used, so we can handle deletions
} MacroEntry;

typedef struct{
    MacroEntry *entries; 
    size_t size;  
} MacroTable;

static MacroTable macro_table; // dictionary instance
static int st_initialized = 0;  


/*
    Initializes the macro table.
*/

void st_init(void){
    if (st_is_initialized()) return;

    macro_table.size = ST_TABLE_SIZE;
    macro_table.entries = calloc(macro_table.size, sizeof(MacroEntry));

    if (macro_table.entries == NULL) {
        printf("Symbol table initialization failed: out of memory.\n");
        st_initialized = 0;
        return;
    }

    st_initialized = 1;
}


/*
    Destroys the macro table.
*/

void st_destroy(void){
    if (!st_is_initialized()) return;

    for (size_t i = 0; i < macro_table.size; i++) {
        if (macro_table.entries[i].in_use) {
            free(macro_table.entries[i].name);
            free(macro_table.entries[i].value);
        }
    }

    free(macro_table.entries);
    macro_table.entries = NULL;
    macro_table.size = 0;

    st_initialized = 0;
}


/*
    Function used by Classifier module to define a new macro in the symbol table.

    If value is NULL, the macro is defined with NULL value.

    Returns 0 on success, other error numbers on different errors (defined as MACROS).
*/

int st_define(const char *name, const char *value) {
    
    if (!st_is_initialized()) return ST_ERR_NOT_INIT;
    if (name == NULL) return ST_ERR_NULL_NAME;
    if (!st_is_valid_name(name)) return ST_ERR_INVALID_NAME;

    size_t free_idx = SIZE_MAX;

    /* Search for existing entry or first free slot */
    for (size_t i = 0; i < macro_table.size; i++) {
        MacroEntry *e = &macro_table.entries[i];

        if (e->in_use) {
            if (strcmp(e->name, name) == 0) {
                /* Update existing */
                free(e->value);
                e->value = NULL;

                if (value) {
                    e->value = malloc(strlen(value) + 1);
                    if (!e->value) return ST_ERR_NO_MEMORY;
                    strcpy(e->value, value);
                }
                return ST_OK;
            }
        } 
        else if (free_idx == SIZE_MAX) {
            free_idx = i;
        }
    }

    /* No free slot: grow dictionary */
    if (free_idx == SIZE_MAX) {
        size_t new_size = macro_table.size * 2;
        MacroEntry *new_entries =
            realloc(macro_table.entries, new_size * sizeof(MacroEntry));

        if (!new_entries) return ST_ERR_NO_MEMORY;

        for (size_t i = macro_table.size; i < new_size; i++) {
            new_entries[i].name = NULL;
            new_entries[i].value = NULL;
            new_entries[i].in_use = 0;
        }

        free_idx = macro_table.size;
        macro_table.entries = new_entries;
        macro_table.size = new_size;
    }

    /* Insert new entry */
    MacroEntry *slot = &macro_table.entries[free_idx];

    slot->name = malloc(strlen(name) + 1);
    if (!slot->name) return ST_ERR_NO_MEMORY;
    strcpy(slot->name, name);

    slot->value = NULL;
    if (value) {
        slot->value = malloc(strlen(value) + 1);
        if (!slot->value) {
            free(slot->name);
            slot->name = NULL;
            return ST_ERR_NO_MEMORY;
        }
        strcpy(slot->value, value);
    }

    slot->in_use = 1;
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
    if (!st_is_initialized()/*something*/) {
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
