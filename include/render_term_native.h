/*
 * render_term_native.h
 *
 *  Created on: Oct 8, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_TERM_NATIVE_H_
#define INCLUDE_RENDER_TERM_NATIVE_H_

#include <stdint.h>



void render_term_native_set_pos(int row, int col);
void render_term_native_set_char(char c);
void render_term_native_set_rgb(uint8_t r, uint8_t g, uint8_t b);
void render_term_native_draw(int x, int y, char c);
void render_term_native_render(void);

#endif /* INCLUDE_RENDER_TERM_NATIVE_H_ */
