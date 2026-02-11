#include "./main.h"

// FILE* ofile = NULL; // The output handler for the project run (same variable name as in modules)

int main(int argc, char *argv[]) {
    
    fprintf(stdout, "Starting module alphabet ...\n");
    al_alphabet();
    fprintf(stdout, "Finished module alphabet!!\n\n");
    
    fprintf(stdout, "Starting module automata ...\n");
    // a_automata();
    fprintf(stdout, "Finished module automata!!\n\n");
    
    fprintf(stdout, "Starting module controller ...\n");
    c_controller();
    fprintf(stdout, "Finished module controller!!\n\n");

    fprintf(stdout, "Starting module counter ...\n");
    cnt_counter();
    fprintf(stdout, "Finished module counter!!\n\n");
    
    fprintf(stdout, "Starting module error_handler ...\n");
    e_error_handler();
    fprintf(stdout, "Finished module error_handler!!\n\n");
    
    fprintf(stdout, "Starting module input_handler ...\n");
    i_input_handler();
    fprintf(stdout, "Finished module input_handler!!\n\n");
    
    fprintf(stdout, "Starting module args ...\n");
    // process_arguments(argc, argv);
    fprintf(stdout, "Finished module args!!\n\n");

    fprintf(stdout, "Starting module output_handler ...\n");
    // o_output_handler();
    fprintf(stdout, "Finished module output_handler!!\n\n");

    fprintf(stdout, "Starting module token ...\n");
    t_token();
    fprintf(stdout, "Finished module token!!\n\n");

    fprintf(stdout, "Starting module token_list ...\n");
    tl_token_list();
    fprintf(stdout, "Finished module token_list!!\n\n");

    fprintf(stdout, "All modules executed successfully!\n\n");

    // fclose(ofile); 
    return 0;
}