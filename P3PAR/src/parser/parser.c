/*
 * -----------------------------------------------------------------------------
 * parser.c 
 *
 * Usage:
 *     Called from the global context module to parse TokenList using the SRA.
 *
 * Status:
 *     In progress.
 *
 * Author: Anna Vasileva
 * -----------------------------------------------------------------------------
 */

#include "./parser.h"

Parser* parser_create(SRA* sra, TokenList* tokens){
    if(!sra || !tokens) return NULL;

    Parser* p = malloc(sizeof(Parser));
    if(!p) return NULL;

    p->SRA = sra;
    p->token = tokens;

    return p;
}

void parser_destroy(Parser* parser){
    if(!parser) return;
    free(parser);
}

Symbol* parser_token_to_symbol(Token token, Language *language)
{
    
    for(int i = 0; i < language->num_symbols; i++){
        if(strcmp(token.lexeme, language->symbols[i]->name) == 0)
            return language->symbols[i];
    }

    return NULL;
}

char* get_name_operation(int action){
    switch(action){
        case ACT_REDUCE:
            return ACT_REDUCE_NAME;
        case ACT_SHIFT:
            return ACT_SHIFT_NAME;
        case ACT_ACCEPT:
            return ACT_ACCEPT_NAME;
        case ACT_ERROR:
            return ACT_ERROR_NAME;
        default:
            return ACT_ERROR_NAME;
    }
}

int parser_run(Parser* parser, Language* language, FILE *output_file){
    if(!parser || !parser->SRA || !parser->token || !language) return PARSE_ERROR;

    int current_input_token = 0;

    TokenNode* node = parser->token->head;
    while(1){
        printf("TOP: %d\n", parser->SRA->stack->top);

        Symbol* sym = NULL;
        if(node != NULL){
            Token* tok = &node->token;
            sym = parser_token_to_symbol(*tok, language);
            if(sym == NULL){
                return ACT_ERROR;
            }
        } else {
            sym = language->symbols[0];
            if(sym == NULL){
                return ACT_ERROR;
            }
        }

        Action action = sra_get_next_action(parser->SRA, *sym);

        o_output_handler(output_file, current_input_token, parser->SRA->stack, get_name_operation(action.type),
            parser->SRA->automata->current_state, language, parser->token);
        
        sra_do_action(parser->SRA, *sym, action);
        switch(action.type){
            case ACT_SHIFT:
                if(node != NULL){
                    node = node->next;
                    current_input_token++;
                }
                break;

            case ACT_REDUCE:
                continue;

            case ACT_ACCEPT:
            case ACT_ERROR:
                return action.type;

            default:
                return ACT_ERROR;
        }

    }
}