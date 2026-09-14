/*
 * render.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "render_term.h"

static void terminal_draw_at(int x, int y, int type) {
	printf("\x1b[%d;%dH", x, y);
	if (type == CELL_WALL) {
		putc('#', stdout);
	}
	if (type == CELL_VOID) {
		putc('@', stdout);
	}
	fflush(stdout);
}

static void terminal_clean_screen() {
	ANSI_CLEAR_SCREEN;
}

static void terminal_set_non_canonical_mode() {
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

static void terminal_set_canonical_mode() {
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

static void terminal_cleanup() {
	terminal_clean_screen();
	terminal_set_canonical_mode();
}

// @formatter:off
RenderAPI terminal_create(){
	RenderAPI api = {
			.init = terminal_set_non_canonical_mode,
			.draw_cell = terminal_draw_at,
			.render_frame = NULL,
			.cleanup = terminal_cleanup,
			.clean_screen = terminal_clean_screen
	};
	return api;
}
// @formatter:on

