/*
 * input_term_binding_to_api.c
 *
 *
 *  Created on: Oct 6, 2026
 *      Author: bomber
 */




#include "input_term_native.h"
#include "input_term_binding_to_api.h"

// @formatter:off
static const INPUT_KEY_API input_term_native_keys_to_api_keys[] = {
		[RAW_UNKNOWN]	= KEY_API_NONE,
		[RAW_W]			= KEY_API_W,
		[RAW_A]			= KEY_API_A,
		[RAW_S]			= KEY_API_S,
		[RAW_D]			= KEY_API_D,
		[RAW_Q]			= KEY_API_Q
};
// @formatter:on


static INPUT_KEY_API get_key_raw_to_api(){
	RAW_KEY rawKey = input_term_native_get_key();
	return input_term_native_keys_to_api_keys[rawKey];
}

InputApi input_term_bindinig_create(void) {
	InputApi api = {
			.get_key = get_key_raw_to_api,
			.init = input_term_set_raw_mode,
			.restore = input_term_set_canonical_mode
	};
	return api;
}



