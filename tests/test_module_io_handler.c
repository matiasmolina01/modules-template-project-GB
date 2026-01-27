/*
 * -----------------------------------------------------------------------------
 * test_module_io_handler.c
 *
 * Unit tests for module_io_handler.
 *
 * Team:
 *     GB
 * 
 * Update 1:
 * 
 * - module_io_handler functionality test (lack test of write_line)
 * Author: Matias Molina
 * Date: 18-01-2026
 * 
 * -----------------------------------------------------------------------------
 */


#include "../tests/test_module_io_handler.h"



// static const char *TEST_FILE_PATH = "ih_test_input.tmp";

// static void create_test_file(void) {
//     FILE *f = fopen(TEST_FILE_PATH, "w");
//     assert(f != NULL);
//     fputs("hello   world\t42\n", f); 
//     fputs("   #define   ON   1\n\n", f);
//     fputs("ultimalinea\n", f);

//     fclose(f);
// }

// static void delete_test_file(void) {
//     remove(TEST_FILE_PATH); // delete the temporal test file
// }

// static void test_open_invalid_path(void) {
//     assert(ioh_open_input(NULL) == false);
//     assert(ioh_open_input("") == false);
// }

// static void test_open_close_valid_path(void) { // open and close a valid file
//     create_test_file();

//     assert(ioh_open_input(TEST_FILE_PATH) == true);
//     assert(ioh_is_eof() == false);

//     assert(ioh_close_input() == true);
//     delete_test_file();
// }

// static void test_read_word_basic(void) { // read words and check content and line numbers
//     char w[64];

//     create_test_file();
//     assert(ioh_open_input(TEST_FILE_PATH) == true);

//     printf(" ------------- test ioh_read_word_basic: -------------\n");

//     int n;

//     while((n = ioh_read_word(w, sizeof(w))) > 0) {
//         printf("Read word: '%s' (length: %d) at line %d\n", w, n, ioh_line_number());
//     }

//     // EOF expected
//     assert(n == 0);
//     assert(ioh_is_eof() == true);

//     printf("\n----------------------------------\n\n");

//     ioh_close_input();
//     delete_test_file();
// }

// static void test_read_after_close_fails(void) {
//     char buf[16];

//     // without open
//     assert(ioh_read_line(buf, sizeof(buf)) == -1);
//     assert(ioh_read_word(buf, sizeof(buf)) == -1);
// }

// void test_io_handler_run_all(void) {
//     test_open_invalid_path();
//     test_open_close_valid_path();
//     test_read_word_basic();
//     test_read_after_close_fails();
// }

int main(void) {

    //printf("Starting tests for Module io handler...\n");
    //test_io_handler_run_all();
    //printf("Finished tests for Module io handler...\n\n");
    printf("Module io handler tests are not yet implemented.\n");

    return 0;
}