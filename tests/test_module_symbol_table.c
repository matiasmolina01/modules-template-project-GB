/*
 * -----------------------------------------------------------------------------
 * test_module_symbol_table.c
 *
 * Unit tests for module_symbol_table.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_symbol_table functionality test
 * 
 * Author: Martí Ponsa
 * Date: 18-01-2026
 * 
 * -----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <string.h>
#include "../tests/test_module_symbol_table.h"

static void report(const char *name, int ok) {
    printf("%-36s : %s\n", name, ok ? "PASS" : "FAIL");
}

static void test_st_init_destroy(void) {
    MacroTable *t = st_init();
    report("st_init sets initialized", st_is_initialized(t));
    st_destroy(t);
    t = NULL; /* avoid checking a freed pointer */
    report("st_destroy clears initialized", !st_is_initialized(t));
}

static void test_st_define_and_get(void) {
    int rc;
    MacroTable *t = st_init();

    rc = st_define(t, "T_DEF", "v1");
    report("st_define returns ST_OK", rc == ST_OK);

    const char *v = st_get(t, "T_DEF");
    report("st_get returns correct value", v != NULL && strcmp(v, "v1") == 0);

    /* Update existing */
    rc = st_define(t, "T_DEF", "v2");
    report("st_define updates existing entry", rc == ST_OK && strcmp(st_get(t, "T_DEF"), "v2") == 0);

    /* Define with NULL value */
    rc = st_define(t, "T_NULL", NULL);
    report("st_define allows NULL value", rc == ST_OK && st_exists(t, "T_NULL") );

    st_destroy(t);
}

static void test_st_exists(void) {
    MacroTable *t = st_init();
    st_define(t, "EX1", "1");
    report("st_exists finds existing macro", st_exists(t, "EX1") == 1);
    report("st_exists returns 0 for missing macro", st_exists(t, "MISSING") == 0);
    st_destroy(t);
}

static void test_st_invalid_name(void) {
    int rc;
    MacroTable *t = st_init();

    rc = st_define(t, NULL, "v");
    report("st_define rejects NULL name", rc == ST_ERR_NULL_NAME);

    /* Maybe in a future we don't want a define that starts with a digit */
    // rc = st_define("1bad", "v");
    // report("st_define rejects invalid name (1bad)", rc == ST_ERR_INVALID_NAME);

    /* empty name */
    rc = st_define(t, "", "v");
    report("st_define rejects empty name", rc == ST_ERR_INVALID_NAME);

    st_destroy(t);
}

static void test_st_print_all(void) {
    MacroTable *t = st_init();
    st_define(t, "P1", "one");
    st_define(t, "P2", NULL);
    printf("\n-- st_print_all output --\n");
    st_print_all(t);
    printf("-- end st_print_all output --\n\n");
    st_destroy(t);
}

void test_symbol_table_run_all(void) {
    printf("\nRunning symbol table tests...\n");
    test_st_init_destroy();
    test_st_define_and_get();
    test_st_exists();
    test_st_invalid_name();
    test_st_print_all();
    printf("Finished symbol table tests.\n\n");
}

int main(void) {
    printf("\nStarting tests for Module symbol table...\n");
    test_symbol_table_run_all();
    printf("Finished tests for Module symbol table...\n\n");
    return 0;
}