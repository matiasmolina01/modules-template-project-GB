#include "./main.h"

// FILE* ofile = NULL; // The output handler for the project run (same variable name as in modules)

int main(int argc, char *argv[]) {
    
    Arguments* args = process_arguments(argc, argv);
	
    #ifdef COUNTCONFIG
        c_count_init(/*This has to be the input file from arguments (argv[1] probably)*/, stdout);
    #endif

    GlobalContext* global_context = gc_init(args);
    s_scanner(global_context);

    #ifdef COUNTCONFIG
        c_count_print_summary();
    #endif

    o_output_handler(global_context->token_list, args->input_path);
	
	//gc_destroy(global_context);

    return 0;
}