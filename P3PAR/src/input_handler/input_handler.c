/*
 * -----------------------------------------------------------------------------
 * input_handler.c 
 *
 * Usage:
 *     Called from the scanner module or test modules to handle input.
 *
 * Status:
 *     Finished
 *
 * Author: Marc Lounds
 * -----------------------------------------------------------------------------
 */

#include "./input_handler.h"


//Para leer carácter por carácter


void i_read_elements_from_file(Input *input){
    
    
   int r;
    char value[MAX_LEN];
    char string_category[MAX_LEN];
    TokenCategory category;
    while ((r = fscanf(input->input_file, " < %[^,] , %[^>] > ", value, string_category)) == 2) { //%[] means read everythin and ^ means NOT so %[^,] means read everything except ,

        // printf("Value: %s | Category: %s\n", value, category);
        Token *token;
        token = t_token_create();
        t_token_set_lexeme(token, value);
        category= t_string_to_category(string_category);
        t_token_update_category(token, category);
        tl_token_list_add(Global_context->token_list, *token);
    
        
        

    }
    if (r == EOF) {
    input->is_eof = IS_EOF; 
    }
}







// char i_read_char(Input *input) {
//     int c;


//     if (input->input_file == NULL) {
// 		// e_error_report(ERR_I_FILE_NOT_FOUND);
//         return NULL;
//     }

//     input->column++;
//     c = fgetc(input->input_file);

//     if (c == EOF) {
//         input->is_eof = IS_EOF;

//         return NULL;   // indica EOF
//     }

//     if (c == '\n') {
//         input->line_number++;
//         input->column = 0;
//     }


//     return c;  // return del carácter 
// }

void i_init(Input *input) {
	input->input_file = NULL;
    // input->line_number = 0;
    input->is_eof = 0;
}

Input* i_create(void) {
    Input *input = (Input*) malloc(sizeof(Input));
    if (input == NULL) return NULL;
    i_init(input);

    return input;
}


int i_is_eof(Input *input) {
    return input->is_eof;
}

int i_open_input(Input *input, const char *path) {
	if(path == NULL || path[0] == '\0') { // invalid path

        exit(1);
    } else {
		input->input_file = fopen(path, MODE_READ);
        if(input->input_file == NULL) { // error opening file
            exit(1);
        }

		return 1;
    }
    return 1;
}


int i_close_input(Input *input) {
    if(input->input_file != NULL) { // close file if opened
        fclose(input->input_file); // close file
        input->input_file = NULL; // reset pointer
    }
    // input->line_number = 0; // reset line number
    // input->is_eof = 0; // reset EOF status

    return 1;
}