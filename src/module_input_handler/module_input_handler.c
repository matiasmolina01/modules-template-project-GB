/*
 * -----------------------------------------------------------------------------
 * module_input_handler.c 
 *
 * Usage:
 *     Called from the main application or test modules to handle input in modules.
 *
 * Status:
 *     Initial development — logic to handle input is not yet implemented.
 *
 * Author: [Matias Molina]
 * -----------------------------------------------------------------------------
 */

#include "./module_input_handler.h"


bool ih_open(const char *path) {
    printf("Input Handler module, still to be implemented\n");
}
bool ih_close(int fd) {
    printf("Input Handler module, still to be implemented\n");
}
int ih_read_line(int fd, char *buffer, size_t max) {
    printf("Input Handler module, still to be implemented\n");
}
int ih_write_line(int fd, char *buffer) {
    printf("Input Handler module, still to be implemented\n");
}