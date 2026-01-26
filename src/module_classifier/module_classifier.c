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
    Uses the symbol table module to handle a define directive from the input file

    Returns:
        1 if success, 0 otherwise.
*/
int cl_define_handler(){
    
}


/*
    Handles the include directives with the help of the recursivity handler

    Returns:
        1 if success, 0 otherwise.
*/
int cl_include_handler(){
    printf(" - Function: cl_include_handler Not implemented.");
}


/*
    Handles the ifdef directives with the help of the recursivity handler

    Returns:
        1 if success, 0 otherwise.
*/
int cl_ifdef_handler(){
    printf(" - Function: cl_ifdef_handler Not implemented.");
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

    global_state->tn_state = tn_state;
    global_state->macro_table = macro_table;
    global_state->replace_flags = replace_flags;
    global_state->rh_stack = rh_stack;
    global_state->rh_process_macro = rh_process_macro;

    return global_state;
}

void cl_free_datastructures(GlobalState* global_state){
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
// TODO receive arguments struct as parameter
int cl_classifier(args_state_t* args_state) {

    GlobalState* global_state =  cl_init_datastructures();
    global_state->args_state = args_state;

    char* input_file_path = args_state->input_path;
    char* output_file_path = args_state->output_path;

    ioh_open_input(input_file_path);
    if (!ioh_open_output_append(output_file_path)){
        ioh_open_output(output_file_path);
    }
    
    char next_word[MAX_SIZE];
    while(ioh_read_word(next_word, sizeof(next_word)) > 0){

        char* normalized_word = text_normalizer(next_word, global_state->tn_state);

        // Process directives which are not commented or in a string
        if(global_state->tn_state->in_block_comment == 0 
            && global_state->tn_state->in_line_comment == 0 
            && global_state->replace_flags->inString == 0
            && global_state->args_state->is_directive_mode == 1){

            switch(cl_directive_type(normalized_word)){

                case INCLUDE:
                cl_include_handler();
                break;
        
                case IFDEF:
                cl_ifdef_handler();
                break;
        
                case DEFINE:
                cl_define_handler();
                break;

                case ENDIF:
                rh_handle_endif(global_state->rh_stack);
                break;
            }

            continue;
        }

        char* final_word = sr_substitute(normalized_word, global_state->replace_flags, global_state->macro_table);

        // Write to output the correct word depending on if its a comment or not
        if(global_state->args_state->is_command_mode == 1){
            ioh_write_line(final_word, strlen(final_word));
        }else{
            ioh_write_line(next_word, strlen(next_word));
        }

        // Resert word buffer
        memset(next_word, 0, sizeof(next_word));
    }

    ioh_close_input();
    ioh_close_output();
    cl_free_datastructures(global_state);

    return 0;
}
