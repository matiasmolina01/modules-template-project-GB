/*
 * -----------------------------------------------------------------------------
 * init.c 
 *
 * Usage:
 *     Called from the main file or test modules to manipulate the datastructures on the GlobalContext.
 *
 * Status:
 *     Final.
 *
 * Author: Franco Olano
 * -----------------------------------------------------------------------------
 */

#include "./global_context.h"


/*
    Initializes the automata respones as default state (A_CONTINUE)
    Parameters:
            int responses[]: empty array
            int num: number of elements to be initialized in the array 
*/
void gc_init_responses(int responses[], int num){
    for(int i = 0; i < num; i++){
        responses[i] = A_CONTINUE;
    }
}


/*
    Define automatas using macros delared in language.h
    Parameters:
            automata_list: list of automatas to be created
*/
void  gc_init_automatas(Automata* automata_list[]){
    
	keyword_transition_table();
    identifiers_transition_table();
    numbers_transition_table();
    special_char_transition_table();
    operators_transition_table();
    literals_transition_table();

    automata_list[OPERATOR_AUTOMATA] = a_create_automata(NUM_SYMBOLS_OPERATOR_AUTOMATA, NUM_STATES_OPERATOR_AUTOMATA,
                                                 NUM_SYMBOLS_OPERATOR_AUTOMATA, operators_alphabet, operators_transitions,
                                                 START_STATE, START_STATE, operators_accepting_states, CAT_OPERATOR);

    automata_list[SPECIAL_CHAR_AUTOMATA] = a_create_automata(NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA, NUM_STATES_SPECIAL_CHAR_AUTOMATA,
                                                 NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA, special_char_alphabet, special_char_transitions,
                                                 START_STATE, START_STATE, special_accepting_states, CAT_SPECIALCHAR);

    automata_list[NUMBERS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_NUMBERS_AUTOMATA, NUM_STATES_NUMBERS_AUTOMATA,
                                                 NUM_SYMBOLS_NUMBERS_AUTOMATA, numbers_alphabet, numbers_transitions,
                                                 START_STATE, START_STATE, numbers_accepting_state, CAT_NUMBER);

    automata_list[KEYWORDS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_KEYWORD_AUTOMATA, NUM_STATES_KEYWORD_AUTOMATA,
                                                 NUM_SYMBOLS_KEYWORD_AUTOMATA, keyword_alphabet, keyword_transitions,
                                                 START_STATE, START_STATE, keyword_accepting_states, CAT_KEYWORD);

    automata_list[LITERALS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_LITERALS_AUTOMATA, NUM_STATES_LITERALS_AUTOMATA,
                                                 NUM_SYMBOLS_LITERALS_AUTOMATA, literals_alphabet, literals_transitions,
                                                 START_STATE, START_STATE, literals_accepting_state, CAT_LITERAL);

    automata_list[IDENTIFIERS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_IDENTIFIERS_AUTOMATA, NUM_STATES_IDENTIFIERS_AUTOMATA,
                                                 NUM_SYMBOLS_IDENTIFIERS_AUTOMATA, identifiers_alphabet, identifiers_transitions,
                                                 START_STATE, START_STATE, identifiers_accepting_state, CAT_IDENTIFIER);

}

/*
    Initilizes the GlobalContext datastructure.
    Parameters:
        arguments: previously initialized arguments data structure

    Returns: 
        initialized GlobalContext pointer.
*/
GlobalContext* gc_init(Arguments* arguments) {
    GlobalContext *global_context = (GlobalContext*) malloc(sizeof(GlobalContext));
    if(global_context == NULL) e_error_report(800);

    global_context->arguments = arguments;

    TokenList *token_list = tl_token_list_init();

    global_context->token_list = token_list;

    for (int i = 0; i < NUM_AUTOMATAS; ++i) {
        global_context->automatas_list[i] = NULL;
    }
    gc_init_automatas(global_context->automatas_list);

    Input* input = i_create();

    global_context->input = input;

    i_open_input(global_context->input, arguments->input_path);

    gc_init_responses(global_context->automata_responses, NUM_AUTOMATAS);
    
    return global_context;
}


/*
    Util function to free the memory space of the global context
    Parameters:
        global_context: GlobalContext to be destroyed.
*/
void gc_destroy(GlobalContext* global_context){
    for(int i = 0; i < NUM_AUTOMATAS; i++){
        a_destroy_automata(global_context->automatas_list[i]);
    }
	i_close_input(global_context->input);
    tl_token_list_destroy(global_context->token_list);
    t_token_destroy(global_context->current_token);
    args_free(global_context->arguments);
    free(global_context);
}