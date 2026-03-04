/*
 * tests/test_module_sra.c
 *
 * Unit tests for SRA action execution helpers.
 */

#include "test_module_sra.h"

FILE *ofile = NULL;

typedef struct SraFixture {
    SRA sra;
    Automata *automata;
    Stack *stack;
    Action **action_table;
    Symbol *alphabet;
    Rule *rules;
    int num_states;
    int num_symbols;
} SraFixture;

static void initialize_action_table(SraFixture *fixture) {
    for (int i = 0; i < fixture->num_states; ++i) {
        for (int j = 0; j < fixture->num_symbols; ++j) {
            fixture->action_table[i][j].type = ACT_ERROR;
            fixture->action_table[i][j].state = -1;
            fixture->action_table[i][j].rule = NULL;
        }
    }
}

static SraFixture create_fixture(int num_states, int num_symbols) {
    SraFixture fixture;
    memset(&fixture, 0, sizeof(SraFixture));

    fixture.num_states = num_states;
    fixture.num_symbols = num_symbols;

    fixture.alphabet = (Symbol *)calloc((size_t)num_symbols, sizeof(Symbol));
    fixture.rules = (Rule *)calloc(2, sizeof(Rule));
    fixture.action_table = (Action **)malloc((size_t)num_states * sizeof(Action *));

    assert(fixture.alphabet != NULL);
    assert(fixture.rules != NULL);
    assert(fixture.action_table != NULL);

    for (int i = 0; i < num_symbols; ++i) {
        fixture.alphabet[i].id = i;
        fixture.alphabet[i].name = NULL;
        fixture.alphabet[i].is_terminal = (i < 2) ? 1 : 0;
    }

    for (int i = 0; i < num_states; ++i) {
        fixture.action_table[i] = (Action *)malloc((size_t)num_symbols * sizeof(Action));
        assert(fixture.action_table[i] != NULL);
    }
    initialize_action_table(&fixture);

    fixture.stack = create_stack(32);
    assert(fixture.stack != NULL);

    fixture.automata = a_create_automata(num_symbols, num_states, fixture.action_table, fixture.alphabet, 0);
    assert(fixture.automata != NULL);

    fixture.sra.automata = fixture.automata;
    fixture.sra.stack = fixture.stack;

    return fixture;
}

static void destroy_fixture(SraFixture *fixture) {
    if (!fixture) {
        return;
    }

    if (fixture->automata) {
        a_destroy_automata(fixture->automata);
    }
    if (fixture->stack) {
        destroy_stack(fixture->stack);
    }
    if (fixture->action_table) {
        for (int i = 0; i < fixture->num_states; ++i) {
            free(fixture->action_table[i]);
        }
        free(fixture->action_table);
    }
    free(fixture->alphabet);
    free(fixture->rules);
}

static void test_check_table_returns_expected_action(void) {
    SraFixture fixture = create_fixture(3, 3);

    fixture.action_table[0][0].type = ACT_SHIFT;
    fixture.action_table[0][0].state = 1;

    Symbol input_symbol = {.id = 0, .name = NULL, .is_terminal = 1};
    Action action = check_table(&fixture.sra, 0, input_symbol);

    assert(action.type == ACT_SHIFT);
    assert(action.state == 1);

    destroy_fixture(&fixture);
}

static void test_sra_shift_pushes_symbol_and_state(void) {
    SraFixture fixture = create_fixture(2, 2);

    Symbol input_symbol = {.id = 1, .name = NULL, .is_terminal = 1};
    sra_shift(&fixture.sra, 7, input_symbol);

    StackItem *top = stack_peek(fixture.stack);
    assert(top != NULL);
    assert(top->symbol_id == 1);
    assert(top->state == 7);

    destroy_fixture(&fixture);
}

