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
#ifdef COUNTCONFIG
    count_local_t __cnt_local_gc_res__;
    c_count_local_init(&__cnt_local_gc_res__);
#endif
    for(int i = 0; i < num; i++){
        responses[i] = A_CONTINUE;
    }
#ifdef COUNTCONFIG
    COUNTGEN(num, __cnt_local_gc_res__);
#endif
}


/*
    Define automatas using macros delared in language.h
    Parameters:
            automata_list: list of automatas to be created
*/
void  gc_init_automatas(Automata* automata_list[]){
#ifdef COUNTCONFIG
    count_local_t __cnt_local_gc_auto__;
    c_count_local_init(&__cnt_local_gc_auto__);
#endif
    
    automata_list[OPERATOR_AUTOMATA] = a_create_automata(NUM_SYMBOLS_OPERATOR_AUTOMATA, NUM_STATES_OPERATOR_AUTOMATA,
                                                 NUM_SYMBOLS_OPERATOR_AUTOMATA, operators_alphabet, operators_transitions,
                                                 START_STATE, START_STATE, operators_accepting_states, CAT_OPERATOR);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_auto__);
#endif

    automata_list[SPECIAL_CHAR_AUTOMATA] = a_create_automata(NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA, NUM_STATES_SPECIAL_CHAR_AUTOMATA,
                                                 NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA, special_char_alphabet, special_char_transitions,
                                                 START_STATE, START_STATE, special_accepting_states, CAT_SPECIALCHAR);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_auto__);
#endif

    automata_list[NUMBERS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_NUMBERS_AUTOMATA, NUM_STATES_NUMBERS_AUTOMATA,
                                                 NUM_SYMBOLS_NUMBERS_AUTOMATA, numbers_alphabet, numbers_transitions,
                                                 START_STATE, START_STATE, numbers_accepting_state, CAT_NUMBER);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_auto__);
#endif

    automata_list[KEYWORDS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_KEYWORD_AUTOMATA, NUM_STATES_KEYWORD_AUTOMATA,
                                                 NUM_SYMBOLS_KEYWORD_AUTOMATA, keyword_alphabet, keyword_transitions,
                                                 START_STATE, START_STATE, keyword_accepting_states, CAT_KEYWORD);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_auto__);
#endif

    automata_list[LITERALS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_LITERALS_AUTOMATA, NUM_STATES_LITERALS_AUTOMATA,
                                                 NUM_SYMBOLS_LITERALS_AUTOMATA, literals_alphabet, literals_transitions,
                                                 START_STATE, START_STATE, literals_accepting_state, CAT_LITERAL);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_auto__);
#endif

    automata_list[IDENTIFIERS_AUTOMATA] = a_create_automata(NUM_SYMBOLS_IDENTIFIERS_AUTOMATA, NUM_STATES_IDENTIFIERS_AUTOMATA,
                                                 NUM_SYMBOLS_IDENTIFIERS_AUTOMATA, identifiers_alphabet, identifiers_transitions,
                                                 START_STATE, START_STATE, identifiers_accepting_state, CAT_IDENTIFIER);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_auto__);
#endif

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
    if(global_context == NULL) e_error_report(ERR_GC_MEMORY_LEAK);

#ifdef COUNTCONFIG
    count_local_t __cnt_local_gc_init__;
    c_count_local_init(&__cnt_local_gc_init__);
    COUNTGEN(1, __cnt_local_gc_init__); /* allocation */
#endif

    global_context->arguments = arguments;

    TokenList *token_list = tl_token_list_init();

    global_context->token_list = token_list;
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_init__); /* token list init */
#endif

    for (int i = 0; i < NUM_AUTOMATAS; ++i) {
        global_context->automatas_list[i] = NULL;
    }
    gc_init_automatas(global_context->automatas_list);
#ifdef COUNTCONFIG
    /* automata creations are counted inside gc_init_automatas */
    COUNTGEN(1, __cnt_local_gc_init__);
#endif

    Input* input = i_create();

    global_context->input = input;
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_init__); /* input create */
#endif

    i_open_input(global_context->input, arguments->input_path);
#ifdef COUNTCONFIG
    COUNTIO(1, __cnt_local_gc_init__); /* opening input considered IO */
#endif

    gc_init_responses(global_context->automata_responses, NUM_AUTOMATAS);
    
    return global_context;
}


/*
    Util function to free the memory space of the global context
    Parameters:
        global_context: GlobalContext to be destroyed.
*/
void gc_destroy(GlobalContext* global_context){
#ifdef COUNTCONFIG
    count_local_t __cnt_local_gc_destroy__;
    c_count_local_init(&__cnt_local_gc_destroy__);
#endif
    for(int i = 0; i < NUM_AUTOMATAS; i++){
        a_destroy_automata(global_context->automatas_list[i]);
#ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_gc_destroy__);
#endif
    }
	i_close_input(global_context->input);
#ifdef COUNTCONFIG
    COUNTIO(1, __cnt_local_gc_destroy__);
#endif
    tl_token_list_destroy(global_context->token_list);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_destroy__);
#endif
    t_token_destroy(global_context->current_token);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_destroy__);
#endif
    args_free(global_context->arguments);
#ifdef COUNTCONFIG
    COUNTGEN(1, __cnt_local_gc_destroy__);
#endif
    free(global_context);
}