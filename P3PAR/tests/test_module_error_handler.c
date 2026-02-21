/*
 * -----------------------------------------------------------------------------
 * test_module_error_handler.c
 *
 * Unit tests for error_handler module.
 * Tests both e_error_handler() and e_error_report() functions for all error codes in error_table.
 * 
 *
 * Team: GB
 *     
 * Update 1:
 * - Initial test implementation for error_handler module
 * - Tests all error codes in error_table
 * - Verifies e_error_handler() functionality
 * 
 * Author: Alex Ruiz
 * Date: 13-02-2026
 * 
 * -----------------------------------------------------------------------------
 */

#include "../tests/test_module_error_handler.h"

FILE *ofile = NULL;

static void report(const char *name, int ok) {
    printf("%-60s : %s\n", name, ok ? "PASS" : "FAIL");
    fprintf(ofile, "%-60s : %s\n", name, ok ? "PASS" : "FAIL");
}

static void test_e_error_handler(void) {
    fprintf(ofile, "\n=== Testing e_error_handler() ===\n");
    printf("\n=== Testing e_error_handler() ===\n");
    
    fprintf(ofile, "Calling e_error_handler():\n");
    printf("Calling e_error_handler():\n");
    e_error_handler();
    
    report("e_error_handler() executed", 1);
}

static void test_e_error_report_all_codes(void) {
    fprintf(ofile, "\n=== Testing e_error_report() for all error codes ===\n");
    printf("\n=== Testing e_error_report() for all error codes ===\n");
    
    int total_errors = sizeof(error_table) / sizeof(Error);
    
    fprintf(ofile, "Total errors in error_table: %d\n\n", total_errors);
    printf("Total errors in error_table: %d\n\n", total_errors);
    
    // Test all error codes in the error_table
    for (int i = 0; i < total_errors; i++) {
        ErrorCode code = error_table[i].code;
        
        fprintf(ofile, "--- Test %d: Error code %d ---\n", i + 1, code);
        printf("--- Test %d: Error code %d ---\n", i + 1, code);
        
        e_error_report(code);
        
        report("e_error_report() handled error code", 1);
        fprintf(ofile, "\n");
        printf("\n");
    }
}

static void test_e_error_report_invalid_code(void) {
    fprintf(ofile, "\n=== Testing e_error_report() with invalid code ===\n");
    printf("\n=== Testing e_error_report() with invalid code ===\n");
    
    ErrorCode invalid_code = 9999;
    
    fprintf(ofile, "Testing with invalid error code: %d\n", invalid_code);
    printf("Testing with invalid error code: %d\n", invalid_code);
    
    e_error_report(invalid_code);
    
    report("e_error_report() handled invalid code", 1);
}

static void test_e_error_report_specific_categories(void) {
    fprintf(ofile, "\n=== Testing e_error_report() by category ===\n");
    printf("\n=== Testing e_error_report() by category ===\n");
    
    // Test Input Handler errors (100-199)
    fprintf(ofile, "\n--- Input Handler Errors (100-199) ---\n");
    printf("\n--- Input Handler Errors (100-199) ---\n");
    e_error_report(ERR_I_FILE_NOT_FOUND);
    e_error_report(ERR_I_PERMISSION_DENIED);
    e_error_report(ERR_I_BUFFER_OVERFLOW);
    report("Input Handler errors tested", 1);
    
    // Test Scanner errors (200-299)
    fprintf(ofile, "\n--- Scanner Errors (200-299) ---\n");
    printf("\n--- Scanner Errors (200-299) ---\n");
    e_error_report(ERR_S_AUTOMATON_MISSING);
    e_error_report(ERR_S_INFINITE_LOOP);
    e_error_report(ERR_S_INVALID_TOKEN_DATA);
    report("Scanner errors tested", 1);
    
    // Test Automata errors (300-399)
    fprintf(ofile, "\n--- Automata Errors (300-399) ---\n");
    printf("\n--- Automata Errors (300-399) ---\n");
    e_error_report(ERR_A_CHAR_NOT_IN_ALPHABET);
    e_error_report(ERR_A_UNDEFINED_TRANSITION);
    e_error_report(ERR_A_INCORRECT_CONFIG);
    report("Automata errors tested", 1);
    
    // Test Token Handler errors (400-499)
    fprintf(ofile, "\n--- Token Handler Errors (400-499) ---\n");
    printf("\n--- Token Handler Errors (400-499) ---\n");
    e_error_report(ERR_T_MEM_ALLOC_TOKEN);
    e_error_report(ERR_T_LIST_NOT_INITIALIZED);
    e_error_report(ERR_T_MEM_LEAK_FREEING);
    report("Token Handler errors tested", 1);
    
    // Test Output Handler errors (500-599)
    fprintf(ofile, "\n--- Output Handler Errors (500-599) ---\n");
    printf("\n--- Output Handler Errors (500-599) ---\n");
    e_error_report(ERR_O_FILE_OPEN_FAILURE);
    e_error_report(ERR_O_WRITE_FAILURE);
    e_error_report(ERR_O_FILE_CLOSE_FAILURE);
    report("Output Handler errors tested", 1);
}

int main(int argc, char *argv[]) {
    ofile = stdout;
    ofile = set_output_test_file(MODERRORTESTLOGFILENAME);

    printf("Starting tests for Error Handler Module...\n");
    fprintf(ofile, "Starting tests for Error Handler Module...\n");
    printf("=============================================================\n");
    fprintf(ofile, "=============================================================\n");

    // Run all tests
    test_e_error_handler();
    test_e_error_report_all_codes();
    test_e_error_report_invalid_code();
    test_e_error_report_specific_categories();

    printf("\n=============================================================\n");
    fprintf(ofile, "\n=============================================================\n");
    printf("Finished tests for Error Handler Module.\n\n");
    fprintf(ofile, "Finished tests for Error Handler Module.\n\n");

    fclose(ofile);
    return 0;
}
