/*
 * render_term_test.c
 *
 *  Created on: Oct 4, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "render_factory.h"
//#include "render_term.h" cdeddsdecca


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

int main(){
	input_term_set_raw_mode();

	RenderAPI render = render_create(RENDER_TERMINAL);


	render.clean_screen();
	render.draw_cell(5,6, CELL_PLAYER);


	input_term_set_canonical_mode();

	printf("hi render test\n");
	return 0;
}
