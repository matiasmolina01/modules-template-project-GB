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



/*
    Initializes the macro table.
*/

MacroTable *st_init(void){
    MacroTable *table = malloc(sizeof(MacroTable));
    if (!table) return NULL;

    table->size = ST_TABLE_SIZE;
    table->entries = calloc(table->size, sizeof(MacroEntry));
    if (table->entries == NULL) {
        printf("Symbol table initialization failed: out of memory.\n");
        free(table);
        return NULL;
    }

    return table;
}


/*
    Destroys the macro table.
*/

void st_destroy(MacroTable *table){
    if (table == NULL) return;

    for (size_t i = 0; i < table->size; i++) {
        if (table->entries[i].in_use) {
            free(table->entries[i].name);
            free(table->entries[i].value);
        }
    }

    free(table->entries);
    table->entries = NULL;
    table->size = 0;

    free(table);
}


/*
    Function used by Classifier module to define a new macro in the symbol table.

    If value is NULL, the macro is defined with NULL value.

    Returns 0 on success, other error numbers on different errors (defined as MACROS).
*/

int st_define(MacroTable *table, const char *name, const char *value) {
    if (table == NULL) return ST_ERR_NOT_INIT;
    if (name == NULL) return ST_ERR_NULL_NAME;
    if (!st_is_valid_name(name)) return ST_ERR_INVALID_NAME;

    size_t free_idx = SIZE_MAX;

    /* Search for existing entry or first free slot */
    for (size_t i = 0; i < table->size; i++) {
        MacroEntry *e = &table->entries[i];

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
        size_t new_size = table->size * 2;
        MacroEntry *new_entries =
            realloc(table->entries, new_size * sizeof(MacroEntry));

        if (!new_entries) return ST_ERR_NO_MEMORY;

        for (size_t i = table->size; i < new_size; i++) {
            new_entries[i].name = NULL;
            new_entries[i].value = NULL;
            new_entries[i].in_use = 0;
        }

        free_idx = table->size;
        table->entries = new_entries;
        table->size = new_size;
    }

    /* Insert new entry */
    MacroEntry *slot = &table->entries[free_idx];

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

const char *st_get(MacroTable *table, const char *name){
    if (table == NULL) return NULL;
    if (name == NULL) return NULL;

    for (size_t i = 0; i < table->size; i++) {
        MacroEntry *e = &table->entries[i];
        if (e->in_use && e->name != NULL && strcmp(e->name, name) == 0) {
            return e->value; /* may be NULL if macro defined without value */
        }
    }
    return NULL;
}


/*
    Function used by Symbol Resolver and Recursivity Handler module to check if a macro exists in the table.

    It will return 1 if the macro exists, or 0 otherwise.
*/

int st_exists(MacroTable *table, const char *name){
    if (table == NULL) return 0;
    if (name == NULL) return 0;

    for (size_t i = 0; i < table->size; i++) {
        MacroEntry *e = &table->entries[i];
        if (e->in_use && e->name != NULL && strcmp(e->name, name) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
    Function used to print all macros in the symbol table for debugging purposes.
*/

void st_print_all(MacroTable *table){
    if (table == NULL) {
        printf("Symbol table not initialized.\n");
        return;
    }

    printf("Symbol table contents (size=%zu):\n", table->size);
    for (size_t i = 0; i < table->size; i++) {
        MacroEntry *e = &table->entries[i];
        if (e->in_use) {
            printf(" - [%zu] name='%s' value='%s'\n",
                   i,
                   e->name ? e->name : "(null)",
                   e->value ? e->value : "(null)");
        }
    }
}


/*
    Function to check if the symbol table has been initialized.

    It will return 1 if initialized, or 0 otherwise.
*/

int st_is_initialized(MacroTable *table){
    return (table != NULL && table->entries != NULL) ? 1 : 0;
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