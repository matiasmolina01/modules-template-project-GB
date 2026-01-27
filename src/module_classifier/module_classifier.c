/*
 * -----------------------------------------------------------------------------
 * module_classifier.c 
 *
 * Usage:
 *     Defines the main flux of the preprocesor. 
 *     Interacts with other modules to detect and process directives
 *      and regular code lines.
 *
 * Status:
 *     In progress
 *
 * Author: [Franco Olano Melo]
 * -----------------------------------------------------------------------------
 */

#include "./module_classifier.h"


/*
    Checks whether a line is any type of directive.

    Parameters:
        char* line: input file's first word
    
    Returns:
        A Directive enum value
        
*/
Directive cl_directive_type(char* word){
    if (strcmp(word, INCLUDE_STR) == 0)
        return  INCLUDE;
    if(strcmp(word, IFDEF_STR) == 0)
        return IFDEF;
    if(strcmp(word, DEFINE_STR) == 0)
        return DEFINE;
    if(strcmp(word, ENDIF_STR) == 0)
        return ENDIF;
        
    return NO_DIRECTIVE;
}

/*
Returns next non commented words
 or hole strings, to use as argument for the directives.
*/

char* cl_next_argument(GlobalState* global_state){
    char* final_word = NULL;
    char next_word[MAX_SIZE];

    while(ioh_read_word(global_state->io_state, next_word, sizeof(next_word)) > 0){
        // Delete comments to ignore them.
        char* normalized_word = text_normalizer(next_word, global_state->tn_state, global_state->replace_flags);
        // if its a space, ignore
        if(global_state->replace_flags->inString == 0 && strcmp(normalized_word, " ") == 0){
            continue;
        }
        // concat normalized_word to final
        size_t current_len = (final_word == NULL) ? 0 : strlen(final_word);
        size_t append_len = strlen(normalized_word);
        
        char* temp = realloc(final_word, current_len + append_len + 1);
        
        if (temp == NULL) {
            if (final_word) free(final_word);
            return NULL;
        }
        final_word = temp;
        if (current_len == 0) {
            final_word[0] = '\0';
        }
        strcat(final_word, normalized_word);

        // IF next word is new line, return new line.
        if(strcmp(normalized_word, "\n") == 0){
            return "\n";
        }
        // IF next word is a not commented word 
        else if (strcmp(normalized_word, "") != 0){
            final_word = normalized_word;
            // if we are not in a string, return this word.
            if(global_state->replace_flags->inString == 0){
                break;
            }
            // else, if we are on a string return the hole string. (continue loop)
        } 
        memset(next_word, 0, sizeof(next_word));
    }
    return final_word;
}




/*
    Uses the symbol table module to handle a define directive from the input file

    Returns:
        1 if success, 0 otherwise.
*/
int cl_define_handler(GlobalState* global_state){
    char* macro_name = cl_next_argument(global_state);
    char* macro_value = cl_next_argument(global_state);

    if(strcmp(macro_value, "\n") == 0){
        macro_value = NULL;
    }

    printf("calling define in macro table for '%s':'%s'\n", macro_name, macro_value);
    st_define(global_state->macro_table, macro_name, macro_value);
}


/*
    Handles the include directives with the help of the recursivity handler

    Returns:
        1 if success, 0 otherwise.
*/
int cl_include_handler(GlobalState* global_state){
    char* include_file_path = cl_next_argument(global_state);
    return rh_handle_include(include_file_path, global_state->args_state);
}


/*
Handles the ifdef directives with the help of the recursivity handler

Returns:
1 if success, 0 otherwise.
*/
int cl_ifdef_handler(GlobalState* global_state){
    char* macro_name = cl_next_argument(global_state);
    // TODO check that macro name is not '' or \n

    rh_handle_ifdef_directive(macro_name, global_state->macro_table,
         global_state->rh_stack, 0, global_state->rh_process_macro);

    return 0; 
}

