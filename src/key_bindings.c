/*
 * key_bindings.c
 *
 *  Created on: Sep 20, 2026
 *      Author: bomber
 */

#include "key_bindings.h"

// @formatter:off
const ACTION_TYPE key_binding_to_action[] = {
		[KEY_LEFT] = ACTION_LEFT,
		[KEY_RIGHT] = ACTION_RIGHT,
		[KEY_UP] = ACTION_UP,
		[KEY_DOWN] = ACTION_DOWN,
		[KEY_NONE] = ACTION_NONE
};
// @formatter:on


