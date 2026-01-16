/*
 * -----------------------------------------------------------------------------
 * module_symbol_resolver.c 
 *
 * Usage:
 *     Called from the main application or test modules to process symbol resolver.
 *
 * Status:
 *     Initial development — logic to handle symbol resolver is not yet implemented.
 *
 * Author: [Marc Lounds]
 * -----------------------------------------------------------------------------
 */


#include "./module_symbol_resolver.h"

int symbol_resolver(int n) {
    printf("Symbol Resolver module, still to be implemented\n");
}


/*
 * -----------------------------------------------------------------------------
 * module_symbol_resolver.c 
 *
 * Usage:
 *     Called from the main application or test modules to process symbol resolver.
 *
 * Status:
 *     Initial development — logic to handle symbol resolver is not yet implemented.
 *
 * Author: [Marc Lounds]
 * -----------------------------------------------------------------------------
 */


#include "./module_symbol_resolver.h"


// int detector(char *input){
//     printf("This function will detect if there is a macro in the input (via using st_exists which will return if that string exists in the dictionary) and if this is the case then it will set the flag to 1 otherwise it will set the flag to 0");
// }

//This function will be used if flag is 1 (if detector detects a macro)
void sr_substitute(char *input){

    // char word[50];
    // char word2[50];
    // int i = 0;
    // int c;

    // while ((c = getchar()) != '\n' && c != EOF) {
    //     int counter = 0;
    //     if (isspace(c)) {
    //         if (i > 0) {
    //             word[i] = '\0';
    //             if(st_exists(word)==1){

    //                 strcpy(word2, st_get);

    //                 printf("Change macro by value\n");
    //                 for(int j = 0; j < i; j++){
    //                     input[counter] = word[j]  //This replaces the macro with the value in the input
    //                 }

    //             }
    //             i = 0;
    //         }g
    //     } else {
    //         word[i++] = c;
    //     }
    // }
    // counter++;
    // // last word before newline
    // if (i > 0) {
    //     word[i] = '\0';
    //     printf("Word: %s\n", word);
    // }

    // return 0;

    
    printf("This function will process the code and will call st_exists and if any string is a key then it is a macro and will be substituted by its value in dictionary in the string ");
} 

void sr_send_output(char *input){
    printf("This function will call the output handler and pass the changed/or not string");
}
