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
#ifdef COUNTCONFIG
    count_local_t __cnt_local_pa__;
    c_count_local_init(&__cnt_local_pa__);
#endif
    printf("Arguments received:\n");
#ifdef COUNTCONFIG
    COUNTIO(19, __cnt_local_pa__); /* approx bytes for the above printf */
#endif
    printf("Input path: %s\n", args->input_path);
#ifdef COUNTCONFIG
    if (args->input_path != NULL) COUNTIO((int)strlen(args->input_path) + 14, __cnt_local_pa__);
    COUNTGEN(1, __cnt_local_pa__);
#endif
}

Arguments* process_arguments(int argc, char *argv[]) {
#ifdef COUNTCONFIG
    count_local_t __cnt_local_pa_proc__;
    c_count_local_init(&__cnt_local_pa_proc__);
#endif

    if(argc < 2) {
#ifdef COUNTCONFIG
        COUNTCOMP(1, __cnt_local_pa_proc__);
#endif
        e_error_report(ERR_MA_INVALID_ARG_NUMBER);
    }

    Arguments* args = (Arguments*) malloc(sizeof(Arguments));
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_pa_proc__); /* allocation */
#endif
    args->input_path = NULL;

    //INPUT AND OUTPUT FILEPATHS
    args->input_path = argv[1];
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_pa_proc__); /* assign input path */
#endif

    //DEBUG FUNCTION
    //print_arguments(args);
    return args;
}

void args_free(Arguments *args){ 
    if(args != NULL){
        if(args->input_path != NULL){
            free((void*)args->input_path);
#ifdef COUNTCONFIG
            count_local_t __cnt_local_af__;
            c_count_local_init(&__cnt_local_af__);
            COUNTGEN(1, __cnt_local_af__); /* free input path */
            COUNTIO(1, __cnt_local_af__);
#endif
        }
        free(args);
#ifdef COUNTCONFIG
        /* count freeing the structure */
        count_local_t __cnt_local_af2__;
        c_count_local_init(&__cnt_local_af2__);
        COUNTGEN(1, __cnt_local_af2__);
#endif
    }
}
