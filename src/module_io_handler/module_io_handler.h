#ifndef MODULE_IO_HANDLER_H
#define MODULE_IO_HANDLER_H

#include "../main.h"

#define IH_MAX_LINE_LENGTH 1024
#define IOH_MODE_READ "r"
#define IOH_MODE_WRITE "w"
#define IOH_MODE_APPEND "a"

typedef struct ioh_state_t{
    FILE *input_file; // input file
    FILE *output_file; // output file
    int line_number; // current line number
    bool is_eof; // end of file status
} ioh_state_t;

typedef struct {
    char chars[64];
} Separator;

// status
void ioh_init(ioh_state_t *g_ioh);
int ioh_line_number(ioh_state_t *g_ioh);
bool ioh_is_eof(ioh_state_t *g_ioh);

// input
bool ioh_open_input(ioh_state_t *g_ioh, const char *path);
bool ioh_close_input(ioh_state_t *g_ioh);
int ioh_read_line(ioh_state_t *g_ioh, char *buffer, size_t max);
int ioh_read_word(ioh_state_t *g_ioh, char *buffer, size_t max);

// output
bool ioh_close_output(ioh_state_t *g_ioh); 
bool ioh_open_output(ioh_state_t *g_ioh, const char *path); // open with "w"
bool ioh_open_output_append(ioh_state_t *g_ioh, const char *path); // open with "a"
int ioh_write_line(ioh_state_t *g_ioh, char *buffer, size_t max);


#endif
 