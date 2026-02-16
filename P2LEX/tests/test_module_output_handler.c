/*
 * -----------------------------------------------------------------------------
 * test_module_output_handler.c
 *
 * Unit tests for module_output_handler.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_output_handler functionality test
 * 
 * Author: Martí Ponsa
 * Date: 16-02-2026
 * 
 * -----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <string.h>
#include "../tests/test_module_output_handler.h"

static void report(const char *name, int ok) {
    printf("%-48s : %s\n", name, ok ? "PASS" : "FAIL");
}

static void test_null_parameters(void) {
    TokenList *list = tl_token_list_init();

    int r1 = o_output_handler(NULL, "infile");
    report("o_output_handler NULL list returns -1", r1 == -1);

    int r2 = o_output_handler(list, NULL);
    report("o_output_handler NULL filename returns -1", r2 == -1);

    tl_token_list_destroy(list);
}

static void test_build_filename_and_write(void) {
    const char *infile = "test_output_handler.tmp";
    char outname[512];
    snprintf(outname, sizeof(outname), "%sscn", infile);

    printf("Input filename: '%s' -> Expected output filename: '%s'\n", infile, outname);

    /* prepare a token list with one token */
    TokenList *list = tl_token_list_init();
    Token t = t_token_create(1, 1);
    t_token_append_char(&t, 'z');
    t_token_update_category(&t, CAT_IDENTIFIER);
    tl_token_list_add(list, t);

    /* ensure no leftover file */
    remove(outname);

    int r = o_output_handler(list, infile);
    report("o_output_handler returns 0 on success", r == 0);

    FILE *f = fopen(outname, "r");
    report("output file created", f != NULL);

    if (f) {
        /* read contents and perform basic checks */
        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        rewind(f);
        report("output file non-empty", len > 0);

        /* read into buffer and check for token lexeme char */
        char *buf = (char*)malloc((size_t)len + 1);
        if (buf) {
            fread(buf, 1, (size_t)len, f);
            buf[len] = '\0';
            report("output contains token lexeme", strstr(buf, "z") != NULL);
            free(buf);
        }

        fclose(f);
        remove(outname);
    }

    tl_token_list_destroy(list);
}

void test_output_handler_run_all(void) {
    printf("\nRunning output handler module tests...\n");

    test_null_parameters();
    test_build_filename_and_write();
    printf("Finished output handler module tests.\n\n");
}


int main(void) {
    printf("\nStarting tests for Module output handler...\n");

    test_output_handler_run_all();

    printf("Finished tests for Module output handler...\n\n");
    return 0;
}
