/*
 * render_native_test.c
 *
 *  Created on: Oct 9, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "render_term_native.h"

#define  DEBUG_ON
#include "debug.h"



int main() {

	/*
	char buff[100 * 1024];

	int ret = snprintf(buff + 1, 10, "ANO");
	ret = snprintf(buff, 10, "XYZ");

	uint8_t a = 254;
	printf("a: %d\n", a);
	a++;
	printf("a: %d\n", a);
	a++;
	printf("a: %d\n", a);

	printf("hi\n");
	*/
	NatCellBuff ctx =  { 0 };
	ScreenBuffer scrnbuff = { 0 };
	NativeTermCell cell;


	rtn_set_cell(&cell, 'R', 14, 15, 163, 200, 100, 240, 255, 100);
	rtn_push_cell_in_buff(&ctx, &cell);
	rtn_render2(&ctx, &scrnbuff);
	rtn_reset_cellbuff(&ctx);
	rtn_set_cell(&cell, 'R', 4, 6, 100, 100, 0, 0, 0, 255);
	rtn_push_cell_in_buff(&ctx, &cell);
	rtn_render2(&ctx, &scrnbuff);

	srand(1);

	rtn_reset_cellbuff(&ctx);
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 90; j++) {
			rtn_set_cell(&cell, 33+rand()%94 ,i , j, rand()%256, rand()%256, rand()%256, rand()%256, rand()%256, rand()%256);
			rtn_push_cell_in_buff(&ctx, &cell);
		}
	}
	rtn_render2(&ctx, &scrnbuff);

	/*
	 *
	 int len = 0;
	 for (int i = 0; i < 60; i++) {
	 for (int j = 0; j < 60; j++) {
	 //render_term_native_draw(i, j, '%');
	 len += snprintf(buff + len, sizeof(buff) - len, "\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c",
	 i, j, i, j, i + j, 'L');
	 }
	 }

	 render_term_native_render_buffer(buff, len);
	 */

	//render_term_native_draw_cell(4, 5, 'P');
	/*
	for (int i = 0; i < 90; i++) {
		for (int j = 0; j < 30; j++) {
			render_term_native_set_char('K');
			render_term_native_set_rgb(i, j, 0);
			render_term_native_set_pos(i, j);
			render_term_native_load_cell();
		}
	}
	*/
	//fprintf(stderr, "dbg: [file: %s] [line: %d] [func: %s] ret: %d\n", __FILE__,
	//__LINE__, __func__, ret);


	DEBUG1s1i("dio can", 0);

	/*
	 render_term_native_set_char('K');
	 render_term_native_set_rgb(0, 0, 255);
	 render_term_native_set_pos(12, 15);
	 render_term_native_load_cell();

	render_term_native_set_char('Z');
	render_term_native_set_rgb(255, 0, 0);
	render_term_native_set_pos(9, 9);
	render_term_native_load_cell();
	render_term_native_render2();
	*/
	//render_term_native_render();
	//render_term_native_set_char('U');
	//render_term_native_render();

	return 0;
}
