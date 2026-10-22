/*
 * render_api_test.c
 *
 *  Created on: Oct 18, 2026
 *      Author: bomber
 */


#include <stdio.h>

#include "render_api.h"
#include "render_factory.h"


int main(){

	RenderAPI render = render_create(RENDER_TERMINAL);

	render.draw_cell(1, 1, SHAPE_CROSS);
	render.draw_cell(1, 2, SHAPE_CIRCLE);
	render.draw_cell(2, 1, SHAPE_CROSS);
	render.draw_cell(2, 2, SHAPE_CIRCLE);
	//render.draw_cell(1, 1, SHAPE_CROSS);
	//render.draw_cell(4, 5, SHAPE_CROSS);

	return 0;
}

