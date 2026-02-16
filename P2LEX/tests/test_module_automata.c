/* 
 * tests/test_module_automata.c
 * 
 * This module is responsible to process the automata transtions, and as a intermediate step to the scanner,
 * to check if the automata is in an accepting state or if the lookahead can continue with the automata.
 *  
 * The functions of this module are called from the scanner module, and they are tested in this test module.
 * 
 * This module has to manipulate launch.json to set the program arguments for running/debugging. 
 * So the contributors of this module have to have "ownership" of launch.json file too.
 * 
 * It includes the test cases of the all functions into this module:
 *      - a_accepting_state
 *      - a_advance_automata
 *      - a_lookahead_process
 *      - a_next_state
 *      - a_mapping_alphabet
 *      - a_process
 *      - a_reset_automata
 *
 * The constants and configurations of the tests are defined in the header file test_module_automata.h.
 * 
 * Team: GB
 * 
 * Update 1: To comprobe all functions into this module.
 * Author: Matias Molina
 * Date: 13/02/2026
*/
#include "../tests/test_module_automata.h"

FILE *ofile = NULL;

// create a function to build an temporal automata, f.e. Numbers automata
void automata_build(Automata *a){
    assert(a != NULL); // does not be null
    memset(a, 0, sizeof(*a)); // initialize all fields to 0 (including the arrays of the struct)

    a->numstates  = 2;   // 0 start, 1 accepting
    a->numcols    = 1;   // only one class of symbols (digits)
    a->numsymbols = 1;

    a->initial_state = 0;
    a->current_state = 0;

    // Reduced alphabet: D = digit (0..9)
    a->alphabet[0].name = 'D';
    a->alphabet[0].col  = 0;

    // Init transitions to -1 (dead) and accept info to 0
    for (int i = 0; i < MAXLEN; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            a->transitions[i][j] = -1;
        }
        a->accept[i].flag = 0;
        a->accept[i].category = CAT_NUMBER;
    }

    // DFA:
    // state 0: D -> 1
    // state 1: D -> 1
    a->transitions[0][0] = 1;
    a->transitions[1][0] = 1;

    // Accepting state
    a->accept[1].flag = 1;
    a->accept[1].category = CAT_NUMBER;
}

/* Pretty print helper for results */
static const char* res_name(int r){
    if (r == A_CONTINUE) return "A_CONTINUE";
    if (r == A_ACCEPT)   return "A_ACCEPT";
    if (r == A_FAIL)     return "A_FAIL";
    return "UNKNOWN";
}

// to prove the test mapping function of the alphabet of the automata, and the error handling of it.
static void test_mapping_alphabet(){
    Automata a;
    automata_build(&a); // build the automata.

    fprintf(ofile, "\n[TEST] a_mapping_alphabet\n"); // print the name of the test

    int colD = a_mapping_alphabet(&a, 'D');
    fprintf(ofile, "mapping('D') = %d (expected 0)\n", colD);
    assert(colD == 0);

    int colX = a_mapping_alphabet(&a, 'X');
    fprintf(ofile, "mapping('X') = %d (expected A_FAIL=%d)\n", colX, A_FAIL);
    assert(colX == A_FAIL);
}

static void test_next_and_advance(){
    Automata a;
    automata_build(&a);

    fprintf(ofile, "\n[TEST] a_next_state + a_advance_automata\n"); // print the name of the test
    fprintf(ofile, "initial current_state = %d\n", a.current_state);

    int ns = a_next_state(&a, 'D');
    fprintf(ofile, "next_state(state=%d, 'D') = %d (expected 1)\n", 0, ns);
    assert(ns == 1);

    int adv = a_advance_automata(&a, 'D');
    fprintf(ofile, "advance('D') = %d, current_state now = %d (expected 1)\n", adv, a.current_state);
    assert(adv == 1);
    assert(a.current_state == 1);

    // Now loop on D at state 1
    ns = a_next_state(&a, 'D');
    fprintf(ofile, "next_state(state=%d, 'D') = %d (expected 1)\n", 1, ns);
    assert(ns == 1);

    // character not in alphabet => next_state returns 0 (not accepted)
    ns = a_next_state(&a, 'X');
    fprintf(ofile, "next_state(state=%d, 'X') = %d (expected 0)\n", a.current_state, ns);
    assert(ns == 0);
}

