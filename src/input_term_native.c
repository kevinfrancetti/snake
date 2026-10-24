/*
 * input_term:native.c
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */


#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "input_term_native.h"


#define INPUT_TERM_w		'w'
#define INPUT_TERM_s		's'
#define INPUT_TERM_a		'a'
#define INPUT_TERM_d		'd'
#define INPUT_TERM_q		'q'


/**
 * Some explanations
 *
 */
void input_term_set_raw_mode(){
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

void input_term_set_canonical_mode(){
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

RAW_KEY input_term_native_get_key() {
	char ch;
	read(STDIN_FILENO, &ch, 1);
	fprintf(stderr, "term_get_key(): %c \n", ch);

	// @formatter:off
	switch (ch) {
		case INPUT_TERM_w:	return RAW_w;
		case INPUT_TERM_s:	return RAW_s;
		case INPUT_TERM_a:	return RAW_a;
		case INPUT_TERM_d:	return RAW_d;
		case INPUT_TERM_q:	return RAW_q;
		default: return RAW_UNKNOWN;
	}
		// @formatter:on
}

