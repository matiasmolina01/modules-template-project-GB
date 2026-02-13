/*
 * -----------------------------------------------------------------------------
 * test_module_token_handler.c
 *
 * Unit tests for module_token_handler.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_token_handler functionality test
 * 
 * Author: Martí Ponsa
 * Date: 13-02-2026
 * 
 * -----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <string.h>
#include "../tests/test_module_token_handler.h"

static void report(const char *name, int ok) {
    printf("%-36s : %s\n", name, ok ? "PASS" : "FAIL");
}


static void test_token_create_destroy(void) {
    Token t = t_token_create(3, 5);

    report("t_token_create sets line", t.line == 3);
    report("t_token_create sets column", t.column == 5);
    report("t_token_create empty length", t.length == 0);
    report("t_token_create default category",
           t.category == CAT_NONRECOGNIZED);

    t_token_destroy(&t);
}


static void test_token_append_and_category(void) {
    Token t = t_token_create(1, 1);

    t_token_append_char(&t, 'a');
    t_token_append_char(&t, 'b');
    t_token_append_char(&t, 'c');

    report("t_token_append_char builds lexeme",
           t.length == 3 && strcmp(t.lexeme, "abc") == 0);

    t_token_update_category(&t, CAT_IDENTIFIER);

    report("t_token_update_category works",
           t.category == CAT_IDENTIFIER);

    t_token_destroy(&t);
}


static void test_token_list_init_size_destroy(void) {
    TokenList list;
    tl_token_list_init(&list);

    report("tl_token_list_init sets size 0",
           tl_token_list_size(&list) == 0);

    tl_token_list_destroy(&list);

    report("tl_token_list_destroy clears list",
           tl_token_list_size(&list) == 0);
}


static void test_token_list_add(void) {
    TokenList list;
    tl_token_list_init(&list);

    Token t1 = t_token_create(1, 1);
    t_token_append_char(&t1, 'x');

    tl_token_list_add(&list, t1);

    report("tl_token_list_add increases size",
           tl_token_list_size(&list) == 1);

    tl_token_list_destroy(&list);
}


static void test_token_update_and_append(void) {
    TokenList list;
    tl_token_list_init(&list);

    Token t = t_token_create(2, 4);
    t_token_append_char(&t, 'y');

    tl_token_update_and_append(&list, &t, CAT_IDENTIFIER);

    report("tl_token_update_and_append size",
           tl_token_list_size(&list) == 1);

    report("tl_token_update_and_append category",
           list.head != NULL &&
           list.head->token.category == CAT_IDENTIFIER);

    tl_token_list_destroy(&list);
}


// Output tests: token print modes
static void test_token_print_release(void) {
    Token t = t_token_create(1, 1);
    t_token_append_char(&t, 'a');
    t_token_update_category(&t, CAT_IDENTIFIER);

    printf("\n-- RELEASE token print --\n");
    t_token_print_release(stdout, &t);
    printf("\n-- end RELEASE token print --\n\n");

    report("t_token_print_release executed", 1);

    t_token_destroy(&t);
}


static void test_token_print_debug(void) {
    Token t = t_token_create(10, 20);
    t_token_append_char(&t, 'b');
    t_token_update_category(&t, CAT_NUMBER);

    printf("\n-- DEBUG token print --\n");
    t_token_print_debug(stdout, &t);
    printf("\n-- end DEBUG token print --\n\n");

    report("t_token_print_debug executed", 1);

    t_token_destroy(&t);
}


static void test_token_list_print_modes(void) {
    TokenList list;
    tl_token_list_init(&list);

    Token t1 = t_token_create(1, 1);
    t_token_append_char(&t1, 'x');
    t_token_update_category(&t1, CAT_IDENTIFIER);
    tl_token_list_add(&list, t1);

    Token t2 = t_token_create(1, 3);
    t_token_append_char(&t2, '7');
    t_token_update_category(&t2, CAT_NUMBER);
    tl_token_list_add(&list, t2);


    printf("\n-- RELEASE token list print --\n");
    tl_token_list_print_release(stdout, &list);
    printf("\n-- end RELEASE token list print --\n\n");

    printf("\n-- DEBUG token list print --\n");
    tl_token_list_print_debug(stdout, &list);
    printf("\n-- end DEBUG token list print --\n\n");

    report("tl_token_list_print modes executed", 1);

    tl_token_list_destroy(&list);
}

void test_token_run_all(void) {
    printf("\nRunning token handler module tests...\n");

    test_token_create_destroy();
    test_token_append_and_category();
    test_token_list_init_size_destroy();
    test_token_list_add();
    test_token_update_and_append();

    test_token_print_release();
    test_token_print_debug();
    test_token_list_print_modes();

    printf("Finished token handler module tests.\n\n");
}


int main(void) {
    printf("\nStarting tests for Module token handler...\n");

    test_token_run_all();

    printf("Finished tests for Module token handler...\n\n");
    return 0;
}
