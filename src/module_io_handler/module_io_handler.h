#ifndef MODULE_IO_HANDLER_H
#define MODULE_IO_HANDLER_H

#include "../main.h"

#define IH_MAX_LINE_LENGTH 1024
#define IOH_MODE_READ "r"
#define IOH_MODE_WRITE "w"
#define IOH_MODE_APPEND "a"

typedef struct {
    FILE *input_file; // input file
    FILE *output_file; // output file
    int line_number; // current line number
    bool is_eof; // end of file status
} ioh_state_t;

// status
int ioh_line_number(void);
bool ioh_is_eof(void);

// input
bool ioh_open_input(const char *path);
bool ioh_close_input(void);
int ioh_read_line(char *buffer, size_t max);
int ioh_read_word(char *buffer, size_t max);

// output
bool ioh_close_output(void); 
bool ioh_open_output(const char *path); // open with "w"
bool ioh_open_output_append(const char *path); // open with "a"
int ioh_write_line(char *buffer, size_t max);


#endif
 