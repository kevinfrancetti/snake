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

#include "debug.h"

#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)

#define CSI					"\x1b["   //Control Sequence Introducer
#define ANSI_CLEAR			CSI "2J"
//#define ANSI_CLEAR_SCREEN printf(CSI "2J")


typedef struct {
	char buff[256 * KB];
	int len;
} ScreenBuffer;


static ScreenBuffer scrn_buff = { 0 }; //screen buffer of chars

void rtn_set_cell(NativeTermCell* cell, char c, int row, int col, \
					uint8_t fr, uint8_t fg, uint8_t fb, \
					uint8_t br, uint8_t bg, uint8_t bb){

	cell->c		= c;
	cell->pos	= (NativeTermCursorPos)	{row, col};
	cell->fg	= (NativeTermColor)		{fr, fg, fb} ;
	cell->bg	= (NativeTermColor)		{br, bg, bb} ;
}

void rtn_draw_buff(NativeTermContext* ctx, NativeTermCell* cell){
	if(ctx->len >= REND_NAT_MAX_CELLS){
		DEBUG1s1i("Too big", 666);
		return;
	}
	ctx->buffer[ctx->len++] = *cell;
}

static void render_term_native_render_buffer(char *buff, int size) {
	write(STDOUT_FILENO, buff, size);
}

void rtn_render(NativeTermContext* ctx){
	scrn_buff.len = 0;
	for (int i = 0; i < ctx->len; i++) {
			NativeTermCell c = ctx->buffer[i];

			scrn_buff.len += snprintf(scrn_buff.buff + scrn_buff.len, sizeof(scrn_buff.buff) - scrn_buff.len,
					"\x1b[%d;%dH\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm%c", c.pos.row, c.pos.col,
					c.fg.r, c.fg.g, c.fg.b, c.bg.r, c.bg.g, c.bg.b, c.c);
		}
		render_term_native_render_buffer(scrn_buff.buff, scrn_buff.len);
}

void rtn_reset_buffer(NativeTermContext* ctx){
	ctx->len = 0;
}


void rtn_init() {

}

void rtn_clean_screen() {
	printf(ANSI_CLEAR);
}

static void render_term_native_cleanup() {
	rtn_clean_screen();
}

