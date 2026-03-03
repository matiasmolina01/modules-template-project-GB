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

/* Helper function to construct a single Action struct based on the parsed characters and IDs. */
Action create_action(char act_type, int act_state, int act_rule, Language *lang) {
    Action act;
    act.state = act_state;
    act.rule = NULL;

    if (act_type == CHAR_SHIFT) {
        act.type = ACT_SHIFT;
    } else if (act_type == CHAR_REDUCE) {
        act.type = ACT_REDUCE;
        act.rule = lang->rules[act_rule];
    } else if (act_type == CHAR_ACCEPT) {
        act.type = ACT_ACCEPT;
    } else {
        act.type = ACT_ERROR;
    }

    return act;
}

/* Processes a single text line to allocate and return an array of Actions for one state. */
Action* parse_action_line(char *line, Language *lang) {
    Action *state_actions = malloc(lang->num_symbols * sizeof(Action));
    char *ptr = line;
    int read_chars = 0;
    char act_type;
    int act_state, act_rule;
    int sym_idx = 0;

    // Read formatted actions until the line ends or we hit the symbol count limit
    while (sym_idx < lang->num_symbols && 
           sscanf(ptr, " %c-%d-%d%n", &act_type, &act_state, &act_rule, &read_chars) == 3) {
        
        state_actions[sym_idx] = create_action(act_type, act_state, act_rule, lang);
        
        sym_idx++;
        ptr += read_chars;
    }
    
    // Fill any missing trailing symbols in the matrix row with ACT_ERROR
    while(sym_idx < lang->num_symbols) {
         state_actions[sym_idx] = create_action(CHAR_ERROR, 0, 0, lang);
         sym_idx++;
    }

    return state_actions;
}

/* Main loop that reads the [ACTIONS] section and builds the SRA Action table. */
void parse_actions(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    int capacity = DEFAULT_CAPACITY;
    
    lang->action_table = malloc(capacity * sizeof(Action*));
    lang->num_states = 0;

    while (fgets(line, sizeof(line), file) && line[0] != '[') {
        if (line[0] == '\n' || line[0] == '\r') continue;

        if (lang->num_states >= capacity) {
            capacity *= 2;
            lang->action_table = realloc(lang->action_table, capacity * sizeof(Action*));
        }

        lang->action_table[lang->num_states++] = parse_action_line(line, lang);
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