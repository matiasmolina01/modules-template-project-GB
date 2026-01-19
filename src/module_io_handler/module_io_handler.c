/*
 * -----------------------------------------------------------------------------
 * module_io_handler.c 
 *
 * This module provides functionality to handle io files for modules.
 * - `ioh_open_input`: Opens an io file for reading.
 * - `ioh_close_input`: Closes the currently opened input file.
 * - `ioh_open_output`: Opens an io file for writing.
 * - `ioh_close_output`: Closes the currently opened output file.
 * - `ioh_read_line`: Reads a line from the input file into a buffer.
 * - `ioh_read_word`: Reads a word from the input file into a buffer.
 * - `ioh_line_number`: Returns the current line number being read.
 * - `ioh_is_eof`: Checks if the end of the file has been reached.
 * - `ioh_write_line`: Placeholder for writing a line to output.
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

// static FILE *input_file = NULL; 
// static int num_line = 0; 
// static bool is_eof = false; // to indicate end of file

static ioh_state_t g_ioh = {NULL, NULL, 0, false};

/* STATE */
int ioh_line_number() {
    return g_ioh.line_number; // return current line number
}

bool ioh_is_eof() {
    return g_ioh.is_eof; // return EOF status
}


/* INPUT */
bool ioh_close_input() {
    if(g_ioh.input_file != NULL) { // close file if opened
        fclose(g_ioh.input_file); // close file
        g_ioh.input_file = NULL; // reset pointer
    }
    g_ioh.line_number = 0; // reset line number
    g_ioh.is_eof = false; // reset EOF status
    return true;
}

bool ioh_open_input(const char *path) {
    ioh_close_input(); // before opening file, close previous one.

    if(path == NULL || path[0] == '\0') { // invalid path
        fprintf(stderr, "ioh_open_input: invalid path\n");
        return false;
    } else {
        g_ioh.input_file = fopen(path, IOH_MODE_READ);
        if(g_ioh.input_file == NULL) { // error opening file
            fprintf(stderr, "ioh_open_input: could not open input file '%s'\n", path);
            return false;
        }
    }
    return true;
}

int ioh_read_line(char *buffer, size_t max) {
    if(g_ioh.input_file == NULL) { // file not opened
        fprintf(stderr, "ioh_read_line: input file not opened\n");
        return -1;
    }

    if(buffer == NULL || max == 0) { // invalid buffer
        fprintf(stderr, "ioh_read_line: invalid buffer\n");
        return -1;
    }

    char* res = fgets(buffer, (int)max, g_ioh.input_file); // read line
    if(res == NULL) { // error or EOF
        if(feof(g_ioh.input_file)) { // end of file
            g_ioh.is_eof = true;
            return 0; // indicate EOF
        } else { // error reading file
            fprintf(stderr, "ioh_read_line: error reading input file\n");
            return -1;
        }
    }

    g_ioh.line_number++; // increment line number

    return (int)strlen(buffer); // return number of characters read
}
int ioh_read_word(char *wordbuffer, size_t max) {

    if(g_ioh.input_file == NULL) { // file not opened
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
    while((c = fgetc(g_ioh.input_file)) != EOF) {
        if(c == '\n'){
            g_ioh.line_number++; // increment line number
        } if(!isspace((unsigned char)c)){
            break; // found the start of a word
        }
    }

    if(c == EOF) { // end of file
        g_ioh.is_eof = true;
        return 0; // indicate EOF
    }

    // read the word
    size_t index = 0;
    while(c!= EOF && !isspace((unsigned char)c)){ // if not EOF and not whitespace -> read word
        if(index < max - 1) { // ensure space for null terminator
            wordbuffer[index++] = (char)c; // add character to buffer
        } else { // if the word is too long...
            while((c = fgetc(g_ioh.input_file)) != EOF && !isspace((unsigned char)c)) {
                // to finish reading the rest of the word
            }
            fprintf(stderr, "ioh_read_word: word too long, so we truncate it\n");
            if(c == '\n'){
                g_ioh.line_number++; // increment line number
            }
            break;
        }

        c=fgetc(g_ioh.input_file);
        if(c == '\n'){
            g_ioh.line_number++; // increment line number
        }
    }

    if(c == EOF) {
        g_ioh.is_eof = true;
    }


    wordbuffer[index] = '\0'; // null-terminate the string
    return (int)index; // return number of characters read
}

/* OUTPUT */
bool ioh_close_output() {
    if(g_ioh.output_file != NULL) { // close file if opened
        fclose(g_ioh.output_file); // close file
        g_ioh.output_file = NULL; // reset pointer
    }
    return true;
}


bool ioh_open_output(const char *path) {
    ioh_close_output(); // before opening file, close previous one.

    if(path == NULL || path[0] == '\0') { // invalid path
        fprintf(stderr, "ioh_open_output: invalid path\n");
        return false;
    } else {
        g_ioh.output_file = fopen(path, IOH_MODE_WRITE);
        if(g_ioh.output_file == NULL) { // error opening file
            fprintf(stderr, "ioh_open_output: could not open output file '%s'\n", path);
            return false;
        }
    }
    return true;
}

bool ioh_open_output_append(const char *path) {
    ioh_close_output(); // before opening file, close previous one.

    if(path == NULL || path[0] == '\0') { // invalid path
        fprintf(stderr, "ioh_open_output_append: invalid path\n");
        return false;
    } else {
        g_ioh.output_file = fopen(path, IOH_MODE_APPEND);
        if(g_ioh.output_file == NULL) { // error opening file
            fprintf(stderr, "ioh_open_output_append: could not open output file '%s'\n", path);
            return false;
        }
    }
    return true;
}

int ioh_write_line(char *buffer, size_t max) {
    if(g_ioh.output_file == NULL) { // output file not opened
        fprintf(stderr, "ioh_write_line: output file not opened\n");
        return -1;
    }

    if(buffer == NULL || max == 0) { // invalid buffer
        fprintf(stderr, "ioh_write_line: invalid buffer\n");
        return -1;
    }

    size_t len = strnlen(buffer,max); // get length of buffer
    if(len == 0) { // nothing to write
        return 0;
    }

    size_t res = fwrite(buffer, 1, len, g_ioh.output_file); // write line
    if(res != len) { // error or EOF
        fprintf(stderr, "ioh_write_line: error writing to output file\n");
        return -1;
    }
    return (int)len; // return number of characters read
}