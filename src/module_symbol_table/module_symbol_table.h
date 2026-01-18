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


int test_symbol_table_module(int n);

/* Lifecycle */
void st_init(void);
void st_destroy(void);
int st_is_initialized(void);

/* Macro definition */
int st_define(const char *name, const char *value);

/* Query */
const char *st_get(const char *name);
int st_exists(const char *name);

/* Debug */
void st_print_all(void);

/* Validation */
int st_is_valid_name(const char *name);


#endif