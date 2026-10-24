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

	RendAPIDrawInstructions apiInfo;
	apiInfo.pos.x	= 5;
	apiInfo.pos.y	= 6;
	apiInfo.fg		= (RendAPIColorRGB) {.r = 24, .g = 34, .b = 255};
	apiInfo.bg		= (RendAPIColorRGB) {.r = 255, .g = 34, .b = 255};
	apiInfo.shape	= SHAPE_CIRCLE;

	render.draw_buff(apiInfo);
	apiInfo.bg		= (RendAPIColorRGB) {.r = 0, .g = 255, .b = 255};
	apiInfo.pos.x	= 10;
	render.draw_buff(apiInfo);
	render.render_frame();

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

