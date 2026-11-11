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

//#define	DEBUG_ON
#include "debug.h"


#define INPUT_TERM_W		'w'
#define INPUT_TERM_S		's'
#define INPUT_TERM_A		'a'
#define INPUT_TERM_D		'd'
#define INPUT_TERM_Q		'q'


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
	DEBUG1s1c("key = ", ch);

	// @formatter:off
	switch (ch) {
		case INPUT_TERM_W:	return RAW_W;
		case INPUT_TERM_S:	return RAW_S;
		case INPUT_TERM_A:	return RAW_A;
		case INPUT_TERM_D:	return RAW_D;
		case INPUT_TERM_Q:	return RAW_Q;
		default: return RAW_UNKNOWN;
	}
		// @formatter:on
}