/*
    Initializes other modules datastructures and stores them in the GlobalState.

    Returns:
        GlobalState* global state datastructure.
*/
GlobalState* cl_init_datastructures(){
    GlobalState* global_state = (GlobalState*) malloc(sizeof(GlobalState));

    TextNormalizerState* tn_state = (TextNormalizerState*) malloc(sizeof(TextNormalizerState));
    text_normalizer_init(tn_state);
    
    MacroTable *macro_table = st_init();

    ReplaceFlags *replace_flags = (ReplaceFlags*) malloc(sizeof(ReplaceFlags));
    sr_init_ReplaceFlags(replace_flags);

    RHStack *rh_stack = rh_stack_create(RH_STACK_CAPACITY);

    RHProcessMacro* rh_process_macro = (RHProcessMacro*) malloc(sizeof(RHProcessMacro));
    rh_process_macro->process = 1;

    ioh_state_t* io_state = ioh_create();

    global_state->tn_state = tn_state;
    global_state->macro_table = macro_table;
    global_state->replace_flags = replace_flags;
    global_state->rh_stack = rh_stack;
    global_state->rh_process_macro = rh_process_macro;
    global_state->io_state = io_state;

    return global_state;
}

void cl_free_datastructures(GlobalState* global_state){
    st_destroy(global_state->macro_table);
    free(global_state->io_state);
    free(global_state);
}

/*
    Classifier main function.
    Reads the input file using the input handler module
    and interacts with the rest to process the output.

    Parameters: 
        input_file_path: input file's path
        output_file_path: outputs file's path

    Returns: 0 if everithing worked out correctly
            1 otherwise
        
*/
int cl_classifier(args_state_t* args_state) {

    GlobalState* global_state =  cl_init_datastructures();
    global_state->args_state = args_state;

    char* input_file_path = args_state->input_path;
    char* output_file_path = args_state->output_path;

    ioh_open_input(global_state->io_state, input_file_path);
    if (!ioh_open_output_append(global_state->io_state, output_file_path)){
        ioh_open_output(global_state->io_state, output_file_path);
    }
    
    char next_word[MAX_SIZE];
    while(ioh_read_word(global_state->io_state, next_word, sizeof(next_word)) > 0){
        // Only process if the ifdef
        if(global_state->rh_process_macro->process == 1){

            char* normalized_word = text_normalizer(next_word, global_state->tn_state, global_state->replace_flags);
    
            // Process directives which are not commented or in a string
            if(global_state->tn_state->in_block_comment == 0 
                && global_state->tn_state->in_line_comment == 0 
                && global_state->replace_flags->inString == 0
                && global_state->args_state->is_directive_mode == 1){
    
                switch(cl_directive_type(normalized_word)){
    
                    case INCLUDE:
                    cl_include_handler(global_state);
                    ioh_write_line(global_state->io_state, '\n', strlen('\n'));
                    continue;
            
                    case IFDEF:
                    cl_ifdef_handler(global_state);
                    ioh_write_line(global_state->io_state, '\n', strlen('\n'));
                    continue;
            
                    case DEFINE:
                    cl_define_handler(global_state);
                    st_print_all(global_state->macro_table);
                    ioh_write_line(global_state->io_state, '\n', strlen('\n'));
                    continue;
    
                    case ENDIF:
                    rh_handle_endif(global_state->rh_stack);
                    break;

                }

            }
    
            char* final_word = sr_substitute(normalized_word, global_state->replace_flags, global_state->macro_table);
            
            // Write to output the correct word depending on if its a comment or not
            if(global_state->args_state->is_command_mode == 1 && strcmp(final_word, "") != 0){
                ioh_write_line(global_state->io_state, final_word, strlen(final_word));
            
            }else if(global_state->args_state->is_command_mode == 0){
                ioh_write_line(global_state->io_state, next_word, strlen(next_word));
            }

        }

        // Resert word buffer
        memset(next_word, 0, sizeof(next_word));
    }

    ioh_close_input(global_state->io_state);
    ioh_close_output(global_state->io_state);
    cl_free_datastructures(global_state);

    return 0;
}
