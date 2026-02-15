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

void print_arguments(int argc, char *argv[]) {
    fprintf(ofile, "Arguments received (%d):\n", argc);
    for (int i = 0; i < argc; i++) {
        fprintf(ofile, "Argument %d: %s\n", i, argv[i]);
    }
    fflush(ofile);
}

// TODO process arguments (similar to P1) into Arguments data structure
Arguments* process_arguments(int argc, char *argv[]) {
    Arguments* args = (Arguments*) malloc(sizeof(Arguments));
    print_arguments(argc, argv);
    fprintf(ofile, "Module arguments: not implemented yet\n");
    fflush(ofile);
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
