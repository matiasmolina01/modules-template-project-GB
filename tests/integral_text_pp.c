









 


void say_hello(void) {
    printf("Hello from the preprocessor test!\n");
}

int main(void) {
    int x = 5;
    int y = 10;

    char* as = " ";

	printf("%d %s %s", 1, "2", "asf  asd d");

        if (x < y) {
        printf("x is smaller than y\n");
    } else {
        printf("x is not smaller than y\n");
    }

    
    say_hello();

    return 1;
}