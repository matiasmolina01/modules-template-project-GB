/*
 * -----------------------------------------------------------------------------
 * scanner.c 
 *
 * Usage:
 * Called from the main file to create a token list.
 * Uses the Automata module and Token Handler module as helpers.
 *
 * Status:
 * Final.
 *
 * Author: Franco Olano
 * -----------------------------------------------------------------------------
 */

#include "./scanner.h"
#include <stdio.h> // Added purely for the debug printfs



/*
    Calls the a_process function for each automata which had a A_CONTINUE response
    Parameters:
            automata_list: array of automata pointer which are going to be updated
            automata_responses: array to be filled with the automata responses
            current_char: char to be processed by the automata
            lookahead: char to be analyzed by the automata to see if it could be processed later
*/
void s_run_automatas(Automata** automata_list, int*automata_responses, char current_char, char lookahead_char, int has_lookahead){

    Lookahead *lookahead = malloc(sizeof(Lookahead));
    if(!lookahead) e_error_report(ERR_S_LOOKAHEAD_OUT_OF_BOUNDS);
	lookahead->has = has_lookahead;
    lookahead->character = lookahead_char;

#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_run__;
    c_count_local_init(&__cnt_local_s_run__);
    COUNTGEN(1, __cnt_local_s_run__);
#endif

    // DEBUG: Print what is being sent to the automatas    
    for(int i = 0; i < NUM_AUTOMATAS; i++){
        if(automata_responses[i] == A_CONTINUE) {
#ifdef COUNTCONFIG
            COUNTCOMP(1, __cnt_local_s_run__);
#endif
            automata_responses[i] = a_process(automata_list[i], current_char, lookahead);
            // DEBUG: Print the response from the automata
#ifdef COUNTCONFIG
            COUNTGEN(1, __cnt_local_s_run__);
#endif
        }
    }
    free(lookahead);
}

/*
    Util function to check if a lexeme is a separator
    Parameters:
        lexeme: char*
        separators: list of separators
        separator_num: number of separators
*/
int s_is_separator(char* lexeme, char separators[], int separator_num){
    for(int i = 0; i < separator_num; i++){
        if(*lexeme == separators[i]) return IS_SEPARATOR;
    }
    return NO_SEPARATOR;
}


/*
    Creates a new token and sets it to the current_token variable.
    Reset Automatas.
    Reset automata responses.
    Parameter:
        global_context: GlobalContext with input information (line, col) and current token
*/
void s_reset_initial_state(GlobalContext* global_context){
    global_context->current_token = t_token_create(global_context->input->line_number, global_context->input->column);

#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_reset__;
    c_count_local_init(&__cnt_local_s_reset__);
    COUNTGEN(1, __cnt_local_s_reset__); /* token create */
#endif

    for(int i = 0; i < NUM_AUTOMATAS; i++){
        a_reset_automata(global_context->automatas_list[i]);
#ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_s_reset__); /* automata reset */
#endif
    }

    gc_init_responses(global_context->automata_responses, NUM_AUTOMATAS);
}

/*
    Function to process the token for a given category.
    Updates the token category and adds it to the final token list.
    Finally sets new current token and reset automata.
    Parameters:
        global_context: global context with token and token list
        category: one of the valid token categories 
*/
void s_process_token(GlobalContext* global_context, TokenCategory category){
    char separators[SEPARATOR_NUM] = SEPARATORS;
    if(s_is_separator(global_context->current_token->lexeme, separators, SEPARATOR_NUM) == NO_SEPARATOR){
#ifdef COUNTCONFIG
        count_local_t __cnt_local_s_process__;
        c_count_local_init(&__cnt_local_s_process__);
        COUNTCOMP(1, __cnt_local_s_process__); /* separator check -> not separator */
#endif
        t_token_update_category(global_context->current_token, category);
        tl_token_list_add(global_context->token_list, *global_context->current_token);
#ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_s_process__); /* token accepted and added */
#endif
    }

    // Creates new token and resets automatas
    s_reset_initial_state(global_context);
}

/*
    Function to accept a Token given that an automata accepted it
    Parameters:
            global_context: global context with automata and token list
            automata_idx: index of the automata (on the automata list) accepting the Token
*/
void s_accept_token(GlobalContext* global_context, int automata_idx){
    Automata * accepted_automata = global_context->automatas_list[automata_idx];

	int st = accepted_automata->current_state;

    TokenCategory category = accepted_automata->accept[st].category;

#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_accept__;
    c_count_local_init(&__cnt_local_s_accept__);
    COUNTGEN(1, __cnt_local_s_accept__); /* acceptance event */
#endif

    s_process_token(global_context, category);
}


