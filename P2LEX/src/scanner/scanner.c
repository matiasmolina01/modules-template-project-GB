/*
 * -----------------------------------------------------------------------------
 * scanner.c 
 *
 * Usage:
 *     Called from the main file to create a token list.
 *      Uses the Automata module and Token Handler module as helpers.
 *
 * Status:
 *     Final.
 *
 * Author: Franco Olano
 * -----------------------------------------------------------------------------
 */

#include "./scanner.h"

/*
    Initializes the automata respones as default state (A_CONTINUE)
    Parameters:
            int responses[]: empty array
            int num: number of elements to be initialized in the array 
*/
void s_init_responses(int responses[], int num){
    for(int i = 0; i < num; i++){
        responses[i] = A_CONTINUE;
    }
}

/*
    Calls the a_process function for each automata which had a A_CONTINUE response
    Parameters:
            automata_list: array of automata pointer which are going to be updated
            automata_responses: array to be filled with the automata responses
            current_char: char to be processed by the automata
            lookahead: char to be analyzed by the automata to see if it could be processed later
*/
void s_run_automatas(Automata** automata_list, int*automata_responses, char current_char, char lookahead_char, int has_lookahead){

    Lookahead lookahead = {has_lookahead, lookahead_char};
    
    for(int i = 0; i < NUM_AUTOMATAS; i++){
        if(automata_list[i] == A_CONTINUE)
        automata_responses[i] = a_process(automata_list[i], current_char, &lookahead);
    }
}

/*
    Creates a new token and sets it to the current_token variable
    Parameter:
        global_context: GlobalContext with input information (line, col) and current token
*/
void s_set_new_current_token(GlobalContext* global_context){
    global_context->current_token = t_token_create(global_context->input->line_number, global_context->input->column);
}

/*
    Function to process the token for a given category.
    Updates the token category and adds it to the final token list.
    Parameters:
        global_context: global context with token and token list
        category: one of the valid token categories 
*/
void s_process_token(GlobalContext* global_context, TokenCategory category){
    t_token_update_category(global_context->current_token, category);
    tl_token_list_add(global_context->token_list, *global_context->current_token);
}

/*
    Function to accept a Token given that an automata accepted it
    Parameters:
            global_context: global context with automata and token list
            automata_idx: index of the automata (on the automata list) accepting the Token
*/
void s_accept_token(GlobalContext* global_context, int automata_idx){
    Automata * accepted_automata = global_context->automatas_list[automata_idx];

    TokenCategory category = (TokenCategory) accepted_automata->accept->category;

    s_process_token(global_context, category);
    s_set_new_current_token(global_context);
}


/*
    Function to reject a Token given that all automatas rejected it
    Parameters:
            global_context: global context with automata and token list
*/
void s_reject_token(GlobalContext* global_context){
    s_process_token(global_context, (TokenCategory) CAT_NONRECOGNIZED);
    s_set_new_current_token(global_context);
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
void s_check_responses(GlobalContext* global_context, int* automata_responses){

    int token_status = CURRENT_TOKEN_FAIL;

    for(int i = 0; i < NUM_AUTOMATAS; i++){

        switch(automata_responses[i]){

            case A_ACCEPT:
            token_status = CURRENT_TOKEN_ACCEPTED;
            s_accept_token(global_context, i);
            break;

            case A_CONTINUE:
            token_status = CURRENT_TOKEN_CONTINUE;
            break;
        } 
    }

    if(token_status == CURRENT_TOKEN_FAIL){
        s_reject_token(global_context);
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
    if (*lookahead == NULL){
        *has_lookahead = NO_LOOKAHEAD;
    }
}


/*
    Implements scanner main functionality

    Parameters:
        GlobalContext*: previously created global context
*/
void s_scanner(GlobalContext* global_context) {

    // INITIAL CONFIGURATION

        // Initial configuration of automata responses
        int automata_reponses[NUM_AUTOMATAS];
        s_init_responses(automata_reponses, NUM_AUTOMATAS);

        // Initial configuration of current char and lookahead
        char current_char, lookahead;
        int has_lookahead = HAS_LOOKAHEAD;
        current_char = i_read_char(global_context->input);
        s_get_lookahead(global_context, &lookahead, &has_lookahead);

        // Create first token
        s_set_new_current_token(global_context);
        t_token_append_char(global_context->current_token, current_char);

    // END OF INITIAL CONFIGURATION


    // MAIN LOOP: until file is completely processed
    while(global_context->input->is_eof == NO_EOF){

        s_run_automatas(global_context->automatas_list, automata_reponses, current_char, lookahead, has_lookahead);

        s_check_responses(global_context, automata_reponses);

        t_token_append_char(global_context->current_token, lookahead);

        current_char = lookahead;
        s_get_lookahead(global_context, &lookahead, &has_lookahead);
    
    }

}