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

Symbol parser_token_to_symbol(Token token)
{
    Symbol sym;

    sym.name = token.lexeme;
    sym.is_terminal = 1;

    if (token.category == CAT_NUMBER)
        sym.id = SYM_NUM;

    else if (token.category == CAT_OPERATOR)
    {
        if (strcmp(token.lexeme, "+") == 0)
            sym.id = SYM_PLUS;

        else if (strcmp(token.lexeme, "*") == 0)
            sym.id = SYM_STAR;
    }

    else if (token.category == CAT_SPECIALCHAR)
    {
        if (strcmp(token.lexeme, "(") == 0)
            sym.id = SYM_LPAREN;

        else if (strcmp(token.lexeme, ")") == 0)
            sym.id = SYM_RPAREN;
    }

    return sym;
}

int parser_run(Parser* parser){
    if(!parser || !parser->SRA || !parser->token) return -1;

    TokenNode* node = parser->token->head;
    
    while(node){
        
        Token* tok = &node->token;
        
        Symbol sym = parser_token_to_symbol(*tok);
        
        int action = sra_action(parser->SRA, sym);
        
        if(action == ACT_SHIFT){
            node = node->next;
        }
        
        else if(action == ACT_REDUCE){
            continue;
        }
        
        else if(action == ACT_ACCEPT){
            return 1;
        }

        else if(action == ACT_ERROR){
            printf("Parser error");
            return -1;
        }
    }

    return 0;
}