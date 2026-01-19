/*
 * -----------------------------------------------------------------------------
 * test_module_classifier.c
 *
 * Unit tests for module_classifier.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_classifier functionality test
 * 
 * Author: Franco Olano
 * Date: 18-01-2026
 * 
 * -----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <string.h>
#include "../tests/test_module_classifier.h"

void test_directive_type() {
    printf(" - cl_directive_type: running tests...\n");

    // 1. Positive Test Cases (Exact Matches)
    assert(cl_directive_type("#include") == INCLUDE);
    assert(cl_directive_type("#define") == DEFINE);
    assert(cl_directive_type("#ifdef") == IFDEF);

    // 2. Negative Test Cases (Valid words, but not directives)
    // Missing the hash
    assert(cl_directive_type("include") == NO_DIRECTIVE); 
    // Random words
    assert(cl_directive_type("int") == NO_DIRECTIVE);
    assert(cl_directive_type("void") == NO_DIRECTIVE);
    
    // 3. Edge Cases
    // Case sensitivity (C is case sensitive, so #INCLUDE is not a directive)
    assert(cl_directive_type("#INCLUDE") == NO_DIRECTIVE);
    // Trailing/Leading whitespace (strcmp is strict, so these should fail)
    assert(cl_directive_type("#include ") == NO_DIRECTIVE);
    assert(cl_directive_type(" #include") == NO_DIRECTIVE);
    // Empty string
    assert(cl_directive_type("") == NO_DIRECTIVE);
    // Partial matches
    assert(cl_directive_type("#inc") == NO_DIRECTIVE);

    printf(" - cl_directive_type: All tests passed successfully!\n");
}

void test_classifier_main(){
    printf(" - cl_classfier: starting tests...\n");
    cl_classifier("../../test/test_module_classifier/test1.c", "../../test/test_module_classifier/out/test1_pp.c");
}

int main(void) {
    printf("\nStarting tests for Module classifier...\n");
    test_directive_type();
    test_classifier_main();
    printf("Finished tests for Module classifier...\n\n");
    return 0;
}