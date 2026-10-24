/*
 * input_term.h
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_INPUT_TERM_NATIVE_H_
#define INCLUDE_INPUT_TERM_NATIVE_H_

// @formatter:off
typedef enum{
	RAW_UNKNOWN,
	RAW_w,
	RAW_s,
	RAW_a,
	RAW_d,
	RAW_q
}RAW_KEY;
// @formatter:on

void input_term_set_raw_mode();
void input_term_set_canonical_mode();
RAW_KEY input_term_native_get_key();


//InputApi input_term_create(void);

#endif /* INCLUDE_INPUT_TERM_NATIVE_H_ */
