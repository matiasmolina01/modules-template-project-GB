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
    
    printf("LLEGA AQUI 5 - File opened: %s\n", args->input_path);
    fflush(stdout);
    
    global_context->tokenlist = i_read_elements_from_file(input, global_context);


    TokenNode* current = global_context->tokenlist->head;
    while (current != NULL) {
        printf("lexeme='%s', category=%d\n",
               current->token.lexeme,
               current->token.category);
        current = current->next;
    }

    // Parser* parser = parser_create(global_context->sra, global_context->tokenlist);

    // int accepted = parser_run(parser);

    // parser_destroy(parser);

    i_close_input(input);
    free(input);
    destroy_global_context(global_context);
    free(args);
	
	//gc_destroy(global_context);

    return 0;
}