/*
 * -----------------------------------------------------------------------------
 * language.c 
 *
 * Usage:
 *     Implement the functions to load the language.txt into the Language data structures
 *
 * Status:
 *     Initial development — logic to handle language is not yet implemented.
 *
 * 
 * Author: [Franco Olano Melo]
 * -----------------------------------------------------------------------------
 */

#include "./language.h"

/* Parses the symbols section from the file and populates the Language structure, returning nothing. */
void parse_symbols(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
    lang->symbols = malloc(DEFAULT_CAPACITY * sizeof(Symbol*));

    while (fgets(line, sizeof(line), file) && line[0] != '[') {
        if (line[0] == '\n') continue;

        Symbol *sym = malloc(sizeof(Symbol));
        sscanf(line, FMT_SYMBOL, &sym->id, name, type);
        
        sym->name = strdup(name);
        sym->is_terminal = (strcmp(type, STR_TERMINAL) == 0) ? 1 : 0;
        
        if (!sym->is_terminal) {
            lang->num_nonterminals++;
        }
        lang->symbols[lang->num_symbols++] = sym;
    }
}

/* Parses the rules section from the file and populates the Language structure, returning nothing. */
void parse_rules(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    lang->rules = malloc(DEFAULT_CAPACITY * sizeof(Rule*));

    while (fgets(line, sizeof(line), file) && line[0] != '[') {
        if (line[0] == '\n') continue;

        Rule *rule = malloc(sizeof(Rule));
        rule->rhs = malloc(MAX_RHS_LEN * sizeof(int));
        rule->rhs_length = 0;

        int offset = 0, read_chars = 0;
        sscanf(line, FMT_RULE_HDR, &rule->id, &rule->lhs, &read_chars);
        offset += read_chars;

        int rhs_val;
        while (sscanf(line + offset, FMT_RHS_ITEM, &rhs_val, &read_chars) == 1) {
            rule->rhs[rule->rhs_length++] = rhs_val;
            offset += read_chars;
        }

        lang->rules[lang->num_rules++] = rule;
    }
}

/* Parses the actions matrix from the file and populates the Language structure, returning nothing. */
void parse_actions(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    lang->action_table = malloc(DEFAULT_CAPACITY * sizeof(Action*));

    while (fgets(line, sizeof(line), file) && line[0] != '[') {
        if (line[0] == '\n') continue;

        Action *state_actions = malloc(lang->num_symbols * sizeof(Action));
        int offset = 0, read_chars = 0;
        char act_type;
        int act_state, act_rule;
        int sym_idx = 0;

        while (sscanf(line + offset, FMT_ACTION, &act_type, &act_state, &act_rule, &read_chars) == 3) {
            state_actions[sym_idx].state = act_state;
            state_actions[sym_idx].rule = NULL;

            if (act_type == CHAR_SHIFT) {
                state_actions[sym_idx].type = ACT_SHIFT;
            } else if (act_type == CHAR_REDUCE) {
                state_actions[sym_idx].type = ACT_REDUCE;
                state_actions[sym_idx].rule = lang->rules[act_rule];
            } else if (act_type == CHAR_ACCEPT) {
                state_actions[sym_idx].type = ACT_ACCEPT;
            } else {
                state_actions[sym_idx].type = ACT_ERROR;
            }

            sym_idx++;
            offset += read_chars;
        }
        lang->action_table[lang->num_states++] = state_actions;
    }
}

/* Creates and returns a Language struct by parsing the provided formatted text file path. */
Language* get_language(const char* language_file_path) {
    FILE *file = fopen(language_file_path, READ_MODE);
    if (!file) return NULL;

    Language *lang = calloc(1, sizeof(Language));
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, SEC_SYMBOLS) == 0) {
            parse_symbols(file, lang);
        } else if (strcmp(line, SEC_START) == 0) {
            if (fgets(line, sizeof(line), file)) {
                lang->start_symbol = atoi(line);
            }
        } else if (strcmp(line, SEC_RULES) == 0) {
            parse_rules(file, lang);
        } else if (strcmp(line, SEC_ACTIONS) == 0) {
            parse_actions(file, lang);
        }
    }

    fclose(file);
    return lang;
}