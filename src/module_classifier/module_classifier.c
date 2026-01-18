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

char* cl_process_word(char* word){
    printf(" - Function: cl_process_line Not implemented.");
}


/*
    Uses the symbol table module to handle a define directive from the input file

    Parameters:
        char* line: input file line.

    Returns:
        1 if success, 0 otherwise.
*/
int cl_define_handler(char* line){
    printf(" - Function: cl_define_handler Not implemented.");
}

int cl_init_datastructures(){
    TextNormalizerState* tn_state;
    // tn_state = init()
}

/*
    Classifier main function.
    Reads the input file using the input handler module
    and interacts with the rest to process the output.

    Parameters: input file's path

    Returns: 0 if everithing worked out correctly
            1 otherwise
        
*/
int cl_classifier(char* file_path) {

    // cl_init_datastructures();
    TextNormalizerState* tn_state;

    ioh_open(file_path);
    
    char next_word[MAX_SIZE];
    while(ioh_read_word(next_word, sizeof(next_word)) > 0){

        char* normalized_word = text_normalizer(next_word, tn_state);

        // TODO if not in comment
        switch(cl_directive_type(normalized_word)){
            case INCLUDE:
            // call recursivity handler - include
            break;
    
            case IFDEF:
            // call recusrivity handler - ifdef
            break;
    
            case DEFINE:
            // call symbol table - declaration of macro
            break;
        }

        // TODO endif

        // TODO final write output


        // Resert word buffer
        memset(next_word, 0, sizeof(next_word));
    }


    return 0;
}
