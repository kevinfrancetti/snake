/*
 * snake_presenter.c
 *
 *  Created on: Oct 6, 2026
 *      Author: bomber
 */

#include "snake_presenter.h"


static RenderAPI* 		render;
static SNK_GAME_STATE*	snk_game_state;



void snk_pres_init(RenderAPI* rend, SNK_GAME_STATE* state){
	render			= rend;
	snk_game_state	= state;
}


void snk_pres_render_state(){
	Element e1 = snk_game_state->snake.components[0];

	RendAPIDrawInstructions cellDescription;
	cellDescription.pos.x	= e1.pos.x;
	cellDescription.pos.y	= e1.pos.y;
	cellDescription.fg		= (RendAPIColorRGB) {.r = 24, .g = 34, .b = 255};
	cellDescription.bg		= (RendAPIColorRGB) {.r = 100, .g = 150, .b = 255};
	cellDescription.shape	= SHAPE_CIRCLE;
	render->draw_buff(cellDescription);
	render->render_frame();

}
