/*
 * -----------------------------------------------------------------------------
 * module_output_handler.c 
 *
 * Usage:
 *     Called from the main application or test modules to handle output in modules.
 *
 * Status:
 *     Initial development — logic to handle output is not yet implemented.
 *
 * Author: [Matias Molina]
 * -----------------------------------------------------------------------------
 */

#include "./module_output_handler.h"

int oh_open(const char *path) {
    print("Output Handler module, still to be implemented\n");
}
int oh_close(int fd) {
    print("Output Handler module, still to be implemented\n");
}
int oh_write_line(int fd, char *buffer) {
    print("Output Handler module, still to be implemented\n");
}
