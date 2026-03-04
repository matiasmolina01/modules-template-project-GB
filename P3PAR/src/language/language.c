/*
 * -----------------------------------------------------------------------------
 * language.c 
 *
 * Usage:
 *     Implement the functions to load the language.txt into the Language data structures
 *
 * Status:
 *     Finished - all functionalities work.
 *
 * 
 * Author: [Franco Olano Melo]
 * -----------------------------------------------------------------------------
 */

#include "./language.h"

/* Helper function that reads lines until a valid data line is found, stopping at new sections or EOF. 
 * Returns 1 if a line is populated, 0 if EOF or a new section is reached. */
int get_next_valid_line(FILE *file, char *line) {
    long pos;
    while (1) {
        pos = ftell(file);
        if (!fgets(line, MAX_LINE_LEN, file)) {
            return 0; // EOF reached
        }
        if (line[0] == '[') {
            fseek(file, pos, SEEK_SET); // Rewind to start of section header
            return 0; // Next section reached
        }
        if (line[0] == '\n' || line[0] == '\r') {
            continue; // Skip empty lines
        }
        return 1; // Valid data line found
    }
}

/* Helper function to construct a single Symbol struct from a text line. 
 * Returns a pointer to the newly allocated Symbol. */
Symbol* create_symbol(char *line, Language *lang) {
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
    Symbol *sym = malloc(sizeof(Symbol));
    
    sscanf(line, FMT_SYMBOL, &sym->id, name, type);
    sym->name = strdup(name);
    sym->is_terminal = (strcmp(type, STR_TERMINAL) == 0) ? 1 : 0;
    
    if (!sym->is_terminal) {
        lang->num_nonterminals++;
    }
    return sym;
}

/* Parses the symbols section from the file and populates the Language structure array. */
void parse_symbols(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    int capacity = DEFAULT_CAPACITY;
    lang->symbols = malloc(capacity * sizeof(Symbol*));

    while (get_next_valid_line(file, line)) {
        if (lang->num_symbols >= capacity) {
            capacity *= 2;
            lang->symbols = realloc(lang->symbols, capacity * sizeof(Symbol*));
        }
        lang->symbols[lang->num_symbols++] = create_symbol(line, lang);
    }
}

/* Helper function to construct a single Rule struct from a text line. 
 * Returns a pointer to the newly allocated Rule. */
Rule* create_rule(char *line) {
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
    return rule;
}

/* Parses the rules section from the file and populates the Language structure array. */
void parse_rules(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    int capacity = DEFAULT_CAPACITY;
    lang->rules = malloc(capacity * sizeof(Rule*));

    while (get_next_valid_line(file, line)) {
        if (lang->num_rules >= capacity) {
            capacity *= 2;
            lang->rules = realloc(lang->rules, capacity * sizeof(Rule*));
        }
        lang->rules[lang->num_rules++] = create_rule(line);
    }
}

/* Helper function to construct a single Action struct based on the parsed values. 
 * Returns the constructed Action struct by value. */
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

/* Processes a single text line to allocate and return an array of Actions for one state. 
 * Returns a pointer to the array of Action structs. */
Action* create_state_actions(char *line, Language *lang) {
    Action *state_actions = malloc(lang->num_symbols * sizeof(Action));
    char *ptr = line;
    int read_chars = 0;
    char act_type;
    int act_state, act_rule;
    int sym_idx = 0;

    while (sym_idx < lang->num_symbols && 
           sscanf(ptr, " %c-%d-%d%n", &act_type, &act_state, &act_rule, &read_chars) == 3) {
        state_actions[sym_idx] = create_action(act_type, act_state, act_rule, lang);
        sym_idx++;
        ptr += read_chars;
    }
    
    while(sym_idx < lang->num_symbols) {
        state_actions[sym_idx] = create_action(CHAR_ERROR, 0, 0, lang);
        sym_idx++;
    }
    return state_actions;
}

/* Parses the actions section from the file and populates the Language SRA matrix. */
void parse_actions(FILE *file, Language *lang) {
    char line[MAX_LINE_LEN];
    int capacity = DEFAULT_CAPACITY;
    lang->action_table = malloc(capacity * sizeof(Action*));
    lang->num_states = 0;

    while (get_next_valid_line(file, line)) {
        if (lang->num_states >= capacity) {
            capacity *= 2;
            lang->action_table = realloc(lang->action_table, capacity * sizeof(Action*));
        }
        lang->action_table[lang->num_states++] = create_state_actions(line, lang);
    }
}

/* Main function that coordinates the parsing of the entire language file. 
 * Returns a pointer to the fully populated Language structure. */
Language* get_language(const char* language_file_path) {
    FILE *file = fopen(language_file_path, READ_MODE);
    if (!file) return NULL;

    Language *lang = calloc(1, sizeof(Language));
    char line[MAX_LINE_LEN];

    // Read headers and dispatch to corresponding parsers
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, SEC_SYMBOLS, strlen(SEC_SYMBOLS) - 1) == 0) {
            parse_symbols(file, lang);
        } else if (strncmp(line, SEC_START, strlen(SEC_START) - 1) == 0) {
            if (get_next_valid_line(file, line)) {
                lang->start_symbol = atoi(line);
            }
        } else if (strncmp(line, SEC_RULES, strlen(SEC_RULES) - 1) == 0) {
            parse_rules(file, lang);
        } else if (strncmp(line, SEC_ACTIONS, strlen(SEC_ACTIONS) - 1) == 0) {
            parse_actions(file, lang);
        }
    }

    fclose(file);
    return lang;
}

/* Frees all dynamically allocated memory associated with the Language symbols, returning nothing. */
void free_symbols(Language *lang) {
    if (lang->symbols != NULL) {
        for (int i = 0; i < lang->num_symbols; i++) {
            if (lang->symbols[i] != NULL) {
                if (lang->symbols[i]->name != NULL) {
                    free(lang->symbols[i]->name);
                }
                free(lang->symbols[i]);
            }
        }
        free(lang->symbols);
        lang->symbols = NULL;
    }
}

/* Frees all dynamically allocated memory associated with the Language rules, returning nothing. */
void free_rules(Language *lang) {
    if (lang->rules != NULL) {
        for (int i = 0; i < lang->num_rules; i++) {
            if (lang->rules[i] != NULL) {
                if (lang->rules[i]->rhs != NULL) {
                    free(lang->rules[i]->rhs);
                }
                free(lang->rules[i]);
            }
        }
        free(lang->rules);
        lang->rules = NULL;
    }
}

/* Frees all dynamically allocated memory associated with the Language action table, returning nothing. */
void free_actions(Language *lang) {
    if (lang->action_table != NULL) {
        for (int i = 0; i < lang->num_states; i++) {
            if (lang->action_table[i] != NULL) {
                free(lang->action_table[i]);
            }
        }
        free(lang->action_table);
        lang->action_table = NULL;
    }
}

/* Frees all dynamically allocated memory associated with the Language structure, returning nothing. */
void free_language(Language *lang) {
    if (lang == NULL) {
        return;
    }

    free_symbols(lang);
    free_rules(lang);
    free_actions(lang);

    free(lang);
}