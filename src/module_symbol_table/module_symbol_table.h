#ifndef MODULE_SYMBOL_TABLE_H
#define MODULE_SYMBOL_TABLE_H

#include "../main.h"

// Error codes for symbol table operations
#define ST_OK                 0
#define ST_ERR_NULL_NAME     -1
#define ST_ERR_INVALID_NAME  -2
#define ST_ERR_ALREADY_DEF   -3
#define ST_ERR_NOT_FOUND     -4
#define ST_ERR_NO_MEMORY     -5
#define ST_ERR_NOT_INIT      -6
#define ST_ERR_INVALID_VALUE -7

// Macro entry structure
typedef struct{
    char *name;
    char *value;
    int in_use; // 0 = free, 1 = used, so we can handle deletions
} MacroEntry;

// Macro table structure
typedef struct MacroTable{
    MacroEntry *entries; 
    size_t size;  
} MacroTable;

/* Lifecycle */
MacroTable *st_init(void);
void st_destroy(MacroTable *table);
int st_is_initialized(MacroTable *table);

/* Macro definition */
int st_define(MacroTable *table, const char *name, const char *value);

/* Query */
const char *st_get(MacroTable *table, const char *name);
int st_exists(MacroTable *table, const char *name);

/* Debug */
void st_print_all(MacroTable *table);

/* Validation */
int st_is_valid_name(const char *name);
int st_is_valid_value(const char *value);

#endif