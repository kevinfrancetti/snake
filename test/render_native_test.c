/*
 * render_native_test.c
 *
 *  Created on: Oct 9, 2026
 *      Author: bomber
 */


#include <stdio.h>
#include <stdint.h>
#include "render_term_native.h"



int main(){

	char buff[100];

	int ret = snprintf(buff + 1, 10, "ANO");
	ret = snprintf(buff, 10, "XYZ");

	uint8_t a = 254;
	printf("a: %d\n", a);
	a++;
	printf("a: %d\n", a);
	a++;
	printf("a: %d\n", a);

	printf("hi\n");

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			render_term_native_draw(i,j, '%');

		}
	}
	render_term_native_draw(4, 5, 'P');

	render_term_native_set_char('K');
	render_term_native_set_rgb(0,0,255);
	render_term_native_set_pos(12, 15);
	render_term_native_render();
	render_term_native_set_char('U');
	render_term_native_render();
	return 0;
}
