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
} NatTermColor;

typedef struct {
	int row;
	int col;
} NatTermCursorPos;

typedef struct {
	NatTermCursorPos pos;
	NatTermColor fg;
	NatTermColor bg;
	char c;
} NatTermCell;

typedef struct {
	NatTermCell buffer[FRAME_BUFF_MAX_SIZE];
	int len; //number of elements already in the buffer
	bool clear_pending;
	NatTermColor clear_color;
} NatFrameBuff;

typedef struct {
	char buff[SCREEN_BUFF_MAX_SIZE];
	int len;
} NatScreenBuffer;


void rtn_init(void);
NatScreenBuffer rtn_create_screenbuff(void);
NatFrameBuff rtn_create_cellbuff(void);
void rtn_push_cell_in_buff(NatFrameBuff* ctx, NatTermCell* cell);
void rtn_render(NatFrameBuff *cellbuff, NatScreenBuffer *scrnbuff);
void rtn_set_cell(NatTermCell* cell, char c, int row, int col, \
					uint8_t fr, uint8_t fg, uint8_t fb, \
					uint8_t br, uint8_t bg, uint8_t bb);
void rtn_clear_color(NatFrameBuff *fb, NatTermColor c);
void rtn_framebuff_reset(NatFrameBuff* ctx);

void rtn_screen_clean_now(void);
void rtn_screen_reset_now(void);
void rtn_cleanup(void);

#endif /* INCLUDE_RENDER_TERM_NATIVE_H_ */
