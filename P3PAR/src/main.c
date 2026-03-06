#include "./main.h"

// FILE* ofile = NULL; // The output handler for the project run (same variable name as in modules)

int main(int argc, char *argv[]) {
    
    Arguments* args = process_arguments(argc, argv);
    
    GlobalContext* global_context = init_global_context(args->language_path);

    Input* input = i_create();

    global_context->tokenlist = i_read_elements_from_file(input, global_context);
    Parser* parser = parser_create(global_context->sra, global_context->tokenlist);

    printf("Starting parsing process...\n");
    if(parser_run(parser, global_context->language) != 0){
        printf("Parsing failed.\n");
    } else {
        printf("Parsing completed successfully.\n");
    }
    printf("Starting parsing process...\n");

    parser_destroy(parser);
    i_close_input(input);
    free(input);
    destroy_global_context(global_context);
    free(args);

    return 0;
}