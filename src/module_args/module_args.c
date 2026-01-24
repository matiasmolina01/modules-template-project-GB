/*
 * -----------------------------------------------------------------------------
 * module_args.c 
 *
 * This module provides functionality to process command-line arguments.
 *
 * Usage:
 *     Called from the main application or test modules to process CLI args.
 *
 * Status:
 *     Initial development — logic to handle arguments is not yet implemented.
 *
 * Author: Matias Molina
 * -----------------------------------------------------------------------------
 */

#include "./module_args.h"

/*
    Frees the memory allocated for args_state_t structure.

    Parameters:
        args_state_t *args - pointer to the args_state_t structure to free
*/
void args_free(args_state_t *args){ 
    if(args != NULL){
        if(args->output_path != NULL){
            free((void*)args->output_path);
        }
        free(args);
    }
}

/*
    Parses command-line arguments and populates an args_state_t structure.

    Parameters:
        int argc - number of command-line arguments
        char *argv[] - array of command-line argument strings

    Returns:
        Pointer to populated args_state_t structure, or NULL on error.
*/
args_state_t *args_parse(int argc, char *argv[]){ // hace falta implementarla
    
    args_state_t *args = malloc(sizeof(args_state_t));
        if (!args) {
        fprintf(stderr, "args_parse: memory allocation failed\n");
        return NULL;
    }

    args->input_path = NULL;
    args->output_path = NULL;
    args->is_command_mode = 0;
    args->is_directive_mode = 0;
    args->is_help_mode = 0;

    if(argc < 2) {
        fprintf(stderr, "args_parse: not enough arguments\n");
        args_free(args);
        return NULL;
    }

    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];

        if(strcmp(arg, ARG_FLAG_H) == 0) {
            args->is_help_mode = 1;
            return args; // ignore rest of arguments
        } else if(strcmp(arg, ARG_FLAG_ALL) == 0){
            args->is_directive_mode = 1;
            args->is_command_mode = 1;
        } else if(strcmp(arg, ARG_FLAG_D) == 0) {
            args->is_directive_mode = 1;
        } else if(strcmp(arg, ARG_FLAG_C) == 0) {
            args->is_command_mode = 1;
        } else if (arg[0] == '-') {
                fprintf(stderr, "args_parse: unknown flag '%s'\n", arg);
                args_free(args);
                return NULL;  
        } else {
            if (args->input_path == NULL) { // file paths
                args->input_path = arg;
        } else {
                fprintf(stderr, "args_parse: too many file paths provided\n");
                args_free(args);
                return NULL;
            }
        }
    }

    if(!args->is_help_mode && args->is_command_mode == 0 && args->is_directive_mode == 0) { // that is to say, no mode selected (no flags)
        args->is_command_mode = 1; // default to command mode
    }

    if(!args->is_help_mode && args->input_path == NULL) { // because help mode doesnt need input path
        fprintf(stderr, "args_parse: input file path is required\n");
        args_free(args);
        return NULL;
    }

    if(!args->is_help_mode) { // to dont set output path when in help mode
        // set output path
        const char *in = args->input_path;
        const char *dot = strrchr(in, '.'); // extension dot

        size_t base_len = (dot != NULL) ? (size_t)(dot - in) : strlen(in);
        const char *ext = (dot != NULL) ? dot : "";

        // to calculate the total output path length
        size_t suffix_len = strlen(ARGS_SUFFIX);
        size_t out_len = base_len + suffix_len + strlen(ext) + 1; // +1 for null terminator
        
        char *output_path = malloc(out_len); 
        if (!output_path) {
            fprintf(stderr, "args_parse: memory allocation failed for output path\n");
            args_free(args);
            return NULL;
        }
        memcpy(output_path, in, base_len); // copy base name

        output_path[base_len] = '\0'; // null terminate before adding suffix
        strcat(output_path, ARGS_SUFFIX); // add _pp
        strcat(output_path, ext); // add extension
        args->output_path = output_path; // set output path
    }

    return args;
}

