/*
 * tests/test_module_input.c
 *
 * This module tests the Input Handler and Token List creation.
 * It reads a formatted .cscn file and converts it into the internal
 * TokenList structure needed by the parser.
 *
 * The goal is to visually verify that the input file was parsed correctly
 * into tokens in memory, and to assert some basic expectations.
 *
 * Team: [GB]
 */

#include "test_module_input.h"
#include <assert.h>

FILE *ofile = NULL;

/* Helper function to print the loaded tokens */
void print_token_list(TokenList *list, FILE *out) {
    if (!list) {
        fprintf(out, "TokenList is NULL. Input parsing failed.\n");
        return;
    }

    fprintf(out, "=== TOKEN LIST LOADED SUCCESSFULLY ===\n");
    fprintf(out, "Total tokens: %d\n", list->size);

    if (list->head == NULL) {
        fprintf(out, "(empty token list)\n");
        fprintf(out, "======================================\n\n");
        return;
    }

    TokenNode *current = list->head;
    int index = 0;

    while (current != NULL) {
        fprintf(out, "  Token %d -> lexeme='%s', category=%d\n",
                index,
                current->token.lexeme ? current->token.lexeme : "(null)",
                current->token.category);
        current = current->next;
        index++;
    }

    fprintf(out, "======================================\n\n");
}

void test_read_input_file(const char *input_file_path, const char *language_file_path) {
    fprintf(ofile, "Testing i_read_elements_from_file with input: %s\n", input_file_path);
    fprintf(ofile, "Using language file: %s\n", language_file_path);

    GlobalContext *gc = init_global_context(language_file_path);
    assert(gc != NULL);

    Input *input = i_create();
    assert(input != NULL);

    int opened = i_open_input(input, input_file_path);
    assert(opened == 1);
    assert(input->input_file != NULL);

    TokenList *list = i_read_elements_from_file(input, gc);
    assert(list != NULL);

    print_token_list(list, ofile);

    /* Basic sanity checks */
    assert(list->size > 0);
    assert(list->head != NULL);
    assert(list->head->token.lexeme != NULL);

    /*
     * For the current sample input, the first token should be NUM.
     * Adjust these asserts if your sample file changes.
     */
    assert(strcmp(list->head->token.lexeme, "NUM") == 0);

    /*
     * If your input file is:
     * <NUM, CAT_NUMBER> <+, CAT_OPERATOR> <NUM, CAT_NUMBER>
     * then size should be 3.
     * If your file changes, update this expected value.
     */
    assert(list->size == 3);

    i_close_input(input);
    free(input);

    tl_token_list_destroy(list);
    free(list);

    destroy_global_context(gc);
}

int main(int argc, char *argv[]) {
    ofile = stdout;

    printf("Starting tests for Module Input...\n");
    if (ofile != stdout) fprintf(ofile, "Starting tests for Module Input...\n");

    const char *target_input =
        (argc >= 2) ? argv[1] : "../tests/test_files/input_file.cscn";

    const char *target_language =
        (argc >= 3) ? argv[2] : "../tests/test_files/language.txt";

    test_read_input_file(target_input, target_language);

    printf("Finished tests for Module Input...\n\n");
    if (ofile != stdout) {
        fprintf(ofile, "Finished tests for Module Input...\n\n");
        fclose(ofile);
    }

    return 0;
}