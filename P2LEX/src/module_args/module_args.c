/*
 * -----------------------------------------------------------------------------
 * module_args.c 
 *
 * This module provides functionality to process command-line arguments.
 * 
 * - `print_arguments`: Prints each command-line argument with its index.
 * - `process_arguments`: Intended to handle application-specific argument logic.
 *                        Currently, it calls `print_arguments` and signals that
 *                        it's not implemented yet.
 *
 * Usage:
 *     Called from the main application or test modules to process CLI args.
 *
 * Status:
 *     Initial development — logic to handle arguments is not yet implemented.
 *
 * Author: [Your Name or Team]
 * -----------------------------------------------------------------------------
 */

#include "./module_args.h"

void print_arguments(Arguments* args) {
    printf("Arguments received:\n");
    printf("Input path: %s\n", args->input_path);
    printf("Output path: %s\n", args->output_path);
}

Arguments* process_arguments(int argc, char *argv[]) {
    //TODO
	//if(argc < 3) error_report();

	Arguments* args = (Arguments*) malloc(sizeof(Arguments));
	args->input_path = NULL;
	args->output_path = NULL;

	//INPUT AND OUTPUT FILEPATHS
	args->input_path = argv[1];
	args->output_path = argv[2];

	//DEBUG FUNCTION
	//print_arguments(args);
    return args;
}

void args_free(Arguments *args){ 
    if(args != NULL){
        if(args->output_path != NULL){
            free((void*)args->output_path);
        }
        free(args);
    }
}
