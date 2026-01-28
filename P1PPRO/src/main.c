#include "./main.h"

FILE* ofile = NULL; // The output handler for the project run (same variable name as in modules)

int main(int argc, char *argv[]) {
    args_state_t *args_state = args_parse(argc, argv);
	cl_classifier(args_state);
    args_free(args_state);
    return 0;
}