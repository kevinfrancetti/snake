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
//#include "render_styles.h"//TODO

#define CSI					"\x1b["   //Control Sequence Introducer
#define ANSI_CLEAR			CSI "2J"
//#define ANSI_CLEAR_SCREEN printf(CSI "2J")

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} NativeTermColor;

typedef struct {
	int row;
	int col;
} NativeTermCursorPos;

typedef struct {
	NativeTermCursorPos pos;
	NativeTermColor 	color;
	char 				c;
} NativeTermContext;

static NativeTermContext g_term_ctx; //terminal context

void render_term_native_set_char(char c) {
	g_term_ctx.c = c;
}

void render_term_native_set_pos(int row, int col) {
	g_term_ctx.pos.row = row;
	g_term_ctx.pos.col = col;
}

void render_term_native_set_rgb(uint8_t r, uint8_t g, uint8_t b) {
	g_term_ctx.color.r = r;
	g_term_ctx.color.g = g;
	g_term_ctx.color.b = b;
}

void render_term_native_render(void) {
	NativeTermCursorPos p = g_term_ctx.pos;
	NativeTermColor color = g_term_ctx.color;
	char c = g_term_ctx.c;
	char buffer[100];

	//printf("\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", p.row, p.col, color.r, color.g,
	//		color.b, c);

	int ret = snprintf(buffer, 100,"\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", p.row, p.col, color.r, color.g,
			color.b, c );
	write(STDOUT_FILENO, buffer, ret);
	fprintf(stderr, "ret=%d\n", ret);

}

static void render_term_native_init() {

}

//"\x1b[%d;%dH"
void render_term_native_draw(int x, int y, char c) {
	char memory[100] = { 0 };
	snprintf(memory, 20, "\x1b[%d;%dH%c", x, y, c);
	write(STDOUT_FILENO, memory, 20);

}

static void render_term_native_clean_screen() {
	printf(ANSI_CLEAR);
}

static void render_term_native_cleanup() {
	render_term_native_clean_screen();
}

