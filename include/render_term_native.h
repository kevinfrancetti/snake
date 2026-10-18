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
	NativeTermColor 	colorfg;
	NativeTermColor 	colorbg;
	char 				c;
} NativeTermCell;

typedef struct{
	NativeTermCell buffer[100];
}NativeTermContext;


void render_term_native_init(void);
void render_term_native_set_pos(int row, int col);
void render_term_native_set_char(char c);
void render_term_native_set_rgb(uint8_t r, uint8_t g, uint8_t b);
void render_term_native_draw_cell(int x, int y, char c);
void render_term_native_render(void);
void render_term_native_render_buffer(char *buff, int size);
void render_term_native_clean_screen(void);

#endif /* INCLUDE_RENDER_TERM_NATIVE_H_ */
