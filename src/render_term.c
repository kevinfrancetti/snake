/*
 * render.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
//#include <ioctl.h>
#include "render_term.h"
//#include "render_styles.h"//TODO

#define CSI					"\x1b["   //Control Sequence Introducer
#define ANSI_CLEAR			CSI "2J"
//#define ANSI_CLEAR_SCREEN printf(CSI "2J")



// @formatter:off
const char styles[CELL_SIZE] = {
		[RENDER_API_EMPTY]	= ' ',
		[CELL_FOOD]			= '@',
		[CELL_PLAYER]		= '#'
};
// @formatter:on

static void render_init(){

}


static void render_term_draw_at(int x, int y, RENDER_API_STYLE type) {
	fprintf(stderr, "X: %d\nY: %d", x, y);
	printf("\x1b[%d;%dH", HEIGHT - y, x);//TODO

	putc(styles[type], stdout);


	fflush(stdout);
}

static void render_term_clean_screen() {
	printf(ANSI_CLEAR);
}


static void render_term_cleanup() {
	render_term_clean_screen();
}

// @formatter:off
RenderAPI terminal_render_create(){
	RenderAPI api = {
			.init = render_init,
			.draw_cell = render_term_draw_at,
			.render_frame = NULL,
			.cleanup = render_term_cleanup,
			.clean_screen = render_term_clean_screen
	};
	return api;
}
// @formatter:on

