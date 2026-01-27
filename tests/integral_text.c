/* 
 * Simple preprocessor test file
 * - Uses system includes
 * - Uses comments
 * - No #define
 * - No local includes
 */

//#include <stdio.h>
// #include <stdlib.h>

/* This function prints a message */
void say_hello(void) {
    printf("Hello from the preprocessor test!\n");
}

int main(void) {
    int x = 5;
    int y = 10;

    char* as = " ";

    // Single-line comment
    if (x < y) {
        printf("x is smaller than y\n");
    } else {
        printf("x is not smaller than y\n");
    }

    /* Multi-line
       comment inside main */
    say_hello();

    return 1;
}