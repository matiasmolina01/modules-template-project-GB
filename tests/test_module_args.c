/*
 * -----------------------------------------------------------------------------
 * test_module_args.c
 *
 * Unit tests for module_args.
 *
 * Team: GB
 * 
 * Update 1:
 * 
 * - module_args functionality test
 * 
 * Author: Matias Molina
 * Date: 24-01-2026
 * -----------------------------------------------------------------------------
 */

#include "../tests/test_module_args.h"

FILE *ofile = NULL; // file handler to send the module's output (to a file or stdout)

static void print_args(args_state_t *args){
    if(args == NULL){
        fprintf(ofile, "Arguments struct is NULL\n");
        return;
    }
    printf("----------- Parsed Arguments Test -----------\n");
    printf("help_mode        : %d\n", args->is_help_mode);
    printf("command_mode (-c): %d\n", args->is_command_mode);
    printf("directive_mode(-d): %d\n", args->is_directive_mode);

    if (args->input_path)
        printf("input_path: %s\n", args->input_path);
    else
        printf("input_path: (null)\n");

    if (args->output_path)
        printf("output_path: %s\n", args->output_path);
    else
        printf("output_path: (null)\n");

    printf("\n----------------------------------\n\n");
}

int main(int argc, char *argv[]) {


    ofile = stdout; // Default output to stdout
    ofile = set_output_test_file(MODARGSTESTLOGFILENAME);

    printf("Starting tests for Module args...\n\n");
    args_state_t *args = args_parse(argc, argv);
    print_args(args);
    args_free(args);

    fprintf(ofile, "\n\nFinished tests for Module args...\n\n");

    fclose(ofile); 
    return 0;
}
