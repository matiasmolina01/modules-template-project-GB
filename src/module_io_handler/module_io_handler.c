/*
 * -----------------------------------------------------------------------------
 * module_io_handler.c 
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

static ioh_state_t g_ioh = {NULL, NULL, 0, false};
static Separator g_separators = { "=,\t ;\"(){}[]<>.?!/\n" };

/* STATE */
/*
    Returns the current line number being read.

    Returns:
        Current line number
*/
int ioh_line_number() {
    return g_ioh.line_number; // return current line number
}

/*
    Checks if the end of the file has been reached.

    Returns:
        true if EOF reached, false otherwise.
*/
bool ioh_is_eof() {
    return g_ioh.is_eof; // return EOF status
}


/* INPUT */
/*
    Closes the currently opened input file.

    Returns:
        true if success, false otherwise.
*/
bool ioh_close_input() {
    if(g_ioh.input_file != NULL) { // close file if opened
        fclose(g_ioh.input_file); // close file
        g_ioh.input_file = NULL; // reset pointer
    }
    g_ioh.line_number = 0; // reset line number
    g_ioh.is_eof = false; // reset EOF status
    return true;
}

/*
    Opens an io file for reading.

    Parameters:
        const char *path - the file path to open
*/
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

/*
    Reads a line from input file

    Parameters:
        char *buffer - buffer to store the read line
        size_t max - maximum number of characters to read
    
    Returns:
        Number of characters read, 0 if EOF reached, -1 on error
*/
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

/*
    Reads a word from input file, interacts with classifier.

    Parameters:
        char *wordbuffer - buffer to store the read word
        size_t max - maximum number of characters to read
    
    Returns:
        Number of characters/letters read, 0 if EOF reached, -1 on error
*/
int ioh_read_word(char *wordbuffer, size_t max) {

    // error handling
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
        for(size_t i = 0; i < sizeof(g_separators.chars); i++){
            if(c == g_separators.chars[i]){
                // if separator, return it as a word
                wordbuffer[0] = (char)c; 
                wordbuffer[1] = '\0'; // null terminate
                if(c == '\n'){
                    g_ioh.line_number++; // increment line number
                }
                return 1; // length 1
            }
        }
        if(!isspace((unsigned char)c)){
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
                ungetc(c, g_ioh.input_file); // put back to the next read
            }
            break;
        }
        c=fgetc(g_ioh.input_file); // read next character
    }

    if(c == '\n') {
        ungetc(c, g_ioh.input_file); // put back to the next read
    }
    if(c == EOF) {
        g_ioh.is_eof = true;
    }


    wordbuffer[index] = '\0'; // null-terminate the string
    return (int)index; // return number of characters read
}

/* OUTPUT */
/*
    Closes the currently opened output file.

    Returns:
        true if success, false otherwise.
*/
bool ioh_close_output() {
    if(g_ioh.output_file != NULL) { // close file if opened
        fclose(g_ioh.output_file); // close file
        g_ioh.output_file = NULL; // reset pointer
    }
    return true;
}

/*
    Opens an io file for writing.

    Parameters:
        const char *path - the file path to open
*/
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

/*
    Opens an io file for appending. !!! To start writting at the end of the file. !!!

    Parameters:
        const char *path - the file path to open
*/
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

/*
    Writes a line to output file.

    Parameters:
        char *buffer - buffer containing the line to write
        size_t max - maximum number of characters to write
    
    Returns:
        Number of characters written, -1 on error
*/
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