/*
 * -----------------------------------------------------------------------------
 * error_handler.c 
 *
 * Usage:
 *     Called from all the other modules or test modules to handle errors.
 *
 * Status:
 *     Requirements-compliant version
 *
 * Author: Alex Ruiz
 * -----------------------------------------------------------------------------
 */

#include "./error_handler.h"

void e_error_handler() {
#ifdef TRACE_ERROR_HANDLER
	printf(MSG_ERROR_HANDLER_DEV);
#endif
}

void e_error_report(ErrorCode code) {
#ifdef TRACE_ERROR_REPORT
	for (int i = 0; i < sizeof(error_table) / sizeof(Error); i++) {
		if (error_table[i].code == code) {
			printf(MSG_ERROR_FORMAT, 
					error_table[i].code, 
					error_table[i].step, 
					error_table[i].message);
			return;
		}
	}
	printf(MSG_UNKNOWN_ERROR, code);
#endif
}
