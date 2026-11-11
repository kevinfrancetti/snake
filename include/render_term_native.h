/*
 * render_term_native.h
 *
 * rtn := render term native
 *
 *  Created on: Oct 8, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_TERM_NATIVE_H_
#define INCLUDE_RENDER_TERM_NATIVE_H_

#include <stdint.h>
#include <stdbool.h>

#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)

#define NATIVE_SCREEN_HEIGHT	30
#define NATIVE_SCREEN_WIDTH		90
#define FRAME_BUFF_MAX_SIZE		(NATIVE_SCREEN_HEIGHT * NATIVE_SCREEN_WIDTH)
#define SCREEN_BUFF_MAX_SIZE	(256 * KB)



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
	NativeTermColor fg;
	NativeTermColor bg;
	char c;
} NatTermCell;

typedef struct {
	NatTermCell buffer[FRAME_BUFF_MAX_SIZE];
	int len; //number of elements already in the buffer
	bool clear_pending;
	NativeTermColor clear_color;
} NatFrameBuff;

typedef struct {
	char buff[SCREEN_BUFF_MAX_SIZE];
	int len;
} ScreenBuffer;


void rtn_init(void);
ScreenBuffer* rtn_get_scrnbuff(void);//remove
NatFrameBuff* rtn_get_natcellbuff(void);//remove
ScreenBuffer rtn_create_screenbuff(void);
NatFrameBuff rtn_create_cellbuff(void);
void rtn_clean_screen(void);
void rtn_clean_screen2(ScreenBuffer*);
void rtn_cleanup(void);
void rtn_clear_color(NatFrameBuff *fb, NativeTermColor c);
void rtn_push_cell_in_buff(NatFrameBuff* ctx, NatTermCell* cell);
void rtn_render(NatFrameBuff* ctx);//remove
void rtn_render2(NatFrameBuff *cellbuff, ScreenBuffer *scrnbuff);
void rtn_set_cell(NatTermCell* cell, char c, int row, int col, \
					uint8_t fr, uint8_t fg, uint8_t fb, \
					uint8_t br, uint8_t bg, uint8_t bb);
void rtn_framebuff_reset(NatFrameBuff* ctx);
void rtn_reset_screen(void);

#endif /* INCLUDE_RENDER_TERM_NATIVE_H_ */
