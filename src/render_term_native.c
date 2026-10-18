/*
 * render_term_native.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
//#include <ioctl.h>
#include "render_term_native.h"


#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)

#define CSI					"\x1b["   //Control Sequence Introducer
#define ANSI_CLEAR			CSI "2J"
//#define ANSI_CLEAR_SCREEN printf(CSI "2J")



static NativeTermCell term_cell; //terminal cell testing

void render_term_native_set_char(char c) {
	term_cell.c = c;
}

void render_term_native_set_pos(int row, int col) {
	term_cell.pos.row = row;
	term_cell.pos.col = col;
}

void render_term_native_set_rgb(uint8_t r, uint8_t g, uint8_t b) {
	term_cell.colorfg.r = r;
	term_cell.colorfg.g = g;
	term_cell.colorfg.b = b;
}

void render_term_native_render(void) {
	NativeTermCursorPos p = term_cell.pos;
	NativeTermColor color = term_cell.colorfg;
	char c = term_cell.c;
	char buffer[100];

	//printf("\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", p.row, p.col, color.r, color.g,
	//		color.b, c);

	int ret = snprintf(buffer, 100,"\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", p.row, p.col, color.r, color.g,
			color.b, c );
	write(STDOUT_FILENO, buffer, ret);
	fprintf(stderr, "dbg: [file: %s] [line: %d] [func: %s] ret: %d\n",__FILE__, __LINE__, __func__, ret);

}


void render_term_native_render_buffer(char *buff, int size){
	write(STDOUT_FILENO, buff, size );
}

void render_term_native_init() {

}

//"\x1b[%d;%dH"
void render_term_native_draw_cell(int x, int y, char c) {
	char memory[100] = { 0 };
	int ret = snprintf(memory, 20, "\x1b[%d;%dH%c", NATIVE_SCREEN_HEIGHT-y, x, c);
	write(STDOUT_FILENO, memory, ret);

}

void render_term_native_clean_screen() {
	printf(ANSI_CLEAR);
}

static void render_term_native_cleanup() {
	render_term_native_clean_screen();
}

