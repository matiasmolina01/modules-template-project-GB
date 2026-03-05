/*
 * -----------------------------------------------------------------------------
 * automata.c 
 *
 * Usage:
 *     Called from the controller module or test modules to check what category the word is.
 *
 * Status:
 *     Initial development — logic to handle automata is not yet implemented.
 *
 * Author: Matias Molina
 * -----------------------------------------------------------------------------
 */

#include "./automata.h"

/*
    Function to create an automata with the parameters.

    Returns:
        Automata* --> pointer to the created automata.
        
        NULL --> failure (invalid parameters or memory allocation failure).
*/
Automata* a_create_automata(int numsymbols, int numstates, Action** action_table , Symbol *alphabet){
    // validations for the parameters...
	if(numstates <= 0 || numstates > MAXLEN) return NULL;
    if(numsymbols <= 0 || numsymbols > MAXCOLS) return NULL;
    if(action_table == NULL) return NULL;
    if(alphabet == NULL) return NULL;
    if(INITIAL_STATE < 0 || INITIAL_STATE >= numstates) return NULL; 

    // AUTOMATA CREATION
    Automata *a = (Automata*)malloc(sizeof(Automata)); // allocate memory for the automata

	if(a == NULL) return NULL; // check if memory allocation was successful

    memset(a, 0, sizeof(*a)); // initialize all fields to 0
    a->numstates = numstates;
    a->numsymbols = numsymbols;
    // a->initial_state = initial_state;
	a->alphabet = alphabet;
    a->current_state = INITIAL_STATE; // set the current state to the initial state
    a->action_table = action_table;

    return a; // return the created automata
}

/*
    Function to get the action of the automata given a state (row) and a symbol id (column).

    Returns:
        Action --> the action of the automata for the given state and symbol id.
        error_action --> failure (invalid parameters).
*/
Action a_get_action(Automata *automata, int state, int symbol_id){
    Action error_action = {ACT_ERROR, -1, NULL}; // default error action
    if(automata == NULL) return error_action;
    if(state < 0 || state >= automata->numstates) return error_action;
    if(symbol_id < 0 || symbol_id >= automata->numsymbols) return error_action;
    
    return automata->action_table[state][symbol_id];
}

/*
    Function to reset the automata to the initial state. (current state = intial state)

    Return:
        A_EMPTY_ERROR --> if the automata is NULL (empty).
        0 --> if the automata was successfully reset.
*/
int a_reset_automata(Automata *automata, int initial_state){
    if(automata == NULL) return A_EMPTY_ERROR;
    automata->current_state = initial_state;
    return 0; // success
}

/*
    Function to free the memory of the automata.

    Returns:
        A_EMPTY_ERROR --> if the automata is NULL (empty).
        0 --> if the automata was successfully destroyed.
*/
int a_destroy_automata(Automata *automata){
    if(automata == NULL) return A_EMPTY_ERROR;
    free(automata);
    return 0;
}