// to test the function a_accepting_state, and the error handling of it.
static void test_accepting_state(){ 
    Automata a;
    automata_build(&a);

    fprintf(ofile, "\n[TEST] a_accepting_state\n");
    fprintf(ofile, "accepting(0) = %d (expected 0)\n", a_accepting_state(&a, 0));
    assert(a_accepting_state(&a, 0) == 0);

    fprintf(ofile, "accepting(1) = %d (expected 1)\n", a_accepting_state(&a, 1));
    assert(a_accepting_state(&a, 1) == 1);
}

// a_lookahead_process
static void test_lookahead_process(){
    Automata a;
    automata_build(&a);

    fprintf(ofile, "\n[TEST] a_lookahead_process\n");

    // Move to accepting state by consuming one D
    assert(a_advance_automata(&a, 'D') == 1);
    assert(a.current_state == 1);

    Lookahead la;
    la.has = 1;
    la.character = 'D';

    int can = a_lookahead_process(&a, &la);
    fprintf(ofile, "lookahead='D' from state 1 => %d (expected 1)\n", can);
    assert(can == 1);

    la.character = 'X';
    can = a_lookahead_process(&a, &la);
    fprintf(ofile, "lookahead='X' from state 1 => %d (expected 0)\n", can);
    assert(can == 0);
}

// a_process
static void test_process(){
    Automata a;
    automata_build(&a);

    fprintf(ofile, "\n[TEST] a_process\n");

    Lookahead la;

    // Case 1: current='D', lookahead='D' => can continue
    la.has = 1;
    la.character = 'D';

    int r = a_process(&a, 'D', &la);
    fprintf(ofile, "process(c='D', la='D') => %s (%d), current_state=%d\n",
            res_name(r), r, a.current_state);
    assert(r == A_CONTINUE);

    // Case 2: current='D', lookahead='X' => cannot continue, but accepting => ACCEPT
    la.character = 'X';
    r = a_process(&a, 'D', &la);
    fprintf(ofile, "process(c='D', la='X') => %s (%d), current_state=%d\n",
            res_name(r), r, a.current_state);
    assert(r == A_ACCEPT);

    // Case 3: fail: current='X' not accepted
    a_reset_automata(&a);
    la.character = 'D';
    r = a_process(&a, 'X', &la);
    fprintf(ofile, "process(c='X', la='D') => %s (%d), current_state=%d\n",
            res_name(r), r, a.current_state);
    assert(r == A_FAIL);
}

// a_reset_automata
static void test_reset(){
    Automata a;
    automata_build(&a);

    fprintf(ofile, "\n[TEST] a_reset_automata\n");
    assert(a_advance_automata(&a, 'D') == 1);
    fprintf(ofile, "before reset, current_state=%d\n", a.current_state);

    a_reset_automata(&a);
    fprintf(ofile, "after reset, current_state=%d (expected %d)\n", a.current_state, a.initial_state);
    assert(a.current_state == a.initial_state);
}


int main(int argc, char *argv[]) {
    (void)argc; (void)argv; // parameters.

    ofile = stdout;
    ofile = set_output_test_file(MODARGSTESTLOGFILENAME);

    // printf("Starting tests for Module automata...\n");
    fprintf(ofile, "Starting tests for Module automata...\n");

    test_mapping_alphabet();
    test_next_and_advance();
    test_accepting_state();
    test_lookahead_process();
    test_process();
    test_reset();

    printf("Finished tests for Module automata...\n\n");
    fprintf(ofile, "Finished tests for Module automata...\n\n");

    fclose(ofile);
    return 0;

}
