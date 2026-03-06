#include "./main.h"

// FILE* ofile = NULL; // The output handler for the project run (same variable name as in modules)

int main(int argc, char *argv[]) {
    
    Arguments* args = process_arguments(argc, argv);
	// TODO: Error handling for arguments processing (e.g., check if input_path is valid) -> or in the module_args.c

    
    char* language_file = "../tests/test_files/language.txt"; // Relative path from build directory
    
    
    GlobalContext* global_context = init_global_context(language_file);
    
    if (global_context == NULL) {
        printf("Error: Could not initialize global context. Check if file exists: %s\n", language_file);
        exit(1);
    }

    Input* input = i_create();
    if(!i_open_input(input, args->input_path)) {
        // e_error_report(ERR_I_FILE_NOT_FOUND);
        printf("Error: Could not open input file '%s'\n", args->input_path);
        exit(1);
    }
    
    fflush(stdout);
    
    global_context->tokenlist = i_read_elements_from_file(input, global_context);



    // Parser* parser = parser_create(global_context->sra, global_context->tokenlist);

    // int accepted = parser_run(parser);

    // parser_destroy(parser);
    printf("FINISH\n");
    
    i_close_input(input);
    printf("FINISH\n");
    free(input);
    printf("FINISH\n");
    destroy_global_context(global_context);
    printf("FINISH\n");
    free(args);
    printf("FINISH\n");
	
	//gc_destroy(global_context);

    return 0;
}