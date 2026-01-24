/*
 * -----------------------------------------------------------------------------
 * module2.h 
 *
 * Header file for module2, which provides functions to handle command-line
 * arguments in a modular and testable way.
 *
 * Functions:
 * - `print_arguments`: Logs each argument received by the program.
 * - `process_arguments`: Intended to process arguments for the application.
 *
 * Usage:
 *     Include this header in main modules or test modules that require access
 *     to command-line processing functionality.
 *
 * Notes:
 *     This is part of a modular project structure, allowing each module to be
 *     developed and tested independently.
 *
 * Team: [Your Team Name]
 * Contributor/s: [Your Name]
 * -----------------------------------------------------------------------------
 */





#ifndef MODULE2_H
#define MODULE2_H

// defines
#define ARGS_SUFFIX "_pp"

// flags
#define ARG_FLAG_C "-c"
#define ARG_FLAG_D "-d"
#define ARG_FLAG_H "-h"
#define ARG_FLAG_ALL "-all"


#include "../main.h"

typedef struct{
    int is_command_mode; // 1 if command mode, 0 otherwise
    int is_directive_mode; // 1 if directive mode, 0 otherwise
    int is_help_mode; // 1 if help mode, 0 otherwise

    const char *input_path; // path to input file
    const char *output_path; // path to output file
} args_state_t;

args_state_t *args_parse(int argc, char *argv[]);
void args_free(args_state_t *args);

#endif

