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
    Function used by next_state to map the character and get the column to use in the matrix for the input c:

    Returns:
        1 --> return the column of the transition table of the automata.
        -1 --> failure.

*/
int a_mapping_alphabet(Automata *automata, char c){
    // TODO
    return 1;
}

/*
    Function to compute the next state of the transition between current state and the character. 

    Returns:
        1 --> the new state after the transition
        -1 --> invalid state or failure.

*/
int a_next_state(Automata *automata, char c){
    return 1;
}


/*
    Function to check if the state is an accepting state or not.

    Returns:
        1 --> if the state is an accepting state.
        0 --> if the state is not an accepting state.
*/
int a_is_accepting_state(Automata *automata, int state){
    if(automata->accept[state].flag == 1){
        return 1;
    }
    return 0;
}

/*
    Function to advance the automata with a given character from scanner. The function checks if the character 
    is accepted by the automata, and if it is, it advances to the next state. If the character is not accepted, 
    it does not advance to the next state.

    Returns:
        1 --> if the character is accepted and the automata has advanced to the next state and the new state is inside current state.
        0 --> if the character is not accepted and the automata has not advanced to the next state.
*/
int a_advance_automata(Automata *automata, char c){
    // TODO
    return 1;
}

/*
    Function to advance the automata with a given character from scanner. The function checks if the character 
    is accepted by the automata, and if it is, it advances to the next state. If the character is not accepted, 
    it does not advance to the next state.

    Returns:
        1 --> 
        0 --> 
*/
int a_process(Automata *automata, char c, Lookahead *lookahead){
    if (!automata->current_state) { // if the current state is invalid, return fail
        return A_FAIL;
    }

    if(!a_advance_automata(automata, c)){ // if the character is not accepted, return fail
        return A_FAIL;
    }

    if(a_is_accepting_state(automata, automata->current_state)){ // if the new state is accepting, return accept
        return A_ACCEPT;
    }

    // falta poner A_CONTINUE.

    
    // TODO
    return A_FAIL;
}

/*
    Function called from the scanner to reset the automata to the initial state.
*/
void a_reset_automata(Automata *automata){
    automata->current_state = automata->initial_state; // reset to initial state
}



