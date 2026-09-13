/*
 * render.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include "render.h"
#include <stdio.h>


void draw_at(int x, int y, int type){
	printf("\x1b[%d;%dH", x, y);
	if(type == CELL_WALL){
		putc('#', stdout);
	}
	if(type == CELL_VOID){
		putc('@', stdout);
	}
	fflush(stdout);

}



void terminal_clean_screen(){
	ANSI_CLEAR_SCREEN;
}

