/* * tests/test_module_global_context.c
 * * This module is responsible for testing the Global Context initialization and destruction. 
 * It verifies that the global context successfully encapsulates the Language module 
 * and handles memory allocation/deallocation properly.
 * * The output is directed to a specified file or stdout.
 *
 * The constants and configurations of the tests are defined in the header file test_module_global_context.h.
 * * Team: [GB]
 * Update 1: Added init and destroy tests for GlobalContext.
 * Author: [Franco Olano Melo]
*/

#include "test_module_global_context.h"
#include <assert.h>

FILE *ofile = NULL; // file handler to send the module's output (to a file or stdout)

/* Helper function to print a summary of the GlobalContext state */
void print_global_context(GlobalContext *context, FILE *out) {
    if (!context) {
        fprintf(out, "GlobalContext is NULL. Initialization failed.\n");
        return;
    }

    fprintf(out, "=== GLOBAL CONTEXT ===\n");
    if (context->language) {
        fprintf(out, "Language struct attached successfully.\n");
        fprintf(out, "  - Start Symbol ID: %d\n", context->language->start_symbol);
        fprintf(out, "  - Total Symbols Loaded: %d\n", context->language->num_symbols);
        fprintf(out, "  - Total Rules Loaded: %d\n", context->language->num_rules);
        fprintf(out, "  - Total States Loaded: %d\n", context->language->num_states);
    } else {
        fprintf(out, "Language struct is NULL. Parsing likely failed.\n");
    }
    fprintf(out, "======================\n\n");
}

/* Tests the full lifecycle of the GlobalContext (init, verify, destroy) */
void test_global_context_lifecycle(const char *test_file_path) {
    fprintf(ofile, "Testing init_global_context with file: %s\n", test_file_path);
    
    // 1. Initialize Context
    GlobalContext *context = init_global_context(test_file_path);
    
    // 2. Verify Allocation and Parsing
    assert(context != NULL); // Context must exist
    assert(context->language != NULL); // Language must have been loaded inside the context
    assert(context->language->num_symbols > 0); // Quick check that data actually populated
    
    // 3. Print verification info
    print_global_context(context, ofile);
    
    // 4. Destroy Context (and implicitly the language inside it)
    fprintf(ofile, "Testing destroy_global_context...\n");
    destroy_global_context(context);
    fprintf(ofile, "Global Context destroyed successfully.\n");
}

int main(int argc, char *argv[]) {
    // Assuming the test framework handles "stdout" vs a real file in set_output_test_file
    ofile = stdout; // Default output to stdout
    // ofile = set_output_test_file(MODGLOBALCTXTTESTLOGFILENAME); 

    printf("Starting tests for Module Global Context...\n");
    if (ofile != stdout) fprintf(ofile, "Starting tests for Module Global Context...\n");
    
    // Provide a default path if no arguments are passed, otherwise use argv[1]
    const char *target_file = (argc >= 2) ? argv[1] : "./P3PAR/tests/test_files/language.txt";
    
    test_global_context_lifecycle(target_file);      
    
    printf("Finished tests for Module Global Context...\n\n");
    if (ofile != stdout) {
        fprintf(ofile, "Finished tests for Module Global Context...\n\n");
        fclose(ofile); 
    }
    
    return 0;
}