/*
 * input_term.c
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "input_api.h"
#include "input_term.h"


#define INPUT_TERM_UP		'w'
#define INPUT_TERM_DOWN		's'
#define INPUT_TERM_LEFT 	'a'
#define INPUT_TERM_RIGHT	'd'
#define INPUT_TERM_QUIT		'q'


void hi(){
	printf("dbg:\n%s\n%d\n%s\n",  __FILE__, __LINE__, __func__);
}

/**
 * Some explanations
 *
 */
static void input_term_set_raw_mode(){
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

static void input_term_set_canonical_mode(){
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}


static INPUT_KEY_API term_get_key() {
	char ch;
	read(STDIN_FILENO, &ch, 1);
	fprintf(stderr, "term_get_key(): %c \n", ch);

	// @formatter:off
	switch (ch) {
		case INPUT_TERM_UP:		return KEY_API_UP;
		case INPUT_TERM_DOWN:	return KEY_API_DOWN;
		case INPUT_TERM_LEFT:	return KEY_API_LEFT;
		case INPUT_TERM_RIGHT:	return KEY_API_RIGHT;
		case INPUT_TERM_QUIT:	return KEY_API_QUIT;
		default: return KEY_API_NONE;
	}
		// @formatter:on

	return KEY_API_NONE;
}

InputApi input_term_create(void) {
	InputApi api = {
			.get_key = term_get_key,
			.init = input_term_set_raw_mode,
			.restore = input_term_set_canonical_mode};
	return api;
}

