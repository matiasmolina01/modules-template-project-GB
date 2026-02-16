/*
 * -----------------------------------------------------------------------------
 * test_module_input_handler.c
 *
 * Unit tests for module_input_handler.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_input_handler functionality test
 * 
 * Author: Martí Ponsa
 * Date: 16-02-2026
 * 
 * -----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tests/test_module_input_handler.h"

static void report(const char *name, int ok) {
    printf("%-36s : %s\n", name, ok ? "PASS" : "FAIL");
}


static void test_input_create_and_init(void) {
    Input *in = i_create();

    report("i_create returns non-NULL", in != NULL);
    if (in != NULL) {
        report("i_init sets input_file NULL", in->input_file == NULL);
        report("i_init sets line_number 0", in->line_number == 0);
        report("i_init sets is_eof 0", in->is_eof == 0);

        free(in);
    }
}


static void test_open_read_close(void) {
    const char *tmp = "test_input_handler.tmp";
    FILE *f = fopen(tmp, "w");
    if (f == NULL) {
        printf("Could not create temporary file for tests\n");
        return;
    }
    /* write content with a newline to exercise line counting */
    fprintf(f, "a\nb");
    fclose(f);

    Input *in = i_create();
    report("i_create for open test", in != NULL);
    if (in == NULL) return;

    int opened = i_open_input(in, tmp);
    report("i_open_input returns success", opened == 1);
    report("input_file set after open", in->input_file != NULL);

    /* Ensure column initialized for safe reads in tests */
    in->column = 0;

    int c1 = i_read_char(in);
    report("i_read_char returns first char 'a'", c1 == 'a');
    report("column incremented after first read", in->column == 1);

    int c2 = i_read_char(in);
    report("i_read_char returns newline char", c2 == '\n');
    report("line_number incremented after newline", in->line_number == 1);
    report("column reset after newline", in->column == 0);

    int c3 = i_read_char(in);
    report("i_read_char returns next char 'b'", c3 == 'b');

    int c4 = i_read_char(in); /* should be EOF (0) */
    report("i_read_char returns 0 at EOF", c4 == 0);
    report("i_is_eof returns true after EOF", i_is_eof(in) == 1);

    int closed = i_close_input(in);
    report("i_close_input returns success", closed == 1);
    report("input_file NULL after close", in->input_file == NULL);
    report("line_number reset after close", in->line_number == 0);
    report("is_eof reset after close", in->is_eof == 0);

    free(in);
    remove(tmp);
}


void test_input_handler_run_all(void) {
    printf("\nRunning input handler module tests...\n");

    test_input_create_and_init();
    test_open_read_close();

    printf("Finished input handler module tests.\n\n");
}


int main(void) {
    printf("\nStarting tests for Module input handler...\n");

    test_input_handler_run_all();

    printf("Finished tests for Module input handler...\n\n");
    return 0;
}
