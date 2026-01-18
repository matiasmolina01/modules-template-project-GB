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
 *     In progress — checks if first word is a directive
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
        
    return NO_DIRECTIVE;
}


/*
    Calls text normalizer to eliminate comments

    Parameters:
        Raw Word from the input file
*/

char* cl_normalize_word(char* word){
    printf(" - Function: cl_process_line Not implemented.");
}


/*
    Uses the symbol table module to handle a define directive from the input file

    Returns:
        1 if success, 0 otherwise.
*/
int cl_define_handler(){
    printf(" - Function: cl_define_handler Not implemented.");
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

    global_state->tn_state = tn_state;
    global_state->macro_table = macro_table;

    return global_state;
}

/*
    Classifier main function.
    Reads the input file using the input handler module
    and interacts with the rest to process the output.

    Parameters: 
        file_path: input file's path

    Returns: 0 if everithing worked out correctly
            1 otherwise
        
*/
int cl_classifier(char* file_path) {

    GlobalState* global_state =  cl_init_datastructures();

    ioh_open(file_path);
    
    char next_word[MAX_SIZE];
    while(ioh_read_word(next_word, sizeof(next_word)) > 0){

        char* normalized_word = text_normalizer(next_word, global_state->tn_state);

        // Process directives which are not commented
        if(global_state->tn_state->in_block_comment == 0 
            && global_state->tn_state->in_line_comment == 0 
            /*&& process directives ON*/){

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
            }
        }

        // TODO final write output


        // Resert word buffer
        memset(next_word, 0, sizeof(next_word));
    }


    return 0;
}
