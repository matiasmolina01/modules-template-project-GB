/* 
 * Simple preprocessor test file
 * - Uses system includes
 * - Uses comments
 * - No #define
 * - No local includes
 */

//#include <stdio.h>
// #include <stdlib.h>

// #define

#define MACRO0 /**//**/ 1
#define MACRO1 /* "56" */"2"
#define MACRO2 
#define MACRO3 "asf  asd d" /* */

/* This function prints a message */
void say_hello(void) {
    printf("Hello from the preprocessor test!\n");
}

int main(void) {
    int x = 5;
    int y = 10;

    char* as = " ";

	printf("%d %s %s", MACRO0, MACRO1, MACRO3);

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