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
    Function to advance the automata with a given character from scanner. The function checks if the character 
    is accepted by the automata, and if it is, it advances to the next state. If the character is not accepted, 
    it does not advance to the next state.

    Returns:
        1 --> if the character is accepted and the automata has advanced to the next state and the new state is inside current state.
        0 --> if the character is not accepted and the automata has not advanced to the next state.
*/
int a_advance_automata(Automata *automata, char character){
    return 1;
}
