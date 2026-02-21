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
#ifdef COUNTCONFIG
			count_local_t __cnt_local_err__;
			c_count_local_init(&__cnt_local_err__);
#endif
			int __written_err__ = printf(MSG_ERROR_FORMAT,
					error_table[i].code,
					error_table[i].step,
					error_table[i].message);
#ifdef COUNTCONFIG
			if (__written_err__ > 0) COUNTIO(__written_err__, __cnt_local_err__);
			COUNTGEN(1, __cnt_local_err__);
#endif
			return;
		}
	}
#ifdef COUNTCONFIG
	count_local_t __cnt_local_err_unknown__;
	c_count_local_init(&__cnt_local_err_unknown__);
#endif
	int __written_err_unknown__ = printf(MSG_UNKNOWN_ERROR, code);
#ifdef COUNTCONFIG
	if (__written_err_unknown__ > 0) COUNTIO(__written_err_unknown__, __cnt_local_err_unknown__);
	COUNTGEN(1, __cnt_local_err_unknown__);
#endif
#endif
}
