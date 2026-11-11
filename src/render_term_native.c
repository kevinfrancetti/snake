/*
 * render_term_native.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
//#include <ioctl.h>
#include "render_term_native.h"

#include "debug.h"

/*
#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)
*/

#define CSI					"\x1b["   //Control Sequence Introducer
#define ANSI_CLEAR			CSI "2J"
#define ANSI_RESET			CSI "0m"
#define ANSI_CURSOR_OFF		CSI "?25l"
#define ANSI_CURSOR_ON		CSI "?25h"

#define ANSI_CURSOR_POS		CSI "%d;%dH"
#define ANSI_FG_RGB			CSI "38;2;%d;%d;%dm"
#define ANSI_BG_RGB			CSI "48;2;%d;%d;%dm"
#define ANSI_CELL_FMT		ANSI_CURSOR_POS ANSI_FG_RGB ANSI_BG_RGB "%c"

//TODO change this shit, make a local factory of this 2 buffers
/*
static ScreenBuffer tmpscrnbuff = { 0 }; //screen buffer of chars
static NatCellBuff cellbuff = { 0 };

ScreenBuffer* rtn_get_scrnbuff(){
	return &tmpscrnbuff;
}

NatCellBuff* rtn_get_natcellbuff(){
	return &cellbuff;
}

//Old but not sure what to keep
void rtn_render(NatCellBuff *ctx) {
	tmpscrnbuff.len = 0;
	for (int i = 0; i < ctx->len; i++) {
		NativeTermCell c = ctx->buffer[i];

		tmpscrnbuff.len += snprintf(tmpscrnbuff.buff + tmpscrnbuff.len,
				sizeof(tmpscrnbuff.buff) - tmpscrnbuff.len,
				ANSI_CELL_FMT, c.pos.row, c.pos.col, c.fg.r, c.fg.g, c.fg.b,
				c.bg.r, c.bg.g, c.bg.b, c.c);

	}
	render_term_native_render_buffer(tmpscrnbuff.buff, tmpscrnbuff.len);
	//rtn_reset_screen();
}

*/

ScreenBuffer rtn_create_screenbuff(){
	ScreenBuffer buff = {.len = 0};
	return buff;
}

NatCellBuff rtn_create_cellbuff(){
	NatCellBuff buff = { .len = 0 };
	return buff;
}


void rtn_set_cell(NativeTermCell* cell, char c, int row, int col, \
					uint8_t fr, uint8_t fg, uint8_t fb, \
					uint8_t br, uint8_t bg, uint8_t bb){

	cell->c		= c;
	cell->pos	= (NativeTermCursorPos)	{row, col};
	cell->fg	= (NativeTermColor)		{fr, fg, fb} ;
	cell->bg	= (NativeTermColor)		{br, bg, bb} ;
}

void rtn_push_cell_in_buff(NatCellBuff* cb, NativeTermCell* cell){
	if(cb->len >= REND_NAT_MAX_CELLS){
		DEBUG1s("FULL NATIVE CELL BUFFER");
		return;
	}
	cb->buffer[cb->len++] = *cell;
}

static void render_term_native_render_buffer(char *buff, int size) {
	write(STDOUT_FILENO, buff, size);
}

//TODO when time check if len is not greater than size, as suggested by snprintf manual.
void rtn_render2(NatCellBuff *cellbuff, ScreenBuffer *sb) {

	for (int i = 0; i < cellbuff->len; i++) {
		NativeTermCell c = cellbuff->buffer[i];

		sb->len += snprintf(sb->buff + sb->len, sizeof(sb->buff) - sb->len,
		ANSI_CELL_FMT, c.pos.row, c.pos.col, c.fg.r, c.fg.g, c.fg.b, c.bg.r,
				c.bg.g, c.bg.b, c.c);

	}
	render_term_native_render_buffer(sb->buff, sb->len);
	//rtn_reset_screen();
	sb->len = 0;
}


void rtn_reset_cellbuff(NatCellBuff* cb){
	cb->len = 0;
}


void rtn_init() {
	write(STDOUT_FILENO, ANSI_CURSOR_OFF, sizeof(ANSI_CURSOR_OFF)-1);
}

void rtn_reset_screen() {
	write(STDOUT_FILENO, ANSI_RESET, sizeof(ANSI_RESET)-1);
}

//this function mimics the opengl style(clean the "back" buffer with a background)
void rtn_clear_color(NatCellBuff *cb, NativeTermColor c){//ancora incompleto con errori.
	cb->len = 0;
	NativeTermCell cell = { .bg = c };
	for(int i = 0; i < REND_NAT_MAX_CELLS; i++){
		rtn_push_cell_in_buff(cb, &cell);
	}
}

void rtn_clean_screen2(ScreenBuffer *sb){
	sb->len += snprintf(sb->buff + sb->len, sizeof(sb->buff) - sb->len, ANSI_CLEAR);
}

void rtn_clean_screen() {
	write(STDOUT_FILENO, ANSI_CLEAR, sizeof(ANSI_CLEAR)-1);
}

void rtn_cleanup() {
	rtn_reset_screen();
	write(STDOUT_FILENO, ANSI_CURSOR_ON, sizeof(ANSI_CURSOR_ON)-1);
	rtn_clean_screen();
}

