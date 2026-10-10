/*
 * key_bindings.c
 *
 *  Created on: Sep 20, 2026
 *      Author: bomber
 */

#include "snake_key_bindings.h"

// @formatter:off
const SNAKE_CMD snake_key_bindings[] = {
		[KEY_API_a]		=	SNK_CMD_LEFT,
		[KEY_API_d]		=	SNK_CMD_RIGHT,
		[KEY_API_w]		=	SNK_CMD_UP,
		[KEY_API_s]		=	SNK_CMD_DOWN,
		[KEY_API_NONE]	=	SNK_CMD_NONE
};
// @formatter:on


