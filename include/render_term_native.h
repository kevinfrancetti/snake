/*
 * render_term_native.h
 *
 *  Created on: Oct 8, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_TERM_NATIVE_H_
#define INCLUDE_RENDER_TERM_NATIVE_H_

#include <stdint.h>

#define NATIVE_SCREEN_HEIGHT	30
#define NATIVE_SCREEN_WIDTH		90
#define REND_NAT_MAX_CELLS		NATIVE_SCREEN_HEIGHT * NATIVE_SCREEN_WIDTH

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
	NativeTermColor 	fg;
	NativeTermColor 	bg;
	char 				c;
} NativeTermCell;

typedef struct{
	NativeTermCell	buffer[REND_NAT_MAX_CELLS];
	int				len;//number of elements already in the buffer
}NativeTermContext;

//rtn := render term native
void rtn_init(void);
void rtn_clean_screen(void);

void rtn_draw_buff(NativeTermContext* ctx, NativeTermCell* cell);
void rtn_render(NativeTermContext* ctx);
void rtn_set_cell(NativeTermCell* cell, char c, int row, int col, \
					uint8_t fr, uint8_t fg, uint8_t fb, \
					uint8_t br, uint8_t bg, uint8_t bb);
void rtn_reset_buffer(NativeTermContext* ctx);

#endif /* INCLUDE_RENDER_TERM_NATIVE_H_ */
