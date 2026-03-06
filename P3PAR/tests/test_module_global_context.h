#ifndef TEST_MODULE_GLOBAL_CONTEXT_H
#define TEST_MODULE_GLOBAL_CONTEXT_H
 
#include "../tests/test_modules.h"
#include "../src/global_context/global_context.h"
#include "../src/sra/sra.h"
#include "../src/automata/automata.h"
#include "../src/stack/stack.h"

// Output file with test results separate from the main program, and each module
// It can go to display (stdout) or to a file (one should be commented out)
#define MODGLOBALCTXTTESTLOGFILENAME "./test_module_global_context.log"
// #define MODGLOBALCTXTTESTLOGFILENAME "stdout"

#endif // TEST_MODULE_GLOBAL_CONTEXT_H