static void test_sra_reduce_pops_rhs_and_pushes_lhs_goto(void) {
    SraFixture fixture = create_fixture(4, 3);
    int rhs_values[] = {0, 1};

    fixture.rules[0].id = 0;
    fixture.rules[0].lhs = 2;
    fixture.rules[0].rhs = rhs_values;
    fixture.rules[0].rhs_length = 2;

    fixture.action_table[0][2].type = ACT_SHIFT;
    fixture.action_table[0][2].state = 2;

    assert(stack_push(fixture.stack, -1, 0) == 1);
    assert(stack_push(fixture.stack, 0, 1) == 1);
    assert(stack_push(fixture.stack, 1, 3) == 1);

    sra_reduce(&fixture.sra, &fixture.rules[0]);

    StackItem *top = stack_peek(fixture.stack);
    assert(top != NULL);
    assert(top->symbol_id == 2);
    assert(top->state == 2);
    assert(fixture.stack->top == 1);

    destroy_fixture(&fixture);
}

static void test_sra_action_shift_case(void) {
    SraFixture fixture = create_fixture(3, 3);

    fixture.action_table[0][0].type = ACT_SHIFT;
    fixture.action_table[0][0].state = 1;

    assert(stack_push(fixture.stack, -1, 0) == 1);

    Symbol input_symbol = {.id = 0, .name = NULL, .is_terminal = 1};
    int result = sra_action(&fixture.sra, input_symbol);

    StackItem *top = stack_peek(fixture.stack);
    assert(result == ACT_SHIFT);
    assert(top != NULL);
    assert(top->symbol_id == 0);
    assert(top->state == 1);

    destroy_fixture(&fixture);
}

static void test_sra_action_reduce_case(void) {
    SraFixture fixture = create_fixture(4, 3);
    int rhs_values[] = {0};

    fixture.rules[1].id = 1;
    fixture.rules[1].lhs = 2;
    fixture.rules[1].rhs = rhs_values;
    fixture.rules[1].rhs_length = 1;

    fixture.action_table[1][1].type = ACT_REDUCE;
    fixture.action_table[1][1].rule = &fixture.rules[1];
    fixture.action_table[0][2].type = ACT_SHIFT;
    fixture.action_table[0][2].state = 2;

    assert(stack_push(fixture.stack, -1, 0) == 1);
    assert(stack_push(fixture.stack, 0, 1) == 1);

    Symbol input_symbol = {.id = 1, .name = NULL, .is_terminal = 1};
    int result = sra_action(&fixture.sra, input_symbol);

    StackItem *top = stack_peek(fixture.stack);
    assert(result == ACT_REDUCE);
    assert(top != NULL);
    assert(top->symbol_id == 2);
    assert(top->state == 2);

    destroy_fixture(&fixture);
}

static void test_sra_action_accept_and_error_cases(void) {
    SraFixture fixture = create_fixture(3, 2);

    fixture.action_table[2][1].type = ACT_ACCEPT;

    assert(stack_push(fixture.stack, -1, 2) == 1);
    Symbol accept_symbol = {.id = 1, .name = NULL, .is_terminal = 1};
    int accept_result = sra_action(&fixture.sra, accept_symbol);
    assert(accept_result == ACT_ACCEPT);

    stack_clear(fixture.stack);
    assert(stack_push(fixture.stack, -1, 1) == 1);
    Symbol error_symbol = {.id = 0, .name = NULL, .is_terminal = 1};
    int error_result = sra_action(&fixture.sra, error_symbol);
    assert(error_result == ACT_ERROR);

    destroy_fixture(&fixture);
}

int main(void) {
    ofile = stdout;

    printf("Starting tests for Module SRA...\n");

    test_check_table_returns_expected_action();
    test_sra_shift_pushes_symbol_and_state();
    test_sra_reduce_pops_rhs_and_pushes_lhs_goto();
    test_sra_action_shift_case();
    test_sra_action_reduce_case();
    test_sra_action_accept_and_error_cases();

    printf("Finished tests for Module SRA...\n\n");
    return 0;
}
