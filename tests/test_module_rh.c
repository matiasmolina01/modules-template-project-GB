/*
 * -----------------------------------------------------------------------------
 * test_module_recursivity_handler.c // test_module_rh.c
 *
 * Unit tests for module_recursivity_handler.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_recursivity_handler functionality test
 * 
 * Author: Àlex Ruiz
 * Date: 25-01-2026
 * 
 * -----------------------------------------------------------------------------
 */

#include "../tests/test_module_rh.h"

FILE *ofile = NULL; //output handler for tests

int cl_classifier(const char *input_path, const char *output_path){
	(void)input_path;
	(void)output_path;
	return 0;
}

static void log_status(const char *msg){
	if(ofile){
		fprintf(ofile, "%s\n", msg);
	}
}

void test_ifdef_ifndef(void){
	MacroTable *table = st_init();
	assert(table != NULL);
	assert(st_define(table, "A", "1") == ST_OK);

	RHStack *stack = rh_stackcreate(8);
	assert(stack != NULL);

	RHProcessMacro pm;

	//#ifdef A (exists) => active
	rh_handle_ifdef_directive("A", table, stack, 0, &pm);
	assert(pm.process == 1);
	assert(rh_stack_is_active(stack) == 1);

	//nested #ifdef B (missing) => inactive, overall inactive
	rh_handle_ifdef_directive("B", table, stack, 0, &pm);
	assert(pm.process == 0);
	assert(rh_stack_is_active(stack) == 0);

	//nested #ifndef B while parent inactive => stays inactive
	rh_handle_ifdef_directive("B", table, stack, 1, &pm);
	assert(pm.process == 0);
	assert(rh_stack_is_active(stack) == 0);

	//Pop innermost (#ifndef B)
	assert(rh_handle_endif(stack) == 1);
	assert(rh_stack_is_active(stack) == 0); //still inactive because #ifdef B inactive
	//Pop #ifdef B (inactive)
	assert(rh_handle_endif(stack) == 1);
	assert(rh_stack_is_active(stack) == 1); //back to active due to #ifdef A

	//Pop #ifdef A (active)
	assert(rh_handle_endif(stack) == 1);
	assert(rh_stack_is_active(stack) == 1); //empty stack treated as active
	rh_stackfree(stack);
	st_destroy(table);

	log_status("test_ifdef_ifndef passed");
}

int main(int argc, char *argv[]){
	(void)argc; (void)argv;

	ofile = set_output_test_file(MODRHTESTLOGFILENAME);
	if(ofile == NULL){
		printf("Failed to open test log file\n");
		return 1;
	}

	fprintf(ofile, "Starting tests for module_recursivity_handler...\n\n");

	test_ifdef_ifndef();

	fprintf(ofile, "\nAll tests passed for module_recursivity_handler.\n");

	if(ofile != stdout){
		fclose(ofile);
	}
	return 0;
}
