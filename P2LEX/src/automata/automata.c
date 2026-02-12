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
        col --> return the column of the transition table of the automata.
        -1 --> failure or not found in alphabet

*/
int a_mapping_alphabet(Automata *automata, char c){
    if(automata == NULL) return -1; // if the automata is null, return failure
    int limit; // to indicate the limit of the alphabet to check...
    if(automata->numsymbols > 0){ // ... if numsymbols is greater than 0, we use it as limit
        limit = automata->numsymbols;
    } else{ // ... otherwise we use numcols.
        limit = automata->numcols; 
    }

    for(int i = 0; i < limit; i++){
        if(automata->alphabet[i].name == c){ // if we find the character in the alphabet, return the column
            int col = automata->alphabet[i].col;
            if(col < 0 || col >= automata->numcols){ // if the column is invalid, return failure
                return -1;
            }
            return col; // return the column of the transition table of the automata
        }
    }
    return -1; // not found in the alphabet
}

/*
    Function to compute the next state of the transition between current state and the character. 

    Returns:
        1 --> the new state after the transition
        -1 --> invalid state or failure.
        0 --> (no transition)

*/
int a_next_state(Automata *automata, char c){
    if(automata == NULL) return -1; // if the automata is null, return failure
    
    int cr = automata->current_state; // current state
    if(cr < 0 || cr >= automata->numstates) return -1; // if the current state is invalid, return failure

    int col = a_mapping_alphabet(automata, c); // get the column of the transition table of the automata for the character
    if(col < 0) return 0; // if the character is not in the alphabet, return failure

    int new_state = automata->transitions[cr][col]; // get the new state from the transition table of the automata

    if(new_state < 0){ // if the new state is invalid, return failure (dead or no transition)
        return 0;
    } else if(new_state >= automata->numstates){
        return -1; // if the new state is invalid, return failure
    }

    return new_state; // return the new state after the transition
}


/*
    Function to check if the state is an accepting state or not.

    Returns:
        1 --> if the state is an accepting state.
        0 --> if the state is not an accepting state.
*/
int a_is_accepting_state(Automata *automata, int state){
    if(automata == NULL) return -1; // if the automata is null, return failure
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
        0 (a_next_state returns 0) --> if the character is not accepted and the automata has not advanced to the next state.
*/
int a_advance_automata(Automata *automata, char c){
    if(automata == NULL) return 0; // if the automata is null, return failure
    
    int new_state = a_next_state(automata, c); // get the new state from the transition table of the automata for the character
    if(new_state > 0){
        automata->current_state = new_state; // advance to the new state
        return 1; // character accepted and automata advanced to the next state
    } else{
        return new_state; // character not accepted and automata has not advanced to the next state (0 or -1)
    }

}

/*
    Function to processes the lookahead character of the automata.

    Returns:
        1 --> if the next state of the automaton with the input lookahead is accepting
        0 --> if is not accepting
*/
int a_lookahead_process(Automata *automata, Lookahead *lookahead){
    if (automata == NULL) return 0;
    if (lookahead == NULL) return 0;
    if (lookahead->has == 0) return 0;  // no lookahead => cannot continue

    int col = a_mapping_alphabet(automata, lookahead->character); // get the column of the transition table of the automata for the lookahead character
    if (col < 0) return 0; // if the lookahead character is not in the alphabet...

    int cs = automata->current_state; // current state
    if(cs < 0 || cs >= automata->numstates) return 0; // if the current state is invalid

    int nw = automata->transitions[cs][col]; // get the next state...
    if(nw < 0 || nw >= automata->numstates) return 0; // ... if the next state is invalid, return 0

    return 1; // the next state is valid, return 1
}
/*
    Function to processes one transition step of the automaton. Consumes current_char, checks if it can continue 
    with lookahead_char, and determines whether to continue, accept, or fail.

    Returns:
        1 (A_ACCEPT) --> automaton can continue
        0 (A_CONTINUE) --> current character consumed, cannot continue, but the current state is accepting
        -1 (A_FAIL) --> cannot consume the current character or stopped in a non-accepting state.
*/
int a_process(Automata *automata, char c, Lookahead *lookahead){
    if(automata == NULL || lookahead == NULL) return A_FAIL; // if the automata or lookahead is null, return failure

    int adv = a_advance_automata(automata, c); // try to advance the automata with the current character
    if(adv != 0){
        return A_FAIL; // if the character is not accepted, return fail
    }




    
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