/*
    Function to reject a Token given that all automatas rejected it
    Parameters:
            global_context: global context with automata and token list
*/
void s_reject_token(GlobalContext* global_context){
#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_reject__;
    c_count_local_init(&__cnt_local_s_reject__);
    COUNTGEN(1, __cnt_local_s_reject__); /* reject event */
#endif
    s_process_token(global_context, (TokenCategory) CAT_NONRECOGNIZED);
}


/*
    Checks the automata responses after processing a character.
    Needs to accept a token if there is an automata which accepted the lexeme
    or reject if every automata failed to process the character (had no valid transitions or in dead state).
    Continue processing the same token token otherwise.
    Parameters:
        global_context: Global Context of the program
        automata_responses: array of automata responses.

*/
void s_check_responses(GlobalContext* global_context){
#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_check__;
    c_count_local_init(&__cnt_local_s_check__);
#endif
    int token_status = CURRENT_TOKEN_FAIL;
    int count_continue = 0;
    int automata_accepted_idx = -1;

    for(int i = 0; i < NUM_AUTOMATAS; i++){
        switch(global_context->automata_responses[i]){

            case A_CONTINUE:
            count_continue++;
#ifdef COUNTCONFIG
            COUNTCOMP(1, __cnt_local_s_check__);
#endif
            break;

            case A_ACCEPT:
            token_status = CURRENT_TOKEN_ACCEPTED;
            automata_accepted_idx = i;
#ifdef COUNTCONFIG
            COUNTCOMP(1, __cnt_local_s_check__);
#endif
            break;
        } 
    }

    if(count_continue > 0) return;

    switch(token_status){
        case CURRENT_TOKEN_FAIL:
        s_reject_token(global_context);
        break;

        case CURRENT_TOKEN_ACCEPTED:
        s_accept_token(global_context, automata_accepted_idx);
        break;
    }
}


/*
    Obtains the lookahead from the input and checks wether there is a next character
    Parameters:
            GlobalContext: global context with input datastructure
            lookahead: lookahead's pointer
            has_lookahead: has lookahead property variable's pointer
*/
void s_get_lookahead(GlobalContext* global_context, char*lookahead, int* has_lookahead){
    *lookahead = i_read_char(global_context->input);
    
#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_look__;
    c_count_local_init(&__cnt_local_s_look__);
    COUNTGEN(1, __cnt_local_s_look__); /* got lookahead */
#endif

    if (*lookahead == NULL){
        *has_lookahead = NO_LOOKAHEAD;
    } else {
    }
}


/*
    Implements scanner main functionality

    Parameters:
        GlobalContext*: previously created global context
*/
void s_scanner(GlobalContext* global_context) {
    // INITIAL CONFIGURATION

#ifdef COUNTCONFIG
    count_local_t __cnt_local_s_scan__;
    c_count_local_init(&__cnt_local_s_scan__);
    COUNTGEN(1, __cnt_local_s_scan__); /* scanner entry */
#endif

        // Initial configuration of automata responses

        s_reset_initial_state(global_context);

        // Initial configuration of current char and lookahead
        char current_char, lookahead;
        int has_lookahead = HAS_LOOKAHEAD;
        
        current_char = i_read_char(global_context->input);
    #ifdef COUNTCONFIG
        COUNTIO(1, __cnt_local_s_scan__); /* read initial char */
    #endif

        t_token_append_char(global_context->current_token, current_char);
    #ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_s_scan__); /* appended char to token */
    #endif

    // END OF INITIAL CONFIGURATION

    // MAIN LOOP: until file is completely processed
    while(global_context->input->is_eof == NO_EOF){
        s_get_lookahead(global_context, &lookahead, &has_lookahead);

        s_run_automatas(global_context->automatas_list, global_context->automata_responses, current_char, lookahead, has_lookahead);

        s_check_responses(global_context);


        t_token_append_char(global_context->current_token, lookahead);
#ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_s_scan__); /* appended lookahead char */
#endif


        current_char = lookahead;
#ifdef COUNTCONFIG
        COUNTGEN(1, __cnt_local_s_scan__); /* loop iteration */
#endif
        
    }
}