// /* 
//  * tests/test_module_automata.c
//  * 
//  * This module is responsible to return the action of an automata given a state and a symbol.
//  *  
//  * 
//  * This module has to manipulate launch.json to set the program arguments for running/debugging. 
//  * So the contributors of this module have to have "ownership" of launch.json file too.
//  * 
//  * It includes the test cases of the all functions into this module:
//  * - a_create_automata
//  * - a_get_action
//  * - a_reset_automata
//  * - a_destroy_automata
//  *
//  * The constants and configurations of the tests are defined in the header file test_module_automata.h.
//  * 
//  * Team: GB
//  * 
//  * Update 1: To comprobe all functions into this module.
//  * Author: Matias Molina
//  * Date: 13/02/2026
//  * 
//  * Update 2: The modifications to LAB3
//  * Author: Matias Molina
//  * Date: 02/03/2026
// */
// #include "../tests/test_module_automata.h"


// static void report(const char *name, int ok) {
//     printf("%-48s : %s\n", name, ok ? "PASS" : "FAIL");
// }

// // function to create a action table for testing
// static Action **build_table(int numstates, int numsymbols){
//     Action **t = (Action**)malloc((size_t)numstates * sizeof(Action*)); // allocate memory for the action table
//     if (!t) return NULL;

//     for (int s = 0; s < numstates; s++) {
//         t[s] = (Action*)malloc((size_t)numsymbols * sizeof(Action));
//         if (!t[s]) {
//             for (int k = 0; k < s; k++) free(t[k]);
//             free(t);
//             return NULL;
//         }
//         for (int c = 0; c < numsymbols; c++) {
//             t[s][c].type = ACT_ERROR;
//             t[s][c].state = -1;
//             t[s][c].rule = NULL;
//         }
//     }

//     // set a couple actions
//     t[0][0].type = ACT_SHIFT;
//     t[0][0].state = 1;

//     t[1][2].type = ACT_ACCEPT;

//     return t;
// }

// // in the lab, must be done by parser or language modules.
// static void free_table(Action **t, int numstates) {
//     if (!t) return;
//     for (int s = 0; s < numstates; s++) free(t[s]);
//     free(t);
// }

// static void test_create_and_basic_fields(void){
//     int numstates = 2, numsymbols = 3;
//     Action **table = build_table(numstates, numsymbols);
//     report("build_table != NULL", table != NULL);
//     if (!table) return;

//     // alphabet can be dummy for this test (only pointer storage is tested)
//     Symbol *alphabet = (Symbol*)0x1; // sentinel non-NULL pointer

//     Automata *a = a_create_automata(numsymbols, numstates, table, alphabet, 0);
//     report("a_create_automata != NULL", a != NULL);
//     if (!a) { free_table(table, numstates); return; }

//     report("numstates set", a->numstates == numstates);
//     report("numsymbols set", a->numsymbols == numsymbols);
//     report("initial_state set", a->initial_state == 0);
//     report("current_state == initial_state", a->current_state == a->initial_state);
//     report("action_table pointer set", a->action_table == table);

//     a_destroy_automata(a);
//     free_table(table, numstates);
// }

// static void test_get_action(void)
// {
//     int numstates = 2, numsymbols = 3;
//     Action **table = build_table(numstates, numsymbols);
//     if (!table) { report("build_table for get_action", 0); return; }

//     Symbol *alphabet = (Symbol*)0x1;
//     Automata *a = a_create_automata(numsymbols, numstates, table, alphabet, 0);
//     if (!a) { report("create for get_action", 0); free_table(table, numstates); return; }

//     Action act;

//     act = a_get_action(a, 0, 0);
//     report("get_action SHIFT", act.type == ACT_SHIFT && act.state == 1);

//     act = a_get_action(a, 1, 2);
//     report("get_action ACCEPT", act.type == ACT_ACCEPT);

//     act = a_get_action(a, 0, 1);
//     report("get_action default ERROR", act.type == ACT_ERROR);

//     act = a_get_action(a, -1, 0);
//     report("get_action invalid state -> ERROR", act.type == ACT_ERROR);

//     act = a_get_action(a, 0, 99);
//     report("get_action invalid symbol -> ERROR", act.type == ACT_ERROR);

//     a_destroy_automata(a);
//     free_table(table, numstates);
// }

// static void test_reset(void)
// {
//     int numstates = 2, numsymbols = 3;
//     Action **table = build_table(numstates, numsymbols);
//     if (!table) { report("build_table for reset", 0); return; }

//     Symbol *alphabet = (Symbol*)0x1;
//     Automata *a = a_create_automata(numsymbols, numstates, table, alphabet, 0);
//     if (!a) { report("create for reset", 0); free_table(table, numstates); return; }

//     a->current_state = 1;
//     a_reset_automata(a);
//     report("reset sets current_state to initial_state", a->current_state == a->initial_state);

//     a_destroy_automata(a);
//     free_table(table, numstates);
// }

// int main(int argc, char *argv[]) {
//     printf("\nStarting tests for Module DFA (LR action table)...\n");
//     test_create_and_basic_fields();
//     test_get_action();
//     test_reset();
//     printf("Finished tests for Module DFA.\n\n");
//     return 0;
// }
