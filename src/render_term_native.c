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

static NativeTermCell term_cell = { 0 }; //terminal cell testing TODO

typedef struct {
	char buff[128 * KB];
	int len;
} ScreenBuffer;


static ScreenBuffer screen_buff = { 0 };

void rtn_set_cell(NativeTermCell* cell, char c, int row, int col, \
					uint8_t fr, uint8_t fg, uint8_t fb, \
					uint8_t br, uint8_t bg, uint8_t bb){

	cell->c			= c;
	cell->pos		= (NativeTermCursorPos)	{row, col};
	cell->colorfg	= (NativeTermColor)		{fr, fg, fb} ;
	cell->colorbg	= (NativeTermColor)		{br, bg, bb} ;
}

void rtn_push(NativeTermContext* ctx, NativeTermCell* cell){
	if(ctx->len >= REND_NAT_MAX_CELLS){
		printf("Too big\n");
		return;
	}
	ctx->buffer[ctx->len++] = *cell;
}

void rtn_render(NativeTermContext* ctx){
	for (int i = 0; i < REND_NAT_MAX_CELLS; i++) {
			NativeTermCell cell = ctx->buffer[i];

			screen_buff.len += snprintf(screen_buff.buff + screen_buff.len, sizeof(screen_buff.buff) - screen_buff.len,
					"\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", cell.pos.row, cell.pos.col,
					cell.colorfg.r, cell.colorfg.g, cell.colorfg.b, cell.c);
			//printf("ctx.len:%d\n", ctx.len);
		}
		render_term_native_render_buffer(screen_buff.buff, screen_buff.len);
}



void render_term_native_render(void) {
	NativeTermCursorPos p = term_cell.pos;
	NativeTermColor color = term_cell.colorfg;
	char c = term_cell.c;
	char buffer[100];

	//printf("\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", p.row, p.col, color.r, color.g,
	//		color.b, c);

	int ret = snprintf(buffer, 100, "\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c", p.row,
			p.col, color.r, color.g, color.b, c);
	write(STDOUT_FILENO, buffer, ret);
	fprintf(stderr, "dbg: [file: %s] [line: %d] [func: %s] ret: %d\n", __FILE__,
	__LINE__, __func__, ret);

}

void render_term_native_render_buffer(char *buff, int size) {
	write(STDOUT_FILENO, buff, size);
}

void render_term_native_draw_cell(int raw, int col, char c) {
	char memory[100] = { 0 };
	int ret = snprintf(memory, 20, "\x1b[%d;%dH%c", col, raw, c);
	write(STDOUT_FILENO, memory, ret);

}

void render_term_native_init() {

}

void render_term_native_clean_screen() {
	printf(ANSI_CLEAR);
}

static void render_term_native_cleanup() {
	render_term_native_clean_screen();
}

