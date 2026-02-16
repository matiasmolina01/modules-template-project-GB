/*
 * -----------------------------------------------------------------------------
 * language.c 
 *
 * Usage:
 *     Called from the automata module or test modules to check what type of character is it.
 *
 * Status:
 *     Initial development — logic to handle language is not yet implemented.
 *
 * 
 * Author: []
 * -----------------------------------------------------------------------------
 */



#include "./language.h"

int keyword_accepting_states[NUM_STATES_KEYWORD_AUTOMATA] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1

    
};

int special_accepting_states[NUM_STATES_SPECIAL_CHAR_AUTOMATA] = {
    0, 1
};

int operators_accepting_states[NUM_STATES_OPERATOR_AUTOMATA] = {
    0, 1
};


int numbers_accepting_state[NUM_STATES_NUMBERS_AUTOMATA] = {
    0, 1
};

int identifiers_accepting_state[NUM_STATES_IDENTIFIERS_AUTOMATA] = {
    0, 1
};

int literals_accepting_state[NUM_STATES_LITERALS_AUTOMATA] = {
    0, 0, 1
};

AlphabetSymbol keyword_alphabet[NUM_SYMBOLS_KEYWORD_AUTOMATA] = {
    {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
    {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
    {'k',10}, {'l',11}, {'m',12}, {'n',13}, {'o',14},
    {'p',15}, {'q',16}, {'r',17}, {'s',18}, {'t',19},
    {'u',20}, {'v',21}, {'w',22}, {'x',23}, {'y',24},
    {'z',25}
};

AlphabetSymbol special_char_alphabet[NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA] = {
    {';', 0}, {',', 1}, {'(', 2}, {')', 3},
    {'{', 4}, {'}', 5}, {'[', 6}
};

AlphabetSymbol numbers_alphabet[NUM_SYMBOLS_NUMBERS_AUTOMATA] = {
    {'0', 0}, {'1',1}, {'2', 2} ,{'3', 3}, {'4', 4},{'5', 5},
    {'6', 6},{'7', 7}, {'8', 8}, {'9', 9} 
};

AlphabetSymbol literals_alphabet[NUM_SYMBOLS_LITERALS_AUTOMATA] = {
    // a-z → columnas 0–25
    {'a', 0},  {'b', 1},  {'c', 2},  {'d', 3},  {'e', 4},
    {'f', 5},  {'g', 6},  {'h', 7},  {'i', 8},  {'j', 9},
    {'k',10},  {'l',11},  {'m',12},  {'n',13},  {'o',14},
    {'p',15},  {'q',16},  {'r',17},  {'s',18},  {'t',19},
    {'u',20},  {'v',21},  {'w',22},  {'x',23},  {'y',24},
    {'z',25},

    // A-Z → columnas 26–51
    {'A',26}, {'B',27}, {'C',28}, {'D',29}, {'E',30},
    {'F',31}, {'G',32}, {'H',33}, {'I',34}, {'J',35},
    {'K',36}, {'L',37}, {'M',38}, {'N',39}, {'O',40},
    {'P',41}, {'Q',42}, {'R',43}, {'S',44}, {'T',45},
    {'U',46}, {'V',47}, {'W',48}, {'X',49}, {'Y',50},
    {'Z',51},

    // 0–9 → columnas 52–61
    {'0',52}, {'1',53}, {'2',54}, {'3',55}, {'4',56},
    {'5',57}, {'6',58}, {'7',59}, {'8',60}, {'9',61},

    // " → columna 62
    {'"',62}
};


AlphabetSymbol identifiers_alphabet[NUM_SYMBOLS_IDENTIFIERS_AUTOMATA] = {
    // a-z → columnas 0–25
    {'a', 0},  {'b', 1},  {'c', 2},  {'d', 3},  {'e', 4},
    {'f', 5},  {'g', 6},  {'h', 7},  {'i', 8},  {'j', 9},
    {'k',10},  {'l',11},  {'m',12},  {'n',13},  {'o',14},
    {'p',15},  {'q',16},  {'r',17},  {'s',18},  {'t',19},
    {'u',20},  {'v',21},  {'w',22},  {'x',23},  {'y',24},
    {'z',25},

    // A-Z → columnas 26–51
    {'A',26}, {'B',27}, {'C',28}, {'D',29}, {'E',30},
    {'F',31}, {'G',32}, {'H',33}, {'I',34}, {'J',35},
    {'K',36}, {'L',37}, {'M',38}, {'N',39}, {'O',40},
    {'P',41}, {'Q',42}, {'R',43}, {'S',44}, {'T',45},
    {'U',46}, {'V',47}, {'W',48}, {'X',49}, {'Y',50},
    {'Z',51},

    // 0–9 → columnas 52–61
    {'0',52}, {'1',53}, {'2',54}, {'3',55}, {'4',56},
    {'5',57}, {'6',58}, {'7',59}, {'8',60}, {'9',61}
};

AlphabetSymbol operators_alphabet[NUM_SYMBOLS_OPERATOR_AUTOMATA] = {
    {'+', 0}, {'-', 1}, {'*', 2}, {'/', 3}
};

int keyword_transitions[NUM_STATES_KEYWORD_AUTOMATA][NUM_SYMBOLS_KEYWORD_AUTOMATA];
int identifiers_transitions[NUM_STATES_IDENTIFIERS_AUTOMATA][NUM_SYMBOLS_IDENTIFIERS_AUTOMATA];
int numbers_transitions[NUM_STATES_NUMBERS_AUTOMATA][NUM_SYMBOLS_NUMBERS_AUTOMATA];
int special_char_transitions[NUM_STATES_SPECIAL_CHAR_AUTOMATA][NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA];
int operators_transitions[NUM_STATES_OPERATOR_AUTOMATA][NUM_SYMBOLS_OPERATOR_AUTOMATA];
int literals_transitions[NUM_STATES_LITERALS_AUTOMATA][NUM_SYMBOLS_LITERALS_AUTOMATA];

char mapping_input_char(char c) {

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 'S' ; // LETTER
    }

    if (c >= '0' && c <= '9') {
        return 'D'; // DIGIT
    }
    return c;
    

    // return DEAD_TRANSITION; // símbolo no válido
}




void keyword_transition_table(){

     for (int i = 0; i < NUM_STATES_KEYWORD_AUTOMATA; i++) {
        for (int j = 0; j < NUM_SYMBOLS_KEYWORD_AUTOMATA; j++) {
            keyword_transitions[i][j] = DEAD_TRANSITION;
        }
        // a->accept[i].flag = 0;
        // a->accept[i].category[0] = '\0';
    }

    keyword_transitions[0][2] = 18;
    keyword_transitions[0][4] = 3;
    keyword_transitions[0][7] = 1;
    keyword_transitions[0][11] = 12;
    keyword_transitions[0][15] = 22;
    keyword_transitions[0][16] = 7;

    keyword_transitions[1][5] = 2;
    keyword_transitions[1][9] = 22;

    keyword_transitions[3][8] = 4;

    keyword_transitions[4][12] = 5;

    keyword_transitions[5][4] = 6;

    keyword_transitions[7][6] = 8;

    keyword_transitions[8][7] = 9;

    keyword_transitions[9][8] = 10;

    keyword_transitions[10][4] = 11;

    keyword_transitions[12][4] = 13;

    keyword_transitions[13][13] = 14;

    keyword_transitions[14][14] = 15;

    keyword_transitions[15][11] = 16;

    keyword_transitions[16][9] = 17;

    keyword_transitions[18][6] = 19;

    keyword_transitions[19][0] = 20;

    keyword_transitions[20][11] =21;

    keyword_transitions[22][13] = 23;
}



void identifiers_transition_table(){

     for (int i = 0; i < NUM_STATES_IDENTIFIERS_AUTOMATA; i++) {
        for (int j = 0; j < NUM_SYMBOLS_IDENTIFIERS_AUTOMATA; j++) {
            identifiers_transitions[i][j] = DEAD_TRANSITION;
        }
        // a->accept[i].flag = 0;
        // a->accept[i].category[0] = '\0';
    }
    //Esto es con el compressed alphabet
        // //Hay dos entradas en el alphabeto que son L de letter que mapea a 0 y D de digit que mapea a 1
        // a->transitions[0][0] = 1;
      

        // a->transitions[1][0] = 1;
        // a->transitions[1][1] = 1;

        //Sabemos que primeras 54 columnas (27 posiciones para minusculas y 27 para mayúsculas) son para letras
        for(int i = 0; i < 54; i++){
             identifiers_transitions[0][i] = 1;
        }
        //Primeras 54 para letras y 10 restantes para digitos, todos transicionan a el mismo estado
        for(int i = 0; i < 64; i++){
            identifiers_transitions[1][i] = 1;
        }

        






    }

    

void numbers_transition_table(){

     for (int i = 0; i < NUM_STATES_NUMBERS_AUTOMATA; i++) {
        for (int j = 0; j < NUM_SYMBOLS_NUMBERS_AUTOMATA; j++) {
            numbers_transitions[i][j] = DEAD_TRANSITION;
        }
        // a->accept[i].flag = 0;
        // a->accept[i].category[0] = '\0';
    }
        //Esto para la tabla compressed de alphabet
        //Hay una entradas en el alphabeto que es D de digit que mapea a 0
        // a->transitions[0][0] = 1;
        // a->transitions[1][0] = 1;

        for(int i= 0; i <10;i++){
            numbers_transitions[0][i] = 1;
            numbers_transitions[1][i] = 1;
        }
    }



void special_char_transition_table(){

    for (int i = 0; i < NUM_STATES_SPECIAL_CHAR_AUTOMATA; i++) {
        for (int j = 0; j < NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA; j++) {
           special_char_transitions[i][j] = DEAD_TRANSITION;
        }
        // a->accept[i].flag = 0;
        // a->accept[i].category[0] = '\0';
    }


    special_char_transitions[0][0] = 1;
    special_char_transitions[0][1] = 1;
    special_char_transitions[0][2] = 1;
    special_char_transitions[0][3] = 1;
    special_char_transitions[0][4] = 1;
    special_char_transitions[0][5] = 1;
    special_char_transitions[0][6] = 1;
    
}



void operators_transition_table(){

    for (int i = 0; i < NUM_STATES_OPERATOR_AUTOMATA; i++) {
        for (int j = 0; j < NUM_SYMBOLS_OPERATOR_AUTOMATA; j++) {
            operators_transitions[i][j] = DEAD_TRANSITION;
        }
        // a->accept[i].flag = 0;
        // a->accept[i].category[0] = '\0';
    }
    operators_transitions[0][0] = 1;
    operators_transitions[0][1] = 1;
    operators_transitions[0][2] = 1;
    operators_transitions[0][3] = 1;
}



void literals_transition_table(){

    for (int i = 0; i < NUM_STATES_LITERALS_AUTOMATA; i++) {
        for (int j = 0; j < NUM_SYMBOLS_LITERALS_AUTOMATA; j++) {
            literals_transitions[i][j] = DEAD_TRANSITION;
        }
        // a->accept[i].flag = 0;
        // a->accept[i].category[0] = '\0';
    }

    //Aquí tenemos tres entradas en la compressed table en las que si "L" se mapea a 0 si "D" se mapea a 1 y si """ a 2
    // a->transitions[0][2] = 1;

    // a->transitions[1][0] = 1;
    // a->transitions[1][1] = 1;
    // a->transitions[1][2] = 1;
    literals_transitions[0][2] = 1;
    for(int i= 0 ; i < NUM_SYMBOLS_LITERALS_AUTOMATA;i++){
        if(i < NUM_SYMBOLS_LITERALS_AUTOMATA - 1){
             literals_transitions[1][i] = 1;
        }
        else{
            literals_transitions[1][i] = 2;
        }
    }

}

