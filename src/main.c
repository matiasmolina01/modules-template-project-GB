#include "./main.h"

FILE* ofile = NULL; // The output handler for the project run (same variable name as in modules)

int main(int argc, char *argv[]) {
    int n = 0;

    ofile = stdout; // Default output to stdout
    ofile = set_output_test_file(PROJOUTFILENAME);
    
    fprintf(ofile, "Starting module_args ...\n");
    process_arguments(argc, argv); 
    fprintf(ofile, "Finished module_args!!\n");

    fprintf(ofile, "Starting module_classifier ...\n");
    cl_classifier("input", "output");
    fprintf(ofile, "Finished module_classifier!!\n");

    fprintf(ofile, "Starting module_io_handler ...\n");
    ioh_open_input("/test");
    fprintf(ofile, "Finished module_io_handler!!\n");
    
    fprintf(ofile, "Starting module_recursivity_handler ...\n");
    recursivity_handler(n);
    fprintf(ofile, "Finished module_recursivity_handler!!\n");

    fprintf(ofile, "Starting module_symbol_resolver ...\n");
    // symbol_resolver(n);
    fprintf(ofile, "Finished module_symbol_resolver!!\n");

    fprintf(ofile, "Starting module_symbol_table ...\n");
    // test_symbol_table_module(n); this function does not longer exist. 
    // If you want to run tests, call them from build/tests/Debug/test_module_symbol_table.exe.
    fprintf(ofile, "Finished module_symbol_table!!\n");

    fprintf(ofile, "Starting module_text_normalizer ...\n");
    // text_normalizer(n);
    fprintf(ofile, "Finished module_text_normalizer!!\n");

    printf("All modules executed successfully!\n\n");
    fprintf(ofile, "All modules executed successfully!\n\n");

    fclose(ofile); 
    return 0;
}