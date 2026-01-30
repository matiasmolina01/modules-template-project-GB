#ifndef MAIN_H
#define MAIN_H
 
#include <stdio.h>
#include <stdbool.h>
#include "./utils_files.h"
#include "./alphabet/alphabet.h"
#include "./automata/automata.h"
#include "./controller/controller.h"
#include "./counter/counter.h"
#include "./error_handler/error_handler.h"
#include "./input_handler/input_handler.h"
#include "./module_args/module_args.h"
#include "./output_handler/output_handler.h"
#include "./token/token.h"
#include "./token_list/token_list.h"

// Output file of project run: either a stdout or a filename with log extension (comment one out)
#define PROJOUTFILENAME "./proj_modules_template.log"
//#define PROJOUTFILENAME "stdout"

extern FILE* ofile; // The output handler for the project run (same variable name as in modules)

#endif // MAIN_H
