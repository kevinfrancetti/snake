/*
 * render_api_test.c
 *
 *  Created on: Oct 18, 2026
 *      Author: bomber
 */


#include <stdio.h>
#include <unistd.h>

#include "render_api.h"
#include "render_factory.h"

#define BUF_SIZE	2

typedef struct{
	uint32_t ID;
}Entity;



RendAPIDrawInstructions g_cells1[BUF_SIZE];
RendAPIDrawInstructions g_cells2[BUF_SIZE];
RendAPIDrawInstructions *g_ptr_cells;



void init_cells(RendAPIDrawInstructions *cells, int size){
	for(int i = 0; i < size; i++){
		(cells + i)->pos.x = i;
		(cells + i)->pos.y = 5;
		(cells + i)->bg = (RendAPIColorRGB) {.r = 0, .g = 0, .b = 255};
	}
}

void rend_cells(RenderAPI *render, RendAPIDrawInstructions *cells, int size ){
	for(int i = 0; i < size; i++){
		render->draw_buff(cells[i]);
	}
	render->render_frame();
}

void update_cells(){

}


int main(){

	RenderAPI render = render_create(RENDER_TERMINAL);
	//ciao
	init_cells(g_cells1, BUF_SIZE);
	rend_cells(&render, g_cells1, BUF_SIZE);

	RendAPIDrawInstructions cel;
	cel.pos.x	= 0;
	cel.pos.y	= 0;
	cel.fg		= (RendAPIColorRGB) {.r = 24, .g = 34, .b = 255};
	cel.bg		= (RendAPIColorRGB) {.r = 255, .g = 0, .b = 0};
	cel.shape	= SHAPE_CIRCLE;
	render.draw_buff(cel);
	cel.pos.x = 1;
	cel.pos.y = 1;
	render.draw_buff(cel);

	cel.bg		= (RendAPIColorRGB) {.r = 0, .g = 255, .b = 255};
	cel.pos.x	= 10;
	render.draw_buff(cel);
	render.render_frame();
	render.clear_color((RendAPIColorRGB) {100,0,0});
	sleep(1);
	//render.render_frame();

	/*
	render.draw_cell(1, 1, SHAPE_CROSS);
	render.draw_cell(1, 2, SHAPE_CIRCLE);
	render.draw_cell(2, 1, SHAPE_CROSS);
	render.draw_cell(2, 2, SHAPE_CIRCLE);
	*/

	//render.draw_cell(1, 1, SHAPE_CROSS);
	//render.draw_cell(4, 5, SHAPE_CROSS);

	return 0;
}

