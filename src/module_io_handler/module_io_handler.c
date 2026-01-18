/*
 * -----------------------------------------------------------------------------
 * module_io_handler.c 
 *
 * This module provides functionality to handle io files for modules.
 * - `ioh_open`: Opens an io file for reading.
 * - `ioh_close`: Closes the currently opened input file.
 * - `ioh_read_line`: Reads a line from the input file into a buffer.
 * - `ioh_read_word`: Reads a word from the input file into a buffer.
 * - `ioh_line_number`: Returns the current line number being read.
 * - `ioh_is_eof`: Checks if the end of the file has been reached.
 * 
 * Usage:
 *     Called from the main application or test modules to handle io in modules.
 *
 * Status:
 *     Initial development — logic to handle io is not yet implemented.
 *
 * Author: [Matias Molina]
 * -----------------------------------------------------------------------------
 */

#include "./module_io_handler.h"

static FILE *input_file = NULL; // input file
static int num_line = 0; // current line number
static bool is_eof = false; // to indicate end of file


bool ioh_close() {
    if(input_file != NULL) { // close file if opened
        fclose(input_file); // close file
        input_file = NULL; // reset pointer
    }
    num_line = 0; // reset line number
    is_eof = false; // reset EOF status
    return true;
}

bool ioh_open(const char *path) {
    ioh_close(); // before opening file, close previous one.

    if(path == NULL || path[0] == '\0') { // invalid path
        fprintf(stderr, "ioh_open: invalid path\n");
        return false;
    } else {
        input_file = fopen(path, "r");
        if(input_file == NULL) { // error opening file
            fprintf(stderr, "ioh_open: could not open input file '%s'\n", path);
            return false;
        }
    }
    return true;
}

int ioh_read_line(char *buffer, size_t max) {
    if(input_file == NULL) { // file not opened
        fprintf(stderr, "ioh_read_line: input file not opened\n");
        return -1;
    }

    if(buffer == NULL || max == 0) { // invalid buffer
        fprintf(stderr, "ioh_read_line: invalid buffer\n");
        return -1;
    }

    char* res = fgets(buffer, (int)max, input_file); // read line
    if(res == NULL) { // error or EOF
        if(feof(input_file)) { // end of file
            is_eof = true;
            return 0; // indicate EOF
        } else { // error reading file
            fprintf(stderr, "ioh_read_line: error reading input file\n");
            return -1;
        }
    }

    num_line++; // increment line number

    return (int)strlen(buffer); // return number of characters read
}
int ioh_read_word(char *wordbuffer, size_t max) {

    if(input_file == NULL) { // file not opened
        fprintf(stderr, "ioh_read_word: input file not opened\n");
        return -1;
    }

    if(wordbuffer == NULL || max < 2) { // invalid buffer, max >= 2: one char + '\0'
        fprintf(stderr, "ioh_read_word: invalid buffer\n");
        return -1;
    }

    wordbuffer[0] = '\0'; // initialize buffer

    int c;

    // to start reading the word, skip whitespace
    while((c = fgetc(input_file)) != EOF) {
        if(c == '\n'){
            num_line++; // increment line number
        } if(!isspace((unsigned char)c)){
            break; // found the start of a word
        }
    }

    if(c == EOF) { // end of file
        is_eof = true;
        return 0; // indicate EOF
    }

    // read the word
    size_t index = 0;
    while(c!= EOF && !isspace((unsigned char)c)){ // if not EOF and not whitespace -> read word
        if(index < max - 1) { // ensure space for null terminator
            wordbuffer[index++] = (char)c; // add character to buffer
        } else { // if the word is too long...
            while((c = fgetc(input_file)) != EOF && !isspace((unsigned char)c)) {
                // to finish reading the rest of the word
            }
            fprintf(stderr, "ioh_read_word: word too long, so we truncate it\n");
            if(c == '\n'){
                num_line++; // increment line number
            }
            break;
        }

        c=fgetc(input_file);
        if(c == '\n'){
            num_line++; // increment line number
        }
    }

    if(c == EOF) {
        is_eof = true;
    }


    wordbuffer[index] = '\0'; // null-terminate the string
    return (int)index; // return number of characters read
}

int ioh_line_number() {
    return num_line; // return current line number
}

bool ioh_is_eof() {
    return is_eof; // return EOF status
}

int ioh_write_line(char *buffer, size_t max) {
    printf("Output Handler module, still to be implemented\n");
}