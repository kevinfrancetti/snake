/*
 * input_term.c
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <unistd.h>
#include "input_api.h"
#include "input_term.h"

static Key term_get_key() {
	char ch;
	read(STDIN_FILENO, &ch, 1);
	fprintf(stderr, "term_get_key(): %c \n", ch);

	// @formatter:off
	switch (ch) {
		case 'w': return KEY_UP;
		case 'a': return KEY_LEFT;
		case 's': return KEY_DOWN;
		case 'd': return KEY_RIGHT;
		case 'q': return KEY_QUIT;
			break;
		default: return KEY_NONE;
			break;
	}
		// @formatter:on

	return KEY_NONE; //TODO ripigliati pezzo di merda
}

InputApi input_term_create(void) {
	InputApi api = { .get_key = term_get_key };
	return api;
}

