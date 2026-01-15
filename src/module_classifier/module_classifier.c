/*
 * -----------------------------------------------------------------------------
 * module_output_handler.c 
 *
 * Usage:
 *     Used as a "detector" to detect when the input file has comments or directive
 *
 * Status:
 *     Initial development — logic not yet implemented.
 *
 * Author: [Franco Olano Melo]
 * -----------------------------------------------------------------------------
 */

#include "./module_classifier.h"

// Macro definitions on the types of directives
#define NO_DIRECTIVE 0
#define DEFINE 1
#define INCLUDE 2
#define IFDEF 3


/*
    Checks whether a line is any type of directive.

    Parameters:
        char* line: input file's line
    
    Returns:
        DEFINE if its a define directive
        INCLUDE if its a include directive
        IFDEF if its a ifdef directive
        NO_DIRECTIVE otherwise.
        
*/
int is_directive(char* line){
    printf(" - Function: is_directive Not implemented.");
    return NO_DIRECTIVE;
}

/*
    Uses the input handler module to read a file line.

    Parameters:
        char* file_path: input file path.

    Returns:
        Next Unprcessed file line.

*/
char* read_input_line(char* file_path){
    printf(" - Function: read_input_line Not implemented.");
}

/*
    Uses the text normalizer module to remove comments.

    Parameters:
        char* line: input file line.

    Returns:
        line any without comments
*/
char* delete_commets(char* line){
    printf(" - Function: delete_commets Not implemented.");
}

/*
    Uses the symbol table module to define a macro from the input file

    Parameters:
        char* line: input file line.

    Returns:
        1 if success, 0 otherwise.
*/
int define_macro(char* line){
    printf(" - Function: define_macro Not implemented.");
}

/*
    Uses the recursivity handler module to include a new file 
    specified in a #include directive.

    Parameters:
        char* line: input file line.

    Returns:
        1 if success, 0 otherwise.
*/
int include_file(char* line){
    printf(" - Function: include_file Not implemented.");
}

/*
    Uses the recursivity handler module to process a ifdef block.

    Parameters:
        char* ifdef_block: hole ifdef block.

    Returns:
        1 if success, 0 otherwise.
*/
int process_ifdef_block(char* ifdef_block){

}

/*
    Classifier main function.
    Reads the input file using the input handler module
    and interacts with the rest to process the output.

    Parameters:

    Returns: 
        
*/
int classifier(int n) {
    printf("Classifier module, still to be implemented\n");

    char* line = " ";
    return is_directive(line);
}
